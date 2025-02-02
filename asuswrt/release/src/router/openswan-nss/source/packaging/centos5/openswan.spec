Summary: Openswan IPsec implementation
Name: openswan
Version: 2.6.41
%{!?buildklips: %{expand: %%define buildklips 0}}
%{!?buildxen: %{expand: %%define buildxen 0}}

# nss build
%{!?buildnss: %{expand: %%define buildnss 0}}

# The default kernel version to build for is the latest of
# the installed binary kernel
# This can be overridden by "--define 'kversion x.x.x-y.y.y'"
%define defkv %(rpm -q kernel kernel-smp| grep -v "not installed" | sed "s/kernel-smp-\\\(.\*\\\)$/\\1smp/"| sed "s/kernel-//"| sort | tail -1)
%{!?kversion: %{expand: %%define kversion %defkv}}
%define krelver %(echo %{kversion} | tr -s '-' '_')

# Openswan -pre/-rc nomenclature has to co-exist with hyphen paranoia
%define srcpkgver %(echo %{version} | tr -s '_' '-')
%define ourrelease 1
Release: %{ourrelease}
License: GPLv2, some BSD
Url: http://www.openswan.org/
Source: openswan-%{srcpkgver}.tar.gz
Group: System Environment/Daemons
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Summary: Openswan - An IPsec and IKE implementation
Group: System Environment/Daemons
BuildRequires: gmp-devel bison flex bind-devel redhat-rpm-config xmlto
%if %{buildnss}
BuildRequires: nss >= 3.12.6-2
%endif
Requires: iproute >= 2.6.8
Requires(post): coreutils bash
Requires(preun): initscripts chkconfig
Requires(post): /sbin/chkconfig
Requires(preun): /sbin/chkconfig
Requires(preun): /sbin/service

%description
Openswan is a free implementation of IPsec & IKE for Linux.  IPsec is 
the Internet Protocol Security and uses strong cryptography to provide
both authentication and encryption services.  These services allow you
to build secure tunnels through untrusted networks.  Everything passing
through the untrusted net is encrypted by the ipsec gateway machine and 
decrypted by the gateway at the other end of the tunnel.  The resulting
tunnel is a virtual private network or VPN.

This package contains Bluerose Openswan, which is a variant maintained
by Michael Richardson <mcr@sandelman.ca>.  No version information is provided
with this package other than a year and week number. For a supported product
contact sales@xelerance.com.

This package contains the daemons and userland tools for setting up
Openswan. It optionally also builds the Openswan KLIPS IPsec stack that
is an alternative for the NETKEY/XFRM IPsec stack that exists in the
default Linux kernel.

Openswan 2.6.x also supports IKEv2 (RFC4309)

%if %{buildklips}
%package klips
Summary: Openswan kernel module
Group:  System Environment/Kernel
Release: %{krelver}_%{ourrelease}
Requires: kernel = %{kversion}, %{name}-%{version}

%description klips
This package contains only the ipsec module for the RedHat/Fedora series of
kernels.
%endif

%prep
%setup -q -n openswan-%{srcpkgver}

%build
%{__make} \
  USERCOMPILE="-g %{optflags} -fPIE -pie" \
  USERLINK="-g -pie" \
  HAVE_THREADS="true" \
%if %{buildnss}
  USE_LIBNSS="true" \
  USE_FIPSCHECK="true" \
  USE_LIBCAP_NG="true" \
%endif
  USE_DYNAMICDNS="true" \
  USE_LWRES="true" \
  INC_USRLOCAL=%{_prefix} \
  FINALLIBDIR=%{_libdir}/ipsec \
  MANTREE=%{_mandir} \
  INC_RCDEFAULT=%{_initrddir} \
  programs
FS=$(pwd)

%if %{buildklips}
mkdir -p BUILD.%{_target_cpu}

cd packaging/fedora
# rpm doesn't know we're compiling kernel code. optflags will give us -m64
%{__make} -C $FS MOD26BUILDDIR=$FS/BUILD.%{_target_cpu} \
    OPENSWANSRCDIR=$FS \
    KLIPSCOMPILE="%{optflags}" \
    KERNELSRC=/lib/modules/%{kversion}/build \
%if %{buildxen}
    ARCH=xen \
%else
    ARCH=%{_arch} \
%endif
    MODULE_DEF_INCLUDE=$FS/packaging/centos5/config-%{_target_cpu}.h \
    MODULE_EXTRA_INCLUDE=$FS/packaging/centos5/extra_%{krelver}.h \
    include module
%endif

%install
rm -rf ${RPM_BUILD_ROOT}
%{__make} \
  DESTDIR=%{buildroot} \
  INC_USRLOCAL=%{_prefix} \
  FINALLIBDIR=%{_libdir}/ipsec \
  MANTREE=%{buildroot}%{_mandir} \
  INC_RCDEFAULT=%{_initrddir} \
  USE_LWRES="true" \
  install
FS=$(pwd)
rm -rf %{buildroot}/usr/share/doc/openswan
rm -rf %{buildroot}/%{_initrddir}/setup
rm -rf %{buildroot}/etc/ipsec.d/examples
find %{buildroot}%{_mandir}  -type f | xargs chmod a-x

install -d -m 0700 %{buildroot}%{_localstatedir}/run/pluto
# used when setting --perpeerlog without --perpeerlogbase 
install -d -m 0700 %{buildroot}%{_localstatedir}/log/pluto/peer
install -d %{buildroot}%{_sbindir}

%if %{buildklips}
mkdir -p %{buildroot}/lib/modules/%{kversion}/kernel/net/ipsec
for i in $FS/BUILD.%{_target_cpu}/ipsec.ko  $FS/modobj/ipsec.o
do
  if [ -f $i ]
  then
    cp $i %{buildroot}/lib/modules/%{kversion}/kernel/net/ipsec 
  fi
done
%endif

%clean
rm -rf ${RPM_BUILD_ROOT}

%files 
%defattr(-,root,root)
%doc BUGS CHANGES COPYING CREDITS README LICENSE
%doc OBJ.linux.*/programs/examples/*.conf
#%doc doc/manpage.d/*
# /usr/share/doc/openswan/*
%attr(0644,root,root) %config(noreplace) %{_sysconfdir}/ipsec.conf
%attr(0700,root,root) %dir %{_sysconfdir}/ipsec.d
%attr(0700,root,root) %dir %{_localstatedir}/log/pluto/peer
%attr(0644,root,root) %config(noreplace) %{_sysconfdir}/ipsec.d/policies/*
%{_localstatedir}/run/pluto
%{_initrddir}/ipsec
%{_libdir}/ipsec
%{_sbindir}/ipsec
%{_libexecdir}/ipsec
%doc %{_mandir}/*/*

%if %{buildklips}
%files klips
%defattr (-,root,root)
/lib/modules/%{kversion}/kernel/net/ipsec
%endif

%preun
if [ $1 -eq 0 ]; then
        /sbin/service ipsec stop > /dev/null 2>&1
        /sbin/chkconfig --del ipsec
fi

%postun
if [ $1 -ge 1 ] ; then
 /sbin/service ipsec condrestart 2>&1 >/dev/null
fi

%if %{buildklips}
%postun klips
/sbin/depmod -ae %{kversion}
%post klips
/sbin/depmod -ae %{kversion}
%endif

%post 
/sbin/chkconfig --add ipsec

%changelog
* Thu Dec 20 2007 Paul Wouters <paul@xelerance.com> - 2.6.03-1
- Applied patch by RedHat to allow building with debug package
* Thu Dec 20 2007 Paul Wouters <paul@xelerance.com> - 2.6.01-1
- Work around for warnings in BIND related code
- Remove bogus file /etc/init.d/setup at install
- Cleaned up spec file

* Mon Oct 10 2005 Paul Wouters <paul@xelerance.com>
- Updated for klips on xen 
- added ldconfig for post klips to obtain ipsec module dependancies
- Run 'make include' since on FC4 kernel source does not have the links yet.

* Wed Jan  5 2005 Paul Wouters <paul@xelerance.com>
- Updated for x86_64 and klips on 2.6

* Sun Sep  5 2004 Paul Wouters <paul@xelerance.com>
- Updated for openswan

* Fri Aug 22 2003 Sam Sgro <sam@freeswan.org>
- Juggling release/source package names to allow for 
  -pre/-rc releases to build.

* Thu Aug 14 2003 Sam Sgro <sam@freeswan.org>
- Reverting back to pre-x.509 version, cosmetic changes.

* Tue May 20 2003 Charlie Brady <charlieb@e-smith.com> 2.0.0-x509_1.3.2_2es
- Add "Obsoletes: freeswan" to userland RPM.

* Fri May 16 2003 Charlie Brady <charlieb@e-smith.com> 2.0.0-x509_1.3.2_1es
- Add version 1.3.2 of the x509 patch.
- Add missing /usr/libexec/ipsec dir and files.
- Minor tidy up of spec file.

* Thu May 15 2003 Charlie Brady <charlieb@e-smith.com> 2.0.0-1es
- Based on work by Paul Lahaie of Steamballoon, Michael
  Richardson of freeS/WAN team and Tuomo Soini <tis@foobar.fi>.
- Build freeswan RPMs from a single source RPM, for RedHat, but
  should work on any RPM based system.
