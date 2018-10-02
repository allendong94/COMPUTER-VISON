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
    int Size_r = 300;
    int Size_c = 400;
    // Check for proper syntax
    if (argc < 3) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4) {
        BytesPerPixel = 1; // default 1 is grey image；3 original
    } else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5) {
            Size = atoi(argv[4]);
        }
    }
    // Allocate image data array
    unsigned char Imagedata[Size_r][Size_c][BytesPerPixel];
    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size_r * Size_c * BytesPerPixel, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    /*
     * int outImagedata[400][300][3];
    for (int i = 0; i < Size_r; i++)
    {
        for (int j = 0; j< Size_c; j++) {
            outImagedata[i][j][2] = (int) Imagedata[i][j][2];
            outImagedata[i][j][1] = (int) Imagedata[i][j][1];
            outImagedata[i][j][0] = (int) Imagedata[i][j][0];
        }
    }
    */
    /*
    ofstream fout("out.txt");
    for (int i = 0; i < Size_r; i++) {
        for (int j = 0; j< Size_c; j++) {
            fout <<outImagedata[i][j][2] << " ";
        }
    }
    fout.close();
     */
    int histogram_r[256]={};int histogram_g[256]={};int histogram_b[256]={};// initiual
    int culmul_r[256];int culmul_g[256];int culmul_b[256];
    // count every grayscale's number;
    for (int i = 0; i < Size_r; i++)
    {
        for (int j = 0; j< Size_c; j++) {
            histogram_r[Imagedata[i][j][0]]=histogram_r[Imagedata[i][j][0]]+1;
            histogram_g[Imagedata[i][j][1]]=histogram_g[Imagedata[i][j][1]]+1;
            histogram_b[Imagedata[i][j][2]]=histogram_b[Imagedata[i][j][2]]+1;
        }
    }
    culmul_r[0]=histogram_r[0];culmul_g[0]=histogram_g[0];culmul_b[0]=histogram_b[0];
    for (int m=1;m<256;m++)
    {
        culmul_r[m]=histogram_r[m]+culmul_r[m-1];
        culmul_g[m]=histogram_g[m]+culmul_g[m-1];
        culmul_b[m]=histogram_b[m]+culmul_b[m-1];
    }
    for (int m=0;m<256;m++)
    {
        culmul_r[m]=(float(culmul_r[m])/float((Size_r*Size_c)))*255;
        culmul_g[m]=(float(culmul_g[m])/float((Size_r*Size_c)))*255;
        culmul_b[m]=(float(culmul_b[m])/float((Size_r*Size_c)))*255;
    }
    for (int i = 0; i < Size_r; i++)
    {
        for (int j = 0; j< Size_c; j++) {
            Imagedata[i][j][0]=(culmul_r[Imagedata[i][j][0]]);
            Imagedata[i][j][1]=(culmul_g[Imagedata[i][j][1]]);
            Imagedata[i][j][2]=(culmul_b[Imagedata[i][j][2]]);
        }
    }
    /////////////////////////FINISH MY CODE////////////////////////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Size_r*Size_c*BytesPerPixel, file);
    fclose(file);
    return 0;
}
