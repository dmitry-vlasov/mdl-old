SUBDIRS = \
	auxiliary \
	expression \
	interface \
	lexer \
	math \
	parser \
	source \
	types

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/nstd \
	-I$(top_srcdir)/src/nsgl

noinst_HEADERS = \
	smm_Smm.hpp \
	smm_Smm.cpp \
	\
	smm.dpp \
	smm.hpp \
	smm.cpp 

bin_PROGRAMS = \
	smm

smm_SOURCES = \
	smm_main.cpp
