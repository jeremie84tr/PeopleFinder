//
// Created by jérémie on 11/12/2024.
//
#include "Image.h"

#include <iostream>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#endif //STB_IMAGE_WRITE_IMPLEMENTATION

Image::Image(int width, int height, int channels, unsigned char* data) {
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->data = new unsigned char[width * height * channels];
    for (int i=0; i<width*height*channels; i++) {
        this->data[i] = data[i];
    }
}

Image::~Image() {
    std::cout << "suppression image" << std::endl;
    delete[] this->data;
    this->data = nullptr;
}

cv::Mat* Image::getMat() {
    // Vérifie si les données existent
    if (data == nullptr) {
        return nullptr; // Retourne un pointeur nul si aucune donnée n'est disponible
    }

    // Détermine le type de Mat en fonction du nombre de canaux
    int type;
    if (channels == 1) {
        type = CV_8UC1; // Image en niveaux de gris
    } else if (channels == 3) {
        type = CV_8UC3; // Image couleur RGB
    } else if (channels == 4) {
        type = CV_8UC4; // Image couleur avec transparence (RGBA)
    } else {
        throw std::invalid_argument("Unsupported number of channels");
    }

    // Crée une nouvelle instance de cv::Mat
    return new cv::Mat(height, width, type, data);
}


void remplirVecteur(int vecteurId, int comparaisonI, int comparaisonJ, int i, int j, long* vecteur, unsigned char* data, int channels, int width, int height) {
    if (i > comparaisonI && i < height + comparaisonI && j > comparaisonJ && j < width + comparaisonJ) {
        int iDataChanneled = ((i - comparaisonI) * width + (j - comparaisonJ)) * channels;
        vecteur[vecteurId] = 0;
        if (channels >= 1) {//monochrome
            vecteur[vecteurId] += data[iDataChanneled] * data[iDataChanneled];
        }
        if (channels > 2) {//pas monochrome pas alpha
            vecteur[vecteurId] += data[iDataChanneled + 1] * data[iDataChanneled + 1];
        }
        if (channels >= 3) {
            vecteur[vecteurId] += data[iDataChanneled + 2] * data[iDataChanneled + 2];
        }
    } else {
        vecteur[vecteurId] = -1;
    }
}

Image* Image::edgeDetection() {
    long size = this->width * this->height;
    unsigned char data[size];
    int nbVecteurs;
    int totVecteurs;
    long vecteurCouleur[9];
    for (int i=0; i<this->height; i++) {
        for (int j=0; j<this->width; j++) {
            remplirVecteur(0,-1,0, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(1,-1,-1, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(2,-1,1, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(3,0,-1, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(4,0,0, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(5,0,1, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(6,1,0, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(7,1,-1, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);
            remplirVecteur(8,1,1, i, j, vecteurCouleur, this->data, this->channels, this->width, this->height);

            nbVecteurs = 0;
            totVecteurs = 0;
            for (int vecteurId=0; vecteurId<9; vecteurId++) {
                if (vecteurCouleur[vecteurId] != -1) {
                    totVecteurs += vecteurCouleur[vecteurId];
                    nbVecteurs++;
                }
            }
            if (nbVecteurs != 0) {
                int result = totVecteurs / nbVecteurs;
                if (vecteurCouleur[4] == result) {
                    data[i * this->width + j] = 0;
                } else {
                    int val = (255 - vecteurCouleur[4] / abs(result - vecteurCouleur[4]) * nbVecteurs * 5);
                    if (val < 0) {
                        data[i * this->width + j] = 0 ;
                    } else {
                        data[i * this->width + j] = val ;
                    }
                }
            } else {
                data[i * this->width + j] = 128;
            }
        }
    }
    return new Image(this->width,this->height,1,data);
}


/**
 *
 * @param channel the channel you want to get from the image
 * @return the image grayscaled to the channel wanted
 */
Image* Image::getChannel(channel channel) {
    if (this->channels == 1) { //Image en noir et blanc
        return this;
    }
    unsigned char* data = new unsigned char[this->width * this->height];
    enum channel defChannel;
    if (this->channels == 2) {
        //Image en noir et blanc avec alpha
        if (channel == alpha) {
            defChannel = green;
        } else {
            defChannel = red;
        }
    } else { //Image standard
        defChannel = channel;
    }
    int iChannel;
    for (int i = 0; i < width * height; i++) {
        iChannel = i * this->channels;
        if (this->channels == 3 && channel == alpha) {
            data[i] = 255;
        } else {
            data[i] = this->data[iChannel + defChannel];
        }
    }
    return new Image(this->width,this->height,1,data);
}

int Image::getWidth() {
    return this->width;
}

int Image::getHeight() {
    return this->height;
}



/**
 *
 * @param x the starting x point of your crop (can be negative)
 * @param y the starting y point of your crop (can be negative)
 * @param width the width of your crop
 * @param height the height of your crop
 * @return the image cropped or enlarged
 */
Image* Image::crop(int x, int y, int width, int height) {
    if (width <= 0 or height <= 0) {
        return new Image(0,0,0,nullptr);
    }
    long dimensions = width * height * this->channels;
    unsigned char* data = new unsigned char[dimensions];

    /* setting up out of bounds */
    int oobx = 0; //Out Of Bounds X -> before picture width
    if (x < 0) {
        oobx = -x;
    }
    int oobw = 0; //Out Of Bounds W -> after picture width
    if (x + width > this->width) {
        oobw = x + width - this->width;
    }
    int ooby = 0; //Out Of Bounds Y -> before picture height
    if (y < 0) {
        ooby = -y;
    }
    int oobh = 0; //Out Of Bounds H -> after picture height
    if (y + height > this->height) {
        oobh = y + height - this->height;
    }

    int iChannel;
    long iData = 0;
    for (int oob = 0; oob < ooby; oob++) {//Black generated by default for Out Of Bounds Y
        for (int j = 0; j < width; j++) {
            for (int channel = 0; channel < this->channels; channel++) {
                data[iData++] = 0;
            }
        }
    }
    for (int i = y; i < y + height; i++) {
        if (iData == dimensions or i >= this->height) {//The crop is full or the image is out of bounds
            break;
        }
        if (i >= 0) {
            for (int oob = 0; oob < oobx; oob++) {//Black generated by default for Out Of Bounds X for each line
                for (int channel = 0; channel < this->channels; channel++) {
                    data[iData++] = 0;
                }
            }
            for (int j = x; j < x + width; j++) {//the line iteration
                if (j >= this->width) {//the image line is full
                    break;
                }
                if (j >= 0) {
                    iChannel = (i * this->width + j) * this->channels;
                    for (int channel = 0; channel < this->channels; channel++) {
                        data[iData++] = this->data[iChannel + channel];
                    }
                }
            }
            for (int oob = 0; oob < oobw; oob++) {//Black generated by default for Out Of Bounds W for each line
                for (int channel = 0; channel < this->channels; channel++) {
                    data[iData++] = 0;
                }
            }
        }
    }
    for (int oob = 0; oob < oobh; oob++) {//Black generated by default for Out Of Bounds H
        for (int j = 0; j < width; j++) {
            for (int channel = 0; channel < this->channels; channel++) {
                data[iData++] = 0;
            }
        }
    }

    Image* ret = new Image(width, height, this->channels, data);
    delete[] data;
    return ret;
}

/**
 *
 * @param filename the filename/filepath where you want to save the image
 */
void Image::save(const char* filename) {
    if (!stbi_write_png(filename, width, height, channels, data, width * channels)) {

    }
}
