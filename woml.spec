%define LIBNAME woml
Summary: woml library
Name: libsmartmet-%{LIBNAME}
Version: 15.6.17
Release: 1%{?dist}.fmi
License: FMI
Group: Development/Libraries
URL: http://www.weatherproof.fi
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: boost-devel >= 1.55.0
BuildRequires: libsmartmet-macgyver-devel >= 15.5.19
BuildRequires: libxml++-devel
BuildRequires: libsmartmet-regression >= 11.6.15
Requires: libsmartmet-macgyver >= 15.5.19
Requires: xqilla
Requires: xerces-c
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
%defattr(0775,root,root,-)
%{_includedir}/smartmet/%{LIBNAME}
%{_libdir}/libsmartmet_%{LIBNAME}.a


%changelog
* Wed Jun 17 2015 Mikko Visa <mikko.visa@fmi.fi> - 15.6.17-1.fmi
- Heiskanen: removed dependency on explicit xqilla version to support multiple RHEL versions
- Heiskanen: removed dependency on explicit libxml++ version to support multiple RHEL versions
- Kinniä: updated some failing test input files
- Heiskanen: ported to RHEL 7
- Heiskanen: Using dynamic linkage from now on
* Tue Mar 31 2015 Mika Heiskanen <mika.heiskanen@fmi.fi> - 15.3.30-1.fmi
- Use dynamic linking of smartmet libraries
- MIRWA-1070
* Thu Jan 15 2015 Mikko Visa <mikko.visa@fmi.fi> - 15.1.15-1.fmi
- Rebuild for RHEL7
* Wed Nov 19 2014 Mikko Visa <mikko.visa@fmi.fi> - 14.11.19-1.fmi
- MIRWA-894; loading component info text for surfaces
- LENTOSAA-743; loading multiple values (categories) for migratoryBirds
- MIRWA-894; loading component info text for ParameterValueSetPoint and PointMeteorologicalSymbol objects too
- MIRWA-894; loading component info text
- MIRWA-933; 03_AltocumulusCloud_3_5 not appearing on map
- MIRWA-892; added parsing for ParameterValueSetArea
- LENTOSAA-881; Turbulence output
- added getter for document creator
- added storage for labeling information
* Thu Nov 28 2013 Mikko Visa <mikko.visa@fmi.fi> - 13.11.28-1.fmi
- Modifications to support elevation hole handling in frontier
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
