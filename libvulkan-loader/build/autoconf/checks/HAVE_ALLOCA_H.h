// HAVE_ALLOCA_H : BUILD2_AUTOCONF_LIBC_VERSION

#ifndef BUILD2_AUTOCONF_LIBC_VERSION
#  error BUILD2_AUTOCONF_LIBC_VERSION appears to be conditionally included
#endif

#undef HAVE_ALLOCA_H

/* Check for the <alloca.h> header.
 *
 * Available since Linux/glibc 2.0 and Mac OS (exact version is unclear
 * but for a while now). Not available on Windows except MinGW. Not
 * available on FreeBSD, OpenBSD, or NetBSD.
 */
#if defined(__linux__)             || \
    defined(BUILD2_AUTOCONF_MACOS) || \
    defined(__MINGW32__)
#  define HAVE_ALLOCA_H 1
#endif
