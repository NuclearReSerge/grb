TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET  = grb

DEFINES += GRB_VERSION="0.1"

QMAKE_CXXFLAGS += -std=c++11 -O0 -Wextra -Werror -Wpedantic

QMAKE_LFLAGS = -g

HEADERS += \
    Common/Exception.h \
    Common/Global.h \
    Common/GlobalName.h \
    Common/Singleton.h \
    Common/trace.h \
    Data/Catalog.h \
    Data/CatalogEntry.h \
    Data/CatalogEntryFactory.h \
    Data/CatalogEntryGrbcat.h \
    Data/Coordinates.h \
    Data/DataBaseFormat.h \
    Data/DataBaseFormatFactory.h \
    Data/DataBaseFormatGrbcat.h \
    Data/DataType.h \
    Data/Duration.h \
    Data/Observatory.h \
    Data/Reference.h \
    Data/Region.h \
    Data/TimeDef.h \
    Data/TimeMod.h \
    Data/TimePoint.h \
    Tools/NameMapper.h \
    Tools/Parser.h \
    Analyzer/GreatCircleDistance.h

SOURCES += \
    Analyzer/Init.cpp \
    Analyzer/Main.cpp \
    Common/Exception.cpp \
    Common/GlobalName.cpp \
    Data/Catalog.cpp \
    Data/CatalogEntry.cpp \
    Data/CatalogEntryFactory.cpp \
    Data/CatalogEntryGrbcat.cpp \
    Data/Coordinates.cpp \
    Data/DataBaseFormat.cpp \
    Data/DataBaseFormatFactory.cpp \
    Data/DataBaseFormatGrbcat.cpp \
    Data/DataType.cpp \
    Data/Duration.cpp \
    Data/Observatory.cpp \
    Data/Reference.cpp \
    Data/Region.cpp \
    Data/TimeDef.cpp \
    Data/TimeMod.cpp \
    Data/TimePoint.cpp \
    Tools/NameMapper.cpp \
    Tools/Parser.cpp \
    Analyzer/GreatCircleDistance.cpp
