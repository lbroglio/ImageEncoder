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
}


int main(int argc, char* argv[]){

    //Location of the first argument. Will be moved if options flags are given
    int firstArgLoc = 1;
    //Flag for if the user want to encode or decode information. 0 is encode, 1 is decode
    int encodeDecodeFlag = 0;
    //String to hold the user given file path is a file is provided for data
    std::string dataFilePath = "";

    //If options are given on the command line
    if(argv[1][0] == '-'){
        //Move location of first argument forward
        firstArgLoc += 1;

        //Print error message and exit if there are two few arguments
        if(argc < 3){
            std::cout << "Error: Insuficient number of command line arguments" << std::endl;
            exit(1);
        }

        //Get options
        std::string options = argv[1];

        //If the decode option is set switch the decode flag to one
        if(options.find('d') != std::string::npos){
            encodeDecodeFlag = 1;
        }

        //If the file option is set
        if(options.find('f') != std::string::npos){
            //If a file name is provided read it in
            if(argc > 4){
                //Set data file to the read file
                dataFilePath = argv[4];
            }
            //Else give it generic name
            else{
                dataFilePath = "./decoded_text.txt";
            }


        }

    }

    //Get location of the image file
    std::string imgFilePath = argv[firstArgLoc];

    //Encode data
    if(encodeDecodeFlag == 0){ 
      //Print error message and exit if there are two few arguments
        if(firstArgLoc != 1 && argc < 4){
            std::cout << "Error: Insuficient number of command line arguments" << std::endl;
            exit(1);         
        }

        ImagePPM* encodeIn;
        //Read in provided file as a ImagePPM object
        try{
             encodeIn = new ImagePPM(imgFilePath);
        }
        //If the file isn't found print error message and exit
        catch(std::invalid_argument){
            std::cout << "Error: The provided image file could not be opened." << std::endl;
            exit(1);
        }

        //String containing data to encode into the image
        std::string textToEncode;

        //If a data file has been set
        if(dataFilePath != ""){
            //Open the file
            std::ifstream dataToEncodeFile(dataFilePath);

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
            //Set text to encode to the first word ignoring the first character since it should be quotes
            std::string firstWord = argv[firstArgLoc + 1];
            textToEncode = firstWord.substr(1);

            //Read in the data to encode from the command line
            for(int i = firstArgLoc + 2; i < argc; i++){
                std::string currWord = argv[i];
                textToEncode += " " + currWord;


                //Stop when a closing quote is found and theres no slash with it
                if((textToEncode[textToEncode.length() - 1] == '\"' || textToEncode[textToEncode.length() - 1] == '\'') && textToEncode[textToEncode.length() - 2] != '\\'){
                    textToEncode.pop_back();
                    break;
                }
            }

        }

        //Encode text
        encode(encodeIn,textToEncode);

        //Get name of the encoded file without .ppm
        std::string inputFileName = imgFilePath.substr(0,imgFilePath.length() - 4);

        //Create file path to output file to 
        std::string outputFilePath = inputFileName += "_ENCODED.ppm";

        //Open output file 
        std::ofstream outFile(outputFilePath);

        //Output the encoded image
        outFile << encodeIn;

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
        catch(std::invalid_argument){
            std::cout << "Error: The provided image file could not be opened." << std::endl;
            exit(1);
        }

        //Decode the text from the image
        std::string decodedText = decode(decodeFrom);

        delete decodeFrom;

        //If the file option was set output the decoced text to a file
        if(dataFilePath != ""){
            std::ofstream outFile(dataFilePath);

            outFile << decodedText;

            outFile.close();
        }

        //Output the decoded text to the console.
        std::cout << decodedText << std::endl;


    }

    return 0;
}