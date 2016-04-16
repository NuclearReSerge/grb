TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET  = grb_ut

DEFINES += GRB_VERSION="0.1"

QMAKE_CXXFLAGS += -std=c++11 -O0 -Wextra -Werror -Wpedantic

QMAKE_LFLAGS = -g

QMAKE_LIBS = -lgtest -pthread

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
    Tools/Parser.h

SOURCES += \
    Analyzer/Init.cpp \
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
    Tools/Parser.cpp

HEADERS += \
    test/Mock/CatalogEntryMock.h \
    test/Mock/CatalogMock.h \
    test/Mock/DataBaseFormatMock.h \
    test/Mock/NameMapperCommon.h \
    test/Mock/NameMapperMock.h

SOURCES += \
    test/Mock/CatalogEntryMock.cpp \
    test/Mock/CatalogMock.cpp \
    test/Mock/DataBaseFormatMock.cpp \
    test/Mock/NameMapperCommon.cpp \
    test/Mock/NameMapperMock.cpp

SOURCES += \
    test/UnitTests.cpp

SOURCES += \
    test/UnitTest/Common/test/ExceptionTest.cpp \
    test/UnitTest/Common/test/SingletonTest.cpp \
    test/UnitTest/Data/test/ObservatoryTest.cpp \
    test/UnitTest/Data/test/ReferenceTest.cpp \
    test/UnitTest/Data/test/RegionTest.cpp \
    test/UnitTest/Data/test/TimeDefTest.cpp \
    test/UnitTest/Data/test/TimeModTest.cpp \
    test/UnitTest/Tools/test/NameMapperTest.cpp \
    test/UnitTest/Tools/test/ParserFileTest.cpp \
    test/UnitTest/Tools/test/ParserTest.cpp