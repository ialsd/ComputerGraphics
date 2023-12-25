QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -lopengl32
LIBS += -lglu32

CONFIG += c++17

SOURCES += \
    main.cpp \

HEADERS += \
    ../../../../../../../freeglut/include/GL/freeglut.h \
    ../../../../../../../freeglut/include/GL/freeglut_ext.h \
    ../../../../../../../freeglut/include/GL/freeglut_std.h \
    ../../../../../../../freeglut/include/GL/glut.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../../../../../../freeglut/include/GL

win32: LIBS += -L$$PWD/../../../../../../../freeglut/lib/x64/ -lfreeglut

INCLUDEPATH += $$PWD/../../../../../../../freeglut/lib/x64
DEPENDPATH += $$PWD/../../../../../../../freeglut/lib/x64

RESOURCES += \
    res.qrc
