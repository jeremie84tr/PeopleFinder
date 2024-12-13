#include <iostream>
#include "ImageAnalyser.h"

int main() {
    ImageAnalyser image_analyser = ImageAnalyser();
    image_analyser.LoadImage("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/dictionnary/jeremie/entree.png");
    image_analyser.getImage()->edgeDetection()->save("shrek_edged.png");
    image_analyser.LoadImage("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/dictionnary/jeremie/img.png");
    image_analyser.getImage()->edgeDetection()->save("img_edged.png");
    image_analyser.LoadImage("C:/Users/jeremie/Documents/cours/M2-S1/traitement du document nu/tp2/dictionnary/jeremie/jeremie_1.png");
    image_analyser.getImage()->edgeDetection()->save("jeremie1_edged.png");
    return 0;
}
