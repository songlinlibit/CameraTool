#ifndef PREVIEWLABEL_H
#define PREVIEWLABEL_H


#include "qevent.h"
#include <QLabel>
#include <QObject>
#include <QDialog>
#include <QStatusBar>

class previewLabel : public QLabel
{
    Q_OBJECT
public:
    previewLabel(QWidget* parent=nullptr, bool enable_mouse = false);

    void accpetPixmap(QPixmap frame);
    QPixmap frame;

    void mousePressEvent(QMouseEvent *e) override;
    void getGrayValue();
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    bool enable_mouse = false;
    int x_in_Label = -1, y_in_Label = -1, x_in_Ui = -1, y_in_Ui = -1, x_in_Img = -1, y_in_Img = -1;
    uchar * grayValue;
signals:
    void updateGrayValue(int ,int ,uchar *);
};

class previewDialog : public QDialog
{
    Q_OBJECT
public:
    previewDialog(QWidget* parent=nullptr);
    QLabel *frames_label;
    previewLabel *plabel;

    void setGrayValue(int x, int y, uchar *value);
private:
    void resizeEvent(QResizeEvent *event) override;

    ~previewDialog(){
        if(plabel) delete plabel;
        if(frames_label) delete frames_label;
    }


};



#endif // PREVIEWLABEL_H
