#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The RGB values of a pixel. */
struct Pixel {
    int red;
    int green;
    int blue;
};

/* An image loaded from a PPM file. */
struct PPM {
    /* TODO: Question 1 */

    int width;
    int height;
    int color;
    char number[3];
    struct Pixel * pixels;

};

/* Reads an image from an open PPM file.
 * Returns a new struct PPM, or NULL if the image cannot be read. */
 
struct PPM *getPPM(FILE * f)
{
    /* Read the PPM file's magic number */
    char number[3];
    if (fscanf(f, "%2s\n", number) != 1) {
        fprintf(stderr, "Invalid  missing number\n");
        return NULL;
    }


    /* Read the image width, height, and maximum color value */
    int width, height, max_color;
    if (fscanf(f, "%d %d\n%d\n", &width, &height, &max_color) != 3) {
        fprintf(stderr, "Invalid  missing image dimensions or maximum color \n");
        return NULL;
    }

    /* Allocate memory for the pixel array */
    struct Pixel *pixels = malloc(width * height * sizeof(struct Pixel));
    

    /* Read the pixel values */
    int i;
    for (i = 0; i < width * height; i++) {
        int red, green, blue;
        if (fscanf(f, "%d %d %d", &red, &green, &blue) != 3) {
            fprintf(stderr, "Invalid pixel data is missing or corrupt\n");
            free(pixels);
            return NULL;
        }
        pixels[i].red = red;
        pixels[i].green = green;
        pixels[i].blue = blue;
    }

    /* Create and return the PPM structure */
    struct PPM *img = malloc(sizeof(struct PPM));
    if (img == NULL) {
        fprintf(stderr, "Error\n");
        free(pixels);
        return NULL;
    }
    strcpy(img->number, number);
    img->width = width;
    img->height = height;
    img->color = max_color;
    img->pixels = pixels;
    return img;
}

/* Write img to stdout in PPM format. */
    /* TODO: Question 2b */
void showPPM(const struct PPM *img)

{
     /* Print the PPM file header */
    printf("%s\n", img->number);
    printf("%d %d\n", img->width, img->height);
    printf("%d\n", img->color);

    /* Print the pixel values */
    int i;
    for (i = 0; i < img->width * img->height; i++) {
        printf("%d %d %d\n", img->pixels[i].red, img->pixels[i].green, img->pixels[i].blue);
        }

}

/* Opens and reads a PPM file, returning a pointer to a new struct PPM.
 * On error, prints an error message and returns NULL. */
struct PPM *readPPM(const char *filename)
{
    /* Open the file for reading */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);

        return NULL;
    }

    /* Load the image using getPPM */
    struct PPM *img = getPPM(f);

    /* Close the file */
    fclose(f);

    if (img == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }

    return img;
}


struct PPM *copyPPM(const struct PPM *old)
{
    // Allocating memory for the new PPM structure
    struct PPM *new = malloc(sizeof(struct PPM));

    // Copying from the old PPM to the new PPM
    strcpy(new->number, old->number);
    new->width = old->width;
    new->height = old->height;
    new->color = old->color;

    // Allocating memory for the pixel array in the new PPM
    new->pixels = malloc(new->width *new->height * sizeof(struct Pixel));

    // Coping the pixel data from the old PPM to the new PPM
    for (int i = 0; i < new->width *new->height; i++)
    {
        new->pixels[i].red = old->pixels[i].red;
        new->pixels[i].green = old->pixels[i].green;
        new->pixels[i].blue = old->pixels[i].blue;
    }
    return new;
}



/* Encode the string text into the red channel of image img.
 * Returns a new struct PPM, or NULL on error. */
struct PPM *encode(const char *text, const struct PPM *img)
{ 
    struct PPM *encodeimg = copyPPM(img); // New PPM made by copying the old one

    int random;
    int n = (img->height * img->width) / (strlen(text) + 1); 
    random = rand() % n;                                     // Generating random number between zero and n-1

    int i = 0;
    int j = random;
    while (i < strlen(text))
    {
        if (encodeimg->pixels[j].red == text[i])  
        {
            j = j + 1; // If yes, simply move to the next one
        }
        else
        {
            encodeimg->pixels[j].red = text[i]; 
            i = i + 1;
            j = j + random; // Incremented by random and not 1 so that two successive pixels arent selected
        }
    }

    if (encodeimg == NULL)
    {
        return NULL;
    }
    else
    {
        fprintf(stderr, "Message Encoded.\n");
        return encodeimg;
    }

}



/* Extract the string encoded in the red channel of newimg, by comparing it
 * with oldimg. The two images must have the same size.
 * Returns a new C string, or NULL on error. */
char *decode(const struct PPM *oldimg, const struct PPM *newimg)
{
       int i = 0;
    int j = 0;

    if (oldimg->height * oldimg->width == newimg->height * newimg->width) // Checking if both images have same dimensions
    {
        char *str = (char *)malloc(oldimg->height * oldimg->width * sizeof(char));

        while (i < oldimg->height * oldimg->width) 
        {
            if (oldimg->pixels[i].red != newimg->pixels[i].red) // If red values are not same, add the red value of newimg to str
            {
                str[j] = newimg->pixels[i].red;
                j = j + 1;
            }

            i = i + 1;
        }

        return str; // Final decoded message is returned
    }
    else
    {
        return NULL;
    }


}


/* TODO: Question 3 */
int main(int argc, char *argv[])
{    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Parse command-line arguments */
    if (argc == 3 && strcmp(argv[1], "t") == 0) {
        /* Mode "t" - test PPM reading and writing */

        struct PPM *img = readPPM(argv[2]);
        showPPM(img);

    } else if (argc == 3 && strcmp(argv[1], "e") == 0) {
        /* Mode "e" - encode PPM */
        struct PPM *oldimg = readPPM(argv[2]);

        fprintf(stderr, "Enter message for encode ");
        char message[1024];
        fgets(message, 1024, stdin);
        message[strcspn(message, "\n")] = 0;


        /* TODO: prompt for a message from the user, and read it into a string */

        struct PPM *newimg = encode(message,oldimg);
        showPPM(newimg);
       
        
        /* TODO: encode the text into the image with encode, and assign to newimg */

        /* TODO: write the image to stdout with showPPM */

    } else if (argc == 4 && strcmp(argv[1], "d") == 0) {
        /* Mode "d" - decode PPM */

        struct PPM *oldimg =  readPPM(argv[2]);
    
        /* TODO: get original file filename from argv, load it with
           readPPM, then assign to oldimg */

        struct PPM *newimg = readPPM(argv[3]);
        /* TODO: get encoded file filename from argv, load it with
           readPPM, then assign to newimg */

        char *message= (char *)malloc(255);
        message = decode(oldimg, newimg); // Using the decode function and storing the result in 'message'

        if (message != NULL)
        {

            printf("Decoded Message ");
            printf("%s", message); // Message is printed
        }
        else
        {
            fprintf(stderr, "Couldn't decode\n");
            return 1;
        }
;

        /* TODO: decode the encodedPPM with the comparisonPPM and assign to message */

        /* TODO: print the decoded message to stdout */

    } else {
        fprintf(stderr, "Unrecognised or incomplete command \n");
        return 1;
    }
  return 0;
}
