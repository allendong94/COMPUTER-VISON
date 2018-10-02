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
    int MAX=255*255;
    int Size;
    int Size_r = 256;
    int Size_c = 256;
    int size = Size_r * Size_c;
    int matrix_size = 5;//matrix的参数应该为变量
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
    unsigned char Imagedata1[Size_r][Size_c][BytesPerPixel];
    unsigned char Imagedata2[Size_r][Size_c][BytesPerPixel];
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open original file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata1, sizeof(unsigned char), Size_r * Size_c * BytesPerPixel, file);
    fclose(file);
    if (!(file = fopen(argv[2], "rb"))) {
        cout << "Cannot open filtered file: " << argv[2] << endl;
        exit(1);
    }
    fread(Imagedata2, sizeof(unsigned char), Size_r * Size_c * BytesPerPixel, file);
    fclose(file);
    double value[3]={};
    for(int i=0;i<Size_r;i++)
    {
        for(int j=0;j<Size_c;j++)
        {
            value[0]=value[0]+pow((Imagedata1[i][j][0]-Imagedata2[i][j][0]),2);
            value[1]=value[1]+pow((Imagedata1[i][j][1]-Imagedata2[i][j][1]),2);
            value[2]=value[2]+pow((Imagedata1[i][j][2]-Imagedata2[i][j][2]),2);
        }
    }
    value[0]=value[0]/(Size_r * Size_c);
    value[1]=value[1]/(Size_r * Size_c);
    value[2]=value[2]/(Size_r * Size_c);
    float psnr[3]={};
    psnr[0]=10*log10(MAX/value[0]);
    psnr[1]=10*log10(MAX/value[1]);
    psnr[2]=10*log10(MAX/value[2]);
    float avg=(psnr[0]+psnr[1]+psnr[2])/3;
    cout<<"psnr of red channel is:"<<psnr[0]<<endl;
    cout<<"psnr of green channel is:"<<psnr[1]<<endl;
    cout<<"psnr of blue channel is:"<<psnr[2]<<endl;
    cout<<"psnr of avg channel is:"<<avg<<endl;
    return 0;
}

