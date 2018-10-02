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
    FILE *file;int size_r = atoi(argv[4]);int size_c = atoi(argv[3]);int x=(5/2);
    // Allocate image data array
    unsigned char Imagedata[size_r][size_c][3];int Image_temp[size_r][size_c];int Image_temp2[size_r][size_c];
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

    //int sobel_x[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};int sobel_y[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    //extension
    //int log_3[3][3]={{1,2,1},{2,4,2},{1,2,1}};int v_3=16;
    int log_5[5][5]={{0,0,-1,0,0},{0,-1,-2,-1,0},{-1,-2,16,-2,-1},{0,-1,-2,-1,0},{0,0,-1,0,0}};int v_5=273;

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
            Imageedge[i-x][j-x]=(log_5[0][0]*Imagedataresize[i-2][j-2]+log_5[0][1]*Imagedataresize[i-2][j-1]+log_5[0][2]*Imagedataresize[i-2][j]+log_5[0][3]*Imagedataresize[i-2][j+1]+log_5[0][4]*Imagedataresize[i-2][j+2]
            +log_5[1][0]*Imagedataresize[i-1][j-2]+log_5[1][1]*Imagedataresize[i-1][j-1]+log_5[1][2]*Imagedataresize[i-1][j]+log_5[1][3]*Imagedataresize[i-1][j+1]+log_5[1][4]*Imagedataresize[i-1][j+2]
            +log_5[2][0]*Imagedataresize[i][j-2]+log_5[2][1]*Imagedataresize[i][j-1]+log_5[2][2]*Imagedataresize[i][j]+log_5[2][3]*Imagedataresize[i][j+1]+log_5[2][4]*Imagedataresize[i][j+2]
            +log_5[3][0]*Imagedataresize[i+1][j-2]+log_5[3][1]*Imagedataresize[i+1][j-1]+log_5[3][2]*Imagedataresize[i+1][j]+log_5[3][3]*Imagedataresize[i+1][j+1]+log_5[3][4]*Imagedataresize[i+1][j+2]
            +log_5[4][0]*Imagedataresize[i+2][j-2]+log_5[4][1]*Imagedataresize[i+2][j-1]+log_5[4][2]*Imagedataresize[i+2][j]+log_5[4][3]*Imagedataresize[i+2][j+1]+log_5[4][4]*Imagedataresize[i+2][j+2]);
        }
    }
    int max=0,min=255;
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

      for(int i=0;i<size_r;i++)
      {
          for(int j=0;j<size_c;j++)
          {

              Image_temp[i][j]=255*(abs(Imageedge[i][j])-0)/(max-0);

          }
      }

/*
      int nms_size=2;
      for(int i=0;i<size_r;i+=nms_size)
      {
          for(int j=0;j<size_c;j+=nms_size)
          {
              int max_valy=0;int max_valx=0;
              for(int m=0;m<nms_size;m++)
              {

                      if (i + m < size_r && j + m < size_c)
                      {
                          if (Imageedge[i ][j + m] > max_valy) { max_valy =Imageedge[i ][j + m]; }
                          if (Imageedge[i +m][j ] > max_valx) { max_valx =Imageedge[i+m ][j]; }
                      }


              }
              for(int m=0;m<nms_size;m++)
              {

                      if (i + m < size_r && j + m < size_c)
                      {
                          if (Imageedge[i][j + m] < max_valy) { Imageedge[i][j + m] = 0; }
                          if (Imageedge[i+m][j + m] < max_valx) { Imageedge[i+m][j ] = 0; }
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
            histogram[Image_temp[i][j]]+=1;
        }
    }
    int gray_value=0;
    int ii=-1;
    int thr=0;
    int pixel_num=(size_r*size_c*9)/10;

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

    thr=((float)thr/255.0)*(max-0)+0;
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            if( Imageedge[i][j]>=thr)
            {Image_temp2[i][j]=1;}
            if( Imageedge[i][j]<=-1*thr)
            {Image_temp2[i][j]=-1;}
            if( Imageedge[i][j]<thr&&Imageedge[i][j]>(-thr))
            {Image_temp2[i][j]=0;}
        }
    }

    for(int i=1;i<size_r-1;i++)
    {
        for(int j=1;j<size_c-1;j++)
        {
            if(Image_temp2[i][j]==0)
            {
                if ((Image_temp2[i][j-1]*Image_temp2[i][j+1] <0)||(Image_temp2[i+1][j]*Image_temp2[i-1][j] <0)||(Image_temp2[i-1][j-1]*Image_temp2[i+1][j+1] <0)||(Image_temp2[i-1][j+1]*Image_temp2[i+1][j-1] <0)) { Image_temp2[i][j] = 0; }
                else { Image_temp2[i][j] = 255; }
            }
        }
    }

    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            Imagegray[i][j]=(unsigned char)Image_temp2[i][j];
        }

    }
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            if(Imagegray[i][j]<128){Imagegray[i][j]=0;}
            else{Imagegray[i][j]=255;}
        }

    }

    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            //if(Imagegray[i][j]==0&&Imagegray[i][j-1]==0)
           // {Imagegray[i][j-1]=255;}
            if(Imagegray[i][j]==0&&Imagegray[i-1][j-1]==0)
            {Imagegray[i-1][j]=255;}
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



