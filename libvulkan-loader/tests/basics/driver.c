#include <vulkan/vulkan.h>

#undef NDEBUG
#include <assert.h>

int main (void)
{
  /* layer enumeration reads manifests from disk, no GPU needed */
  uint32_t n = 0;
  VkResult r = vkEnumerateInstanceLayerProperties (&n, NULL);
  assert (r == VK_SUCCESS);
  return 0;
}
