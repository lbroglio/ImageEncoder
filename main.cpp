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

    int convertLen =  toConvert.length();

    for(int i = 0; i < convertLen; i++){
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
    //Add a null terminator to the string
    dataToEncode += '\0';

    //Put the string into binary
    std::bitset<8>* binToEncode = stringToBinary(dataToEncode);
    //Counter for what number pixel to edit
    int pixelCounter = 0;
    //Counter for value within pixel (RGB)
    int inPixelCounter = 0;

    int encodeLen = dataToEncode.length();
    //For every character
    for(int i =0; i < encodeLen; i++){
        //For every bit in that characters binary version
       for(int j = 7; j >= 0; j-=1){

        //If the RGB count if 3 go to the next pixel's red value
        if(inPixelCounter == 3){
            pixelCounter++;
            inPixelCounter = 0;
        }

        //Choose to edit the red green or blue value
        switch(inPixelCounter){
            case 0:{
                //If the LSB in the red value is different than the current bit to encode
                if((encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].red & 1) != (binToEncode[i][j])){
                    //Toggle the LSB in the red value
                    encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].red ^= 1UL <<  0;
                }
                break;
            }
            case 1:{
                //If the LSB in the green value is different than the current bit to encode
                if((encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].green & 1) != (binToEncode[i][j])){
                    //Toggle the LSB in the green value
                    encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].green ^= 1UL <<  0;
                }
                break;
            }
            case 2:{
                //If the LSB in the blue value is different than the current bit to encode
                if((encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].blue & 1) != (binToEncode[i][j])){
                    //Toggle the LSB in the blue value
                    encodeIN->imageData[pixelCounter / 512][pixelCounter % 512].blue ^= 1UL <<  0;
                }
                break;
            }
        }

        //Go to the next RGB value
        inPixelCounter++;
       }
    }
}


std::string decode(ImagePPM* decodeFrom){
    std::string decodedData;

    std::bitset<8> currentCharBin;

    int pixelCounter = 0;
    int inPixelCounter = 0;

    int charBitCounter = 7;

    bool foundTerminator = false;

    while(foundTerminator == false && (pixelCounter+1) < (decodeFrom->length * decodeFrom->width)){
        if(inPixelCounter == 3){
            pixelCounter++;
            inPixelCounter = 0;
        }

        if(charBitCounter == -1){
            char toAdd = currentCharBin.to_ulong();

            if(toAdd == '\0'){
                foundTerminator = true;
            }
            else{
                decodedData += toAdd;
                charBitCounter = 7;
            }
        }

        switch (inPixelCounter)
        {
            case 0:
                currentCharBin[charBitCounter] =  decodeFrom->imageData[pixelCounter / 512][pixelCounter % 512].red & 1;
                break;
            case 1:
                currentCharBin[charBitCounter] =  decodeFrom->imageData[pixelCounter / 512][pixelCounter % 512].green & 1;
                break;
            case 2:
                currentCharBin[charBitCounter] =  decodeFrom->imageData[pixelCounter / 512][pixelCounter % 512].blue & 1;
                break;
        }
        charBitCounter -= 1;
        inPixelCounter++;
    }
    return decodedData;
}


int main(int argc, char* argv[]){
    /*
    ImagePPM parsedImg("./TestImages/WhiteSquare.ppm");

    encode(&parsedImg, "Hi, My name is Luke");

    std::ofstream outFile("./TestEncode.ppm");

    outFile << parsedImg;

    outFile.close();
    */
   ImagePPM parsedImg("./TestEncode.ppm");

   std::cout << decode(&parsedImg) << std::endl;
   
    

    return 0;
}