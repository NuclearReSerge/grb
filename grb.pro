TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET  = grb

DEFINES += GRB_VERSION="0.2"
# DEFINES += INCLUDE_FUNCTION_IN_EXC

QMAKE_CXXFLAGS += -std=c++11 -O0 -Wextra -Werror -Wpedantic

QMAKE_LFLAGS = -g

QMAKE_LIBS =

HEADERS += \
    Analyzer/Analyzer.h \
    Analyzer/AnalyzerCmdMapper.h \
    Analyzer/AnalyzerCmdType.h \
    Analyzer/AnalyzerFactory.h \
    Analyzer/AnalyzerGrbcat.h \
    Analyzer/AnalyzerMapper.h \
    Analyzer/AnalyzerType.h \
    CLI/Cmd.h \
    CLI/CmdAnalyzer.h \
    CLI/CmdCorrelation.h \
    CLI/CmdDatabase.h \
    CLI/CmdFilter.h \
    CLI/CmdHelp.h \
    CLI/CmdModel.h \
    CLI/CmdQuit.h \
    CLI/CommandFactory.h \
    CLI/CommandLine.h \
    CLI/CommandMapper.h \
    CLI/CommandType.h \
    Common/Exception.h \
    Common/Factory.h \
    Common/Global.h \
    Common/Mapper.h \
    Common/Singleton.h \
    Common/trace.h \
    Correlation/ArcFormulaMapper.h \
    Correlation/ArcFormulaType.h \
    Correlation/Correlation.h \
    Correlation/CorrelationFactory.h \
    Correlation/CorrelationMapper.h \
    Correlation/CorrelationTimeArcGrbcat.h \
    Correlation/CorrelationType.h \
    Correlation/GreatCircleDistance.h \
    Data/Catalog.h \
    Data/CatalogEntry.h \
    Data/CatalogEntryFactory.h \
    Data/CatalogEntryGrbcat.h \
    Data/CatalogEntryMapper.h \
    Data/CatalogEntryType.h \
    Data/ColumnMapper.h \
    Data/ColumnType.h \
    Data/Coordinates.h \
    Data/CoordinateStructures.h \
    Data/CoordinateSystemMapper.h \
    Data/CoordinateSystemType.h \
    Data/DataBaseColumn.h \
    Data/DataBaseFormat.h \
    Data/DataBaseFormatFactory.h \
    Data/DataBaseFormatGrbcat.h \
    Data/DataBaseFormatMapper.h \
    Data/DataBaseFormatType.h \
    Data/DateMapper.h \
    Data/DateType.h \
    Data/Duration.h \
    Data/ObservatoryMapper.h \
    Data/ReferenceMapper.h \
    Data/RegionMapper.h \
    Data/TimeDefMapper.h \
    Data/TimeModMapper.h \
    Data/UnitMapper.h \
    Data/UnitType.h \
    Data/ValueMapper.h \
    Data/ValueType.h \
    Filter/Filter.h \
    Filter/FilterFactory.h \
    Filter/FilterMapper.h \
    Filter/FilterNone.h \
    Filter/FilterType.h \
    Main/AnalysisData.h \
    Model/IsotropicBallModel.h \
    Model/IsotropicSphereModel.h \
    Model/Model.h \
    Model/ModelCmdMapper.h \
    Model/ModelCmdType.h \
    Model/ModelFactory.h \
    Model/ModelMapper.h \
    Model/ModelType.h \
    Tools/ConvertSpaceTime.h \
    Tools/NameMapper.h \
    Tools/Parser.h

SOURCES += \
    Analyzer/Analyzer.cpp \
    Analyzer/AnalyzerCmdMapper.cpp \
    Analyzer/AnalyzerFactory.cpp \
    Analyzer/AnalyzerGrbcat.cpp \
    Analyzer/AnalyzerMapper.cpp \
    CLI/Cmd.cpp \
    CLI/CmdAnalyzer.cpp \
    CLI/CmdCorrelation.cpp \
    CLI/CmdDatabase.cpp \
    CLI/CmdFilter.cpp \
    CLI/CmdHelp.cpp \
    CLI/CmdModel.cpp \
    CLI/CmdQuit.cpp \
    CLI/CommandFactory.cpp \
    CLI/CommandLine.cpp \
    CLI/CommandMapper.cpp \
    Common/Exception.cpp \
    Correlation/ArcFormulaMapper.cpp \
    Correlation/CorrelationFactory.cpp \
    Correlation/CorrelationMapper.cpp \
    Correlation/CorrelationTimeArcGrbcat.cpp \
    Correlation/GreatCircleDistance.cpp \
    Data/Catalog.cpp \
    Data/CatalogEntryFactory.cpp \
    Data/CatalogEntryGrbcat.cpp \
    Data/CatalogEntryMapper.cpp \
    Data/ColumnMapper.cpp \
    Data/Coordinates.cpp \
    Data/CoordinateSystemMapper.cpp \
    Data/DataBaseFormatFactory.cpp \
    Data/DataBaseFormatGrbcat.cpp \
    Data/DataBaseFormatMapper.cpp \
    Data/DateMapper.cpp \
    Data/Duration.cpp \
    Data/ObservatoryMapper.cpp \
    Data/ReferenceMapper.cpp \
    Data/RegionMapper.cpp \
    Data/TimeDefMapper.cpp \
    Data/TimeModMapper.cpp \
    Data/UnitMapper.cpp \
    Data/ValueMapper.cpp \
    Filter/FilterFactory.cpp \
    Filter/FilterMapper.cpp \
    Filter/FilterNone.cpp \
    Main/AnalysisData.cpp \
    Main/Init.cpp \
    Main/Main.cpp \
    Model/IsotropicBallModel.cpp \
    Model/IsotropicSphereModel.cpp \
    Model/ModelCmdMapper.cpp \
    Model/ModelFactory.cpp \
    Model/ModelMapper.cpp \
    Tools/ConvertSpaceTime.cpp \
    Tools/NameMapper.cpp \
    Tools/Parser.cpp
