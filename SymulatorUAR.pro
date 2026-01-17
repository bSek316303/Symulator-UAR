QT       += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Generator.cpp \
    ProstyUAR.cpp \
    arx_dialog.cpp \
    fabryka_wykresow.cpp \
    main.cpp \
    mainwindow.cpp \
    menedzer.cpp \
    menedzerUAR.cpp \
    modelARX.cpp \
    regulatorPID.cpp \
    sim_handler.cpp \
    testy.cpp \
    testy_setterow.cpp \
    testy_symulacji.cpp

HEADERS += \
    Generator.h \
    ProstyUAR.h \
    arx_dialog.h \
    fabryka_wykresow.h \
    mainwindow.h \
    menedzer.h \
    menedzerUAR.h \
    modelARX.h \
    regulatorPID.h \
    sim_handler.h \
    stale.h \
    testy.h \
    testy_setterow.h \
    testy_symulacji.h

FORMS += \
    arx_dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
