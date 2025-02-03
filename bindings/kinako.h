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

#define CGLM_USE_ANONYMOUS_STRUCT 1
#include <cglm/cglm.h>
#include <cglm/struct.h>

typedef uint16_t	KnKeyCode;
typedef uint16_t	KnMouseButton;
typedef uint32_t	KN_EventType;
typedef struct KnAppRenderEvent KnAppRenderEvent;
typedef struct KnAppTickEvent KnAppTickEvent;
typedef struct KnAppUpdateEvent KnAppUpdateEvent;
typedef struct KnApplication KnApplication;
typedef struct KnBufferLayout KnBufferLayout;
typedef struct KnCamera KnCamera;
typedef struct KnEvent KnEvent;
typedef struct KnEventDispatcher KnEventDispatcher;
typedef struct KnFramebuffer KnFramebuffer;
typedef struct KnImGuiLayer KnImGuiLayer;
typedef struct KnIndexBuffer KnIndexBuffer;
typedef struct KnInput KnInput;
typedef struct KnKeyEvent KnKeyEvent;
typedef struct KnKeyPressedEvent KnKeyPressedEvent;
typedef struct KnKeyReleasedEvent KnKeyReleasedEvent;
typedef struct KnLayer KnLayer;
typedef struct KnLayerStack KnLayerStack;
typedef struct KnLog KnLog;
typedef struct KnMouseButtonEvent KnMouseButtonEvent;
typedef struct KnMouseButtonPressedEvent KnMouseButtonPressedEvent;
typedef struct KnMouseButtonReleasedEvent KnMouseButtonReleasedEvent;
typedef struct KnMouseMotionEvent KnMouseMotionEvent;
typedef struct KnMouseWheelEvent KnMouseWheelEvent;
typedef struct KnOrthographicCamera KnOrthographicCamera;
typedef struct KnOrthographicCameraController KnOrthographicCameraController;
typedef struct KnPerspectiveCamera KnPerspectiveCamera;
typedef struct KnPerspectiveCameraController KnPerspectiveCameraController;
typedef struct KnRenderCommand KnRenderCommand;
typedef struct KnRenderer KnRenderer;
typedef struct KnRenderer2D KnRenderer2D;
typedef struct KnRenderer2D_Shader2D KnRenderer2D_Shader2D;
typedef struct KnRenderer2D_Statistics KnRenderer2D_Statistics;
typedef struct KnRendererAPI KnRendererAPI;
typedef struct KnShader KnShader;
typedef struct KnShaderLibrary KnShaderLibrary;
typedef struct KnTexture KnTexture;
typedef struct KnTexture2D KnTexture2D;
typedef struct KnTimer KnTimer;
typedef struct KnUniformBuffer KnUniformBuffer;
typedef struct KnVertexArray KnVertexArray;
typedef struct KnVertexBuffer KnVertexBuffer;
typedef struct KnWindow KnWindow;
typedef struct KnWindowCloseEvent KnWindowCloseEvent;
typedef struct KnWindowResizeEvent KnWindowResizeEvent;
typedef struct KnApplicationConfig KnApplicationConfig;
typedef struct KnBufferElement KnBufferElement;
typedef struct KnCircleVertex KnCircleVertex;
typedef struct KnFramebufferAttachmentConfig KnFramebufferAttachmentConfig;
typedef struct KnFramebufferConfig KnFramebufferConfig;
typedef struct KnFramebufferTextureConfig KnFramebufferTextureConfig;
typedef struct KnLineVertex KnLineVertex;
typedef struct KnOrthographicCameraControllerConfig KnOrthographicCameraControllerConfig;
typedef struct KnPerspectiveCameraControllerConfig KnPerspectiveCameraControllerConfig;
typedef struct KnPipeline KnPipeline;
typedef struct KnQuadVertex KnQuadVertex;
typedef struct KnRenderer2D_BuiltinUniforms KnRenderer2D_BuiltinUniforms;
typedef struct KnRenderer2D_CameraUniforms KnRenderer2D_CameraUniforms;
typedef struct KnShader2D KnShader2D;
typedef struct KnTextureConfig KnTextureConfig;
typedef struct KnTime KnTime;
typedef struct KnWindowProps KnWindowProps;

KINAKO_API KnApplication* KnApplication_Application(ApplicationConfig *config);
KINAKO_API void KnApplication_DestroyApplication(KnApplication* self);
KINAKO_API KnLayer * KnApplication_PushLayer(KnApplication* self, Layer *layer);
KINAKO_API KnLayer * KnApplication_PushOverlay(KnApplication* self, Layer *layer);
KINAKO_API void KnApplication_Close(KnApplication* self);
KINAKO_API KnWindow* KnApplication_GetWindow(KnApplication* self); // [retref]
KINAKO_API uint64_t KnApplication_GetFPS(const KnApplication* self);
KINAKO_API float KnApplication_GetDeltaTime(const KnApplication* self);
KINAKO_API KnImGuiLayer * KnApplication_GetImGuiLayer(const KnApplication* self);
KINAKO_API void KnApplication_Run(KnApplication* self);
KINAKO_API KnApplication* KnApplication_Get(void); // [retref]
KINAKO_API KnBufferLayout* KnBufferLayout_BufferLayout(void);
KINAKO_API KnBufferLayout* KnBufferLayout_BufferLayout(std::initializer_list< BufferElement > elements);
KINAKO_API KnBufferLayout* KnBufferLayout_BufferLayout(std::vector< BufferElement > *elements);
KINAKO_API uint32_t KnBufferLayout_GetStride(const KnBufferLayout* self);
KINAKO_API const KnBufferElement** KnBufferLayout_GetElements(const KnBufferLayout* self); // [retref]
KINAKO_API KnCamera* KnCamera_Camera(void);
KINAKO_API KnCamera* KnCamera_Camera(glm::mat4 *projection_matrix);
KINAKO_API void KnCamera_DestroyCamera(KnCamera* self);
KINAKO_API const glm::mat4* KnCamera_GetProjectionMatrix(const KnCamera* self); // [retref]
KINAKO_API void KnEvent_DestroyEvent(KnEvent* self);
KINAKO_API KN_EventType KnEvent_GetEventType(const KnEvent* self);
KINAKO_API const char * KnEvent_GetName(const KnEvent* self);
KINAKO_API int KnEvent_GetCategoryFlags(const KnEvent* self);
KINAKO_API const char* KnEvent_ToString(const KnEvent* self);
KINAKO_API bool KnEvent_IsInCategory(KnEvent* self, EventCategory category);
KINAKO_API KnEventDispatcher* KnEventDispatcher_EventDispatcher(Event *event);
KINAKO_API bool KnEventDispatcher_Dispatch(const KnEventDispatcher* self, F *func);
KINAKO_API void KnFramebuffer_DestroyFramebuffer(KnFramebuffer* self);
KINAKO_API void KnFramebuffer_Bind(KnFramebuffer* self);
KINAKO_API void KnFramebuffer_Unbind(KnFramebuffer* self);
KINAKO_API void KnFramebuffer_Resize(KnFramebuffer* self, uint32_t width, uint32_t height);
KINAKO_API int KnFramebuffer_ReadPixel(KnFramebuffer* self, uint32_t attachmentIndex, int x, int y);
KINAKO_API void KnFramebuffer_ClearAttachment(KnFramebuffer* self, uint32_t attachmentIndex, int value);
KINAKO_API uint32_t KnFramebuffer_GetColorAttachmentRendererID(KnFramebuffer* self, uint32_t index=0 const );
KINAKO_API const KnFramebufferConfig* KnFramebuffer_GetConfig(const KnFramebuffer* self); // [retref]
KINAKO_API uint32_t KnFramebuffer_GetRendererID(const KnFramebuffer* self);
KINAKO_API KnFramebuffer* KnFramebuffer_Create(FramebufferConfig *config);
KINAKO_API KnImGuiLayer* KnImGuiLayer_ImGuiLayer(void);
KINAKO_API void KnImGuiLayer_DestroyImGuiLayer(KnImGuiLayer* self);
KINAKO_API void KnImGuiLayer_Begin(KnImGuiLayer* self);
KINAKO_API void KnImGuiLayer_End(KnImGuiLayer* self);
KINAKO_API void KnImGuiLayer_OnAttach(KnImGuiLayer* self);
KINAKO_API void KnImGuiLayer_OnDetach(KnImGuiLayer* self);
KINAKO_API void KnImGuiLayer_OnEvent(KnImGuiLayer* self, Event *event override);
KINAKO_API void KnImGuiLayer_BlockEvents(KnImGuiLayer* self, bool block);
KINAKO_API void KnIndexBuffer_DestroyIndexBuffer(KnIndexBuffer* self);
KINAKO_API void KnIndexBuffer_Bind(const KnIndexBuffer* self);
KINAKO_API void KnIndexBuffer_Unbind(const KnIndexBuffer* self);
KINAKO_API uint32_t KnIndexBuffer_GetCount(const KnIndexBuffer* self);
KINAKO_API KnIndexBuffer* KnIndexBuffer_Create(uint32_t *indices, uint32_t count);
KINAKO_API KnKeyCode KnKeyEvent_GetKeyCode(const KnKeyEvent* self);
KINAKO_API void KnLayer_DestroyLayer(KnLayer* self);
KINAKO_API void KnLayer_OnAttach(KnLayer* self);
KINAKO_API void KnLayer_OnDetach(KnLayer* self);
KINAKO_API void KnLayer_OnUpdate(KnLayer* self, float delta);
KINAKO_API void KnLayer_OnImGuiRender(KnLayer* self);
KINAKO_API void KnLayer_OnEvent(KnLayer* self, Event *event);
KINAKO_API const const char** KnLayer_GetName(const KnLayer* self); // [retref]
KINAKO_API KnLayerStack* KnLayerStack_LayerStack(void);
KINAKO_API void KnLayerStack_DestroyLayerStack(KnLayerStack* self);
KINAKO_API void KnLayerStack_PushLayer(KnLayerStack* self, Layer *layer);
KINAKO_API void KnLayerStack_PopLayer(KnLayerStack* self, Layer *layer);
KINAKO_API void KnLayerStack_PushOverlay(KnLayerStack* self, Layer *layer);
KINAKO_API void KnLayerStack_PopOverlay(KnLayerStack* self, Layer *layer);
KINAKO_API void KnLayerStack_Clear(KnLayerStack* self);
KINAKO_API void KnLog_Init(void);
KINAKO_API void KnLog_Trace(char_view fmt, Args **... args);
KINAKO_API void KnLog_Info(char_view fmt, Args **... args);
KINAKO_API void KnLog_Warn(char_view fmt, Args **... args);
KINAKO_API void KnLog_Error(char_view fmt, Args **... args);
KINAKO_API void KnLog_Critical(char_view fmt, Args **... args);
KINAKO_API KnMouseButtonEvent* KnMouseButtonEvent_MouseButtonEvent(void);
KINAKO_API KnMouseButton KnMouseButtonEvent_GetButton(const KnMouseButtonEvent* self);
KINAKO_API KnMouseMotionEvent* KnMouseMotionEvent_MouseMotionEvent(float x, float y, float rel_x, float rel_y);
KINAKO_API float KnMouseMotionEvent_GetX(const KnMouseMotionEvent* self);
KINAKO_API float KnMouseMotionEvent_GetY(const KnMouseMotionEvent* self);
KINAKO_API float KnMouseMotionEvent_GetXRelative(const KnMouseMotionEvent* self);
KINAKO_API float KnMouseMotionEvent_GetYRelative(const KnMouseMotionEvent* self);
KINAKO_API const char* KnMouseMotionEvent_ToString(const KnMouseMotionEvent* self);
KINAKO_API KnMouseWheelEvent* KnMouseWheelEvent_MouseWheelEvent(float x, float y);
KINAKO_API float KnMouseWheelEvent_GetXOffset(const KnMouseWheelEvent* self);
KINAKO_API float KnMouseWheelEvent_GetYOffset(const KnMouseWheelEvent* self);
KINAKO_API const char* KnMouseWheelEvent_ToString(const KnMouseWheelEvent* self);
KINAKO_API KnOrthographicCamera* KnOrthographicCamera_OrthographicCamera(float left, float right, float bottom, float top);
KINAKO_API void KnOrthographicCamera_DestroyOrthographicCamera(KnOrthographicCamera* self);
KINAKO_API void KnOrthographicCamera_SetProjection(KnOrthographicCamera* self, float left, float right, float bottom, float top);
KINAKO_API void KnOrthographicCamera_SetPosition(const KnOrthographicCamera* self, glm::vec3 *position);
KINAKO_API void KnOrthographicCamera_SetRotation(const KnOrthographicCamera* self, glm::vec3 *rotation);
KINAKO_API const glm::vec3* KnOrthographicCamera_GetPosition(const KnOrthographicCamera* self); // [retref]
KINAKO_API const glm::vec3* KnOrthographicCamera_GetRotation(const KnOrthographicCamera* self); // [retref]
KINAKO_API const glm::mat4* KnOrthographicCamera_GetProjectionMatrix(const KnOrthographicCamera* self); // [retref]
KINAKO_API const glm::mat4* KnOrthographicCamera_GetViewMatrix(const KnOrthographicCamera* self); // [retref]
KINAKO_API const glm::mat4* KnOrthographicCamera_GetViewProjectionMatrix(const KnOrthographicCamera* self); // [retref]
KINAKO_API KnOrthographicCameraController* KnOrthographicCameraController_OrthographicCameraController(OrthographicCameraControllerConfig *config=OrthographicCameraControllerConfig());
KINAKO_API void KnOrthographicCameraController_OnUpdate(KnOrthographicCameraController* self, float delta);
KINAKO_API void KnOrthographicCameraController_OnEvent(KnOrthographicCameraController* self, Event *event);
KINAKO_API void KnOrthographicCameraController_OnResize(KnOrthographicCameraController* self, float width, float height);
KINAKO_API KnOrthographicCamera* KnOrthographicCameraController_GetCamera(KnOrthographicCameraController* self); // [retref]
KINAKO_API const KnOrthographicCamera* KnOrthographicCameraController_GetCamera(const KnOrthographicCameraController* self); // [retref]
KINAKO_API KnPerspectiveCamera* KnPerspectiveCamera_PerspectiveCamera(void);
KINAKO_API KnPerspectiveCamera* KnPerspectiveCamera_PerspectiveCamera(float viewport_width, float viewport_height, float fov, float near_clip, float far_clip);
KINAKO_API void KnPerspectiveCamera_DestroyPerspectiveCamera(KnPerspectiveCamera* self);
KINAKO_API void KnPerspectiveCamera_OnUpdate(KnPerspectiveCamera* self);
KINAKO_API void KnPerspectiveCamera_SetViewportSize(KnPerspectiveCamera* self, float width, float height);
KINAKO_API void KnPerspectiveCamera_SetDistance(KnPerspectiveCamera* self, float distance);
KINAKO_API void KnPerspectiveCamera_SetPosition(const KnPerspectiveCamera* self, glm::vec3 *position);
KINAKO_API float KnPerspectiveCamera_GetDistance(const KnPerspectiveCamera* self);
KINAKO_API const glm::mat4* KnPerspectiveCamera_GetViewMatrix(const KnPerspectiveCamera* self); // [retref]
KINAKO_API glm::mat4 KnPerspectiveCamera_GetViewProjectionMatrix(const KnPerspectiveCamera* self);
KINAKO_API glm::vec3 KnPerspectiveCamera_GetUpDirection(const KnPerspectiveCamera* self);
KINAKO_API glm::vec3 KnPerspectiveCamera_GetRightDirection(const KnPerspectiveCamera* self);
KINAKO_API glm::vec3 KnPerspectiveCamera_GetForwardDirection(const KnPerspectiveCamera* self);
KINAKO_API glm::quat KnPerspectiveCamera_GetOrientation(const KnPerspectiveCamera* self);
KINAKO_API const glm::vec3* KnPerspectiveCamera_GetPosition(const KnPerspectiveCamera* self); // [retref]
KINAKO_API float KnPerspectiveCamera_GetPitch(const KnPerspectiveCamera* self);
KINAKO_API float KnPerspectiveCamera_GetYaw(const KnPerspectiveCamera* self);
KINAKO_API bool KnPerspectiveCamera_OnMouseWheel(KnPerspectiveCamera* self, MouseWheelEvent *e);
KINAKO_API bool KnPerspectiveCamera_OnMouseMotion(KnPerspectiveCamera* self, MouseMotionEvent *event);
KINAKO_API KnPerspectiveCameraController* KnPerspectiveCameraController_PerspectiveCameraController(PerspectiveCameraControllerConfig *config=PerspectiveCameraControllerConfig());
KINAKO_API void KnPerspectiveCameraController_OnUpdate(KnPerspectiveCameraController* self, float delta);
KINAKO_API void KnPerspectiveCameraController_OnEvent(KnPerspectiveCameraController* self, Event *e);
KINAKO_API void KnPerspectiveCameraController_OnResize(KnPerspectiveCameraController* self, float width, float height);
KINAKO_API KnPerspectiveCamera* KnPerspectiveCameraController_GetCamera(KnPerspectiveCameraController* self); // [retref]
KINAKO_API const KnPerspectiveCamera* KnPerspectiveCameraController_GetCamera(const KnPerspectiveCameraController* self); // [retref]
KINAKO_API bool KnPerspectiveCameraController_IsCursorLocked(const KnPerspectiveCameraController* self);
KINAKO_API void KnPerspectiveCameraController_SetCursorLock(KnPerspectiveCameraController* self, bool enabled);
KINAKO_API bool KnPerspectiveCameraController_IsRotationEnabled(const KnPerspectiveCameraController* self);
KINAKO_API void KnPerspectiveCameraController_SetRotationEnabled(KnPerspectiveCameraController* self, bool enabled);
KINAKO_API void KnRenderCommand_Init(void);
KINAKO_API void KnRenderCommand_SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
KINAKO_API void KnRenderCommand_SetClearColor(glm::vec4 *color);
KINAKO_API void KnRenderCommand_SetClearColor(float r, float g, float b, float a);
KINAKO_API void KnRenderCommand_SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
KINAKO_API void KnRenderCommand_Clear(void);
KINAKO_API void KnRenderCommand_DrawIndexed(Ref< VertexArray > *vertex_array, uint32_t index_count);
KINAKO_API void KnRenderCommand_DrawLines(Ref< VertexArray > *vertex_array, uint32_t vertex_count);
KINAKO_API void KnRenderCommand_DrawTriangles(Ref< VertexArray > *vertex_array, uint32_t vertex_count);
KINAKO_API void KnRenderCommand_SetLineWidth(float width);
KINAKO_API void KnRenderer_Init(void);
KINAKO_API void KnRenderer_Shutdown(void);
KINAKO_API void KnRenderer_BeginFrame(PerspectiveCamera *camera);
KINAKO_API void KnRenderer_EndFrame(void);
KINAKO_API void KnRenderer_OnWindowResize(uint32_t width, uint32_t height);
KINAKO_API void KnRenderer_Submit(Ref< Shader > *shader, Ref< VertexArray > *vertex_array, glm::mat4 *transform=glm::mat4(1.0f));
KINAKO_API void KnRenderer_SubmitTriangles(Ref< Shader > *shader, Ref< VertexArray > *vertex_array, uint32_t vertex_count, glm::mat4 *transform=glm::mat4(1.0f));
KINAKO_API void KnRenderer2D_BeginFrame(Camera *camera, glm::mat4 *transform);
KINAKO_API void KnRenderer2D_BeginFrame(OrthographicCamera *camera);
KINAKO_API void KnRenderer2D_BeginFrame(PerspectiveCamera *camera);
KINAKO_API void KnRenderer2D_Flush(void);
KINAKO_API void KnRenderer2D_UpdateViewport(void);
KINAKO_API void KnRenderer2D_EndFrame(void);
KINAKO_API void KnRenderer2D_DrawCircle(glm::mat4 *transform, glm::vec4 *color, float thickness=1.0f, float fade=0.005f);
KINAKO_API void KnRenderer2D_DrawLine(glm::vec3 *p0, glm::vec3 *p1, glm::vec4 *color);
KINAKO_API float KnRenderer2D_GetLineWidth(void);
KINAKO_API void KnRenderer2D_SetLineWidth(float width);
KINAKO_API void KnRenderer2D_DrawQuad(glm::vec2 *position, glm::vec2 *size, glm::vec4 *color);
KINAKO_API void KnRenderer2D_DrawQuad(glm::vec3 *position, glm::vec2 *size, glm::vec4 *color);
KINAKO_API void KnRenderer2D_DrawQuad(glm::vec2 *position, glm::vec2 *size, Ref< Texture2D > *texture, glm::vec4 *tint_color=glm::vec4(1.0f));
KINAKO_API void KnRenderer2D_DrawQuad(glm::vec3 *position, glm::vec2 *size, Ref< Texture2D > *texture, glm::vec4 *tint_color=glm::vec4(1.0f));
KINAKO_API void KnRenderer2D_DrawQuad(glm::mat4 *transform, glm::vec4 *color);
KINAKO_API void KnRenderer2D_DrawQuad(glm::mat4 *transform, Ref< Texture2D > *texture, glm::vec4 *tint_color=glm::vec4(1.0f));
KINAKO_API void KnRenderer2D_DrawRotatedQuad(glm::vec2 *position, glm::vec2 *size, float rotation, glm::vec4 *color);
KINAKO_API void KnRenderer2D_DrawRotatedQuad(glm::vec3 *position, glm::vec2 *size, float rotation, glm::vec4 *color);
KINAKO_API void KnRenderer2D_DrawRotatedQuad(glm::vec2 *position, glm::vec2 *size, float rotation, Ref< Texture2D > *texture, glm::vec4 *tintColor=glm::vec4(1.0f));
KINAKO_API void KnRenderer2D_DrawRotatedQuad(glm::vec3 *position, glm::vec2 *size, float rotation, Ref< Texture2D > *texture, glm::vec4 *tintColor=glm::vec4(1.0f));
KINAKO_API void KnRenderer2D_DrawRect(glm::vec3 *position, glm::vec2 *size, glm::vec4 *color);
KINAKO_API void KnRenderer2D_DrawRect(glm::mat4 *transform, glm::vec4 *color);
KINAKO_API KnShader2D KnRenderer2D_MakeShader(char *filepath, char *program_name);
KINAKO_API KnShader2D KnRenderer2D_MakeShader(char *program_name, char *vertexSrc, char *fragmentSrc);
KINAKO_API void KnRenderer2D_SetQuadShader(Shader2D *shader);
KINAKO_API void KnRenderer2D_ResetQuadShader(void);
KINAKO_API void KnRenderer2D_Init(void);
KINAKO_API void KnRenderer2D_Shutdown(void);
KINAKO_API KnShader** KnRenderer2D_Shader2D_GetShader(KnRenderer2D_Shader2D* self); // [retref]
KINAKO_API uint32_t KnRenderer2D_Statistics_GetTotalVertexCount(KnRenderer2D_Statistics* self);
KINAKO_API uint32_t KnRenderer2D_Statistics_GetTotalIndexCount(KnRenderer2D_Statistics* self);
KINAKO_API void KnRenderer2D_Statistics_Reset(KnRenderer2D_Statistics* self);
KINAKO_API uint32_t KnRenderer2D_Statistics_GetDrawCalls(const KnRenderer2D_Statistics* self);
KINAKO_API uint32_t KnRenderer2D_Statistics_GetQuadCount(const KnRenderer2D_Statistics* self);
KINAKO_API void KnRendererAPI_DestroyRendererAPI(KnRendererAPI* self);
KINAKO_API void KnRendererAPI_Init(KnRendererAPI* self);
KINAKO_API void KnRendererAPI_SetViewport(KnRendererAPI* self, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
KINAKO_API void KnRendererAPI_SetClearColor(const KnRendererAPI* self, glm::vec4 *color);
KINAKO_API void KnRendererAPI_Clear(KnRendererAPI* self);
KINAKO_API void KnRendererAPI_DrawIndexed(const KnRendererAPI* self, Ref< VertexArray > *vertex_array, uint32_t index_count);
KINAKO_API void KnRendererAPI_DrawLines(const KnRendererAPI* self, Ref< VertexArray > *vertex_array, uint32_t vertex_count);
KINAKO_API void KnRendererAPI_DrawTriangles(const KnRendererAPI* self, Ref< VertexArray > *vertexArray, uint32_t vertexCount);
KINAKO_API void KnRendererAPI_SetLineWidth(KnRendererAPI* self, float width);
KINAKO_API KnRendererAPI* KnRendererAPI_Create(void);
KINAKO_API void KnShader_DestroyShader(KnShader* self);
KINAKO_API void KnShader_Bind(const KnShader* self);
KINAKO_API void KnShader_Unbind(const KnShader* self);
KINAKO_API void KnShader_SetInt(const KnShader* self, char *name, int value);
KINAKO_API void KnShader_SetIntArray(const KnShader* self, char *name, int *values, uint32_t count);
KINAKO_API void KnShader_SetFloat(const KnShader* self, char *name, float value);
KINAKO_API void KnShader_SetFloat2(const KnShader* self, char *name, glm::vec2 *value);
KINAKO_API void KnShader_SetFloat3(const KnShader* self, char *name, glm::vec3 *value);
KINAKO_API void KnShader_SetFloat4(const KnShader* self, char *name, glm::vec4 *value);
KINAKO_API void KnShader_SetMat4(const KnShader* self, char *name, glm::mat4 *value);
KINAKO_API const const char** KnShader_GetName(const KnShader* self); // [retref]
KINAKO_API KnShader* KnShader_Create(char *filepath, char *program_name);
KINAKO_API KnShader* KnShader_Create(char *name, char *vertexSrc, char *fragmentSrc);
KINAKO_API void KnShaderLibrary_Add(const KnShaderLibrary* self, char *name, Ref< Shader > *shader);
KINAKO_API void KnShaderLibrary_Add(const KnShaderLibrary* self, Ref< Shader > *shader);
KINAKO_API KnShader* KnShaderLibrary_Load(const KnShaderLibrary* self, char *filepath, char *name);
KINAKO_API KnShader* KnShaderLibrary_Load(const KnShaderLibrary* self, char *name, char *vertexSrc, char *fragmentSrc);
KINAKO_API KnShader* KnShaderLibrary_Get(const KnShaderLibrary* self, char *name);
KINAKO_API bool KnShaderLibrary_Exists(const KnShaderLibrary* self, char *name const);
KINAKO_API KnTimer* KnTimer_Timer(void);
KINAKO_API void KnTimer_Reset(KnTimer* self);
KINAKO_API float KnTimer_ElapsedSeconds(KnTimer* self);
KINAKO_API float KnTimer_ElapsedMS(KnTimer* self);
KINAKO_API void KnUniformBuffer_DestroyUniformBuffer(KnUniformBuffer* self);
KINAKO_API void KnUniformBuffer_SetData(const KnUniformBuffer* self, void *data, uint32_t size, uint32_t offset=0);
KINAKO_API KnUniformBuffer* KnUniformBuffer_Create(uint32_t size, uint32_t binding);
KINAKO_API void KnVertexArray_DestroyVertexArray(KnVertexArray* self);
KINAKO_API void KnVertexArray_Bind(const KnVertexArray* self);
KINAKO_API void KnVertexArray_Unbind(const KnVertexArray* self);
KINAKO_API void KnVertexArray_AddVertexBuffer(const KnVertexArray* self, Ref< VertexBuffer > *vertex_buffer);
KINAKO_API void KnVertexArray_SetIndexBuffer(const KnVertexArray* self, Ref< IndexBuffer > *index_buffer);
KINAKO_API const KnVertexBuffer** KnVertexArray_GetVertexBuffers(const KnVertexArray* self); // [retref]
KINAKO_API const KnIndexBuffer** KnVertexArray_GetIndexBuffer(const KnVertexArray* self); // [retref]
KINAKO_API KnVertexArray* KnVertexArray_Create(void);
KINAKO_API void KnVertexBuffer_DestroyVertexBuffer(KnVertexBuffer* self);
KINAKO_API void KnVertexBuffer_Bind(const KnVertexBuffer* self);
KINAKO_API void KnVertexBuffer_Unbind(const KnVertexBuffer* self);
KINAKO_API void KnVertexBuffer_SetData(const KnVertexBuffer* self, void *data, uint32_t size);
KINAKO_API void KnVertexBuffer_SetLayout(const KnVertexBuffer* self, BufferLayout *layout);
KINAKO_API const KnBufferLayout* KnVertexBuffer_GetLayout(const KnVertexBuffer* self); // [retref]
KINAKO_API KnVertexBuffer* KnVertexBuffer_Create(uint32_t size);
KINAKO_API KnVertexBuffer* KnVertexBuffer_Create(void *vertices, uint32_t size);
KINAKO_API void KnWindow_DestroyWindow(KnWindow* self);
KINAKO_API void KnWindow_OnUpdate(KnWindow* self);
KINAKO_API void * KnWindow_GetNativeWindow(const KnWindow* self);
KINAKO_API glm::ivec2 KnWindow_GetSize(const KnWindow* self);
KINAKO_API uint32_t KnWindow_GetWidth(const KnWindow* self);
KINAKO_API uint32_t KnWindow_GetHeight(const KnWindow* self);
KINAKO_API bool KnWindow_GetRelativeMouseMode(const KnWindow* self);
KINAKO_API bool KnWindow_IsFocused(const KnWindow* self);
KINAKO_API bool KnWindow_IsHovered(const KnWindow* self);
KINAKO_API bool KnWindow_IsVSync(const KnWindow* self);
KINAKO_API void KnWindow_SetVSync(KnWindow* self, bool enabled);
KINAKO_API void KnWindow_SetEventCallback(const KnWindow* self, EventCallback *callback);
KINAKO_API void KnWindow_SetTitle(const KnWindow* self, char *title);
KINAKO_API void KnWindow_SetRelativeMouseMode(KnWindow* self, bool enabled);
KINAKO_API void KnWindow_WarpMouse(KnWindow* self, float x, float y);
KINAKO_API KnWindow* KnWindow_Create(WindowProps *props);
KINAKO_API KnWindowResizeEvent* KnWindowResizeEvent_WindowResizeEvent(uint32_t width, uint32_t height);
KINAKO_API uint32_t KnWindowResizeEvent_GetWidth(KnWindowResizeEvent* self);
KINAKO_API uint32_t KnWindowResizeEvent_GetHeight(KnWindowResizeEvent* self);
KINAKO_API const char* KnWindowResizeEvent_ToString(const KnWindowResizeEvent* self);
KINAKO_API KnBufferElement* KnBufferElement_BufferElement(void);
KINAKO_API KnBufferElement* KnBufferElement_BufferElement(ShaderDataType type, char *name, bool normalized=false);
KINAKO_API uint32_t KnBufferElement_GetComponentCount(const KnBufferElement* self);
KINAKO_API KnFramebufferAttachmentConfig* KnFramebufferAttachmentConfig_FramebufferAttachmentConfig(void);
KINAKO_API KnFramebufferAttachmentConfig* KnFramebufferAttachmentConfig_FramebufferAttachmentConfig(std::initializer_list< FramebufferTextureConfig > attachments);
KINAKO_API KnFramebufferTextureConfig* KnFramebufferTextureConfig_FramebufferTextureConfig(void);
KINAKO_API KnFramebufferTextureConfig* KnFramebufferTextureConfig_FramebufferTextureConfig(FramebufferTextureFormat format);
KINAKO_API void KnTokenBase< Tp, type >_TokenBase(KnTokenBase* self, Tp t, string_type w, uint32_t r, uint32_t c);
KINAKO_API KnWindowProps* KnWindowProps_WindowProps(char *title="Kinai", uint32_t width=KN_DEFAULT_WINDOW_WIDTH, uint32_t height=KN_DEFAULT_WINDOW_HEIGHT, bool fullscreen=false, bool no_vsync=false);
