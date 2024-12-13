//
// Created by jérémie on 11/12/2024.
//

#include "ImageAnalyser.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#endif //STB_IMAGE_IMPLEMENTATION
// #include "opencv2/opencv.hpp"
// #include "opencv2/facemark.hpp"
// #include "opencv2/face.hpp"
// #include "opencv2/highgui.hpp"
// #include "opencv2/imgproc.hpp"
// #include "opencv2/objdetect.hpp"

#include <iostream>

// using namespace cv;
// using namespace cv::face;


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
    // CascadeClassifier face_cascade;
    // face_cascade.load("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/data/cascade/haarcascade_frontalcatface.xml");
    //
    // Mat img = imread("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/dictionnary/jeremie/entree.png");//TODO: convertir image vers Mat
    // Ptr<Facemark> facemark = createFacemarkKazemi();
    // facemark->loadModel("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/data/model/lbfmodel.yaml");
    // std::cout<<"Loaded model"<<std::endl;
    //
    // resize(img,img,Size(460,460),0,0,INTER_LINEAR_EXACT);
    //
    // Mat gray;
    // std::vector<Rect> faces;
    // if(img.channels()>1){
    //     cvtColor(img,gray,COLOR_BGR2GRAY);
    // }
    // else{
    //     gray = img.clone();
    // }
    // equalizeHist( gray, gray );
    //
    // face_cascade.detectMultiScale( gray, faces, 1.1, 3,0, Size(30, 30) );
    //
    // std::vector< std::vector<Point2f> > shapes;
    //
    // if (facemark->fit(img,faces,shapes))
    // {
    //     for ( size_t i = 0; i < faces.size(); i++ )
    //     {
    //         cv::rectangle(img,faces[i],Scalar( 255, 0, 0 ));
    //     }
    //     for (unsigned long i=0;i<faces.size();i++){
    //         for(unsigned long k=0;k<shapes[i].size();k++)
    //             cv::circle(img,shapes[i][k],5,cv::Scalar(0,0,255),FILLED);
    //     }
    //     namedWindow("Detected_shape");
    //     imshow("Detected_shape",img);
    //     waitKey(0);
    // }

    return std::vector<Image*>();
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



