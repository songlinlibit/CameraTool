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

QImage::Format convertPixelFormat(VmbPixelFormatType srcFormat){
    QImage::Format temp;
    switch(srcFormat){
        case VmbPixelFormatMono8:
        case VmbPixelFormatMono12:
            temp = QImage::Format_Grayscale8;
            break;
        case VmbPixelFormatMono16:
            temp = QImage::Format_Grayscale16;
            break;
        default:
            temp = QImage::Format_RGB888;
    }
    return temp;
}

bool isFullBitsFormat(VmbPixelFormatType srcFormat){
    switch(srcFormat){
        case VmbPixelFormatMono16:
        case VmbPixelFormatMono12:
        case VmbPixelFormatMono8:
            return true;
        default:
            return false;
    }
    return false;
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
                qDebug()<<"m_nWidth: "<<m_nWidth<<",  m_nHeight: "<<m_nHeight; 
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
                        m_Image=QImage(GetWidth(),GetHeight(),QImage::Format_RGB32);
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
        qDebug()<<"connect unsucess";
    }
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
    return err;
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

    Result = VmbSetImageInfoFromPixelFormat( ePixelFormat, nWidth, nHeight, &SourceImage );
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
    case QImage::Format_RGB32:
        OutputFormat = "BGRA32";
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

    Result = VmbImageTransform( &SourceImage, &DestImage,NULL,0 );
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
           VmbPixelFormatType ePixelFormat = GetPixelFormat();
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
                       if( ! m_Image.isNull() )
                       {
                          CopyToImage( pBuffer,ePixelFormat, m_Image );
                          // qDebug()<<QString("imageBits.format() : %1").arg(m_Image.format());
                          emit pixmapReady(QPixmap::fromImage(m_Image));
                       }
                   }
               }
           }
           else
           {
               qDebug()<<"Failure in receiving image: "<<status;
           }
           if (isFullBitsFormat(ePixelFormat)) {
              m_FullBitFrame = tFrameInfo(pFrame, false);
              emit fullBitPixmapReady(m_FullBitFrame);

           }
           QueueFrame( pFrame );
       }
}
