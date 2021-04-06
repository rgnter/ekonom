#include "EkonomApp.hpp"

bool _showConsole() {
#ifdef WIN32 
    AllocConsole();

    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);

    spdlog::info("Console attached");
    return true;
#else
    spdlog::warn("Console not implemented for this OS");
    return false;
#endif
}

ekonom::EkonomApp::EkonomApp() {

    this->application = App::Create(Settings{
            "rgnt", "ekonom_app", "assets/", false, false
    });

    this->window = Window::Create(this->application->main_monitor(), 1024, 512,
                                  false, kWindowFlags_Titled);
    this->window->MoveToCenter();
    this->overlay = Overlay::Create(*window, 1, 1, 0, 0);
}

void ekonom::EkonomApp::Run() {
    _instance = this;
    this->overlay->view()->LoadURL("file:///app.html");

    this->application->set_listener(this);
    this->window->set_listener(this);
    this->overlay->view()->set_load_listener(this);
    this->overlay->view()->set_view_listener(this);

    OnResize(this->window.get(), this->window->width(), this->window->height());

    this->application->Run();
}

void ekonom::EkonomApp::showConsole()
{
    _showConsole();
}

void ekonom::EkonomApp::switchUltralightDebug()
{
    this->ultralightDebug = !this->ultralightDebug;
    spdlog::info("Ultralight debugging is now {}", this->ultralightDebug ? "active" : "inactive");
}

void ekonom::EkonomApp::switchEkonomDebug()
{
    this->ekonomDebug = !this->ekonomDebug;
    spdlog::info("Ekonom debugging is now {}", this->ekonomDebug ? "active" : "inactive");
}

void ekonom::EkonomApp::OnClose(ultralight::Window* window) {
    spdlog::info("Close window call");
    this->application->Quit();
}

void ekonom::EkonomApp::OnResize(ultralight::Window* window, uint32_t width_px, uint32_t height_px) {
    this->overlay->Resize(width_px, height_px);
    spdlog::debug("Resize window(0x{:x}) to {}x{x}", window->native_handle(), width_px, height_px);
}

void ekonom::EkonomApp::OnChangeURL(ultralight::View *caller, const ultralight::String &url) {
    spdlog::debug("URL Switch to '{}'", url.utf8().data());
}

void ekonom::EkonomApp::OnChangeTitle(ultralight::View *caller, const ultralight::String &title) {
    this->window->SetTitle(title.utf8().data());
}

void ekonom::EkonomApp::ShowInspector() {
    RefPtr<View> inspector = this->overlay->view()->inspector();
    inspector->Resize(1024, 100);

    RefPtr<Overlay> inspectorOverlay = Overlay::Create(*this->window, *inspector, 0, 0);
}


void bindJSFunction(const char* functionName, JSContextRef& ctx, JSObjectCallAsFunctionCallback callback) 
{
    auto funcName = JSStringCreateWithUTF8CString(functionName);

    JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, funcName, callback);
    JSObjectRef globalObj = JSContextGetGlobalObject(ctx);

    JSObjectSetProperty(ctx, globalObj, funcName, func, 0, 0);
    JSStringRelease(funcName);
}

void ekonom::EkonomApp::OnDOMReady(ultralight::View *caller, uint64_t frame_id, bool is_main_frame,
                                   const ultralight::String &url) {
    Ref<JSContext> ctxLock = caller->LockJSContext();
    JSContextRef ctx = ctxLock.get();

    auto funcQuit = [](JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
        const JSValueRef arguments[], JSValueRef* exception)
    {
        auto instance = ekonom::EkonomApp::_instance;
        instance->OnClose(instance->window.get());

        return JSValueMakeNull(ctx);
    };
    bindJSFunction("_quit", ctx, funcQuit);

    auto funcDebugUltralight = [](JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
        const JSValueRef arguments[], JSValueRef* exception)
    {
        auto instance = ekonom::EkonomApp::_instance;
        instance->switchUltralightDebug();

        return JSValueMakeNull(ctx);
    };
    auto funcDebugEkonom = [](JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
        const JSValueRef arguments[], JSValueRef* exception)
    {
        auto instance = ekonom::EkonomApp::_instance;
        instance->switchEkonomDebug();

        return JSValueMakeNull(ctx);
    };
    auto funcShowConsole = [](JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
        const JSValueRef arguments[], JSValueRef* exception)
    {
        auto instance = ekonom::EkonomApp::_instance;
        instance->showConsole();

        return JSValueMakeNull(ctx);
    };
    bindJSFunction("_settings_debugUltralightSwitch", ctx, funcDebugUltralight);
    bindJSFunction("_settings_debugEkonomSwitch", ctx, funcDebugEkonom);
    bindJSFunction("_settings_showDebugConsole", ctx, funcShowConsole);

    this->window->Show();
}

const char* sourceName(ultralight::MessageSource level) {
    switch (level) {
        case ultralight::MessageSource::kMessageSource_XML: return "XML";
        case ultralight::MessageSource::kMessageSource_JS: return "JavaScript";
        case ultralight::MessageSource::kMessageSource_Network: return "Network";
        case ultralight::MessageSource::kMessageSource_ConsoleAPI: return "Console";
        case ultralight::MessageSource::kMessageSource_Storage: return "Storage";
        case ultralight::MessageSource::kMessageSource_AppCache: return "AppCache";
        case ultralight::MessageSource::kMessageSource_Rendering: return "Rendering";
        case ultralight::MessageSource::kMessageSource_CSS: return "CSS";
        case ultralight::MessageSource::kMessageSource_Security: return "Security";
        case ultralight::MessageSource::kMessageSource_ContentBlocker: return "ContentBlock";
        case ultralight::MessageSource::kMessageSource_Other: return "Other";
    }
    return "???";
}

void ekonom::EkonomApp::OnAddConsoleMessage(ultralight::View* caller,
    MessageSource source,
    MessageLevel level,
    const String& message,
    uint32_t line_number,
    uint32_t column_number,
    const String& source_id) {

    spdlog::level::level_enum spdlogLevel;
    switch (level) {
    case MessageLevel::kMessageLevel_Warning:   spdlogLevel = spdlog::level::warn;  break;
        case MessageLevel::kMessageLevel_Error: spdlogLevel = spdlog::level::err;   break;
        case MessageLevel::kMessageLevel_Debug: spdlogLevel = spdlog::level::debug; break;
        case MessageLevel::kMessageLevel_Info:  spdlogLevel = spdlog::level::info;  break;
        default: spdlogLevel = spdlog::level::info;  break;
    }
    // todo enable ultralight debug
    spdlog::log(spdlogLevel, "[{} {}@({}:{})] {}", sourceName(source), source_id.utf8().data(), line_number, column_number, message.utf8().data());
}