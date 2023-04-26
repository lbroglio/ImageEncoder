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
 * Reads in ASCII color values
 * 
 * @param imgFile Pointer to the file stream to read fro
 * 
 * @return Pixel object created from the parsed data
 */
Pixel readPixelASCII(std::ifstream* imgFile){
    Pixel toReturn;

    toReturn.red = atoi(readEntryASCII(imgFile).c_str());
    toReturn.green = atoi(readEntryASCII(imgFile).c_str());
    toReturn.blue = atoi(readEntryASCII(imgFile).c_str());

    return toReturn;
}

/**
 * @brief Reads the three color values that make up a pixel from the given file. 
 * Returns a pixel object representing the parsed data
 * Reads in Binary color values
 * 
 * @param imgFile Pointer to the file stream to read from
 * 
 * @return Pixel object created from the parsed data
 */
Pixel readPixelBinary(std::ifstream* imgFile){
    Pixel toReturn;

    toReturn.red = imgFile->get();
    toReturn.green = imgFile->get();
    toReturn.blue = imgFile->get();;

    return toReturn;
}


ImagePPM::ImagePPM(int magicNumber, int length, int width, int maxColorVal,Pixel** imageData) : magicNumber(magicNumber), length(length), width(width), maxColorVal(maxColorVal), imageData(imageData){}

ImagePPM::~ImagePPM(){
    for(int i = 0; i<length; i++){
        delete[] imageData[i];
    }
    delete[] imageData;
}

ImagePPM::ImagePPM(std::string filePath){
    //Load the file
    std::ifstream imgFile(filePath);

    //Check if the provided file exists throw exception if it doesn't
    if(!imgFile){
        throw std::invalid_argument("Provided file does not exist");
    }
    
    //Get the entry containting the magic number (Will be in P# format)
    std::string magicNumberStr = readEntryASCII(&imgFile);
    
    //Get magic number from its string
    magicNumber = magicNumberStr[1] - '0';

    //Get the dimesions and color depth
    length = atoi(readEntryASCII(&imgFile).c_str());
    width = atoi(readEntryASCII(&imgFile).c_str());
    maxColorVal = atoi(readEntryASCII(&imgFile).c_str());

    //Initialized the 2D array to store the pixels
    imageData = new Pixel*[length];
    for(int i =0; i < length; i++){
        imageData[i] = new Pixel[width];
    }

    //If a P3 PPM image is provided
    if(magicNumber == 3){
        //Read in all of the pixels in the ASCII format
        for(int i =0; i < length; i++){
            for(int j =0; j < width; j++){
                imageData[i][j] = readPixelASCII(&imgFile);
            }
        }
    }
    //If a P6 PPM image is provided
    else{
        //Save the current postion in the file
        std::streampos filePos = imgFile.tellg();

        //Close the file
        imgFile.close();

        //Reopen to read binary
        imgFile.open(filePath, std::ios::binary);

        //Return to saved position
        imgFile.seekg(filePos);

        //Move past the seperator between the header and body
        imgFile.get();

        //Read in all of the pixels in the binary format
        for(int i =0; i < length; i++){
            for(int j =0; j < width; j++){
                imageData[i][j] = readPixelBinary(&imgFile);
            }
        }


    }
    //Close the file
    imgFile.close();
}

std::ofstream& operator<<(std::ofstream& file,const Pixel& outputFrom){
    file << outputFrom.red << ' ' << outputFrom.green << ' ' << outputFrom.blue;

    return file;
}

std::ofstream& operator<<(std::ofstream& file,const ImagePPM& outputFrom){
    if(outputFrom.magicNumber == 3){
        return printP3(file,outputFrom);
    }
    else{
        return printP6(file,outputFrom);
    }
}

std::ofstream& printP3(std::ofstream& file,const ImagePPM& outputFrom){
    //Output the header
    file << 'P' << outputFrom.magicNumber << '\n';
    file << outputFrom.length << ' ' << outputFrom.width << '\n';
    file << outputFrom.maxColorVal << '\n';

    //Output the data
    for(int i = 0; i < outputFrom.length; i++){
        for(int j = 0; j < outputFrom.width; j++){
            file << (outputFrom.imageData[i][j]) << '\n';
        }
    }

    return file;
}


std::ofstream& printP6(std::ofstream& file,const ImagePPM& outputFrom){
    //Output the header
    file << 'P' << outputFrom.magicNumber<< '\n';
    file << outputFrom.length  << ' ' << outputFrom.width << '\n';
    file << outputFrom.maxColorVal  << '\n';

    //Output the data
    for(int i = 0; i < outputFrom.length; i++){
        for(int j = 0; j < outputFrom.width; j++){
            file.put(outputFrom.imageData[i][j].red);
            file.put(outputFrom.imageData[i][j].green);
            file.put(outputFrom.imageData[i][j].blue);
        }
    }

    return file;
}