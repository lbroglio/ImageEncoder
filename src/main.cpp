#include<iostream>
#include<fstream>
#include<string>
#include"imageData.h"
#include"encodeDecode.h"



/**
 * @brief Read in the data from a provided file into a string so it can be encoded
 * 
 * @param readFrom Poitner to the file stream to read from.
 * @return String containing the entire contents of the file
 */
std::string readDataFile(std::ifstream* readFrom){
    std::string readData = "";
    char readChar = readFrom->get();
    while(readFrom->peek() != EOF){
        readData += readChar;
        readChar = readFrom->get();
    }

    return readData;
}

/**
 * @brief Interpret the flags set by the user 
 * 
 * @param flags The string containing the flags
 * @param encodeDecodeFlag Memory location to set the flag for whether the program should encode or decode from a file
 * @param typeOverride Memory location to set the override for the type of PPM to output.
 * @param fileModeFlag Memory location to set the flag for whether the program is in file mode
 *  (In file mode data to encode is read from a file and in decode mode it is output to a file)
 *  1 means the program is in file mode 0 means it is not
 */
void readFlags(std::string flags, int* encodeDecodeFlag, int* typeOverride, int* fileModeFlag){
    //If the decode option is set switch the decode flag to one
    if(flags.find('d') != std::string::npos){
        *encodeDecodeFlag = 1;
    }

    //If the user puts the flag 3 overide output type to a P3 PPM
    if(flags.find('3') != std::string::npos){
        *typeOverride = 3;
    }
    //If the user puts the flag 6 overide output type to a P6 PPM
    else if(flags.find('6') != std::string::npos){
        *typeOverride = 6;
    }

    //If the file option is set
    if(flags.find('f') != std::string::npos){
        *fileModeFlag = 1;
    }

}


int main(int argc, char* argv[]){

    // Current location of the argument being interpreted
    int argLoc = 1;
    // Flag for if the user want to encode or decode information. 0 is encode, 1 is decode
    int encodeDecodeFlag = 0;
    /*  Flag for whether the program is in file mode
        (In file mode data to encode is read from a file and in decode mode it is output to a file)
        1 means the program is in file mode 0 means it is not
    */
    int fileModeFlag = 0;
    // String to hold the user given file path if a file is provided for data
    std::string dataFilePath = "";
    // The path to the file to output the result of the operation to (Depending on the settings files may not be output to)
    std::string outputFilePath = "";
    // Used to set the type of PPM (P3 or P6) depending on command line flags
    int typeOverride = -1;
    // The position to start reading or writing data from as a pixel index
    int startPos = 0;


    //Print error message and exit if there are two few arguments
    if(argc < 3){
        std::cout << "Error: Insuficient number of command line arguments" << std::endl;
        exit(1);
    }

    //If flags are set on the command line
    if(argv[1][0] == '-' && argv[1][1] != '-'){
        //Move location of first argument forward
        argLoc += 1;

        // Read the flags
        readFlags(argv[1], &encodeDecodeFlag, &typeOverride, &fileModeFlag);
    }

    // Move through the options set by the user
    std::string currentArgStr = argv[argLoc];
    // While an option is being read
    while(currentArgStr.substr(0, 2) == "--"){
        if(currentArgStr == "--output" || currentArgStr == "--o"){
            outputFilePath = argv[++argLoc];
        }
        else if(currentArgStr == "--starting-point" || currentArgStr == "--s"){
            startPos = std::atoi(argv[++argLoc]);
        }

        currentArgStr = argv[++argLoc];
    }

    //Get location of the image file
    std::string imgFilePath = currentArgStr;

    //Encode data
    if(encodeDecodeFlag == 0){ 
        // Print error message and exit if there are two few arguments
        if(argc - argLoc < 2){
            std::cout << "Error: Insuficient number of command line arguments" << std::endl;
            exit(1);         
        }

        ImagePPM* encodeIn;
        //Read in provided file as a ImagePPM object
        try{
             encodeIn = new ImagePPM(imgFilePath);
        }
        //If the file isn't found print error message and exit
        catch(std::invalid_argument const&){
            std::cout << "Error: The provided image file could not be opened." << std::endl;
            exit(1);
        }

        //String containing data to encode into the image
        std::string textToEncode;

        // If the program is in file mode
        if(fileModeFlag == 1){
            //Open the file
            std::ifstream dataToEncodeFile(argv[++argLoc]);

            //If the file is invalid print and error message and exit
            if(!dataToEncodeFile){
                std::cout << "Error: The provided data file could not be opened." << std::endl;
                exit(1);
            }

            //Save the contents of the file to textToEncode 
            textToEncode = readDataFile(&dataToEncodeFile);

            //Close the file
            dataToEncodeFile.close();
        }
        else{
            //Set textToEncode to the text provided by the command line 
            textToEncode = argv[++argLoc];
        }

        //Encode text
        encode(encodeIn, textToEncode, startPos);

        //Get name of the encoded file without .ppm
        std::string inputFileName = imgFilePath.substr(0,imgFilePath.length() - 4);

        // If an output file has not been set; create file path to output file to 
        if(outputFilePath == ""){
            outputFilePath = inputFileName += "_ENCODED.ppm";
        }

        //Change the type if the user put an overide flag
        if(typeOverride != -1){
            encodeIn->magicNumber = typeOverride;       
        }

        //Open output file 
        std::ofstream outFile;

        //Open in correct mode normal for P3 binary for P6
        if(encodeIn->magicNumber == 3){
            outFile.open(outputFilePath);
        }
        else{
            outFile.open(outputFilePath, std::ios::binary);
        }

        //Output the encoded image
        outFile << *encodeIn;

        //Close the file
        outFile.close();

        delete encodeIn;
    }
    else{
        ImagePPM* decodeFrom;
        //Read in provided file as a ImagePPM object
        try{
            decodeFrom = new ImagePPM(imgFilePath);
        }
        //If the file isn't found print error message and exit
        catch(std::invalid_argument const&){
            std::cout << "Error: The provided image file could not be opened." << std::endl;
            exit(1);
        }

        //Decode the text from the image
        std::string decodedText = decode(decodeFrom, startPos);

        delete decodeFrom;

        //If the file option was set output the decoced text to a file
        if(fileModeFlag == 1){
            if(outputFilePath == ""){
                std::cout << "Error: The required option --output has not been set." << std::endl;
                exit(1);
            }


            std::ofstream outFile(outputFilePath);

            outFile << decodedText;

            outFile.close();
        }
        else{
            //Output the decoded text to the console.
            std::cout << decodedText << std::endl;
        }




    }

    return 0;
}