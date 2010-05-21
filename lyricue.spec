# $Revision: 1.12 $, $Date: 2010/03/14 10:18:19 $
# TODO:
# - Make sure server subpackage can run without the client

%include    /usr/lib/rpm/macros.perl

Summary:	GNU Lyric Display System, client interface
Name:		lyricue
Version:	2.0.0
Release:	0.11
License:	GPL
Group:		X11/Applications/Graphics
Source0:	http://www.adebenham.com/debian/%{name}_%{version}.tar.gz
# Source0-md5:	cd0fb1c9b0e6ccadc52cda2601b86be6
URL:		http://www.lyricue.org
BuildRequires:	gettext-devel
BuildRequires:	rpm-perlprov
BuildRequires:	sed >= 4.0
Requires:	mysql-client
Requires:	perl-DBD-mysql
Requires:	perl-DBI
Requires:	perl-Gtk2-GladeXML
Requires:	perl-Gtk2-Spell
Requires:	perl-URI
Suggests:	%{name}-server
Suggests:	%{name}-remote
Suggests:	diatheke
Suggests:	mysql
Suggests:	perl(Clutter)
Suggests:	perl(DBD::mysql)
Suggests:	perl(Gtk2::TrayIcon)
Suggests:	unoconv
BuildArch:	noarch
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
Lyricue is used to edit and display song lyrics and passages of text
along with images and videos on a second screen/projector. It was
designed for use at live events such as church services, concerts and
seminars.

%package server
Summary:	GNU Lyric Display System, server interface
Group:		X11/Applications/Graphics
Suggests:	perl(Clutter)
Suggests:	perl(DBD::mysql)
Suggests:	perl(Locale::gettext)

%description server
Component to handle action display and projection of slides.

%package remote
Summary:	GNU Lyric Display System, remote control cli
Group:	Libraries

%description remote
Remote control CLI to control the projection server from any shell.

%prep
%setup -q
sed -e 's#po/es_ES#po/es#' -i Makefile
mv po/es{_ES,}.po

%build
%{__make}

%install
rm -rf $RPM_BUILD_ROOT
%{make} install \
	DESTDIR=$RPM_BUILD_ROOT

mv $RPM_BUILD_ROOT/%{_sysconfdir}/%{name}/access.conf{.example,}

%find_lang %{name}

rm -rf $RPM_BUILD_ROOT%{_datadir}/docs/%{name}

%clean
rm -rf $RPM_BUILD_ROOT

%files -f %{name}.lang
%defattr(644,root,root,755)
%doc docs/*
%dir %{_sysconfdir}/%{name}
%config(noreplace) %{_sysconfdir}/%{name}/*.conf
%attr(755,root,root) %{_bindir}/%{name}
%attr(755,root,root) %{_bindir}/import_media
%dir %{_datadir}/%{name}
%{_datadir}/%{name}/*
%{_desktopdir}/%{name}.desktop

%files server
%defattr(644,root,root,755)
%attr(755,root,root) %{_bindir}/%{name}_server
%{_desktopdir}/%{name}_server.desktop

%files remote
%defattr(644,root,root,755)
%attr(755,root,root) %{_bindir}/%{name}_remote

%define date	%(echo `LC_ALL="C" date +"%a %b %d %Y"`)
%changelog
* %{date} Lyricue Team <lds-devel@lists.sourceforge.net>
All persons listed below can be reached at lds-devel@lists.sourceforge.net

$Log: lyricue.spec,v $
Revision 1.12  2010/03/14 10:18:19  cjdebenh
Remove GnomeCanvas Support and fix OSD with clutter 0.8

Revision 1.11  2009/07/30 04:19:51  cjdebenh
Move website references to lyricue.org

Revision 1.10  2009/06/16 23:05:08  cjdebenh
Better error reporting, handle locales better for preferences dialog and work on import db stuff

Revision 1.9  2009/06/10 04:58:21  cjdebenh
Move to 2.0.0

Revision 1.9  2009/06/10 04:27:52  cjdebenh
Update numbering to 2.0.0

Revision 1.8  2009/04/22 04:27:52  cjdebenh
Update numbering to 1.9.9

Revision 1.8  2009/22/04 02:18:22  cjdebenh
Update for 1.9.9 release

Revision 1.7  2008/10/03 02:18:22  cjdebenh
Update for 1.9.8 release

Revision 1.6  2007/11/12 03:40:57  cjdebenh
Import spec file from Caleb Maclennan

