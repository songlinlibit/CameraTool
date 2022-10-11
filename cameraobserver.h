#ifndef CAMERAOBSERVER_H
#define CAMERAOBSERVER_H

#include <QObject>
#include<Include/VimbaSystem.h>
#include<Include/ICameraListObserver.h>
class CameraObserver : public QObject,
        public AVT::VmbAPI::ICameraListObserver
{
Q_OBJECT
public:
    explicit CameraObserver(QObject *parent = nullptr);
    virtual void CameraListChanged( AVT::VmbAPI::CameraPtr pCam,
                                    AVT::VmbAPI::UpdateTriggerType reason );

    QVector<QString>& getCameraNames(){return listOfCameraName;};
signals:
    void updateDeviceList ();

private:
    QVector<QString> listOfCameraName;
};

#endif // CAMERAOBSERVER_H
