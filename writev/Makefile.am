AM_CFLAGS = -I$(top_srcdir)/lib @AM_CFLAGS@
bin_PROGRAMS = writev
writev_SOURCES = writev.c
writev_LDADD = $(top_builddir)/lib/libbenchmark.a $(AM_LDFLAGS)
TMP= writeV.txt writelseek.txt

GRAPHS = writev.csv writelseek.csv
PROG   = writev

include ../lib/lib.mk
