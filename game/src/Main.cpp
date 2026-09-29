#include <Engine.h>
#include <iostream>

int main() {
    std::cout << "[Game] Starting Scuffed TFT..." << std::endl;

    MyTFTEngine::Application application;

    if (!application.Initialize()) {
        std::cerr << "[Game] Engine initialization failed! Aborting." << std::endl;
        return -1;
    }

    application.Run();

    application.Shutdown();
    return 0;
}