QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/LED_components/led_driver.cpp \
    core/LED_components/led_module.cpp \
    core/main.cpp \
    core/mainwindow-dual-config.cpp \
    core/mainwindow-input-change.cpp \
    core/mainwindow-startup.cpp \
    core/mainwindow-setup-slots.cpp \
    core/mainwindow-single-config.cpp \
    core/mainwindow-colour.cpp \
    core/mainwindow-table.cpp \
    core/mainwindow.cpp

HEADERS += \
    core/LED_components/led_driver.h \
    core/LED_components/led_module.h \
    core/mainwindow.h

FORMS += \
    core/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
