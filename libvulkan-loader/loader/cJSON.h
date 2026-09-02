/* Upstream sources include "cJSON.h". Map that onto the libcjson compat
 * layer. Use a normal include rather than compiler force-include: MSVC /FI
 * re-processes CRT and cJSON.h when the TU includes them again (C2011).
 */
#include "cJSON-compat.h"
