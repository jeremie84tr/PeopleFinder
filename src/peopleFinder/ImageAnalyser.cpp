//
// Created by jérémie on 11/12/2024.
//

#include "ImageAnalyser.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#endif //STB_IMAGE_IMPLEMENTATION

ImageAnalyser::ImageAnalyser() {
    this->image = nullptr;
}

ImageAnalyser::ImageAnalyser(Image image) {
    this->image = &image;
}

/**
 *
 * @param filename the filename/filepath of the image you want to load
 */
void ImageAnalyser::LoadImage(const char *filename) {
    // Load the image
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    this->image = new Image(width, height, channels, data);
}

/**
 * 
 * @return The vector of all the heads found in the image
 */
std::vector<Image*> ImageAnalyser::findHead() {
    //TODO: cette fonction devra chercher toutes les têtes dans une image
    std::vector<Image*> ret;
    return ret;
}

/**
 *
 * @param filename the filename/filepath where you want to save the image
 */
void ImageAnalyser::SaveImage(const char * filename) {
    this->image->save(filename);
}

Image *ImageAnalyser::getImage() {
    return this->image;
}



