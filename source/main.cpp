#include <string>
#include <thread>
#include "../include/window_manager/X11/X11Manager.h"
#include "../include/TouhouBot.h"

int main() {
    std::string targetWindowTitle {"Touhou Ghostly Dream"};
    TouhouBot::X11Manager window_manager = TouhouBot::X11Manager{targetWindowTitle};
    launch(window_manager);
    return 0;
}
