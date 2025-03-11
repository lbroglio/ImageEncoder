#include<iostream>
#include<fstream>
#include<bitset>
#include<string>
#include"imageData.h"


/**
 * @brief Converts the contents of a string to an array of Bitsets. Each bitset represents the binary value of the chars ASCII code.
 * 
 * @param toConvert The string to convert
 * @return Pointer to the array of bitsets storing the characters in binary 
 */
std::bitset<8>* stringToBinary(std::string toConvert);

/**
 * @brief Encodes a given string into the given PPM image
 * 
 * @param encodeIN Pointer to the PPM Image to encode the data in
 * @param dataToEncode String to encode in the image
 * @param startingPoint The pixel value (with the first pixel indexed by 0)
 * to start writing the data at.
 */
void encode(ImagePPM* encodeIN, std::string dataToEncode, int startingPoint);

/**
 * @brief Takes a pointer to a ImagePPM object and decodes information from it by reading from the LSB until it reads a null byte.
 * 
 * @param decodeFrom Pointer to the ImagePPM to read from
 *  * @param startingPoint The pixel value (with the first pixel indexed by 0)
 * to start reading the data at.
 * @return String containing the decoded data
 */
std::string decode(ImagePPM* decodeFrom, int startingPoint);