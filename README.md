# Vulkan-Loader - The Vulkan ICD loader

This is a `build2` package repository for
[`Vulkan-Loader`](https://github.com/KhronosGroup/Vulkan-Loader), containing
the `libvulkan-loader` package (the open-source Khronos Vulkan ICD loader).

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libvulkan-loader` in your `build2`-based project, then instead see the
accompanying
[`libvulkan-loader/PACKAGE-README.md`](libvulkan-loader/PACKAGE-README.md)
file.

The development setup for `Vulkan-Loader` uses the standard `bdep`-based
workflow. For example:

```
git clone https://github.com/build2-packaging/Vulkan-Loader.git
cd Vulkan-Loader

bdep init -C @gcc cc config.c=gcc
bdep update
bdep test
```
