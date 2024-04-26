#ifndef SSVEPCLASSIFY_H
#define SSVEPCLASSIFY_H

#include <QObject>
#include "CCA/cca.h"
class SSVEPClassify : public QObject
{
    Q_OBJECT
public:
    explicit SSVEPClassify(QObject *parent = nullptr);
    double Classify(double X[][mydatalength2],int channel_num);
signals:
private:
    void *classifier;
};

#endif // SSVEPCLASSIFY_H
