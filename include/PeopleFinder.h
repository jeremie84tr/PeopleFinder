//
// Created by jérémie on 11/12/2024.
// This class is intended to find someone given an image, comparing this individual with a dictionnary.
//

#ifndef PEOPLEFINDER_H
#define PEOPLEFINDER_H
#include <string>
#include "ImageAnalyser.h"


class PeopleFinder {
    std::string* arg;
    std::string* description;
    std::string* argvalues;
    ImageAnalyser imageAnalyser;

    bool useCamera;
    char* outputDirectory;

    void printArgs();
    int findArg(char* arg);
    int runArg(int argn);
public:
    PeopleFinder();
    int runArgs(int argc, char** argv);
};



#endif //PEOPLEFINDER_H
