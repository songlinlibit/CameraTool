#include "imageprocessthread.h"
#include "Include/SharedPointerDefines.h"
#include "VimbaC/Include/VmbCommonTypes.h"
#include "frameobserver.h"
#include <memory>
#include <string>
#include "./VimbaImageTransform/Include/VmbTransform.h"
#include "qdebug.h"
#include "qimage.h"
imageProcessThread::imageProcessThread(int id,QObject* parent):QObject{parent},m_system(VimbaSystem::GetInstance()),
    id(id)
{
   m_bIsStreaming=false;
}

enum    { NUM_FRAMES=3, };



imageProcessThread::~imageProcessThread()
{
}

std::string imageProcessThread::ErrorCodeToMessage( VmbErrorType eErr ) const
{
    return "nullptr";
}

VmbErrorType imageProcessThread::StartUp()
{
    VmbErrorType res;

    // Start Vimba
    res = m_system.Startup();
    if( VmbErrorSuccess == res )
    {
        // This will be wrapped in a shared_ptr so we don't delete it
        SP_SET( m_pCameraObserver , new CameraObserver() );
        // Register an observer whose callback routine gets triggered whenever a camera is plugged in or out
        res = m_system.RegisterCameraListObserver( m_pCameraObserver );
    }

    return res;
}

//
// Shuts down the API
//
void imageProcessThread::ShutDown()
{
    // Release Vimba
    m_system.Shutdown();
}
/*** helper function to set image size to a value that is dividable by modulo 2 and a multiple of the increment.
\note this is needed because VimbaImageTransform does not support odd values for some input formats
*/
inline VmbErrorType SetValueIntMod2( const CameraPtr &camera, const std::string &featureName, VmbInt64_t &storage )
{
    VmbErrorType    res;
    FeaturePtr      pFeature;
    VmbInt64_t      minValue = 0;
    VmbInt64_t      maxValue = 0;
    VmbInt64_t      incrementValue = 0;

    res = SP_ACCESS( camera )->GetFeatureByName( featureName.c_str(), pFeature );
    if( VmbErrorSuccess != res )
    {
        return res;
    }

    res = SP_ACCESS( pFeature )->GetRange( minValue, maxValue );
    if( VmbErrorSuccess != res )
    {
        return res;
    }

    res = SP_ACCESS( pFeature )->GetIncrement( incrementValue);
    if( VmbErrorSuccess != res)
    {
        return res;
    }

    maxValue = maxValue - ( maxValue % incrementValue );
    if( maxValue % 2 != 0)
    {
        maxValue -= incrementValue;
    }

    res = SP_ACCESS( pFeature )->SetValue( maxValue );
    if( VmbErrorSuccess != res )
    {
        return res;
    }

    storage = maxValue;
    return res;
}

VmbErrorType imageProcessThread::ConnectCamera( const std::string &rStrCameraID ){
    // Open the desired camera by its ID
    VmbErrorType res = m_system.OpenCameraByID( rStrCameraID.c_str(), VmbAccessModeFull, m_pCamera );
    if( VmbErrorSuccess == res ){
        m_connected_state = true;
        emit this->streamStarted();
    }else {
        qDebug()<<"connect camera fail: "<<res;
    }
    return res;
}

VmbErrorType imageProcessThread::StartContinuousImageAcquisition()
{
    VmbErrorType res;
    if( m_connected_state )
    {
        // Set the GeV packet size to the highest possible value
        // (In this example we do not test whether this cam actually is a GigE cam)
        FeaturePtr pCommandFeature;
        if(VmbErrorSuccess != SP_ACCESS( m_pCamera )->GetFeatureByName( "TriggerMode", pCommandFeature ))
        {
            qDebug()<<"error";
        }
        else
        {
           auto rec=SP_ACCESS( pCommandFeature )->SetValue("Off");
           qDebug()<<"Setting triggermode:"<<rec;
        }

        if( VmbErrorSuccess == SP_ACCESS( m_pCamera )->GetFeatureByName( "GVSPAdjustPacketSize", pCommandFeature ) )
        {
            if( VmbErrorSuccess == SP_ACCESS( pCommandFeature )->RunCommand() )
            {
                bool bIsCommandDone = false;
                do
                {
                    if( VmbErrorSuccess != SP_ACCESS( pCommandFeature )->IsCommandDone( bIsCommandDone ) )
                    {
                        break;
                    }
                } while( false == bIsCommandDone );
            }
        }
        res = SetValueIntMod2( m_pCamera,"Width", m_nWidth );
        if( VmbErrorSuccess == res )
        {
            res = SetValueIntMod2( m_pCamera, "Height", m_nHeight );
            if( VmbErrorSuccess == res )
            {
                // Store currently selected image format
                FeaturePtr pFormatFeature;
                res = SP_ACCESS( m_pCamera )->GetFeatureByName( "PixelFormat", pFormatFeature );
                if( VmbErrorSuccess == res )
                {
                    res = SP_ACCESS( pFormatFeature )->GetValue( m_nPixelFormat );
                    if ( VmbErrorSuccess == res )
                    {
                        // Create a frame observer for this camera (This will be wrapped in a shared_ptr so we don't delete it)

                        SP_SET( m_pFrameObserver , new FrameObserver( m_pCamera ) );
                        // Start streaming
                        res = SP_ACCESS( m_pCamera )->StartContinuousImageAcquisition( NUM_FRAMES,  m_pFrameObserver );

                        connect(m_pFrameObserver.get(),&FrameObserver::FrameReceivedSignal,
                                this,&imageProcessThread::recvImage);
                        m_bIsStreaming=true;
                        m_Image=QImage(GetWidth(),GetHeight(),QImage::Format_RGB888);
                    }
                }
            }
        }
        if ( VmbErrorSuccess != res )
        {
            // If anything fails after opening the camera we close it
            SP_ACCESS( m_pCamera )->Close();
        }
    }
    else
    {
        qDebug()<<"connect unsucess,error code:"<<res;
    }
    m_Image = QImage(GetWidth(), GetHeight(), QImage::Format_RGB888 );
    VimbaSystem&        sys         = VimbaSystem::GetInstance();           // Get a reference to the VimbaSystem singleton
    // Print out version of Vimba
    VmbErrorType        err          ;                 // Initialize the Vimba API
    FeaturePtrVector    features;                                           // A vector of std::shared_ptr<AVT::VmbAPI::Feature> objects
    err = m_pCamera->GetFeatures( features );

    QMap<QString,FeaturePtr> tmp;

    for(auto& feature:features)
    {
        std::string name;
        feature->GetName(name);
        QString r=QString::fromStdString(name);

        tmp.insert(r,feature);
    }

    emit sendFeatures(tmp);
    return res;
}

VmbErrorType imageProcessThread::StopContinuousImageAcquisition()
{
    if(m_bIsStreaming==false)
    {
        return VmbErrorSuccess;
    }
    // Stop streaming
    SP_ACCESS( m_pCamera )->StopContinuousImageAcquisition();
    m_bIsStreaming=false;

    emit streamStopped();

    // Close camera
    m_connected_state = false;
    return  m_pCamera->Close();
};


CameraPtrVector imageProcessThread::GetCameraList()
{
    CameraPtrVector cameras;
    // Get all known cameras
    if( VmbErrorSuccess == m_system.GetCameras( cameras ) )
    {
        // And return them
        return cameras;
    }
    return CameraPtrVector();
}


int imageProcessThread::GetWidth() const
{
    return static_cast<int>(m_nWidth);
}


int imageProcessThread::GetHeight() const
{
    return static_cast<int>(m_nHeight);
}


VmbPixelFormatType imageProcessThread::GetPixelFormat() const
{
    return static_cast<VmbPixelFormatType>(m_nPixelFormat);
}


FramePtr imageProcessThread::GetFrame()
{
     return m_pFrameObserver->GetFrame();
}

void imageProcessThread::ClearFrameQueue()
{
     m_pFrameObserver->ClearFrameQueue();
}


VmbErrorType imageProcessThread::QueueFrame( FramePtr pFrame )
{
    return SP_ACCESS( m_pCamera )->QueueFrame( pFrame );
}


QObject* imageProcessThread::GetCameraObserver()
{
   return nullptr;
}

//
// Returns the frame observer as QObject pointer to connect their signals to the view's slots
//
QObject* imageProcessThread::GetFrameObserver()
{
   return SP_DYN_CAST( m_pFrameObserver, FrameObserver ).get();
}


std::string imageProcessThread::GetVersion() const
{
   return "";
}


VmbErrorType imageProcessThread::CopyToImage( VmbUchar_t *pInBuffer, VmbPixelFormat_t ePixelFormat, QImage &pOutImage, const float *Matrix /*= NULL */ )
{
    const int           nHeight = GetHeight();
    const int           nWidth  = GetWidth();

    VmbImage            SourceImage,DestImage;
    VmbError_t          Result;
    SourceImage.Size    = sizeof( SourceImage );
    DestImage.Size      = sizeof( DestImage );

    Result = VmbSetImageInfoFromPixelFormat( ePixelFormat, nWidth, nHeight, & SourceImage );
    if( VmbErrorSuccess != Result )
    {
        qDebug( "Could not set source image info", static_cast<VmbErrorType>( Result ) );
        return static_cast<VmbErrorType>( Result );
    }
    QString             OutputFormat;
    const int           bytes_per_line = pOutImage.bytesPerLine();
    switch( pOutImage.format() )
    {
    default:
        qDebug( "unknown output format",VmbErrorBadParameter );
        return VmbErrorBadParameter;
    case QImage::Format_RGB888:
        if( nWidth*3 != bytes_per_line )
        {
            qDebug( "image transform does not support stride",VmbErrorWrongType );
            return VmbErrorWrongType;
        }
        OutputFormat = "RGB24";
        break;
    }
    Result = VmbSetImageInfoFromString( OutputFormat.toStdString().c_str(), OutputFormat.length(),nWidth,nHeight, &DestImage );
    if( VmbErrorSuccess != Result )
    {
        qDebug( "could not set output image info",static_cast<VmbErrorType>( Result ) );
        return static_cast<VmbErrorType>( Result );
    }
    SourceImage.Data    = pInBuffer;
    DestImage.Data      = pOutImage.bits();
    // do color processing?
    if( NULL != Matrix )
    {
        VmbTransformInfo TransformParameter;
        Result = VmbSetColorCorrectionMatrix3x3( Matrix, &TransformParameter );
        if( VmbErrorSuccess == Result )
        {
            Result = VmbImageTransform( &SourceImage, &DestImage, &TransformParameter,1 );
        }
        else
        {
            qDebug( "could not set matrix t o transform info ", static_cast<VmbErrorType>( Result ) );
            return static_cast<VmbErrorType>( Result );
        }
    }
    else
    {
        Result = VmbImageTransform( &SourceImage, &DestImage,NULL,0 );
    }
    if( VmbErrorSuccess != Result )
    {
        qDebug( "could not transform image", static_cast<VmbErrorType>( Result ) );
        return static_cast<VmbErrorType>( Result );
    }
    return static_cast<VmbErrorType>( Result );
}

void imageProcessThread::recvImage(int status)
{

    if( true == m_bIsStreaming )
       {
           // Pick up frame
           FramePtr pFrame = m_pFrameObserver->GetFrame();
           if( SP_ISNULL( pFrame ) )
           {
               qDebug("frame pointer is NULL, late frame ready message");
               return;
           }
           // See if it is not corrupt
           if( VmbFrameStatusComplete == status )
           {
               VmbUchar_t *pBuffer;
               VmbErrorType err = SP_ACCESS( pFrame )->GetImage( pBuffer );
               if( VmbErrorSuccess == err )
               {
                   VmbUint32_t nSize;
                   err = SP_ACCESS( pFrame )->GetImageSize( nSize );
                   if( VmbErrorSuccess == err )
                   {
                       VmbPixelFormatType ePixelFormat = GetPixelFormat();
                       if( ! m_Image.isNull() )
                       {
                           // Copy it
                           // We need that because Qt might repaint the view after we have released the frame already
                           if(false)
                           {
                               static const VmbFloat_t Matrix[] = {    8.0f, 0.1f, 0.1f, // this matrix just makes a quick color to mono conversion
                                                                       0.1f, 0.8f, 0.1f,
                                                                       0.0f, 0.0f, 1.0f };
                               if( VmbErrorSuccess != CopyToImage( pBuffer,ePixelFormat, m_Image, Matrix ) )
                               {
                                   qDebug("image copying failed");
                               }
                           }
                           else
                           {
                               CopyToImage( pBuffer,ePixelFormat, m_Image );
                           }

                           // Display it
                          emit pixmapReady(QPixmap::fromImage(m_Image));
                       }
                   }
               }
           }
           else
           {
               // If we receive an incomplete image we do nothing but logging
               qDebug()<<"Failure in receiving image: "<<status;
           }

           // And queue it to continue streaming
          QueueFrame( pFrame );
       }
}
