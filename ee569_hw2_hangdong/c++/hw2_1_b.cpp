#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;
unsigned char New[2000][1500][3]={};
unsigned char New_out[2000][1500][3]={};
int main(int argc, char *argv[])

{
    cout<<"readraw IO is working"<<endl;
    // Define file pointer and variables
    FILE *file;
    int size_r,size_c;
    int BytesPerPixel=3;
    // Check for proper syntax
    if (argc < 5){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
        if (argc >= 5) {
            size_r = atoi(argv[4]);
            size_c = atoi(argv[5]);
        }
    // Allocate image data array
    unsigned char Imagedataleft[size_r][size_c][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedataleft, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    unsigned char Imagedatamid[size_r][size_c][BytesPerPixel];
    if (!(file=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(Imagedatamid, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);

    fclose(file);
    int i_l,j_l,i_h;
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    float H[3][3]={{2.0567,0.0366,87.93},{0.8774,1.4031,371.5986},{0.0011,0.000014,1}};
    //initial the middle
    int d=500;
    for (int i =0+d; i < size_r+d; ++i)
    {
        for(int j=0+d;j<size_c+d; ++j)
        {
            for(int k=0;k<3;k++)
            {
                New[i][j][k] = Imagedatamid[i-d][j-d][k];
            }
        }
    }
//left
    for (int i = 0; i < size_r; ++i)
    {
        for(int j=0;j<size_c; ++j)
        {
            for(int k=0;k<3;k++)
            {
                j_l = ((j * H[0][0] + i * H[0][1] + H[0][2])/(j * H[2][0] + i * H[2][1] + 1));
                i_l = ((j * H[1][0] + i * H[1][1] + H[1][2])/(j * H[2][0] + i * H[2][1] + 1));
                New[i_l][j_l][k] = Imagedataleft[i][j][k];
                New[i_l+1][j_l][k] = Imagedataleft[i][j][k];
                New[i_l+1][j_l+1][k] = Imagedataleft[i][j][k];
                New[i_l][j_l+1][k] = Imagedataleft[i][j][k];
                New[i_l][j_l-1][k] = Imagedataleft[i][j][k];
                New[i_l-1][j_l-1][k] = Imagedataleft[i][j][k];
                New[i_l-1][j_l][k] = Imagedataleft[i][j][k];
            }
        }
    }

    //right
    unsigned char Imagedataright[size_r][size_c][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[3],"rb"))) {
        cout << "Cannot open file: " << argv[3] <<endl;
        exit(1);
    }
    fread(Imagedataright, sizeof(unsigned char), size_r*size_c*BytesPerPixel, file);
    float HH[3][3]={{0.3029,-0.0384,709.5805},{-0.586,0.855,527.966},{-0.000715,-0.000042,1}};
    for (int i = 0; i < size_r; ++i)
    {
        for(int j=0;j<size_c; ++j)
        {
            for(int k=0;k<3;k++)
            {
                j_l = ((j * HH[0][0] + i * HH[0][1] + HH[0][2])/(j * HH[2][0] + i * HH[2][1] + 1));
                i_l = ((j * HH[1][0] + i * HH[1][1] + HH[1][2])/(j * HH[2][0] + i * HH[2][1] + 1));
                New[i_l][j_l][k] = Imagedataright[i][j][k];
                New[i_l+1][j_l][k] = Imagedataright[i][j][k];
                New[i_l+1][j_l+1][k] = Imagedataright[i][j][k];
                New[i_l][j_l+1][k] = Imagedataright[i][j][k];
                New[i_l][j_l-1][k] = Imagedataright[i][j][k];
                New[i_l-1][j_l-1][k] = Imagedataright[i][j][k];
                New[i_l-1][j_l][k] = Imagedataright[i][j][k];
            }
        }
    }
    //insert values

    ///////////////////////// END /////////////////////////
    if (!(file=fopen(argv[6],"wb"))) {
        cout << "Cannot open file: " << argv[6] << endl;
        exit(1);
    }
    fwrite(New, sizeof(unsigned char), 2000*1500*3, file);
    fclose(file);
    return 0;
}

