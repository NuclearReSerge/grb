TEMPLATE = app
CONFIG  -= app_bundle
CONFIG  -= qt
CONFIG  -= debug
CONFIG  += console
CONFIG  += release
CONFIG  += thread
TARGET   = grb_ut

DEFINES += \
    GRB_VERSION="0.2" \
    TEST_PRINT_EXC \

QMAKE_CXXFLAGS = \
    -std=c++11 \
    -O0 \
    -Wextra \
    -Werror \
    -Wpedantic \
    -fPIC \
    -fprofile-arcs -ftest-coverage --coverage \

QMAKE_LFLAGS = \
    -g \

QMAKE_LIBS = \
    -lgtest -lgmock \
    -pthread \
    -fprofile-arcs --coverage \

#make -j4 && ./grb_ut && lcov --no-external --capture -d . -d ../../grb -o coverage.info && genhtml coverage.info --output-directory out

HEADERS_UT_MOCK += \
    test/Mock/AnalyzerMock.h \
    test/Mock/CatalogEntryMock.h \
    test/Mock/CatalogMock.h \
    test/Mock/CmdMock.h \
    test/Mock/CoordinatesMock.h \
    test/Mock/CorrelationMock.h \
    test/Mock/DatabaseMock.h \
    test/Mock/FactoryMock.h \
    test/Mock/FactoryTestFixtures.h \
    test/Mock/FilterMock.h \
    test/Mock/MapperMock.h \
    test/Mock/MapperTestFixtures.h \
    test/Mock/ModelMock.h \
    test/Mock/MockHelper.h \
    test/Mock/NameMapperMock.h \
    test/Mock/NameMapperTestFixtures.h \
    test/Mock/ParserMock.h \

#HEADERS += \
#    test/UnitTest/Data/test/CatalogEntryMockSample.h

SOURCES_UT_MOCK += \
    test/Mock/MockHelper.cpp \

SOURCES_UT_ANALYSER += \
    test/UnitTest/Analyzer/test/AnalyzerCmdMapperTest.cpp \
    test/UnitTest/Analyzer/test/AnalyzerFactoryTest.cpp \
    test/UnitTest/Analyzer/test/AnalyzerGrbcatTest.cpp \
    test/UnitTest/Analyzer/test/AnalyzerMapperTest.cpp \
    test/UnitTest/Analyzer/test/AnalyzerTest.cpp \

SOURCES_UT_CATALOG += \
    test/UnitTest/Catalog/test/CatalogEntryFactoryTest.cpp \
    test/UnitTest/Catalog/test/CatalogEntryGrbcatTest.cpp \
    test/UnitTest/Catalog/test/CatalogEntryMapperTest.cpp \
    test/UnitTest/Catalog/test/CatalogEntryTest.cpp \
    test/UnitTest/Catalog/test/CatalogTest.cpp \
    test/UnitTest/Catalog/test/CoordinatesTest.cpp \
    test/UnitTest/Catalog/test/DurationTest.cpp \

SOURCES_UT_CLI += \
    test/UnitTest/CLI/test/CmdAnalyzerTest.cpp \
    test/UnitTest/CLI/test/CmdCorrelationTest.cpp \
    test/UnitTest/CLI/test/CmdDatabaseTest.cpp \
    test/UnitTest/CLI/test/CmdFilterTest.cpp \
    test/UnitTest/CLI/test/CmdHelpTest.cpp \
    test/UnitTest/CLI/test/CmdModelTest.cpp \
    test/UnitTest/CLI/test/CmdQuitTest.cpp \
    test/UnitTest/CLI/test/CmdTest.cpp \
    test/UnitTest/CLI/test/CommandFactoryTest.cpp \
    test/UnitTest/CLI/test/CommandLineTest.cpp \
    test/UnitTest/CLI/test/CommandMapperTest.cpp \

SOURCES_UT_COMMON += \
    test/UnitTest/Common/test/ExceptionTest.cpp \
    test/UnitTest/Common/test/FactoryTest.cpp \
    test/UnitTest/Common/test/MapperTest.cpp \
    test/UnitTest/Common/test/SingletonTest.cpp \

SOURCES_UT_CORRELATION += \
    test/UnitTest/Correlation/test/ArcFormulaMapperTest.cpp \
    test/UnitTest/Correlation/test/CorrelationFactoryTest.cpp \
    test/UnitTest/Correlation/test/CorrelationMapperTest.cpp \
    test/UnitTest/Correlation/test/CorrelationTest.cpp \
    test/UnitTest/Correlation/test/CorrelationTimeArcGrbcatTest.cpp \
    test/UnitTest/Correlation/test/GreatCircleDistanceTest.cpp \

SOURCES_UT_DATA += \
    test/UnitTest/Data/test/CoordinateSystemMapperTest.cpp \
    test/UnitTest/Data/test/DateMapperTest.cpp \
    test/UnitTest/Data/test/ObservatoryMapperTest.cpp \
    test/UnitTest/Data/test/ReferenceMapperTest.cpp \
    test/UnitTest/Data/test/RegionMapperTest.cpp \
    test/UnitTest/Data/test/TimeDefMapperTest.cpp \
    test/UnitTest/Data/test/TimeModMapperTest.cpp \
    test/UnitTest/Data/test/UnitMapperTest.cpp \
    test/UnitTest/Data/test/ValueMapperTest.cpp \

SOURCES_UT_DATABASE += \
    test/UnitTest/Database/test/DatabaseColumnTest.cpp \
    test/UnitTest/Database/test/DatabaseFactoryTest.cpp \
    test/UnitTest/Database/test/DatabaseGrbcatTest.cpp \
    test/UnitTest/Database/test/DatabaseMapperTest.cpp \
    test/UnitTest/Database/test/DatabaseTest.cpp \

SOURCES_UT_FILTER += \
    test/UnitTest/Filter/test/FilterFactoryTest.cpp \
    test/UnitTest/Filter/test/FilterMapperTest.cpp \
    test/UnitTest/Filter/test/FilterNoneTest.cpp \

SOURCES_UT_MAIN += \
    test/UnitTest/Main/test/AnalysisDataTest.cpp \
    test/UnitTest/Main/test/InitTest.cpp \

SOURCES_UT_MODEL += \
    test/UnitTest/Model/test/IsotropicBallModelTest.cpp \
    test/UnitTest/Model/test/IsotropicSphereModelTest.cpp \
    test/UnitTest/Model/test/ModelCmdMapperTest.cpp \
    test/UnitTest/Model/test/ModelFactoryTest.cpp \
    test/UnitTest/Model/test/ModelMapperTest.cpp \
    test/UnitTest/Model/test/ModelTest.cpp \

SOURCES_UT_TOOLS += \
    test/UnitTest/Tools/test/ConvertSpaceTimeTest.cpp \
    test/UnitTest/Tools/test/NameMapperTest.cpp \
    test/UnitTest/Tools/test/ParserDatabaseTest.cpp \
#    test/UnitTest/Tools/test/ParserFileTest.cpp \
    test/UnitTest/Tools/test/ParserTest.cpp \
    test/UnitTest/Tools/test/SyntaxVerifierTest.cpp \

SOURCES += \
    test/UnitTests.cpp \
    $${SOURCES_UT_MOCK} \
                                    #   +---------------------------+---------------------------+
                                    #   |   Line Coverage           |   Functions               |
                                    #   +---------------------------+---------------------------+
    $${SOURCES_UT_ANALYSER} \       #   | 100.0 %        194 /  194 |  95.5 %         42 /   44 |
    $${SOURCES_UT_CATALOG} \        #   |                           |                           |
    $${SOURCES_UT_CLI} \            #   | 100.0 %        516 /  516 |  98.1 %        104 /  106 |
    $${SOURCES_UT_COMMON} \         #   |  94.0 %         63 /   67 |  19.9 %         33 /  166 |
    $${SOURCES_UT_CORRELATION} \    #   |  40.5 %         87 /  215 |  71.1 %         32 /   45 |
    $${SOURCES_UT_DATA} \           #   |  91.3 %        432 /  473 |  86.8 %        203 /  234 |
    $${SOURCES_UT_DATABASE} \       #   |                           |                           |
    $${SOURCES_UT_FILTER} \         #   | 100.0 %         24 /   24 |  89.5 %         17 /   19 |
    $${SOURCES_UT_MAIN} \           #   | 100.0 %         52 /   52 | 100.0 %         17 /   17 |
    $${SOURCES_UT_MODEL} \          #   |  97.4 %        191 /  196 |  96.5 %         55 /   57 |
    $${SOURCES_UT_TOOLS} \          #   |  99.4 %        350 /  352 |  92.7 %         38 /   41 |
                                    #   +---------------------------+---------------------------+

HEADERS += \
    $${HEADERS_UT_MOCK} \

HEADERS += \
    Analyzer/Analyzer.h \
    Analyzer/AnalyzerCmdType.h \
    Analyzer/AnalyzerCmdMapper.h \
    Analyzer/AnalyzerFactory.h \
    Analyzer/AnalyzerGrbcat.h \
    Analyzer/AnalyzerMapper.h \
    Analyzer/AnalyzerType.h \
    Catalog/Catalog.h \
    Catalog/CatalogEntry.h \
    Catalog/CatalogEntryFactory.h \
    Catalog/CatalogEntryGrbcat.h \
    Catalog/CatalogEntryMapper.h \
    Catalog/CatalogType.h \
    Catalog/Coordinates.h \
    Catalog/CoordinateStructures.h \
    Catalog/Duration.h \
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
    Common/BaseObject.h \
    Common/Exception.h \
    Common/Factory.h \
    Common/Global.h \
    Common/Mapper.h \
    Common/Singleton.h \
    Common/trace.h \
    Correlation/ArcFormulaMapper.h \
    Correlation/ArcFormulaType.h \
    Correlation/Correlation.h \
    Correlation/CorrelationCmdMapper.h \
    Correlation/CorrelationCmdType.h \
    Correlation/CorrelationFactory.h \
    Correlation/CorrelationMapper.h \
    Correlation/CorrelationTimeArcGrbcat.h \
    Correlation/CorrelationType.h \
    Correlation/GreatCircleDistance.h \
    Data/ColumnMapper.h \
    Data/ColumnType.h \
    Data/CoordinateSystemMapper.h \
    Data/CoordinateSystemType.h \
    Data/DateMapper.h \
    Data/DateType.h \
    Data/ObservatoryMapper.h \
    Data/ReferenceMapper.h \
    Data/RegionMapper.h \
    Data/TimeDefMapper.h \
    Data/TimeModMapper.h \
    Data/UnitMapper.h \
    Data/UnitType.h \
    Data/ValueMapper.h \
    Data/ValueType.h \
    Database/DatabaseCmdMapper.h \
    Database/DatabaseCmdType.h \
    Database/DatabaseType.h \
    Database/Database.h \
    Database/DatabaseColumn.h \
    Database/DatabaseFactory.h \
    Database/DatabaseGrbcat.h \
    Database/DatabaseMapper.h \
    Filter/Filter.h \
    Filter/FilterCmdType.h \
    Filter/FilterCmdMapper.h \
    Filter/FilterFactory.h \
    Filter/FilterMapper.h \
    Filter/FilterNone.h \
    Filter/FilterType.h \
    Main/AnalysisData.h \
    Main/Init.h \
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
    Tools/Parser.h \
    Tools/ParserDatabase.h \
    Tools/SyntaxVerifier.h \

SOURCES += \
    Analyzer/AnalyzerCmdMapper.cpp \
    Analyzer/AnalyzerFactory.cpp \
    Analyzer/AnalyzerGrbcat.cpp \
    Analyzer/AnalyzerMapper.cpp \
    Catalog/Catalog.cpp \
    Catalog/CatalogEntryFactory.cpp \
    Catalog/CatalogEntryGrbcat.cpp \
    Catalog/CatalogEntryMapper.cpp \
    Catalog/Coordinates.cpp \
    Catalog/Duration.cpp \
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
    Correlation/CorrelationCmdMapper.cpp \
    Correlation/CorrelationFactory.cpp \
    Correlation/CorrelationMapper.cpp \
    Correlation/CorrelationTimeArcGrbcat.cpp \
    Correlation/GreatCircleDistance.cpp \
    Data/ColumnMapper.cpp \
    Data/CoordinateSystemMapper.cpp \
    Data/DateMapper.cpp \
    Data/ObservatoryMapper.cpp \
    Data/ReferenceMapper.cpp \
    Data/RegionMapper.cpp \
    Data/TimeDefMapper.cpp \
    Data/TimeModMapper.cpp \
    Data/UnitMapper.cpp \
    Data/ValueMapper.cpp \
    Database/DatabaseCmdMapper.cpp \
    Database/DatabaseFactory.cpp \
    Database/DatabaseGrbcat.cpp \
    Database/DatabaseMapper.cpp \
    Filter/FilterCmdMapper.cpp \
    Filter/FilterFactory.cpp \
    Filter/FilterMapper.cpp \
    Filter/FilterNone.cpp \
    Main/AnalysisData.cpp \
    Main/Init.cpp \
#    Main/Main.cpp \
    Model/IsotropicBallModel.cpp \
    Model/IsotropicSphereModel.cpp \
    Model/ModelCmdMapper.cpp \
    Model/ModelFactory.cpp \
    Model/ModelMapper.cpp \
    Tools/ConvertSpaceTime.cpp \
    Tools/NameMapper.cpp \
    Tools/ParserDatabase.cpp \
    Tools/SyntaxVerifier.cpp \
