#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T12:47:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = designer
TEMPLATE = app

SOURCES += main.cpp \
           designer.cpp \
           textedit.cpp \
           coloredbutton.cpp \
           designer_covers.cpp \
           designer_itunes.cpp \
           designer_files.cpp \
           designer_guisets.cpp \
           designer_lastfm.cpp \
           designer_templates.cpp \
           designer_icons.cpp \
           template.cpp \
           settings.cpp \
           albumsettings.cpp \
           decorationsettings.cpp

HEADERS  += designer.h \
            textedit.h \
            coloredbutton.h \
            template.h \
            settings.h \
            albumsettings.h \
            decorationsettings.h

FORMS += \
    designer.ui

INCLUDEPATH += $$PWD/../3rdparty/taglib/include/

win32
{
    LIBS += -L$$PWD/../3rdparty/taglib/lib/libtag.dll.a
}

unix
{
    LIBS += /usr/local/lib/libtag.a
    LIBS += /usr/local/lib/libz.a
}
