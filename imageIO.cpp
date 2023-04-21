#include<string>
#include<iostream>
#include<fstream>
#include"imageData.h"

/**
 * @brief Gets the next entry it can find in the given file stream.
 * Moves past white space until it finds the entry
 * 
 * @param imgFile Pointer to the file stream to get an entry from
 * @return The entry as a string
 */
std::string readEntryASCII(std::ifstream* imgFile){
    //Initialize needed varables
    std::string entry = "";
    char curr = 'x';
    
    //While the next character is not whitespace or the entry isn't empty
    while((imgFile->peek() != ' ' && imgFile->peek() != '\n' && imgFile->peek() != EOF) || (entry == ""  && imgFile->peek() != EOF)){
        //Get the next character in the file
        curr = imgFile->get();

        //If a comment is encountered bypass it 
        if(curr == '#'){
            if(entry == ""){
                while(curr != '\n'){
                    curr = imgFile->get();
                }
            }
        }

        //Ad the current character if it isn't white space
        if(curr != ' ' &&  curr != '\n'){
            entry += curr;
        }
        
    }

    return entry;
}

/**
 * @brief Reads the three color values that make up a pixel from the given file. 
 * Returns a pixel object representing the parsed data
 * 
 * @param imgFile Pointer to the file stream to read fro
 * 
 * @return Pixel object created from the parsed data
 */
Pixel readPixelASCII(std::ifstream* imgFile){
    Pixel toReturn;

    toReturn.red = readEntryASCII(imgFile);
    toReturn.blue = readEntryASCII(imgFile);
    toReturn.green = readEntryASCII(imgFile);

    return pixel;
}


ImagePPM::ImagePPM(int magicNumber, int length, int width, int maxColorVal,Pixel** imageData) : magicNumber(magicNumber), length(length), width(width), maxColorVal(maxColorVal), imageData(imageData){}

ImagePPM::~ImagePPM(){
    for(int i = 0; i<length; i++){
        delete[] imageData[i];
    }
    delete[] imageData;
}

ImagePPM parsePPMFile(std::string filePath){
    //Load the file
    std::ifstream imgFile(filePath);
    
    //Get the entry containting the magic number (Will be in P# format)
    std::string magicNumberStr = readEntryASCII(&imgFile);
    
    //Get the dimesions and color depth
    int length = atoi(readEntryASCII(&imgFile).c_str());
    int width = atoi(readEntryASCII(&imgFile).c_str());
    int colorMax = atoi(readEntryASCII(&imgFile).c_str());

    //Initialized the 2D array to store the pixels
    Pixel** imageData = new Pixel*[length];
    for(int i =0; i < length; i++){
        imageData[i] = new Pixel[width];
    }

    for(int i =0; i < length; i++){
        for(int j =0; j < width; j++){
            imageData[i][j] =  
        }
    }
    
}