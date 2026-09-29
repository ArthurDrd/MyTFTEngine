#include <Engine.h>
#include "BoardLayer.h"
#include <iostream>

int main() {
    std::cout << "[Game] Starting Scuffed TFT..." << std::endl;

    MyTFTEngine::Application app;

    if (!app.Initialize()) {
        std::cerr << "[Game] Engine initialization failed! Aborting." << std::endl;
        return -1;
    }

    app.PushLayer(new MyTFTGame::BoardLayer());

    app.Run();
    app.Shutdown();

    return 0;
}