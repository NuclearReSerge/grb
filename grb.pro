TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET  = grb

DEFINES += GRB_VERSION="0.1"

QMAKE_CXXFLAGS += -std=c++11 -O0 -Wextra -Werror -Wpedantic

QMAKE_LFLAGS = -g

HEADERS += \
    Analyzer/AnalyzeGrbcat.h \
    Analyzer/Analyzer.h \
    Analyzer/Correlation.h \
    Analyzer/CorrelationTimeArcGrbcat.h \
    Analyzer/GreatCircleDistance.h \
    CLI/Cmd.h \
    CLI/CmdDatabase.h \
    CLI/CmdHelp.h \
    CLI/CmdQuit.h \
    CLI/CommandFactory.h \
    CLI/CommandLine.h \
    CLI/CommandMapper.h \
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
    Tools/Mapper.h \
    Tools/NameMapper.h \
    Tools/Parser.h \
    CLI/CmdAnalyze.h \
    Analyzer/AnalyzerFactory.h

SOURCES += \
    Analyzer/AnalyzeGrbcat.cpp \
    Analyzer/Analyzer.cpp \
    Analyzer/Correlation.cpp \
    Analyzer/CorrelationTimeArcGrbcat.cpp \
    Analyzer/GreatCircleDistance.cpp \
    CLI/Cmd.cpp \
    CLI/CmdDatabase.cpp \
    CLI/CmdHelp.cpp \
    CLI/CmdQuit.cpp \
    CLI/CommandFactory.cpp \
    CLI/CommandLine.cpp \
    CLI/CommandMapper.cpp \
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
    Main/Init.cpp \
    Main/Main.cpp \
    Tools/NameMapper.cpp \
    Tools/Parser.cpp \
    CLI/CmdAnalyze.cpp \
    Analyzer/AnalyzerFactory.cpp
