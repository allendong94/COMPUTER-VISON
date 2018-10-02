#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(int argc, char *argv[]) {
    cout << "readraw IO is working" << endl;
    // Define file pointer and variables
    FILE *file;
    int size_r, size_c;
    int N = 6;//ITERATIVE TIMES
    // Check for proper syntax
    if (argc < 3) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 512]" << endl;
        return 0;
    }

    size_r = atoi(argv[3]);
    size_c = atoi(argv[4]);
    string Thin[46] = { "010011000","010110000","000110010","000011010","001011001",
                        "111010000","100110100","000010111","110011000","010011001","011110000","001011010","011011000","110110000",
                        "000110110","000011011","110011001","011110100","111011000","011011001","111110000","110110100","100110110",
                        "000110111","000011111","001011011","111011001","111110100","100110111","001011111","011011011","111111000",
                        "110110110","000111111","111011011","011011111","111111100","111111001","111110110","110110111","100111111",
                        "001111111","111011111","111111101","111110111","101111111" };
    string UThin[364] = { "001010000","100010000","000010010","000011000","001011000","011010000","110010000","100110000","000110100",
                          "000010110","000010011","000011001","011110000","110011000","010011001","001011010","001011100","011010100","011011100",
                          "110010001","100110001","110110001","001010110","001110100","001110110","100011001","100010011","100011011","110110000",
                          "110110001","110111000","110111001","111110000","111110001","111111000","111111001","110110010","110110011","110111010",
                          "110111011","111110010","111110011","111111010","111111011","110110100","110110101","110111100","110111101","111110100",
                          "111110101","111111100","111111101","110110110","110110111","110111110","110111111","111110110","111110111","111111110",
                          "111111111","010110010","011110010","110110010","111110010","010110010","010110011","010110110","010110111","010011010",
                          "010011011","010011110","010011111","010011010","011011010","110011010","111011010","010111000","010111100","110111000",
                          "110111100","010111000","010111001","011111000","011111001","000111010","000111011","001111010","001111011","000111010",
                          "000111110","100111010","100111110","100010101","100011100","100011101","101010100","101010101","101011100","101011101",
                          "100010111","100011110","100011111","101010110","101010111","101011110","101011111","110010101","110011100","110011101",
                          "111010100","111010101","111011100","111011101","110010111","110011110","110011111","111010110","111010111","111011110",
                          "111011111","100110101","100111100","100111101","101110100","101110101","101111100","101111101","100110111","100111110",
                          "100111111","101110110","101110111","101111110","101111111","110110101","110111100","110111101","111110100","111110101",
                          "111111100","111111101","110110111","110111110","110111111","111110110","111110111","111111110","111111111","101010100",
                          "101010010","101010110","101010001","101010101","101010011","101010111","101011100","101011010","101011110","101011001",
                          "101011101","101011011","101011111","111010100","111010010","111010110","111010001","111010101","111010011","111010111",
                          "111011100","111011010","111011110","111011001","111011101","111011011","111011111","101110100","101110010","101110110",
                          "101110001","101110101","101110011","101110111","101111100","101111010","101111110","101111001","101111101","101111011",
                          "101111111","111110100","111110010","111110110","111110001","111110101","111110011","111110111","111111100","111111010",
                          "111111110","111111001","111111101","111111011","111111111","001010101","001110001","001110101","101010001","101010101",
                          "101110001","101110101","001011101","001111001","001111101","101011001","101011101","101111001","101111101","001010111",
                          "001110011","001110111","101010011","101010111","101110011","101110111","001011111","001111011","001111111","101011011",
                          "101011111","101111011","101111111","011010101","011110001","011110101","111010001","111010101","111110001","111110101",
                          "011011101","011111001","011111101","111011001","111011101","111111001","111111101","011010111","011110011","011110111",
                          "111010011","111010111","111110011","111110111","011011111","011111011","011111111","111011011","111011111","111111011",
                          "111111111","001010101","010010101","011010101","100010101","101010101","110010101","111010101","001011101","010011101",
                          "011011101","100011101","101011101","110011101","111011101","001010111","010010111","011010111","100010111","101010111",
                          "110010111","111010111","001011111","010011111","011011111","100011111","101011111","110011111","111011111","001110101",
                          "010110101","011110101","100110101","101110101","110110101","111110101","001111101","010111101","011111101","100111101",
                          "101111101","110111101","111111101","001110111","010110111","011110111","100110111","101110111","110110111","111110111",
                          "001111111","010111111","011111111","100111111","101111111","110111111","111111111","001110010","001110011","101110010",
                          "101110011","010110001","011110001","010110101","011110101","010011100","010011101","110011100","110011101","100011010",
                          "101011010","100011110","101011110","110110000","110110001","110111000","110111001","111110000","111110001","111111000",
                          "111111001","110110010","110110011","110111010","110111011","111110010","111110011","111111010","111111011","110110100",
                          "110110101","110111100","110111101","111110100","111110101","111111100","111111101","110110110","110110111","110111110",
                          "110111111","111110110","111110111","111111110","111111111" };
    // Allocate image data array
    unsigned char Imagedata[size_r][size_c];
    unsigned char Imagedata1[size_r][size_c];
    unsigned char OUT[size_r][size_c];
    unsigned char OUT1[size_r][size_c];
    int New[size_r][size_c];
    int M[size_r][size_c];
    int U[size_r][size_c];
    int bound;
    int VALUE;
    //int Imagedata[Size][Size][BytesPerPixel];
    // Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r * size_c, file);
    fclose(file);


    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    for (int i = 0; i < size_r; i++) {
        for (int j = 0; j < size_c; j++) {
            if((int)Imagedata[i][j]<30) {
                Imagedata1[i][j] = 255;
                OUT[i][j]=255;
            }
            else
            {
                Imagedata1[i][j] = 0;
                OUT[i][j]=0;
            }
        }
    }

    VALUE = 1;
    for (int i = 1; i < size_r - 1; i++) {
        for (int j = 1; j < size_c - 1; j++) {
            if (Imagedata1[i][j] != 0) {

                    if ((Imagedata1[i - 1][j - 1] != 0) &&( Imagedata1[i - 1][j - 1] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i - 1][j - 1];
                    }
                    if ((Imagedata1[i - 1][j] != 0 )&&( Imagedata1[i - 1][j] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i - 1][j];
                    }
                    if ((Imagedata1[i][j - 1] != 0 )&&( Imagedata1[i][j - 1] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i][j - 1];
                    }

                    if ((Imagedata1[i - 1][j + 1] != 0 )&&( Imagedata1[i - 1][j + 1] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i - 1][j + 1];
                    }
                    if ((Imagedata1[i][j + 1] != 0 )&&( Imagedata1[i][j + 1] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i][j + 1];
                    }
                    if ((Imagedata1[i + 1][j - 1] != 0 )&&( Imagedata1[i + 1][j - 1] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i + 1][j - 1];
                    }
                    if ((Imagedata1[i + 1][j] != 0 )&&( Imagedata1[i + 1][j] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i + 1][j];
                    }
                    if ((Imagedata1[i + 1][j + 1] != 0 )&&( Imagedata1[i + 1][j + 1] < Imagedata1[i][j])) {
                        Imagedata1[i][j] = Imagedata1[i + 1][j + 1];
                    }
                    if(Imagedata1[i][j] ==255)
                    {Imagedata1[i][j] = VALUE; VALUE += 1;}


            }
        }
    }

    for (int j = 1; j < size_c - 1; j++) {
        for (int  i= 1; i < size_r- 1; i++) {
            if (Imagedata1[i][j] != 0) {

                if ((Imagedata1[i - 1][j - 1] != 0) &&( Imagedata1[i - 1][j - 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i - 1][j - 1];
                }
                if ((Imagedata1[i - 1][j] != 0 )&&( Imagedata1[i - 1][j] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i - 1][j];
                }
                if ((Imagedata1[i][j - 1] != 0 )&&( Imagedata1[i][j - 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i][j - 1];
                }

                if ((Imagedata1[i - 1][j + 1] != 0 )&&( Imagedata1[i - 1][j + 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i - 1][j + 1];
                }
                if ((Imagedata1[i][j + 1] != 0 )&&( Imagedata1[i][j + 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i][j + 1];
                }
                if ((Imagedata1[i + 1][j - 1] != 0 )&&( Imagedata1[i + 1][j - 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i + 1][j - 1];
                }
                if ((Imagedata1[i + 1][j] != 0 )&&( Imagedata1[i + 1][j] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i + 1][j];
                }
                if ((Imagedata1[i + 1][j + 1] != 0 )&&( Imagedata1[i + 1][j + 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i + 1][j + 1];
                }


            }
        }
    }
    for (int j =size_c - 1; j > 1; j--) {
        for (int  i= size_r- 1; i >1 ; i--) {
            if (Imagedata1[i][j] != 0) {

                if ((Imagedata1[i - 1][j - 1] != 0) &&( Imagedata1[i - 1][j - 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i - 1][j - 1];
                }
                if ((Imagedata1[i - 1][j] != 0 )&&( Imagedata1[i - 1][j] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i - 1][j];
                }
                if ((Imagedata1[i][j - 1] != 0 )&&( Imagedata1[i][j - 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i][j - 1];
                }

                if ((Imagedata1[i - 1][j + 1] != 0 )&&( Imagedata1[i - 1][j + 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i - 1][j + 1];
                }
                if ((Imagedata1[i][j + 1] != 0 )&&( Imagedata1[i][j + 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i][j + 1];
                }
                if ((Imagedata1[i + 1][j - 1] != 0 )&&( Imagedata1[i + 1][j - 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i + 1][j - 1];
                }
                if ((Imagedata1[i + 1][j] != 0 )&&( Imagedata1[i + 1][j] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i + 1][j];
                }
                if ((Imagedata1[i + 1][j + 1] != 0 )&&( Imagedata1[i + 1][j + 1] < Imagedata1[i][j])) {
                    Imagedata1[i][j] = Imagedata1[i + 1][j + 1];
                }


            }
        }
    }

    int out[100]={};int count=0;
    for (int i = 1; i < size_r-1; i++)
    {
        for (int j = 1; j < size_c-1; j++)
        {
            if((Imagedata1[i][j]!=0))
            {out[(int)Imagedata1[i][j]]+=1;}
        }
    }
    for(int i=0;i<100;i++)
    {
        if(out[i]!=0)
        {count+=1;}
    }
    int p=sqrt(count);
    cout<<"the number of pieces is:"<<count<<endl;
    //////////
    int unique_num[count];
    for(int i=0;i<count;i++)
    {
        unique_num[i]=0;
    }
    int xx=0;
    for(int x=0;x<p;x++)
    {

                //the string UShrink and Shrink are based on the link:https://github.com/DixithR19/EE569/blob/master/HW2/EE569_hw2_3098766483_gomari.pdf
        for (int i = 0+x*(size_r/p); i < (x+1)*(size_r/p); i++)
        { for(int y=0;y<p;y++)
            {
            for (int j = 0 + y * (size_c / p); j < (y + 1) * (size_c / p); j++) {

                if (Imagedata[i][j] > 58) {
                    New[i][j] = 0;
                    //OUT[i][j]= 255;
                } else {
                    New[i][j] = 1;
                    //OUT[i][j]= 0;
                }

            }
         }
        }
                int total=size_r*size_c;int count=0;
                bool sign=false;
               // for(int iter=0;iter<N;iter++)
               while(!sign)
                {
                    for (int i = 1+x*(size_r/p); i < (x+1)*(size_r/p)-1; i++)
                    {
                        for(int y=0;y<p;y++) {
                            for (int j = 1 + y * (size_c / p); j < (y + 1) * (size_c / p) - 1; j++) {
                                if (New[i][j] == 0) {
                                    M[i][j] = 0;
                                } else {
                                    bound = 2 * (New[i + 1][j - 1] + New[i - 1][j] + New[i][j + 1] + New[i][j - 1]) +
                                            (New[i - 1][j - 1] + New[i - 1][j + 1] + New[i + 1][j - 1] +
                                             New[i + 1][j + 1]);
                                    if (bound == 0 || bound == 12) {
                                        M[i][j] = 0;
                                    } else {
                                        string s;
                                        int count = 0;
                                        for (int m = i - 1; m <= i + 1; m++) {
                                            for (int n = j - 1; n <= j + 1; n++) {
                                                if (New[m][n] == 1)
                                                    s.append("1");
                                                else
                                                    s.append("0");
                                            }
                                        }
                                        for (int ii = 0; ii < 46; ii++) {
                                            if (s == Thin[ii]) {
                                                count += 1;
                                            }
                                        }
                                        if (count == 0) {
                                            M[i][j] = 0;
                                        } else {
                                            M[i][j] = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //unconditonal shrink
                    for (int i = 1+x*(size_r/p); i < (x+1)*(size_r/p)-1; i++)
                    {
                        for(int y=0;y<p;y++) {
                            for (int j = 1 + y * (size_c / p); j < (y + 1) * (size_c / p) - 1; j++) {
                                if (M[i][j] == 0) {
                                    U[i][j] = New[i][j];
                                } else {
                                    string t;
                                    int count = 0;
                                    for (int m = i - 1; m <= i + 1; m++) {
                                        for (int n = j - 1; n <= j + 1; n++) {
                                            if (M[m][n] == 1)
                                                t.append("1");
                                            else
                                                t.append("0");
                                        }
                                    }
                                    for (int ii = 0; ii < 364; ii++) {
                                        if (t == UThin[ii]) {
                                            count += 1;
                                        }
                                    }
                                    if (count == 0) {
                                        U[i][j] = 0;
                                    } else {
                                        U[i][j] = New[i][j];
                                    }
                                }
                                New[i][j] = U[i][j];

                            }
                        }
                    }
                    int number=0;
                    for (int i = 0+x*(size_r/p); i < (x+1)*(size_r/p); i++)
                    {
                        for(int y=0;y<p;y++) {
                            for (int j = 0 + y * (size_c / p); j < (y + 1) * (size_c / p); j++) {
                                if (New[i][j] == 1) {
                                    number++;
                                    OUT[i][j] = 255;
                                }
                                else { OUT[i][j] = 0; }
                            }
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
        for(int y=0;y<p;y++)
        {
            for (int i = 1+x*(size_r/p); i < (x+1)*(size_r/p)-1; i++)
            {
                for (int j = 1 + y * (size_c / p); j < (y + 1) * (size_c / p) - 1; j++)
                {
                    if ((OUT[i][j] == 255))
                    {

                        if((OUT[i-1][j-1]+OUT[i-1][j]+OUT[i-1][j+1]+OUT[i][j-1]+OUT[i][j+1]+OUT[i+1][j+1]+OUT[i+1][j]+OUT[i+1][j-1])/255==1)
                        {OUT1[i][j]=255; unique_num[xx] += 1;}
                        else
                        {OUT1[i][j]=0;}
                    }

                }
            }
            xx+=1;
        }
    }

int unique[p*p];
    for(int i=0;i<p*p;i++)
    {
        unique[i]=0;
    }
    for(int i=0;i<p*p;i++) {
        //cout << "the number of unique pieces is:" << unique_num[i]<<" "<<unique_num[i+1]<<" "<<unique_num[i+2]<<" "<<unique_num[i+3]<< endl;
        unique[unique_num[i]] +=1;
    }
    count=0;
    for(int i=0;i<p*p;i++)
    {
        if(unique[i]!=0)
        {
          count+=1;
            cout << "the number of #" <<count<<"unique piece is:"<< unique[i]<< endl;
        }
    }
    ///////////////////////// END /////////////////////////

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OUT1, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);
    if (!(file=fopen(argv[5],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OUT, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);
    return 0;
}
