%define LIBNAME woml
Summary: woml library
Name: libsmartmet-%{LIBNAME}
Version: 12.6.1
Release: 1.el6.fmi
License: FMI
Group: Development/Libraries
URL: http://www.weatherproof.fi
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: boost-devel >= 1.49
BuildRequires: libsmartmet-macgyver >= 11.4.19-1
BuildRequires: libxml++-devel >= 2.20.0-1
BuildRequires: libsmartmet-regression >= 11.6.15-1
Requires: xqilla >= 2.2.3-8
Requires: xerces-c >= 3.0.1-20
Requires: cairo >= 1.8.8-3.1
Provides: %{LIBNAME}

%description
FMI WOML library

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n %{LIBNAME}
 
%build
make %{_smp_mflags}
make test

%install
%makeinstall includedir=%{buildroot}%{_includedir}/smartmet

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,0775)
%{_includedir}/smartmet/%{LIBNAME}
%{_libdir}/libsmartmet_%{LIBNAME}.a


%changelog
* Wed Aug  3 2011 Mika Heiskanen <mika.heiskanen@fmi.fi> - 11.8.3-1.el5.fmi
- Upgraded to boost 1.47
* Tue Aug  2 2011 Mika Heiskanen <mika.heiskanen@fmi.fi> - 11.8.2-1.el5.fmi
- Upgraded to use boost 1.46 API
* Wed Aug 18 2010 Mika Heiskanen <mika.heiskanen@fmi.fi> - 10.8.18-1.el5.fmi
- Added accessors required by the frontier program
* Tue Jun 15 2010 Mika Heiskanen <mika.heiskanen@fmi.fi> - 10.6.15-1.el5.fmi
- Initial build
