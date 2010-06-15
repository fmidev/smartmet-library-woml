%define LIBNAME woml
Summary: woml library
Name: libsmartmet-%{LIBNAME}
Version: 10.6.15
Release: 1.el5.fmi
License: FMI
Group: Development/Libraries
URL: http://www.weatherproof.fi
Source0: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: boost-devel >= 1.41
BuildRequires: libsmartmet-macgyver >= 10.6.1-1
BuildRequires: libxml++-devel >= 2.20.0-1
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
* Tue Jun 15 2010 Mika Heiskanen <mika.heiskanen@fmi.fi> - 10.6.15-1.el5.fmi
- Initial build
