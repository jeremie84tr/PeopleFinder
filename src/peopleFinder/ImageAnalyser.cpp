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


ImageAnalyser::ImageAnalyser(): image(0,0,0,nullptr), actualX(0), actualY(0), actualHeight(0), actualWidth(0) {
}

ImageAnalyser::ImageAnalyser(Image image): image(0,0,0,nullptr), actualX(0), actualY(0), actualWidth(0), actualHeight(0) {
    this->image = image.crop(0,0,image.getWidth(),image.getHeight());
}

/**
 *
 * @param filename the filename/filepath of the image you want to load
 */
void ImageAnalyser::LoadImage(const char *filename) {
    // Load the image
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    this->image = Image(width, height, channels, data);
}

void ImageAnalyser::LoadImage(cv::Mat image) {
    this->image = Image(image.cols, image.rows, image.channels(), image.data);
}


/**
 * 
 * @return The vector of all the heads found in the image
 */
std::vector<Image> ImageAnalyser::findHead() {

    CascadeClassifier face_cascade;
    face_cascade.load("data/cascade/haarcascade_frontalface_default.xml");

    Mat *img = this->getImage()->getMat();

    double coef_x = 460.0 / this->getImage()->getWidth();
    double coef_y = 460.0 / this->getImage()->getHeight();
    double coef;
    if (coef_x < coef_y) {
        coef = coef_x;
    } else {
        coef = coef_y;
    }

    resize(*img,*img,Size(),coef,coef,INTER_LINEAR_EXACT);

    Mat gray;
    std::vector<Rect> faces;
    if(img->channels()>1){
        cvtColor(*img,gray,COLOR_BGR2GRAY);
    }
    else{
        gray = img->clone();
    }
    equalizeHist( gray, gray );

    std::cout << "apres gray" << std::endl;

    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );

    std::vector< std::vector<Point2f> > shapes;

    std::vector<Image> images;

    std::cout << faces.size() << " faces found" << std::endl;

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        images.push_back(this->image.crop(faces[i].x / coef, faces[i].y / coef, faces[i].width / coef, faces[i].height / coef));
    }

    return images;
}

double ImageAnalyser::getCoef(double objectiveWidth, double width, double height) {
    if (width <= 0) {
        width = 1;
    }
    if (height <= 0) {
        height = 1;
    }
    double coef_x = objectiveWidth / width;
    double coef_y = objectiveWidth / height;
    if (coef_x < coef_y) {
        return coef_x;
    } else {
        return coef_y;
    }
}


Image ImageAnalyser::getZoomedFaces(double coef_adaptation) {
    CascadeClassifier face_cascade;
    face_cascade.load("data/cascade/haarcascade_frontalface_default.xml");

    Mat *img = this->getImage()->getMat();


    double coef = getCoef(460, this->getImage()->getWidth(), this->getImage()->getWidth());

    resize(*img,*img,Size(),coef,coef,INTER_LINEAR_EXACT);

    Mat gray;
    std::vector<Rect> faces;
    if(img->channels()>1){
        cvtColor(*img,gray,COLOR_BGR2GRAY);
    }
    else{
        gray = img->clone();
    }
    equalizeHist( gray, gray );

    std::cout << "apres gray" << std::endl;

    face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );

    std::vector< std::vector<Point2f> > shapes;

    std::vector<Image> images;

    std::cout << faces.size() << " faces found" << std::endl;

    int minX = -1;
    int minY = -1;
    int maxX = 0;
    int maxY = 0;


    for (int i = 0; i < faces.size(); ++i) {
        if (minX == -1 || faces.data()[i].x < minX) {
            minX = faces.data()[i].x;
        }
        if (minY == -1 || faces.data()[i].y < minY) {
            minY = faces.data()[i].y;
        }
        if (maxX == 0 || faces.data()[i].x + faces.data()[i].width > maxX) {
            maxX = faces.data()[i].x + faces.data()[i].width;
        }
        if (maxY == 0 || faces.data()[i].y + faces.data()[i].height > maxY) {
            maxY = faces.data()[i].y + faces.data()[i].height;
        }
    }

    if (minX == -1) {
        minX = 0;
        minY = 0;
        maxX = this->image.getWidth() * coef;
        maxY = this->image.getHeight() * coef;
    }

    actualX += (minX - actualX) * coef_adaptation;
    actualY += (minY - actualY) * coef_adaptation;
    actualWidth += ((maxX - minX) - actualWidth) * coef_adaptation;
    actualHeight += ((maxY - minY) - actualHeight) * coef_adaptation;

    return this->image.crop(actualX / coef, actualY / coef, actualWidth / coef, actualHeight / coef);
}


/**
 *
 * @param filename the filename/filepath where you want to save the image
 */
void ImageAnalyser::SaveImage(const char * filename) {
    this->image.save(filename);
}

Image *ImageAnalyser::getImage() {
    return &this->image;
}



