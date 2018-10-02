// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

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
	int BytesPerPixel;
	int Size = 512;
    int resize=650;
	int Size_r = 480;
	int Size_c = 854;
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
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	// Allocate image data array
	unsigned char Imagedata[Size_r][Size_c][BytesPerPixel];
    //int Imagedata[Size][Size][BytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size_r*Size_c*BytesPerPixel, file);
	fclose(file);
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	// Write image data (filename specified by second argument) from image data matrix
	//unsigned char r[Size][Size];unsigned char g[Size][Size];unsigned char b[Size][Size];
    /*
    //question1
	//1(lightness)
    for(int i=0;i<Size;i++)
	{
		for (int j = 0; j < Size; j++)
		{
			unsigned char value_max=max(max(Imagedata[i][j][1],Imagedata[i][j][2]),Imagedata[i][j][3]);
			unsigned char value_min=min(min(Imagedata[i][j][1],Imagedata[i][j][2]),Imagedata[i][j][3]);
         Imagedata[i][j][1]=Imagedata[i][j][2]=Imagedata[i][j][3]=(value_max+value_min)/2;
		}
	}
	//end 1
    */
    /*
	//2(average)
	for(int i=0;i<Size;i++)
	{
		for (int j = 0; j < Size; j++)
		{
	     Imagedata[i][j][0]=Imagedata[i][j][1]=Imagedata[i][j][2]=(Imagedata[i][j][1]+Imagedata[i][j][2]+Imagedata[i][j][0])/3;
		}
	}
	//end 2
    */
    //0.21 R + 0.72 G + 0.07B
    //[0]红色R；[1]绿色G；[2]蓝色B；
    /*
    //3(luminosity)
    for(int i=0;i<Size;i++)
    {
        for (int j = 0; j < Size; j++)
        {
            unsigned char value_lum=0.21*Imagedata[i][j][0]+0.72*Imagedata[i][j][1]+0.07*Imagedata[i][j][2];
            Imagedata[i][j][0]=value_lum;
            Imagedata[i][j][1]=value_lum;
            Imagedata[i][j][2]=value_lum;
        }
    }
    //end  3
     */

    //question 2 cmy
    //c=1-r;m=1-g;y=1-b
    unsigned char Imagedata_CMY[Size_r][Size_c][3];
    for(int i=0;i<Size_r;i++)
    {
        for (int j = 0; j < Size_c; j++)
        {
          Imagedata_CMY[i][j][0]=255-Imagedata[i][j][0];
            Imagedata_CMY[i][j][1]=255-Imagedata[i][j][1];
            Imagedata_CMY[i][j][2]=255-Imagedata[i][j][2];
        }
    }
    //end question 2

    /*
    //resize
    unsigned char reImagedata[resize][resize][BytesPerPixel];
    float scal=(float)resize/(float)Size;
    for(int dstx=0;dstx<resize;dstx++)
    {
        for(int dsty=0;dsty<resize;dsty++)
        {
            float x=(dstx/scal);float y=(dsty/scal);
            float u=x-floor(x);float v=y-floor(y);
            int xx= ceil(x);int yy = ceil(y);
            int xa = floor(x);int ya = floor(y);
            reImagedata[dstx][dsty][0]=(1-u)*(1-v)*Imagedata[xx][yy][0] + u*(1-v)*Imagedata[xa][yy][0]+(1-u)*v*Imagedata[xx][ya][0]+ u*v*Imagedata[xa][ya][0];
            reImagedata[dstx][dsty][1]=(1-u)*(1-v)*Imagedata[xx][yy][1] + u*(1-v)*Imagedata[xa][yy][1]+(1-u)*v*Imagedata[xx][ya][1] + u*v*Imagedata[xa][ya][1];
            reImagedata[dstx][dsty][2]=(1-u)*(1-v)*Imagedata[xx][yy][2] + u*(1-v)*Imagedata[xa][yy][2]+(1-u)*v*Imagedata[xx][ya][2] + u*v*Imagedata[xa][ya][2];
        }
    }
     */
	/////////////////////////FINISH MY CODE////////////////////////////////////////////
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata_CMY, sizeof(unsigned char), Size_r*Size_c*BytesPerPixel, file);
	fclose(file);
	return 0;
}
