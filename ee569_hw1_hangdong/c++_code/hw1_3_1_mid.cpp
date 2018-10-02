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
    int Size;
    int Size_r = 256;
    int Size_c = 256;
    int size = Size_r * Size_c;
    int matrix_size =5;//matrix的参数应该为变量
    int M = 4;//Values of each channels
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
    unsigned char output[Size_r][Size_c][BytesPerPixel];
    int col_map[Size_r][Size_c][BytesPerPixel];
    int *row = (int *) malloc(sizeof(int) * size * 3);
    int *column = (int *) malloc(sizeof(int) * size * 3);
    int y = floor((float) matrix_size / 2);

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size_r * Size_c * BytesPerPixel, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////


    //unsigned char Imagedataresizer[Size_r + 2 * x][Size_c][BytesPerPixel];
    //unsigned char Imagedataresize[Size_r + 2 * x][Size_c + 2 * x][BytesPerPixel];
    //extension
/*
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < Size_c; jj++) {
            Imagedataresizer[ii][jj][0] = (unsigned char) Imagedata[ii][jj][0];
            Imagedataresizer[ii][jj][1] = (unsigned char) Imagedata[ii][jj][1];
            Imagedataresizer[ii][jj][2] = (unsigned char) Imagedata[ii][jj][2];
        }
    }
    for (int ii = 0; ii < Size_r; ii++) {
        for (int jj = 0; jj < Size_c; jj++) {
            Imagedataresizer[ii + x][jj][0] = (unsigned char) Imagedata[ii][jj][0];
            Imagedataresizer[ii + x][jj][1] = (unsigned char) Imagedata[ii][jj][1];
            Imagedataresizer[ii + x][jj][2] = (unsigned char) Imagedata[ii][jj][2];
        }
    }
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < Size_c; jj++) {
            Imagedataresizer[ii + Size_r + x][jj][0] = (unsigned char) Imagedata[Size_r - 1-ii][jj][0];
            Imagedataresizer[ii + Size_r + x][jj][1] = (unsigned char) Imagedata[Size_r - 1-ii][jj][1];
            Imagedataresizer[ii + Size_r + x][jj][2] = (unsigned char) Imagedata[Size_r - 1-ii][jj][2];
        }
    }
    //new img
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < Size_r + 2 * x; jj++) {
            Imagedataresize[jj][ii][0] = Imagedataresizer[jj][ii][0];
            Imagedataresize[jj][ii][1] = Imagedataresizer[jj][ii][1];
            Imagedataresize[jj][ii][2] = Imagedataresizer[jj][ii][2];
        }
    }
    for (int ii = 0; ii < Size_c; ii++) {
        for (int jj = 0; jj < Size_r + 2 * x; jj++) {
            Imagedataresize[jj][ii + x][0] = Imagedataresizer[jj][ii][0];
            Imagedataresize[jj][ii + x][1] = Imagedataresizer[jj][ii][1];
            Imagedataresize[jj][ii + x][2] = Imagedataresizer[jj][ii][2];
        }
    }
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < Size_r + 2 * x; jj++) {
            Imagedataresize[jj][ii + Size_c + x][0] = Imagedataresizer[jj][Size_c - 1-ii][0];
            Imagedataresize[jj][ii + Size_c + x][1] = Imagedataresizer[jj][Size_c - 1-ii][1];
            Imagedataresize[jj][ii + Size_c + x][2] = Imagedataresizer[jj][Size_c - 1-ii][2];
        }
    }
*/
//start build up denoise
    for (int n = 0; n < 3; n++) {
        for (int i = 0; i < Size_r; i++) {
            for (int j = 0; j < Size_c; j++) {

                output[i][j][n] = Imagedata[i][j][n];
            }
        }
    }
    int matrix_num=matrix_size*matrix_size;
    for (int i = 0; i < Size_r-2*y; i++) {
        for (int j = 0; j < Size_c-2*y; j++)
        {
            int value_r[matrix_num],value_g[matrix_num],value_b[matrix_num];
            int x=0;
            for (int m = 0; m < matrix_size; m++) {
                for (int n = 0; n < matrix_size; n++) {
                    value_r[x] = Imagedata[i + m][j + n][0];
                    value_g[x] = Imagedata[i + m][j + n][1];
                    value_b[x] = Imagedata[i + m][j + n][2];
                    x=x+1;
                }
            }
            sort(value_r,value_r+matrix_num);
            sort(value_g,value_g+matrix_num);
            sort(value_b,value_b+matrix_num);
            int pixel = floor(matrix_size / 2);
            output[i + pixel][j + pixel][0] = value_r[(int)(matrix_num/2)] ;
            output[i + pixel][j + pixel][1] = value_g[(int)(matrix_num/2)] ;
            output[i + pixel][j + pixel][2] = value_b[(int)(matrix_num/2)] ;
        }
    }
    /////////////////////////FINISH MY CODE////////////////////////////////////////////
    if (!(file = fopen(argv[2], "wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (Size_r) * (Size_c) * BytesPerPixel, file);
    fclose(file);
    return 0;
}

