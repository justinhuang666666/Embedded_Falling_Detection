QT       += core gui serialport mqtt location positioning quickwidgets network quick multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

QT_FOR_CONFIG += location-private
qtConfig(geoservices_mapboxgl): QT += sql
qtConfig(geoservices_osm): QT += concurrent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -LC:\Program Files\OpenSSL-Win64\lib -lopenssl
#LIBS += -lopengl32

SOURCES += \
    main.cpp \
    myclass.cpp \
    myvideo.cpp \
    qcustomplot.cpp \
    widget.cpp

HEADERS += \
    myclass.h \
    myvideo.h \
    qcustomplot.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc
