//
// Created by jérémie on 11/12/2024.
//

#include "ImageAnalyser.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#endif //STB_IMAGE_IMPLEMENTATION
#include "opencv2/opencv.hpp"
#include "opencv2/face/facemark.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

#include <iostream>

using namespace cv;
using namespace cv::face;


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

    CascadeClassifier face_cascade;
    face_cascade.load("data/cascade/haarcascade_frontalface_default.xml");

    Mat *img = this->getImage()->getMat();

    resize(*img,*img,Size(460,460),0,0,INTER_LINEAR_EXACT);

    Mat gray;
    std::vector<Rect> faces;
    if(img->channels()>1){
        cvtColor(*img,gray,COLOR_BGR2GRAY);
    }
    else{
        gray = img->clone();
    }
    equalizeHist( gray, gray );

    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );

    std::vector< std::vector<Point2f> > shapes;

    std::vector<Image*> images;

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        images.push_back(this->image->crop(faces[i].x, faces[i].y, faces[i].width, faces[i].height));
    }

    return images;
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



