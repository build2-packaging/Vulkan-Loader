# vulkan-loader-asm-offset - Vulkan Loader

This is a `build2` package for the [`<UPSTREAM-NAME>`](https://<UPSTREAM-URL>)
executable. It is a <SUMMARY-OF-FUNCTIONALITY>.

Note that the `vulkan-loader-asm-offset` executable in this package provides `build2` metadata.


## Usage

To start using `vulkan-loader-asm-offset` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * vulkan-loader-asm-offset ^<VERSION>
```

Then import the executable in your `buildfile`:

```
import! [metadata] <TARGET> = vulkan-loader-asm-offset%exe{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
exe{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.vulkan_loader_asm_offset.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>
