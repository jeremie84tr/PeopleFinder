#include <iostream>
#include "ImageAnalyser.h"

int main() {
    ImageAnalyser image_analyser = ImageAnalyser();
    image_analyser.LoadImage("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/dictionnary/jeremie/img_1.png");
    image_analyser.getImage()->getChannel(red)->save("rouge.png");
    image_analyser.getImage()->getChannel(green)->save("vert.png");
    image_analyser.getImage()->getChannel(blue)->save("bleu.png");
    return 0;
}
