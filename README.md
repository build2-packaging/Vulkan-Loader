# Vulkan-Loader - The Vulkan ICD loader

This is a `build2` package repository for
[`Vulkan-Loader`](https://github.com/KhronosGroup/Vulkan-Loader), containing:

- `libvulkan-loader` - the open-source Khronos Vulkan ICD loader
- `vulkan-loader-asm-offset` - host tool that emits ASM structure offsets for
  the loader's GAS trampolines (build-time dependency of the library)

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. For package usage, see
[`libvulkan-loader/PACKAGE-README.md`](libvulkan-loader/PACKAGE-README.md) and
[`vulkan-loader-asm-offset/PACKAGE-README.md`](vulkan-loader-asm-offset/PACKAGE-README.md).

The development setup for `Vulkan-Loader` uses the standard `bdep`-based
workflow. For example:

```
git clone https://github.com/build2-packaging/Vulkan-Loader.git
cd Vulkan-Loader

bdep init -C @gcc cc config.c=gcc
bdep update
bdep test
```
