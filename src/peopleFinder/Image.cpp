//
// Created by jérémie on 11/12/2024.
//
#include "Image.h"

Image::Image(int width, int height, int channels, unsigned char* data) {
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->data = data;
}

Image* Image::getChannel(channel channel) {
    if (this->channels == 1) { //Image en noir et blanc
        return this;
    }
    unsigned char data[this->width * this->height];
    enum channel defChannel;
    if (this->channels == 2) { //Image en noir et blanc avec alpha
        if (channel == alpha) {
            defChannel = red;
        } else {
            defChannel = green;
        }
    } else { //Image standard
        defChannel = channel;
    }
    int iChannel;
    for (int i = 0; i < width * height; i++) {
        iChannel = i * this->channels;
        data[i] = this->data[iChannel + defChannel];
    }
    return new Image(this->width,this->height,1,data);
}