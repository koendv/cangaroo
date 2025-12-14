#ifndef HARDWAREFILTER_H
#define HARDWAREFILTER_H

#include <QString>
#include <driver/CanInterface.h>

bool setHardwareFilter(CanInterface *intf, QString filter_def);

#endif // HARDWAREFILTER_H
