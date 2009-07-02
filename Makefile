BINARIES = lyricue lyricue_remote lyricue_server import_media
SHARE = lyricue.glade images/lyricue.png images/lyricue-icon.png
SQL = mysql/Create_lyricDb.sql mysql/Create_mediaDb.sql mysql/Update_1.2.sql mysql/Update_1.9.sql mysql/Update_1.9.4.sql mysql/Update_1.9.7.sql
DESKTOP = lyricue.desktop lyricue_server.desktop
ETC = default.conf access.conf.example
DOCS = docs/Development.txt docs/example_song.txt docs/AUTHORS docs/NEWS docs/README docs/song_template.txt docs/TODO
INSTALL = /usr/bin/install -c -m 755
INSTALLDATA = /usr/bin/install -c -m 644 -D
POFILES = po/de.po po/en_US.po po/fr.po po/nl.po po/sv.po po/es_ES.po
MOFILES = po/de.po.mo po/en_US.po.mo po/fr.po.mo po/nl.po.mo po/sv.po.mo po/es_ES.po.mo

all: $(MOFILES)

%.po.mo:
	@for t in $(POFILES); do msgfmt -o $$t.mo $$t;done

install: 
	mkdir -p $(DESTDIR)/usr/bin
	$(INSTALL) $(BINARIES) $(DESTDIR)/usr/bin

	mkdir -p $(DESTDIR)/usr/share/lyricue
	$(INSTALLDATA) $(SHARE) $(DESTDIR)/usr/share/lyricue

	mkdir -p $(DESTDIR)/usr/share/lyricue/mysql
	$(INSTALLDATA) $(SQL) $(DESTDIR)/usr/share/lyricue/mysql

	mkdir -p $(DESTDIR)/etc/lyricue
	$(INSTALLDATA) $(ETC) $(DESTDIR)/etc/lyricue

	mkdir -p $(DESTDIR)/usr/share/applications
	$(INSTALLDATA) $(DESKTOP) $(DESTDIR)/usr/share/applications

	mkdir -p $(DESTDIR)/usr/share/doc/lyricue
	$(INSTALLDATA) $(DOCS) $(DESTDIR)/usr/share/doc/lyricue

	@for t in $(MOFILES); do l=`basename $$t .po.mo`; $(INSTALLDATA) $$t $(DESTDIR)/usr/share/locale/$$l/LC_MESSAGES/lyricue.mo;done

uninstall:
	cd $(DESTDIR)/usr/bin; \
	rm $(BINARIES)
	cd $(DESTDIR)/usr/share/lyricue; \
	rm $(SHARE) $(SQL)
	cd $(DESTDIR)/usr/share/applications; \
	rm $(DESKTOP)

clean:
	rm $(MOFILES)
