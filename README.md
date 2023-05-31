# Image-Steganography
This coursework involves writing a steganography program in C called "steg," which is capable of encoding and decoding secret messages in bitmap images. The program will operate in two modes: encode and decode, selected by the first command-line argument being "e" or "d."

# The Problem
The steganography program, "steg," will encode and decode secret messages in bitmap images. The encoding process involves replacing the red value in random pixels of the image with characters from the text, resulting in a new image. The decoding process involves comparing the new image with the original image and extracting characters from the new image where it differs from the old one.

<h3>Encoding Command:</h3>

./steg e old.ppm >new.ppm

The program prompts for a message to encode and outputs the new image to stdout, which can be redirected to a file.

<h3>Decoding Command:</h3>

./steg d old.ppm new.ppm

The program decodes the message and outputs the hidden text to stdout.

# The PPM Image Format
The program will work with Plain PPM format images, which are simple open source image formats designed to be easily read and written by C programs. A Plain PPM file consists of ASCII text and has the following structure:

P3

#comment1

#...

#commentN

width height

max

r1 g1 b1

r2 g2 b2

r3 g3 b3

...

P3: Code indicating Plain PPM format.

comment: Arbitrary optional comment text.
width: Integer number of columns.
height: Integer number of rows.
max: Integer maximum colour value (usually 255).
ri gi bi: Integers between 0 and max representing the red, green, and blue values of pixel i.
All integers are in decimal format.

