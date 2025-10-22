#if defined(SOKOL_IMPL) && !defined(SOKOL_DEBUGTEXT_IMPL)
#define SOKOL_DEBUGTEXT_IMPL
#endif
#ifndef SOKOL_DEBUGTEXT_INCLUDED

#define SOKOL_DEBUGTEXT_INCLUDED (1)
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // size_t
#include <stdarg.h> // va_list
#include <sokol_gfx.h>

#if !defined(SOKOL_GFX_INCLUDED)
#error "Please include sokol_gfx.h before sokol_debugtext.h"
#endif

#if defined(SOKOL_API_DECL) && !defined(SOKOL_DEBUGTEXT_API_DECL)
#define SOKOL_DEBUGTEXT_API_DECL SOKOL_API_DECL
#endif
#ifndef SOKOL_DEBUGTEXT_API_DECL
#if defined(_WIN32) && defined(SOKOL_DLL) && defined(SOKOL_DEBUGTEXT_IMPL)
#define SOKOL_DEBUGTEXT_API_DECL __declspec(dllexport)
#elif defined(_WIN32) && defined(SOKOL_DLL)
#define SOKOL_DEBUGTEXT_API_DECL __declspec(dllimport)
#else
#define SOKOL_DEBUGTEXT_API_DECL extern
#endif
#endif

#if defined(__GNUC__)
#define SOKOL_DEBUGTEXT_PRINTF_ATTR __attribute__((format(printf, 1, 2)))
#else
#define SOKOL_DEBUGTEXT_PRINTF_ATTR
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define _SDTX_LOG_ITEMS \
    _SDTX_LOGITEM_XMACRO(OK, "Ok") \
    _SDTX_LOGITEM_XMACRO(MALLOC_FAILED, "memory allocation failed") \
    _SDTX_LOGITEM_XMACRO(ADD_COMMIT_LISTENER_FAILED, "sg_add_commit_listener() failed") \
    _SDTX_LOGITEM_XMACRO(COMMAND_BUFFER_FULL, "command buffer full (adjust via sdtx_context_desc_t.max_commands)") \
    _SDTX_LOGITEM_XMACRO(CONTEXT_POOL_EXHAUSTED, "context pool exhausted (adjust via sdtx_desc_t.context_pool_size)") \
    _SDTX_LOGITEM_XMACRO(CANNOT_DESTROY_DEFAULT_CONTEXT, "cannot destroy default context") \

#define _SDTX_LOGITEM_XMACRO(item,msg) SDTX_LOGITEM_##item,
typedef enum sdtx_log_item_t {
    _SDTX_LOG_ITEMS
} sdtx_log_item_t;
#undef _SDTX_LOGITEM_XMACRO

/*
    sdtx_logger_t

    Used in sdtx_desc_t to provide a custom logging and error reporting
    callback to sokol-debugtext.
*/
typedef struct sdtx_logger_t {
    void (*func)(
        const char* tag,                // always "sdtx"
        uint32_t log_level,             // 0=panic, 1=error, 2=warning, 3=info
        uint32_t log_item_id,           // SDTX_LOGITEM_*
        const char* message_or_null,    // a message string, may be nullptr in release mode
        uint32_t line_nr,               // line number in sokol_debugtext.h
        const char* filename_or_null,   // source filename, may be nullptr in release mode
        void* user_data);
    void* user_data;
} sdtx_logger_t;

/* a rendering context handle */
typedef struct sdtx_context { uint32_t id; } sdtx_context;

/* the default context handle */
static const sdtx_context SDTX_DEFAULT_CONTEXT = { 0x00010001 };

/*
    sdtx_range is a pointer-size-pair struct used to pass memory
    blobs into sokol-debugtext. When initialized from a value type
    (array or struct), use the SDTX_RANGE() macro to build
    an sdtx_range struct.
*/
typedef struct sdtx_range {
    const void* ptr;
    size_t size;
} sdtx_range;

// disabling this for every includer isn't great, but the warning is also quite pointless
#if defined(_MSC_VER)
#pragma warning(disable:4221)   /* /W4 only: nonstandard extension used: 'x': cannot be initialized using address of automatic variable 'y' */
#pragma warning(disable:4204)   /* VS2015: nonstandard extension used: non-constant aggregate initializer */
#endif
#if defined(__cplusplus)
#define SDTX_RANGE(x) sdtx_range{ &x, sizeof(x) }
#else
#define SDTX_RANGE(x) (sdtx_range){ &x, sizeof(x) }
#endif

#define SDTX_MAX_FONTS (8)

typedef struct sdtx_font_desc_t {
    sdtx_range data;        // pointer to and size of font pixel data
    uint8_t first_char;     // first character index in font pixel data
    uint8_t last_char;      // last character index in font pixel data, inclusive (default: 255)
} sdtx_font_desc_t;

typedef struct sdtx_context_desc_t {
    int max_commands;                       // max number of draw commands, each layer transition counts as a command, default: 4096
    int char_buf_size;                      // max number of characters rendered in one frame, default: 4096
    float canvas_width;                     // the initial virtual canvas width, default: 640
    float canvas_height;                    // the initial virtual canvas height, default: 400
    int tab_width;                          // tab width in number of characters, default: 4
    sg_pixel_format color_format;           // color pixel format of target render pass
    sg_pixel_format depth_format;           // depth pixel format of target render pass
    int sample_count;                       // MSAA sample count of target render pass
} sdtx_context_desc_t;

typedef struct sdtx_allocator_t {
    void* (*alloc_fn)(size_t size, void* user_data);
    void (*free_fn)(void* ptr, void* user_data);
    void* user_data;
} sdtx_allocator_t;

typedef struct sdtx_desc_t {
    int context_pool_size;                  // max number of rendering contexts that can be created, default: 8
    int printf_buf_size;                    // size of internal buffer for snprintf(), default: 4096
    sdtx_font_desc_t fonts[SDTX_MAX_FONTS]; // up to 8 fonts descriptions
    sdtx_context_desc_t context;            // the default context creation parameters
    sdtx_allocator_t allocator;             // optional memory allocation overrides (default: malloc/free)
    sdtx_logger_t logger;                   // optional log override function (default: NO LOGGING)
} sdtx_desc_t;

/* initialization/shutdown */
SOKOL_DEBUGTEXT_API_DECL void sdtx_setup(const sdtx_desc_t* desc);
SOKOL_DEBUGTEXT_API_DECL void sdtx_shutdown(void);

/* builtin font data (use to populate sdtx_desc.font[]) */
SOKOL_DEBUGTEXT_API_DECL sdtx_font_desc_t sdtx_font_kc853(void);
SOKOL_DEBUGTEXT_API_DECL sdtx_font_desc_t sdtx_font_kc854(void);
SOKOL_DEBUGTEXT_API_DECL sdtx_font_desc_t sdtx_font_z1013(void);
SOKOL_DEBUGTEXT_API_DECL sdtx_font_desc_t sdtx_font_cpc(void);
SOKOL_DEBUGTEXT_API_DECL sdtx_font_desc_t sdtx_font_c64(void);
SOKOL_DEBUGTEXT_API_DECL sdtx_font_desc_t sdtx_font_oric(void);

/* context functions */
SOKOL_DEBUGTEXT_API_DECL sdtx_context sdtx_make_context(const sdtx_context_desc_t* desc);
SOKOL_DEBUGTEXT_API_DECL void sdtx_destroy_context(sdtx_context ctx);
SOKOL_DEBUGTEXT_API_DECL void sdtx_set_context(sdtx_context ctx);
SOKOL_DEBUGTEXT_API_DECL sdtx_context sdtx_get_context(void);
SOKOL_DEBUGTEXT_API_DECL sdtx_context sdtx_default_context(void);

/* drawing functions (call inside sokol-gfx render pass) */
SOKOL_DEBUGTEXT_API_DECL void sdtx_draw(void);
SOKOL_DEBUGTEXT_API_DECL void sdtx_context_draw(sdtx_context ctx);
SOKOL_DEBUGTEXT_API_DECL void sdtx_draw_layer(int layer_id);
SOKOL_DEBUGTEXT_API_DECL void sdtx_context_draw_layer(sdtx_context ctx, int layer_id);

/* switch render layer */
SOKOL_DEBUGTEXT_API_DECL void sdtx_layer(int layer_id);

/* switch to a different font */
SOKOL_DEBUGTEXT_API_DECL void sdtx_font(int font_index);

/* set a new virtual canvas size in screen pixels */
SOKOL_DEBUGTEXT_API_DECL void sdtx_canvas(float w, float h);

/* set a new origin in character grid coordinates */
SOKOL_DEBUGTEXT_API_DECL void sdtx_origin(float x, float y);

/* cursor movement functions (relative to origin in character grid coordinates) */
SOKOL_DEBUGTEXT_API_DECL void sdtx_home(void);
SOKOL_DEBUGTEXT_API_DECL void sdtx_pos(float x, float y);
SOKOL_DEBUGTEXT_API_DECL void sdtx_pos_x(float x);
SOKOL_DEBUGTEXT_API_DECL void sdtx_pos_y(float y);
SOKOL_DEBUGTEXT_API_DECL void sdtx_move(float dx, float dy);
SOKOL_DEBUGTEXT_API_DECL void sdtx_move_x(float dx);
SOKOL_DEBUGTEXT_API_DECL void sdtx_move_y(float dy);
SOKOL_DEBUGTEXT_API_DECL void sdtx_crlf(void);

/* set the current text color */
SOKOL_DEBUGTEXT_API_DECL void sdtx_color3b(uint8_t r, uint8_t g, uint8_t b);              // RGB 0..255, A=255
SOKOL_DEBUGTEXT_API_DECL void sdtx_color3f(float r, float g, float b);                    // RGB 0.0f..1.0f, A=1.0f
SOKOL_DEBUGTEXT_API_DECL void sdtx_color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a);   // RGBA 0..255
SOKOL_DEBUGTEXT_API_DECL void sdtx_color4f(float r, float g, float b, float a);           // RGBA 0.0f..1.0f
SOKOL_DEBUGTEXT_API_DECL void sdtx_color1i(uint32_t rgba);                                // ABGR 0xAABBGGRR

/* text rendering */
SOKOL_DEBUGTEXT_API_DECL void sdtx_putc(char c);
SOKOL_DEBUGTEXT_API_DECL void sdtx_puts(const char* str);             // does NOT append newline!
SOKOL_DEBUGTEXT_API_DECL void sdtx_putr(const char* str, int len);    // 'put range', also stops at zero-char
SOKOL_DEBUGTEXT_API_DECL int sdtx_printf(const char* fmt, ...) SOKOL_DEBUGTEXT_PRINTF_ATTR;
SOKOL_DEBUGTEXT_API_DECL int sdtx_vprintf(const char* fmt, va_list args);

/* language bindings helper: get the internal printf format buffer */
SOKOL_DEBUGTEXT_API_DECL sdtx_range sdtx_get_cleared_fmt_buffer(void);

#ifdef __cplusplus
} /* extern "C" */
/* C++ const-ref wrappers */
inline void sdtx_setup(const sdtx_desc_t& desc) { return sdtx_setup(&desc); }
inline sdtx_context sdtx_make_context(const sdtx_context_desc_t& desc) { return sdtx_make_context(&desc); }
#endif
#endif /* SOKOL_DEBUGTEXT_INCLUDED */

// >>implementation
#define SOKOL_DEBUGTEXT_IMPL_INCLUDED (1)

#if defined(SOKOL_MALLOC) || defined(SOKOL_CALLOC) || defined(SOKOL_FREE)
#error "SOKOL_MALLOC/CALLOC/FREE macros are no longer supported, please use sdtx_desc_t.allocator to override memory allocation functions"
#endif

#include <string.h> // memset
#include <math.h>   // fmodf
#include <stdarg.h> // for vsnprintf
#include <stdlib.h> // malloc/free

#ifndef SOKOL_API_IMPL
    #define SOKOL_API_IMPL
#endif
#ifndef SOKOL_DEBUG
    #ifndef NDEBUG
        #define SOKOL_DEBUG
    #endif
#endif
#ifndef SOKOL_ASSERT
    #include <assert.h>
    #define SOKOL_ASSERT(c) assert(c)
#endif

#ifndef SOKOL_UNREACHABLE
    #define SOKOL_UNREACHABLE SOKOL_ASSERT(false)
#endif
#ifndef _SOKOL_UNUSED
    #define _SOKOL_UNUSED(x) (void)(x)
#endif

#ifndef SOKOL_VSNPRINTF
#include <stdio.h>
#define SOKOL_VSNPRINTF vsnprintf
#endif

#define _sdtx_def(val, def) (((val) == 0) ? (def) : (val))
#define _SDTX_INIT_COOKIE (0xACBAABCA)

#define _SDTX_DEFAULT_MAX_COMMANDS (4096)
#define _SDTX_DEFAULT_CONTEXT_POOL_SIZE (8)
#define _SDTX_DEFAULT_CHAR_BUF_SIZE (4096)
#define _SDTX_DEFAULT_PRINTF_BUF_SIZE (4096)
#define _SDTX_DEFAULT_CANVAS_WIDTH (640)
#define _SDTX_DEFAULT_CANVAS_HEIGHT (480)
#define _SDTX_DEFAULT_TAB_WIDTH (4)
#define _SDTX_DEFAULT_COLOR (0xFF00FFFF)
#define _SDTX_INVALID_SLOT_INDEX (0)
#define _SDTX_SLOT_SHIFT (16)
#define _SDTX_MAX_POOL_SIZE (1<<_SDTX_SLOT_SHIFT)
#define _SDTX_SLOT_MASK (_SDTX_MAX_POOL_SIZE-1)

// >>structs
typedef struct {
    uint32_t id;
    sg_resource_state state;
} _sdtx_slot_t;

typedef struct {
    int size;
    int queue_top;
    uint32_t* gen_ctrs;
    int* free_queue;
} _sdtx_pool_t;

typedef struct {
    float x, y;
} _sdtx_float2_t;

typedef struct {
    float x, y;
    uint16_t u, v;
    uint32_t color;
} _sdtx_vertex_t;

typedef struct {
    int layer_id;
    int first_vertex;
    int num_vertices;
} _sdtx_command_t;

typedef struct {
    _sdtx_slot_t slot;
    sdtx_context_desc_t desc;
    uint32_t frame_id;
    uint32_t update_frame_id;
    struct {
        int cap;
        int next;
        _sdtx_vertex_t* ptr;
    } vertices;
    struct {
        int cap;
        int next;
        _sdtx_command_t* ptr;
    } commands;
    sg_buffer vbuf;
    sg_pipeline pip;
    int cur_font;
    int cur_layer_id;
    _sdtx_float2_t canvas_size;
    _sdtx_float2_t glyph_size;
    _sdtx_float2_t origin;
    _sdtx_float2_t pos;
    float tab_width;
    uint32_t color;
} _sdtx_context_t;

typedef struct {
    _sdtx_pool_t pool;
    _sdtx_context_t* contexts;
} _sdtx_context_pool_t;

typedef struct {
    uint32_t init_cookie;
    sdtx_desc_t desc;
    sg_image font_img;
    sg_view font_view;
    sg_sampler font_smp;
    sg_shader shader;
    uint32_t fmt_buf_size;
    char* fmt_buf;
    sdtx_context def_ctx_id;
    sdtx_context cur_ctx_id;
    _sdtx_context_t* cur_ctx;   // may be 0!
    _sdtx_context_pool_t context_pool;
    uint8_t font_pixels[SDTX_MAX_FONTS * 256 * 8 * 8];
} _sdtx_t;
static _sdtx_t _sdtx;

static void _sdtx_init_context(sdtx_context ctx_id, const sdtx_context_desc_t* in_desc) {
    sg_push_debug_group("sokol-debugtext");

    SOKOL_ASSERT((ctx_id.id != SG_INVALID_ID) && in_desc);
    _sdtx_context_t* ctx = _sdtx_lookup_context(ctx_id.id);
    SOKOL_ASSERT(ctx);
    ctx->desc = _sdtx_context_desc_defaults(in_desc);
    ctx->frame_id = 1;

    ctx->vertices.cap = 6 * ctx->desc.char_buf_size;
    const size_t vbuf_size = (size_t)ctx->vertices.cap * sizeof(_sdtx_vertex_t);
    ctx->vertices.ptr = (_sdtx_vertex_t*) _sdtx_malloc(vbuf_size);

    ctx->commands.cap = ctx->desc.max_commands;
    ctx->commands.ptr = (_sdtx_command_t*) _sdtx_malloc((size_t)ctx->commands.cap * sizeof(_sdtx_command_t));
    _sdtx_set_layer(ctx, 0);

    sg_buffer_desc vbuf_desc;
    _sdtx_clear(&vbuf_desc, sizeof(vbuf_desc));
    vbuf_desc.size = vbuf_size;
    vbuf_desc.usage.vertex_buffer = true;
    vbuf_desc.usage.stream_update = true;
    vbuf_desc.label = "sdtx-vbuf";
    ctx->vbuf = sg_make_buffer(&vbuf_desc);
    SOKOL_ASSERT(SG_INVALID_ID != ctx->vbuf.id);

    sg_pipeline_desc pip_desc;
    _sdtx_clear(&pip_desc, sizeof(pip_desc));
    pip_desc.layout.buffers[0].stride = sizeof(_sdtx_vertex_t);
    pip_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
    pip_desc.layout.attrs[1].format = SG_VERTEXFORMAT_USHORT2N;
    pip_desc.layout.attrs[2].format = SG_VERTEXFORMAT_UBYTE4N;
    pip_desc.shader = _sdtx.shader;
    pip_desc.index_type = SG_INDEXTYPE_NONE;
    pip_desc.sample_count = ctx->desc.sample_count;
    pip_desc.depth.pixel_format = ctx->desc.depth_format;
    pip_desc.colors[0].pixel_format = ctx->desc.color_format;
    pip_desc.colors[0].blend.enabled = true;
    pip_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
    pip_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    pip_desc.colors[0].blend.src_factor_alpha = SG_BLENDFACTOR_ONE;
    pip_desc.colors[0].blend.dst_factor_alpha = SG_BLENDFACTOR_ZERO;
    pip_desc.label = "sdtx-pipeline";
    ctx->pip = sg_make_pipeline(&pip_desc);
    SOKOL_ASSERT(SG_INVALID_ID != ctx->pip.id);

    ctx->canvas_size.x = ctx->desc.canvas_width;
    ctx->canvas_size.y = ctx->desc.canvas_height;
    ctx->glyph_size.x = 8.0f / ctx->canvas_size.x;
    ctx->glyph_size.y = 8.0f / ctx->canvas_size.y;
    ctx->tab_width = (float) ctx->desc.tab_width;
    ctx->color = _SDTX_DEFAULT_COLOR;

    if (!sg_add_commit_listener(_sdtx_make_commit_listener(ctx))) {
        _SDTX_ERROR(ADD_COMMIT_LISTENER_FAILED);
    }
    sg_pop_debug_group();
}

static void _sdtx_destroy_context(sdtx_context ctx_id) {
    _sdtx_context_t* ctx = _sdtx_lookup_context(ctx_id.id);
    if (ctx) {
        if (ctx->vertices.ptr) {
            _sdtx_free(ctx->vertices.ptr);
            ctx->vertices.ptr = 0;
            ctx->vertices.cap = 0;
            ctx->vertices.next = 0;
        }
        if (ctx->commands.ptr) {
            _sdtx_free(ctx->commands.ptr);
            ctx->commands.ptr = 0;
            ctx->commands.cap = 0;
            ctx->commands.next = 0;
        }
        sg_push_debug_group("sokol_debugtext");
        sg_destroy_buffer(ctx->vbuf);
        sg_destroy_pipeline(ctx->pip);
        sg_remove_commit_listener(_sdtx_make_commit_listener(ctx));
        sg_pop_debug_group();
        _sdtx_clear(ctx, sizeof(*ctx));
        _sdtx_pool_free_index(&_sdtx.context_pool.pool, _sdtx_slot_index(ctx_id.id));
    }
}

static bool _sdtx_is_default_context(sdtx_context ctx_id) {
    return ctx_id.id == SDTX_DEFAULT_CONTEXT.id;
}

// >>misc

// unpack linear 8x8 bits-per-pixel font data into 2D byte-per-pixel texture data
static void _sdtx_unpack_font(const sdtx_font_desc_t* font_desc, uint8_t* out_pixels) {
    SOKOL_ASSERT(font_desc->data.ptr);
    SOKOL_ASSERT((font_desc->data.size > 0) && ((font_desc->data.size % 8) == 0));
    SOKOL_ASSERT(font_desc->first_char <= font_desc->last_char);
    SOKOL_ASSERT((size_t)(((font_desc->last_char - font_desc->first_char) + 1) * 8) == font_desc->data.size);
    const uint8_t* ptr = (const uint8_t*) font_desc->data.ptr;
    for (int chr = font_desc->first_char; chr <= font_desc->last_char; chr++) {
        for (int line = 0; line < 8; line++) {
            uint8_t bits = *ptr++;
            for (int x = 0; x < 8; x++) {
                out_pixels[line*256*8 + chr*8 + x] = ((bits>>(7-x)) & 1) ? 0xFF : 0x00;
            }
        }
    }
}

static void _sdtx_setup_common(void) {
    _sdtx.fmt_buf_size = (uint32_t) _sdtx.desc.printf_buf_size + 1;
    _sdtx.fmt_buf = (char*) _sdtx_malloc_clear(_sdtx.fmt_buf_size);

    sg_push_debug_group("sokol-debugtext");
    sg_shader_desc shd_desc;
    _sdtx_clear(&shd_desc, sizeof(shd_desc));
    shd_desc.label = "sokol-debugtext-shader";
    shd_desc.attrs[0].glsl_name = "position";
    shd_desc.attrs[1].glsl_name = "texcoord0";
    shd_desc.attrs[2].glsl_name = "color0";
    shd_desc.attrs[0].hlsl_sem_name = "TEXCOORD";
    shd_desc.attrs[0].hlsl_sem_index = 0;
    shd_desc.attrs[1].hlsl_sem_name = "TEXCOORD";
    shd_desc.attrs[1].hlsl_sem_index = 1;
    shd_desc.attrs[2].hlsl_sem_name = "TEXCOORD";
    shd_desc.attrs[2].hlsl_sem_index = 2;
    shd_desc.views[0].texture.stage = SG_SHADERSTAGE_FRAGMENT;
    shd_desc.views[0].texture.image_type = SG_IMAGETYPE_2D;
    shd_desc.views[0].texture.sample_type = SG_IMAGESAMPLETYPE_FLOAT;
    shd_desc.views[0].texture.hlsl_register_t_n = 0;
    shd_desc.views[0].texture.msl_texture_n = 0;
    shd_desc.views[0].texture.wgsl_group1_binding_n = 64;
    shd_desc.samplers[0].stage = SG_SHADERSTAGE_FRAGMENT;
    shd_desc.samplers[0].sampler_type = SG_SAMPLERTYPE_FILTERING;
    shd_desc.samplers[0].hlsl_register_s_n = 0;
    shd_desc.samplers[0].msl_sampler_n = 0;
    shd_desc.samplers[0].wgsl_group1_binding_n = 80;
    shd_desc.texture_sampler_pairs[0].stage = SG_SHADERSTAGE_FRAGMENT;
    shd_desc.texture_sampler_pairs[0].view_slot = 0;
    shd_desc.texture_sampler_pairs[0].sampler_slot = 0;
    shd_desc.texture_sampler_pairs[0].glsl_name = "tex_smp";
	shd_desc.vertex_func.source = (const char*)_sdtx_vs_source_glsl410;
	shd_desc.fragment_func.source = (const char*)_sdtx_fs_source_glsl410;
    _sdtx.shader = sg_make_shader(&shd_desc);
    SOKOL_ASSERT(SG_INVALID_ID != _sdtx.shader.id);

    // unpack font data
    memset(_sdtx.font_pixels, 0xFF, sizeof(_sdtx.font_pixels));
    const int unpacked_font_size = (int) (sizeof(_sdtx.font_pixels) / SDTX_MAX_FONTS);
    for (int i = 0; i < SDTX_MAX_FONTS; i++) {
        if (_sdtx.desc.fonts[i].data.ptr) {
            _sdtx_unpack_font(&_sdtx.desc.fonts[i], &_sdtx.font_pixels[i * unpacked_font_size]);
        }
    }

    // create font image, texture view and sampler
    sg_image_desc img_desc;
    _sdtx_clear(&img_desc, sizeof(img_desc));
    img_desc.width = 256 * 8;
    img_desc.height = SDTX_MAX_FONTS * 8;
    img_desc.pixel_format = SG_PIXELFORMAT_R8;
    img_desc.data.mip_levels[0] = SG_RANGE(_sdtx.font_pixels);
    img_desc.label = "sdtx-font-texture";
    _sdtx.font_img = sg_make_image(&img_desc);
    SOKOL_ASSERT(SG_INVALID_ID != _sdtx.font_img.id);

    sg_view_desc view_desc;
    _sdtx_clear(&view_desc, sizeof(view_desc));
    view_desc.texture.image = _sdtx.font_img;
    view_desc.label = "sdtx-font-texture-view";
    _sdtx.font_view = sg_make_view(&view_desc);
    SOKOL_ASSERT(SG_INVALID_ID != _sdtx.font_view.id);

    sg_sampler_desc smp_desc;
    _sdtx_clear(&smp_desc, sizeof(smp_desc));
    smp_desc.min_filter = SG_FILTER_NEAREST;
    smp_desc.mag_filter = SG_FILTER_NEAREST;
    smp_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
    smp_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
    smp_desc.label = "sdtx-font-sampler";
    _sdtx.font_smp = sg_make_sampler(&smp_desc);
    SOKOL_ASSERT(SG_INVALID_ID != _sdtx.font_smp.id);

    sg_pop_debug_group();
}

static void _sdtx_discard_common(void) {
    sg_push_debug_group("sokol-debugtext");
    sg_destroy_sampler(_sdtx.font_smp);
    sg_destroy_view(_sdtx.font_view);
    sg_destroy_image(_sdtx.font_img);
    sg_destroy_shader(_sdtx.shader);
    if (_sdtx.fmt_buf) {
        _sdtx_free(_sdtx.fmt_buf);
        _sdtx.fmt_buf = 0;
    }
    sg_pop_debug_group();
}

static uint32_t _sdtx_pack_rgbab(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (uint32_t)(((uint32_t)a<<24)|((uint32_t)b<<16)|((uint32_t)g<<8)|r);
}

static float _sdtx_clamp(float v, float lo, float hi) {
    if (v < lo) return lo;
    else if (v > hi) return hi;
    else return v;
}

static uint32_t _sdtx_pack_rgbaf(float r, float g, float b, float a) {
    uint8_t r_u8 = (uint8_t) (_sdtx_clamp(r, 0.0f, 1.0f) * 255.0f);
    uint8_t g_u8 = (uint8_t) (_sdtx_clamp(g, 0.0f, 1.0f) * 255.0f);
    uint8_t b_u8 = (uint8_t) (_sdtx_clamp(b, 0.0f, 1.0f) * 255.0f);
    uint8_t a_u8 = (uint8_t) (_sdtx_clamp(a, 0.0f, 1.0f) * 255.0f);
    return _sdtx_pack_rgbab(r_u8, g_u8, b_u8, a_u8);
}

static void _sdtx_ctrl_char(_sdtx_context_t* ctx, uint8_t c) {
    switch (c) {
        case '\r':
            ctx->pos.x = 0.0f;
            break;
        case '\n':
            ctx->pos.x = 0.0f;
            ctx->pos.y += 1.0f;
            break;
        case '\t':
            ctx->pos.x = (ctx->pos.x - fmodf(ctx->pos.x, ctx->tab_width)) + ctx->tab_width;
            break;
        case ' ':
            ctx->pos.x += 1.0f;
            break;
    }
}

static _sdtx_vertex_t* _sdtx_next_vertex(_sdtx_context_t* ctx) {
    if ((ctx->vertices.next + 6) <= ctx->vertices.cap) {
        _sdtx_vertex_t* vx = &ctx->vertices.ptr[ctx->vertices.next];
        ctx->vertices.next += 6;
        return vx;
    } else {
        return 0;
    }
}

static _sdtx_command_t* _sdtx_cur_command(_sdtx_context_t* ctx) {
    if (ctx->commands.next > 0) {
        return &ctx->commands.ptr[ctx->commands.next - 1];
    } else {
        return 0;
    }
}

static _sdtx_command_t* _sdtx_next_command(_sdtx_context_t* ctx) {
    if (ctx->commands.next < ctx->commands.cap) {
        return &ctx->commands.ptr[ctx->commands.next++];
    } else {
        _SDTX_ERROR(COMMAND_BUFFER_FULL);
        return 0;
    }
}

static void _sdtx_set_layer(_sdtx_context_t* ctx, int layer_id) {
    ctx->cur_layer_id = layer_id;
    _sdtx_command_t* cur_cmd = _sdtx_cur_command(ctx);
    if (cur_cmd) {
        if ((cur_cmd->num_vertices == 0) || (cur_cmd->layer_id == layer_id)) {
            // no vertices recorded in current draw command, or layer hasn't changed, can just reuse this
            cur_cmd->layer_id = layer_id;
        } else {
            // layer has changed, need to start a new draw command
            _sdtx_command_t* next_cmd = _sdtx_next_command(ctx);
            if (next_cmd) {
                next_cmd->layer_id = layer_id;
                next_cmd->first_vertex = cur_cmd->first_vertex + cur_cmd->num_vertices;
                next_cmd->num_vertices = 0;
            }
        }
    } else {
        // first draw command in frame
        _sdtx_command_t* next_cmd = _sdtx_next_command(ctx);
        if (next_cmd) {
            next_cmd->layer_id = layer_id;
            next_cmd->first_vertex = 0;
            next_cmd->num_vertices = 0;
        }
    }
}

static void _sdtx_render_char(_sdtx_context_t* ctx, uint8_t c) {
    _sdtx_vertex_t* vx = _sdtx_next_vertex(ctx);
    _sdtx_command_t* cmd = _sdtx_cur_command(ctx);
    if (vx && cmd) {
        // update vertex count in current draw command
        cmd->num_vertices += 6;

        const float x0 = (ctx->origin.x + ctx->pos.x) * ctx->glyph_size.x;
        const float y0 = (ctx->origin.y + ctx->pos.y) * ctx->glyph_size.y;
        const float x1 = x0 + ctx->glyph_size.x;
        const float y1 = y0 + ctx->glyph_size.y;

        // glyph width and height in font texture space
        // NOTE: the '+1' and '-2' fixes texture bleeding into the neighboring font texture cell
        const uint16_t uvw = 0x10000 / 0x100;
        const uint16_t uvh = 0x10000 / SDTX_MAX_FONTS;
        const uint16_t u0 = (((uint16_t)c) * uvw) + 1;
        const uint16_t v0 = (((uint16_t)ctx->cur_font) * uvh) + 1;
        uint16_t u1 = (u0 + uvw) - 2;
        uint16_t v1 = (v0 + uvh) - 2;
        const uint32_t color = ctx->color;

        // write 6 vertices
        vx->x=x0; vx->y=y0; vx->u = u0; vx->v = v0; vx->color = color; vx++;
        vx->x=x1; vx->y=y0; vx->u = u1; vx->v = v0; vx->color = color; vx++;
        vx->x=x1; vx->y=y1; vx->u = u1; vx->v = v1; vx->color = color; vx++;

        vx->x=x0; vx->y=y0; vx->u = u0; vx->v = v0; vx->color = color; vx++;
        vx->x=x1; vx->y=y1; vx->u = u1; vx->v = v1; vx->color = color; vx++;
        vx->x=x0; vx->y=y1; vx->u = u0; vx->v = v1; vx->color = color; vx++;
    }
    ctx->pos.x += 1.0f;
}

static void _sdtx_put_char(_sdtx_context_t* ctx, char c) {
    uint8_t c_u8 = (uint8_t)c;
    if (c_u8 <= 32) {
        _sdtx_ctrl_char(ctx, c_u8);
    } else {
        _sdtx_render_char(ctx, c_u8);
    }
}

SOKOL_API_IMPL void _sdtx_draw_layer(_sdtx_context_t* ctx, int layer_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT(ctx);
    if ((ctx->vertices.next > 0) && (ctx->commands.next > 0)) {
        sg_push_debug_group("sokol-debugtext");

        if (ctx->update_frame_id != ctx->frame_id) {
            ctx->update_frame_id = ctx->frame_id;
            const sg_range range = { ctx->vertices.ptr, (size_t)ctx->vertices.next * sizeof(_sdtx_vertex_t) };
            sg_update_buffer(ctx->vbuf, &range);
        }

        sg_apply_pipeline(ctx->pip);
        sg_bindings bindings;
        _sdtx_clear(&bindings, sizeof(bindings));
        bindings.vertex_buffers[0] = ctx->vbuf;
        bindings.views[0] = _sdtx.font_view;
        bindings.samplers[0] = _sdtx.font_smp;
        sg_apply_bindings(&bindings);
        for (int cmd_index = 0; cmd_index < ctx->commands.next; cmd_index++) {
            const _sdtx_command_t* cmd = &ctx->commands.ptr[cmd_index];
            if (cmd->layer_id != layer_id) {
                continue;
            }
            SOKOL_ASSERT((cmd->num_vertices % 6) == 0);
            sg_draw(cmd->first_vertex, cmd->num_vertices, 1);
        }
        sg_pop_debug_group();
    }
}

static sdtx_desc_t _sdtx_desc_defaults(const sdtx_desc_t* desc) {
    SOKOL_ASSERT((desc->allocator.alloc_fn && desc->allocator.free_fn) || (!desc->allocator.alloc_fn && !desc->allocator.free_fn));
    sdtx_desc_t res = *desc;
    res.context_pool_size = _sdtx_def(res.context_pool_size, _SDTX_DEFAULT_CONTEXT_POOL_SIZE);
    res.printf_buf_size = _sdtx_def(res.printf_buf_size, _SDTX_DEFAULT_PRINTF_BUF_SIZE);
    for (int i = 0; i < SDTX_MAX_FONTS; i++) {
        if (res.fonts[i].data.ptr) {
            res.fonts[i].last_char = _sdtx_def(res.fonts[i].last_char, 255);
        }
    }
    res.context = _sdtx_context_desc_defaults(&res.context);
    SOKOL_ASSERT(res.context_pool_size > 0);
    SOKOL_ASSERT(res.printf_buf_size > 0);
    SOKOL_ASSERT(res.context.char_buf_size > 0);
    return res;
}

// >>public
SOKOL_API_IMPL void sdtx_setup(const sdtx_desc_t* desc) {
    SOKOL_ASSERT(desc);
    _sdtx_clear(&_sdtx, sizeof(_sdtx));
    _sdtx.init_cookie = _SDTX_INIT_COOKIE;
    _sdtx.desc = _sdtx_desc_defaults(desc);
    _sdtx_setup_context_pool(&_sdtx.desc);
    _sdtx_setup_common();
    _sdtx.def_ctx_id = sdtx_make_context(&_sdtx.desc.context);
    SOKOL_ASSERT(SDTX_DEFAULT_CONTEXT.id == _sdtx.def_ctx_id.id);
    sdtx_set_context(_sdtx.def_ctx_id);
}

SOKOL_API_IMPL void sdtx_shutdown(void) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    for (int i = 0; i < _sdtx.context_pool.pool.size; i++) {
        _sdtx_context_t* ctx = &_sdtx.context_pool.contexts[i];
        _sdtx_destroy_context(_sdtx_make_ctx_id(ctx->slot.id));
    }
    _sdtx_discard_common();
    _sdtx_discard_context_pool();
    _sdtx.init_cookie = 0;
}

SOKOL_API_IMPL sdtx_font_desc_t sdtx_font_kc853(void) {
    sdtx_font_desc_t desc = { { _sdtx_font_kc853, sizeof(_sdtx_font_kc853) }, 0, 255 };
    return desc;
}

SOKOL_API_IMPL sdtx_font_desc_t sdtx_font_kc854(void) {
    sdtx_font_desc_t desc = { { _sdtx_font_kc854, sizeof(_sdtx_font_kc854) }, 0, 255 };
    return desc;
}

SOKOL_API_IMPL sdtx_font_desc_t sdtx_font_z1013(void) {
    sdtx_font_desc_t desc = { { _sdtx_font_z1013, sizeof(_sdtx_font_z1013) }, 0, 255 };
    return desc;
}

SOKOL_API_IMPL sdtx_font_desc_t sdtx_font_cpc(void) {
    sdtx_font_desc_t desc = { { _sdtx_font_cpc, sizeof(_sdtx_font_cpc) }, 0, 255 };
    return desc;
}

SOKOL_API_IMPL sdtx_font_desc_t sdtx_font_c64(void) {
    sdtx_font_desc_t desc = { { _sdtx_font_c64, sizeof(_sdtx_font_c64) }, 0, 255 };
    return desc;
}

SOKOL_API_IMPL sdtx_font_desc_t sdtx_font_oric(void) {
    sdtx_font_desc_t desc = { { _sdtx_font_oric, sizeof(_sdtx_font_oric) }, 0, 255 };
    return desc;
}

SOKOL_API_IMPL sdtx_context sdtx_make_context(const sdtx_context_desc_t* desc) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT(desc);
    sdtx_context ctx_id = _sdtx_alloc_context();
    if (ctx_id.id != SG_INVALID_ID) {
        _sdtx_init_context(ctx_id, desc);
    } else {
        _SDTX_ERROR(CONTEXT_POOL_EXHAUSTED);
    }
    return ctx_id;
}

SOKOL_API_IMPL void sdtx_destroy_context(sdtx_context ctx_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    if (_sdtx_is_default_context(ctx_id)) {
        _SDTX_ERROR(CANNOT_DESTROY_DEFAULT_CONTEXT);
        return;
    }
    _sdtx_destroy_context(ctx_id);
    // re-validate the current context pointer (this will return a nullptr
    // if we just destroyed the current context)
    _sdtx.cur_ctx = _sdtx_lookup_context(_sdtx.cur_ctx_id.id);
}

SOKOL_API_IMPL void sdtx_set_context(sdtx_context ctx_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    if (_sdtx_is_default_context(ctx_id)) {
        _sdtx.cur_ctx_id = _sdtx.def_ctx_id;
    } else {
        _sdtx.cur_ctx_id = ctx_id;
    }
    // this may return a nullptr if the ctx_id handle is invalid
    _sdtx.cur_ctx = _sdtx_lookup_context(_sdtx.cur_ctx_id.id);
}

SOKOL_API_IMPL sdtx_context sdtx_get_context(void) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    return _sdtx.cur_ctx_id;
}

SOKOL_API_IMPL sdtx_context sdtx_default_context(void) {
    return SDTX_DEFAULT_CONTEXT;
}

SOKOL_API_IMPL void sdtx_layer(int layer_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        _sdtx_set_layer(ctx, layer_id);
    }
}

SOKOL_API_IMPL void sdtx_font(int font_index) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT((font_index >= 0) && (font_index < SDTX_MAX_FONTS));
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->cur_font = font_index;
    }
}

SOKOL_API_IMPL void sdtx_canvas(float w, float h) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT(!isnan(w));
    SOKOL_ASSERT(!isnan(h));
    SOKOL_ASSERT((w > 0.0f) && (h > 0.0f));
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->canvas_size.x = w;
        ctx->canvas_size.y = h;
        ctx->glyph_size.x = (8.0f / ctx->canvas_size.x);
        ctx->glyph_size.y = (8.0f / ctx->canvas_size.y);
        ctx->origin.x = 0.0f;
        ctx->origin.y = 0.0f;
        ctx->pos.x = 0.0f;
        ctx->pos.y = 0.0f;
    }
}

SOKOL_API_IMPL void sdtx_origin(float x, float y) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->origin.x = x;
        ctx->origin.y = y;
    }
}

SOKOL_API_IMPL void sdtx_home(void) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.x = 0.0f;
        ctx->pos.y = 0.0f;
    }
}

SOKOL_API_IMPL void sdtx_pos(float x, float y) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.x = x;
        ctx->pos.y = y;
    }
}

SOKOL_API_IMPL void sdtx_pos_x(float x) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.x = x;
    }
}

SOKOL_API_IMPL void sdtx_pos_y(float y) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.y = y;
    }
}

SOKOL_API_IMPL void sdtx_move(float dx, float dy) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.x += dx;
        ctx->pos.y += dy;
    }
}

SOKOL_API_IMPL void sdtx_move_x(float dx) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.x += dx;
    }
}

SOKOL_API_IMPL void sdtx_move_y(float dy) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.y += dy;
    }
}

SOKOL_API_IMPL void sdtx_crlf(void) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->pos.x = 0.0f;
        ctx->pos.y += 1.0f;
    }
}

SOKOL_API_IMPL void sdtx_color3b(uint8_t r, uint8_t g, uint8_t b) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->color = _sdtx_pack_rgbab(r, g, b, 255);
    }
}

SOKOL_API_IMPL void sdtx_color3f(float r, float g, float b) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->color = _sdtx_pack_rgbaf(r, g, b, 1.0f);
    }
}

SOKOL_API_IMPL void sdtx_color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->color = _sdtx_pack_rgbab(r, g, b, a);
    }
}

SOKOL_API_IMPL void sdtx_color4f(float r, float g, float b, float a) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->color = _sdtx_pack_rgbaf(r, g, b, a);
    }
}

SOKOL_API_IMPL void sdtx_color1i(uint32_t rgba) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        ctx->color = rgba;
    }
}

SOKOL_DEBUGTEXT_API_DECL void sdtx_putc(char chr) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        _sdtx_put_char(ctx, chr);
    }
}

SOKOL_DEBUGTEXT_API_DECL void sdtx_puts(const char* str) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        char chr;
        while (0 != (chr = *str++)) {
            _sdtx_put_char(ctx, chr);
        }
    }
}

SOKOL_DEBUGTEXT_API_DECL void sdtx_putr(const char* str, int len) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        for (int i = 0; i < len; i++) {
            char chr = str[i];
            if (0 == chr) {
                break;
            }
            _sdtx_put_char(ctx, chr);
        }
    }
}

SOKOL_DEBUGTEXT_API_DECL int sdtx_vprintf(const char* fmt, va_list args) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT(_sdtx.fmt_buf && (_sdtx.fmt_buf_size >= 2));
    int res = SOKOL_VSNPRINTF(_sdtx.fmt_buf, _sdtx.fmt_buf_size, fmt, args);
    // make sure we're 0-terminated in case we're on an old MSVC
    _sdtx.fmt_buf[_sdtx.fmt_buf_size-1] = 0;
    sdtx_puts(_sdtx.fmt_buf);
    return res;
}

SOKOL_DEBUGTEXT_API_DECL int sdtx_printf(const char* fmt, ...) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT(_sdtx.fmt_buf && (_sdtx.fmt_buf_size >= 2));
    va_list args;
    va_start(args, fmt);
    int res = SOKOL_VSNPRINTF(_sdtx.fmt_buf, _sdtx.fmt_buf_size, fmt, args);
    va_end(args);
    // make sure we're 0-terminated in case we're on an old MSVC
    _sdtx.fmt_buf[_sdtx.fmt_buf_size-1] = 0;
    sdtx_puts(_sdtx.fmt_buf);
    return res;
}

SOKOL_DEBUGTEXT_API_DECL sdtx_range sdtx_get_cleared_fmt_buffer(void) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    SOKOL_ASSERT(_sdtx.fmt_buf && (_sdtx.fmt_buf_size >= 2));
    memset(_sdtx.fmt_buf, 0, _sdtx.fmt_buf_size);
    sdtx_range res; _sdtx_clear(&res, sizeof(res));
    res.ptr = _sdtx.fmt_buf;
    res.size = _sdtx.fmt_buf_size - 1;
    return res;
}

SOKOL_API_IMPL void sdtx_draw(void) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        _sdtx_draw_layer(ctx, 0);
    }
}

SOKOL_API_IMPL void sdtx_context_draw(sdtx_context ctx_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx_lookup_context(ctx_id.id);
    if (ctx) {
        _sdtx_draw_layer(ctx, 0);
    }
}

SOKOL_API_IMPL void sdtx_draw_layer(int layer_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx.cur_ctx;
    if (ctx) {
        _sdtx_draw_layer(ctx, layer_id);
    }
}

SOKOL_API_IMPL void sdtx_context_draw_layer(sdtx_context ctx_id, int layer_id) {
    SOKOL_ASSERT(_SDTX_INIT_COOKIE == _sdtx.init_cookie);
    _sdtx_context_t* ctx = _sdtx_lookup_context(ctx_id.id);
    if (ctx) {
        _sdtx_draw_layer(ctx, layer_id);
    }
}
#endif // SOKOL_DEBUGTEXT_IMPL