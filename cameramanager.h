#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H



#include <QObject>
#include<QPixmap>
#include<camerainfo.h>
#include "Include/SharedPointerDefines.h"
#include"Include/VimbaCPP.h"
#include<QMap>
using AVT::VmbAPI::FeaturePtr;
class CameraObserver;
class imageProcessThread;
class cameraManager : public QObject
{
    Q_OBJECT
public:
    explicit cameraManager(QObject *parent = nullptr);
    ~cameraManager();

    void disConnectFromCameraOne(QString& ip);
    void connectToCameraOne(QString& ip);
    void disConnectFromCameraTwo(QString& ip);
    void connectToCameraTwo(QString& ip);
    void StartImageAcquisition(int CameraCode);

    void on_DeviceListChanged();
    double getCurrentCameraExposure(int code);
    int64_t   getCurrentCameraBPS(int code);
    double getCurrentAcquisitionFrameRateAbs(int code);
    double getCurrentAcquisitionFrameRateLimit(int code);

    QList<QString> getCameraList();

    bool cameraTwoRunning=false;
    bool cameraOneRunning=false;

    QMap <QString, FeaturePtr>          mapToFeatureOne;
    QMap<QString, FeaturePtr>           mapToFeatureTwo;


    void on_adjustExposure(int code,double value);
    void on_adjustFrameRate(int code, double value);
    void on_adjustBps(int code, int value);
    void on_adjustFormat(int code, QString format);
signals:

    void sendCameraList(QVector<QString> list);
    void sendImageToChannelOne(QPixmap);
    void sendImageToChannelTwo(QPixmap);

    void startOne(std::string);
    void startTwo(std::string);

    void updateExposure(int,double,double,double);
    void updateFeatureUI(int code);



 private:
    imageProcessThread* thread1;
    imageProcessThread* thread2;

    QThread* realThread1;
    QThread* realThread2;

    CameraObserver* observer;
    CameraInfo::CameraInfoVector m_CameraInfos;

    AVT::VmbAPI::CameraPtr Camera1;
    AVT::VmbAPI::CameraPtr Camera2;

    void getMetaCameraInfos();
    void updateCameraFeatureMap(int code,QStringList names);
    void storeCameraFeatures(QString cameraId);

};

#endif // CAMERAMANAGER_H
