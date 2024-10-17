//
// Created by matuyuhi on 2024/10/08.
//

#include "SDK/SDKCore.h"
#include <iostream>

int main()
{
    try {
        // bool success = SDKCore::CreatePlaySession("1", "2");
        bool success = SDKCore::PostPlayersPositionLog("1", "20");
        if (success) {
            std::cout << "Play session created successfully!" << std::endl;
        } else {
            std::cerr << "Failed to create play session." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
