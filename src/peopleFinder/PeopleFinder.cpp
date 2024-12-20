//
// Created by jérémie on 11/12/2024.
//

#include "PeopleFinder.h"

int NB_ARG = 3;

PeopleFinder::PeopleFinder() {
    this->arg = new std::string[NB_ARG]{
        "-h",
        "-c",
        "-o"
    };
    this->description = new std::string[NB_ARG]{
        "Display help",
        "This argument uses the camera",
        "The directory destination "
    };
    this->argvalues = new std::string[NB_ARG] {
        "",
        "",
        "./"
    };
    this->imageAnalyser = ImageAnalyser();
}

void PeopleFinder::printArgs() {
    bool nextIsData = false;
    int maxLen = 1;
    for (int i = 0; i < NB_ARG; ++i) {
        if (this->arg[i].length() > maxLen) {
            maxLen = this->arg[i].length();
        }
    }
    for (int i = 0; i < NB_ARG; ++i) {
        for (int charIndex = 0; charIndex < maxLen + 1; ++charIndex) {
            if (this->arg[i].length() <= charIndex) {
                std::cout << " ";
            } else {
                std::cout << this->arg[i].c_str()[charIndex];
            }
        }
        std::cout << ": ";
        std::cout << this->description[i] << std::endl;
    }
    std::cout << std::endl;
}

int PeopleFinder::findArg(char *arg) {
    int nbValides = NB_ARG;
    int* valides = new int[nbValides];
    for (int i = 0; i < nbValides; ++i) {
        valides[i] = i;
    }
    int argn = 0;
    char actual = arg[argn];
    while (actual != '\0') {
        for (int argnum = 0; argnum < nbValides; ++argnum) {
            //TODO: mettre en place la recherche de l'argument en comparant les caracteres
        }
        actual = arg[++argn];
    }
}


int PeopleFinder::runArg(int argn) {
    switch (argn) {
        case 0: {printArgs();return 0}
        case 1:
        default: return 0;
    }
}


int PeopleFinder::runArgs(int argc, char **argv) {
    for (int argn = 0; argn < argc; ++argn) {

    }
}


