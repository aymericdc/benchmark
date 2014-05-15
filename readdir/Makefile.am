AM_CFLAGS = -I$(top_srcdir)/lib @AM_CFLAGS@
bin_PROGRAMS = readdir
readdir_SOURCES = readdir.c
readdir_LDADD = $(top_builddir)/lib/libbenchmark.a $(AM_LDFLAGS)
TMP = -r temp

GRAPHS = readdir.csv
PROG   = readdir

include ../lib/lib.mk
