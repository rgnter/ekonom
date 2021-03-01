
#include <Ultralight/View.h>
#include <Ultralight/Listener.h>

#include "EkonomApp.hpp"

ekonom::EkonomApp::EkonomApp() {
    this->app = App::Create(Settings{
        "rgnt", "ekonom_app", ".", false, false
    });
    this->window = Window::Create(this->app->main_monitor(), 1024, 512,
                                  false, kWindowFlags_Titled);

    this->app->set_window(*window);
    this->overlay = Overlay::Create(*window, 1, 1, 0, 0);

    this->app->set_listener(this);
    this->window->set_listener(this);

    this->overlay->view()->set_load_listener(this);
    this->overlay->view()->set_view_listener(this);
}

ekonom::EkonomApp::~EkonomApp() {

}

void ekonom::EkonomApp::Run() {
    this->app->Run();
}


void ekonom::EkonomApp::OnClose() {

}

void ekonom::EkonomApp::OnResize(uint32_t width, uint32_t height) {
    this->overlay->Resize(width, height);
}

