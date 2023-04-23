#include<iostream>
#include<fstream>
#include<bitset>
#include<string>
#include<cmath>
#include"imageData.h"

/**
 * @brief Converts the contents of a string to an array of Bitsets. Each bitset represents the binary value of the chars ASCII code.
 * 
 * @param toConvert The string to convert
 * @return Pointer to the array of bitsets storing the characters in binary 
 */
std::bitset<8>* stringToBinary(std::string toConvert){
    std::bitset<8>* asBinary = new std::bitset<8>[toConvert.length()];

    for(int i = 0; i < toConvert.length(); i++){
        *(asBinary + i) = toConvert[i];
    }

    return asBinary;
}

/**
 * @brief Encodes a given string into the given PPM image
 * 
 * @param encodeIN Pointer to the PPM Image to encode the data in
 * @param dataToEncode String to encode in the image
 */
void encode(ImagePPM* encodeIN, std::string dataToEncode){
    double bitNumF = log2(encodeIN->maxColorVal);
    const size_t bitNum = (size_t)(ceil(bitNumF));

    std::bitset<8>* binToEncode = stringToBinary(dataToEncode);

    int pixelCounter = 0;
    int inPixelCounter = 0;
    for(int i =0; i < dataToEncode.length(); i++){
       for(int j = 7; j >= -1; j--){
        if(inPixelCounter == 3){
            pixelCounter++;
            inPixelCounter = 0;
        }

        switch(inPixelCounter){
            case 0:
                encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].red |= binToEncode[i][j];
                break;
            case 1:
                encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].green |= binToEncode[i][j];
                break;
            case 2:
                encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].blue |= binToEncode[i][j];
                break;
        }
        
       }
    }
}

std::string decode(ImagePPM decodeFrom){

}



int main(int argc, char* argv[]){
    ImagePPM parsedImg("./TestImages/WhiteSquare.ppm");

    encode(&parsedImg, "Hi, My name is Luke");

    std::ofstream outFile("./TestEncode.ppm");

    outFile << parsedImg;

    outFile.close();
    

    return 0;
}