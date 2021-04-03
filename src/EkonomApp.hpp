

#ifdef WIN32 
    #include <windows.h>
#endif

#include <AppCore/AppCore.h>
#include <JavaScriptCore/JavaScript.h>
#include <Ultralight/View.h>
#include <Ultralight/Listener.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <OpenXLSX.hpp>

#include "defines/defines.hpp"

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

    private:
        bool ultralightDebug = false;
        bool ekonomDebug = false;
    

    public:
        EkonomApp();

    public:
        void Run();
        void ShowInspector();

        void showConsole();
        void switchUltralightDebug();
        void switchEkonomDebug();

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
