#ifndef OPENCVTESTS_X11MANAGER_H
#define OPENCVTESTS_X11MANAGER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace TouhouBot {

    class X11Manager {
        public :
            explicit X11Manager(std::string &target_window_name);
            ~X11Manager();
            char *getImage();
            cv::Mat getMatrix();
            bool isWindowClosed();

        private :
            void setUpManager();

            std::string m_target_window_name;
            XWindowAttributes m_window_attributes;
            Window m_target_window = 0;
            Display *m_display;
            XImage *m_image;
    };

} // TouhouBot

#endif //OPENCVTESTS_X11MANAGER_H
