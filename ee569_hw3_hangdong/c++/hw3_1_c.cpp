#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int main(int argc, char *argv[])
{
    cout << "readraw IO is working" << endl;
    FILE *file;
    int size_r=atoi(argv[4]), size_c=atoi(argv[3]);
    int BytesPerPixel = 1;int window=45;
    // Allocate image data array
    unsigned char Imagedata[size_r][size_c];
    unsigned char out[size_r][size_c];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r * size_c * BytesPerPixel, file);
    fclose(file);
    int half_win=window/2;
    for(int i=0;i<size_r-window;i++)
    {
        for(int j=0;j<size_c-window;j++)
        {
            int value=0;int histogram[256]={};int max=0;
           for(int n=0;n<window;n++)
           {
               for(int m=0;m<window;m++)
               {
                   histogram[Imagedata[i+n][j+m]]+=1;
               }
           }
           for(int k=0;k<256;k++)
           {
               if(histogram[k]>max){max=histogram[k];value=k;}
           }
            out[i][j]=value;
            /*
            for(int n=0;n<window;n++)
            {
                for(int m=0;m<window;m++)
                {
                    out[i+n][j+m]=out[i][j];
                }
            }
             */
        }
    }

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(out, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);
    return 0;
}

