SUBDIRS = \
	auxiliary \
	console \
	expression \
	form \
	interface \
	lexer \
	math \
	parser \
	prover \
	refactor \
	study \
	types

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/nstd \
	-I$(top_srcdir)/src/nsgl

bin_PROGRAMS = \
	mdl

noinst_HEADERS = \
	mdl_Engine.hpp \
	mdl_macro.hpp \
	\
	mdl_Engine.cpp \
	\
	mdl.dpp \
	mdl.hpp \
	mdl.cpp

mdl_SOURCES = \
	mdl_main.cpp
