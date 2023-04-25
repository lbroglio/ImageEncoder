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
 */
void encode(ImagePPM* encodeIN, std::string dataToEncode);

/**
 * @brief Takes a pointer to a ImagePPM object and decodes information from it by reading from the LSB until it reads a null byte.
 * 
 * @param decodeFrom Pointer to the ImagePPM to read from
 * @return String containing the decoded data
 */
std::string decode(ImagePPM* decodeFrom);