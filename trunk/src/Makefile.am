## Process this file with automake to produce Makefile.in

## Created by Anjuta

gladedir = $(datadir)/laex/glade
glade_DATA = laex.glade

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(LAEX_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = laex

laex_SOURCES = \
	main.c\
	main_window.c \
	main_window.h \
	centry.c \
	centry.h \
	cstrman.c \
	cstrman.h \
	data.c \
	data.h \
	word_preview.c \
	word_preview.h \
	select_words.h \
	select_words.c \
	dialog_edit_entry.c \
	dialog_edit_entry.h \
	statistics.h \
	statistics.c \
	word_practise.c \
	word_practise.h

laex_LDFLAGS = \
	-Wl,--export-dynamic

laex_LDADD = $(LAEX_LIBS)

EXTRA_DIST = $(glade_DATA)
