#include "../../../include/window_manager/X11/X11Manager.h"

// Constructor && Destructor

TouhouBot::X11Manager::X11Manager(std::string &target_window_name) : m_target_window_name{target_window_name}
{
    m_display = XOpenDisplay(nullptr);
    if (m_display == nullptr)
        std::cerr << "Failed to open display" << std::endl;
    setUpManager();
}

TouhouBot::X11Manager::~X11Manager()
{
    XCloseDisplay(m_display);
}

// Methods

void TouhouBot::X11Manager::setUpManager()
{
    Window parentWindow = 0;
    Window* childWindows = nullptr;
    unsigned int numChildWindows;
    if (m_display == nullptr)
        return;
    Window root = DefaultRootWindow(m_display);

    XQueryTree(m_display, root, &root, &parentWindow, &childWindows, &numChildWindows);
    for (unsigned int i = 0; i < numChildWindows; i += 1) {
        char *windowName;
        XFetchName(m_display, childWindows[i], &windowName);
        std::string windowString {windowName};
        if (windowName == "NULL")
            std::cerr << "Game not launched" << std::endl;
        if (windowName != nullptr && windowString.find(m_target_window_name) != std::string::npos) {
            m_target_window = childWindows[i];
            break;
        }
    }
    XGetWindowAttributes(m_display, m_target_window, &m_window_attributes);
    m_image = XGetImage(m_display, m_target_window, 0, 0, m_window_attributes.width,
                              m_window_attributes.height, AllPlanes, ZPixmap);
}

char *TouhouBot::X11Manager::getImage()
{
    XDestroyImage(m_image);
    m_image = XGetImage(m_display, m_target_window, 0, 0, m_window_attributes.width,
                              m_window_attributes.height, AllPlanes, ZPixmap);
    return m_image->data;
}

cv::Mat TouhouBot::X11Manager::getMatrix()
{
    cv::Mat screenshot{m_window_attributes.height, m_window_attributes.width, CV_8UC4, m_image->data};
    return screenshot;
}

bool TouhouBot::X11Manager::isWindowClosed()
{
    XEvent event;
    XCheckTypedWindowEvent(m_display, m_target_window, DestroyNotify, &event);
    return event.type == DestroyNotify;
}
