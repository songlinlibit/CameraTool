#include "previewlabel.h"
#include<QPaintEvent>
#include<QPainter>

previewLabel::previewLabel(QWidget* parent):QLabel{parent}
{
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
    //
    frame=f;
    update();
}

previewDialog::previewDialog(QWidget* parent):QDialog{parent}
{
    plabel = new previewLabel(this);
    plabel->resize(size());
}

void previewDialog::resizeEvent(QResizeEvent *event)
{
    plabel->resize(size());
}
