%define DIRNAME woml
%define LIBNAME smartmet-%{DIRNAME}
%define SPECNAME smartmet-library-%{DIRNAME}
Summary: woml library
Name: %{SPECNAME}
Version: 25.2.18
Release: 1%{?dist}.fmi
License: MIT
Group: Development/Libraries
URL: https://github.com/fmidev/smartmet-library-woml
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%if 0%{?rhel} && 0%{rhel} < 9
%define smartmet_boost boost169
%else
%define smartmet_boost boost
%endif

BuildRequires: rpm-build
BuildRequires: gcc-c++
BuildRequires: make
BuildRequires: %{smartmet_boost}-devel
BuildRequires: smartmet-library-macgyver-devel >= 25.2.18
BuildRequires: xqilla-devel
Requires: smartmet-library-macgyver >= 25.2.18
Requires: xqilla
Requires: xerces-c
Provides: %{SPECNAME}
Obsoletes: libsmartmet-woml < 17.1.4
#TestRequires: %{smartmet_boost}-devel
#TestRequires: smartmet-library-macgyver-devel >= 25.2.18
#TestRequires: smartmet-library-regression
#TestRequires: gcc-c++
#TestRequires: xqilla-devel

%description
FMI WOML library

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n %{SPECNAME}
 
%build
make %{_smp_mflags}
# make test

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(0775,root,root,0775)
%{_libdir}/lib%{LIBNAME}.so
%defattr(0664,root,root,0775)
%{_includedir}/smartmet/%{DIRNAME}/*.h

%changelog
* Tue Feb 18 2025 Andris Pavēnis <andris.pavenis@fmi.fi> 25.2.18-1.fmi
- Update to gdal-3.10, geos-3.13 and proj-9.5

* Wed Aug  7 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.8.7-1.fmi
- Update to gdal-3.8, geos-3.12, proj-94 and fmt-11

* Mon Jul 22 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.7.22-1.fmi
- Replace BOOST_FOREACH and boost::array

* Fri Jul 12 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.7.12-1.fmi
- Replace many boost library types with C++ standard library ones

* Thu May 16 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.5.16-1.fmi
- Clean up boost date-time uses

* Mon May  6 2024 Andris Pavēnis <andris.pavenis@fmi.fi> 24.5.6-1.fmi
- Use Date library (https://github.com/HowardHinnant/date) instead of boost date_time

* Fri Feb 23 2024 Mika Heiskanen <mika.heiskanen@fmi.fi> 24.2.23-1.fmi
- Full repackaging

* Fri Jul 28 2023 Andris Pavēnis <andris.pavenis@fmi.fi> 23.7.28-1.fmi
- Repackage due to bulk ABI changes in macgyver/newbase/spine

* Fri Jun 17 2022 Andris Pavēnis <andris.pavenis@fmi.fi> 22.6.17-1.fmi
- Add support for RHEL9. Update libpqxx to 7.7.0 (rhel8+) and fmt to 8.1.1

* Mon May 23 2022 Mika Heiskanen <mika.heiskanen@fmi.fi> - 22.5.23-1.fmi
- Fixed so-file to be executable

* Thu May  6 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.5.6-1.fmi
- Repackaged due to NFmiAzimuthalArea ABI changes

* Thu Mar 25 2021 Pertti Kinnia <pertti.kinnia@fmi.fi> - 21.3.25-1.fmi
- CB clouds ('cloudLayersCB') are stored separately in woml; LENTOSAA-1155
- Removed obsolete libxml++-devel build dependency

* Thu Jan 14 2021 Mika Heiskanen <mika.heiskanen@fmi.fi> - 21.1.14-1.fmi
- Repackaged smartmet to resolve debuginfo issues

* Wed Sep 30 2020 Pertti Kinnia <pertti.kinnia@fmi.fi> - 20.9.30-1.fmi
- Added feature's class name to base class to render cloud layers first for better cloud label placement (no reserved areas yet exist); LENTOSAA-1143
- Removed obsolete smartmet-library-regression dependency

* Fri Aug 21 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.8.21-1.fmi
- Upgrade to fmt 6.2

* Sat Apr 18 2020 Mika Heiskanen <mika.heiskanen@fmi.fi> - 20.4.18-1.fmi
- Upgrade to Boost 1.69

* Fri Sep 27 2019 Mika Heiskanen <mika.heiskanen@fmi.fi> - 19.9.27-1.fmi
- Repackaged due to ABI changes in SmartMet libraries

* Thu Jul 26 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.7.26-1.fmi
- Prefer nullptr over NULL

* Sat Apr  7 2018 Mika Heiskanen <mika.heiskanen@fmi.fi> - 18.4.7-1.fmi
- Upgrade to boost 1.66

* Tue Oct  3 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.10.3-1.fmi
- Change to MIT license

* Mon Aug 28 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.8.28-1.fmi
- Upgrade to boost 1.65

* Wed Jan  4 2017 Mika Heiskanen <mika.heiskanen@fmi.fi> - 17.1.4-1.fmi
- Switched to FMI open source naming conventions
- In addition to missing text nodes ignoring empty gml:posList text nodes too. Fixes MIRRISERVER-561.

* Mon Aug 22 2016 Mikko Visa <mikko.visa@fmi.fi> - 16.8.22-1.fmi
- Ignoring empty cubic spline surfaces (e.g. SurfacePrecipitationArea) in strict mode too (mirwa still produces them occasionally)

* Mon Nov 23 2015 Mikko Visa <mikko.visa@fmi.fi> - 15.11.23-1.fmi
- MIRWA-1144; LongInfo feature must be stored (even if it is empty) when loading woml, otherwise frontier's output will contain a broken text area (rect without width)

* Thu Nov 19 2015 Mikko Visa <mikko.visa@fmi.fi> - 15.11.19-1.fmi
- MIRWA-1144; Fixed bug in testing number of features loaded from input document

* Mon Nov 16 2015 Mikko Visa <mikko.visa@fmi.fi> - 15.11.16-1.fmi
- MIRWA-1141; ignore incomplete weather fronts in nonstrict mode
- LENTOSAA-1056; using targetRegion/regionId scheme 'urn:x-finnish-meterological-institute:icao:code' instead of 'ICAO'
- LENTOSAA-1056; In addition to "fmi", using targetRegion/regionId schema "ICAO" too

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
