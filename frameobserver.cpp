#include "frameobserver.h"

FrameObserver::FrameObserver(AVT::VmbAPI::CameraPtr pCamera,QObject *parent)
    : AVT::VmbAPI::IFrameObserver{pCamera},QObject{parent}
{

}

void FrameObserver::FrameReceived( const AVT::VmbAPI::FramePtr pFrame )
{
    bool bQueueDirectly = true;
    VmbFrameStatusType eReceiveStatus;

    if(     0 != receivers(SIGNAL(FrameReceivedSignal(int)) )
        &&  VmbErrorSuccess == pFrame->GetReceiveStatus( eReceiveStatus ) )
    {
        // Lock the frame queue
        m_FramesMutex.lock();
        // Add frame to queue
        m_Frames.push( pFrame );
        // Unlock frame queue
        m_FramesMutex.unlock();
        // Emit the frame received signal
        emit FrameReceivedSignal( eReceiveStatus );
        bQueueDirectly = false;
    }

    // If any error occurred we queue the frame without notification
    if( true == bQueueDirectly )
    {
        m_pCamera->QueueFrame( pFrame );
    }
}

//
// After the view has been notified about a new frame it can pick it up.
// It is then removed from the internal queue
//
// Returns:
//  A shared pointer to the latest frame
//
AVT::VmbAPI::FramePtr FrameObserver::GetFrame()
{
    // Lock the frame queue
    m_FramesMutex.lock();
    // Pop frame from queue
    AVT::VmbAPI::FramePtr res;
    if( !m_Frames.empty() )
    {
        res = m_Frames.front();
        m_Frames.pop();
    }
    // Unlock frame queue
    m_FramesMutex.unlock();
    return res;
}

//
// Clears the internal (double buffering) frame queue
//
void FrameObserver::ClearFrameQueue()
{
    // Lock the frame queue
    m_FramesMutex.lock();
    // Clear the frame queue and release the memory
    std::queue<AVT::VmbAPI::FramePtr> empty;
    std::swap( m_Frames, empty );
    // Unlock the frame queue
    m_FramesMutex.unlock();


} // namespace AVT::VmbAPI::Examples
