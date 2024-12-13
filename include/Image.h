//
// Created by jérémie on 11/12/2024.
//

#ifndef IMAGE_H
#define IMAGE_H

enum channel {
  red = 0,
  green = 1,
  blue = 2,
  alpha = 3
};

class Image {
    int width;
    int height;
    int channels;
    unsigned char* data;

public:
    Image(int, int, int, unsigned char*);
    Image* edgeDetection();
    Image* getChannel(channel);
    Image* crop(int x, int y, int width, int height);
    void save(const char*);
};

#endif //IMAGE_H
