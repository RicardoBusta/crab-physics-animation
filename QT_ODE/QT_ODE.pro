#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T22:28:35
#
#-------------------------------------------------

QT       += core gui opengl glu

TARGET = QT_ODE
TEMPLATE = app

DEFINES += \
    SHADERS_ENABLED \
    dSINGLE
    #DEBUG_MODE

SOURCES += \
    main.cpp \
    physics/physics.cpp \    
    interface/glframe.cpp \
    interface/mainwindow.cpp \
    graphics/glwidget.cpp \
    graphics/scene.cpp \
    graphics/glprimitive.cpp \
    graphics/material.cpp \
    graphics/camera.cpp \
    math/vector3f.cpp \
    math/matrix4f.cpp

HEADERS  += \
    physics/physics.h \
    interface/glframe.h \
    interface/mainwindow.h \
    graphics/glwidget.h \
    graphics/scene.h \
    graphics/glprimitive.h \
    graphics/material.h \
    graphics/camera.h \
    math/vector3f.h \
    math/matrix4f.h

FORMS    += \
    interface/mainwindow.ui

OTHER_FILES += \
    shaders/phong.vert \
    shaders/phong.frag \
    shaders/toon.vert \
    shaders/toon.frag

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

RESOURCES += \
    shaders/shaders.qrc
