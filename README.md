# Description
This program performs image stenography, the process of hiding information or data within an image, with user provided data and images stored in the PPM format.

The program works by replacing the least significant bit in the color values which make up the pixels in the provided image with the bits the provided data. 

The program encodes an 8 bit (1 byte) number into the program for every character(the number is the characters ASCII coce) in the data the user provided to encode. 

The program will take in a given PPM image and output a new PPM with encoded data if in encode mode or the decoded data if in decode mode.

# Usage
The program should be compiled with Make by running `make`

The program can be run with the following format:
`./ImageSten -[flags] [--option..] <Filepath to Image file> {Data to encode | file to get data from}`

## Flags
- -h: Print the help information (This output) 
- -3: Override the output .ppm image to be in p3 (ASCII) format.
- -6: Override the output .ppm image to be in p6 (binary) format.
- -d: Decode data from an image (instead of encoding like in default)
- -f: Puts the program into file mode. 
    - If encoding the program will then read data to encode from a file specified in the second argument.
    - If decoding the program will ouput the decoded data to a file. Name of the file must be set with the output option. 

## Options: 
- --output/--o: Set the name of the any output file. 
    - If in encode mode this will set the name of the output .ppm file
    - If in decode mode this will set the name of the file the data is output to if the program is in file mode (-f flag).
- --start-point/--s: Set the location within the file to start reading from/ writing to
## Examples: 
- Encode "Hello, World." into the image TestFiles/RedSquare.ppm:
    - `ImageSten TestFiles/RedSquare.ppm  "Hello, World."`
- Encode the text in the file TestFiles/TheTimeMachine.txt into the image TestFiles/Galaxy.ppm and output it as encoded_image.ppm:
    - `ImageSten -f --output encoded_image.ppm TestFiles Galaxy.ppm TestFiles/TheTimeMachine.txt`
- Decode the data from the image RedSquare_ENCODED.ppm:
    - `ImageSten -d RedSquare_ENCODED.ppm`
- Decode the data from the image encoded_image.ppm and write it to the file data.txt:
    - `ImageSten -df --output data.txt encoded_image.ppm`
    
*Example images and data are included in the TestFiles folder*

