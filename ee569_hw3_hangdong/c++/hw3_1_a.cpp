#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cmath>
using namespace std;
//texture1.raw texture2.raw texture3.raw texture4.raw texture5.raw texture6.raw texture7.raw texture8.raw texture9.raw texture10.raw texture11.raw texture12.raw
typedef struct
{
    double x1;
    double x2;
    double x3;
    double x4;
    double x5;
    double x6;
    double x7;
    double x8;
    double x9;
}Point;

double* feature_9(int argc, char *argv[],int key) {
    // Define file pointer and variables
    FILE *file;
    int size_r=128, size_c=128;
    int BytesPerPixel = 1;
    int x = (5 / 2);//mask size
    // Allocate image data array
    unsigned char Imagedata[size_r][size_c];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[key], "rb"))) {
        cout << "Cannot open file: " << argv[key] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r * size_c * BytesPerPixel, file);
    fclose(file);
    double Imagedataresizer[size_r + 2 * x][size_c];
    double Imagedataresize[size_r + 2 * x][size_c + 2 * x];
    double Image_ee[size_r][size_c];
    double Image_es[size_r][size_c];
    double Image_ew[size_r][size_c];
    double Image_se[size_r][size_c];
    double Image_ss[size_r][size_c];
    double Image_sw[size_r][size_c];
    double Image_we[size_r][size_c];
    double Image_ws[size_r][size_c];
    double Image_ww[size_r][size_c];
/*
    //subtract global mean
    float sum = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            sum += (float)(Imagedata[i][j]);
        }
    }

    sum = sum / (size_r * size_c);
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            Imagedata[i][j] = (Imagedata[i][j]-(3/3)*sum);
        }
    }
*/
/*
    //extension
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < size_c; jj++) {
            Imagedataresizer[ii][jj] =(double)  Imagedata[0][jj];

        }
    }
    for (int ii = 0; ii < size_r; ii++) {
        for (int jj = 0; jj < size_c; jj++) {
            Imagedataresizer[ii + x][jj] = (double) Imagedata[ii][jj];

        }
    }
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < size_c; jj++) {
            Imagedataresizer[ii + size_r + x][jj] =(double)  Imagedata[size_r - 1][jj];

        }
    }
    //new img
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < size_r + 2 * x; jj++) {
            Imagedataresize[jj][ii] = Imagedataresizer[jj][0];

        }
    }
    for (int ii = 0; ii < size_c; ii++) {
        for (int jj = 0; jj < size_r + 2 * x; jj++) {
            Imagedataresize[jj][ii + x] = Imagedataresizer[jj][ii];

        }
    }
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < size_r + 2 * x; jj++) {
            Imagedataresize[jj][ii + size_c + x] = Imagedataresizer[jj][size_c - 1];

        }
    }

*/

    //extension
    for (int i = 2; i < size_r+ 2; i++) {
        for (int j = 2; j < size_c + 2; j++) {
            Imagedataresize[i][j] = (double)Imagedata[i - 2][j - 2];
        }
    }
    for (int j = 0; j < size_c+2; j++) {
        Imagedataresize[0][j] = (double)Imagedata[0][j];
        Imagedataresize[1][j] = (double)Imagedata[0][j];
        Imagedataresize[size_r - 2][j] = (double)Imagedata[size_c][j];
        Imagedataresize[size_r - 1][j] = (double)Imagedata[size_c][j];
    }
    for (int i = 0; i < size_r + 2; i++) {
        Imagedataresize[i][0] = (double)Imagedata[i][0];
        Imagedataresize[i][1] = (double)Imagedata[i][1];
        Imagedataresize[i][size_c + 1] = (double)Imagedata[i][size_c];
        Imagedataresize[i][size_c + 2] = (double)Imagedata[i][size_c];
    }

    //compute mask
    int e5[5] = {-1, -2, 0, 2, 1};
    int s5[5] = {-1, 0, 2, 0, -1};
    int w5[5] = {-1, 2, 0, -2, 1};
    /*
    int e5e5[5][5] = {};
    int e5s5[5][5] = {};
    int e5w5[5][5] = {};
    int s5e5[5][5] = {};
    int s5s5[5][5] = {};
    int s5w5[5][5] = {};
    int w5e5[5][5] = {};
    int w5s5[5][5] = {};
    int w5w5[5][5] = {};
     */
    int e5s5[5][5] = {{1,0,-2,0,1},{2,0,-4,0,2},{0,0,0,0,0},{-2,0,4,0,-2},{-1,0,2,0,-1}};
    int s5e5[5][5] = {{1,2,0,-2,-1},{0,0,0,0,0},{-2,-4,0,4,2},{0,0,0,0,0},{1,2,0,-2,1}};
    int e5w5[5][5] = {{1,-2,0,2,-1},{2,-4,0,4,-2},{0,0,0,0,0},{-2,4,0,-4,2},{-1,2,0,-2,1}};
    int w5e5[5][5] = {{1,2,0,-2,-1},{-2,-4,0,4,2},{0,0,0,0,0},{2,4,0,-4,-2},{-1,-2,0,2,1}};
    int s5w5[5][5] = {{1,-2,0,2,-1},{0,0,0,0,0},{-2,4,0,-4,2},{0,0,0,0,0},{1,-2,0,2,-1}};
    int w5s5[5][5] = {{1,0,-2,0,1},{-2,0,4,0,-2},{0,0,0,0,0},{2,0,-4,0,2},{-1,0,2,0,-1}};
    int e5e5[5][5] = {{1,2,0,-2,-1},{2,4,0,-4,-2},{0,0,0,0,0},{-2,-4,0,4,2},{-1,-2,0,2,1}};
    int s5s5[5][5] = {{1,0,-2,0,1},{0,0,0,0,0},{-2,0,4,0,-2},{0,0,0,0,0},{1,0,-2,0,1}};
    int w5w5[5][5] = {{1,-2,0,2,-1},{-2,4,0,-4,2},{0,0,0,0,0},{2,-4,0,4,-2},{-1,2,0,-2,1}};
    /*
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            e5e5[i][j] = e5[i] * e5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            e5s5[i][j] = e5[i] * s5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            e5w5[i][j] = e5[i] * w5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            s5e5[i][j] = s5[i] * e5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            s5s5[i][j] = s5[i] * s5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            s5w5[i][j] = s5[i] * w5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            w5e5[i][j] = w5[i] * e5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            w5s5[i][j] = w5[i] * s5[j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            w5w5[i][j] = w5[i] * w5[j];
        }
    }
     */
    //compute the features
    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_ee[i - x][j - x] =(
                    e5e5[0][0] * Imagedataresize[i - 2][j - 2] + e5e5[0][1] * Imagedataresize[i - 2][j - 1] +
                    e5e5[0][2] * Imagedataresize[i - 2][j] +
                    e5e5[0][3] * Imagedataresize[i - 2][j + 1] + e5e5[0][4] * Imagedataresize[i - 2][j + 2] +
                    e5e5[1][0] * Imagedataresize[i - 1][j - 2] +
                    e5e5[1][1] * Imagedataresize[i - 1][j - 1] + e5e5[1][2] * Imagedataresize[i - 1][j] +
                    e5e5[1][3] * Imagedataresize[i - 1][j + 1] +
                    e5e5[1][4] * Imagedataresize[i - 1][j + 2] + e5e5[2][0] * Imagedataresize[i][j - 2] +
                    e5e5[2][1] * Imagedataresize[i][j - 1] +
                    e5e5[2][2] * Imagedataresize[i][j] + e5e5[2][3] * Imagedataresize[i][j + 1] +
                    e5e5[2][4] * Imagedataresize[i][j + 2] +
                    e5e5[3][0] * Imagedataresize[i + 1][j - 2] + e5e5[3][1] * Imagedataresize[i + 1][j - 1] +
                    e5e5[3][2] * Imagedataresize[i + 1][j] +
                    e5e5[3][3] * Imagedataresize[i + 1][j + 1] + e5e5[3][4] * Imagedataresize[i + 1][j + 2] +
                    e5e5[4][0] * Imagedataresize[i + 2][j - 2] +
                    e5e5[4][1] * Imagedataresize[i + 2][j - 1] + e5e5[4][2] * Imagedataresize[i + 2][j] +
                    e5e5[4][3] * Imagedataresize[i + 2][j + 1] +
                    e5e5[4][4] * Imagedataresize[i + 2][j + 2])/36.0;
        }
    }
    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_es[i - x][j - x] =(
                    e5s5[0][0] * Imagedataresize[i - 2][j - 2] + e5s5[0][1] * Imagedataresize[i - 2][j - 1] +
                    e5s5[0][2] * Imagedataresize[i - 2][j] +
                    e5s5[0][3] * Imagedataresize[i - 2][j + 1] + e5s5[0][4] * Imagedataresize[i - 2][j + 2] +
                    e5s5[1][0] * Imagedataresize[i - 1][j - 2] +
                    e5s5[1][1] * Imagedataresize[i - 1][j - 1] + e5s5[1][2] * Imagedataresize[i - 1][j] +
                    e5s5[1][3] * Imagedataresize[i - 1][j + 1] +
                    e5s5[1][4] * Imagedataresize[i - 1][j + 2] + e5s5[2][0] * Imagedataresize[i][j - 2] +
                    e5s5[2][1] * Imagedataresize[i][j - 1] +
                    e5s5[2][2] * Imagedataresize[i][j] + e5s5[2][3] * Imagedataresize[i][j + 1] +
                    e5s5[2][4] * Imagedataresize[i][j + 2] +
                    e5s5[3][0] * Imagedataresize[i + 1][j - 2] + e5s5[3][1] * Imagedataresize[i + 1][j - 1] +
                    e5s5[3][2] * Imagedataresize[i + 1][j] +
                    e5s5[3][3] * Imagedataresize[i + 1][j + 1] + e5s5[3][4] * Imagedataresize[i + 1][j + 2] +
                    e5s5[4][0] * Imagedataresize[i + 2][j - 2] +
                    e5s5[4][1] * Imagedataresize[i + 2][j - 1] + e5s5[4][2] * Imagedataresize[i + 2][j] +
                    e5s5[4][3] * Imagedataresize[i + 2][j + 1] +
                    e5s5[4][4] * Imagedataresize[i + 2][j + 2])/24.0;
        }
    }

    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_ew[i - x][j - x] =(
                    e5w5[0][0] * Imagedataresize[i - 2][j - 2] + e5w5[0][1] * Imagedataresize[i - 2][j - 1] +
                    e5w5[0][2] * Imagedataresize[i - 2][j] +
                    e5w5[0][3] * Imagedataresize[i - 2][j + 1] + e5w5[0][4] * Imagedataresize[i - 2][j + 2] +
                    e5w5[1][0] * Imagedataresize[i - 1][j - 2] +
                    e5w5[1][1] * Imagedataresize[i - 1][j - 1] + e5w5[1][2] * Imagedataresize[i - 1][j] +
                    e5w5[1][3] * Imagedataresize[i - 1][j + 1] +
                    e5w5[1][4] * Imagedataresize[i - 1][j + 2] + e5w5[2][0] * Imagedataresize[i][j - 2] +
                    e5w5[2][1] * Imagedataresize[i][j - 1] +
                    e5w5[2][2] * Imagedataresize[i][j] + e5w5[2][3] * Imagedataresize[i][j + 1] +
                    e5w5[2][4] * Imagedataresize[i][j + 2] +
                    e5w5[3][0] * Imagedataresize[i + 1][j - 2] + e5w5[3][1] * Imagedataresize[i + 1][j - 1] +
                    e5w5[3][2] * Imagedataresize[i + 1][j] +
                    e5w5[3][3] * Imagedataresize[i + 1][j + 1] + e5w5[3][4] * Imagedataresize[i + 1][j + 2] +
                    e5w5[4][0] * Imagedataresize[i + 2][j - 2] +
                    e5w5[4][1] * Imagedataresize[i + 2][j - 1] + e5w5[4][2] * Imagedataresize[i + 2][j] +
                    e5w5[4][3] * Imagedataresize[i + 2][j + 1] +
                    e5w5[4][4] * Imagedataresize[i + 2][j + 2])/36.0;
        }
    }

    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_se[i - x][j - x] =(
                    s5e5[0][0] * Imagedataresize[i - 2][j - 2] + s5e5[0][1] * Imagedataresize[i - 2][j - 1] +
                    s5e5[0][2] * Imagedataresize[i - 2][j] +
                    s5e5[0][3] * Imagedataresize[i - 2][j + 1] + s5e5[0][4] * Imagedataresize[i - 2][j + 2] +
                    s5e5[1][0] * Imagedataresize[i - 1][j - 2] +
                    s5e5[1][1] * Imagedataresize[i - 1][j - 1] + s5e5[1][2] * Imagedataresize[i - 1][j] +
                    s5e5[1][3] * Imagedataresize[i - 1][j + 1] +
                    s5e5[1][4] * Imagedataresize[i - 1][j + 2] + s5e5[2][0] * Imagedataresize[i][j - 2] +
                    s5e5[2][1] * Imagedataresize[i][j - 1] +
                    s5e5[2][2] * Imagedataresize[i][j] + s5e5[2][3] * Imagedataresize[i][j + 1] +
                    s5e5[2][4] * Imagedataresize[i][j + 2] +
                    s5e5[3][0] * Imagedataresize[i + 1][j - 2] + s5e5[3][1] * Imagedataresize[i + 1][j - 1] +
                    s5e5[3][2] * Imagedataresize[i + 1][j] +
                    s5e5[3][3] * Imagedataresize[i + 1][j + 1] + s5e5[3][4] * Imagedataresize[i + 1][j + 2] +
                    s5e5[4][0] * Imagedataresize[i + 2][j - 2] +
                    s5e5[4][1] * Imagedataresize[i + 2][j - 1] + s5e5[4][2] * Imagedataresize[i + 2][j] +
                    s5e5[4][3] * Imagedataresize[i + 2][j + 1] +
                    s5e5[4][4] * Imagedataresize[i + 2][j + 2])/24.0;
        }
    }

    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_ss[i - x][j - x] =(
                    s5s5[0][0] * Imagedataresize[i - 2][j - 2] + s5s5[0][1] * Imagedataresize[i - 2][j - 1] +
                    s5s5[0][2] * Imagedataresize[i - 2][j] +
                    s5s5[0][3] * Imagedataresize[i - 2][j + 1] + s5s5[0][4] * Imagedataresize[i - 2][j + 2] +
                    s5s5[1][0] * Imagedataresize[i - 1][j - 2] +
                    s5s5[1][1] * Imagedataresize[i - 1][j - 1] + s5s5[1][2] * Imagedataresize[i - 1][j] +
                    s5s5[1][3] * Imagedataresize[i - 1][j + 1] +
                    s5s5[1][4] * Imagedataresize[i - 1][j + 2] + s5s5[2][0] * Imagedataresize[i][j - 2] +
                    s5s5[2][1] * Imagedataresize[i][j - 1] +
                    s5s5[2][2] * Imagedataresize[i][j] + s5s5[2][3] * Imagedataresize[i][j + 1] +
                    s5s5[2][4] * Imagedataresize[i][j + 2] +
                    s5s5[3][0] * Imagedataresize[i + 1][j - 2] + s5s5[3][1] * Imagedataresize[i + 1][j - 1] +
                    s5s5[3][2] * Imagedataresize[i + 1][j] +
                    s5s5[3][3] * Imagedataresize[i + 1][j + 1] + s5s5[3][4] * Imagedataresize[i + 1][j + 2] +
                    s5s5[4][0] * Imagedataresize[i + 2][j - 2] +
                    s5s5[4][1] * Imagedataresize[i + 2][j - 1] + s5s5[4][2] * Imagedataresize[i + 2][j] +
                    s5s5[4][3] * Imagedataresize[i + 2][j + 1] +
                    s5s5[4][4] * Imagedataresize[i + 2][j + 2])/16.0;
        }
    }

    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_sw[i - x][j - x] =(
                    s5w5[0][0] * Imagedataresize[i - 2][j - 2] + s5w5[0][1] * Imagedataresize[i - 2][j - 1] +
                    s5w5[0][2] * Imagedataresize[i - 2][j] +
                    s5w5[0][3] * Imagedataresize[i - 2][j + 1] + s5w5[0][4] * Imagedataresize[i - 2][j + 2] +
                    s5w5[1][0] * Imagedataresize[i - 1][j - 2] +
                    s5w5[1][1] * Imagedataresize[i - 1][j - 1] + s5w5[1][2] * Imagedataresize[i - 1][j] +
                    s5w5[1][3] * Imagedataresize[i - 1][j + 1] +
                    s5w5[1][4] * Imagedataresize[i - 1][j + 2] + s5w5[2][0] * Imagedataresize[i][j - 2] +
                    s5w5[2][1] * Imagedataresize[i][j - 1] +
                    s5w5[2][2] * Imagedataresize[i][j] + s5w5[2][3] * Imagedataresize[i][j + 1] +
                    s5w5[2][4] * Imagedataresize[i][j + 2] +
                    s5w5[3][0] * Imagedataresize[i + 1][j - 2] + s5w5[3][1] * Imagedataresize[i + 1][j - 1] +
                    s5w5[3][2] * Imagedataresize[i + 1][j] +
                    s5w5[3][3] * Imagedataresize[i + 1][j + 1] + s5w5[3][4] * Imagedataresize[i + 1][j + 2] +
                    s5w5[4][0] * Imagedataresize[i + 2][j - 2] +
                    s5w5[4][1] * Imagedataresize[i + 2][j - 1] + s5w5[4][2] * Imagedataresize[i + 2][j] +
                    s5w5[4][3] * Imagedataresize[i + 2][j + 1] +
                    s5w5[4][4] * Imagedataresize[i + 2][j + 2])/24.0;
        }
    }

    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_we[i - x][j - x] =(
                    w5e5[0][0] * Imagedataresize[i - 2][j - 2] + w5e5[0][1] * Imagedataresize[i - 2][j - 1] +
                    w5e5[0][2] * Imagedataresize[i - 2][j] +
                    w5e5[0][3] * Imagedataresize[i - 2][j + 1] + w5e5[0][4] * Imagedataresize[i - 2][j + 2] +
                    w5e5[1][0] * Imagedataresize[i - 1][j - 2] +
                    w5e5[1][1] * Imagedataresize[i - 1][j - 1] + w5e5[1][2] * Imagedataresize[i - 1][j] +
                    w5e5[1][3] * Imagedataresize[i - 1][j + 1] +
                    w5e5[1][4] * Imagedataresize[i - 1][j + 2] + w5e5[2][0] * Imagedataresize[i][j - 2] +
                    w5e5[2][1] * Imagedataresize[i][j - 1] +
                    w5e5[2][2] * Imagedataresize[i][j] + w5e5[2][3] * Imagedataresize[i][j + 1] +
                    w5e5[2][4] * Imagedataresize[i][j + 2] +
                    w5e5[3][0] * Imagedataresize[i + 1][j - 2] + w5e5[3][1] * Imagedataresize[i + 1][j - 1] +
                    w5e5[3][2] * Imagedataresize[i + 1][j] +
                    w5e5[3][3] * Imagedataresize[i + 1][j + 1] + w5e5[3][4] * Imagedataresize[i + 1][j + 2] +
                    w5e5[4][0] * Imagedataresize[i + 2][j - 2] +
                    w5e5[4][1] * Imagedataresize[i + 2][j - 1] + w5e5[4][2] * Imagedataresize[i + 2][j] +
                    w5e5[4][3] * Imagedataresize[i + 2][j + 1] +
                    w5e5[4][4] * Imagedataresize[i + 2][j + 2])/36.0;
        }
    }


    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_ws[i - x][j - x] =(
                    w5s5[0][0] * Imagedataresize[i - 2][j - 2] + w5s5[0][1] * Imagedataresize[i - 2][j - 1] +
                    w5s5[0][2] * Imagedataresize[i - 2][j] +
                    w5s5[0][3] * Imagedataresize[i - 2][j + 1] + w5s5[0][4] * Imagedataresize[i - 2][j + 2] +
                    w5s5[1][0] * Imagedataresize[i - 1][j - 2] +
                    w5s5[1][1] * Imagedataresize[i - 1][j - 1] + w5s5[1][2] * Imagedataresize[i - 1][j] +
                    w5s5[1][3] * Imagedataresize[i - 1][j + 1] +
                    w5s5[1][4] * Imagedataresize[i - 1][j + 2] + w5s5[2][0] * Imagedataresize[i][j - 2] +
                    w5s5[2][1] * Imagedataresize[i][j - 1] +
                    w5s5[2][2] * Imagedataresize[i][j] + w5s5[2][3] * Imagedataresize[i][j + 1] +
                    w5s5[2][4] * Imagedataresize[i][j + 2] +
                    w5s5[3][0] * Imagedataresize[i + 1][j - 2] + w5s5[3][1] * Imagedataresize[i + 1][j - 1] +
                    w5s5[3][2] * Imagedataresize[i + 1][j] +
                    w5s5[3][3] * Imagedataresize[i + 1][j + 1] + w5s5[3][4] * Imagedataresize[i + 1][j + 2] +
                    w5s5[4][0] * Imagedataresize[i + 2][j - 2] +
                    w5s5[4][1] * Imagedataresize[i + 2][j - 1] + w5s5[4][2] * Imagedataresize[i + 2][j] +
                    w5s5[4][3] * Imagedataresize[i + 2][j + 1] +
                    w5s5[4][4] * Imagedataresize[i + 2][j + 2])/24.0;
        }
    }

    for (int i = x; i < size_r + x; i++) {
        for (int j = x; j < size_c + x; j++) {
            Image_ww[i - x][j - x] =(
                    w5w5[0][0] * Imagedataresize[i - 2][j - 2] + w5w5[0][1] * Imagedataresize[i - 2][j - 1] +
                    w5w5[0][2] * Imagedataresize[i - 2][j] +
                    w5w5[0][3] * Imagedataresize[i - 2][j + 1] + w5w5[0][4] * Imagedataresize[i - 2][j + 2] +
                    w5w5[1][0] * Imagedataresize[i - 1][j - 2] +
                    w5w5[1][1] * Imagedataresize[i - 1][j - 1] + w5w5[1][2] * Imagedataresize[i - 1][j] +
                    w5w5[1][3] * Imagedataresize[i - 1][j + 1] +
                    w5w5[1][4] * Imagedataresize[i - 1][j + 2] + w5w5[2][0] * Imagedataresize[i][j - 2] +
                    w5w5[2][1] * Imagedataresize[i][j - 1] +
                    w5w5[2][2] * Imagedataresize[i][j] + w5w5[2][3] * Imagedataresize[i][j + 1] +
                    w5w5[2][4] * Imagedataresize[i][j + 2] +
                    w5w5[3][0] * Imagedataresize[i + 1][j - 2] + w5w5[3][1] * Imagedataresize[i + 1][j - 1] +
                    w5w5[3][2] * Imagedataresize[i + 1][j] +
                    w5w5[3][3] * Imagedataresize[i + 1][j + 1] + w5w5[3][4] * Imagedataresize[i + 1][j + 2] +
                    w5w5[4][0] * Imagedataresize[i + 2][j - 2] +
                    w5w5[4][1] * Imagedataresize[i + 2][j - 1] + w5w5[4][2] * Imagedataresize[i + 2][j] +
                    w5w5[4][3] * Imagedataresize[i + 2][j + 1] +
                    w5w5[4][4] * Imagedataresize[i + 2][j + 2])/36.0;
        }
    }

    double egy_ee = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_ee += Image_ee[i][j] * Image_ee[i][j];
        }
    }
    egy_ee = egy_ee / (size_r * size_c);

    double egy_es = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_es += Image_es[i][j] * Image_es[i][j];
        }
    }
    egy_es = egy_es / (size_r * size_c);

    double egy_ew = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_ew += Image_ew[i][j] * Image_ew[i][j];
        }
    }
    egy_ew = egy_ew / (size_r * size_c);

    double egy_se = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_se += Image_se[i][j] * Image_se[i][j];
        }
    }
    egy_se = egy_se / (size_r * size_c);

    double egy_ss = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_ss += Image_ss[i][j] * Image_ss[i][j];
        }
    }
    egy_ss = egy_ss / (size_r * size_c);

    double egy_sw = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_sw += Image_sw[i][j] * Image_sw[i][j];
        }
    }
    egy_sw = egy_sw / (size_r * size_c);

    double egy_we = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_we += Image_we[i][j] * Image_we[i][j];
        }
    }
    egy_we = egy_we / (size_r * size_c);

    double egy_ws = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_ws += Image_ws[i][j] * Image_ws[i][j];
        }
    }
    egy_ws = egy_ws / (size_r * size_c);

    double egy_ww = 0;
    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            egy_ww += Image_ww[i][j] * Image_ww[i][j];
        }
    }
    egy_ww = egy_ww / (size_r * size_c);
    double* feature=(double*)malloc(sizeof(double)*9);
    *(feature+0) = egy_ee;// (size_r * size_c);
    *(feature+1) = egy_es;// (size_r * size_c);
    *(feature+2) = egy_ew;// (size_r * size_c);
    *(feature+3) = egy_se;// (size_r * size_c);
    *(feature+4) = egy_ss;// (size_r * size_c);
    *(feature+5) = egy_sw;// (size_r * size_c);
    *(feature+6) = egy_we;// (size_r * size_c);
    *(feature+7) = egy_ws;// (size_r * size_c);
    *(feature+8) = egy_ww;// (size_r * size_c);
    return feature;
}
int k_means(double feature[12][9], int k)
{
/*
    double feature[12][9]={
            {209, 339, 72, 65, 54, 48, 370, 140, 20 },
            {44, 95, 16, 12, 13, 10, 61, 30, 5 },
            {25, 203, 11, 11, 9, 8, 42, 19, 4 },
            {233, 376, 76, 75, 56, 54, 407, 159, 20 },
            {26, 196, 10, 12, 9, 8, 49, 21, 4 },
            {231, 391, 80, 74, 61, 56, 393, 158, 23 },
            {16, 241, 8, 8, 8, 7, 18, 16, 4 },
            {16, 232, 8, 8, 8, 7, 18, 16, 4 },
            {28, 87, 10, 11, 9, 8, 43, 21, 4 },
            {15, 240, 8, 8, 8, 7, 18, 15, 3,},
            {22, 207, 10, 9, 8, 6, 34, 17, 3 },
            {51, 102, 20, 15, 17, 14, 67, 38, 7 }
    };
*/
    vector<Point> initial_temp;
    vector<Point> vecPoint;
    vector<Point> vecCenter;
    vector<vector<Point> > vecCluster;
    Point temp;
    double distance,mindistance;
    int flag,round=1;
    double errorSum1=0;
    double errorSum2=1;
    for(int i=0;i<12;i++)
    {
        temp.x1=feature[i][0];
        temp.x2=feature[i][1];
        temp.x3=feature[i][2];
        temp.x4=feature[i][3];
        temp.x5=feature[i][4];
        temp.x6=feature[i][5];
        temp.x7=feature[i][6];
        temp.x8=feature[i][7];
        temp.x9=feature[i][8];
        vecPoint.push_back(temp);
    }

    temp.x1=feature[1][0];
    temp.x2=feature[1][1];
    temp.x3=feature[1][2];
    temp.x4=feature[1][3];
    temp.x5=feature[1][4];
    temp.x6=feature[1][5];
    temp.x7=feature[1][6];
    temp.x8=feature[1][7];
    temp.x9=feature[1][8];
    vecCenter.push_back(temp);
    temp.x1=feature[2][0];
    temp.x2=feature[2][1];
    temp.x3=feature[2][2];
    temp.x4=feature[2][3];
    temp.x5=feature[2][4];
    temp.x6=feature[2][5];
    temp.x7=feature[2][6];
    temp.x8=feature[2][7];
    temp.x9=feature[2][8];
    vecCenter.push_back(temp);
    temp.x1=feature[0][0];
    temp.x2=feature[0][1];
    temp.x3=feature[0][2];
    temp.x4=feature[0][3];
    temp.x5=feature[0][4];
    temp.x6=feature[0][5];
    temp.x7=feature[0][6];
    temp.x8=feature[0][7];
    temp.x9=feature[0][8];
    vecCenter.push_back(temp);
    temp.x1=feature[6][0];
    temp.x2=feature[6][1];
    temp.x3=feature[6][2];
    temp.x4=feature[6][3];
    temp.x5=feature[6][4];
    temp.x6=feature[6][5];
    temp.x7=feature[6][6];
    temp.x8=feature[6][7];
    temp.x9=feature[6][8];
    vecCenter.push_back(temp);



    for(int i=0;i<4;i++)
    {
        vecCluster.push_back(initial_temp);
    }
    while(fabs(errorSum2-errorSum1)>0.001)
    {
        for(int i=0;i<vecCluster.size();i++)
        {
            vecCluster[i].clear();
        }
        for(int i=0;i<12;i++)
        {
            mindistance=sqrt(pow(vecPoint[i].x1-vecCenter[0].x1,2)+pow(vecPoint[i].x2-vecCenter[0].x2,2)+pow(vecPoint[i].x3-vecCenter[0].x3,2)
                             +pow(vecPoint[i].x4-vecCenter[0].x4,2)+pow(vecPoint[i].x5-vecCenter[0].x5,2)+pow(vecPoint[i].x6-vecCenter[0].x6,2)
                             +pow(vecPoint[i].x7-vecCenter[0].x7,2)+pow(vecPoint[i].x8-vecCenter[0].x8,2)+pow(vecPoint[i].x9-vecCenter[0].x9,2));
            flag=0;
            for(int k=1;k<4;k++)
            {
                distance=sqrt(pow(vecPoint[i].x1-vecCenter[k].x1,2)+pow(vecPoint[i].x2-vecCenter[k].x2,2)+pow(vecPoint[i].x3-vecCenter[k].x3,2)
                              +pow(vecPoint[i].x4-vecCenter[k].x4,2)+pow(vecPoint[i].x5-vecCenter[k].x5,2)+pow(vecPoint[i].x6-vecCenter[k].x6,2)
                              +pow(vecPoint[i].x7-vecCenter[k].x7,2)+pow(vecPoint[i].x8-vecCenter[k].x8,2)+pow(vecPoint[i].x9-vecCenter[k].x9,2));
                if(distance<mindistance)
                {
                    flag=k;
                    mindistance=distance;
                }
            }
            vecCluster[flag].push_back(vecPoint[i]);
        }

        cout<<"-------NO."<<round<<"th iteration result:-------"<<endl;
        for(int i=0;i<vecCluster.size();i++)
        {
            cout<<"Cluster"<<i+1<<": ";
            for(int j=0;j<vecCluster[i].size();j++)
            {
                for(int key=0;key<12;key++)
                {
                    if(vecCluster[i][j].x1==feature[key][0]&&vecCluster[i][j].x2==feature[key][1])
                    {
                        cout<<"texture"<<key+1<<" ";
                    }
                }
            }
            cout<<endl;
        }
        cout<<"--------------------------------------"<<endl;

        if(round==1)
        {

            errorSum1=0;
            for(int k=0;k<4;k++)
            {
                for(int i=0;i<vecCluster[k].size();i++)
                {
                    errorSum1+=pow(vecCenter[k].x1-vecCluster[k][i].x1,2)+pow(vecCenter[k].x2-vecCluster[k][i].x2,2)+pow(vecCenter[k].x3-vecCluster[k][i].x3,2)
                               +pow(vecCenter[k].x4-vecCluster[k][i].x4,2)+pow(vecCenter[k].x5-vecCluster[k][i].x5,2)+pow(vecCenter[k].x6-vecCluster[k][i].x6,2)
                               +pow(vecCenter[k].x7-vecCluster[k][i].x7,2)+pow(vecCenter[k].x8-vecCluster[k][i].x8,2)+pow(vecCenter[k].x9-vecCluster[k][i].x9,2);
                }
            }
        }
        else
        {
            errorSum1=errorSum2;
        }

        round++;
        double sum_x1,sum_x2,sum_x3,sum_x4,sum_x5,sum_x6,sum_x7,sum_x8,sum_x9;
        vecCenter.clear();
        for(int k=0;k<4;k++)
        {
            sum_x1=0;sum_x2=0;sum_x3=0;sum_x4=0;sum_x5=0;sum_x6=0;sum_x7=0;sum_x8=0;sum_x9=0;
            for(int i=0;i<vecCluster[k].size();i++)
            {
                sum_x1+=vecCluster[k][i].x1;
                sum_x2+=vecCluster[k][i].x2;
                sum_x3+=vecCluster[k][i].x3;
                sum_x4+=vecCluster[k][i].x4;
                sum_x5+=vecCluster[k][i].x5;
                sum_x6+=vecCluster[k][i].x6;
                sum_x7+=vecCluster[k][i].x7;
                sum_x8+=vecCluster[k][i].x8;
                sum_x9+=vecCluster[k][i].x9;
            }
            temp.x1=sum_x1/vecCluster[k].size();
            temp.x2=sum_x2/vecCluster[k].size();
            temp.x3=sum_x3/vecCluster[k].size();
            temp.x4=sum_x4/vecCluster[k].size();
            temp.x5=sum_x5/vecCluster[k].size();
            temp.x6=sum_x6/vecCluster[k].size();
            temp.x7=sum_x7/vecCluster[k].size();
            temp.x8=sum_x8/vecCluster[k].size();
            temp.x9=sum_x9/vecCluster[k].size();
            vecCenter.push_back(temp);
        }
        errorSum2=0;

        for(k=0;k<4;k++)
        {
            for(int i=0;i<vecCluster[k].size();i++)
            {
                errorSum2+=pow(vecCenter[k].x1-vecCluster[k][i].x1,2)+pow(vecCenter[k].x2-vecCluster[k][i].x2,2)+pow(vecCenter[k].x3-vecCluster[k][i].x3,2)
                           +pow(vecCenter[k].x4-vecCluster[k][i].x4,2)+pow(vecCenter[k].x5-vecCluster[k][i].x5,2)+pow(vecCenter[k].x6-vecCluster[k][i].x6,2)
                           +pow(vecCenter[k].x7-vecCluster[k][i].x7,2)+pow(vecCenter[k].x8-vecCluster[k][i].x8,2)+pow(vecCenter[k].x9-vecCluster[k][i].x9,2);
            }
        }
    }

    cout<<"------------Final result:-------------"<<endl;
    for(int i=0;i<vecCluster.size();i++)
    {
        cout<<"Cluster"<<i+1<<": ";
        for(int j=0;j<vecCluster[i].size();j++)
        {
            for(int key=0;key<12;key++)
            {
                if(vecCluster[i][j].x1==feature[key][0]&&vecCluster[i][j].x2==feature[key][1])
                {
                    cout<<"texture"<<key+1<<" ";
                }
            }
            //cout<<"("<<vecCluster[i][j].x1<<","<<vecCluster[i][j].x2<<","<<vecCluster[i][j].x3<<","<<vecCluster[i][j].x4<<","<<vecCluster[i][j].x5<<","<<vecCluster[i][j].x6<<","<<vecCluster[i][j].x7<<","<<vecCluster[i][j].x8<<","<<vecCluster[i][j].x9<<") ";
        }
        cout<<endl;
    }
    return 0;
}
int main(int argc, char *argv[])
{
        cout << "readraw IO is working" << endl;
    double feature_vec[12][9]={};
    double* p;
        for(int key=1;key<=12;key++)
        {
            //cout<<"start iteration time: "<<key<<endl;
            p=feature_9(argc,argv,key);
            for (int i = 0; i < 9; i++)
            {
                feature_vec[key-1][i]=*(p + i);
                cout<<(int)feature_vec[key-1][i]<<" ";
            }
            cout<<endl;
            //cout<<"iteration time: "<<key<<" "<<"finished"<<endl;
        }

        int k=4;
        k_means(feature_vec,k);

        return 0;
}
