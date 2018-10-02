#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
unsigned char Imagedata[700][700][3];
unsigned char New[700][700][3];
double te_err[700][700][3];
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
    //unsigned char Imagedata[size_r][size_c][BytesPerPixel];
    //unsigned char New[size_r][size_c][BytesPerPixel];
    //double te_err[size_r][size_c][BytesPerPixel];
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
    for(int i=0;i<size_r-1;i++)
    {

        count=count+1;
        if(count%2==1)
        {
            for (int j = 0; j < size_c-1; j++) {
                for (int k = 0; k < BytesPerPixel; k++) {
                    if (te_err[i][j][k] < 0.5) {
                        New[i][j][k] =(unsigned) 0;error =  te_err[i][j][k]-0 ;
                    } else {
                        New[i][j][k] =(unsigned) 255;error =  te_err[i][j][k]-1;
                    }
                    //Floyd method

                    {te_err[i][j+1][k]=te_err[i][j+1][k]+error*7/16;}

                    {te_err[i+1][j-1][k]=te_err[i+1][j-1][k]+error*3/16;}

                    {te_err[i+1][j][k]=te_err[i+1][j][k]+error*5/16;}

                    {te_err[i+1][j+1][k]=te_err[i+1][j+1][k]+error*1/16;}
                }
            }
        }

        else
        {
            for (int j = 0; j < size_c-1; j++) {
                for (int k = 0; k < BytesPerPixel; k++) {
                    if (te_err[i][j][k] < 0.5) {
                        New[i][j][k] =(unsigned) 0;error =  te_err[i][j][k]-0 ;
                    } else {
                        New[i][j][k] =(unsigned) 255;error =  te_err[i][j][k]-1;
                    }

                    {te_err[i][j+1][k]=te_err[i][j+1][k]+error*7/16;}

                    {te_err[i+1][j-1][k]=te_err[i+1][j-1][k]+error*3/16;}

                    {te_err[i+1][j][k]=te_err[i+1][j][k]+error*5/16;}

                    {te_err[i+1][j+1][k]=te_err[i+1][j+1][k]+error*1/16;}
                }
            }
        }
    }

    ///////////////////////// END /////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(New, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    fclose(file);
    return 0;
}