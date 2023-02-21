#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QFont>
#include <QElapsedTimer>
#include <QDebug>
#include <QQuickItem>
#include <QMediaPlayer>
#include <QVideoWidget>
//#include <QSurfaceFormat>
#include <QFrame>
#include <QtMqtt/qmqttmessage.h>
#include <QByteArray>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();
    player = new QMediaPlayer(this);
    //QMediaPlayer *player = new QMediaPlayer;
    player->setVideoOutput(ui->widget);
    player->setMedia(QUrl::fromLocalFile("C:/Users/xujub/Desktop/GUI/test/falling.mpg"));
    //player->setMedia(QUrl(QStringLiteral("falling.mpg")));


    //ui->widget->setGeometry(100, 100, 300, 400);
    ui->widget->show();
    player->setPosition(0);
    player->pause();

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Widget::ProcessVideo);

    ui->frame->setFrameShape(QFrame::Box);
    ui->frame->setFrameShadow(QFrame::Raised);
    ui->frame->setLineWidth(3);
    ui->frame->setMidLineWidth(2);

    //ui->widget->show();


    /*QOpenGLContext *globalContext = QOpenGLContext::globalShareContext();
    if (!globalContext) {
        globalContext = new QOpenGLContext();
        globalContext->create();
    }
    ui->quickWidget_2->setFormat(globalContext->format());*/
    //ui->quickWidget_2->setFormat(QOpenGLContext::globalShareContext()->format());
    //ui->quickWidget_2->setSource(QUrl(QStringLiteral("qrc:/fallmodel.qml")));
    //ui->quickWidget_2->show();

    /*Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = ui->widget_2->createWindowContainer(view);
    container->setMinimumSize(200, 100);
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 40.0f));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    Qt3DRender::QSceneLoader *sceneLoader = new Qt3DRender::QSceneLoader(rootEntity);
    sceneLoader->setSource(QUrl::fromLocalFile("C:/Users/xujub/Desktop/GUI/test/Falling.fbx"));
    rootEntity->addComponent(sceneLoader);
    view->setRootEntity(rootEntity);*/
    //ui->widget->show();

    setWindowTitle("Falling Detector GUI"); //set the window name

    timer1 = new QTimer(this);
    timer_plot = new QTimer(this);
    timer1->start(500);
    connect(timer1, &QTimer::timeout, this, &Widget::TimerEvent);

    serial = new QSerialPort(this);
    ui->comboBox_14->setCurrentIndex(4);
    ui->comboBox_15->setCurrentIndex(3);
    ui->comboBox_16->setCurrentIndex(2);
    ui->comboBox_17->setCurrentIndex(0);
    ui->comboBox_18->setCurrentIndex(0);
    //setup the mqtt
    /*////////////////////////////////////////////////////////////////////////////////*/
    m_client = new QMqttClient(this);
    //m_client->setHostname(ui->lineEdit_3->text());
    m_client->setHostname("test.mosquitto.org");
    //m_client->setPort(ui->spinBox_4->value());
    m_client->setPort(1883);
    /*connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
        //ui->editLog->insertPlainText(content);
        QString LastText;
        LastText = ui->textEdit->toPlainText();
        LastText = LastText.append(content);
        ui->textEdit->setText(LastText);
    });*/
    //connect(m_client, &QMqttClient::connected, this, &Widget::OnConnected);
    connect(m_client, &QMqttClient::messageReceived, this, &Widget::UpdateMessage);
    /*////////////////////////////////////////////////////////////////////////////////*/

    /*////////////////////////////////////////////////////////////////////////////////*/
    /*setup the customplot1*/
    //add the graph and set the color to red
    ui->customplot1_2->addGraph();
    ui->customplot1_2->graph(0)->setPen(QPen(Qt::red));
    ui->customplot1_2->graph(0)->setAntialiasedFill(false);

    //Configure x-Axis as time in secs
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->customplot1_2->xAxis->setTicker(timeTicker);
    ui->customplot1_2->axisRect()->setupFullAxesBox();

    //configure the x and y axis labels
    ui->customplot1_2->xAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->customplot1_2->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->customplot1_2->xAxis->setLabel("Time(s)");
    ui->customplot1_2->yAxis->setLabel("SVM raw datas");

    //make top and right axis visible, but without ticks and label
    ui->customplot1_2->xAxis2->setVisible(false);
    ui->customplot1_2->yAxis2->setVisible(false);
    ui->customplot1_2->xAxis2->setTicks(false);
    ui->customplot1_2->yAxis2->setTicks(false);
    ui->customplot1_2->xAxis2->setTickLabels(false);
    ui->customplot1_2->yAxis2->setTickLabels(false);

    /*setup the customplot2*/
    //add the graph and set the color to red
    ui->customplot2_2->addGraph();
    ui->customplot2_2->graph(0)->setPen(QPen(Qt::red));
    ui->customplot2_2->graph(0)->setAntialiasedFill(false);

    //Configure x-Axis as time in secs
    //QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    //timeTicker->setTimeFormat("%s");
    ui->customplot2_2->xAxis->setTicker(timeTicker);
    ui->customplot2_2->axisRect()->setupFullAxesBox();

    //configure the x and y axis labels
    ui->customplot2_2->xAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->customplot2_2->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->customplot2_2->xAxis->setLabel("Time(s)");
    ui->customplot2_2->yAxis->setLabel("Gyroscope raw datas");

    //make top and right axis visible, but without ticks and label
    ui->customplot2_2->xAxis2->setVisible(false);
    ui->customplot2_2->yAxis2->setVisible(false);
    ui->customplot2_2->xAxis2->setTicks(false);
    ui->customplot2_2->yAxis2->setTicks(false);
    ui->customplot2_2->xAxis2->setTickLabels(false);
    ui->customplot2_2->yAxis2->setTickLabels(false);

    /*setup the customplot3*/
    //add the graph and set the color to red
    ui->customplot3_2->addGraph();
    ui->customplot3_2->graph(0)->setPen(QPen(Qt::red));
    ui->customplot3_2->graph(0)->setAntialiasedFill(false);

    //Configure x-Axis as time in secs
    //QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    //timeTicker->setTimeFormat("%s");
    ui->customplot3_2->xAxis->setTicker(timeTicker);
    ui->customplot3_2->axisRect()->setupFullAxesBox();

    //configure the x and y axis labels
    ui->customplot3_2->xAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->customplot3_2->yAxis->setTickLabelFont(QFont(QFont().family(),8));
    ui->customplot3_2->xAxis->setLabel("Time(s)");
    ui->customplot3_2->yAxis->setLabel("Pitch and Roll raw datas");

    //make top and right axis visible, but without ticks and label
    ui->customplot3_2->xAxis2->setVisible(false);
    ui->customplot3_2->yAxis2->setVisible(false);
    ui->customplot3_2->xAxis2->setTicks(false);
    ui->customplot3_2->yAxis2->setTicks(false);
    ui->customplot3_2->xAxis2->setTickLabels(false);
    ui->customplot3_2->yAxis2->setTickLabels(false);


    //set up and initialize the graph plotting timer
    SVM_DATA = 0;
    GYRO_DATA = 0;
    PITCHandROLL = 0;
    PlotStart = 0;
    connect(timer_plot, &QTimer::timeout, this, &Widget::RealtimePlot);
    timer_plot->start(10);
    /*//////////////////////////////////////////////////////////////////////////////*/


    ReceiveBytes = 0;
    connect(serial, &QSerialPort::readyRead, this, &Widget::SerialPort_Readyread);
    ui->checkBox_7->setCheckState(Qt::Checked);
    //connect(m_client, &QMqttSubscription::messageReceived, this, &Widget::UpdateMessage);

    /*/////////////////////////////////////////////////////////////////////////////*/
    //map setup
    obj1 = ui->quickWidget->rootObject();
   // connect(this, SIGNAL(setCenter(QVariant,QVariant)), obj1, SLOT(setCenter(QVariant, QVariant)));
    //emit setCenter(51.00000000, 0.00000000);
    mc = new MyClass(this);
    connect(mc, SIGNAL(TriggerQML()), obj1, SLOT(showRoute()));
    connect(mc, SIGNAL(TriggerQML_2()), obj1, SLOT(clearRoute()));
    //mywidget = new My3DWidget(this);
    ui->pushButton_2->setStyleSheet("border-style: solid");
    ui->pushButton_2->setStyleSheet("border-color: lightgreen");
    ui->pushButton_2->setStyleSheet("border-radius: 20px");
    ui->pushButton_2->setStyleSheet("background-color: lightgreen");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::TimerEvent()
{
    QStringList newPortStringList;
    newPortStringList.clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        newPortStringList += info.portName();
    if(newPortStringList.size() != PortStringList.size())
    {
        PortStringList = newPortStringList;
        ui->comboBox_13->clear();
        ui->comboBox_13->addItems(newPortStringList);
    }
}


void Widget::on_pushButton_12_clicked()
{
    if(ui->pushButton_12->text() == QString("Open Serial"))
    {
        serial->setPortName(ui->comboBox_13->currentText());
        serial->setBaudRate(ui->comboBox_14->currentText().toInt());
        switch(ui->comboBox_15->currentText().toInt())
        {
            case 5:serial->setDataBits(QSerialPort::Data5);break;
            case 6:serial->setDataBits(QSerialPort::Data6);break;
            case 7:serial->setDataBits(QSerialPort::Data7);break;
            case 8:serial->setDataBits(QSerialPort::Data8);break;
            default:serial->setDataBits(QSerialPort::Data8);
        }
        switch(ui->comboBox_16->currentIndex())
        {
            case 0:serial->setParity(QSerialPort::EvenParity);break;
            case 1:serial->setParity(QSerialPort::OddParity);break;
            case 2:serial->setParity(QSerialPort::NoParity);break;
            default:serial->setParity(QSerialPort::NoParity);
        }
        switch(ui->comboBox_17->currentIndex())
        {
            case 0:serial->setStopBits(QSerialPort::OneStop);break;
            case 1:serial->setStopBits(QSerialPort::OneAndHalfStop);break;
            case 2:serial->setStopBits(QSerialPort::TwoStop);break;
            default:serial->setStopBits(QSerialPort::OneStop);
        }
        switch(ui->comboBox_18->currentIndex())
        {
            case 0:serial->setFlowControl(QSerialPort::NoFlowControl);break;
            case 1:serial->setFlowControl(QSerialPort::HardwareControl);break;
            case 2:serial->setFlowControl(QSerialPort::SoftwareControl);break;
            default:serial->setFlowControl(QSerialPort::NoFlowControl);
        }
        if(!serial->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this, "Error", "Cannot Open Serial", QMessageBox::Ok);
            return;
        }
        ui->comboBox_13->setEnabled(false);
        ui->comboBox_14->setEnabled(false);
        ui->comboBox_15->setEnabled(false);
        ui->comboBox_16->setEnabled(false);
        ui->comboBox_17->setEnabled(false);
        ui->comboBox_18->setEnabled(false);

        ui->pushButton_12->setText("Close Serial");
    }
    else
    {
        serial->close();
        ui->comboBox_13->setEnabled(true);
        ui->comboBox_14->setEnabled(true);
        ui->comboBox_15->setEnabled(true);
        ui->comboBox_16->setEnabled(true);
        ui->comboBox_17->setEnabled(true);
        ui->comboBox_18->setEnabled(true);

        ui->pushButton_12->setText("Open Serial");
    }
}


void Widget::on_checkBox_7_clicked()
{
    ui->checkBox_7->setCheckState(Qt::Checked);
    ui->checkBox_8->setCheckState(Qt::Unchecked);
    ui->checkBox_9->setCheckState(Qt::Unchecked);
}


void Widget::on_checkBox_8_clicked()
{
    ui->checkBox_7->setCheckState(Qt::Unchecked);
    ui->checkBox_8->setCheckState(Qt::Checked);
    ui->checkBox_9->setCheckState(Qt::Unchecked);
}


void Widget::on_checkBox_9_clicked()
{
    ui->checkBox_7->setCheckState(Qt::Unchecked);
    ui->checkBox_8->setCheckState(Qt::Unchecked);
    ui->checkBox_9->setCheckState(Qt::Checked);
}

void Widget::SerialPort_Readyread()
{
    QString LastText;
    int Length;
    if(ui->checkBox_9->checkState() != Qt::Checked)
    {
        LastText = ui->textEdit_2->toPlainText();
        ReceiveText = serial->readAll();
        ReceiveBytes += ReceiveText.length();
        ui->label_32->setText(QString::number(ReceiveBytes));

        if(ui->checkBox_8->checkState() == Qt::Checked)
        {
            ReceiveText = ReceiveText.toLatin1().toHex();
            Length = ReceiveText.length();
            for(int i=0; i<Length/2; i++)
            {
                ReceiveText.insert(2+3*i, ' ');
            }
        }
        else
        {
            ReceiveText = ReceiveText.toLatin1();
        }
        LastText = LastText.append(ReceiveText);
        ui->textEdit_2->setText(LastText);
    }
}

void Widget::on_pushButton_10_clicked()
{
    ui->textEdit_2->clear();
    ui->label_32->setText(QString::number(0));
}



void Widget::on_pushButton_11_clicked()
{
    if(ui->pushButton_11->text() == QString("Open Internet"))
    {
        /*auto subscription = m_client->subscribe(ui->lineEdit_2->text(), ui->spinBox_2->text().toUInt());
        if (!subscription) {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }*/
        /*auto subWindow = new SubscriptionWindow(subscription);
        subWindow->setWindowTitle(subscription->topic().filter());
        subWindow->show();*/
        m_client->connectToHost();
        //auto subscription1 = m_client->subscribe(ui->lineEdit_4->text() + QString("SVM"), ui->spinBox_3->text().toUInt());
        auto subscription1 = m_client->subscribe(QString("IC.embedded/fall_detection/SVM_acc/#"), 0);
        //auto subscription2 = m_client->subscribe(ui->lineEdit_4->text() + QString("GYRO"), ui->spinBox_3->text().toUInt());
        auto subscription2 = m_client->subscribe(QString("IC.embedded/fall_detection/SVM_gyr/#"), 0);
        //auto subscription3 = m_client->subscribe(ui->lineEdit_4->text() + QString("ANGLE"), ui->spinBox_3->text().toUInt());
        auto subscription3 = m_client->subscribe(QString("IC.embedded/fall_detection/Angle/#"), 0);
        //auto subscription4 = m_client->subscribe(ui->lineEdit_4->text() + QString("FALL"), ui->spinBox_3->text().toUInt());
        auto subscription4 = m_client->subscribe(QString("IC.embedded/fall_detection/Fall/#"), 0);
        if (!subscription1 || !subscription2 || !subscription3 || !subscription4) {
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
            return;
        }

        ui->lineEdit_3->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->spinBox_4->setEnabled(false);
        ui->spinBox_3->setEnabled(false);

        ui->pushButton_11->setText("Unscribe");
    }
    else
    {
        m_client->disconnectFromHost();
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->spinBox_4->setEnabled(true);
        ui->spinBox_3->setEnabled(true);

        ui->pushButton_11->setText("Open Internet");
    }
}

//this is the function when getting the message through MQTT
void Widget::UpdateMessage(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << "Received message on topic" << topic.name() << "with payload" << message;
    //if(topic == ui->lineEdit_4->text() + QString("SVM"))
    //if(topic == QString("IC.embedded/GROUP_NAME/Pitch"))
    //if(topic == QString("IC.embedded/GROUP_NAME/Fall"))
    if(topic == QString("IC.embedded/fall_detection/SVM_acc"))
    {
        //bool ok;
        //qDebug() << "Case1 message: " << message;
        //qDebug() << "Case1 PITCH: " << message.toDouble();
        //SVM_DATA = message.toULong(&ok);
        SVM_DATA = message.toDouble();
    }
    //else if(topic == ui->lineEdit_4->text() + QString("GYRO"))
    else if(topic == QString("IC.embedded/fall_detection/SVM_gyr"))
    {
        //bool ok;
        //GYRO_DATA = message.toULong(&ok);
        GYRO_DATA = message.toDouble();
    }
    //else if(topic == ui->lineEdit_4->text() + QString("ANGLE"))
    else if(topic == QString("IC.embedded/fall_detection/Angle"))
    {
        //bool ok;
        //PITCHandROLL = message.toULong(&ok);
        PITCHandROLL = message.toDouble();
    }
    else if(topic == QString("IC.embedded/fall_detection/GPS_LAT"))
    {
        TOLAT = message.toDouble();
    }
    else if(topic == QString("IC.embedded/fall_detection/GPS_LNG"))
    {
        TOLNG = message.toDouble();
    }
    else
    {
        //bool ok;
        if(message.toInt() == 1)
        {
            ui->pushButton_2->setText(QString("FALLED"));
            FALL = 1;
            ui->pushButton_2->setStyleSheet("background-color: red");
            //player->setPosition(0);
            player->play();
            obj1->setProperty("toLat", TOLAT);
            obj1->setProperty("toLng", TOLNG);
            emit mc->TriggerQML();
        }
        else
        {
            ui->pushButton_2->setText(QString("ADL"));
            ui->pushButton_2->setStyleSheet("background-color: lightgreen");
            //player->setPosition(0);
            //player->pause();
            FALL = 0;
            TOLAT = LAT;
            TOLNG = LNG;
        }
    }
}

/*void Widget::OnConnected()
{
    auto subscription1 = m_client->subscribe(ui->lineEdit_2->text() + QString("SVM"), ui->spinBox_2->text().toUInt());
    auto subscription2 = m_client->subscribe(ui->lineEdit_2->text() + QString("GYRO"), ui->spinBox_2->text().toUInt());
    auto subscription3 = m_client->subscribe(ui->lineEdit_2->text() + QString("ANGLE"), ui->spinBox_2->text().toUInt());
    auto subscription4 = m_client->subscribe(ui->lineEdit_2->text() + QString("FALL"), ui->spinBox_2->text().toUInt());
    if (!subscription1 || !subscription2 || !subscription3 || !subscription4) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}*/

//the slot of realtime plotting
void Widget::RealtimePlot()
{
    if(PlotStart)
    {
        static QElapsedTimer time;//(QTime::currentTime());
        double key = time.elapsed()/1000.0;
        static double lastPointKey = 0;
        if(key - lastPointKey > 0.002)
        {
            //qDebug() << "Pich is: " << SVM_DATA;
            ui->customplot1_2->graph(0)->addData(key, (double)SVM_DATA);
            ui->customplot2_2->graph(0)->addData(key, (double)GYRO_DATA);
            ui->customplot3_2->graph(0)->addData(key, (double)PITCHandROLL);
            lastPointKey = key;
        }

        //make key axis range scroll right with the data at a constant range of 8.
        ui->customplot1_2->graph(0)->rescaleValueAxis();
        ui->customplot1_2->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->customplot1_2->replot();

        ui->customplot2_2->graph(0)->rescaleValueAxis();
        ui->customplot2_2->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->customplot2_2->replot();

        ui->customplot3_2->graph(0)->rescaleValueAxis();
        ui->customplot3_2->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->customplot3_2->replot();
    }
}

void Widget::on_pushButton_7_clicked()
{
    PlotStart = 1;
}


void Widget::on_pushButton_8_clicked()
{
    if(ui->pushButton_8->text() == QString("STOP"))
    {
        timer_plot->stop();
        ui->pushButton_8->setText(QString("CONTINUE"));
    }
    else
    {
        timer_plot->start(5);
        ui->pushButton_8->setText(QString("STOP"));
    }

}


void Widget::on_pushButton_9_clicked()
{
    //timer_plot->start(5);
    //ui->customplot1->clearItems();
    //ui->customplot2->clearItems();
    //ui->customplot3->clearItems();
    SVM_DATA = 0;
    GYRO_DATA = 0;
    PITCHandROLL = 0;

}



void Widget::on_cancelbutton_clicked()
{
    ui->pushButton_2->setText(QString("ADL"));
    ui->pushButton_2->setStyleSheet("background-color: lightgreen");
    FALL = 0;
    TOLAT = LAT;
    TOLNG = LNG;
    player->setPosition(0);
    player->pause();
}


void Widget::on_pushButton_13_clicked()
{
    //obj1->setProperty("oldLat", 0.17621700);
    //obj1->setProperty("oldLng", 51.49905683);
    emit mc->TriggerQML_2();

}


void Widget::on_pushButton_clicked()
{ 
    emit mc->TriggerQML();
    //sending model and ID to Raspberry Pi
    QMqttTopicName topic_mode("mode");
    //QMqttMessage message_mode(QString(ui->comboBox->currentText()));//(QString(ui->comboBox->currentText()));
    //auto publish1 = m_client->publish(QString("mode"), ui->comboBox->currentIndex());
    /*switch(ui->comboBox->currentIndex())
    {
    case 0: m_client->publish(QString("mode"), 0); break;
    case 1: m_client->publish(QString("mode"), ); break;
    }*/
}

void Widget::ProcessVideo()
{
    if(player->mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        if(FALL == 0)
        {
            player->setPosition(0);
            player->pause();
        }
        else
        {
            player->setPosition(0);
            player->play();
        }
    }
}

