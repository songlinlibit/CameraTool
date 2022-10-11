#ifndef PREVIEWLABEL_H
#define PREVIEWLABEL_H


#include "qevent.h"
#include <QLabel>
#include <QObject>
#include <QDialog>

class previewLabel : public QLabel
{
    Q_OBJECT
public:
    previewLabel(QWidget* parent=nullptr);

    void accpetPixmap(QPixmap frame);
    QPixmap frame;
protected:
    void paintEvent(QPaintEvent* event) override;

private:


};

class previewDialog : public QDialog
{
    Q_OBJECT
public:
    previewDialog(QWidget* parent=nullptr);

    previewLabel *plabel;
private:
    void resizeEvent(QResizeEvent *event) override;
    ~previewDialog(){
        if(plabel) delete plabel;
    }


};



#endif // PREVIEWLABEL_H
