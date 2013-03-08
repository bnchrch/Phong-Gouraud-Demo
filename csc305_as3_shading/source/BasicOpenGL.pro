#-------------------------------------------------
#
# Project created by QtCreator 2012-09-13T13:41:55
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = BasicOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basicopenglview.cpp \
    vector.cpp \
    matrix.cpp \
    geometry.cpp \
    supporting_files/s_program.cpp \
    supporting_files/s_geometry.cpp \
    supporting_files/s_shader.cpp \
    supporting_files/s_openglerror.cpp \
    supporting_files/s_parameter.cpp \
    supporting_files/s_stream.cpp \
    supporting_files/s_tokenizer.cpp \
    supporting_files/s_core3_2_context.cpp \
    supporting_files/s_basicopenglview.cpp \
    supporting_files/s_mainwindow.cpp

HEADERS  += mainwindow.h \
    basicopenglview.h \
    geometry.h \
    vector.h \
    supporting_files/s_program.h \
    supporting_files/s_parameter.h \
    matrix.h \
    supporting_files/s_openglerror.h \
    supporting_files/s_shader.h \
    supporting_files/s_stream.h \
    supporting_files/s_tokenizer.h \
    supporting_files/s_core3_2_context.h

FORMS    += mainwindow.ui

mac {
     OBJECTIVE_SOURCES  += supporting_files/s_core_profile_attributes.mm 
     LIBS += -framework Foundation -framework Cocoa
}
else {
    INCLUDEPATH += external/include
        SOURCES += external/src/glew.c
}

OTHER_FILES += \
    materials/phong.vs \
    materials/phong.material \
    materials/phong.fs \
    materials/Gouraud.vs \
    materials/Gouraud.material \
    materials/Gouraud.fs \
    materials/displacement.png \
    materials/default.vs \
    materials/default.material \
    materials/default.fs \
    materials/colormap.png \
    materials/ben.vs \
    materials/ben.material \
    materials/ben.fs \
    materials/ben copy.vs \
    materials/Gouraud2.vs \
    materials/Gouraud2.material \
    materials/Gouraud2.fs \
    materials/phongTex.vs \
    materials/phongTex.material \
    materials/phongTex.fs \
    materials/phongTexBump.vs \
    materials/phongTexBump.material \
    materials/phongTexBump.fs
