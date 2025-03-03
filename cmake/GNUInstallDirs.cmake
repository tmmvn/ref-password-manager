# - Define GNU standard installation directories
# Provides install directory variables as defined for GNU software:
#  http://www.gnu.org/prep/standards/html_node/Directory-Variables.html
# Inclusion of this module defines the following variables:
#  CMAKE_INSTALL_<dir>      - destination for files of a given type
#  CMAKE_INSTALL_FULL_<dir> - corresponding absolute path
# where <dir> is one of:
#  BINDIR           - user executables (bin)
#  SBINDIR          - system admin executables (sbin)
#  LIBEXECDIR       - program executables (libexec)
#  SYSCONFDIR       - read-only single-machine data (etc)
#  SHAREDSTATEDIR   - modifiable architecture-independent data (com)
#  LOCALSTATEDIR    - modifiable single-machine data (var)
#  LIBDIR           - object code libraries (lib or lib64 or lib/<multiarch-tuple> on Debian)
#  INCLUDEDIR       - C header files (include)
#  OLDINCLUDEDIR    - C header files for non-gcc (/usr/include)
#  DATAROOTDIR      - read-only architecture-independent data root (share)
#  DATADIR          - read-only architecture-independent data (DATAROOTDIR)
#  INFODIR          - info documentation (DATAROOTDIR/info)
#  LOCALEDIR        - locale-dependent data (DATAROOTDIR/locale)
#  MANDIR           - man documentation (DATAROOTDIR/man)
#  DOCDIR           - documentation root (DATAROOTDIR/doc/PROJECT_NAME)
# Each CMAKE_INSTALL_<dir> value may be passed to the DESTINATION options of
# install() commands for the corresponding file type.  If the includer does
# not define a value the above-shown default will be used and the value will
# appear in the cache for editing by the user.
# Each CMAKE_INSTALL_FULL_<dir> value contains an absolute path constructed
# from the corresponding destination by prepending (if necessary) the value
# of CMAKE_INSTALL_PREFIX.
#=============================================================================
# Copyright 2011 Nikita Krupen'ko <krnekit@gmail.com>
# Copyright 2011 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)
# Installation directories
#
IF(NOT DEFINED CMAKE_INSTALL_BINDIR)
	SET(CMAKE_INSTALL_BINDIR "bin" CACHE PATH "user executables (bin)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_SBINDIR)
	SET(CMAKE_INSTALL_SBINDIR "sbin" CACHE PATH "system admin executables (sbin)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_LIBEXECDIR)
	SET(CMAKE_INSTALL_LIBEXECDIR "libexec" CACHE PATH "program executables (libexec)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_SYSCONFDIR)
	SET(CMAKE_INSTALL_SYSCONFDIR "etc" CACHE PATH "read-only single-machine data (etc)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_SHAREDSTATEDIR)
	SET(CMAKE_INSTALL_SHAREDSTATEDIR "com" CACHE PATH "modifiable architecture-independent data (com)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_LOCALSTATEDIR)
	SET(CMAKE_INSTALL_LOCALSTATEDIR "var" CACHE PATH "modifiable single-machine data (var)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_LIBDIR)
	SET(_LIBDIR_DEFAULT "lib")
	# Override this default 'lib' with 'lib64' iff:
	#  - we are on Linux system but NOT cross-compiling
	#  - we are NOT on debian
	#  - we are on a 64 bits system
	# reason is: amd64 ABI: http://www.x86-64.org/documentation/abi.pdf
	# For Debian with multiarch, use 'lib/${CMAKE_LIBRARY_ARCHITECTURE}' if
	# CMAKE_LIBRARY_ARCHITECTURE is set (which contains e.g. "i386-linux-gnu"
	# See http://wiki.debian.org/Multiarch
	IF((CMAKE_SYSTEM_NAME MATCHES "Linux|kFreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "GNU")
		AND NOT CMAKE_CROSSCOMPILING)
		IF(EXISTS "/etc/debian_version") # is this a debian system ?
			IF(CMAKE_LIBRARY_ARCHITECTURE)
				SET(_LIBDIR_DEFAULT "lib/${CMAKE_LIBRARY_ARCHITECTURE}")
			ENDIF()
		ELSE() # not debian, rely on CMAKE_SIZEOF_VOID_P:
			IF(NOT DEFINED CMAKE_SIZEOF_VOID_P)
				MESSAGE(AUTHOR_WARNING
					"Unable to determine default CMAKE_INSTALL_LIBDIR directory because no target architecture is known. "
					"Please enable at least one language before including GNUInstallDirs.")
			ELSE()
				IF("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
					SET(_LIBDIR_DEFAULT "lib64")
				ENDIF()
			ENDIF()
		ENDIF()
	ENDIF()
	SET(CMAKE_INSTALL_LIBDIR "${_LIBDIR_DEFAULT}" CACHE PATH "object code libraries (${_LIBDIR_DEFAULT})")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
	SET(CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "C header files (include)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_OLDINCLUDEDIR)
	SET(CMAKE_INSTALL_OLDINCLUDEDIR "/usr/include" CACHE PATH "C header files for non-gcc (/usr/include)")
ENDIF()
IF(NOT DEFINED CMAKE_INSTALL_DATAROOTDIR)
	SET(CMAKE_INSTALL_DATAROOTDIR "share" CACHE PATH "read-only architecture-independent data root (share)")
ENDIF()
#-----------------------------------------------------------------------------
# Values whose defaults are relative to DATAROOTDIR.  Store empty values in
# the cache and store the defaults in local variables if the cache values are
# not set explicitly.  This auto-updates the defaults as DATAROOTDIR changes.
IF(NOT CMAKE_INSTALL_DATADIR)
	SET(CMAKE_INSTALL_DATADIR "" CACHE PATH "read-only architecture-independent data (DATAROOTDIR)")
	SET(CMAKE_INSTALL_DATADIR "${CMAKE_INSTALL_DATAROOTDIR}")
ENDIF()
IF(NOT CMAKE_INSTALL_INFODIR)
	SET(CMAKE_INSTALL_INFODIR "" CACHE PATH "info documentation (DATAROOTDIR/info)")
	SET(CMAKE_INSTALL_INFODIR "${CMAKE_INSTALL_DATAROOTDIR}/info")
ENDIF()
IF(NOT CMAKE_INSTALL_LOCALEDIR)
	SET(CMAKE_INSTALL_LOCALEDIR "" CACHE PATH "locale-dependent data (DATAROOTDIR/locale)")
	SET(CMAKE_INSTALL_LOCALEDIR "${CMAKE_INSTALL_DATAROOTDIR}/locale")
ENDIF()
IF(NOT CMAKE_INSTALL_MANDIR)
	SET(CMAKE_INSTALL_MANDIR "" CACHE PATH "man documentation (DATAROOTDIR/man)")
	SET(CMAKE_INSTALL_MANDIR "${CMAKE_INSTALL_DATAROOTDIR}/man")
ENDIF()
IF(NOT CMAKE_INSTALL_DOCDIR)
	SET(CMAKE_INSTALL_DOCDIR "" CACHE PATH "documentation root (DATAROOTDIR/doc/PROJECT_NAME)")
	SET(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}")
ENDIF()
#-----------------------------------------------------------------------------
MARK_AS_ADVANCED(
	CMAKE_INSTALL_BINDIR
	CMAKE_INSTALL_SBINDIR
	CMAKE_INSTALL_LIBEXECDIR
	CMAKE_INSTALL_SYSCONFDIR
	CMAKE_INSTALL_SHAREDSTATEDIR
	CMAKE_INSTALL_LOCALSTATEDIR
	CMAKE_INSTALL_LIBDIR
	CMAKE_INSTALL_INCLUDEDIR
	CMAKE_INSTALL_OLDINCLUDEDIR
	CMAKE_INSTALL_DATAROOTDIR
	CMAKE_INSTALL_DATADIR
	CMAKE_INSTALL_INFODIR
	CMAKE_INSTALL_LOCALEDIR
	CMAKE_INSTALL_MANDIR
	CMAKE_INSTALL_DOCDIR
)
# Result directories
#
FOREACH(dir
	BINDIR
	SBINDIR
	LIBEXECDIR
	SYSCONFDIR
	SHAREDSTATEDIR
	LOCALSTATEDIR
	LIBDIR
	INCLUDEDIR
	OLDINCLUDEDIR
	DATAROOTDIR
	DATADIR
	INFODIR
	LOCALEDIR
	MANDIR
	DOCDIR
)
	IF(NOT IS_ABSOLUTE ${CMAKE_INSTALL_${dir}})
		SET(CMAKE_INSTALL_FULL_${dir} "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_${dir}}")
	ELSE()
		SET(CMAKE_INSTALL_FULL_${dir} "${CMAKE_INSTALL_${dir}}")
	ENDIF()
ENDFOREACH()
