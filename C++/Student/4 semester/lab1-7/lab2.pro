QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csv_reader.cpp \
    json_reader.cpp \
    libs.cpp \
    main.cpp \
    mainwindow.cpp \
    qtexterror.cpp

HEADERS += \
    abstract_reader.h \
    csv_reader.h \
    json.hpp \
    json_reader.h \
    libs.h \
    mainwindow.h \
    qtexterror.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    lab2_ru_RU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

OTHER_FILES += \
    input.csv
