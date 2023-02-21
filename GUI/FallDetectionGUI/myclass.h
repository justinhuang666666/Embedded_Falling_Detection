#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
//#include <Qt3DCore>
//#include <Qt3DRender>
//#include <Qt3DExtras>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);

signals:
    void TriggerQML(void);
    void TriggerQML_2(void);
};

#endif // MYCLASS_H
