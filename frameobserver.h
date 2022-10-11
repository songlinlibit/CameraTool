#ifndef FRAMEOBSERVER_H
#define FRAMEOBSERVER_H

#include <QObject>
#include <mutex>
#include"Include/VimbaCPP.h"
#include<queue>
class FrameObserver : public QObject,
        virtual public AVT::VmbAPI::IFrameObserver
{
    Q_OBJECT
public:
    explicit FrameObserver(AVT::VmbAPI::CameraPtr pCamera,QObject *parent = nullptr);

    virtual void FrameReceived( const AVT::VmbAPI::FramePtr pFrame );


    AVT::VmbAPI::FramePtr GetFrame();


        void ClearFrameQueue();

      private:

        std::queue<AVT::VmbAPI::FramePtr> m_Frames;
        std::mutex m_FramesMutex;

      signals:
        //
        // The frame received event (Qt signal) that notifies about a new incoming frame
        //
        // Parameters:
        //  [out]   status          The frame receive status
        //
        void FrameReceivedSignal( int status );

signals:


};

#endif // FRAMEOBSERVER_H
