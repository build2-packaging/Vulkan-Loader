# vulkan-loader-asm-offset - Host tool for Vulkan loader ASM offsets

This is a `build2` package for a small host tool from
[`Vulkan-Loader`](https://github.com/KhronosGroup/Vulkan-Loader). It builds
`exe{asm_offset}`, which emits `gen_defines.asm` with structure offsets used
by the loader's GAS unknown-extension trampolines.


## Usage

Add a build-time dependency to your `manifest`, adjusting the version
constraint as appropriate:

```
depends: * vulkan-loader-asm-offset ^1.4.359
```

Then import the executable in your `buildfile`:

```
import! asm_offset = vulkan-loader-asm-offset%exe{asm_offset}
```

Run it with a dialect argument (`GAS`, `MASM`, or `MARMASM`). It writes
`gen_defines.asm` in the process current working directory.


## Importable targets

This package provides the following importable targets:

```
exe{asm_offset}
```

Host helper used when building the loader's optional assembly trampolines.
Not required by applications at runtime.


## Configuration variables

This package has no configuration variables.
