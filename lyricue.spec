# $Revision: 1.7 $, $Date: 2008/10/03 02:18:22 $
Summary:	The GNU Lyric Display System
Name:		lyricue
Version:	1.9.8
Release:	0.9
License:	GPL
Group:		X11/Applications/Graphics
URL:		http://www.adebenham.com/lyricue/
Source0:	http://www.adebenham.com/debian/%{name}_%{version}.tar.gz
Patch0:		%{name}-makefile.patch
Patch1:		%{name}-desktop.patch
Requires:	mysql-client
Requires:	perl-DBD-mysql
Requires:	perl-DBI
Requires:	perl-Gnome2-Canvas
Requires:	perl-Gtk2-GladeXML
Requires:	perl-Gtk2-Spell
Requires:	perl-URI
Suggests:	perl-Gtk2-TrayIcon
Suggests:	perl-Locale-gettext
Suggests:	sword-devel
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
This application is used to edit/display song lyrics and passages of
text on a second screen/projector for use at live events such as
church services, concerts and seminars.

%prep
%setup -q
%patch0
%patch1

%build
%{__make}

%install
rm -rf $RPM_BUILD_ROOT
%{make} install \
	DESTDIR=$RPM_BUILD_ROOT

mv $RPM_BUILD_ROOT%{_datadir}/locale/es{_ES,}

%{find_lang} %{name}

rm -rf $RPM_BUILD_ROOT%{_datadir}/docs/%{name}

%clean
rm -rf $RPM_BUILD_ROOT

%files -f %{name}.lang
%defattr(644,root,root,755)
%dir %{_sysconfdir}/lyricue
%config(noreplace) %{_sysconfdir}/lyricue/*
%attr(755,root,root) %{_bindir}/*
%dir %{_datadir}/lyricue
%{_datadir}/lyricue/*
%doc docs/*
%{_desktopdir}/lyricue.desktop
%{_desktopdir}/lyricue_server.desktop

%define date	%(echo `LC_ALL="C" date +"%a %b %d %Y"`)
%changelog
* %{date} Lyricue Team <lds-devel@lists.sourceforge.net>
All persons listed below can be reached at lds-devel@lists.sourceforge.net

$Log: lyricue.spec,v $
Revision 1.7  2008/10/03 02:18:22  cjdebenh
Update for 1.9.8 release

Revision 1.6  2007/11/12 03:40:57  cjdebenh
Import spec file from Caleb Maclennan

