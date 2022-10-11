#include "cameraobserver.h"
#include "Include/ICameraListObserver.h"
#include "VimbaC/Include/VmbCommonTypes.h"
#include <QDebug>>

CameraObserver::CameraObserver(QObject *parent)
    : QObject{parent},AVT::VmbAPI::ICameraListObserver{}
{

}

void CameraObserver::CameraListChanged ( AVT::VmbAPI::CameraPtr pCam, AVT::VmbAPI::UpdateTriggerType reason )
{
        AVT::VmbAPI::VimbaSystem& sys = AVT::VmbAPI::VimbaSystem::GetInstance();   // Get a reference to the VimbaSystem singleton
        // Initialize the Vimba API
        AVT::VmbAPI::CameraPtrVector     cameras;                       // A vector of std::shared_ptr<AVT::VmbAPI::Camera> objects

        VmbErrorType err;
        err = sys.GetCameras(cameras);

        if( VmbErrorSuccess == err )
        {
            listOfCameraName.clear();
            for(auto i :cameras)
            {
                std::string tmp;
                i->GetID(tmp);
                qDebug()<<"CameraObserver::CameraListChanged find camera"<<QString::fromStdString(tmp);
                listOfCameraName.push_back(QString::fromStdString(tmp));
            }

            emit updateDeviceList();
        }
}
