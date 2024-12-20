//
// Created by jérémie on 11/12/2024.
// This class is intended to manage the analysis of images in order to be used with the PeopleFinder.
//

#ifndef IMAGEANALYSER_H
#define IMAGEANALYSER_H

#include "image.h"
#include "opencv2/opencv.hpp"
#include <vector>

class ImageAnalyser {
    Image image;
    int actualX;
    int actualY;
    int actualWidth;
    int actualHeight;

public:
    ImageAnalyser();

    ImageAnalyser(Image *image);

    ImageAnalyser(Image);
    void LoadImage(const char*);
    void LoadImage(cv::Mat);
    double getCoef(double, double, double);
    std::vector<Image> findHead();
    Image getZoomedFaces(double);
    void SaveImage(const char*);
    Image* getImage();
};


/*const char* filename = "example.jpg";

    // Load the image
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 1;
    }

    std::cout << "Loaded image: " << filename << "\n";
    std::cout << "Dimensions: " << width << "x" << height << ", Channels: " << channels << "\n";
 */


#endif //IMAGEANALYSER_H
