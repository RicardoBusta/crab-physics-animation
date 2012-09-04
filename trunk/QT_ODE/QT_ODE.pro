#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T22:28:35
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = QT_ODE
TEMPLATE = app

SOURCES += \
    main.cpp \
    physics/physics.cpp \
    interface/glwidget.cpp \
    interface/glframe.cpp \
    interface/mainwindow.cpp \
    graphics/scene.cpp \
    graphics/glprimitive.cpp

HEADERS  += \
    physics/physics.h \
    interface/glwidget.h \
    interface/glframe.h \
    interface/mainwindow.h \
    graphics/scene.h \
    graphics/glprimitive.h

FORMS    += \
    interface/mainwindow.ui

INCLUDEPATH += $$PWD/../ode-0.12/include
DEPENDPATH += $$PWD/../ode-0.12/include

#linux
unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lode

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../../../../../../usr/local/lib/libode.a

#win32
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ode-0.12/lib/DebugSingleLib/ -llibode_single
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ode-0.12/lib/DebugSingleLib/ -llibode_singled

INCLUDEPATH += $$PWD/../ode-0.12/lib/DebugSingleLib
DEPENDPATH += $$PWD/../ode-0.12/lib/DebugSingleLib

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../ode-0.12/lib/DebugSingleLib/libode_single.a
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../ode-0.12/lib/DebugSingleLib/libode_singled.a
