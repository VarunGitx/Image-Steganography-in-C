# Who I am
Varun Senthilkumar
- Student ID: H00384753

# Program design

In this coursework i have shown i can create a steganography program that encrypts and decrypts hidden messages in bitmap images using the 
C programing language.By using steganography,it involves concealing information in an image file without altering the original file in any
way.It is employed to safeguard confidential information ,carry out hidden communications and keep the data hidden from intruders.

The program where PPM(PORTABLE PIXMAP)Picture format is used by the software to store the image data.Set of RGB values are used to represent image
in PPM format.Three integers are used to represent each pixel and one for each colour red green and blue.The software decodes hidden messages 
into the image from PPM file.

The program's main function encrypts a secret message into an image by reading it from a PPM file. The message is supplied to the application as a 
string argument and a random index is first created by the program within the pixel data range. To determine the index range i have divided the number
of pixels by the message's length, plus one. The ASCII values of each character are then iteratively recorded in the red channel of the image at the designated
index and then application outputs the encoded image in PPM format to a standard output.

The program uses structure to store the data ,PPM structure stores the image data loaded from the PPM file, and pixel structure stores the RGB values
 of a single pixel. Number, height ,width Maximum value of colour , and  pointer to an array of data which has pixel are included in the PPM structure.
The READ PPM file is read by the getPPM function, which then returns a new PPM structure with the picture data within and then gets the values of the PPM 
image suich as height ,width and max .The function then gets the pixel values from the file and then allots memory for the pixel data.
it then returns the newly created PPM structure.

The specified text is encoded into the image's red pixel through the encode function. A random index is created within the pixel data 
.The new PPM structure with the decoded picture data is then returned by the function and the pixel of data from the old image is then
copied to the new image and then returned through the decode function .

In conclusion, I use C programming language to implement image steganography. A secret message is encoded into the red pixel of an image that is 
read from a PPM file, and then the encoded image is then written to the standard output. The program reads,loads and encodes the image data using the 
structures and operations. This program can be useful for protecting sensitive information or for hiding communications.

# Choice of data structures and algorithms

In get PPM the data structures used in this function are suitable for reading and saving PPM formatted image and structs and dynamic memory 
allocation make helps to store image data. The file I/O and looping make it possible to read data from a file and parse it into the right data structures.

In struct ppm data structures and algorithms are suitable for printing out image data in PPM format. The usage of a struct enables quick access to the image data fields, 
and looping enables quick output of all the image's pixel values.



