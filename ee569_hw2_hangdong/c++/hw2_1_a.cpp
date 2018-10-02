#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(int argc, char *argv[])

{
    cout<<"readraw IO is working"<<endl;
    // Define file pointer and variables
    FILE *file;
    int size_r,size_c;
    int BytesPerPixel;
    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default 1 is grey image；3 original
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5) {
            size_r = atoi(argv[4]);
            size_c = atoi(argv[5]);
        }
    }
    // Allocate image data array
    unsigned char Imagedata[size_r][size_c][BytesPerPixel];
    unsigned char Warp[size_r][size_c][BytesPerPixel];
    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    fclose(file);
    int N=size_c/2;int v,y;float u;int M;
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //For part 1
    for (int i = 0; i < size_r / 2; i++) {
        M=pow((N*N-(N-i-1)*(N-i-1)),0.5);
        for(int j = 0; j <M+1; j++) {
            for (int k = 0; k < 3; k++) {
                u = ((float)N/(float)(M))*(float)j;
                v = u - floor(u);
                y = floor(u);
                Warp[i][j+(N-1)-M][k] = (v)*Imagedata[i][y + 1][k]+ (1-v)*Imagedata[i][y][k];

            }
        }
    }

    // For part 2

    for (int i = 0; i < size_r / 2; i++) {
        M=pow((N*N-(N-i-1)*(N-i-1)),0.5);
        for (int j = size_c/2; j < (size_c/2 + M); j++) {
            for (int k = 0; k < 3; k++) {
                u = ((float)N/(float)(M))*(float)(j- N)+N;
                v = u - floor(u);
                y = floor(u);
                Warp[i][j][k] =  (v)*Imagedata[i][y + 1][k]+ (1-v)*Imagedata[i][y][k];
            }
        }
    }

    // For part 3

    for (int i = size_r/2; i < size_r; i++) {
        M=pow((N*N-(N-i-1)*(N-i-1)),0.5);
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 3; k++) {

                u= ((float)N/(float)(M)*(float)j);
                v = u - floor(u);
                y = floor(u);
                Warp[i][j+N-M][k] = (v)*Imagedata[i][y + 1][k]+ (1-v)*Imagedata[i][y][k];
            }
        }
    }

    // For part 4

    for (int i = size_r / 2; i < size_r; i++) {
        M=pow((N*N-(N-i-1)*(N-i-1)),0.5);
        for (int j = size_c / 2; j < size_c - (N-M); j++) {
            for(int k = 0; k < 3; k++) {
                u= (float(N)/(float)(M)*(float)(j - N)) + N;
                v = u - floor(u);
                y = floor(u);
                Warp[i][j][k] = (v)*Imagedata[i][y + 1][k]+ (1-v)*Imagedata[i][y][k];
            }
        }
    }

    ///////////////////////// END /////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Warp, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    fclose(file);
    return 0;
}
