#pragma once

#pragma once

// Platform detection using predefined macros
#if defined(_WIN32)
	/* Windows x64/x86 */
	#if defined(_WIN64)
		/* Windows x64  */
		#define KN_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define KN_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define KN_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define KN_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__EMSCRIPTEN__)
	#define KN_PLATFORM_WEB
#elif defined(__linux__)
	#define KN_PLATFORM_LINUX
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#if defined(KN_PLATFORM_WINDOWS) || defined(KN_PLATFORM_LINUX) || defined(KN_PLATFORM_MACOS)
	#define KN_PLATFORM_DESKTOP
	#include <glad/glad.h>
	#if defined(KINAI_OPENGL)
		#include <imgui/backends/imgui_impl_sdl3.h>
		#include <imgui/backends/imgui_impl_opengl3.h>
	#endif
	#if defined(_WIN32)
		#define WIN32_MEAN_AND_LEAN
		#include <windows.h>
		#include <direct.h>
	#elif defined(__APPLE__)
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>
		#include <curses.h>
	#else
		#include <GL/gl.h>
		#include <GL/glu.h>
	#endif
#elif defined(KN_PLATFORM_WEB)
	#include <emscripten/emscripten.h>
	#include <emscripten/html5.h>
	#include <emscripten/key_codes.h>
	#include <GLES3/gl3.h>
	#define glCreateBuffers			glGenBuffers
	#define glCreateVertexArrays	glGenVertexArrays
	#define glCreateTextures		glGenTextures
#endif

#if !defined(KINAI_OPENGL) && !defined(KINAI_HEADLESS)
# error "Please select a backend by defining KINAI_OPENGL or KINAI_HEADLESS"
#endif

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
#define BIT(x) (1 << x)

#define CGLM_USE_ANONYMOUS_STRUCT 1
#include <cglm/cglm.h>
#include <cglm/struct.h>

#include <sokol/sokol_gfx.h>
#include <SDL3/SDL.h>

typedef struct KnAppRenderEvent KnAppRenderEvent;
typedef struct KnAppTickEvent KnAppTickEvent;
typedef struct KnAppUpdateEvent KnAppUpdateEvent;
typedef struct KnApplication KnApplication;
typedef struct KnApplicationConfig KnApplicationConfig;
typedef struct KnBufferElement KnBufferElement;
typedef struct KnBufferLayout KnBufferLayout;
typedef struct KnCamera KnCamera;
typedef struct KnCircleVertex KnCircleVertex;
typedef struct KnEvent KnEvent;
typedef struct KnEventDispatcher KnEventDispatcher;
typedef struct KnFramebuffer KnFramebuffer;
typedef struct KnFramebufferAttachmentConfig KnFramebufferAttachmentConfig;
typedef struct KnFramebufferConfig KnFramebufferConfig;
typedef struct KnFramebufferTextureConfig KnFramebufferTextureConfig;
typedef struct KnImGuiLayer KnImGuiLayer;
typedef struct KnIndexBuffer KnIndexBuffer;
typedef struct KnInput KnInput;
typedef struct KnKeyEvent KnKeyEvent;
typedef struct KnKeyPressedEvent KnKeyPressedEvent;
typedef struct KnKeyReleasedEvent KnKeyReleasedEvent;
typedef struct KnLayer KnLayer;
typedef struct KnLayerStack KnLayerStack;
typedef struct KnLineVertex KnLineVertex;
typedef struct KnLog KnLog;
typedef struct KnMouseButtonEvent KnMouseButtonEvent;
typedef struct KnMouseButtonPressedEvent KnMouseButtonPressedEvent;
typedef struct KnMouseButtonReleasedEvent KnMouseButtonReleasedEvent;
typedef struct KnMouseMotionEvent KnMouseMotionEvent;
typedef struct KnMouseWheelEvent KnMouseWheelEvent;
typedef struct KnOrthographicCamera KnOrthographicCamera;
typedef struct KnOrthographicCameraController KnOrthographicCameraController;
typedef struct KnOrthographicCameraControllerConfig KnOrthographicCameraControllerConfig;
typedef struct KnPerspectiveCamera KnPerspectiveCamera;
typedef struct KnPerspectiveCameraController KnPerspectiveCameraController;
typedef struct KnPerspectiveCameraControllerConfig KnPerspectiveCameraControllerConfig;
typedef struct KnPipeline KnPipeline;
typedef struct KnQuadVertex KnQuadVertex;
typedef struct KnRenderCommand KnRenderCommand;
typedef struct KnRenderer KnRenderer;
typedef struct KnRenderer2D KnRenderer2D;
typedef struct KnRendererAPI KnRendererAPI;
typedef struct KnShader KnShader;
typedef struct KnShader2D KnShader2D;
typedef struct KnShaderLibrary KnShaderLibrary;
typedef struct KnTexture KnTexture;
typedef struct KnTexture2D KnTexture2D;
typedef struct KnTextureConfig KnTextureConfig;
typedef struct KnTime KnTime;
typedef struct KnTimer KnTimer;
typedef struct KnUniformBuffer KnUniformBuffer;
typedef struct KnVertexArray KnVertexArray;
typedef struct KnVertexBuffer KnVertexBuffer;
typedef struct KnWindow KnWindow;
typedef struct KnWindowCloseEvent KnWindowCloseEvent;
typedef struct KnWindowProps KnWindowProps;
typedef struct KnWindowResizeEvent KnWindowResizeEvent;

typedef enum KnEventCategory
{
	EventCategoryNone = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
} KnEventCategory;

typedef enum KnKN_CustomEventType
{
	KN_EVENT_WINDOW_TICK = SDL_EVENT_USER,
	KN_EVENT_WINDOW_UPDATE,
	KN_EVENT_WINDOW_RENDER,
	KN_EVENT_LAST
} KnKN_CustomEventType;

typedef enum KnFramebufferTextureFormat
{
	None = 0,
	RGBA8,
	RED_INTEGER,
	DEPTH24STENCIL8,
	Depth = DEPTH24STENCIL8
} KnFramebufferTextureFormat;

typedef enum KnImageFormat
{
	None = 0,
	R8,
	RGB8,
	RGBA8,
	RGBA32F
} KnImageFormat;

typedef enum KnShaderDataType
{
	None = 0,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool,
	UByte,
	UByte2,
	UByte3,
	UByte4,
	UInt,
	UInt2,
	UInt3,
	UInt4
} KnShaderDataType;

typedef void* KnScope;
typedef void* KnRef;
typedef uint16_t KnKeyCode;
typedef uint16_t KnMouseButton;
typedef uint32_t KnEventType;



void KnApplication_Application(const KnApplicationConfig* config);
void KnApplication_DestroyApplication();
KnLayer* KnApplication_PushLayer(KnLayer* layer);
KnLayer* KnApplication_PushOverlay(KnLayer* layer);
void KnApplication_Close();
KnWindow* KnApplication_GetWindow();
uint64_t KnApplication_GetFPS();
float KnApplication_GetDeltaTime();
KnImGuiLayer* KnApplication_GetImGuiLayer();
void KnApplication_Run();
KnApplication* KnApplication_Get();

void KnAppRenderEvent_AppRenderEvent();
void KnAppTickEvent_AppTickEvent();
void KnAppUpdateEvent_AppUpdateEvent();
void KnBufferElement_BufferElement();
void KnBufferElement_BufferElement2(KnShaderDataType type, void* name, bool normalized);
uint32_t KnBufferElement_GetComponentCount();
void KnBufferLayout_BufferLayout();
void KnBufferLayout_BufferLayout2(KnBufferElement* elements);
void KnBufferLayout_BufferLayout3(const KnBufferElement* elements);
uint32_t KnBufferLayout_GetStride();
const KnBufferElement* KnBufferLayout_GetElements();
KnBufferElement* KnBufferLayout_begin();
KnBufferElement* KnBufferLayout_end();
KnBufferElement* KnBufferLayout_begin2();
KnBufferElement* KnBufferLayout_end2();

void KnCamera_Camera();
void KnCamera_Camera2(const mat4s* projection_matrix);
void KnCamera_DestroyCamera();
const mat4s* KnCamera_GetProjectionMatrix();


void KnEvent_DestroyEvent();
KnEventType KnEvent_GetEventType();
const char* KnEvent_GetName();
int KnEvent_GetCategoryFlags();
void* KnEvent_ToString();
bool KnEvent_IsInCategory(KnEventCategory category);
void KnEventDispatcher_EventDispatcher(KnEvent* event);
bool KnEventDispatcher_Dispatch(const F* func);
void KnFramebuffer_DestroyFramebuffer();
void KnFramebuffer_Bind();
void KnFramebuffer_Unbind();
void KnFramebuffer_Resize(uint32_t width, uint32_t height);
int KnFramebuffer_ReadPixel(uint32_t attachmentIndex, int x, int y);
void KnFramebuffer_ClearAttachment(uint32_t attachmentIndex, int value);
uint32_t KnFramebuffer_GetColorAttachmentRendererID(uint32_t index);
const KnFramebufferConfig* KnFramebuffer_GetConfig();
uint32_t KnFramebuffer_GetRendererID();
KnFramebuffer* KnFramebuffer_Create(const KnFramebufferConfig* config);
void KnFramebufferAttachmentConfig_FramebufferAttachmentConfig();
void KnFramebufferAttachmentConfig_FramebufferAttachmentConfig2(KnFramebufferTextureConfig* attachments);

void KnFramebufferTextureConfig_FramebufferTextureConfig();
void KnFramebufferTextureConfig_FramebufferTextureConfig2(KnFramebufferTextureFormat format);
void KnImGuiLayer_ImGuiLayer();
void KnImGuiLayer_DestroyImGuiLayer();
void KnImGuiLayer_Begin();
void KnImGuiLayer_End();
void KnImGuiLayer_OnAttach();
void KnImGuiLayer_OnDetach();
void KnImGuiLayer_OnEvent(KnEvent* event);
void KnImGuiLayer_BlockEvents(bool block);
void KnIndexBuffer_DestroyIndexBuffer();
void KnIndexBuffer_Bind();
void KnIndexBuffer_Unbind();
uint32_t KnIndexBuffer_GetCount();
KnIndexBuffer* KnIndexBuffer_Create(const uint32_t* indices, uint32_t count);
bool KnInput_IsKeyPressed(KnKeyCode key);
bool KnInput_IsMouseButtonPressed(KnMouseButton button);
vec2s KnInput_GetMousePosition();
float KnInput_GetMouseX();
float KnInput_GetMouseY();

KnKeyCode KnKeyEvent_GetKeyCode();
void KnKeyEvent_EVENT_CLASS_CATEGORY(EventCategoryKeyboard| EventCategoryInput);
void KnKeyPressedEvent_KeyPressedEvent(const KnKeyCode keycode, bool repeat);
bool KnKeyPressedEvent_IsRepeat();
void* KnKeyPressedEvent_ToString();
void KnKeyReleasedEvent_KeyReleasedEvent(const KnKeyCode keycode);
void* KnKeyReleasedEvent_ToString();
void KnLayer_DestroyLayer();
void KnLayer_OnAttach();
void KnLayer_OnDetach();
void KnLayer_OnUpdate(float delta);
void KnLayer_OnImGuiRender();
void KnLayer_OnEvent(KnEvent* event);
void* KnLayer_GetName();
void KnLayerStack_LayerStack();
void KnLayerStack_DestroyLayerStack();
void KnLayerStack_PushLayer(KnLayer* layer);
void KnLayerStack_PopLayer(KnLayer* layer);
void KnLayerStack_PushOverlay(KnLayer* layer);
void KnLayerStack_PopOverlay(KnLayer* layer);
void KnLayerStack_Clear();
KnLayer* KnLayerStack_begin();
KnLayer* KnLayerStack_begin2();
KnLayer* KnLayerStack_end();
KnLayer* KnLayerStack_end2();
KnLayer* KnLayerStack_rbegin();
KnLayer* KnLayerStack_rbegin2();
KnLayer* KnLayerStack_rend();
KnLayer* KnLayerStack_rend2();

void KnLog_Init();
void KnLog_Trace(void* fmt, Args**... args);
void KnLog_Info(void* fmt, Args**... args);
void KnLog_Warn(void* fmt, Args**... args);
void KnLog_Error(void* fmt, Args**... args);
void KnLog_Critical(void* fmt, Args**... args);
void KnMouseButtonEvent_MouseButtonEvent();
KnMouseButton KnMouseButtonEvent_GetButton();
void KnMouseButtonEvent_EVENT_CLASS_CATEGORY(EventCategoryMouse|EventCategoryInput| EventCategoryMouseButton);
void KnMouseButtonPressedEvent_MouseButtonPressedEvent(const KnMouseButton button);
void KnMouseButtonPressedEvent_EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_BUTTON_DOWN None);
void* KnMouseButtonPressedEvent_ToString();
void KnMouseButtonReleasedEvent_MouseButtonReleasedEvent(const KnMouseButton button);
void KnMouseButtonReleasedEvent_EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_BUTTON_UP None);
void* KnMouseButtonReleasedEvent_ToString();
void KnMouseMotionEvent_MouseMotionEvent(const float x, const float y, const float rel_x, const float rel_y);
float KnMouseMotionEvent_GetX();
float KnMouseMotionEvent_GetY();
float KnMouseMotionEvent_GetXRelative();
float KnMouseMotionEvent_GetYRelative();
void KnMouseMotionEvent_EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_MOTION None);
void KnMouseMotionEvent_EVENT_CLASS_CATEGORY(EventCategoryMouse| EventCategoryInput);
void* KnMouseMotionEvent_ToString();
void KnMouseWheelEvent_MouseWheelEvent(const float x, const float y);
float KnMouseWheelEvent_GetXOffset();
float KnMouseWheelEvent_GetYOffset();
void KnMouseWheelEvent_EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_WHEEL None);
void KnMouseWheelEvent_EVENT_CLASS_CATEGORY(EventCategoryMouse| EventCategoryInput);
void* KnMouseWheelEvent_ToString();
void KnOrthographicCamera_OrthographicCamera(float left, float right, float bottom, float top);
void KnOrthographicCamera_DestroyOrthographicCamera();
void KnOrthographicCamera_SetProjection(float left, float right, float bottom, float top);
void KnOrthographicCamera_SetPosition(const vec3s* position);
void KnOrthographicCamera_SetRotation(const vec3s* rotation);
const vec3s* KnOrthographicCamera_GetPosition();
const vec3s* KnOrthographicCamera_GetRotation();
const mat4s* KnOrthographicCamera_GetProjectionMatrix();
const mat4s* KnOrthographicCamera_GetViewMatrix();
const mat4s* KnOrthographicCamera_GetViewProjectionMatrix();
void KnOrthographicCameraController_OrthographicCameraController(const KnOrthographicCameraControllerConfig* config);
void KnOrthographicCameraController_OnUpdate(float delta);
void KnOrthographicCameraController_OnEvent(KnEvent* event);
void KnOrthographicCameraController_OnResize(float width, float height);
KnOrthographicCamera* KnOrthographicCameraController_GetCamera();
const KnOrthographicCamera* KnOrthographicCameraController_GetCamera2();

void KnParser_Parser(void* filepath);
KN_INLINE void* KnParser_YELLOW(const void** s);
KN_INLINE void* KnParser_CYAN(const void** s);
KN_INLINE void* KnParser_MAGENTA(const void** s);
KN_INLINE void* KnParser_RED(const void** s);
KN_INLINE void* KnParser_WHITE(const void** s);
KN_INLINE bool KnParser_iterator_equals(void** it, const token_type* t);
KN_INLINE bool KnParser_iterator_equals2(void** it, const void** s);
void KnPerspectiveCamera_PerspectiveCamera();
void KnPerspectiveCamera_PerspectiveCamera2(float viewport_width, float viewport_height, float fov, float near_clip, float far_clip);
void KnPerspectiveCamera_DestroyPerspectiveCamera();
void KnPerspectiveCamera_OnUpdate();
void KnPerspectiveCamera_SetViewportSize(float width, float height);
void KnPerspectiveCamera_SetDistance(float distance);
void KnPerspectiveCamera_SetPosition(const vec3s* position);
float KnPerspectiveCamera_GetDistance();
const mat4s* KnPerspectiveCamera_GetViewMatrix();
mat4s KnPerspectiveCamera_GetViewProjectionMatrix();
vec3s KnPerspectiveCamera_GetUpDirection();
vec3s KnPerspectiveCamera_GetRightDirection();
vec3s KnPerspectiveCamera_GetForwardDirection();
versors KnPerspectiveCamera_GetOrientation();
const vec3s* KnPerspectiveCamera_GetPosition();
float KnPerspectiveCamera_GetPitch();
float KnPerspectiveCamera_GetYaw();
bool KnPerspectiveCamera_OnMouseWheel(KnMouseWheelEvent* e);
bool KnPerspectiveCamera_OnMouseMotion(KnMouseMotionEvent* event);
void KnPerspectiveCameraController_PerspectiveCameraController(const KnPerspectiveCameraControllerConfig* config);
void KnPerspectiveCameraController_OnUpdate(float delta);
void KnPerspectiveCameraController_OnEvent(KnEvent* e);
void KnPerspectiveCameraController_OnResize(float width, float height);
KnPerspectiveCamera* KnPerspectiveCameraController_GetCamera();
const KnPerspectiveCamera* KnPerspectiveCameraController_GetCamera2();
bool KnPerspectiveCameraController_IsCursorLocked();
void KnPerspectiveCameraController_SetCursorLock(bool enabled);
bool KnPerspectiveCameraController_IsRotationEnabled();
void KnPerspectiveCameraController_SetRotationEnabled(bool enabled);



void KnRenderCommand_Init();
void KnRenderCommand_SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void KnRenderCommand_SetClearColor(const vec4s* color);
void KnRenderCommand_SetClearColor2(float r, float g, float b, float a);
void KnRenderCommand_SetClearColor3(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void KnRenderCommand_Clear();
void KnRenderCommand_DrawIndexed(const KnVertexArray* vertex_array, uint32_t index_count);
void KnRenderCommand_DrawLines(const KnVertexArray* vertex_array, uint32_t vertex_count);
void KnRenderCommand_DrawTriangles(const KnVertexArray* vertex_array, uint32_t vertex_count);
void KnRenderCommand_SetLineWidth(float width);
void KnRenderer_Init();
void KnRenderer_Shutdown();
void KnRenderer_BeginFrame(const KnPerspectiveCamera* camera);
void KnRenderer_EndFrame();
void KnRenderer_OnWindowResize(uint32_t width, uint32_t height);
void KnRenderer_Submit(const KnShader* shader, const KnVertexArray* vertex_array, const mat4s* transform);
void KnRenderer_SubmitTriangles(const KnShader* shader, const KnVertexArray* vertex_array, uint32_t vertex_count, const mat4s* transform);
void KnRenderer2D_BeginFrame(const KnCamera* camera, const mat4s* transform);
void KnRenderer2D_BeginFrame2(const KnOrthographicCamera* camera);
void KnRenderer2D_BeginFrame3(const KnPerspectiveCamera* camera);
void KnRenderer2D_Flush();
void KnRenderer2D_UpdateViewport();
void KnRenderer2D_EndFrame();
void KnRenderer2D_DrawCircle(const mat4s* transform, const vec4s* color, float thickness, float fade);
void KnRenderer2D_DrawLine(const vec3s* p0, vec3s* p1, const vec4s* color);
float KnRenderer2D_GetLineWidth();
void KnRenderer2D_SetLineWidth(float width);
void KnRenderer2D_DrawQuad(const vec2s* position, const vec2s* size, const vec4s* color);
void KnRenderer2D_DrawQuad2(const vec3s* position, const vec2s* size, const vec4s* color);
void KnRenderer2D_DrawQuad3(const vec2s* position, const vec2s* size, const KnTexture2D* texture, const vec4s* tint_color);
void KnRenderer2D_DrawQuad4(const vec3s* position, const vec2s* size, const KnTexture2D* texture, const vec4s* tint_color);
void KnRenderer2D_DrawQuad5(const vec2s* position, const vec2s* size, const KnTexture2D* texture, const vec2s* uvStart, const vec2s* uvEnd, const vec4s* tint_color);
void KnRenderer2D_DrawQuad6(const vec3s* position, const vec2s* size, const KnTexture2D* texture, const vec2s* uvStart, const vec2s* uvEnd, const vec4s* tint_color);
void KnRenderer2D_DrawQuad7(const mat4s* transform, const vec4s* color);
void KnRenderer2D_DrawQuad8(const mat4s* transform, const KnTexture2D* texture);
void KnRenderer2D_DrawQuad9(const mat4s* transform, const KnTexture2D* texture, const vec2s* uvStart, const vec2s* uvEnd, const vec4s* tint_color);
void KnRenderer2D_DrawRotatedQuad(const vec2s* position, const vec2s* size, float rotation, const vec4s* color);
void KnRenderer2D_DrawRotatedQuad2(const vec3s* position, const vec2s* size, float rotation, const vec4s* color);
void KnRenderer2D_DrawRotatedQuad3(const vec2s* position, const vec2s* size, float rotation, const KnTexture2D* texture, const vec4s* tintColor);
void KnRenderer2D_DrawRotatedQuad4(const vec3s* position, const vec2s* size, float rotation, const KnTexture2D* texture, const vec4s* tintColor);
void KnRenderer2D_DrawRect(const vec3s* position, const vec2s* size, const vec4s* color);
void KnRenderer2D_DrawRect2(const mat4s* transform, const vec4s* color);
KnShader2D* KnRenderer2D_MakeShader(void* program_name, void* vertexSrc, void* fragmentSrc);
void KnRenderer2D_SetQuadShader(KnShader2D* shader);
void KnRenderer2D_ResetQuadShader();
void KnRenderer2D_Init();
void KnRenderer2D_Shutdown();
KnStatistics* KnRenderer2D_GetStats();
void KnRendererAPI_DestroyRendererAPI();
void KnRendererAPI_Init();
void KnRendererAPI_SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
void KnRendererAPI_SetClearColor(const vec4s* color);
void KnRendererAPI_Clear();
void KnRendererAPI_DrawIndexed(const KnVertexArray* vertex_array, uint32_t index_count);
void KnRendererAPI_DrawLines(const KnVertexArray* vertex_array, uint32_t vertex_count);
void KnRendererAPI_DrawTriangles(const KnVertexArray* vertexArray, uint32_t vertexCount);
void KnRendererAPI_SetLineWidth(float width);
KnRendererAPI* KnRendererAPI_Create();
void KnShader_DestroyShader();
void KnShader_Bind();
void KnShader_Unbind();
void KnShader_SetInt(void* name, int value);
void KnShader_SetIntArray(void* name, int* values, uint32_t count);
void KnShader_SetFloat(void* name, float value);
void KnShader_SetFloat2(void* name, const vec2s* value);
void KnShader_SetFloat3(void* name, const vec3s* value);
void KnShader_SetFloat4(void* name, const vec4s* value);
void KnShader_SetMat4(void* name, const mat4s* value);
void* KnShader_GetName();
KnShader* KnShader_Create(void* filepath, void* program_name);
KnShader* KnShader_Create2(void* name, void* vertexSrc, void* fragmentSrc);
KnShader* KnRenderer2D::Shader2D_GetShader();

void KnShaderLibrary_Add(void* name, const KnShader* shader);
void KnShaderLibrary_Add2(const KnShader* shader);
KnShader* KnShaderLibrary_Load(void* filepath, void* name);
KnShader* KnShaderLibrary_Load2(void* name, void* vertexSrc, void* fragmentSrc);
KnShader* KnShaderLibrary_Get(void* name);
bool KnShaderLibrary_Exists(void* name);
uint32_t KnRenderer2D::Statistics_GetTotalVertexCount();
uint32_t KnRenderer2D::Statistics_GetTotalIndexCount();
void KnRenderer2D::Statistics_Reset();
uint32_t KnRenderer2D::Statistics_GetDrawCalls();
uint32_t KnRenderer2D::Statistics_GetQuadCount();
void KnTexture_DestroyTexture();
const KnTextureConfig* KnTexture_GetConfig();
uint32_t KnTexture_GetWidth();
uint32_t KnTexture_GetHeight();
uint32_t KnTexture_GetRendererID();
void* KnTexture_GetPath();
void KnTexture_SetData(void* data, uint32_t size);
void KnTexture_Bind(uint32_t slot);
bool KnTexture_IsLoaded();
bool KnTexture_equals(const KnTexture* other);
KnTexture2D* KnTexture2D_Create(const KnTextureConfig* config);
KnTexture2D* KnTexture2D_Create2(void* path, GLenum min_filter, GLenum max_filter);


void KnTimer_Timer();
void KnTimer_Reset();
float KnTimer_ElapsedSeconds();
float KnTimer_ElapsedMS();
void KnTokenBase_TokenBase(Tp t, void* w, uint32_t r, uint32_t c);
void KnUniformBuffer_DestroyUniformBuffer();
void KnUniformBuffer_SetData(const void* data, uint32_t size, uint32_t offset);
KnUniformBuffer* KnUniformBuffer_Create(uint32_t size, uint32_t binding);
void KnVertexArray_DestroyVertexArray();
void KnVertexArray_Bind();
void KnVertexArray_Unbind();
void KnVertexArray_AddVertexBuffer(const KnVertexBuffer* vertex_buffer);
void KnVertexArray_SetIndexBuffer(const KnIndexBuffer* index_buffer);
const KnVertexBuffer* KnVertexArray_GetVertexBuffers();
const KnIndexBuffer* KnVertexArray_GetIndexBuffer();
KnVertexArray* KnVertexArray_Create();
void KnVertexBuffer_DestroyVertexBuffer();
void KnVertexBuffer_Bind();
void KnVertexBuffer_Unbind();
void KnVertexBuffer_SetData(const void* data, uint32_t size);
void KnVertexBuffer_SetLayout(const KnBufferLayout* layout);
const KnBufferLayout* KnVertexBuffer_GetLayout();
KnVertexBuffer* KnVertexBuffer_Create(uint32_t size);
KnVertexBuffer* KnVertexBuffer_Create2(const void* vertices, uint32_t size);
void KnWindow_DestroyWindow();
void KnWindow_OnUpdate();
void* KnWindow_GetNativeWindow();
ivec2s KnWindow_GetSize();
uint32_t KnWindow_GetWidth();
uint32_t KnWindow_GetHeight();
bool KnWindow_GetRelativeMouseMode();
bool KnWindow_IsFocused();
bool KnWindow_IsHovered();
sg_environment KnWindow_GetSokolEnvironment();
sg_swapchain KnWindow_GetSokolSwapchain();
bool KnWindow_IsVSync();
void KnWindow_SetVSync(bool enabled);
void KnWindow_SetEventCallback(const EventCallback* callback);
void KnWindow_SetTitle(void* title);
void KnWindow_SetRelativeMouseMode(bool enabled);
void KnWindow_WarpMouse(float x, float y);
KnWindow* KnWindow_Create(const KnWindowProps* props);
void KnWindowCloseEvent_WindowCloseEvent();
void KnWindowCloseEvent_EVENT_CLASS_TYPE(SDL_EVENT_WINDOW_CLOSE_REQUESTED None);
void KnWindowCloseEvent_EVENT_CLASS_CATEGORY(EventCategoryApplication None);
void KnWindowProps_WindowProps(void* title, uint32_t width, uint32_t height, bool fullscreen, bool no_vsync);
void KnWindowResizeEvent_WindowResizeEvent(uint32_t width, uint32_t height);
uint32_t KnWindowResizeEvent_GetWidth();
uint32_t KnWindowResizeEvent_GetHeight();
void* KnWindowResizeEvent_ToString();
void KnWindowResizeEvent_EVENT_CLASS_TYPE(SDL_EVENT_WINDOW_RESIZED None);
void KnWindowResizeEvent_EVENT_CLASS_CATEGORY(EventCategoryApplication None);
