#pragma once

#if defined(__cplusplus)
	#include <cassert>
	#include <cerrno>
	#include <cstdint>
	#include <cstdlib>
	#include <cstring>
	#include <memory>
	#define EXTERN	extern "C"
#else
	#include <stdarg.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <stdint.h>
	#define EXTERN	extern
#endif // defined(__cplusplus)

#define KINAKO_API	EXTERN
#define KN_NODISCARD
#define KN_INLINE	inline

#define CGLM_USE_ANONYMOUS_STRUCT 1
#include <cglm/cglm.h>
#include <cglm/struct.h>

#include <sokol/sokol_gfx.h>
