#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>
#include <tesseract/baseapi.h>
#include "../include/window_manager/X11/X11Manager.h"

const cv::Rect scoreRect {600, 80, 200, 20};
const cv::Rect gameRect {40, 20, 480, 560};

int launch(TouhouBot::X11Manager window_manager)
{
    while (true) {
        char *image = window_manager.getImage();
        if (image == nullptr)
            return -1;
        cv::Mat screenshot = window_manager.getMatrix();
        cv::Mat grayscale;
        //cv::cvtColor(screenshot, grayscale, cv::COLOR_BGR2GRAY);

        cv::resize(screenshot, screenshot, cv::Size(801, 601));  // Redimensionnement
        // cv::normalize(image, image, 0, 1, cv::NORM_MINMAX); // Normalisation
        // grayscale = (grayscale - 128.0) / 128.0;
        cv::Mat score = screenshot(scoreRect);
        cv::Mat game = screenshot(gameRect);
        /* tesseract::TessBaseAPI tess;
        tess.Init(nullptr, "eng");
        tess.SetImage(score.data, score.cols, score.rows, 1, score.step);

        std::string results = tess.GetUTF8Text();
        if (!results.empty()) {
            std::cout << "Detected Text : " << results << std::endl;
            results.erase(0, results.find_first_of(' ') + 1);
            int true_score = std::stoi(results);
            std::cout << "Detected Text : " << true_score << std::endl;
        }
        tess.End(); */

        cv::imshow("Game", game);
        cv::imshow("Score", score);
        //cv::imshow("Score", score);

        if (cv::waitKey(1) == 'q')
            break;
    }
    cv::destroyAllWindows();
}