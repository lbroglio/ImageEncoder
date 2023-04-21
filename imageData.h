#ifndef IMGFORMAT_H
#define IMGFORMAT_H

/**
 * @brief Stores the RGB values for a pixel in this image as integers
 * 
 */
struct Pixel{
    int red;
    int blue;
    int green;
    /**
     * @brief Outputs the contents of an Pixel object to a file.
     * 
     * @param file The filestream to output to
     * @param outputFrom The Pixel object to output
     * 
     * @return The file stream with the given Pixel output to it
     */
    friend std::ofstream operator<<(std::ofstream file,Pixel outputFrom);
};


/**
 * @brief Stores a the data of an image in PPM format
 * 
 */
class ImagePPM{
    public:
        /** @brief The magic number of this PPM. 3 if the colors are stored as ASCII numbers. 6 they are stored in binary*/
        int& magicNumber;
        /** @brief The length of this image*/
        int& length;
        /** @brief The width of this image*/
        int& width;
        /** @brief The maximum value any of the colors values in this image can be*/
        int& maxColorVal;
        /** @brief An array of the pixels making up this image*/
        Pixel** imageData;
        /**
         * @brief Construct a new ImagePPM 
         * 
         * @param magicNumber The magic number of the PPM to create
         * @param length The length of the image
         * @param width The width of this image
         * @param maxColorVal Ther max color value for this image
         * @param imageData  Double pointer storing the pixels which make up this image
         */
        ImagePPM(int magicNumber, int length, int width, int maxColorVal,Pixel** imageData);
        /**
         * @brief Destroy the Image PPM object
         * Free the memory of its data array
         */
        ~ImagePPM();
    
    /**
     * @brief Outputs the contents of an ImagePPM object to a file. Creates a valid .PPM image file
     * 
     * @param file The filestream to output to
     * @param outputFrom The ImagePPM object to output
     * 
     * @return The file stream with the given ImagePPM output to it
     */
    friend std::ofstream operator<<(std::ofstream file,ImagePPM outputFrom);
        
};

/**
 * @brief Parses in the data from a PPM image and converts it into a ImagePPM object.
 * 
 * @param filePath The file path to the image file to parse
 * @return An ImagePPM object storing the parsed data
 */
ImagePPM parsePPMFile(std::string filePath);





#endif
