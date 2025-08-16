#include <iostream>
#include <memory>
#include <stdexcept>
#include <signal.h>
#include "Menu.h"
#include "Library.h"
#include "Utils.h"

// Global variable to access library for signal handler
std::unique_ptr<Library> g_library = nullptr;

// Signal handler for graceful shutdown
void signalHandler(int signal) {
    if (g_library) {
        std::cout << "\nDang luu du lieu truoc khi thoat..." << std::endl;
        g_library->saveData();
        std::cout << "Da luu du lieu thanh cong!" << std::endl;
    }
    exit(signal);
}

int main() {
    try {
        // Set console encoding for Windows
        #ifdef WIN32
        system("chcp 65001 > nul");
        #endif

        std::cout << "=== HE THONG QUAN LY THU VIEN (LMS) ===" << std::endl;
        std::cout << "Version: 1.0.0" << std::endl;
        std::cout << "Platform: " << Utils::getPlatformName() << std::endl;
        std::cout << "C++ Standard: C++20" << std::endl;
        std::cout << "=========================================" << std::endl << std::endl;

        // Initialize library
        g_library = std::make_unique<Library>("Thu Vien Quoc Gia", 
                                            "123 Duong ABC, Ha Noi", 
                                            "024-12345678", 
                                            "thuvien@example.com");

        // Set up signal handlers for graceful shutdown
        signal(SIGINT, signalHandler);   // Ctrl+C
        signal(SIGTERM, signalHandler);  // Termination signal
        
        #ifdef WIN32
        signal(SIGBREAK, signalHandler); // Windows Ctrl+Break
        #endif

        // Create and run menu system
        Menu menu(*g_library);
        menu.run();

        std::cout << "\nCam on ban da su dung he thong!" << std::endl;
        std::cout << "Hen gap lai!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Loi nghiem trong: " << e.what() << std::endl;
        std::cerr << "Vui long kiem tra lai he thong!" << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Loi khong xac dinh xay ra!" << std::endl;
        std::cerr << "Vui long kiem tra lai he thong!" << std::endl;
        return 1;
    }

    return 0;
}
