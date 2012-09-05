#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T22:28:35
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = QT_ODE
TEMPLATE = app

DEFINES += dSINGLE

SOURCES += \
    main.cpp \
    physics/physics.cpp \
    interface/glwidget.cpp \
    interface/glframe.cpp \
    interface/mainwindow.cpp \
    graphics/scene.cpp \
    graphics/glprimitive.cpp \
    graphics/material.cpp

HEADERS  += \
    physics/physics.h \
    interface/glwidget.h \
    interface/glframe.h \
    interface/mainwindow.h \
    graphics/scene.h \
    graphics/glprimitive.h \
    graphics/material.h

FORMS    += \
    interface/mainwindow.ui

#linux
unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lode
INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include
unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libode.a

#windows
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ode-0.12/lib/DebugSingleDLL/ -lode_single
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ode-0.12/lib/DebugSingleDLL/ -lode_singled
INCLUDEPATH += $$PWD/../ode-0.12/include
DEPENDPATH += $$PWD/../ode-0.12/include
