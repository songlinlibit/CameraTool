#include "mainwindow.h"
#include "camerabutton.h"
#include "cameramanager.h"
#include "previewlabel.h"
#include "qpixmap.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QThread>
// #include <QImageReader>
#include <QInputDialog>
#include <QMessageBox>

#include <thread>
#include <future>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap p;
    p.load("D:\\204_qt_proj\\proj7\\CameraViewer\\test.bmp");
    qDebug()<<"p"<<p.isNull();

    QAction* ac1=new QAction("设置相机1保存路径");
    QAction* ac2=new QAction("设置相机2保存路径");

    connect(ac1,&QAction::triggered,this,&MainWindow::setCameraSavePath);
    connect(ac2,&QAction::triggered,this,&MainWindow::setCameraSavePath);

    ui->menu->addAction(ac1);
    ui->menu->addAction(ac2);

    ui->preview_1->accpetPixmap(p);
    ui->preview_2->accpetPixmap(p);

    filePath_1="./defaultBuf/first/";
    filePath_2="./defaultBuf/second/";

    manager=new cameraManager();
    managerThread=new QThread(this);

    connect(ui->pushButton,&CameraButton::activateCamera,this->manager,&cameraManager::connectToCameraOne);
    connect(ui->pushButton_2,&CameraButton::activateCamera,this->manager,&cameraManager::connectToCameraTwo);
    connect(ui->pushButton,&CameraButton::closeCamera,this->manager,&cameraManager::disConnectFromCameraOne);
    connect(ui->pushButton_2,&CameraButton::closeCamera,this->manager,&cameraManager::disConnectFromCameraTwo);

    connect(manager,&cameraManager::sendImageToChannelOne,ui->preview_2,&previewLabel::accpetPixmap);
    connect(manager,&cameraManager::sendImageToChannelTwo,ui->preview_1,&previewLabel::accpetPixmap);
    connect(manager,&cameraManager::sentFullBitPixelMapOne,this,&MainWindow::saveFullBitPixelMapOne);
    connect(manager,&cameraManager::sentFullBitPixelMapTwo,this,&MainWindow::saveFullBitPixelMapTwo);
    connect(manager,&cameraManager::updateExposure,this,&MainWindow::on_updateExposure);
    connect(manager,&cameraManager::sendCameraList,this,[=](QVector<QString> names){
        ui->comboBox_3->clear();
        for(auto& i:names)
        {
            ui->comboBox_3->addItem(i);
        }
    });

    connect(manager,&cameraManager::updateFeatureUI,this,&MainWindow::on_featuresUI);
    connect(this,&MainWindow::setExposure,manager,&cameraManager::on_adjustExposure);
    connect(this,&MainWindow::setFrameRate,manager,&cameraManager::on_adjustFrameRate);
    connect(this,&MainWindow::setBPS,manager,&cameraManager::on_adjustBps);

    connect(ui->lineEdit_2, &QLineEdit::returnPressed, this, &MainWindow::updateExporesureOne);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::updateExporesureTwo);

    manager->moveToThread(managerThread);

    managerThread->start();

    ui->comboBox_4->addItem("Mono8");
    ui->comboBox_4->addItem("Mono12");
    ui->comboBox_4->addItem("Mono16");

    ui->comboBox_5->addItem("Mono8");
    ui->comboBox_5->addItem("Mono12");
    ui->comboBox_5->addItem("Mono16");

    initCameraInfos();
    ui->comboBox_3->setEditable(true);

    for ( int i = 0; i < 256; ++i )
    {
        m_ColorTable.push_back( QColor( i, i, i ).rgb() );
    }
}

MainWindow::~MainWindow()
{
  manager->deleteLater();
  qDebug()<<"quiting mainwindow";
  managerThread->quit();
  qDebug()<<"quit signal pushed...";
  managerThread->wait();
  qDebug()<<"wait finished";
  delete ui;
}


void MainWindow::setCameraSavePath()
{
    QAction* sender=qobject_cast<QAction*>(QObject::sender());

    QString tmp=QFileDialog::getExistingDirectory(this);

    if(sender->text()=="设置相机1保存路径")
    {
        filePath_1=tmp;
    }
    else if(sender->text()=="设置相机2保存路径")
    {
        filePath_2=tmp;
    }
}

void MainWindow::saveFullBitPixelMapOne(tFrameInfo tempFullBitPixel){
    m_FullBitPixelMapOne = tempFullBitPixel;
    return;
}

void MainWindow::saveFullBitPixelMapTwo(tFrameInfo tempFullBitPixel){
    m_FullBitPixelMapTwo = tempFullBitPixel;
    return;
}

void MainWindow::initCameraInfos()
{
    auto cameras=manager->getCameraList();
    ui->comboBox_3->addItems(cameras);
}

void MainWindow::on_pushButton_3_clicked()
{
    // make a copy of the images before save-as dialog appears (image can change during time dialog open)
    QImage      image = (ui->preview_2->frame.toImage());
    QString     fileExtension = QString(".jpeg;;.jpg;;.png;;.tif;;.tiff");
    bool        isImageAvailable = true;

    if ( image.isNull() )
    {
        isImageAvailable = false;
    }
    else
    {
        auto m_saveFileDialog = new QFileDialog ( this, tr("Save Image"), QString(), fileExtension );
        qDebug()<<"extension : "<<fileExtension;
        m_saveFileDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
        m_saveFileDialog->setAcceptMode(QFileDialog::AcceptSave);

        if(m_saveFileDialog->exec())
        {   //OK
           auto m_SelectedExtension = m_saveFileDialog->selectedNameFilter();
           QStringList files = m_saveFileDialog->selectedFiles();

           if(!files.isEmpty())
           {
                QString fileName = files.at(0);

                if(!fileName.endsWith(m_SelectedExtension))
                {
                    fileName.append(m_SelectedExtension);
                }

                bool saved = false;
                std::future<bool> result;

                // save image using LibTiff library for 16 Bit
                if(m_SelectedExtension.contains(".tif"))
                {
                    result = std::async(std::launch::async, [](tFrameInfo temp, QString file){
                        ImageWriter TiffWriter;
                        return TiffWriter.WriteTiff(temp, file.toUtf8().constData());
                    }, m_FullBitPixelMapOne, fileName);
                }
                // use default QImage save functionality
                else
                {

                    saved = image.convertToFormat(QImage::Format_Indexed8, m_ColorTable).save( fileName );
                }

                if ( true == saved || result.get())
                {
                    QMessageBox::information( this, tr( "Vimba Viewer" ), tr( "Image: " ) + fileName + tr( " saved successfully" ));
                }
                else
                {
                    QMessageBox::warning( this, tr( "Vimba Viewer" ), tr( "Error saving image" ));
                }
            }
        }
        delete m_saveFileDialog;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    // make a copy of the images before save-as dialog appears (image can change during time dialog open)
    QImage      image = (ui->preview_1->frame.toImage());
    QString     fileExtension = QString(".jpeg;;.jpg;;.png;;.tif;;.tiff");
    bool        isImageAvailable = true;

    if ( image.isNull() )
    {
        isImageAvailable = false;
    }
    else
    {
        auto m_saveFileDialog = new QFileDialog ( this, tr("Save Image"), QString(), fileExtension );
        qDebug()<<"extension : "<<fileExtension;
        m_saveFileDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
        m_saveFileDialog->setAcceptMode(QFileDialog::AcceptSave);

        if(m_saveFileDialog->exec())
        {   //OK
           auto m_SelectedExtension = m_saveFileDialog->selectedNameFilter();
           QStringList files = m_saveFileDialog->selectedFiles();

           if(!files.isEmpty())
           {
                QString fileName = files.at(0);

                if(!fileName.endsWith(m_SelectedExtension))
                {
                    fileName.append(m_SelectedExtension);
                }

                bool saved = false;
                std::future<bool> result;

                // save image using LibTiff library for 16 Bit
                if(m_SelectedExtension.contains(".tif"))
                {
                    result = std::async(std::launch::async, [](tFrameInfo temp, QString file){
                        ImageWriter TiffWriter;
                        return TiffWriter.WriteTiff(temp, file.toUtf8().constData());
                    }, m_FullBitPixelMapTwo, fileName);
                }
                // use default QImage save functionality
                else
                {
                    saved = image.convertToFormat(QImage::Format_Indexed8, m_ColorTable).save( fileName );
                }

                if ( true == saved || result.get())
                {
                    QMessageBox::information( this, tr( "Vimba Viewer" ), tr( "Image: " ) + fileName + tr( " saved successfully" ));
                }
                else
                {
                    QMessageBox::warning( this, tr( "Vimba Viewer" ), tr( "Error saving image" ));
                }
            }
        }
        delete m_saveFileDialog;
    }
}

void MainWindow::on_updateExposure(int code,double current,double lower,double upper)
{
   if(code==1)
   {
       ui->horizontalSlider->setMaximum(0);
       ui->horizontalSlider->setMaximum(10000);
       ui->horizontalSlider->setSliderPosition(current);
       ui->lineEdit_2->setText(QString("%1").arg(current));
   }
   else if(code==2)
   {
       ui->horizontalSlider_2->setMaximum(0);
       ui->horizontalSlider_2->setMaximum(10000);
       ui->horizontalSlider_2->setSliderPosition(current);
       ui->lineEdit->setText(QString("%1").arg(current));
   }
}

void MainWindow::on_featuresUI(int code)
{
    if(code==1)
    {
       auto& tmp=manager->mapToFeatureOne;

       for(auto iter=tmp.begin();iter!=tmp.end();++iter)
       {
           ui->comboBox->addItem(iter.key());
       }

    }
    else if(code==2)
    {
        auto& tmp=manager->mapToFeatureTwo;
        for(auto iter=tmp.begin();iter!=tmp.end();++iter)
        {
            ui->comboBox_2->addItem(iter.key());
        }
    }
}

void MainWindow::updateExporesureOne() {
    QString s = ui->lineEdit_2->text();
    ui->horizontalSlider->setSliderPosition(s.toInt());
    bool ok = false;
    auto value = s.toDouble(&ok);
    if(!ok) {
        QMessageBox::information( this, tr( "警告" ), tr( "请输入纯数字" ));
        return;
    }
    emit setExposure(1,value);
}

void MainWindow::updateExporesureTwo() {
    QString s = ui->lineEdit->text();
    ui->horizontalSlider_2->setSliderPosition(s.toInt());
    bool ok = false;
    auto value = s.toDouble(&ok);
    if(!ok) {
        QMessageBox::information( this, tr( "警告" ), tr( "请输入纯数字" ));
        return;
    }
    emit setExposure(2,value);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->lineEdit_2->setText(QString("%1").arg(position));
    emit setExposure(1,position);

}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
     ui->lineEdit->setText(QString("%1").arg(position));
     emit setExposure(2,position);

}


void MainWindow::on_pushButton_7_clicked()
{
    //CameraOne frameRate;
    bool ok;
      auto current=manager->getCurrentAcquisitionFrameRateAbs(1);
    auto rate=QInputDialog::getDouble(this,"输入你想要的帧率",
                                      "新帧率:",current, 0, 120, 1, &ok);
    if(ok)
    {
        auto limit_value = manager->getCurrentAcquisitionFrameRateLimit(1);
        if (limit_value < rate || 0 > rate) {
        QMessageBox::information( this, "警告",
        "Acquisition Frame Rate Abs Should be 0 ~ 33.2");
        } else {
                    emit setFrameRate(1,rate);

        }
    }

}


void MainWindow::on_pushButton_11_clicked()
{
    bool ok;
    auto current=manager->getCurrentAcquisitionFrameRateAbs(2);
    auto rate=QInputDialog::getDouble(this,"输入你想要的帧率",
                                      "新帧率:",current, 0, 120, 1, &ok);
    if(ok)
    {
        auto limit_value = manager->getCurrentAcquisitionFrameRateLimit(2);
        if (limit_value < rate || 0 > rate) {
        QMessageBox::warning( this, "警告",
        "Acquisition Frame Rate Abs Should be 0 ~ 33.2");
        } else {
                    emit setFrameRate(2,rate);

        }
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    bool ok;
    auto current=manager->getCurrentCameraBPS(1);
    QMessageBox::warning(this,"输入不正确的BPS可能会导致严重后果！","Be sure when proceed.");
    auto rate=QInputDialog::getInt(this,"输入你想要的BPS",
                                      "新BPS:",current,-2147483647, 2147483647,1,&ok);
    if(ok)
    {
        emit setBPS(1,rate);
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    bool ok;
    auto current=manager->getCurrentCameraBPS(2);
    QMessageBox::warning(this,"输入不正确的BPS可能会导致严重后果！","Are you sure to proceed？");
    auto rate=QInputDialog::getInt(this,"输入你想要的BPS",
                                      "新BPS:",current,-2147483647, 2147483647,1,&ok);
    if(ok)
    {
        emit setBPS(2,rate);
    }
}


void MainWindow::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    //camera one
    manager->on_adjustFormat(1,arg1);

}


void MainWindow::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    manager->on_adjustFormat(2,arg1);
}

void MainWindow::on_pushButton_6_clicked()
{
    manager->StartImageAcquisition(1);
    // ComboBox4.Enabled = False;
}

void MainWindow::on_pushButton_10_clicked()
{
    manager->StartImageAcquisition(2);
    // ComboBox5.Enabled = False;
}


void MainWindow::on_pushButton_5_clicked()
{
    QPixmap p;
    p.load("D:\\204_qt_proj\\proj7\\CameraViewer\\test.bmp");

    previewDialog* dialog = new previewDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Hello, dialog!"));
    dialog->plabel->accpetPixmap(p);
    connect(manager,&cameraManager::sendImageToChannelOne,dialog->plabel,&previewLabel::accpetPixmap);
    dialog->show();
}


void MainWindow::on_pushButton_9_clicked()
{
    QPixmap p;
    p.load("D:\\204_qt_proj\\proj7\\CameraViewer\\test.bmp");

    previewDialog* dialog = new previewDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Hello, dialog!"));
    dialog->plabel->accpetPixmap(p);
    connect(manager,&cameraManager::sendImageToChannelTwo,dialog->plabel,&previewLabel::accpetPixmap);
    dialog->show();
}

