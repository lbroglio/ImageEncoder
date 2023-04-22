#include<iostream>
#include<fstream>
#include"imageData.h"

int main(int argc, char* argv[]){
    ImagePPM parsedImg("./TestImages/WhiteSquare.ppm");

    for(int i = 370; i < 512; i++){
        for(int j =0; j < 512; j++){
            Pixel tmp;
            tmp.red = 255;
            tmp.blue = 0;
            tmp.green = 0;
            parsedImg.imageData[i][j] = tmp;
        }
    }

    std::ofstream outFile("./TestOutput.ppm");

    outFile << parsedImg;

    outFile.close();



    return 0;
}