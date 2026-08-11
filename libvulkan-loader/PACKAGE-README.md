# libvulkan-loader - The Vulkan ICD loader

This is a `build2` package for the
[`Vulkan-Loader`](https://github.com/KhronosGroup/Vulkan-Loader) project.
It provides the open-source Khronos Vulkan ICD loader, the dispatch layer
between Vulkan applications and GPU-vendor ICDs. It builds `libvulkan.so` on
Linux and `vulkan-1.dll` on Windows.

Note that the GPU driver (ICD) itself must still be installed on the target
system. The loader loads it at runtime and cannot be packaged here.


## Usage

To start using `libvulkan-loader` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libvulkan-loader ^1.4.359
```

Then import the library in your `buildfile`:

```
import libs = libvulkan-loader%lib{vulkan}
```

If you were previously depending on `libvulkan-meta` (which links against a
system-installed SDK loader), change only the `depends:` line above. No
`buildfile` changes are needed since both packages export `lib{vulkan}`.


## Importable targets

This package provides the following importable targets:

```
lib{vulkan}
```

The shared library implementing the Vulkan ICD dispatch layer. Linking against
it also transitively imports `libvulkan-headers` so consumers get the Vulkan C
headers without a separate `depends:` entry. Optional unknown-extension
trampolines are built when a suitable assembler is available. Whether they
are present is exported as target metadata
`libvulkan_loader.unknown_functions`.


## Configuration variables

This package has no configuration variables.
