lib_LTLIBRARIES = libmanygames_input.la
libmanygames_input_la_SOURCES = mouse_input.cpp
libmanygames_input_la_LDFLAGS = -module -shared -rpath @prefix@/lib
AM_CXXFLAGS = -I@top_srcdir@/include $(SIGC_CFLAGS)
LIBS _= $(SIGC_LIBS)
INCLUDES = -I@top_srcdir@/include