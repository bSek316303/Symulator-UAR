QT       += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Generator.cpp \
    ProstyUAR.cpp \
    arxconfig.cpp \
    fabryka_wykresow.cpp \
    genconfig.cpp \
    main.cpp \
    mainwindow.cpp \
    menedzer.cpp \
    menedzerUAR.cpp \
    modelARX.cpp \
    obsluga_pliku.cpp \
    pidconfig.cpp \
    regulatorPID.cpp \
    testy.cpp

HEADERS += \
    Generator.h \
    ProstyUAR.h \
    arxconfig.h \
    config.h \
    fabryka_wykresow.h \
    genconfig.h \
    mainwindow.h \
    menedzer.h \
    menedzerUAR.h \
    modelARX.h \
    obsluga_pliku.h \
    pidconfig.h \
    regulatorPID.h \
    stale.h \
    testy.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
