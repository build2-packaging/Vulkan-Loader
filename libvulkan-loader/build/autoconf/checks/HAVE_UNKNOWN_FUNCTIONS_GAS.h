// HAVE_UNKNOWN_FUNCTIONS_GAS

#undef HAVE_UNKNOWN_FUNCTIONS_GAS

/* GAS trampolines for unknown device and physical-device extension entry
 * points (unknown_ext_chain_gas_*.S). GCC/Clang on Linux, macOS, or BSD,
 * targeting x86/x86_64 or ARM/AArch64. Not a try_compile of the assembler.
 */
#if (defined(__GNUC__) || defined(__clang__)) && \
    !defined(_MSC_VER) && \
    (defined(__x86_64__) || defined(__i386__) || \
     defined(__aarch64__) || defined(__arm__)) && \
    (defined(__linux__) || defined(__APPLE__) || \
     defined(__FreeBSD__) || defined(__OpenBSD__) || \
     defined(__NetBSD__) || defined(__DragonFly__))
#  define HAVE_UNKNOWN_FUNCTIONS_GAS 1
#endif
