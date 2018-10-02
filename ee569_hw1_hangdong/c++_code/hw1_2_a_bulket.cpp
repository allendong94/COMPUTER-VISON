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
    int Size_r =338;
    int Size_c =600;
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
    int m_r=0,m_g=0,m_b=0;//int row[Size_r*Size_c][3];int column[Size_r*Size_c][3];
    int row[Size_r*Size_c][3];int column[Size_r*Size_c][3];
    for(int i=0;i<Size_r*Size_c;i++)
    {
        for(int j=0;j<3;j++)
        {
            row[i][j]=0;column[i][j]=0;
        }
    }
    for(int color=0;color<256;color++)
    {
        for(int i=0;i<Size_r;i++)
        {
            for(int j=0;j<Size_c;j++)
            {
                if(int(Imagedata[i][j][0])==color)
                {
                    row[m_r][0]=i;
                    column[m_r][0]=j;
                    m_r+=1;
                }
                if(int(Imagedata[i][j][1])==color)
                {
                    row[m_g][1]=i;
                    column[m_g][1]=j;
                    m_g+=1;
                }
                if(int(Imagedata[i][j][2])==color)
                {
                    row[m_b][2]=i;
                    column[m_b][2]=j;
                    m_b+=1;
                }
            }
        }
    }
    int c=ceil(3.0/2.0);
    int bulket=ceil(float(Size_r*Size_c)/float(256));
    for (int m=0;m<256;m++)
    {
        for(int n=0+m*bulket;n<bulket+m*bulket;n++)
        {
            if(n<Size_r*Size_c)
            {
                Imagedata[row[n][0]][column[n][0]][0]=m;
                Imagedata[row[n][1]][column[n][1]][1]=m;
                Imagedata[row[n][2]][column[n][2]][2]=m;
            }
            else
            {break;}
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

