%define LIBNAME woml
Summary: woml library
Name: libsmartmet-%{LIBNAME}
Version: 13.7.3
Release: 1%{?dist}.fmi
License: FMI
Group: Development/Libraries
URL: http://www.weatherproof.fi
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: boost-devel >= 1.54
BuildRequires: libsmartmet-macgyver >= 13.7.3
BuildRequires: libxml++-devel >= 2.30.0-1
BuildRequires: libsmartmet-regression >= 11.6.15-1
Requires: xqilla >= 2.2.3-8
Requires: xerces-c >= 3.0.1
Provides: %{LIBNAME}

%description
FMI WOML library

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n %{LIBNAME}
 
%build
make %{_smp_mflags}
# make test

%install
%makeinstall includedir=%{buildroot}%{_includedir}/smartmet

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,0775)
%{_includedir}/smartmet/%{LIBNAME}
%{_libdir}/libsmartmet_%{LIBNAME}.a


%changelog
* Wed Jul  3 2013 Mika Heiskanen <mika.heiskanen@fmi.fi> - 13.7.3-1.fmi
- Update to boost 1.54
* Fri Jan 11 2013 Mikko Visa <mikko.visa@fmi.fi> - 13.1.11-1.fmi
- RPM building now uses a user specific rpmbuild directory
- Fixed automatic detection for tar --exclude-cvs option to speed up rpm building
- Misc additions, changes and bug fixes
* Tue Aug  7 2012 Mika Heiskanen <mika.heiskanen@fmi.fi> - 12.8.7-1.fmi
- RHEL6 release
* Fri Jun  1 2012 Mikko Visa <mikko.visa@fmi.fi> - 12.6.1-1.fmi
- First version supporting WOML schema instead of metobjects schema.
* Wed Aug  3 2011 Mika Heiskanen <mika.heiskanen@fmi.fi> - 11.8.3-1.fmi
- Upgraded to boost 1.47
* Tue Aug  2 2011 Mika Heiskanen <mika.heiskanen@fmi.fi> - 11.8.2-1.fmi
- Upgraded to use boost 1.46 API
* Wed Aug 18 2010 Mika Heiskanen <mika.heiskanen@fmi.fi> - 10.8.18-1.fmi
- Added accessors required by the frontier program
* Tue Jun 15 2010 Mika Heiskanen <mika.heiskanen@fmi.fi> - 10.6.15-1.fmi
- Initial build
