TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET  = grb

DEFINES += GRB_VERSION="0.2"

QMAKE_CXXFLAGS += -std=c++11 -O0 -Wextra -Werror -Wpedantic

QMAKE_LFLAGS = -g

QMAKE_LIBS =

HEADERS += \
    Analyzer/Analyzer.h \
    Analyzer/AnalyzerFactory.h \
    Analyzer/AnalyzerGrbcat.h \
    Analyzer/AnalyzerMapper.h \
    CLI/Cmd.h \
    CLI/CmdAnalyzer.h \
    CLI/CmdCorrelation.h \
    CLI/CmdDatabase.h \
    CLI/CmdFactory.h \
    CLI/CmdFilter.h \
    CLI/CmdHelp.h \
    CLI/CmdMapper.h \
    CLI/CmdModel.h \
    CLI/CmdQuit.h \
    CLI/CommandLine.h \
    Common/Exception.h \
    Common/Global.h \
    Common/Singleton.h \
    Common/trace.h \
    Correlation/ArcFormulaMapper.h \
    Correlation/Correlation.h \
    Correlation/CorrelationFactory.h \
    Correlation/CorrelationMapper.h \
    Correlation/CorrelationTimeArcGrbcat.h \
    Correlation/GreatCircleDistance.h \
    Data/Catalog.h \
    Data/CatalogEntry.h \
    Data/CatalogEntryFactory.h \
    Data/CatalogEntryGrbcat.h \
    Data/CatalogEntryMapper.h \
    Data/ColumnMapper.h \
    Data/Coordinates.h \
    Data/CoordinateSystemMapper.h \
    Data/DataBaseFormat.h \
    Data/DataBaseFormatFactory.h \
    Data/DataBaseFormatGrbcat.h \
    Data/DataBaseFormatMapper.h \
    Data/DataType.h \
    Data/DateMapper.h \
    Data/Duration.h \
    Data/Observatory.h \
    Data/Reference.h \
    Data/Region.h \
    Data/TimeDef.h \
    Data/TimeMod.h \
    Data/UnitMapper.h \
    Data/ValueMapper.h \
    Filter/Filter.h \
    Filter/FilterFactory.h \
    Filter/FilterMapper.h \
    Filter/FilterNone.h \
    Main/AnalysisData.h \
    Model/IsotropicBallModel.h \
    Model/IsotropicSphereModel.h \
    Model/Model.h \
    Model/ModelFactory.h \
    Model/ModelMapper.h \
    Tools/ConvertSpaceTime.h \
    Tools/Mapper.h \
    Tools/NameMapper.h \
    Tools/Parser.h \
    Model/ModelCmdMapper.h

SOURCES += \
    Analyzer/Analyzer.cpp \
    Analyzer/AnalyzerFactory.cpp \
    Analyzer/AnalyzerGrbcat.cpp \
    Analyzer/AnalyzerMapper.cpp \
    CLI/Cmd.cpp \
    CLI/CmdAnalyzer.cpp \
    CLI/CmdCorrelation.cpp \
    CLI/CmdDatabase.cpp \
    CLI/CmdFactory.cpp \
    CLI/CmdFilter.cpp \
    CLI/CmdHelp.cpp \
    CLI/CmdMapper.cpp \
    CLI/CmdModel.cpp \
    CLI/CmdQuit.cpp \
    CLI/CommandLine.cpp \
    Common/Exception.cpp \
    Correlation/ArcFormulaMapper.cpp \
    Correlation/Correlation.cpp \
    Correlation/CorrelationFactory.cpp \
    Correlation/CorrelationMapper.cpp \
    Correlation/CorrelationTimeArcGrbcat.cpp \
    Correlation/GreatCircleDistance.cpp \
    Data/Catalog.cpp \
    Data/CatalogEntry.cpp \
    Data/CatalogEntryFactory.cpp \
    Data/CatalogEntryGrbcat.cpp \
    Data/CatalogEntryMapper.cpp \
    Data/ColumnMapper.cpp \
    Data/Coordinates.cpp \
    Data/CoordinateSystemMapper.cpp \
    Data/DataBaseFormat.cpp \
    Data/DataBaseFormatFactory.cpp \
    Data/DataBaseFormatGrbcat.cpp \
    Data/DataBaseFormatMapper.cpp \
    Data/DataType.cpp \
    Data/DateMapper.cpp \
    Data/Duration.cpp \
    Data/Observatory.cpp \
    Data/Reference.cpp \
    Data/Region.cpp \
    Data/TimeDef.cpp \
    Data/TimeMod.cpp \
    Data/UnitMapper.cpp \
    Data/ValueMapper.cpp \
    Filter/Filter.cpp \
    Filter/FilterFactory.cpp \
    Filter/FilterMapper.cpp \
    Filter/FilterNone.cpp \
    Main/Init.cpp \
    Main/Main.cpp \
    Model/IsotropicBallModel.cpp \
    Model/IsotropicSphereModel.cpp \
    Model/Model.cpp \
    Model/ModelFactory.cpp \
    Model/ModelMapper.cpp \
    Tools/ConvertSpaceTime.cpp \
    Tools/NameMapper.cpp \
    Tools/Parser.cpp \
    Model/ModelCmdMapper.cpp


