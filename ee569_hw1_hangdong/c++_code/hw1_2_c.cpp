// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "readraw IO is working" << endl;
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    int Size = 512;
    int Size_r =256;
    int Size_c =256;
    // Check for proper syntax
    if (argc < 3) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }
    // Check if image is grayscale or color
    if (argc < 4) {
        BytesPerPixel = 1; // default 1 is grey image；3 original
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5) {
            Size = atoi(argv[4]);
        }
    }
    // Allocate image data array
    unsigned char Imagedata[Size_r][Size_c][BytesPerPixel];
    unsigned char outImagedata[Size_r][Size_c][BytesPerPixel];
    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size_r * Size_c * BytesPerPixel, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    for (int i = 0; i < Size_r; i++)
    {
        for (int j = 0; j< Size_c; j++)
        {
            outImagedata[i][j][0]=Imagedata[i][j][0];
            outImagedata[i][j][1]=Imagedata[i][j][1];
            outImagedata[i][j][2]=Imagedata[i][j][2];
        }
    }
    //deal with channel red
    float scale_r=3.2/5.0;
    float scale_g=3.0/5.0;
    float scale_b=3.0/5.0;
    int x_r=floor(256*(1-scale_r));
    int x_g=floor(256*(1-scale_g)/4);
    int x_b=floor(256*(1-scale_b)/5);
    for (int i = 0; i < Size_r; i++)
    {
        for (int j = 0; j< Size_c; j++)
        {
            outImagedata[i][Size_c-1-j][0]=floor(scale_r*(255-1.0*Imagedata[i][j][0]))+x_r;
            outImagedata[i][Size_c-1-j][1]=floor(scale_g*(255-1.0*Imagedata[i][j][1]))+x_g;
            outImagedata[i][Size_c-1-j][2]=floor(scale_b*(255-1.0*Imagedata[i][j][2]))+x_b;
        }
    }
    //deal with channel green and blue
    /////////////////////////FINISH MY CODE////////////////////////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(outImagedata, sizeof(unsigned char), Size_r*Size_c*BytesPerPixel, file);
    fclose(file);
    return 0;
}





