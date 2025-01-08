#include <charconv>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"
#include "ImageAnalyser.h"

int main() {
    ImageAnalyser image_analyser = ImageAnalyser();

    std::string sourceName = "images_source/";
    std::string file = "diplome2";
    sourceName += file + ".jpg";
    image_analyser.LoadImage(sourceName.c_str());

    // std::vector<Image> faces = image_analyser.findHead();
    // std::string filename;
    // Image* image;
    // std::cout << faces.size() << " faces" << std::endl;
    // for (int i=0; i<faces.size(); i++) {
    //     std::cout << "face found" << std::endl;
    //     image = &faces.data()[i];
    //     filename = file + "_face";
    //     filename += std::to_string(i);
    //     filename += ".png";
    //     cv::imshow("Image", *image->getMat());
    //     cv::waitKey(100);
    //     image->save(filename.c_str());
    //     filename = file + "_face";
    //     filename += std::to_string(i);
    //     filename += "edged.png";
    //     image->edgeDetection().save(filename.c_str());
    // }
    cv::Mat camImage;
    cv::VideoCapture camera(0);
    Image* zoomedFaces;
    double coef;
    while(true) {
        camera.read(camImage);
        image_analyser.LoadImage(camImage);
        zoomedFaces = image_analyser.getZoomedFaces(0.3);
        camImage = *zoomedFaces->getMat();
        coef = image_analyser.getCoef(480, camImage.cols, camImage.rows);
        cv::resize(camImage, camImage, cv::Size(), coef, coef, cv::INTER_LINEAR );
        cv::imshow("Image", camImage);
        cv::waitKey(1);
        delete zoomedFaces;
    }
    cv::destroyAllWindows();
    return 0;
}
