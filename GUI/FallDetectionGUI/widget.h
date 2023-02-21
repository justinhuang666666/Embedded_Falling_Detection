#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QtSerialPort/QtSerialPort>
//#include <QMqttClient>
#include "qmqttclient.h"
//#include <QMqttSubscription>
#include "qmqttsubscription.h"
#include <QVariant>
#include "myclass.h"
#include <QOpenGLContext>
#include <QSurfaceFormat>
//#include <Qt3DCore>
//#include <Qt3DRender>
//#include <Qt3DExtras>
//#include "my3dwidget.h"
#include <QMediaPlayer>

//extern QSurfaceFormat format;
//extern QOpenGLContext context;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

#define LAT 51.49905
#define LNG 0.176217
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void setCenter(QVariant, QVariant);
private slots:
    void TimerEvent();
    void on_pushButton_12_clicked();
    void SerialPort_Readyread();

    //void on_checkBox_clicked();

    void on_checkBox_8_clicked();

    void on_checkBox_9_clicked();

    void on_pushButton_10_clicked();


    void on_checkBox_7_clicked();

    void on_pushButton_11_clicked();
    void UpdateMessage(const QByteArray &message, const QMqttTopicName &topic);
    //void OnConnected();
    void RealtimePlot();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_cancelbutton_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_clicked();

    void ProcessVideo();

private:
    Ui::Widget *ui;
    QTimer *timer1;
    QStringList PortStringList;
    QSerialPort *serial;
    QString ReceiveText;
    long ReceiveBytes;
    QMqttClient *m_client;
    QTimer *timer_plot;
    double SVM_DATA;
    double GYRO_DATA;
    double PITCHandROLL;
    int FALL = 0;
    int PlotStart;
    QObject *obj1;
    MyClass *mc;

    //QSurfaceFormat *format;
    //QOpenGLContext *context;
    QObject *obj2;
    //My3DWidget *mywidget;
    QMediaPlayer *player;

    int StartPosition_FALL = 3000;
    int StartPosition_notFall = 5000;
    double TOLAT = LAT;
    double TOLNG = LNG;
};
#endif // WIDGET_H
