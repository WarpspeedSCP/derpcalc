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
    real.hpp \
    token.hpp \
    eval.hpp


SOURCES += \
    derp.cpp \
    io.cpp \
    parse.cpp \
    token.cpp \
    eval.cpp \
    derp.cpp

DEFINES += "DEBUG"
