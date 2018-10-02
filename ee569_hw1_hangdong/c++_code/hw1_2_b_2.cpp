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
    int Size_r =338;
    int Size_c =600;
    int size=Size_r*Size_c;
    int matrix_size=9;//matrix的参数应该为变量
    int M=4;//Values of each channels
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
    int  col_map[Size_r][Size_c][BytesPerPixel];
    int* row=(int*)malloc(sizeof(int)*size*3);
    int* column=(int*)malloc(sizeof(int)*size*3);
    int x=floor((float)matrix_size/2);

    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Size_r * Size_c * BytesPerPixel, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    int m_r=0,m_g=0,m_b=0;//int row[Size_r*Size_c][3];int column[Size_r*Size_c][3];
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

    unsigned char Imagedataresizer[Size_r+2*x][Size_c][BytesPerPixel];
    unsigned char Imagedataresize[Size_r+2*x][Size_c+2*x][BytesPerPixel];
    //extension
    for(int ii=0;ii<x;ii++)
    {
        for(int jj=0;jj<Size_c;jj++)
        {
            Imagedataresizer[ii][jj][0]=(unsigned char)col_map[0][jj][0];
            Imagedataresizer[ii][jj][1]=(unsigned char)col_map[0][jj][1];
            Imagedataresizer[ii][jj][2]=(unsigned char)col_map[0][jj][2];
        }
    }
    for(int ii=0;ii<Size_r;ii++)
    {
        for(int jj=0;jj<Size_c;jj++)
        {
            Imagedataresizer[ii+x][jj][0]=(unsigned char)col_map[ii][jj][0];
            Imagedataresizer[ii+x][jj][1]=(unsigned char)col_map[ii][jj][1];
            Imagedataresizer[ii+x][jj][2]=(unsigned char)col_map[ii][jj][2];
        }
    }
    for(int ii=0;ii<x;ii++)
    {
        for(int jj=0;jj<Size_c;jj++)
        {
            Imagedataresizer[ii+Size_r+x][jj][0]=(unsigned char)col_map[Size_r-1][jj][0];
            Imagedataresizer[ii+Size_r+x][jj][1]=(unsigned char)col_map[Size_r-1][jj][1];
            Imagedataresizer[ii+Size_r+x][jj][2]=(unsigned char)col_map[Size_r-1][jj][2];
        }
    }
    //new img
    for(int ii=0;ii<x;ii++)
    {
        for(int jj=0;jj<Size_r+2*x;jj++)
        {
            Imagedataresize[jj][ii][0]=Imagedataresizer[jj][0][0];
            Imagedataresize[jj][ii][1]=Imagedataresizer[jj][0][1];
            Imagedataresize[jj][ii][2]=Imagedataresizer[jj][0][2];
        }
    }
    for(int ii=0;ii<Size_c;ii++)
    {
        for(int jj=0;jj<Size_r+2*x;jj++)
        {
            Imagedataresize[jj][ii+x][0]=Imagedataresizer[jj][ii][0];
            Imagedataresize[jj][ii+x][1]=Imagedataresizer[jj][ii][1];
            Imagedataresize[jj][ii+x][2]=Imagedataresizer[jj][ii][2];
        }
    }
    for(int ii=0;ii<x;ii++)
    {
        for(int jj=0;jj<Size_r+2*x;jj++)
        {
            Imagedataresize[jj][ii+Size_c+x][0]=Imagedataresizer[jj][Size_c-1][0];
            Imagedataresize[jj][ii+Size_c+x][1]=Imagedataresizer[jj][Size_c-1][1];
            Imagedataresize[jj][ii+Size_c+x][2]=Imagedataresizer[jj][Size_c-1][2];
        }
    }
//start build up oil
    for(int n=0;n<3;n++)
    {
        for (int i = 0; i < Size_r; i++)
        {
            for (int j = 0; j < Size_c; j++)
            {

                output[i][j][n]=Imagedata[i][j][n];
            }
        }
    }
    for(int i=0;i<Size_r-2;i++)
    {
        for(int j=0;j<Size_c-2;j++)
        {
            int col_plate[M][M][M];
            for(int r=0;r<M;r++)
            {
                for (int g = 0; g < M; g++)
                {
                    for (int b = 0; b < M; b++)
                    {
                        col_plate[r][g][b] = 0;
                    }
                }
            }
            for(int m=0;m<matrix_size;m++)
            {
                for(int n=0;n<matrix_size;n++)
                {
                    int r_index=(int)Imagedataresize[i+m][j+n][0];
                    int g_index=(int)Imagedataresize[i+m][j+n][1];
                    int b_index=(int)Imagedataresize[i+m][j+n][2];
                    //int r_index=col_map[i+m][j+n][0];
                    //int g_index=col_map[i+m][j+n][1];
                    //int b_index=col_map[i+m][j+n][2];
                    col_plate[r_index][g_index][b_index]+=1;//将3通道数据组合存入col_plate数组
                }
            }
            int max=col_plate[0][0][0];int r_out=0,g_out=0,b_out=0;
            for(int r=0;r<M;r++) {
                for(int g=0;g<M;g++) {
                    for(int b=0;b<M;b++) {
                        if(max<col_plate[r][g][b]) {
                            max=col_plate[r][g][b];
                            r_out=r;
                            g_out=g;
                            b_out=b;
                        }
                    }
                }
            }
            int pixel=floor(matrix_size/2);
            output[i+pixel][j+pixel][0]=(unsigned char)c_r[r_out];
            output[i+pixel][j+pixel][1]=(unsigned char)c_g[g_out];
            output[i+pixel][j+pixel][2]=(unsigned char)c_b[b_out];
        }
    }
    /////////////////////////FINISH MY CODE////////////////////////////////////////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), (Size_r)*(Size_c)*BytesPerPixel, file);
    fclose(file);
    return 0;
}

