xemmaidir = $(XEMMAI_MODULE_PATH)

xemmai_LTLIBRARIES = libxml.la
AM_CPPFLAGS = $(LIBXML_CFLAGS) $(XEMMAI_CFLAGS)
AM_CXXFLAGS = -std=c++11
AM_LDFLAGS = -module -avoid-version
if DEBUG
AM_CXXFLAGS += -g
else
AM_CPPFLAGS += -DNDEBUG
AM_CXXFLAGS += -O3
endif
if PROFILE
AM_CXXFLAGS += -pg
AM_LDFLAGS += -pg
endif
libxml_la_LIBADD = $(LIBXML_LIBS) $(XEMMAI_LIBS)
libxml_la_SOURCES = \
	reader.h \
	reader.cc \
	writer.h \
	writer.cc \
	io.h \
	io.cc \
	libxml.h \
	libxml.cc
