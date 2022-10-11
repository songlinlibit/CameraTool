#ifndef CAMERABUTTON_H
#define CAMERABUTTON_H

#include "qwidget.h"
#include <QPushButton>
#include<QObject>
class CameraButton : public QPushButton
{
    Q_OBJECT
public:
    CameraButton(QWidget* parnet=nullptr);

signals:
    void activateCamera(QString&);
    void closeCamera(QString&);


 protected:
    void mousePressEvent(QMouseEvent* event) override;

   QString currentIp;
   bool    isConnected = false;
};

#endif // CAMERABUTTON_H
