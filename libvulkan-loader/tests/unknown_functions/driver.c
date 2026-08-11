// Smoke test: when libvulkan_loader.unknown_functions metadata is true, the
// static loader archive contains assembly trampoline entry points. Taking the
// address of one of them proves those objects were linked. Calling them
// without a real device dispatch table would crash, so we only verify linkage.

#include <vulkan/vulkan.h>

#undef NDEBUG
#include <assert.h>
#include <stdint.h>

// Implemented by unknown_ext_chain_* assembly, declared in dev_ext_trampoline.c
// when UNKNOWN_FUNCTIONS_SUPPORTED is defined. Not a public API.
VKAPI_ATTR void VKAPI_CALL vkdev_ext0 (VkDevice device);

int
main (void)
{
  volatile uintptr_t p = (uintptr_t)vkdev_ext0;
  assert (p != 0);
  (void)p;
  return 0;
}
