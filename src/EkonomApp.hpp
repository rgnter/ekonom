

#include <AppCore/AppCore.h>

namespace ekonom {

    using namespace ultralight;

    class EkonomApp : public AppListener,
                      public WindowListener,
                      public LoadListener,
                      public ViewListener {
    private:
        RefPtr<App>     app;
        RefPtr<Window>  window;
        RefPtr<Overlay> overlay;

    public:
        EkonomApp();
        ~EkonomApp() override;

    public:
        void Run();

    public:
        void OnClose() override;
        void OnResize(uint32_t width, uint32_t height) override;

    };

}
