//
// Created by jérémie on 11/12/2024.
//

#include "ImageAnalyser.h"

ImageAnalyser::ImageAnalyser() {
    this->image = nullptr;
}

ImageAnalyser::ImageAnalyser(Image image) {
    this->image = &image;
}


void ImageAnalyser::LoadImage(const char *filename) {
    // Load the image
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    this->image = new Image(width, height, channels, data);
}

std::vector<Image*> ImageAnalyser::findHead() {
    //TODO: cette fonction devra chercher toutes les têtes dans une image
    std::vector<Image*> ret;
    return ret;
}


