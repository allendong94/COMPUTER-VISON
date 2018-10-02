#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
unsigned char Imagedata[700][700][3];
unsigned char New[700][700][3];
float te_err[700][700][3];
char key;
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
    //float te_err[size_r][size_c][BytesPerPixel];
    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    fclose(file);
    float error;int count=0;
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //Minimal Brightness Variation Quadruples

    for(int i=0;i<size_r;i++)
    {
        for (int j = 0; j < size_c; j++)
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                te_err[i][j][k]=1-((float)Imagedata[i][j][k])/255.0;
            }
        }
    }

    for(int i=0;i<size_r;i++)
    {


            for (int j = 0; j < size_c; j++)
            {
                /*
                /////////////////////////////////
                if(Imagedata[i][j][0]+Imagedata[i][j][1]>255)
                {
                    if(Imagedata[i][j][2]+Imagedata[i][j][1]>255)
                    {
                        if(Imagedata[i][j][2]+Imagedata[i][j][1]+Imagedata[i][j][0]>510)
                        {
                            key[i][j]=0;//cmyw
                        }
                        else
                        {
                            key[i][j]=1;//mygc
                        }
                    }
                    else
                    {
                        key[i][j]=2;//rgmy
                    }
                }
                else
                {
                    if(Imagedata[i][j][2]+Imagedata[i][j][1]<=255)
                    {
                        if(Imagedata[i][j][2]+Imagedata[i][j][1]+Imagedata[i][j][0]<=255)
                        {
                            key[i][j]=3;//krgb
                        }
                        else
                        {
                            key[i][j]=4;//rgbm
                        }
                    }
                    else
                    {
                        key[i][j]=5;//cmgb
                    }
                }
                */
                /////////////////////////////////
                float d_c=pow((te_err[i][j][0]-1),2)+pow((te_err[i][j][1]),2)+pow((te_err[i][j][2]),2);
                float d_m=pow((te_err[i][j][0]),2)+pow((te_err[i][j][1]-1),2)+pow((te_err[i][j][2]),2);
                float d_b=pow((te_err[i][j][0]-1),2)+pow((te_err[i][j][1]-1),2)+pow((te_err[i][j][2]),2);
                float d_g=pow((te_err[i][j][0]-1),2)+pow((te_err[i][j][1]),2)+pow((te_err[i][j][2]-1),2);
                float d_r=pow((te_err[i][j][0]),2)+pow((te_err[i][j][1]-1),2)+pow((te_err[i][j][2]-1),2);
                float d_y=pow((te_err[i][j][0]),2)+pow((te_err[i][j][1]),2)+pow((te_err[i][j][2]-1),2);
                float d_w=pow((te_err[i][j][0]),2)+pow((te_err[i][j][1]),2)+pow((te_err[i][j][2]),2);
                float d_k=pow((te_err[i][j][0]-1),2)+pow((te_err[i][j][1]-1),2)+pow((te_err[i][j][2]-1),2);
                if(d_c<min(d_m,min(d_b,min(d_g,min(d_r,min(d_y,min(d_w,d_k)))))))
                {key='C';}
                else if(d_m<min(d_c,min(d_b,min(d_g,min(d_r,min(d_y,min(d_w,d_k)))))))
                {key='M';}
                else if(d_y<min(d_m,min(d_b,min(d_g,min(d_r,min(d_c,min(d_w,d_k)))))))
                {key='Y';}
                else if(d_g<min(d_m,min(d_b,min(d_c,min(d_r,min(d_y,min(d_w,d_k)))))))
                {key='G';}
                else if(d_r<min(d_m,min(d_b,min(d_g,min(d_c,min(d_y,min(d_w,d_k)))))))
                {key='R';}
                else if(d_b<min(d_m,min(d_c,min(d_g,min(d_r,min(d_y,min(d_w,d_k)))))))
                {key='B';}
                else if(d_k<min(d_m,min(d_b,min(d_g,min(d_r,min(d_y,min(d_w,d_c)))))))
                {key='K';}
                else if(d_w<min(d_m,min(d_b,min(d_g,min(d_r,min(d_y,min(d_c,d_k)))))))
                {key='W';}
               switch(key)
               {
                   case'C':{
                       New[i][j][0]=255;New[i][j][1]=0;New[i][j][2]=0;
                       break;
                   }
                   case'M':{
                       New[i][j][0]=0;New[i][j][1]=255;New[i][j][2]=0;
                       break;
                   }
                   case'Y':{
                       New[i][j][0]=0;New[i][j][1]=0;New[i][j][2]=255;
                       break;
                   }
                   case'G':{
                       New[i][j][0]=255;New[i][j][1]=0;New[i][j][2]=255;
                       break;
                   }
                   case'R':{
                       New[i][j][0]=0;New[i][j][1]=255;New[i][j][2]=255;
                       break;
                   }
                   case'B':{
                       New[i][j][0]=255;New[i][j][1]=255;New[i][j][2]=0;
                       break;
                   }
                   case'K':{
                       New[i][j][0]=255;New[i][j][1]=255;New[i][j][2]=255;
                       break;
                   }
                   case'W':{
                       New[i][j][0]=0;New[i][j][1]=0;New[i][j][2]=0;
                       break;
                   }
               }
                /////////////////////////////////
                    //Floyd method
                for(int k=0;k<BytesPerPixel;k++)
                {
                    error=te_err[i][j+1][k]-(((float)New[i][j][k])/255.0);
                    if (j+1<size_c){te_err[i][j+1][k]=te_err[i][j+1][k]+error*7/16;}
                    if (j-1>=0&&i+1<size_r){te_err[i+1][j-1][k]=te_err[i+1][j-1][k]+error*3/16;}
                    if (i+1<size_r){te_err[i+1][j][k]=te_err[i+1][j][k]+error*5/16;}
                    if (i+1<size_r&&j+1<size_c){te_err[i+1][j+1][k]=te_err[i+1][j+1][k]+error*1/16;}
                }

            }
    }

    for(int i=0;i<size_r;i++)
    {
        for (int j = 0; j < size_c; j++)
        {
            for(int k=0;k<BytesPerPixel;k++)
            {
                New[i][j][k]=255-New[i][j][k];
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

