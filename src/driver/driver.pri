SOURCES += \
    $$PWD/CanFilter/canfilter.cpp \
    $$PWD/CanFilter/canfilter_bxcan.cpp \
    $$PWD/CanFilter/canfilter_fdcan.cpp \
    $$PWD/CanFilter/canfilter_usb.cpp \
    $$PWD/CanFilter/usb_device.cpp \
    $$PWD/CanFilter/usb_info.cpp \
    $$PWD/CanInterface.cpp \
    $$PWD/CanListener.cpp \
    $$PWD/CanDriver.cpp \
    $$PWD/CanTiming.cpp \
    $$PWD/GenericCanSetupPage.cpp \
    $$PWD/HardwareFilter.cpp

HEADERS  += \
    $$PWD/CanFilter/canfilter.hpp \
    $$PWD/CanFilter/canfilter_bxcan.hpp \
    $$PWD/CanFilter/canfilter_fdcan.hpp \
    $$PWD/CanFilter/canfilter_usb.hpp \
    $$PWD/CanFilter/usb_device.hpp \
    $$PWD/CanFilter/usb_info.hpp \
    $$PWD/CanInterface.h \
    $$PWD/CanListener.h \
    $$PWD/CanDriver.h \
    $$PWD/CanTiming.h \
    $$PWD/GenericCanSetupPage.h \
    $$PWD/HardwareFilter.h

FORMS += \
    $$PWD/GenericCanSetupPage.ui
