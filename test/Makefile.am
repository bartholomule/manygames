EXTRA_DIST = do_all_tests.sh testinclude.hpp
noinst_PROGRAMS = test_raster test_rgbcolor test_rgbacolor
test_raster_SOURCES = test_raster.cpp
test_rgbcolor_SOURCES = test_rgbcolor.cpp
test_rgbacolor_SOURCES = test_rgbacolor.cpp
INCLUDES=-I@top_srcdir@/include
# Turn off optimizations, so that these tests will actually execute.
AM_CXXFLAGS:=-O0 -ggdb