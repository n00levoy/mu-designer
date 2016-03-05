#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T12:47:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = designer
TEMPLATE = app

SOURCES += main.cpp\
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
    dtemplate.cpp \
    dsettings.cpp \
    dalbumsettings.cpp \
    ddecorationsettings.cpp

HEADERS  += designer.h \
    textedit.h \
    coloredbutton.h \
    dtemplate.h \
    dsettings.h \
    dalbumsettings.h \
    ddecorationsettings.h

FORMS += \
    designer.ui

TAGLIBDIR = $$quote(E:/Qt/Libs/taglib-1.10)
INCLUDEPATH += $$quote( $${TAGLIBDIR}/ )
INCLUDEPATH += $$quote( $${TAGLIBDIR}/taglib )
INCLUDEPATH += $$quote( $${TAGLIBDIR}/taglib/toolkit )
INCLUDEPATH += $$quote( $${TAGLIBDIR}/taglib/mpeg )

LIBS += $$quote($${TAGLIBDIR}/lib/libtaglib.a)

RESOURCES +=
