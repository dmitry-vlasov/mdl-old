SUBDIRS = \
	ast \
	auxiliary \
	cut \
	expression \
	interface \
	lexer \
	math \
	parser \
	types

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	\
	-I$(top_srcdir)/src/nstd \
	-I$(top_srcdir)/src/nsgl \
	-I$(top_srcdir)/src/mm
	
noinst_HEADERS = \
	mm_Mm.hpp \
	mm_Mm.cpp \
	\
	mm.dpp \
	mm.hpp \
	mm.cpp
	
bin_PROGRAMS = \
	mm

mm_SOURCES = \
	mm_main.cpp
