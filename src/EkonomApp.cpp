#include "EkonomApp.hpp"


ekonom::EkonomApp::EkonomApp() {
    this->application = App::Create(Settings{
            "rgnt", "ekonom_app", ".", false, false
    });

    this->window = Window::Create(this->application->main_monitor(), 1024, 512,
                                  false, kWindowFlags_Titled | kWindowFlags_Resizable);

    this->overlay = Overlay::Create(*window, 1, 1, 0, 0);
}

ekonom::EkonomApp::~EkonomApp() {

}

void ekonom::EkonomApp::Run() {
    this->overlay->view()->LoadURL("file:///assets/interface/app.html");


    (*this->application).set_listener(this);
    this->window->set_listener(this);
    this->overlay->view()->set_load_listener(this);
    this->overlay->view()->set_view_listener(this);

    OnResize(this->window->width(), this->window->height());
    ShowInspector();


    this->application->Run();
}


void ekonom::EkonomApp::OnResize(uint32_t width, uint32_t height) {
    this->overlay->Resize(width, height);
}

void ekonom::EkonomApp::OnChangeURL(ultralight::View *caller, const ultralight::String &url) {
    printf("%s\n", url.utf8().data());
}

void ekonom::EkonomApp::OnChangeTitle(ultralight::View *caller, const ultralight::String &title) {
    this->window->SetTitle(title.utf8().data());
}

void ekonom::EkonomApp::ShowInspector() {
    RefPtr<View> inspector = this->overlay->view()->inspector();
    inspector->Resize(1024, 100);

    RefPtr<Overlay> inspectorOverlay = Overlay::Create(*this->window, *inspector, 0, 0);
}

void ekonom::EkonomApp::OnDOMReady(ultralight::View *caller, uint64_t frame_id, bool is_main_frame,
                                   const ultralight::String &url) {
    Ref<JSContext> ctxLock = caller->LockJSContext();
    JSContextRef ctx = ctxLock.get();

    auto funcName = JSStringCreateWithUTF8CString("test");
    auto funcLmb = [](JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount,
                      const JSValueRef arguments[], JSValueRef *exception) -> JSValueRef {
        spdlog::info("píča");
        return nullptr;
    };


    JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, funcName, funcLmb);


    JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
    JSObjectSetProperty(ctx, globalObj, funcName, func, 0, 0);

    JSStringRelease(funcName);
}

void ekonom::EkonomApp::OnClose(ultralight::Window* window) {
    spdlog::info("Close window call");
    this->application->Quit();
}

void ekonom::EkonomApp::OnResize(ultralight::Window *window, uint32_t width_px, uint32_t height_px) {

}

