TEMPLATE     = app
CONFIG      += qt release
TARGET       = ascurpic_hack
DEPENDPATH  += . include src
INCLUDEPATH += . include

QMAKE_CXXFLAGS_RELEASE += -march=native -pipe -O2
QMAKE_CFLAGS_RELEASE    = $$QMAKE_CXXFLAGS_RELEASE
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wfatal-errors
QMAKE_CFLAGS_WARN_ON    = $$QMAKE_CXXFLAGS_WARN_ON

HEADERS += include/ascurpic.h \
           include/bitmap.h \
           include/gui.h

SOURCES += src/disp_info_bmp.c \
           src/free_bitmap.c \
           src/get_bmp_color.c \
           src/load_bitmap.c \
           src/main.cpp \
           src/parse_opts.c \
           src/write_page.c \
           src/xmalloc.c \
           src/gui.cpp
