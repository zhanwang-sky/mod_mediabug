include $(top_srcdir)/build/modmake.rulesam
MODNAME=mod_mediabug

mod_LTLIBRARIES = mod_mediabug.la
mod_mediabug_la_SOURCES  = mod_mediabug.c
mod_mediabug_la_CFLAGS   = $(AM_CFLAGS)
mod_mediabug_la_LIBADD   = $(switch_builddir)/libfreeswitch.la
mod_mediabug_la_LDFLAGS  = -avoid-version -module -no-undefined -shared
