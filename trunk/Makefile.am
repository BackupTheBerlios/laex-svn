## Process this file with automake to produce Makefile.in


SUBDIRS = src po

laexdocdir = ${prefix}/doc/laex
laexdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS
	
laexdochtmldir = ${prefix}/doc/@PACKAGE@/html
laexdochtml_DATA = src/doc/main.html


laex_ui_filedir = "$(datadir)"/@PACKAGE@/ui
laex_ui_file_DATA = src/ui/main_window.ui \
                    src/ui/dialogEditEntry.ui \
                    src/ui/assistant_import.ui \
                    src/ui/assistant_export.ui \
                    src/ui/dialogStartTraining.ui

laex_pixmaps_filedir = "$(datadir)"/@PACKAGE@/pixmaps
laex_pixmaps_file_DATA = src/icons/laex.png \
                         src/icons/laex_small.png \
                         src/icons/laex.svg
                    
gnomemenudir = $(datadir)/applications
gnomemenu_DATA = laex.desktop

menu_icon_DATA = \
	src/icons/laex.png

menu_icondir = \
	$(datadir)/pixmaps

EXTRA_DIST = $(laexdoc_DATA) $(laexdochtml_DATA) $(laex_ui_file_DATA) $(laex_pixmaps_file_DATA) $(gnomemenu_DATA) \
        src/win32.zip

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

