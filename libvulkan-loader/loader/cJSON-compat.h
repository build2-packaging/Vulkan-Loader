/* Map upstream loader_cJSON_* names onto stock libcjson.
 *
 * Query and delete have the same signature and are macros. Parse and Print
 * take a VkAllocationCallbacks and an out-of-memory flag in the loader fork.
 * Those extra arguments are ignored here. JSON memory uses the libcjson
 * allocator (malloc/free unless hooks are set). A null return is treated as
 * a parse or print failure, not OOM.
 *
 * The vendored loader_cJSON_Print is not stock JSON serialization. For a
 * string node it copies valuestring with no surrounding quotes and without
 * extra backslash escaping, and callers treat that as an allocated string
 * value (ICD library_path, layer names, and so on). Stock cJSON_Print wraps
 * strings in quotes, so the Print family is implemented here rather than
 * forwarded.
 *
 * Included via the cJSON.h thunk (upstream writes #include "cJSON.h").
 * Do not pull vk_loader_platform.h or extra CRT headers here. MSVC then
 * re-includes them from the TU and errors with C2011 on corecrt/cJSON.
 */

#ifndef LOADER_CJSON_COMPAT_H
#define LOADER_CJSON_COMPAT_H

#ifndef __ASSEMBLER__

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>

/* loader_json.h uses this before vk_loader_platform.h is included. Empty
 * unless SHOULD_EXPORT_TEST_FUNCTIONS, matching that header's default.
 */
#ifndef TEST_FUNCTION_EXPORT
#define TEST_FUNCTION_EXPORT
#endif

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
loader_cjson_dup_string (const cJSON *item, bool *out_of_memory)
{
  const char *s;
  size_t n;
  char *copy;

  if (out_of_memory != NULL)
    *out_of_memory = false;

  s = cJSON_GetStringValue (item);
  if (s == NULL)
    s = "";

  n = strlen (s) + 1;
  copy = (char *) malloc (n);
  if (copy == NULL)
  {
    if (out_of_memory != NULL)
      *out_of_memory = true;
    return NULL;
  }

  memcpy (copy, s, n);
  return copy;
}

static inline char *
loader_cJSON_Print (const cJSON *item, bool *out_of_memory)
{
  if (item != NULL && cJSON_IsString (item))
    return loader_cjson_dup_string (item, out_of_memory);

  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_Print (item);
}

static inline char *
loader_cJSON_PrintUnformatted (const cJSON *item, bool *out_of_memory)
{
  if (item != NULL && cJSON_IsString (item))
    return loader_cjson_dup_string (item, out_of_memory);

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
  if (item != NULL && cJSON_IsString (item))
    return loader_cjson_dup_string (item, out_of_memory);

  if (out_of_memory != NULL)
    *out_of_memory = false;

  return cJSON_PrintBuffered (item, prebuffer, fmt);
}

static inline cJSON_bool
loader_cJSON_PrintPreallocated (cJSON *item,
                                char *buffer,
                                const int length,
                                const cJSON_bool format)
{
  const char *s;
  size_t n;

  if (item != NULL && cJSON_IsString (item))
  {
    if (buffer == NULL || length <= 0)
      return (cJSON_bool) 0;

    s = cJSON_GetStringValue (item);
    if (s == NULL)
      s = "";

    n = strlen (s);
    if (n + 1 > (size_t) length)
      return (cJSON_bool) 0;

    memcpy (buffer, s, n + 1);
    return (cJSON_bool) 1;
  }

  return cJSON_PrintPreallocated (item, buffer, length, format);
}

#ifdef __cplusplus
}
#endif

#endif /* !__ASSEMBLER__ */

#endif
