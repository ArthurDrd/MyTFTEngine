#include <Engine.h>
#include <iostream>

int main() {
    std::cout << "[Game] Starting Scuffed TFT..." << std::endl;

    MyTFTEngine::Application application;

    if (application.Initialize()) {
        application.Run();
    }
    else {
        std::cerr << "[Game] Engine initialization failed! Aborting." << std::endl;
    }

    application.Shutdown();
    return 0;
}