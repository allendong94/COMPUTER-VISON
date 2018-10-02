#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
//Boat.raw output.raw 321 481
int main(int argc, char *argv[])

{
    cout<<"readraw IO is working"<<endl;
    // Define file pointer and variables

    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    FILE *file;int size_r = atoi(argv[4]);int size_c = atoi(argv[3]);int x=(3/2);
    // Allocate image data array
    unsigned char Imagedata[size_r][size_c][3];int Image_x[size_r][size_c];int Image_y[size_r][size_c];
    unsigned char Imagegray[size_r][size_c];int Imageedge[size_r][size_c];
    int Imagedataresizer[size_r + 2 * x][size_c];
    int Imagedataresize[size_r + 2 * x][size_c + 2 * x];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r*size_c*3, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    for(int i=0;i<size_r;i++)
    {
        for (int j = 0; j < size_c; j++)
        {
            unsigned char value_lum=0.21*Imagedata[i][j][0]+0.72*Imagedata[i][j][1]+0.07*Imagedata[i][j][2];
            //unsigned char value_lum=(Imagedata[i][j][0]+Imagedata[i][j][1]+Imagedata[i][j][2])/3;
            Imagegray[i][j]=value_lum;

        }
    }

    int sobel_x[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};int sobel_y[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    //extension

    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < size_c; jj++) {
            Imagedataresizer[ii][jj] = (int) Imagegray[0][jj];

        }
    }
    for (int ii = 0; ii < size_r; ii++) {
        for (int jj = 0; jj < size_c; jj++) {
            Imagedataresizer[ii + x][jj] =(int)  Imagegray[ii][jj];

        }
    }
    for (int ii = 0; ii < x; ii++) {
        for (int jj = 0; jj < size_c; jj++) {
            Imagedataresizer[ii + size_r + x][jj] =(int) Imagegray[size_r - 1][jj];

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
     for(int i=x;i<x+size_r;i++)
    {
      for(int j=x;j<x+size_c;j++)
      {
       Image_x[i-x][j-x]=(sobel_x[0][0]*Imagedataresize[i-1][j-1]+sobel_x[0][1]*Imagedataresize[i-1][j]+sobel_x[0][2]*Imagedataresize[i-1][j+1]
                         +sobel_x[1][0]*Imagedataresize[i][j-1]+sobel_x[1][1]*Imagedataresize[i][j]+sobel_x[1][2]*Imagedataresize[i][j+1]
                         +sobel_x[2][0]*Imagedataresize[i+1][j-1]+sobel_x[2][1]*Imagedataresize[i+1][j]+sobel_x[2][2]*Imagedataresize[i+1][j+1]);
       Image_y[i-x][j-x]=(sobel_y[0][0]*Imagedataresize[i-1][j-1]+sobel_y[0][1]*Imagedataresize[i-1][j]+sobel_y[0][2]*Imagedataresize[i-1][j+1]
                         +sobel_y[1][0]*Imagedataresize[i][j-1]+sobel_y[1][1]*Imagedataresize[i][j]+sobel_y[1][2]*Imagedataresize[i][j+1]
                         +sobel_y[2][0]*Imagedataresize[i+1][j-1]+sobel_y[2][1]*Imagedataresize[i+1][j]+sobel_y[2][2]*Imagedataresize[i+1][j+1]);
      }
    }
    int max_x=-255;int max_y=-255;int min_x=255;int min_y=255;
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            if(Image_x[i][j]>max_x)
            {max_x=Image_x[i][j];}
            if(Image_y[i][j]>max_y)
            {max_y=Image_y[i][j];}
            if(Image_x[i][j]<min_x)
            {min_x=Image_x[i][j];}
            if(Image_y[i][j]<min_y)
            {min_y=Image_y[i][j];}
        }
    }

    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            Imageedge[i][j]=pow((pow(Image_x[i][j],2)+ pow(Image_y[i][j],2)),0.5);
            //Imageedge[i][j]=Image_y[i][j];
        }
    }
    int max=-255,min=255;
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            if(Imageedge[i][j]>max)
            {max=Imageedge[i][j];}
            if(Imageedge[i][j]<min)
            {min=Imageedge[i][j];}
        }
    }
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            Imageedge[i][j]=255*(Imageedge[i][j]-min)/(max-min);

        }
    }
/*
    int nms_size=1;
    for(int i=0;i<size_r;i+=nms_size)
    {
        for(int j=0;j<size_c;j+=nms_size)
        {
            int max_val=0;
            for(int m=0;m<nms_size;m++)
            {

                    if (i + m < size_r && j + m < size_c)
                    {
                        if (Imageedge[i ][j + m] > max_val) { max_val =Imageedge[i ][j + m]; }
                        if (Imageedge[i +m][j ] > max_val) { max_val=Imageedge[i+m ][j]; }
                        if (Imageedge[i +m][j +m] > max_val) { max_val=Imageedge[i+m ][j+m]; }
                    }


            }
            for(int m=0;m<nms_size;m++)
            {

                    if (i + m < size_r && j + m < size_c)
                    {
                        if (Imageedge[i][j + m] < max_val) { Imageedge[i][j + m] = 0; }
                        if (Imageedge[i+m][j ] < max_val) { Imageedge[i+m][j ] = 0; }
                        if (Imageedge[i+m][j + m] < max_val) { Imageedge[i+m][j+m ] = 0; }
                    }

            }
        }
    }
*/

    int histogram[256]={};
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            histogram[Imageedge[i][j]]+=1;
        }
    }
    int gray_value=0;
    int ii=-1;
    int thr=0;
    int pixel_num=(size_r*size_c*9.0)/10;

    while(thr==0)
    {
        if(gray_value>=pixel_num)
        {thr=ii;}
        else
        {
            ii+=1;
            gray_value+=histogram[ii];
        }
    }

    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            if( Imageedge[i][j]>=thr)
            {Imageedge[i][j]=0;}
            else
            {Imageedge[i][j]=255;}

        }
    }

    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            Imagegray[i][j]=(unsigned char)Imageedge[i][j];
        }

    }


    /////////////////////////end my code/////////
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(Imagegray, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);
     return 0;
}


