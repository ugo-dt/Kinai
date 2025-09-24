#include "kinako.h"
#include <Kinai/Kinai.hpp>

KnApplication* KnApplication_Application(KnApplication *self, const KnApplicationConfig* config)
{
    return new Kinai::Application(*config);
}

void KnApplication_DestroyApplication(KnApplication *self)
{
    delete (self);
}

KnLayer* KnApplication_PushLayer(KnApplication *self, KnLayer* layer)
{
    return ((Kinai::Application*)self)->PushLayer(layer);
}

KnLayer* KnApplication_PushOverlay(KnApplication *self, KnLayer* layer)
{
    return ((Kinai::Application*)self)->PushOverlay(layer);
}

void KnApplication_Close(KnApplication *self)
{
    return ((Kinai::Application*)self)->Close();
}

KnWindow* KnApplication_GetWindow(KnApplication *self)
{
    return ((Kinai::Application*)self)->GetWindow();
}

uint64_t KnApplication_GetFPS(KnApplication *self)
{
    return ((Kinai::Application*)self)->GetFPS();
}

float KnApplication_GetDeltaTime(KnApplication *self)
{
    return ((Kinai::Application*)self)->GetDeltaTime();
}

KnImGuiLayer* KnApplication_GetImGuiLayer(KnApplication *self)
{
    return ((Kinai::Application*)self)->GetImGuiLayer();
}

void KnApplication_Run(KnApplication *self)
{
    return ((Kinai::Application*)self)->Run();
}

KnApplication* KnApplication_Get(KnApplication *self)
{
    return ((Kinai::Application*)self)->Get();
}


KnAppRenderEvent* KnAppRenderEvent_AppRenderEvent(KnAppRenderEvent *self)
{
    return new Kinai::AppRenderEvent();
}

KnAppTickEvent* KnAppTickEvent_AppTickEvent(KnAppTickEvent *self)
{
    return new Kinai::AppTickEvent();
}

KnAppUpdateEvent* KnAppUpdateEvent_AppUpdateEvent(KnAppUpdateEvent *self)
{
    return new Kinai::AppUpdateEvent();
}

KnBufferElement* KnBufferElement_BufferElement(KnBufferElement *self)
{
    return new Kinai::BufferElement();
}

KnBufferElement* KnBufferElement_BufferElement2(KnBufferElement *self, KnShaderDataType type, void* name, bool normalized)
{
    return new Kinai::BufferElement(type, *name, normalized);
}

uint32_t KnBufferElement_GetComponentCount(KnBufferElement *self)
{
    return ((Kinai::BufferElement*)self)->GetComponentCount();
}

KnBufferLayout* KnBufferLayout_BufferLayout(KnBufferLayout *self)
{
    return new Kinai::BufferLayout();
}

KnBufferLayout* KnBufferLayout_BufferLayout2(KnBufferLayout *self, KnBufferElement* elements)
{
    return new Kinai::BufferLayout(elements);
}

KnBufferLayout* KnBufferLayout_BufferLayout3(KnBufferLayout *self, const KnBufferElement* elements)
{
    return new Kinai::BufferLayout(*elements);
}

uint32_t KnBufferLayout_GetStride(KnBufferLayout *self)
{
    return ((Kinai::BufferLayout*)self)->GetStride();
}

const KnBufferElement* KnBufferLayout_GetElements(KnBufferLayout *self)
{
    return ((Kinai::BufferLayout*)self)->GetElements();
}

KnBufferElement* KnBufferLayout_begin(KnBufferLayout *self)
{
    return ((Kinai::BufferLayout*)self)->begin();
}

KnBufferElement* KnBufferLayout_end(KnBufferLayout *self)
{
    return ((Kinai::BufferLayout*)self)->end();
}

KnBufferElement* KnBufferLayout_begin2(KnBufferLayout *self)
{
    return ((Kinai::BufferLayout*)self)->begin();
}

KnBufferElement* KnBufferLayout_end2(KnBufferLayout *self)
{
    return ((Kinai::BufferLayout*)self)->end();
}


KnCamera* KnCamera_Camera(KnCamera *self)
{
    return new Kinai::Camera();
}

KnCamera* KnCamera_Camera2(KnCamera *self, const mat4s* projection_matrix)
{
    return new Kinai::Camera(*projection_matrix);
}

void KnCamera_DestroyCamera(KnCamera *self)
{
    delete (self);
}

const mat4s* KnCamera_GetProjectionMatrix(KnCamera *self)
{
    return ((Kinai::Camera*)self)->GetProjectionMatrix();
}



void KnEvent_DestroyEvent(KnEvent *self)
{
    delete (self);
}

KnEventType KnEvent_GetEventType(KnEvent *self)
{
    return ((Kinai::Event*)self)->GetEventType();
}

const char* KnEvent_GetName(KnEvent *self)
{
    return ((Kinai::Event*)self)->GetName();
}

int KnEvent_GetCategoryFlags(KnEvent *self)
{
    return ((Kinai::Event*)self)->GetCategoryFlags();
}

void* KnEvent_ToString(KnEvent *self)
{
    return ((Kinai::Event*)self)->ToString();
}

bool KnEvent_IsInCategory(KnEvent *self, KnEventCategory category)
{
    return ((Kinai::Event*)self)->IsInCategory(category);
}

KnEventDispatcher* KnEventDispatcher_EventDispatcher(KnEventDispatcher *self, KnEvent* event)
{
    return new Kinai::EventDispatcher(*event);
}

bool KnEventDispatcher_Dispatch(KnEventDispatcher *self, const F* func)
{
    return ((Kinai::EventDispatcher*)self)->Dispatch(*func);
}

void KnFramebuffer_DestroyFramebuffer(KnFramebuffer *self)
{
    delete (self);
}

void KnFramebuffer_Bind(KnFramebuffer *self)
{
    return ((Kinai::Framebuffer*)self)->Bind();
}

void KnFramebuffer_Unbind(KnFramebuffer *self)
{
    return ((Kinai::Framebuffer*)self)->Unbind();
}

void KnFramebuffer_Resize(KnFramebuffer *self, uint32_t width, uint32_t height)
{
    return ((Kinai::Framebuffer*)self)->Resize(width, height);
}

int KnFramebuffer_ReadPixel(KnFramebuffer *self, uint32_t attachmentIndex, int x, int y)
{
    return ((Kinai::Framebuffer*)self)->ReadPixel(attachmentIndex, x, y);
}

void KnFramebuffer_ClearAttachment(KnFramebuffer *self, uint32_t attachmentIndex, int value)
{
    return ((Kinai::Framebuffer*)self)->ClearAttachment(attachmentIndex, value);
}

uint32_t KnFramebuffer_GetColorAttachmentRendererID(KnFramebuffer *self, uint32_t index)
{
    return ((Kinai::Framebuffer*)self)->GetColorAttachmentRendererID(index);
}

const KnFramebufferConfig* KnFramebuffer_GetConfig(KnFramebuffer *self)
{
    return ((Kinai::Framebuffer*)self)->GetConfig();
}

uint32_t KnFramebuffer_GetRendererID(KnFramebuffer *self)
{
    return ((Kinai::Framebuffer*)self)->GetRendererID();
}

KnFramebuffer* KnFramebuffer_Create(KnFramebuffer *self, const KnFramebufferConfig* config)
{
    return ((Kinai::Framebuffer*)self)->Create(*config);
}

KnFramebufferAttachmentConfig* KnFramebufferAttachmentConfig_FramebufferAttachmentConfig(KnFramebufferAttachmentConfig *self)
{
    return new Kinai::FramebufferAttachmentConfig();
}

KnFramebufferAttachmentConfig* KnFramebufferAttachmentConfig_FramebufferAttachmentConfig2(KnFramebufferAttachmentConfig *self, KnFramebufferTextureConfig* attachments)
{
    return new Kinai::FramebufferAttachmentConfig(attachments);
}


KnFramebufferTextureConfig* KnFramebufferTextureConfig_FramebufferTextureConfig(KnFramebufferTextureConfig *self)
{
    return new Kinai::FramebufferTextureConfig();
}

KnFramebufferTextureConfig* KnFramebufferTextureConfig_FramebufferTextureConfig2(KnFramebufferTextureConfig *self, KnFramebufferTextureFormat format)
{
    return new Kinai::FramebufferTextureConfig(format);
}

KnImGuiLayer* KnImGuiLayer_ImGuiLayer(KnImGuiLayer *self)
{
    return new Kinai::ImGuiLayer();
}

void KnImGuiLayer_DestroyImGuiLayer(KnImGuiLayer *self)
{
    delete (self);
}

void KnImGuiLayer_Begin(KnImGuiLayer *self)
{
    return ((Kinai::ImGuiLayer*)self)->Begin();
}

void KnImGuiLayer_End(KnImGuiLayer *self)
{
    return ((Kinai::ImGuiLayer*)self)->End();
}

void KnImGuiLayer_OnAttach(KnImGuiLayer *self)
{
    return ((Kinai::ImGuiLayer*)self)->OnAttach();
}

void KnImGuiLayer_OnDetach(KnImGuiLayer *self)
{
    return ((Kinai::ImGuiLayer*)self)->OnDetach();
}

void KnImGuiLayer_OnEvent(KnImGuiLayer *self, KnEvent* event)
{
    return ((Kinai::ImGuiLayer*)self)->OnEvent(*event);
}

void KnImGuiLayer_BlockEvents(KnImGuiLayer *self, bool block)
{
    return ((Kinai::ImGuiLayer*)self)->BlockEvents(block);
}

void KnIndexBuffer_DestroyIndexBuffer(KnIndexBuffer *self)
{
    delete (self);
}

void KnIndexBuffer_Bind(KnIndexBuffer *self)
{
    return ((Kinai::IndexBuffer*)self)->Bind();
}

void KnIndexBuffer_Unbind(KnIndexBuffer *self)
{
    return ((Kinai::IndexBuffer*)self)->Unbind();
}

uint32_t KnIndexBuffer_GetCount(KnIndexBuffer *self)
{
    return ((Kinai::IndexBuffer*)self)->GetCount();
}

KnIndexBuffer* KnIndexBuffer_Create(KnIndexBuffer *self, const uint32_t* indices, uint32_t count)
{
    return ((Kinai::IndexBuffer*)self)->Create(indices, count);
}

bool KnInput_IsKeyPressed(KnInput *self, KnKeyCode key)
{
    return ((Kinai::Input*)self)->IsKeyPressed(key);
}

bool KnInput_IsMouseButtonPressed(KnInput *self, KnMouseButton button)
{
    return ((Kinai::Input*)self)->IsMouseButtonPressed(button);
}

vec2s KnInput_GetMousePosition(KnInput *self)
{
    return ((Kinai::Input*)self)->GetMousePosition();
}

float KnInput_GetMouseX(KnInput *self)
{
    return ((Kinai::Input*)self)->GetMouseX();
}

float KnInput_GetMouseY(KnInput *self)
{
    return ((Kinai::Input*)self)->GetMouseY();
}


KnKeyCode KnKeyEvent_GetKeyCode(KnKeyEvent *self)
{
    return ((Kinai::KeyEvent*)self)->GetKeyCode();
}

void KnKeyEvent_EVENT_CLASS_CATEGORY(KnKeyEvent *self, EventCategoryKeyboard| EventCategoryInput)
{
    return ((Kinai::KeyEvent*)self)->EVENT_CLASS_CATEGORY(EventCategoryInput);
}

KnKeyPressedEvent* KnKeyPressedEvent_KeyPressedEvent(KnKeyPressedEvent *self, const KnKeyCode keycode, bool repeat)
{
    return new Kinai::KeyPressedEvent(keycode, repeat);
}

bool KnKeyPressedEvent_IsRepeat(KnKeyPressedEvent *self)
{
    return ((Kinai::KeyPressedEvent*)self)->IsRepeat();
}

void* KnKeyPressedEvent_ToString(KnKeyPressedEvent *self)
{
    return ((Kinai::KeyPressedEvent*)self)->ToString();
}

KnKeyReleasedEvent* KnKeyReleasedEvent_KeyReleasedEvent(KnKeyReleasedEvent *self, const KnKeyCode keycode)
{
    return new Kinai::KeyReleasedEvent(keycode);
}

void* KnKeyReleasedEvent_ToString(KnKeyReleasedEvent *self)
{
    return ((Kinai::KeyReleasedEvent*)self)->ToString();
}

void KnLayer_DestroyLayer(KnLayer *self)
{
    delete (self);
}

void KnLayer_OnAttach(KnLayer *self)
{
    return ((Kinai::Layer*)self)->OnAttach();
}

void KnLayer_OnDetach(KnLayer *self)
{
    return ((Kinai::Layer*)self)->OnDetach();
}

void KnLayer_OnUpdate(KnLayer *self, float delta)
{
    return ((Kinai::Layer*)self)->OnUpdate(delta);
}

void KnLayer_OnImGuiRender(KnLayer *self)
{
    return ((Kinai::Layer*)self)->OnImGuiRender();
}

void KnLayer_OnEvent(KnLayer *self, KnEvent* event)
{
    return ((Kinai::Layer*)self)->OnEvent(*event);
}

void* KnLayer_GetName(KnLayer *self)
{
    return ((Kinai::Layer*)self)->GetName();
}

KnLayerStack* KnLayerStack_LayerStack(KnLayerStack *self)
{
    return new Kinai::LayerStack();
}

void KnLayerStack_DestroyLayerStack(KnLayerStack *self)
{
    delete (self);
}

void KnLayerStack_PushLayer(KnLayerStack *self, KnLayer* layer)
{
    return ((Kinai::LayerStack*)self)->PushLayer(layer);
}

void KnLayerStack_PopLayer(KnLayerStack *self, KnLayer* layer)
{
    return ((Kinai::LayerStack*)self)->PopLayer(layer);
}

void KnLayerStack_PushOverlay(KnLayerStack *self, KnLayer* layer)
{
    return ((Kinai::LayerStack*)self)->PushOverlay(layer);
}

void KnLayerStack_PopOverlay(KnLayerStack *self, KnLayer* layer)
{
    return ((Kinai::LayerStack*)self)->PopOverlay(layer);
}

void KnLayerStack_Clear(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->Clear();
}

KnLayer* KnLayerStack_begin(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->begin();
}

KnLayer* KnLayerStack_begin2(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->begin();
}

KnLayer* KnLayerStack_end(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->end();
}

KnLayer* KnLayerStack_end2(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->end();
}

KnLayer* KnLayerStack_rbegin(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->rbegin();
}

KnLayer* KnLayerStack_rbegin2(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->rbegin();
}

KnLayer* KnLayerStack_rend(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->rend();
}

KnLayer* KnLayerStack_rend2(KnLayerStack *self)
{
    return ((Kinai::LayerStack*)self)->rend();
}


void KnLog_Init(KnLog *self)
{
    return ((Kinai::Log*)self)->Init();
}

void KnLog_Trace(KnLog *self, void* fmt, Args**... args)
{
    return ((Kinai::Log*)self)->Trace(fmt, *args);
}

void KnLog_Info(KnLog *self, void* fmt, Args**... args)
{
    return ((Kinai::Log*)self)->Info(fmt, *args);
}

void KnLog_Warn(KnLog *self, void* fmt, Args**... args)
{
    return ((Kinai::Log*)self)->Warn(fmt, *args);
}

void KnLog_Error(KnLog *self, void* fmt, Args**... args)
{
    return ((Kinai::Log*)self)->Error(fmt, *args);
}

void KnLog_Critical(KnLog *self, void* fmt, Args**... args)
{
    return ((Kinai::Log*)self)->Critical(fmt, *args);
}

KnMouseButtonEvent* KnMouseButtonEvent_MouseButtonEvent(KnMouseButtonEvent *self)
{
    return new Kinai::MouseButtonEvent();
}

KnMouseButton KnMouseButtonEvent_GetButton(KnMouseButtonEvent *self)
{
    return ((Kinai::MouseButtonEvent*)self)->GetButton();
}

void KnMouseButtonEvent_EVENT_CLASS_CATEGORY(KnMouseButtonEvent *self, EventCategoryMouse|EventCategoryInput| EventCategoryMouseButton)
{
    return ((Kinai::MouseButtonEvent*)self)->EVENT_CLASS_CATEGORY(EventCategoryMouseButton);
}

KnMouseButtonPressedEvent* KnMouseButtonPressedEvent_MouseButtonPressedEvent(KnMouseButtonPressedEvent *self, const KnMouseButton button)
{
    return new Kinai::MouseButtonPressedEvent(button);
}

void KnMouseButtonPressedEvent_EVENT_CLASS_TYPE(KnMouseButtonPressedEvent *self, SDL_EVENT_MOUSE_BUTTON_DOWN )
{
    return ((Kinai::MouseButtonPressedEvent*)self)->EVENT_CLASS_TYPE();
}

void* KnMouseButtonPressedEvent_ToString(KnMouseButtonPressedEvent *self)
{
    return ((Kinai::MouseButtonPressedEvent*)self)->ToString();
}

KnMouseButtonReleasedEvent* KnMouseButtonReleasedEvent_MouseButtonReleasedEvent(KnMouseButtonReleasedEvent *self, const KnMouseButton button)
{
    return new Kinai::MouseButtonReleasedEvent(button);
}

void KnMouseButtonReleasedEvent_EVENT_CLASS_TYPE(KnMouseButtonReleasedEvent *self, SDL_EVENT_MOUSE_BUTTON_UP )
{
    return ((Kinai::MouseButtonReleasedEvent*)self)->EVENT_CLASS_TYPE();
}

void* KnMouseButtonReleasedEvent_ToString(KnMouseButtonReleasedEvent *self)
{
    return ((Kinai::MouseButtonReleasedEvent*)self)->ToString();
}

KnMouseMotionEvent* KnMouseMotionEvent_MouseMotionEvent(KnMouseMotionEvent *self, const float x, const float y, const float rel_x, const float rel_y)
{
    return new Kinai::MouseMotionEvent(x, y, rel_x, rel_y);
}

float KnMouseMotionEvent_GetX(KnMouseMotionEvent *self)
{
    return ((Kinai::MouseMotionEvent*)self)->GetX();
}

float KnMouseMotionEvent_GetY(KnMouseMotionEvent *self)
{
    return ((Kinai::MouseMotionEvent*)self)->GetY();
}

float KnMouseMotionEvent_GetXRelative(KnMouseMotionEvent *self)
{
    return ((Kinai::MouseMotionEvent*)self)->GetXRelative();
}

float KnMouseMotionEvent_GetYRelative(KnMouseMotionEvent *self)
{
    return ((Kinai::MouseMotionEvent*)self)->GetYRelative();
}

void KnMouseMotionEvent_EVENT_CLASS_TYPE(KnMouseMotionEvent *self, SDL_EVENT_MOUSE_MOTION )
{
    return ((Kinai::MouseMotionEvent*)self)->EVENT_CLASS_TYPE();
}

void KnMouseMotionEvent_EVENT_CLASS_CATEGORY(KnMouseMotionEvent *self, EventCategoryMouse| EventCategoryInput)
{
    return ((Kinai::MouseMotionEvent*)self)->EVENT_CLASS_CATEGORY(EventCategoryInput);
}

void* KnMouseMotionEvent_ToString(KnMouseMotionEvent *self)
{
    return ((Kinai::MouseMotionEvent*)self)->ToString();
}

KnMouseWheelEvent* KnMouseWheelEvent_MouseWheelEvent(KnMouseWheelEvent *self, const float x, const float y)
{
    return new Kinai::MouseWheelEvent(x, y);
}

float KnMouseWheelEvent_GetXOffset(KnMouseWheelEvent *self)
{
    return ((Kinai::MouseWheelEvent*)self)->GetXOffset();
}

float KnMouseWheelEvent_GetYOffset(KnMouseWheelEvent *self)
{
    return ((Kinai::MouseWheelEvent*)self)->GetYOffset();
}

void KnMouseWheelEvent_EVENT_CLASS_TYPE(KnMouseWheelEvent *self, SDL_EVENT_MOUSE_WHEEL )
{
    return ((Kinai::MouseWheelEvent*)self)->EVENT_CLASS_TYPE();
}

void KnMouseWheelEvent_EVENT_CLASS_CATEGORY(KnMouseWheelEvent *self, EventCategoryMouse| EventCategoryInput)
{
    return ((Kinai::MouseWheelEvent*)self)->EVENT_CLASS_CATEGORY(EventCategoryInput);
}

void* KnMouseWheelEvent_ToString(KnMouseWheelEvent *self)
{
    return ((Kinai::MouseWheelEvent*)self)->ToString();
}

KnOrthographicCamera* KnOrthographicCamera_OrthographicCamera(KnOrthographicCamera *self, float left, float right, float bottom, float top)
{
    return new Kinai::OrthographicCamera(left, right, bottom, top);
}

void KnOrthographicCamera_DestroyOrthographicCamera(KnOrthographicCamera *self)
{
    delete (self);
}

void KnOrthographicCamera_SetProjection(KnOrthographicCamera *self, float left, float right, float bottom, float top)
{
    return ((Kinai::OrthographicCamera*)self)->SetProjection(left, right, bottom, top);
}

void KnOrthographicCamera_SetPosition(KnOrthographicCamera *self, const vec3s* position)
{
    return ((Kinai::OrthographicCamera*)self)->SetPosition(*position);
}

void KnOrthographicCamera_SetRotation(KnOrthographicCamera *self, const vec3s* rotation)
{
    return ((Kinai::OrthographicCamera*)self)->SetRotation(*rotation);
}

const vec3s* KnOrthographicCamera_GetPosition(KnOrthographicCamera *self)
{
    return ((Kinai::OrthographicCamera*)self)->GetPosition();
}

const vec3s* KnOrthographicCamera_GetRotation(KnOrthographicCamera *self)
{
    return ((Kinai::OrthographicCamera*)self)->GetRotation();
}

const mat4s* KnOrthographicCamera_GetProjectionMatrix(KnOrthographicCamera *self)
{
    return ((Kinai::OrthographicCamera*)self)->GetProjectionMatrix();
}

const mat4s* KnOrthographicCamera_GetViewMatrix(KnOrthographicCamera *self)
{
    return ((Kinai::OrthographicCamera*)self)->GetViewMatrix();
}

const mat4s* KnOrthographicCamera_GetViewProjectionMatrix(KnOrthographicCamera *self)
{
    return ((Kinai::OrthographicCamera*)self)->GetViewProjectionMatrix();
}

KnOrthographicCameraController* KnOrthographicCameraController_OrthographicCameraController(KnOrthographicCameraController *self, const KnOrthographicCameraControllerConfig* config)
{
    return new Kinai::OrthographicCameraController(*config);
}

void KnOrthographicCameraController_OnUpdate(KnOrthographicCameraController *self, float delta)
{
    return ((Kinai::OrthographicCameraController*)self)->OnUpdate(delta);
}

void KnOrthographicCameraController_OnEvent(KnOrthographicCameraController *self, KnEvent* event)
{
    return ((Kinai::OrthographicCameraController*)self)->OnEvent(*event);
}

void KnOrthographicCameraController_OnResize(KnOrthographicCameraController *self, float width, float height)
{
    return ((Kinai::OrthographicCameraController*)self)->OnResize(width, height);
}

KnOrthographicCamera* KnOrthographicCameraController_GetCamera(KnOrthographicCameraController *self)
{
    return ((Kinai::OrthographicCameraController*)self)->GetCamera();
}

const KnOrthographicCamera* KnOrthographicCameraController_GetCamera2(KnOrthographicCameraController *self)
{
    return ((Kinai::OrthographicCameraController*)self)->GetCamera();
}


KnParser* KnParser_Parser(KnParser *self, void* filepath)
{
    return new Kinai::Parser(*filepath);
}

KN_INLINE void* KnParser_YELLOW(KnParser *self, const void** s)
{
    return ((Kinai::Parser*)self)->YELLOW(*s);
}

KN_INLINE void* KnParser_CYAN(KnParser *self, const void** s)
{
    return ((Kinai::Parser*)self)->CYAN(*s);
}

KN_INLINE void* KnParser_MAGENTA(KnParser *self, const void** s)
{
    return ((Kinai::Parser*)self)->MAGENTA(*s);
}

KN_INLINE void* KnParser_RED(KnParser *self, const void** s)
{
    return ((Kinai::Parser*)self)->RED(*s);
}

KN_INLINE void* KnParser_WHITE(KnParser *self, const void** s)
{
    return ((Kinai::Parser*)self)->WHITE(*s);
}

KN_INLINE bool KnParser_iterator_equals(KnParser *self, void** it, const token_type* t)
{
    return ((Kinai::Parser*)self)->iterator_equals(*it, *t);
}

KN_INLINE bool KnParser_iterator_equals2(KnParser *self, void** it, const void** s)
{
    return ((Kinai::Parser*)self)->iterator_equals(*it, *s);
}

KnPerspectiveCamera* KnPerspectiveCamera_PerspectiveCamera(KnPerspectiveCamera *self)
{
    return new Kinai::PerspectiveCamera();
}

KnPerspectiveCamera* KnPerspectiveCamera_PerspectiveCamera2(KnPerspectiveCamera *self, float viewport_width, float viewport_height, float fov, float near_clip, float far_clip)
{
    return new Kinai::PerspectiveCamera(viewport_width, viewport_height, fov, near_clip, far_clip);
}

void KnPerspectiveCamera_DestroyPerspectiveCamera(KnPerspectiveCamera *self)
{
    delete (self);
}

void KnPerspectiveCamera_OnUpdate(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->OnUpdate();
}

void KnPerspectiveCamera_SetViewportSize(KnPerspectiveCamera *self, float width, float height)
{
    return ((Kinai::PerspectiveCamera*)self)->SetViewportSize(width, height);
}

void KnPerspectiveCamera_SetDistance(KnPerspectiveCamera *self, float distance)
{
    return ((Kinai::PerspectiveCamera*)self)->SetDistance(distance);
}

void KnPerspectiveCamera_SetPosition(KnPerspectiveCamera *self, const vec3s* position)
{
    return ((Kinai::PerspectiveCamera*)self)->SetPosition(*position);
}

float KnPerspectiveCamera_GetDistance(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetDistance();
}

const mat4s* KnPerspectiveCamera_GetViewMatrix(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetViewMatrix();
}

mat4s KnPerspectiveCamera_GetViewProjectionMatrix(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetViewProjectionMatrix();
}

vec3s KnPerspectiveCamera_GetUpDirection(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetUpDirection();
}

vec3s KnPerspectiveCamera_GetRightDirection(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetRightDirection();
}

vec3s KnPerspectiveCamera_GetForwardDirection(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetForwardDirection();
}

versors KnPerspectiveCamera_GetOrientation(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetOrientation();
}

const vec3s* KnPerspectiveCamera_GetPosition(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetPosition();
}

float KnPerspectiveCamera_GetPitch(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetPitch();
}

float KnPerspectiveCamera_GetYaw(KnPerspectiveCamera *self)
{
    return ((Kinai::PerspectiveCamera*)self)->GetYaw();
}

bool KnPerspectiveCamera_OnMouseWheel(KnPerspectiveCamera *self, KnMouseWheelEvent* e)
{
    return ((Kinai::PerspectiveCamera*)self)->OnMouseWheel(*e);
}

bool KnPerspectiveCamera_OnMouseMotion(KnPerspectiveCamera *self, KnMouseMotionEvent* event)
{
    return ((Kinai::PerspectiveCamera*)self)->OnMouseMotion(*event);
}

KnPerspectiveCameraController* KnPerspectiveCameraController_PerspectiveCameraController(KnPerspectiveCameraController *self, const KnPerspectiveCameraControllerConfig* config)
{
    return new Kinai::PerspectiveCameraController(*config);
}

void KnPerspectiveCameraController_OnUpdate(KnPerspectiveCameraController *self, float delta)
{
    return ((Kinai::PerspectiveCameraController*)self)->OnUpdate(delta);
}

void KnPerspectiveCameraController_OnEvent(KnPerspectiveCameraController *self, KnEvent* e)
{
    return ((Kinai::PerspectiveCameraController*)self)->OnEvent(*e);
}

void KnPerspectiveCameraController_OnResize(KnPerspectiveCameraController *self, float width, float height)
{
    return ((Kinai::PerspectiveCameraController*)self)->OnResize(width, height);
}

KnPerspectiveCamera* KnPerspectiveCameraController_GetCamera(KnPerspectiveCameraController *self)
{
    return ((Kinai::PerspectiveCameraController*)self)->GetCamera();
}

const KnPerspectiveCamera* KnPerspectiveCameraController_GetCamera2(KnPerspectiveCameraController *self)
{
    return ((Kinai::PerspectiveCameraController*)self)->GetCamera();
}

bool KnPerspectiveCameraController_IsCursorLocked(KnPerspectiveCameraController *self)
{
    return ((Kinai::PerspectiveCameraController*)self)->IsCursorLocked();
}

void KnPerspectiveCameraController_SetCursorLock(KnPerspectiveCameraController *self, bool enabled)
{
    return ((Kinai::PerspectiveCameraController*)self)->SetCursorLock(enabled);
}

bool KnPerspectiveCameraController_IsRotationEnabled(KnPerspectiveCameraController *self)
{
    return ((Kinai::PerspectiveCameraController*)self)->IsRotationEnabled();
}

void KnPerspectiveCameraController_SetRotationEnabled(KnPerspectiveCameraController *self, bool enabled)
{
    return ((Kinai::PerspectiveCameraController*)self)->SetRotationEnabled(enabled);
}




void KnRenderer_Init(KnRenderer *self)
{
    return ((Kinai::Renderer*)self)->Init();
}

void KnRenderer_SetViewport(KnRenderer *self, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    return ((Kinai::Renderer*)self)->SetViewport(x, y, width, height);
}

void KnRenderer_SetClearColor(KnRenderer *self, const vec4s* color)
{
    return ((Kinai::Renderer*)self)->SetClearColor(*color);
}

void KnRenderer_SetClearColor2(KnRenderer *self, float r, float g, float b, float a)
{
    return ((Kinai::Renderer*)self)->SetClearColor(r, g, b, a);
}

void KnRenderer_SetClearColor3(KnRenderer *self, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ((Kinai::Renderer*)self)->SetClearColor(r, g, b, a);
}

void KnRenderer_Clear(KnRenderer *self)
{
    return ((Kinai::Renderer*)self)->Clear();
}

void KnRenderer_DrawIndexed(KnRenderer *self, const KnVertexArray* vertex_array, uint32_t index_count)
{
    return ((Kinai::Renderer*)self)->DrawIndexed(*vertex_array, index_count);
}

void KnRenderer_DrawLines(KnRenderer *self, const KnVertexArray* vertex_array, uint32_t vertex_count)
{
    return ((Kinai::Renderer*)self)->DrawLines(*vertex_array, vertex_count);
}

void KnRenderer_DrawTriangles(KnRenderer *self, const KnVertexArray* vertex_array, uint32_t vertex_count)
{
    return ((Kinai::Renderer*)self)->DrawTriangles(*vertex_array, vertex_count);
}

void KnRenderer_SetLineWidth(KnRenderer *self, float width)
{
    return ((Kinai::Renderer*)self)->SetLineWidth(width);
}

void KnRenderer_Init(KnRenderer *self)
{
    return ((Kinai::Renderer*)self)->Init();
}

void KnRenderer_Shutdown(KnRenderer *self)
{
    return ((Kinai::Renderer*)self)->Shutdown();
}

void KnRenderer_BeginFrame(KnRenderer *self, const KnPerspectiveCamera* camera)
{
    return ((Kinai::Renderer*)self)->BeginFrame(*camera);
}

void KnRenderer_EndFrame(KnRenderer *self)
{
    return ((Kinai::Renderer*)self)->EndFrame();
}

void KnRenderer_OnWindowResize(KnRenderer *self, uint32_t width, uint32_t height)
{
    return ((Kinai::Renderer*)self)->OnWindowResize(width, height);
}

void KnRenderer_Submit(KnRenderer *self, const KnShader* shader, const KnVertexArray* vertex_array, const mat4s* transform)
{
    return ((Kinai::Renderer*)self)->Submit(*shader, *vertex_array, *transform);
}

void KnRenderer_SubmitTriangles(KnRenderer *self, const KnShader* shader, const KnVertexArray* vertex_array, uint32_t vertex_count, const mat4s* transform)
{
    return ((Kinai::Renderer*)self)->SubmitTriangles(*shader, *vertex_array, vertex_count, *transform);
}

void KnRenderer2D_BeginFrame(KnRenderer2D *self, const KnCamera* camera, const mat4s* transform)
{
    return ((Kinai::Renderer2D*)self)->BeginFrame(*camera, *transform);
}

void KnRenderer2D_BeginFrame2(KnRenderer2D *self, const KnOrthographicCamera* camera)
{
    return ((Kinai::Renderer2D*)self)->BeginFrame(*camera);
}

void KnRenderer2D_BeginFrame3(KnRenderer2D *self, const KnPerspectiveCamera* camera)
{
    return ((Kinai::Renderer2D*)self)->BeginFrame(*camera);
}

void KnRenderer2D_Flush(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->Flush();
}

void KnRenderer2D_UpdateViewport(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->UpdateViewport();
}

void KnRenderer2D_EndFrame(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->EndFrame();
}

void KnRenderer2D_DrawCircle(KnRenderer2D *self, const mat4s* transform, const vec4s* color, float thickness, float fade)
{
    return ((Kinai::Renderer2D*)self)->DrawCircle(*transform, *color, thickness, fade);
}

void KnRenderer2D_DrawLine(KnRenderer2D *self, const vec3s* p0, vec3s* p1, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawLine(*p0, *p1, *color);
}

float KnRenderer2D_GetLineWidth(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->GetLineWidth();
}

void KnRenderer2D_SetLineWidth(KnRenderer2D *self, float width)
{
    return ((Kinai::Renderer2D*)self)->SetLineWidth(width);
}

void KnRenderer2D_DrawQuad(KnRenderer2D *self, const vec2s* position, const vec2s* size, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*position, *size, *color);
}

void KnRenderer2D_DrawQuad2(KnRenderer2D *self, const vec3s* position, const vec2s* size, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*position, *size, *color);
}

void KnRenderer2D_DrawQuad3(KnRenderer2D *self, const vec2s* position, const vec2s* size, const KnTexture2D* texture, const vec4s* tint_color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*position, *size, *texture, *tint_color);
}

void KnRenderer2D_DrawQuad4(KnRenderer2D *self, const vec3s* position, const vec2s* size, const KnTexture2D* texture, const vec4s* tint_color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*position, *size, *texture, *tint_color);
}

void KnRenderer2D_DrawQuad5(KnRenderer2D *self, const vec2s* position, const vec2s* size, const KnTexture2D* texture, const vec2s* uvStart, const vec2s* uvEnd, const vec4s* tint_color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*position, *size, *texture, *uvStart, *uvEnd, *tint_color);
}

void KnRenderer2D_DrawQuad6(KnRenderer2D *self, const vec3s* position, const vec2s* size, const KnTexture2D* texture, const vec2s* uvStart, const vec2s* uvEnd, const vec4s* tint_color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*position, *size, *texture, *uvStart, *uvEnd, *tint_color);
}

void KnRenderer2D_DrawQuad7(KnRenderer2D *self, const mat4s* transform, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*transform, *color);
}

void KnRenderer2D_DrawQuad8(KnRenderer2D *self, const mat4s* transform, const KnTexture2D* texture)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*transform, *texture);
}

void KnRenderer2D_DrawQuad9(KnRenderer2D *self, const mat4s* transform, const KnTexture2D* texture, const vec2s* uvStart, const vec2s* uvEnd, const vec4s* tint_color)
{
    return ((Kinai::Renderer2D*)self)->DrawQuad(*transform, *texture, *uvStart, *uvEnd, *tint_color);
}

void KnRenderer2D_DrawRotatedQuad(KnRenderer2D *self, const vec2s* position, const vec2s* size, float rotation, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawRotatedQuad(*position, *size, rotation, *color);
}

void KnRenderer2D_DrawRotatedQuad2(KnRenderer2D *self, const vec3s* position, const vec2s* size, float rotation, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawRotatedQuad(*position, *size, rotation, *color);
}

void KnRenderer2D_DrawRotatedQuad3(KnRenderer2D *self, const vec2s* position, const vec2s* size, float rotation, const KnTexture2D* texture, const vec4s* tintColor)
{
    return ((Kinai::Renderer2D*)self)->DrawRotatedQuad(*position, *size, rotation, *texture, *tintColor);
}

void KnRenderer2D_DrawRotatedQuad4(KnRenderer2D *self, const vec3s* position, const vec2s* size, float rotation, const KnTexture2D* texture, const vec4s* tintColor)
{
    return ((Kinai::Renderer2D*)self)->DrawRotatedQuad(*position, *size, rotation, *texture, *tintColor);
}

void KnRenderer2D_DrawRect(KnRenderer2D *self, const vec3s* position, const vec2s* size, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawRect(*position, *size, *color);
}

void KnRenderer2D_DrawRect2(KnRenderer2D *self, const mat4s* transform, const vec4s* color)
{
    return ((Kinai::Renderer2D*)self)->DrawRect(*transform, *color);
}

KnShader2D* KnRenderer2D_MakeShader(KnRenderer2D *self, void* program_name, void* vertexSrc, void* fragmentSrc)
{
    return ((Kinai::Renderer2D*)self)->MakeShader(*program_name, *vertexSrc, *fragmentSrc);
}

void KnRenderer2D_SetQuadShader(KnRenderer2D *self, KnShader2D* shader)
{
    return ((Kinai::Renderer2D*)self)->SetQuadShader(*shader);
}

void KnRenderer2D_ResetQuadShader(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->ResetQuadShader();
}

void KnRenderer2D_Init(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->Init();
}

void KnRenderer2D_Shutdown(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->Shutdown();
}

KnStatistics* KnRenderer2D_GetStats(KnRenderer2D *self)
{
    return ((Kinai::Renderer2D*)self)->GetStats();
}

void KnRendererAPI_DestroyRendererAPI(KnRendererAPI *self)
{
    delete (self);
}

void KnRendererAPI_Init(KnRendererAPI *self)
{
    return ((Kinai::RendererAPI*)self)->Init();
}

void KnRendererAPI_SetViewport(KnRendererAPI *self, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    return ((Kinai::RendererAPI*)self)->SetViewport(x, y, width, height);
}

void KnRendererAPI_SetClearColor(KnRendererAPI *self, const vec4s* color)
{
    return ((Kinai::RendererAPI*)self)->SetClearColor(*color);
}

void KnRendererAPI_Clear(KnRendererAPI *self)
{
    return ((Kinai::RendererAPI*)self)->Clear();
}

void KnRendererAPI_DrawIndexed(KnRendererAPI *self, const KnVertexArray* vertex_array, uint32_t index_count)
{
    return ((Kinai::RendererAPI*)self)->DrawIndexed(*vertex_array, index_count);
}

void KnRendererAPI_DrawLines(KnRendererAPI *self, const KnVertexArray* vertex_array, uint32_t vertex_count)
{
    return ((Kinai::RendererAPI*)self)->DrawLines(*vertex_array, vertex_count);
}

void KnRendererAPI_DrawTriangles(KnRendererAPI *self, const KnVertexArray* vertexArray, uint32_t vertexCount)
{
    return ((Kinai::RendererAPI*)self)->DrawTriangles(*vertexArray, vertexCount);
}

void KnRendererAPI_SetLineWidth(KnRendererAPI *self, float width)
{
    return ((Kinai::RendererAPI*)self)->SetLineWidth(width);
}

KnRendererAPI* KnRendererAPI_Create(KnRendererAPI *self)
{
    return ((Kinai::RendererAPI*)self)->Create();
}

void KnShader_DestroyShader(KnShader *self)
{
    delete (self);
}

void KnShader_Bind(KnShader *self)
{
    return ((Kinai::Shader*)self)->Bind();
}

void KnShader_Unbind(KnShader *self)
{
    return ((Kinai::Shader*)self)->Unbind();
}

void KnShader_SetInt(KnShader *self, void* name, int value)
{
    return ((Kinai::Shader*)self)->SetInt(*name, value);
}

void KnShader_SetIntArray(KnShader *self, void* name, int* values, uint32_t count)
{
    return ((Kinai::Shader*)self)->SetIntArray(*name, values, count);
}

void KnShader_SetFloat(KnShader *self, void* name, float value)
{
    return ((Kinai::Shader*)self)->SetFloat(*name, value);
}

void KnShader_SetFloat2(KnShader *self, void* name, const vec2s* value)
{
    return ((Kinai::Shader*)self)->SetFloat2(*name, *value);
}

void KnShader_SetFloat3(KnShader *self, void* name, const vec3s* value)
{
    return ((Kinai::Shader*)self)->SetFloat3(*name, *value);
}

void KnShader_SetFloat4(KnShader *self, void* name, const vec4s* value)
{
    return ((Kinai::Shader*)self)->SetFloat4(*name, *value);
}

void KnShader_SetMat4(KnShader *self, void* name, const mat4s* value)
{
    return ((Kinai::Shader*)self)->SetMat4(*name, *value);
}

void* KnShader_GetName(KnShader *self)
{
    return ((Kinai::Shader*)self)->GetName();
}

KnShader* KnShader_Create(KnShader *self, void* filepath, void* program_name)
{
    return ((Kinai::Shader*)self)->Create(*filepath, *program_name);
}

KnShader* KnShader_Create2(KnShader *self, void* name, void* vertexSrc, void* fragmentSrc)
{
    return ((Kinai::Shader*)self)->Create(*name, *vertexSrc, *fragmentSrc);
}

KnShader* KnRenderer2D_Shader2D_GetShader(KnRenderer2D_Shader2D *self)
{
    return ((Kinai::Renderer2D::Shader2D*)self)->GetShader();
}


void KnShaderLibrary_Add(KnShaderLibrary *self, void* name, const KnShader* shader)
{
    return ((Kinai::ShaderLibrary*)self)->Add(*name, *shader);
}

void KnShaderLibrary_Add2(KnShaderLibrary *self, const KnShader* shader)
{
    return ((Kinai::ShaderLibrary*)self)->Add(*shader);
}

KnShader* KnShaderLibrary_Load(KnShaderLibrary *self, void* filepath, void* name)
{
    return ((Kinai::ShaderLibrary*)self)->Load(*filepath, *name);
}

KnShader* KnShaderLibrary_Load2(KnShaderLibrary *self, void* name, void* vertexSrc, void* fragmentSrc)
{
    return ((Kinai::ShaderLibrary*)self)->Load(*name, *vertexSrc, *fragmentSrc);
}

KnShader* KnShaderLibrary_Get(KnShaderLibrary *self, void* name)
{
    return ((Kinai::ShaderLibrary*)self)->Get(*name);
}

bool KnShaderLibrary_Exists(KnShaderLibrary *self, void* name)
{
    return ((Kinai::ShaderLibrary*)self)->Exists(*name);
}

uint32_t KnRenderer2D_Statistics_GetTotalVertexCount(KnRenderer2D_Statistics *self)
{
    return ((Kinai::Renderer2D::Statistics*)self)->GetTotalVertexCount();
}

uint32_t KnRenderer2D_Statistics_GetTotalIndexCount(KnRenderer2D_Statistics *self)
{
    return ((Kinai::Renderer2D::Statistics*)self)->GetTotalIndexCount();
}

void KnRenderer2D_Statistics_Reset(KnRenderer2D_Statistics *self)
{
    return ((Kinai::Renderer2D::Statistics*)self)->Reset();
}

uint32_t KnRenderer2D_Statistics_GetDrawCalls(KnRenderer2D_Statistics *self)
{
    return ((Kinai::Renderer2D::Statistics*)self)->GetDrawCalls();
}

uint32_t KnRenderer2D_Statistics_GetQuadCount(KnRenderer2D_Statistics *self)
{
    return ((Kinai::Renderer2D::Statistics*)self)->GetQuadCount();
}

void KnTexture_DestroyTexture(KnTexture *self)
{
    delete (self);
}

const KnTextureConfig* KnTexture_GetConfig(KnTexture *self)
{
    return ((Kinai::Texture*)self)->GetConfig();
}

uint32_t KnTexture_GetWidth(KnTexture *self)
{
    return ((Kinai::Texture*)self)->GetWidth();
}

uint32_t KnTexture_GetHeight(KnTexture *self)
{
    return ((Kinai::Texture*)self)->GetHeight();
}

uint32_t KnTexture_GetRendererID(KnTexture *self)
{
    return ((Kinai::Texture*)self)->GetRendererID();
}

void* KnTexture_GetPath(KnTexture *self)
{
    return ((Kinai::Texture*)self)->GetPath();
}

void KnTexture_SetData(KnTexture *self, void* data, uint32_t size)
{
    return ((Kinai::Texture*)self)->SetData(data, size);
}

void KnTexture_Bind(KnTexture *self, uint32_t slot)
{
    return ((Kinai::Texture*)self)->Bind(slot);
}

bool KnTexture_IsLoaded(KnTexture *self)
{
    return ((Kinai::Texture*)self)->IsLoaded();
}

bool KnTexture_equals(KnTexture *self, const KnTexture* other)
{
    return ((Kinai::Texture*)self)->equals(*other);
}

KnTexture2D* KnTexture2D_Create(KnTexture2D *self, const KnTextureConfig* config)
{
    return ((Kinai::Texture2D*)self)->Create(*config);
}

KnTexture2D* KnTexture2D_Create2(KnTexture2D *self, void* path, GLenum min_filter, GLenum max_filter)
{
    return ((Kinai::Texture2D*)self)->Create(*path, min_filter, max_filter);
}



KnTimer* KnTimer_Timer(KnTimer *self)
{
    return new Kinai::Timer();
}

void KnTimer_Reset(KnTimer *self)
{
    return ((Kinai::Timer*)self)->Reset();
}

float KnTimer_ElapsedSeconds(KnTimer *self)
{
    return ((Kinai::Timer*)self)->ElapsedSeconds();
}

float KnTimer_ElapsedMS(KnTimer *self)
{
    return ((Kinai::Timer*)self)->ElapsedMS();
}

KnTokenBase* KnTokenBase_TokenBase(KnTokenBase *self, Tp t, void* w, uint32_t r, uint32_t c)
{
    return new Kinai::TokenBase(t, w, r, c);
}

void KnUniformBuffer_DestroyUniformBuffer(KnUniformBuffer *self)
{
    delete (self);
}

void KnUniformBuffer_SetData(KnUniformBuffer *self, const void* data, uint32_t size, uint32_t offset)
{
    return ((Kinai::UniformBuffer*)self)->SetData(data, size, offset);
}

KnUniformBuffer* KnUniformBuffer_Create(KnUniformBuffer *self, uint32_t size, uint32_t binding)
{
    return ((Kinai::UniformBuffer*)self)->Create(size, binding);
}

void KnVertexArray_DestroyVertexArray(KnVertexArray *self)
{
    delete (self);
}

void KnVertexArray_Bind(KnVertexArray *self)
{
    return ((Kinai::VertexArray*)self)->Bind();
}

void KnVertexArray_Unbind(KnVertexArray *self)
{
    return ((Kinai::VertexArray*)self)->Unbind();
}

void KnVertexArray_AddVertexBuffer(KnVertexArray *self, const KnVertexBuffer* vertex_buffer)
{
    return ((Kinai::VertexArray*)self)->AddVertexBuffer(*vertex_buffer);
}

void KnVertexArray_SetIndexBuffer(KnVertexArray *self, const KnIndexBuffer* index_buffer)
{
    return ((Kinai::VertexArray*)self)->SetIndexBuffer(*index_buffer);
}

const KnVertexBuffer* KnVertexArray_GetVertexBuffers(KnVertexArray *self)
{
    return ((Kinai::VertexArray*)self)->GetVertexBuffers();
}

const KnIndexBuffer* KnVertexArray_GetIndexBuffer(KnVertexArray *self)
{
    return ((Kinai::VertexArray*)self)->GetIndexBuffer();
}

KnVertexArray* KnVertexArray_Create(KnVertexArray *self)
{
    return ((Kinai::VertexArray*)self)->Create();
}

void KnVertexBuffer_DestroyVertexBuffer(KnVertexBuffer *self)
{
    delete (self);
}

void KnVertexBuffer_Bind(KnVertexBuffer *self)
{
    return ((Kinai::VertexBuffer*)self)->Bind();
}

void KnVertexBuffer_Unbind(KnVertexBuffer *self)
{
    return ((Kinai::VertexBuffer*)self)->Unbind();
}

void KnVertexBuffer_SetData(KnVertexBuffer *self, const void* data, uint32_t size)
{
    return ((Kinai::VertexBuffer*)self)->SetData(data, size);
}

void KnVertexBuffer_SetLayout(KnVertexBuffer *self, const KnBufferLayout* layout)
{
    return ((Kinai::VertexBuffer*)self)->SetLayout(*layout);
}

const KnBufferLayout* KnVertexBuffer_GetLayout(KnVertexBuffer *self)
{
    return ((Kinai::VertexBuffer*)self)->GetLayout();
}

KnVertexBuffer* KnVertexBuffer_Create(KnVertexBuffer *self, uint32_t size)
{
    return ((Kinai::VertexBuffer*)self)->Create(size);
}

KnVertexBuffer* KnVertexBuffer_Create2(KnVertexBuffer *self, const void* vertices, uint32_t size)
{
    return ((Kinai::VertexBuffer*)self)->Create(vertices, size);
}

void KnWindow_DestroyWindow(KnWindow *self)
{
    delete (self);
}

void KnWindow_OnUpdate(KnWindow *self)
{
    return ((Kinai::Window*)self)->OnUpdate();
}

void* KnWindow_GetNativeWindow(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetNativeWindow();
}

ivec2s KnWindow_GetSize(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetSize();
}

uint32_t KnWindow_GetWidth(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetWidth();
}

uint32_t KnWindow_GetHeight(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetHeight();
}

bool KnWindow_GetRelativeMouseMode(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetRelativeMouseMode();
}

bool KnWindow_IsFocused(KnWindow *self)
{
    return ((Kinai::Window*)self)->IsFocused();
}

bool KnWindow_IsHovered(KnWindow *self)
{
    return ((Kinai::Window*)self)->IsHovered();
}

sg_environment KnWindow_GetSokolEnvironment(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetSokolEnvironment();
}

sg_swapchain KnWindow_GetSokolSwapchain(KnWindow *self)
{
    return ((Kinai::Window*)self)->GetSokolSwapchain();
}

bool KnWindow_IsVSync(KnWindow *self)
{
    return ((Kinai::Window*)self)->IsVSync();
}

void KnWindow_SetVSync(KnWindow *self, bool enabled)
{
    return ((Kinai::Window*)self)->SetVSync(enabled);
}

void KnWindow_SetEventCallback(KnWindow *self, const EventCallback* callback)
{
    return ((Kinai::Window*)self)->SetEventCallback(*callback);
}

void KnWindow_SetTitle(KnWindow *self, void* title)
{
    return ((Kinai::Window*)self)->SetTitle(*title);
}

void KnWindow_SetRelativeMouseMode(KnWindow *self, bool enabled)
{
    return ((Kinai::Window*)self)->SetRelativeMouseMode(enabled);
}

void KnWindow_WarpMouse(KnWindow *self, float x, float y)
{
    return ((Kinai::Window*)self)->WarpMouse(x, y);
}

KnWindow* KnWindow_Create(KnWindow *self, const KnWindowProps* props)
{
    return ((Kinai::Window*)self)->Create(*props);
}

KnWindowCloseEvent* KnWindowCloseEvent_WindowCloseEvent(KnWindowCloseEvent *self)
{
    return new Kinai::WindowCloseEvent();
}

void KnWindowCloseEvent_EVENT_CLASS_TYPE(KnWindowCloseEvent *self, SDL_EVENT_WINDOW_CLOSE_REQUESTED )
{
    return ((Kinai::WindowCloseEvent*)self)->EVENT_CLASS_TYPE();
}

void KnWindowCloseEvent_EVENT_CLASS_CATEGORY(KnWindowCloseEvent *self, EventCategoryApplication )
{
    return ((Kinai::WindowCloseEvent*)self)->EVENT_CLASS_CATEGORY();
}

KnWindowProps* KnWindowProps_WindowProps(KnWindowProps *self, void* title, uint32_t width, uint32_t height, bool fullscreen, bool no_vsync)
{
    return new Kinai::WindowProps(*title, width, height, fullscreen, no_vsync);
}

KnWindowResizeEvent* KnWindowResizeEvent_WindowResizeEvent(KnWindowResizeEvent *self, uint32_t width, uint32_t height)
{
    return new Kinai::WindowResizeEvent(width, height);
}

uint32_t KnWindowResizeEvent_GetWidth(KnWindowResizeEvent *self)
{
    return ((Kinai::WindowResizeEvent*)self)->GetWidth();
}

uint32_t KnWindowResizeEvent_GetHeight(KnWindowResizeEvent *self)
{
    return ((Kinai::WindowResizeEvent*)self)->GetHeight();
}

void* KnWindowResizeEvent_ToString(KnWindowResizeEvent *self)
{
    return ((Kinai::WindowResizeEvent*)self)->ToString();
}

void KnWindowResizeEvent_EVENT_CLASS_TYPE(KnWindowResizeEvent *self, SDL_EVENT_WINDOW_RESIZED )
{
    return ((Kinai::WindowResizeEvent*)self)->EVENT_CLASS_TYPE();
}

void KnWindowResizeEvent_EVENT_CLASS_CATEGORY(KnWindowResizeEvent *self, EventCategoryApplication )
{
    return ((Kinai::WindowResizeEvent*)self)->EVENT_CLASS_CATEGORY();
}

