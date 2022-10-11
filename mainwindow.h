#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Include/VimbaCPP.h"
#include<camerainfo.h>
using namespace AVT::VmbAPI;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QThread;
class cameraManager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCameraSavePath();

    void initCameraInfos();

                   class FindByName
                   {
                       const QString m_Name;
                   public:
                       FindByName( const QString &s)
                           : m_Name( s )
                       {}
                       bool operator()( const CameraInfo &i) const
                       {
                           return i.DisplayName() == m_Name;
                       }
                   };
                   class CameraPtrCompare
                   {
                       const CameraPtr m_Camera;
                   public:
                       CameraPtrCompare( const CameraPtr& cam)
                           : m_Camera( cam )
                       {}
                       bool operator() ( const CameraPtr& other) const
                       {
                           return m_Camera.get() == other.get();
                       }
                   };


                   CameraInfo::CameraInfoVector                m_CameraInfos;

                 signals:
                  void setExposure(int code,double abs);
                  void setFrameRate(int code,double abs);
                  void setBPS(int code, double abs);
                  void setFormat(int code,QString format);


private slots:
                   void on_pushButton_3_clicked();

                   void on_pushButton_4_clicked();

                   void on_updateExposure(int code,double current,double lower,double upper);
                   void on_featuresUI(int code);

                   void on_lineEdit_2_textEdited(const QString &arg1);

                   void on_lineEdit_textEdited(const QString &arg1);


                   void on_horizontalSlider_sliderMoved(int position);

                   void on_horizontalSlider_2_sliderMoved(int position);

                   void on_pushButton_7_clicked();

                   void on_pushButton_11_clicked();

                   void on_pushButton_8_clicked();

                   void on_pushButton_12_clicked();

                   void on_comboBox_5_currentTextChanged(const QString &arg1);

                   void on_comboBox_4_currentTextChanged(const QString &arg1);

                   void on_pushButton_5_clicked();

                   void on_pushButton_9_clicked();
                   
                   void on_pushButton_6_clicked();

                   void on_pushButton_10_clicked();

                   void on_pushButton_15_clicked();

                   void on_pushButton_16_clicked();

                   void on_pushButton_17_clicked();

                   void on_pushButton_18_clicked();

                   void on_pushButton_20_clicked();
                   
                   void on_pushButton_21_clicked();
                   
                   void on_pushButton_22_clicked();
                   
                   void on_pushButton_23_clicked();


private:
    Ui::MainWindow *ui;

    QString filePath_1;
    QString filePath_2;

    QString ip_1;
    QString ip_2;

    QString                         m_SelectedCamera;
    bool                            m_bIsCurrentModelChecked;
    bool                            m_bIsOpenByRightMouseClick;
    bool                            m_bIsInitialized;

     cameraManager* manager=nullptr;
     QThread* managerThread=nullptr;


};
#endif // MAINWINDOW_H
