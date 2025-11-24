QT       += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Generator.cpp \
    ProstyUAR.cpp \
    main.cpp \
    mainwindow.cpp \
    menedzerUAR.cpp \
    menedzer_symulacji.cpp \
    modelARX.cpp \
    obsluga_pliku.cpp \
    regulatorPID.cpp

HEADERS += \
    Generator.h \
    ProstyUAR.h \
    main.h \
    mainwindow.h \
    menedzerUAR.h \
    menedzer_symulacji.h \
    modelARX.h \
    obsluga_pliku.h \
    regulatorPID.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
