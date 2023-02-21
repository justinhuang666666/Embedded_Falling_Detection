#include "myvideo.h"
#include <QMediaPlayer>
#include <QVideoWidget>

MyVideo::MyVideo(QWidget *parent)
    : QWidget{parent}
{
    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *vw = new QVideoWidget;

    player->setVideoOutput(vw);
    //player->setMedia(QUrl::fromLocalFile("C:/Users/xujub/Desktop/GUI/test/falling.mpg"));

    vw->setGeometry(100, 100, 300, 400);
    vw->show();
    player->play();
}
