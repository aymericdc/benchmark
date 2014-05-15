AM_CFLAGS = -I$(top_srcdir)/lib @AM_CFLAGS@
bin_PROGRAMS = writev
readdir_SOURCES = writev.c
readdir_LDADD = $(top_builddir)/lib/libbenchmark.a $(AM_LDFLAGS)

GRAPHS = writev.csv
PROG   = writev

include ../lib/lib.mk
