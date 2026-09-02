#include <vulkan/vulkan.h>

#include <stdio.h>

int
main (void)
{
  // Create an instance and enumerate physical devices. That is the path
  // that scans ICD manifests and loads a GPU driver. Unlike tests/basics,
  // this fails if no compatible ICD is installed.

  VkApplicationInfo app = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "libvulkan-loader-live",
    .apiVersion = VK_API_VERSION_1_0,
  };

#ifdef __APPLE__
  // MoltenVK is a portability ICD. Any app on macOS must enable this
  // extension and flag or the loader will skip the driver.
  const char *exts[] = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME};
#endif

  VkInstanceCreateInfo ci = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
#ifdef __APPLE__
    .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
    .enabledExtensionCount = 1,
    .ppEnabledExtensionNames = exts,
#endif
    .pApplicationInfo = &app,
  };

  VkInstance inst = VK_NULL_HANDLE;
  VkResult r = vkCreateInstance (&ci, NULL, &inst);
  if (r != VK_SUCCESS)
  {
    fprintf (stderr,
             "vkCreateInstance failed (%d). No ICD was loaded, or the "
             "driver rejected the instance.\n",
             (int)r);
    return 1;
  }

  uint32_t n = 0;
  r = vkEnumeratePhysicalDevices (inst, &n, NULL);
  if (r != VK_SUCCESS || n == 0)
  {
    fprintf (stderr,
             "no physical devices (vkEnumeratePhysicalDevices=%d, count=%u)\n",
             (int)r, n);
    vkDestroyInstance (inst, NULL);
    return 1;
  }

  vkDestroyInstance (inst, NULL);
  return 0;
}
