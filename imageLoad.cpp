#include<string>
#include"imageLoad.h"


ImagePPM::ImagePPM(int magicNumber, int length, int width, int maxColorVal,Pixel** imageData) : magicNumber(magicNumber), length(length), width(width), maxColorVal(maxColorVal), imageData(imageData){}

ImagePPM parsePPMFile(std::string filePath){
    
}