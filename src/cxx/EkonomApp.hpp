#include <utility>
#include <cstdint>

#include <AppCore/AppCore.h>
#include <JavaScriptCore/JavaScript.h>
#include <Ultralight/View.h>
#include <Ultralight/Listener.h>

#include <spdlog/spdlog.h>
#include <OpenXLSX.hpp>

namespace ekonom {

    using namespace ultralight;

    class EkonomApp : public AppListener,
        public WindowListener,
        public LoadListener,
        public ViewListener {
    public:
        inline static ekonom::EkonomApp* _instance;

        std::shared_ptr<spdlog::logger> logger;

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

        void OnAddConsoleMessage(ultralight::View* caller,
            MessageSource source,
            MessageLevel level,
            const String& message,
            uint32_t line_number,
            uint32_t column_number,
            const String& source_id) override;
    };
}
