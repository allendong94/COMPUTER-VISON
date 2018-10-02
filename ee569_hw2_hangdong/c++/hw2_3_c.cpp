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
    int size_r,size_c;
    int N=17;//ITERATIVE TIMES
    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }

    size_r = atoi(argv[3]);
    size_c = atoi(argv[4]);

    // Allocate image data array
    unsigned char Imagedata[size_r][size_c];
    unsigned char OUT[size_r][size_c];
    int New[size_r][size_c];
    int M[size_r][size_c];
    int U[size_r][size_c];
    int bound;

    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    string Ske[40] = { "111111011","111111110","110111111","011111111","010011000","010110000","000110010","000011010","001011001",
                       "111010000","100110100","000010111","111011000","011011001","111110000","110110100","100110110","000110111","000011111","001011011","111011001","111110100","100110111",
                       "001011111","011011011","111111000","110110110","000111111","111011011","011011111","111111100","111111001","111110110","110110111","100111111",
                       "001111111","111011111","111111101","111110111","101111111" };

    string USke[444] = { "000010001","000010100","001010000","100010000","000010010","000011000","000110000","010010000",
                         "010011000","010110000","000011010","000110010",
                         "110110000","110110001","110111000","110111001","111110000","111110001","111111000","111111001",
                         "110110010","110110011","110111010","110111011","111110010","111110011","111111010","111111011",
                         "110110100","110110101","110111100","110111101","111110100","111110101","111111100","111111101",
                         "110110110","110110111","110111110","110111111","111110110","111110111","111111110","111111111",
                         "000011011","001011011","010011011","011011011","000011111","001011111","010011111","011011111",
                         "000111011","001111011","010111011","011111011","000111111","001111111","010111111","011111111",
                         "100011011","101011011","110011011","111011011","100011111","101011111","110011111","111011111",
                         "100111011","101111011","110111011","111111011","100111111","101111111","110111111","111111111",
                         "010110010","010110011","010111010","010111011","011110010","011110011","011111010","011111011",
                         "010110110","010110111","010111110","010111111","011110110","011110111","011111110","011111111",
                         "110110010","110110011","110111010","110111011","111110010","111110011","111111010","111111011",
                         "110110110","110110111","110111110","110111111","111110110","111110111","111111110","111111111",
                         "010111000","010111001","011111000","011111001","010111010","010111011","011111010","011111011",
                         "010111100","010111101","011111100","011111101","010111110","010111111","011111110","011111111",
                         "110111000","110111001","111111000","111111001","110111010","110111011","111111010","111111011",
                         "110111100","110111101","111111100","111111101","110111110","110111111","111111110","111111111",
                         "010011010","010011011","011011010","011011011","010011110","010011111","011011110","011011111",
                         "010111010","010111011","011111010","011111011","010111110","010111111","011111110","011111111",
                         "110011010","110011011","111011010","111011011","110011110","110011111","111011110","111011111",
                         "110111010","110111011","111111010","111111011","110111110","110111111","111111110","111111111",
                         "000111010","000111011","001111010","001111011","010111010","010111011","011111010","011111011",
                         "000111110","000111111","001111110","001111111","010111110","010111111","011111110","011111111",
                         "100111010","100111011","101111010","101111011","110111010","110111011","111111010","111111011",
                         "100111110","100111111","101111110","101111111","110111110","110111111","111111110","111111111",
                         "100010101","100011100","101010100","100011101","101010101","101011100","101011101","100010111",
                         "100011110","101010110","100011111","101010111","101011110","101011111","110010101","110011100",
                         "111010100","110011101","111010101","111011100","111011101","110010111","110011110","111010110",
                         "110011111","111010111","111011110","111011111","100110101","100111100","101110100","100111101",
                         "101110101","101111100","101111101","100110111","100111110","101110110","100111111","101110111",
                         "101111110","101111111","110110101","110111100","111110100","110111101","111110101","111111100",
                         "111111101","110110111","110111110","111110110","110111111","111110111","111111110","111111111",
                         "101010100","101010010","101010110","101010001","101010101","101010011","101010111","101011100",
                         "101011010","101011110","101011001","101011101","101011011","101011111","111010100","111010010",
                         "111010110","111010001","111010101","111010011","111010111","111011100","111011010","111011110",
                         "111011001","111011101","111011011","111011111","101110100","101110010","101110110","101110001",
                         "101110101","101110011","101110111","101111100","101111010","101111110","101111001","101111101",
                         "101111011","101111111","111110100","111110010","111110110","111110001","111110101","111110011",
                         "111110111","111111100","111111010","111111110","111111001","111111101","111111011","111111111",
                         "001010101","001110001","001110101","101010001","101010101","101110001","101110101","001011101",
                         "001111001","001111101","101011001","101011101","101111001","101111101","001010111","001110011",
                         "001110111","101010011","101010111","101110011","101110111","001011111","001111011","001111111",
                         "101011011","101011111","101111011","101111111","011010101","011110001","011110101","111010001",
                         "111010101","111110001","111110101","011011101","011111001","011111101","111011001","111011101",
                         "111111001","111111101","011010111","011110011","011110111","111010011","111010111","111110011",
                         "111110111","011011111","011111011","011111111","111011011","111011111","111111011","111111111",
                         "001010101","010010101","011010101","100010101","101010101","110010101","111010101","001011101",
                         "010011101","011011101","100011101","101011101","110011101","111011101","001010111","010010111",
                         "011010111","100010111","101010111","110010111","111010111","001011111","010011111","011011111",
                         "100011111","101011111","110011111","111011111","001110101","010110101","011110101","100110101",
                         "101110101","110110101","111110101","001111101","010111101","011111101","100111101","101111101",
                         "110111101","111111101","001110111","010110111","011110111","100110111","101110111","110110111",
                         "111110111","001111111","010111111","011111111","100111111","101111111","110111111","111111111",
                         "001110010","001110011","101110010","101110011","110010001","111010001","110010101","111010101",
                         "010011100","010011101","110011100","110011101","100011010","101011010","100011110","101011110" };
    //the string UThin and Thin are based on the link:https://github.com/DixithR19/EE569/blob/master/HW2/EE569_hw2_3098766483_gomari.pdf
    for (int i = 0; i < size_r; i++)
    {
        for (int j = 0; j < size_c; j++)
        {

            if (Imagedata[i][j]> 110)
            {
                New[i][j]= 0;
                //OUT[i][j]= 255;
            }
            else
            {
                New[i][j]= 1;
                //OUT[i][j]= 0;
            }

        }
    }
    int total=size_r*size_c;int count=0;
    bool sign=false;
    //for(int iter=0;iter<N;iter++)
    while(!sign)
    {count+=1;
        for(int i=1;i<size_r-1;i++)
        {
            for(int j=1;j<size_c-1;j++)
            {
                if(New[i][j]==0)
                {
                    M[i][j] = 0;
                }
                else
                {
                    bound=2*(New[i+1][j-1]+New[i-1][j]+New[i][j+1]+New[i][j-1])+(New[i-1][j-1]+New[i-1][j+1]+New[i+1][j-1]+New[i+1][j+1]);
                    if(bound==0||bound==12)
                    {
                        M[i][j] = 0;
                    }
                    else
                    {
                        string s;int count=0;
                        for (int m = i - 1; m <= i + 1; m++) {
                            for (int n = j - 1; n <= j + 1; n++) {
                                if (New[m][n]==1)
                                    s.append("1");
                                else
                                    s.append("0");
                            }
                        }
                        for (int ii = 0; ii < 40; ii++) {
                            if (s ==Ske[ii]) {
                                count += 1;
                            }
                        }
                        if (count == 0) {
                            M[i][j] = 0;
                        }
                        else {
                            M[i][j] = 1;
                        }
                    }
                }
            }
        }
        //unconditonal shrink
        for(int i=1;i<size_r-1;i++)
        {
            for(int j=1;j<size_c-1;j++)
            {
/*
                if(M[i][j]==1)
                {U[i][j]=New[i][j]*(M[i][j-1]*M[i][j+1]*M[i+1][j+1]*M[i-1][j-1]*M[i+1][j]*M[i-1][j]*M[i-1][j+1]*M[i+1][j-1]);}
                else
                {
                 U[i][j]=New[i][j];
                }
                New[i][j]=U[i][j];
*/
                if(M[i][j]==0)
                {
                    U[i][j]=New[i][j];
                }
                else
                {
                    string t;int count=0;
                    for (int m = i - 1; m <= i + 1; m++) {
                        for (int n = j - 1; n <= j + 1; n++) {
                            if (M[m][n]==1)
                                t.append("1");
                            else
                                t.append("0");
                        }
                    }
                    for (int ii = 0; ii < 444; ii++) {
                        if (t == USke[ii]) {
                            count += 1;
                        }
                    }
                    if (count == 0) {
                        U[i][j] = 0;
                    }
                    else {
                        U[i][j] = New[i][j];
                    }
                }
                New[i][j] = U[i][j];

            }
        }
        int number=0;
        for(int i=0;i<size_r;i++)
        {
            for(int j=0;j<size_c;j++)
            {
                if(New[i][j]==1){number++;OUT[i][j]=255;}
                else {OUT[i][j]=0;}
            }
        }
        if(total>number)
        {
            total=number;
        }
        else if(total=number)
        {
            sign=true;
        }
    }


    //cout<<"the number of stars is:"<<total<<endl;
    //cout<<"the number of stars size is:"<<count-1<<endl;
    ///////////////////////// END /////////////////////////

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OUT, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);

    return 0;
}

