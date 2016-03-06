#ifndef DSETTINGS_H
#define DSETTINGS_H

#include <QObject>
#include "template.h"

class dSettings : public QObject
{
    Q_OBJECT

public:
    dSettings(dTemplate*);

protected:
    dTemplate* designTemplate;

};

#endif // DSETTINGS_H
