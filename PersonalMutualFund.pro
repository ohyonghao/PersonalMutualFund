QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AccountLedgerView.cpp \
    DateDelegate.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AccountLedgerView.h \
    DateDelegate.h \
    mainwindow.h

FORMS += \
    AccountLedgerView.ui \
    mainwindow.ui

TRANSLATIONS += \
    PersonalMutualFund_zh_TW.ts


# Setup Postgres Support
unix:LIBS += -lpq
win32:LIBS += libpqdll.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
