#ifndef IMAGEPROCESSTHREAD_H
#define IMAGEPROCESSTHREAD_H


#include <QThread>
#include <QObject>
#include <memory>

#include"Include/VimbaCPP.h"
#include "cameraobserver.h"
#include "qpixmap.h"
#include<QMap>
class FrameObserver;
using namespace AVT::VmbAPI;
class imageProcessThread : public QObject
{
    Q_OBJECT
public:
    imageProcessThread(int id,QObject* parent=nullptr);
    ~imageProcessThread();
    VmbErrorType        StartUp();
    VmbErrorType CopyToImage( VmbUchar_t *pInBuffer, VmbPixelFormat_t ePixelFormat, QImage &pOutImage, const float *Matrix = NULL );

        //
        // Shuts down the API
        //
        void                ShutDown();

        //

        VmbErrorType        StartContinuousImageAcquisition();
        VmbErrorType        StopContinuousImageAcquisition();
        VmbErrorType        ConnectCamera( const std::string &rStrCameraID );
        bool                isConnected(){ return m_connected_state;}

        int                 GetWidth() const;

        int                 GetHeight() const;

        //

        VmbPixelFormatType  GetPixelFormat() const;
        CameraPtrVector     GetCameraList();


        FramePtr            GetFrame();


        //
        VmbErrorType        QueueFrame( FramePtr pFrame );

        void                ClearFrameQueue();


        QObject*            GetCameraObserver();


        QObject*            GetFrameObserver();


        std::string         ErrorCodeToMessage( VmbErrorType eErr ) const;


        std::string         GetVersion() const;
        CameraObserver* ob;
        CameraPtr           m_pCamera;

  signals:
        void pixmapReady(QPixmap);
        void streamStarted();
        void streamStopped();
        void sendFeatures(QMap<QString,FeaturePtr>);
  private:
        // A reference to our Vimba singleton
        VimbaSystem&                m_system;
        // The currently streaming camera

        // Every camera has its own frame observer
        AVT::VmbAPI::shared_ptr<FrameObserver>          m_pFrameObserver;
        // Our camera observer
        ICameraListObserverPtr      m_pCameraObserver;
        // The current pixel format
        VmbInt64_t                  m_nPixelFormat;
        // The current width
        VmbInt64_t                  m_nWidth;
        // The current height
        VmbInt64_t                  m_nHeight;
        bool m_bIsStreaming;


        QImage  m_Image;
        bool    m_connected_state;
        int id;
private:
        void recvImage(int status);
};

#endif // IMAGEPROCESSTHREAD_H
