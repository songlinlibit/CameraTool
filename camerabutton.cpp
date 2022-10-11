#include "camerabutton.h"
#include "qcursor.h"
#include "qmenu.h"
#include "qnamespace.h"
#include<QMouseEvent>
#include<QInputDialog>
CameraButton::CameraButton(QWidget* parent):QPushButton{parent}
{

}

void CameraButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        QMenu* menu=new QMenu(this);

        QAction* ac1=new QAction("启动相机");
        QAction* ac2=new QAction("关闭相机");

        menu->addAction(ac1);
        menu->addAction(ac2);

        connect(ac1,&QAction::triggered,this,[=](){
          QString tmpIp;
          tmpIp=QInputDialog::getText(this,"输入IP","请输入你想要连接的相机的ID");
          if(tmpIp=="" || isConnected)
          {
              return;
          }
          currentIp = tmpIp;
          isConnected = true;
          emit activateCamera(currentIp);
        menu->deleteLater();});

        connect(ac2,&QAction::triggered,this,[=](){
            if(currentIp=="")
            {
                return;
            }
            isConnected = false;
            emit closeCamera(currentIp);
        menu->deleteLater();});

        menu->popup(QCursor::pos());

        event->accept();
    }
    QPushButton::mousePressEvent(event);
}
