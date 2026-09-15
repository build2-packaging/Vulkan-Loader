#include <vulkan/vulkan.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef NDEBUG
#include <assert.h>

// Enumerate a fixture implicit layer whose manifest lives under
// VK_ADD_IMPLICIT_LAYER_PATH (set by testscript). The library_path is
// never loaded. A quoted name from stock cJSON_Print fails strcmp.

static const char kName[] = "VK_LAYER_BUILD2_json_strings";
static const char kDesc[] = "build2 json string parse test";

int
main (void)
{
  uint32_t n = 0;
  VkResult r = vkEnumerateInstanceLayerProperties (&n, NULL);
  assert (r == VK_SUCCESS);

  VkLayerProperties *layers = NULL;
  if (n != 0)
  {
    layers = malloc (n * sizeof *layers);
    assert (layers != NULL);
    r = vkEnumerateInstanceLayerProperties (&n, layers);
    assert (r == VK_SUCCESS);
  }

  int found = 0;
  for (uint32_t i = 0; i < n; ++i)
  {
    if (strcmp (layers[i].layerName, kName) == 0)
    {
      found = 1;
      assert (strlen (layers[i].layerName) == sizeof kName - 1);
      assert (strcmp (layers[i].description, kDesc) == 0);
      assert (strlen (layers[i].description) == sizeof kDesc - 1);
    }
  }

  if (!found)
  {
    fprintf (stderr, "expected layer %s, enumerated %u layer(s):\n", kName, n);
    for (uint32_t i = 0; i < n; ++i)
      fprintf (stderr, "  [%s] len=%zu\n",
               layers[i].layerName, strlen (layers[i].layerName));
  }

  free (layers);
  assert (found);
  return 0;
}
