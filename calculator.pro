TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES

DISTFILES += \
    calculator.pro.user \
    calculator.pro.autosave \
    LICENSE \
    README.md \

HEADERS += \
    io.hpp \
    parse.hpp \
    token.hpp \
    eval.hpp \
    types.hpp \
    tree.hh \
    tree_util.hh


SOURCES += \
    derp.cpp \
    io.cpp \
    parse.cpp \
    token.cpp \
    eval.cpp \
    derp.cpp

DEFINES += "DEBUG"
