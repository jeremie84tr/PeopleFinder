#include <charconv>
#include <iostream>
#include "ImageAnalyser.h"

int main() {
    ImageAnalyser image_analyser = ImageAnalyser();

    image_analyser.LoadImage("dictionnary/jeremie/jeremie_1.png");
    image_analyser.getImage()->edgeDetection()->save("jeremie1_edged.png");


    std::vector<Image*> faces = image_analyser.findHead();
    std::string filename;
    Image* image;
    std::cout << faces.size() << " faces" << std::endl;
    for (int i=0; i<faces.size(); i++) {
        std::cout << "face found" << std::endl;
        image = faces.data()[i];
        filename = "aaa_face";
        filename += std::to_string(i);
        filename += ".png";
        image->save(filename.c_str());
    }
    return 0;
}
