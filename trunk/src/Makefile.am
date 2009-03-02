## Process this file with automake to produce Makefile.in



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_PREFIX_DIR=\""$(prefix)"\" \
	$(LAEX_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g\
	 -O3
	 
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
	word_practise.h \
	dialog_messages.h \
	dialog_messages.c \
	assistant_import.h \
	assistant_import.c \
	assistant_export.h \
	assistant_export.c \
	ck_diagramm.h \
	ck_diagramm.c

laex_LDFLAGS = \
	-Wl,--export-dynamic

laex_LDADD = $(LAEX_LIBS)
