#include "previewlabel.h"
#include<QPaintEvent>
#include<QPainter>

previewLabel::previewLabel(QWidget* parent, bool _enable_mouse):QLabel{parent}
{
    enable_mouse = _enable_mouse;
    setScaledContents(true);
}


void previewLabel::paintEvent(QPaintEvent* event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,size().width(),size().height()),frame);
}

void previewLabel::accpetPixmap(QPixmap f)
{
    frame=f;
    update();
    if(y_in_Img != -1 || x_in_Img != -1){
        getGrayValue();
    }
}

void previewLabel::mousePressEvent(QMouseEvent *e)
{
    if(!enable_mouse) return;
    x_in_Label = e->position().x();
    y_in_Label = e->position().y();
    x_in_Ui = geometry().x() +x_in_Label;
    y_in_Ui = geometry().y() + y_in_Label;
    //TODO:这里需要知道输入图像的大小，然后根据缩放关系求出相应位置
    x_in_Img = x_in_Label* 2064/width();
    y_in_Img = y_in_Label * 1544/height();
    /*  for DEBUG
    qDebug() << "mouse_in_label: "<< x_in_Label <<","<< y_in_Label
                      <<  "    mouse_in_Ui: " << x_in_Ui << "," << y_in_Ui
                      << "    mouse_in_Img: " <<x_in_Img <<"," << y_in_Img;
    ************/
    if(y_in_Img != -1 || x_in_Img != -1){
        getGrayValue();
    }

}

void previewLabel::getGrayValue(){
    if(y_in_Img == -1 || x_in_Img == -1){
        return;
    }
//    qDebug()<<"depth = "<< QString("depth : %1").arg(frame.depth());
    QPixmap tempPix = frame.copy(x_in_Img, y_in_Img, 1, 1);    // 获取坐标值位置处的像素图
//    qDebug()<<"depth = "<< QString("depth : %1").arg(tempPix.depth());
    QImage imageBits = tempPix.toImage();
//    qDebug()<<QString("imageBits.format() : %1").arg(imageBits.format());
    if(imageBits.isNull() == false) {
        if(imageBits.allGray() == true) {    //  判断是否为灰度图
              grayValue = imageBits.bits();    //  获取灰度值
//              qDebug()<<QString("gray : %1").arg(*grayValue);
          }
         else
         {
              qDebug()<<QString("Unsupport RGB image");
         }
     }
    emit updateGrayValue(x_in_Img, y_in_Img, grayValue);

}


previewDialog::previewDialog(QWidget* parent):QDialog{parent}
{
    plabel = new previewLabel(this, true);
    plabel->resize(size().width(), size().height()-20);

    frames_label = new QLabel(this);
    frames_label->setGeometry(0, size().height()-20,size().width(),20);

    connect(plabel,&previewLabel::updateGrayValue,this,&previewDialog::setGrayValue);
}

void previewDialog::resizeEvent(QResizeEvent *event)
{
    plabel->resize(size().width(), size().height()-20);
    frames_label->setGeometry(0, size().height()-20,size().width(),20);
}

void previewDialog::setGrayValue(int x, int y, uchar *value){
    frames_label->setText(QString("x : %1, y : %2，value : %3").arg(x).arg(y).arg(*value));
}
