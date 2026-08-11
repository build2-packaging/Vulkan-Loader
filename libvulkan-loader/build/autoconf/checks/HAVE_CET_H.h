// HAVE_CET_H : BUILD2_AUTOCONF_LIBC_VERSION

#ifndef BUILD2_AUTOCONF_LIBC_VERSION
#  error BUILD2_AUTOCONF_LIBC_VERSION appears to be conditionally included
#endif

#undef HAVE_CET_H

/* <cet.h> provides _CET_ENDBR for Intel CET. Used by
 * unknown_ext_chain_gas_x86.S. Approximate: glibc Linux on x86/x86_64.
 * Without it the assembly uses an empty _CET_ENDBR.
 */
#if (defined(__i386__) || defined(__x86_64__)) && \
    defined(__linux__) && \
    BUILD2_AUTOCONF_GLIBC_PREREQ(2, 28)
#  define HAVE_CET_H 1
#endif
