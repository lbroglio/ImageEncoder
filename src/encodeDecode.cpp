#include<iostream>
#include<fstream>
#include<bitset>
#include<string>
#include"imageData.h"

std::bitset<8>* stringToBinary(std::string toConvert){
    std::bitset<8>* asBinary = new std::bitset<8>[toConvert.length()];

    int convertLen =  toConvert.length();

    for(int i = 0; i < convertLen; i++){
        *(asBinary + i) = toConvert[i];
    }

    return asBinary;
}


void encode(ImagePPM* encodeIN, std::string dataToEncode, int startingPoint){
    //Add a null terminator to the string
    dataToEncode += '\0';

    //Put the string into binary
    std::bitset<8>* binToEncode = stringToBinary(dataToEncode);
    //Counter for what number pixel to edit
    int pixelCounter = startingPoint;
    //Counter for value within pixel (RGB)
    int inPixelCounter = 0;

    int encodeLen = dataToEncode.length();

    //Check if the file has space to encode the given data
    if((encodeIN->length * encodeIN->width) * 3 < (encodeLen + 1) * 8){
        //Print error message and exit if there isn't enough space
        std::cout << "Error: The provided data is to large to be stored within the given image." << std::endl;
        exit(1);
    }


    //For every character
    for(int i =0; i < encodeLen; i++){
        //For every bit in that characters binary version
       for(int j = 7; j >= 0; j-=1){

        //If the RGB count if 3 go to the next pixel's red value
        if(inPixelCounter == 3){
            pixelCounter++;
            inPixelCounter = 0;
            // Wrap around the image if needed
            if(pixelCounter >= encodeIN->length){
                pixelCounter = 0;

            }
        }

        //Choose to edit the red green or blue value
        switch(inPixelCounter){
            case 0:{
                //If the LSB in the red value is different than the current bit to encode
                if((encodeIN->imageData[pixelCounter / encodeIN->length][pixelCounter % encodeIN->length].red & 1) != (binToEncode[i][j])){
                    //Toggle the LSB in the red value
                    encodeIN->imageData[pixelCounter / encodeIN->length][pixelCounter % encodeIN->length].red ^= 1UL <<  0;
                }
                break;
            }
            case 1:{
                //If the LSB in the green value is different than the current bit to encode
                if((encodeIN->imageData[pixelCounter / encodeIN->length][pixelCounter % encodeIN->length].green & 1) != (binToEncode[i][j])){
                    //Toggle the LSB in the green value
                    encodeIN->imageData[pixelCounter / encodeIN->length][pixelCounter % encodeIN->length].green ^= 1UL <<  0;
                }
                break;
            }
            case 2:{
                //If the LSB in the blue value is different than the current bit to encode
                if((encodeIN->imageData[pixelCounter / encodeIN->length][pixelCounter % encodeIN->length].blue & 1) != (binToEncode[i][j])){
                    //Toggle the LSB in the blue value
                    encodeIN->imageData[pixelCounter / encodeIN->length][pixelCounter % encodeIN->length].blue ^= 1UL <<  0;
                }
                break;
            }
        }

        //Go to the next RGB value
        inPixelCounter++;

       }
    }
    delete binToEncode;
}


std::string decode(ImagePPM* decodeFrom, int startingPoint){
    //Variable to store the read characters
    std::string decodedData;

    //Hold the read bits to be added once its completed
    std::bitset<8> currentCharBin;

    //Track what pxiel and color value to read
    int pixelCounter = startingPoint;
    int inPixelCounter = 0;
    
    //Track which bit in the character is being read
    int charBitCounter = 7;

    //If a null terminator has been found
    bool foundTerminator = false;

    //Read from the file by taking LSB until a null terminator is found or the end of the file is reached
    while(foundTerminator == false && (pixelCounter+1) < (decodeFrom->length * decodeFrom->width)){
        //If all of the color values from the current pixel have been read
        if(inPixelCounter == 3){
            //Move to the first color value of the next pixel
            pixelCounter++;
            inPixelCounter = 0;
            // Wrap around the image if needed
            if(pixelCounter >= decodeFrom->length){
                pixelCounter = 0;

            }
        }

        //If 8 bits have been read since the last character was added
        if(charBitCounter == -1){
            //Get the character that has been read
            char toAdd = currentCharBin.to_ulong();

            //If the character is a null terminator
            if(toAdd == '\0'){
                //End the loop
                foundTerminator = true;
            }
            //If it isn't
            else{
                //Add the char and reset what bit is being read
                decodedData += toAdd;
                charBitCounter = 7;
            }
        }

        //Decode the bit from the correct RGB value
        switch (inPixelCounter)
        {
            case 0: 
                //Read the LSB from the red value
                currentCharBin[charBitCounter] =  decodeFrom->imageData[pixelCounter / decodeFrom->length][pixelCounter % decodeFrom->length].red & 1;
                break;
            case 1:
                //Read the LSB from the green value
                currentCharBin[charBitCounter] =  decodeFrom->imageData[pixelCounter / decodeFrom->length][pixelCounter % decodeFrom->length].green & 1;
                break;
            case 2:
                //Read the LSB from the blue value
                currentCharBin[charBitCounter] =  decodeFrom->imageData[pixelCounter / decodeFrom->length][pixelCounter % decodeFrom->length].blue & 1;
                break;
        }
        
        charBitCounter -= 1;
        inPixelCounter++;
    }
    return decodedData;
}
