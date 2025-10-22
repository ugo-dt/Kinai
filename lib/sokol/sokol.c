#ifndef __EMSCRIPTEN__
#include <glad/glad.h>
#endif
#define SOKOL_IMPL
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_time.h"
#define SGP_UNIFORM_CONTENT_SLOTS 32
#include "sokol_gp.h"
#include "sokol_debugtext.h"
