#include "defines/defines.hpp"
#include "EkonomApp.hpp"


void common_start() {
    ekonom::EkonomApp app;

    app.Run();
}


#ifdef _WIN32
#include <windows.h>

int32_t CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    PSTR lpCmdLine, INT nCmdShow) 
{
    common_start();
    return 0;
}

#else

int main(){
    common_start();
}

#endif
