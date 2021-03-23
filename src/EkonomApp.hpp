#include <AppCore/AppCore.h>
#include <JavaScriptCore/JavaScript.h>
#include <Ultralight/View.h>
#include <Ultralight/Listener.h>
#include <spdlog/spdlog.h>
#include <windows.h>


namespace ekonom {

    using namespace ultralight;

    class EkonomApp : public AppListener,
        public WindowListener,
        public LoadListener,
        public ViewListener {
    public:
        /**
        * this unholy instance for c-callback function
        * im really sorry for this. i truly am.
        */
        inline static ekonom::EkonomApp* _instance;

        RefPtr<App> application;
        RefPtr<Window> window;
        RefPtr<Overlay> overlay;

    public:
        EkonomApp();

    public:
        void Run();
        void ShowInspector();

    public:
        void OnClose(ultralight::Window* window) override;
        void OnResize(ultralight::Window* window, uint32_t width_px, uint32_t height_px) override;
        void OnChangeURL(ultralight::View* caller, const String& url) override;
        void OnChangeTitle(ultralight::View* caller, const String& title) override;
        void OnDOMReady(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const String& url) override;

    };
}
