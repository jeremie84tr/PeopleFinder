//
// Created by jérémie on 11/12/2024.
// This class is intended to manage the analysis of images in order to be used with the PeopleFinder.
//

#ifndef IMAGEANALYSER_H
#define IMAGEANALYSER_H

#include "image.h"
#include <vector>

class ImageAnalyser {
    Image* image;

public:
    ImageAnalyser();
    ImageAnalyser(Image);
    void LoadImage(const char*);
    std::vector<Image*> findHead();
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
