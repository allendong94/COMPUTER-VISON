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
    int size=Size_r*Size_c;
    int M=8;//Values of each channels
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
    int col_map[Size_r][Size_c][BytesPerPixel];
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
    fout.close();c
     */
    int m_r=0,m_g=0,m_b=0;//int row[Size_r*Size_c][3];int column[Size_r*Size_c][3];
    //int row[size][3];int column[size][3];
    //int** a = (int**)malloc(sizeof(int)*size*3);
    //int* a = (int*)malloc(sizeof(int)*size*3);
    int* row=(int*)malloc(sizeof(int)*size*3);
    int* column=(int*)malloc(sizeof(int)*size*3);
    /*
    for(int i=0;i<Size_r*Size_c;i++)
    {
        for(int j=0;j<3;j++)
        {
            row[i][j]=0;column[i][j]=0;
        }
    }
     */
    for(int color=0;color<256;color++)
    {
        for(int i=0;i<Size_r;i++)
        {
            for(int j=0;j<Size_c;j++)
            {
                if(int(Imagedata[i][j][0])==color)
                {
                    *(row+m_r*3+0)=i;
                    *(column+m_r*3+0)=j;
                    //row[m_r][0]=i;
                    //column[m_r][0]=j;
                    m_r+=1;
                }
                if(int(Imagedata[i][j][1])==color)
                {
                    *(row+m_g*3+1)=i;
                    *(column+m_g*3+1)=j;
                    //row[m_g][1]=i;
                    //column[m_g][1]=j;
                    m_g+=1;
                }
                if(int(Imagedata[i][j][2])==color)
                {
                    *(row+m_b*3+2)=i;
                    *(column+m_b*3+2)=j;
                    //row[m_b][2]=i;
                    //column[m_b][2]=j;
                    m_b+=1;
                }
            }
        }
    }
    int c_r[M];int c_g[M];int c_b[M];
    for(int t=0;t<M;t++)
    {
        c_r[t]=0;c_g[t]=0;c_b[t]=0;
    }
    for(int i=0;i<M;i++)//变量
    {
        for(int j=0+(Size_r*Size_c/M)*i;j<(Size_r*Size_c/M)+(Size_r*Size_c/M)*i;j++)
        {
            c_r[i]=c_r[i]+int(Imagedata[*(row+j*3+0)][*(column+j*3+0)][0]);
            c_g[i]=c_g[i]+int(Imagedata[*(row+j*3+1)][*(column+j*3+1)][1]);
            c_b[i]=c_b[i]+int(Imagedata[*(row+j*3+2)][*(column+j*3+2)][2]);
        }
        c_r[i]=c_r[i]/((Size_r*Size_c)/M);
        c_g[i]=c_g[i]/((Size_r*Size_c)/M);
        c_b[i]=c_b[i]/((Size_r*Size_c)/M);
        for(int j=0+(Size_r*Size_c/M)*i;j<(Size_r*Size_c/M)+(Size_r*Size_c/M)*i;j++)
        {
            Imagedata[*(row+j*3+0)][*(column+j*3+0)][0]=c_r[i];col_map[*(row+j*3+0)][*(column+j*3+0)][0]=i;
            Imagedata[*(row+j*3+1)][*(column+j*3+1)][1]=c_g[i];col_map[*(row+j*3+1)][*(column+j*3+1)][1]=i;
            Imagedata[*(row+j*3+2)][*(column+j*3+2)][2]=c_b[i];col_map[*(row+j*3+2)][*(column+j*3+2)][2]=i;
        }
    }
    free(row);
    free(column);
    /////////////////////////FINISH MY CODE////////////////////////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Size_r*Size_c*BytesPerPixel, file);
    fclose(file);
    return 0;
}



