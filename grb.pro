TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET  = grb

DEFINES += GRB_VERSION="0.2"

QMAKE_CXXFLAGS += -std=c++11 -O0 -Wextra -Werror -Wpedantic

QMAKE_LFLAGS = -g

HEADERS += \
    Analyzer/Analyzer.h \
    Analyzer/AnalyzerFactory.h \
    Analyzer/AnalyzerGrbcat.h \
    CLI/Cmd.h \
    CLI/CmdDatabase.h \
    CLI/CmdHelp.h \
    CLI/CmdModel.h \
    CLI/CmdQuit.h \
    CLI/CommandLine.h \
    Common/Exception.h \
    Common/Global.h \
    Common/Singleton.h \
    Common/trace.h \
    Correlation/Correlation.h \
    Correlation/CorrelationFactory.h \
    Correlation/CorrelationTimeArcGrbcat.h \
    Correlation/GreatCircleDistance.h \
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
    Main/AnalysisData.h \
    Model/IsotropicBallModel.h \
    Model/IsotropicSphereModel.h \
    Model/Model.h \
    Model/ModelFactory.h \
    Tools/ConvertSpaceTime.h \
    Tools/Mapper.h \
    Tools/NameMapper.h \
    Tools/Parser.h \
    Filter/Filter.h \
    Filter/FilterFactory.h \
    Filter/FilterNone.h \
    Analyzer/AnalyzerMapper.h \
    Correlation/CorrelationMapper.h \
    CLI/CmdMapper.h \
    CLI/CmdFactory.h \
    Data/DataBaseFormatMapper.h \
    Data/CatalogEntryMapper.h \
    Data/CoordinateSystemMapper.h \
    Data/DateMapper.h \
    Filter/FilterMapper.h \
    Model/ModelMapper.h \
    Data/ColumnMapper.h \
    Data/UnitMapper.h \
    Data/ValueMapper.h \
    Correlation/ArcFormulaMapper.h \
    CLI/CmdAnalyzer.h \
    CLI/CmdFilter.h \
    CLI/CmdCorrelation.h

SOURCES += \
    Analyzer/Analyzer.cpp \
    Analyzer/AnalyzerFactory.cpp \
    Analyzer/AnalyzerGrbcat.cpp \
    CLI/Cmd.cpp \
    CLI/CmdDatabase.cpp \
    CLI/CmdHelp.cpp \
    CLI/CmdModel.cpp \
    CLI/CmdQuit.cpp \
    CLI/CommandLine.cpp \
    Common/Exception.cpp \
    Correlation/Correlation.cpp \
    Correlation/CorrelationFactory.cpp \
    Correlation/CorrelationTimeArcGrbcat.cpp \
    Correlation/GreatCircleDistance.cpp \
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
    Main/Init.cpp \
    Main/Main.cpp \
    Model/IsotropicBallModel.cpp \
    Model/IsotropicSphereModel.cpp \
    Model/Model.cpp \
    Model/ModelFactory.cpp \
    Tools/ConvertSpaceTime.cpp \
    Tools/NameMapper.cpp \
    Tools/Parser.cpp \
    Filter/Filter.cpp \
    Filter/FilterFactory.cpp \
    Filter/FilterNone.cpp \
    Analyzer/AnalyzerMapper.cpp \
    Correlation/CorrelationMapper.cpp \
    CLI/CmdFactory.cpp \
    CLI/CmdMapper.cpp \
    Data/DataBaseFormatMapper.cpp \
    Data/CatalogEntryMapper.cpp \
    Data/CoordinateSystemMapper.cpp \
    Data/DateMapper.cpp \
    Filter/FilterMapper.cpp \
    Model/ModelMapper.cpp \
    Data/ColumnMapper.cpp \
    Data/UnitMapper.cpp \
    Data/ValueMapper.cpp \
    Correlation/ArcFormulaMapper.cpp \
    CLI/CmdAnalyzer.cpp \
    CLI/CmdFilter.cpp \
    CLI/CmdCorrelation.cpp

