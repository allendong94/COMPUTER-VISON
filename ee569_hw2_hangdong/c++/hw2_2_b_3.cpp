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
    unsigned char New2[size_r][size_c][BytesPerPixel];
    double te_err[size_r][size_c][BytesPerPixel];
    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    fclose(file);
    double error;int count=0;
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    for(int i=0;i<size_r;i++)
    {
        for (int j = 0; j < size_c; j++)
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                te_err[i][j][k]=((double)Imagedata[i][j][k])/255;
            }
        }
    }
    for(int i=0;i<size_r;i++)
    {

        count=count+1;
        if(count%2==1)
        {
            for (int j = 0; j < size_c; j++) {
                for (int k = 0; k < BytesPerPixel; k++) {
                    //Stucki method
                    if (te_err[i][j][k]<0.5) {
                        error = te_err[i][j][k]-0;
                        New2[i][j][k] = (unsigned char) 0;
                    }
                    else {
                        error = te_err[i][j][k]-1;
                        New2[i][j][k] = (unsigned char) 255;
                    }
                    if (j+1<size_c){te_err[i][j+1][k]=te_err[i][j+1][k]+error*8/42;}
                    if (j+2<size_c){te_err[i][j+2][k]=te_err[i][j+2][k]+error*4/42;}
                    if (j-2>=0&&i+1<size_r){te_err[i+1][j-2][k]=te_err[i+1][j-2][k]+error*2/42;}
                    if (j-1>=0&&i+1<size_r){te_err[i+1][j-1][k]=te_err[i+1][j-1][k]+error*4/42;}
                    if (i+1<size_r){te_err[i+1][j][k]=te_err[i+1][j][k]+error*8/42;}
                    if (j+1<size_c&&i+1<size_r){te_err[i+1][j+1][k]=te_err[i+1][j+1][k]+error*4/42;}
                    if (j+2<size_c&&i+1<size_r){te_err[i+1][j+2][k]=te_err[i+1][j+2][k]+error*2/42;}
                    if (j+1<size_c&&i+2<size_r){te_err[i+2][j+1][k]=te_err[i+2][j+1][k]+error*2/42;}
                    if (j+2<size_c&&i+2<size_r){te_err[i+2][j+2][k]=te_err[i+2][j+2][k]+error*1/42;}
                    if (i+2<size_r){te_err[i+2][j][k]=te_err[i+2][j][k]+error*4/42;}
                    if ((j-1>=0)&&(i+2<size_r)){te_err[i+2][j-1][k]=te_err[i+2][j-1][k]+error*2/42;}
                    if ((j-2>=0)&&(i+2<size_r)){te_err[i+2][j-2][k]=te_err[i+2][j-2][k]+error*1/42;}
                }
            }
        }
        else
        {
            for (int j = 0; j < size_c; j++) {
                for (int k = 0; k < BytesPerPixel; k++) {
                    //Stucki method
                    if (te_err[i][j][k]<0.5) {
                        error = te_err[i][j][k]-0;
                        New2[i][j][k] = (unsigned char) 0;
                    }
                    else {
                        error = te_err[i][j][k]-1;
                        New2[i][j][k] = (unsigned char) 255;
                    }
                    if (j+1<size_c){te_err[i][j+1][k]=te_err[i][j+1][k]+error*8/42;}
                    if (j+2<size_c){te_err[i][j+2][k]=te_err[i][j+2][k]+error*4/42;}
                    if (j-2>=0&&i+1<size_r){te_err[i+1][j-2][k]=te_err[i+1][j-2][k]+error*2/42;}
                    if (j-1>=0&&i+1<size_r){te_err[i+1][j-1][k]=te_err[i+1][j-1][k]+error*4/42;}
                    if (i+1<size_r){te_err[i+1][j][k]=te_err[i+1][j][k]+error*8/42;}
                    if (j+1<size_c&&i+1<size_r){te_err[i+1][j+1][k]=te_err[i+1][j+1][k]+error*4/42;}
                    if (j+2<size_c&&i+1<size_r){te_err[i+1][j+2][k]=te_err[i+1][j+2][k]+error*2/42;}
                    if (j+1<size_c&&i+2<size_r){te_err[i+2][j+1][k]=te_err[i+2][j+1][k]+error*2/42;}
                    if (j+2<size_c&&i+2<size_r){te_err[i+2][j+2][k]=te_err[i+2][j+2][k]+error*1/42;}
                    if (i+2<size_r){te_err[i+2][j][k]=te_err[i+2][j][k]+error*4/42;}
                    if ((j-1>=0)&&(i+2<size_r)){te_err[i+2][j-1][k]=te_err[i+2][j-1][k]+error*2/42;}
                    if ((j-2>=0)&&(i+2<size_r)){te_err[i+2][j-2][k]=te_err[i+2][j-2][k]+error*1/42;}
                }
            }
        }
    }

    ///////////////////////// END /////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(New2, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    fclose(file);
    return 0;
}