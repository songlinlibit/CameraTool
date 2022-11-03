#include "cameramanager.h"
#include "Include/SharedPointerDefines.h"
#include "VimbaC/Include/VmbCommonTypes.h"
#include"cameraobserver.h"
#include "imageprocessthread.h"
#include "qdebug.h"
#include "qthread.h"
#include<QPixmap>

cameraManager::cameraManager(QObject *parent)
    : QObject{parent}
{
   AVT::VmbAPI::VimbaSystem& sys = AVT::VmbAPI::VimbaSystem::GetInstance();
    VmbErrorType err = sys.Startup();
    qDebug()<<"start up err:"<<err;
    if(err!=VmbErrorSuccess)
    {
        qFatal("initializint SDK failed");
        abort();
    }
    observer=new CameraObserver(this);
    VmbErrorType res = sys.RegisterCameraListObserver( ICameraListObserverPtr( observer ));

    connect(observer,&CameraObserver::updateDeviceList,this,&cameraManager::on_DeviceListChanged);

    thread1=new imageProcessThread(1);
    thread2=new imageProcessThread(2);

    realThread2=new QThread(this);
    realThread1=new QThread(this);

    thread1->moveToThread(realThread1);
    thread2->moveToThread(realThread2);

    connect(thread1,&imageProcessThread::pixmapReady,this,&cameraManager::sendImageToChannelOne);
    connect(thread2,&imageProcessThread::pixmapReady,this,&cameraManager::sendImageToChannelTwo);
    connect(thread1,&imageProcessThread::fullBitPixmapReady,this,&cameraManager::sentFullBitPixelMapOne);
    connect(thread2,&imageProcessThread::fullBitPixmapReady,this,&cameraManager::sentFullBitPixelMapTwo);
//    connect(this,&cameraManager::startOne,thread1,&imageProcessThread::StartContinuousImageAcquisition);
//    connect(this,&cameraManager::startTwo,thread2,&imageProcessThread::StartContinuousImageAcquisition);
    connect(this,&cameraManager::startOne,thread1,&imageProcessThread::ConnectCamera);
    connect(this,&cameraManager::startTwo,thread2,&imageProcessThread::ConnectCamera);

    connect(thread1,&imageProcessThread::streamStarted,this,[=](){
        cameraOneRunning=true;
        double curEx;

        Camera1=thread1->m_pCamera;
        FeaturePtr feature;

         Camera1->GetFeatureByName("ExposureTimeAbs",feature);
         feature->GetValue(curEx);

         emit updateExposure(1,curEx,0,0);


    });
    connect(thread2,&imageProcessThread::streamStarted,this,[=](){
        cameraTwoRunning=true;
        Camera2=thread2->m_pCamera;
        double curEx;


        FeaturePtr feature;

         Camera2->GetFeatureByName("ExposureTimeAbs",feature);
         feature->GetValue(curEx);

         emit updateExposure(2,curEx,0,0);


         });
    connect(thread1,&imageProcessThread::streamStopped,this,[=](){cameraOneRunning=false;Camera1.reset();});
    connect(thread2,&imageProcessThread::streamStopped,this,[=](){cameraOneRunning=false;Camera2.reset();});

    connect(thread1,&imageProcessThread::sendFeatures,
            this,[=](QMap<QString,FeaturePtr> r){mapToFeatureOne=r;emit updateFeatureUI(1);});
    connect(thread2,&imageProcessThread::sendFeatures,
            this,[=](QMap<QString,FeaturePtr> r){mapToFeatureTwo=r;emit updateFeatureUI(2);});

    realThread2->start();
    realThread1->start();
}


cameraManager::~cameraManager()
{
    AVT::VmbAPI::VimbaSystem& sys = AVT::VmbAPI::VimbaSystem::GetInstance();
    sys.Shutdown();
    qDebug()<<"quiting manager";

    thread1->StopContinuousImageAcquisition();
    thread2->StopContinuousImageAcquisition();

    realThread1->quit();
    realThread2->quit();
    QThread::sleep(1);
    realThread1->terminate();
    realThread2->terminate();


    qDebug()<<"sys shutdown";
}

void cameraManager::on_DeviceListChanged()
{
    auto tmp=observer->getCameraNames();
    for(auto& i:tmp)
    {
        qDebug()<<"cameraManager::on_DeviceListChanged find camera"<<i;
    }
    emit sendCameraList(tmp);
}

void cameraManager::connectToCameraOne(QString& ip)
{
    emit startOne(ip.toStdString());
}
void cameraManager::connectToCameraTwo(QString& ip)
{ 
   emit startTwo(ip.toStdString());
}
void cameraManager::StartImageAcquisition(int CameraCode)
{
    if(CameraCode == 1){
        if(thread1->isConnected()){
            thread1->StartContinuousImageAcquisition();
        } else qDebug()<<"have not connected camera1";
    }else {
        if(thread2->isConnected()){
            thread2->StartContinuousImageAcquisition();
        } else qDebug()<<"have not connected camera2";
    }
}

void cameraManager::disConnectFromCameraOne(QString& ip)
{
    thread1->StopContinuousImageAcquisition();

}
void cameraManager::disConnectFromCameraTwo(QString& ip)
{
    thread2->StopContinuousImageAcquisition();
}

void cameraManager::getMetaCameraInfos()
{
    AVT::VmbAPI::VimbaSystem&  sys= AVT::VmbAPI::VimbaSystem::GetInstance();
    CameraPtrVector     currentListedCameras;
     VmbErrorType        error = sys.GetCameras(currentListedCameras);

    CameraInfo::CameraInfoVector    remainingCameras;
    if(error!=VmbErrorSuccess)
    {
        qDebug()<<"error when getting cameras :"<<error;
        return;
    }

    CameraPtrVector DisconnectedCameras;
    for (unsigned int i = 0; i < m_CameraInfos.size(); i++)
    {
        if( currentListedCameras.end() == std::find_if(currentListedCameras.begin(), currentListedCameras.end(), CameraPtrCompare( m_CameraInfos[i].Cam() ) ) )
        {
            //遍历currentListedCameras，在Infos里寻找
            DisconnectedCameras.push_back( m_CameraInfos[i].Cam() );
        }
        else
        {
            //如果找到，就添加到remain里去
            remainingCameras.push_back( m_CameraInfos[i] );//如果还在就移到remaining里
        }
    }

    m_CameraInfos = remainingCameras;


    InterfacePtrVector          ifPtrVec;
    QMap <QString, QString>     ifTypeMap;

    std::string                 sInterfaceID;

    error = sys.GetInterfaces(ifPtrVec);

    if(VmbErrorSuccess != error)
    {
        qDebug()<<"Get interface error:"<<error;
        return;
    }

    for(auto &i:ifPtrVec)
    {
        error = i->GetID(sInterfaceID);
        if(VmbErrorSuccess != error)
        {
            qDebug()<<"error code when GetID:"<<error;
            continue;
        }
        VmbInterfaceType    ifType          = VmbInterfaceUnknown;
        VmbErrorType        errorGetType    = i->GetType(ifType) ;
        if(VmbErrorSuccess != errorGetType)
        {
            continue;
        }

        switch(ifType)
        {
        case VmbInterfaceEthernet:
            ifTypeMap[QString::fromStdString(sInterfaceID)] = "GigE";
            break;
        case VmbInterfaceFirewire:
            ifTypeMap[QString::fromStdString(sInterfaceID)] = "1394";

            break;

        case VmbInterfaceUsb:
            ifTypeMap[QString::fromStdString(sInterfaceID)] = "USB";

            break;

        case VmbInterfaceCL:
            ifTypeMap[QString::fromStdString(sInterfaceID)] = "CL";

            break;
        case VmbInterfaceCSI2:
            ifTypeMap[QString::fromStdString(sInterfaceID)] = "CSI-2";
            break;
        default: break;

        }

    }

    CameraPtrVector& Cameras=currentListedCameras;

    if(Cameras.empty())
    {
        emit sendCameraList((QVector<QString>()));
    }
    else
    {
        QVector<QString> rec;
        for(auto &i:Cameras)
        {
            std::string tmp;
            i->GetID(tmp);
            QString tmpS=QString::fromStdString(tmp);
            qDebug()<<"CameraId";
            rec.push_back(tmpS);
        }
        qDebug()<<"Camera detetcted: "<<rec;
        emit sendCameraList(rec);
    }

}

QList<QString> cameraManager::getCameraList()
{
    AVT::VmbAPI::VimbaSystem&  sys= AVT::VmbAPI::VimbaSystem::GetInstance();
    CameraPtrVector     currentListedCameras;
     VmbErrorType        error = sys.GetCameras(currentListedCameras);

     QList<QString> rec;
     for(auto& i:currentListedCameras)
     {
         std::string tmp;
         i->GetID(tmp);
         rec.push_back(QString::fromStdString(tmp));
     }
     return rec;
}

void cameraManager::storeCameraFeatures(QString cameraId)
{

}

void cameraManager::on_adjustFormat(int code,QString r)
{
    FeaturePtr feature;

      if(code==1)
      {
        if(Camera1==nullptr)
        {
            return;
        }
        Camera1->GetFeatureByName("PixelFormat",feature);
        VmbPixelFormatType format;
        if(r == "Mono8")
        {
            format = VmbPixelFormatMono8;
        }
        else if(r=="Mono12")
        {
            format = VmbPixelFormatMono12;
        }
        else if(r=="Mono16")
        {
            format = VmbPixelFormatMono16;
        }
        auto error =  feature->SetValue(format);
        if (VmbErrorSuccess != error) qDebug()<<"error when setting pixelformat:"<<error;
        else qDebug()<<"set format :"<< r << "success!";
      }
      else if(code==2)
      {
        if(Camera2==nullptr)
        {
            return;
        }
        Camera2->GetFeatureByName("PixelFormat",feature);
        VmbPixelFormatType format;
        if(r == "Mono8")
        {
            format = VmbPixelFormatMono8;
        }
        else if(r=="Mono12")
        {
            format = VmbPixelFormatMono12;
        }
        else if(r=="Mono16")
        {
            format = VmbPixelFormatMono16;
        }
        auto error=  feature->SetValue(format);
        if (VmbErrorSuccess != error) qDebug()<<"error when setting pixelformat:"<<error;
        else qDebug()<<"set format :"<< r << "success!";
      }
}

void cameraManager::on_adjustExposure(int code,double value)
{
    FeaturePtr feature;

      if(code==1)
      {
          if(Camera1==nullptr)
          {
              return;
          }
          Camera1->GetFeatureByName("ExposureTimeAbs",feature);
          feature->SetValue(value);
      }
      else if(code==2)
      {
          if(Camera2==nullptr)
          {
              return;
          }
          Camera2->GetFeatureByName("ExposureTimeAbs",feature);
          feature->SetValue(value);
      }
}

void cameraManager::on_adjustFrameRate(int code,double value)
{
    FeaturePtr feature;
    FeaturePtr limit_feature;

      if(code==1)
      {
          if(Camera1==nullptr)
          {
              return;
          }
          Camera1->GetFeatureByName("AcquisitionFrameRateAbs",feature);
          bool err = feature->SetValue(value);
          
      }
      else if(code==2)
      {
          if(Camera2==nullptr)
          {
              return;
          }
          Camera2->GetFeatureByName("AcquisitionFrameRateAbs",feature);
          feature->SetValue(value);
      }
}

void cameraManager::on_adjustBps(int code, int value)
{
    FeaturePtr feature;

      if(code==1)
      {
          if(Camera1==nullptr)
          {
              return;
          }
          Camera1->GetFeatureByName("StreamBytesPerSecond",feature);
          feature->SetValue(value);
      }
      else if(code==2)
      {
          if(Camera2==nullptr)
          {
              return;
          }
          Camera2->GetFeatureByName("StreamBytesPerSecond",feature);
          feature->SetValue(value);
      }
}

int64_t cameraManager::getCurrentCameraBPS(int code)

{
    FeaturePtr feature;
    VmbErrorType lError;
    int64_t value=0;
      if(code==1)
      {
          if(Camera1==nullptr)
          {
              return 0;
          }
          lError = Camera1->GetFeatureByName("StreamBytesPerSecond",feature);
          if(VmbErrorSuccess != lError){
            qDebug()<<"get StreamBytesPerSecond failure: "<<lError;
          }
          lError = feature->GetValue(value);
          if(VmbErrorSuccess != lError){
            qDebug()<<"get StreamBytesPerSecond value failure: "<<lError;
          }
      }
      else if(code==2)
      {
          if(Camera2==nullptr)
          {
              return 0;
          }
          lError = Camera2->GetFeatureByName("StreamBytesPerSecond",feature);
          feature->GetValue(value);
      }

      return value;
}

double cameraManager::getCurrentCameraExposure(int code)
{
    FeaturePtr feature;
    double value=0;
      if(code==1)
      {
          if(Camera1==nullptr)
          {
              return 0;
          }
          Camera1->GetFeatureByName("ExposureTimeAbs",feature);
          feature->GetValue(value);
      }
      else if(code==2)
      {
          if(Camera2==nullptr)
          {
              return 0;
          }
          Camera2->GetFeatureByName("ExposureTimeAbs",feature);
          feature->GetValue(value);
      }

      return value;
}

double cameraManager::getCurrentAcquisitionFrameRateAbs(int code)
{
    FeaturePtr feature;
    double value=0;
    if(code==1)
    {
        if(Camera1==nullptr)
        {
            return 0;
        }
        Camera1->GetFeatureByName("AcquisitionFrameRateAbs",feature);
        feature->GetValue(value);
    }
    else if(code==2)
    {
        if(Camera2==nullptr)
        {
            return 0;
        }
        Camera2->GetFeatureByName("AcquisitionFrameRateAbs",feature);
        feature->GetValue(value);
    }

    return value;
}

double cameraManager::getCurrentAcquisitionFrameRateLimit(int code)
{
    FeaturePtr feature;
    double value=0;
    if(code==1)
    {
        if(Camera1==nullptr)
        {
            return 0;
        }
        Camera1->GetFeatureByName("AcquisitionFrameRateLimit",feature);
        feature->GetValue(value);
    }
    else if(code==2)
    {
        if(Camera2==nullptr)
        {
            return 0;
        }
        Camera2->GetFeatureByName("AcquisitionFrameRateLimit",feature);
        feature->GetValue(value);
    }

    return value;
}

