noinst_PROGRAMS = fb_test
fb_test_SOURCES = fb_test.cpp x_input_window.cpp x_input_window.hpp 
fb_test_LDADD = ../../graphics/libmanygames_graphics.la ../../input/libmanygames_input.la
AM_CXXFLAGS = -I@top_srcdir@/include $(X_INCLUDE_DIRS) $(SIGC_CFLAGS) -O9 
LIBS += $(X_LIBS) -lX11 $(SIGC_LIBS)
