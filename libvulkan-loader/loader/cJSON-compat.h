/* Map upstream loader_cJSON_* names onto stock libcjson.
 *
 * Query, delete, and PrintPreallocated have the same signature and are
 * macros. Parse and Print take a VkAllocationCallbacks and an out-of-memory
 * flag in the loader fork. Those extra arguments are ignored here. JSON
 * memory uses the libcjson allocator (malloc/free unless hooks are set).
 * A null return is treated as a parse or print failure, not OOM.
 */

#ifndef LOADER_CJSON_COMPAT_H
#define LOADER_CJSON_COMPAT_H

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stddef.h>

#include <cjson/cJSON.h>

#include "vk_loader_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VkAllocationCallbacks;

#define loader_cJSON_Delete                     cJSON_Delete
#define loader_cJSON_GetArraySize               cJSON_GetArraySize
#define loader_cJSON_GetArrayItem               cJSON_GetArrayItem
#define loader_cJSON_GetObjectItem              cJSON_GetObjectItem
#define loader_cJSON_GetObjectItemCaseSensitive cJSON_GetObjectItemCaseSensitive
#define loader_cJSON_HasObjectItem              cJSON_HasObjectItem
#define loader_cJSON_GetStringValue             cJSON_GetStringValue
#define loader_cJSON_GetNumberValue             cJSON_GetNumberValue
#define loader_cJSON_IsInvalid                  cJSON_IsInvalid
#define loader_cJSON_IsFalse                    cJSON_IsFalse
#define loader_cJSON_IsTrue                     cJSON_IsTrue
#define loader_cJSON_IsBool                     cJSON_IsBool
#define loader_cJSON_IsNull                     cJSON_IsNull
#define loader_cJSON_IsNumber                   cJSON_IsNumber
#define loader_cJSON_IsString                   cJSON_IsString
#define loader_cJSON_IsArray                    cJSON_IsArray
#define loader_cJSON_IsObject                   cJSON_IsObject
#define loader_cJSON_IsRaw                      cJSON_IsRaw
#define loader_cJSON_PrintPreallocated          cJSON_PrintPreallocated

static inline cJSON *
loader_cJSON_Parse (const struct VkAllocationCallbacks *pAllocator,
                    const char *value,
                    bool *out_of_memory)
{
  (void) pAllocator;
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_Parse (value);
}

static inline cJSON *
loader_cJSON_ParseWithLength (const struct VkAllocationCallbacks *pAllocator,
                              const char *value,
                              size_t buffer_length,
                              bool *out_of_memory)
{
  (void) pAllocator;
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_ParseWithLength (value, buffer_length);
}

static inline cJSON *
loader_cJSON_ParseWithOpts (const struct VkAllocationCallbacks *pAllocator,
                            const char *value,
                            const char **return_parse_end,
                            cJSON_bool require_null_terminated,
                            bool *out_of_memory)
{
  (void) pAllocator;
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_ParseWithOpts (value, return_parse_end, require_null_terminated);
}

static inline cJSON *
loader_cJSON_ParseWithLengthOpts (const struct VkAllocationCallbacks *pAllocator,
                                  const char *value,
                                  size_t buffer_length,
                                  const char **return_parse_end,
                                  cJSON_bool require_null_terminated,
                                  bool *out_of_memory)
{
  (void) pAllocator;
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_ParseWithLengthOpts (value,
                                    buffer_length,
                                    return_parse_end,
                                    require_null_terminated);
}

static inline char *
loader_cJSON_Print (const cJSON *item, bool *out_of_memory)
{
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_Print (item);
}

static inline char *
loader_cJSON_PrintUnformatted (const cJSON *item, bool *out_of_memory)
{
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_PrintUnformatted (item);
}

static inline char *
loader_cJSON_PrintBuffered (const cJSON *item,
                            int prebuffer,
                            cJSON_bool fmt,
                            bool *out_of_memory)
{
  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_PrintBuffered (item, prebuffer, fmt);
}

#ifdef __cplusplus
}
#endif

#endif /* !__ASSEMBLER__ */

#endif
