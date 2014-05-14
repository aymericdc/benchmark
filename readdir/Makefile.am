AM_CFLAGS = -I$(top_srcdir)/lib @AM_CFLAGS@
bin_PROGRAMS = readdir
types_SOURCES = readdir.c
types_LDADD = $(top_builddir)/lib/libbenchmark.a $(AM_LDFLAGS)

GRAPHS = readdir.csv
PROG   = readdir

include ../lib/lib.mk
