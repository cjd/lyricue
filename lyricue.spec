%define name	lyricue
%define version	1.9.2cvs20041001
%define release	1mdk

Name:           %{name} 
Summary:        The GNU Lyric Display System
Version:        %{version} 
Release:        %{release} 
Source0:        http://www.adebenham.com/lyricue/download/%{name}-%{version}.tar.bz2 
URL:            http://www.adebenham.com/lyricue/
Group:          Graphics
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-buildroot 
License:        GPL
Requires:       perl-Gtk2-GladeXML, MySQL, perl-Gtk2-Spell, perl-Gnome2-Canvas
Packager:	Chris Debenham <chris@adebenham.com>

%description
This application is used to edit/display song lyrics on a second screen/project
or for use at singing events such as church services.

%prep 
%setup -q -a 0

%build 

%install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT
for DIR in usr/bin etc/lyricue usr/lib/lyricue usr/share/lyricue usr/share/lyricue/mysql usr/share/lyricue/images usr/share/lyricue/backgrounds usr/share/doc/lyricue usr/share/locale usr/share/locale/de usr/share/locale/en_GB usr/share/locale/en_US usr/share/application;do install -d $RPM_BUILD_ROOT/$DIR;done
./install -f $RPM_BUILD_ROOT -a root
install import_media $RPM_BUILD_ROOT/usr/bin
install install $RPM_BUILD_ROOT/usr/share/lyricue
install mysql/*.sql $RPM_BUILD_ROOT/usr/share/lyricue/mysql/
install debian/lyricue.desktop $RPM_BUILD_ROOT/usr/share/application
install debian/lyricue_server.desktop $RPM_BUILD_ROOT/usr/share/application

%clean 
rm -rf $RPM_BUILD_ROOT 

%files 
%defattr(-,root,root,0755) 
%doc /usr/share/doc/lyricue/*
%config(noreplace) /etc/lyricue/*
%lang(all) /usr/share/locale/*/LC_MESSAGES/lyricue.mo
%{_bindir}/lyricue
%{_bindir}/lyricue_server
%{_bindir}/import_media
%{_datadir}/lyricue/*
%{_datadir}/application/*

%post
cd /usr/share/lyricue
/usr/share/lyricue/install -d

%changelog 
* Thu Oct 07 2004 Chris Debenham <chris@adebenham.com> 1.9.2cvs20041001-1mdk
- initial rpm release
