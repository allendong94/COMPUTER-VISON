#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cmath>
//comb.raw output.raw 600 450 13
unsigned char out[450][600]={};
unsigned char Imagedata[450][600];
float Imageresize[452][602];
float Imagedata1[450][600];
float Imagedata2[450][600];
float Imagedata3[450][600];
float Imagedata4[450][600];
float Imagedata5[450][600];
float Imagedata6[450][600];
float Imagedata7[450][600];
float Imagedata8[450][600];
float Imagedata9[450][600];
float feature_vec[450][600][9];
using namespace std;
typedef struct
{
    double x1;
    double x2;
    double x3;
    double x4;
    double x5;
    double x6;
    double x7;
    double x8;
    double x9;
}Point;
float* feature_3(int argc, char *argv[], int window,int size_r,int size_c) {
    FILE *file;
    int BytesPerPixel=1;
// Allocate image data array
//int E[3] = {-1, -2, 0, 2, 1};
//int S[3] = {-1, 0, 2, 0, -1};
//int L[3] = {-1, 2, 0, -2, 1};
    int ES[3][3] = {{1,-2,1},{0,0,0},{-1,2,-1}};
    int SE[3][3] = {{1,0,-1},{-2,0,2},{1,0,-1}};
    int EL[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    int LE[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int SL[3][3] = {{-1,-2,-1},{2,4,2},{-1,-2,-1}};
    int LS[3][3] = {{-1,2,-1},{-2,4,-2},{-1,2,-1}};
    int EE[3][3] = {{1,0,-1},{0,0,0},{-1,0,1}};
    int SS[3][3] = {{1,-2,1},{-2,4,-2},{1,-2,1}};
    int LL[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
    int half_win=window/2;
    float* Image_feature=(float*)malloc(sizeof(float)*size_r*size_c*9);
// Read image (filename specified by first argument) into image data matrix
    if (!(file = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), size_r * size_c* BytesPerPixel, file);
    fclose(file);

///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

//extension

    for (int i = 1; i < size_r + 1; i++) {
        for (int j = 1; j < size_c + 1; j++) {
            Imageresize[i][j] = (float)Imagedata[i - 1][j - 1];
        }
    }
    for (int j = 0; j < size_c+1; j++) {
        Imageresize[0][j] = (float)Imagedata[0][j];
        Imageresize[size_r - 1][j] = (float)Imagedata[size_r][j];
    }
    for (int i = 0; i < size_r + 1; i++) {
        Imageresize[i][0] = (float)Imagedata[i][0];
        Imageresize[i][size_c + 1] = (float)Imagedata[i][size_c];
    }

//EE

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata7[i-1][j-1] =(
                                          Imageresize[i - 1][j - 1] * EE[0][0] + Imageresize[i - 1][j] * EE[0][1] +
                                          Imageresize[i - 1][j + 1] * EE[0][2] +
                                          Imageresize[i ][j - 1] * EE[1][0] + Imageresize[i ][j ] * EE[1][1] +
                                          Imageresize[i ][j + 1] * EE[1][2] +
                                          Imageresize[i + 1][j - 1] * EE[2][0] + Imageresize[i + 1][j] * EE[2][1] +
                                          Imageresize[i + 1][j + 1] * EE[2][2])/4 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata7[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+6)=sqrt(sum/count);
        }
    }
//ES

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata1[i-1][j-1] =(
                    Imageresize[i - 1][j - 1] * ES[0][0] + Imageresize[i - 1][j] * ES[0][1] +
                    Imageresize[i - 1][j + 1] * ES[0][2] +
                    Imageresize[i ][j - 1] * ES[1][0] + Imageresize[i ][j ] * ES[1][1] +
                    Imageresize[i ][j + 1] * ES[1][2] +
                    Imageresize[i + 1][j - 1] * ES[2][0] + Imageresize[i + 1][j] * ES[2][1] +
                    Imageresize[i + 1][j + 1] * ES[2][2])/8 ;
        }
    }

    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata1[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+0)=sqrt(sum/count);
        }
    }
//EL

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata3[i-1][j-1] =(
                                          Imageresize[i - 1][j - 1] * EL[0][0] + Imageresize[i - 1][j] * EL[0][1] +
                                          Imageresize[i - 1][j + 1] * EL[0][2] +
                                          Imageresize[i ][j - 1] * EL[1][0] + Imageresize[i ][j ] * EL[1][1] +
                                          Imageresize[i ][j + 1] * EL[1][2] +
                                          Imageresize[i + 1][j - 1] * EL[2][0] + Imageresize[i + 1][j] * EL[2][1] +
                                          Imageresize[i + 1][j + 1] * EL[2][2])/8 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata3[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+2)=sqrt(sum/count);
        }
    }
//SE

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata2[i-1][j-1] =(
                    Imageresize[i - 1][j - 1] * SE[0][0] + Imageresize[i - 1][j] * SE[0][1] +
                    Imageresize[i - 1][j + 1] * SE[0][2] +
                    Imageresize[i ][j - 1] * SE[1][0] + Imageresize[i ][j ] * SE[1][1] +
                    Imageresize[i ][j + 1] * SE[1][2] +
                    Imageresize[i + 1][j - 1] * SE[2][0] + Imageresize[i + 1][j] * SE[2][1] +
                    Imageresize[i + 1][j + 1] * SE[2][2])/8 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata2[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+1)=sqrt(sum/count);
        }
    }

//SS

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata8[i-1][j-1] =(
                                          Imageresize[i - 1][j - 1] * SS[0][0] + Imageresize[i - 1][j] * SS[0][1] +
                                          Imageresize[i - 1][j + 1] * SS[0][2] +
                                          Imageresize[i ][j - 1] * SS[1][0] + Imageresize[i ][j ] * SS[1][1] +
                                          Imageresize[i ][j + 1] * SS[1][2] +
                                          Imageresize[i + 1][j - 1] * SS[2][0] + Imageresize[i + 1][j] * SS[2][1] +
                                          Imageresize[i + 1][j + 1] * SS[2][2])/16 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata8[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+7)=sqrt(sum/count);
        }
    }
//SL

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata5[i-1][j-1] =(
                    Imageresize[i - 1][j - 1] * SL[0][0] + Imageresize[i - 1][j] * SL[0][1] +
                    Imageresize[i - 1][j + 1] * SL[0][2] +
                    Imageresize[i ][j - 1] * SL[1][0] + Imageresize[i ][j ] * SL[1][1] +
                    Imageresize[i ][j + 1] * SL[1][2] +
                    Imageresize[i + 1][j - 1] * SL[2][0] + Imageresize[i + 1][j] * SL[2][1] +
                    Imageresize[i + 1][j + 1]* SL[2][2])/16 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata5[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+4)=sqrt(sum/count);
        }
    }

//LE

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata4[i-1][j-1]=(
                                         Imageresize[i - 1][j - 1] * LE[0][0] + Imageresize[i - 1][j] * LE[0][1] +
                                         Imageresize[i - 1][j + 1] * LE[0][2] +
                                         Imageresize[i ][j - 1] * LE[1][0] + Imageresize[i ][j ] * LE[1][1] +
                                         Imageresize[i ][j + 1] * LE[1][2] +
                                         Imageresize[i + 1][j - 1] * LE[2][0] + Imageresize[i + 1][j] * LE[2][1] +
                                         Imageresize[i + 1][j + 1] * LE[2][2] )/8;
        }
    }
    for (int i=0;i<size_r;i++){
        for (int j=0;j<size_c;j++){
            Imagedata4[i][j]=Imagedata4[i][j]/8.0;
        }
    }

    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata4[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+3)=sqrt(sum/count);
        }
    }
//LS

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata6[i-1][j-1] =(
                                          Imageresize[i - 1][j - 1] * LS[0][0] + Imageresize[i - 1][j] * LS[0][1] +
                                          Imageresize[i - 1][j + 1] * LS[0][2] +
                                          Imageresize[i ][j - 1] * LS[1][0] + Imageresize[i ][j ]* LS[1][1] +
                                          Imageresize[i ][j + 1] * LS[1][2] +
                                          Imageresize[i + 1][j - 1] * LS[2][0] + Imageresize[i + 1][j] * LS[2][1] +
                                          Imageresize[i + 1][j + 1]* LS[2][2])/16 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata6[p][q],2);
                        count++;
                    }

                }
            }
            *(Image_feature+i*(size_c*9)+j*9+5)=sqrt(sum/count);
        }
    }
//LL

    for (int i = 1; i < size_r+1; i++) {
        for (int j = 1; j < size_c+1; j++) {
            Imagedata9[i-1][j-1] =(
                    Imageresize[i - 1][j - 1] * LL[0][0] + Imageresize[i - 1][j]* LL[0][1] +
                    Imageresize[i - 1][j + 1] * LL[0][2] +
                    Imageresize[i ][j - 1] * LL[1][0] + Imageresize[i ][j ] * LL[1][1] +
                    Imageresize[i ][j + 1] * LL[1][2] +
                    Imageresize[i + 1][j - 1] * LL[2][0] + Imageresize[i + 1][j] * LL[2][1] +
                    Imageresize[i + 1][j + 1] * LL[2][2])/16 ;
        }
    }


    for (int i=0;i<size_r;i++)
    {
        for (int j=0;j<size_c;j++)
        {
            int count=0;int sum=0;
            for (int p=i-half_win;p<i+half_win;p++)
            {
                for (int q=j-half_win;q<j+half_win;q++)
                {
                    if ((p>0)&&(p<size_r)&&(q>0)&&(q<size_c))
                    {
                        sum+=pow(Imagedata9[p][q],2);
                        count++;
                    }

                }
            }

            *(Image_feature+i*(size_c*9)+j*9+8)=sqrt(sum/count);
        }
    }
    /*
    for(int i=0;i<size_r*size_c;i++)
    {

        for(int j=0;j<9;j++)
        {
            *(Image_feature+row*(size_c*9)+col*9+j)=featurevector[i][j];
        }
    }
*/
    return Image_feature;
}
int k_means(float feature[450][600][9], int cluster_num,int size_r,int size_c,char *argv[])
{
    int  gray_scale[6]={0,51,102,153,204,255};
    vector<Point> vecPoint;
    vector<Point> vecCenter;
    vector<vector<Point> > vecCluster;
    Point temp;
    double distance,mindistance;
    int flag,round=1;
    double errorSum1=0;
    double errorSum2=1;
    for(int i=0;i<size_r;i++)
    {
        for(int j=0;j<size_c;j++)
        {
            temp.x1 = feature[i][j][0];
            temp.x2 = feature[i][j][1];
            temp.x3 = feature[i][j][2];
            temp.x4 = feature[i][j][3];
            temp.x5 = feature[i][j][4];
            temp.x6 = feature[i][j][5];
            temp.x7 = feature[i][j][6];
            temp.x8 = feature[i][j][7];
            temp.x9 = feature[i][j][8];
            vecPoint.push_back(temp);
        }
    }
//initialize center
    temp.x1=feature[70][40][0];
    temp.x2=feature[70][40][1];
    temp.x3=feature[70][40][2];
    temp.x4=feature[70][40][3];
    temp.x5=feature[70][40][4];
    temp.x6=feature[70][40][5];
    temp.x7=feature[70][40][6];
    temp.x8=feature[70][40][7];
    temp.x9=feature[70][40][8];
    vecCenter.push_back(temp);
    temp.x1=feature[70][580][0];
    temp.x2=feature[70][580][1];
    temp.x3=feature[70][580][2];
    temp.x4=feature[70][580][3];
    temp.x5=feature[70][580][4];
    temp.x6=feature[70][580][5];
    temp.x7=feature[70][580][6];
    temp.x8=feature[70][580][7];
    temp.x9=feature[70][580][8];
    vecCenter.push_back(temp);
    temp.x1=feature[410][80][0];
    temp.x2=feature[410][80][1];
    temp.x3=feature[410][80][2];
    temp.x4=feature[410][80][3];
    temp.x5=feature[410][80][4];
    temp.x6=feature[410][80][5];
    temp.x7=feature[410][80][6];
    temp.x8=feature[410][80][7];
    temp.x9=feature[410][80][8];
    vecCenter.push_back(temp);
    temp.x1=feature[440][540][0];
    temp.x2=feature[440][540][1];
    temp.x3=feature[440][540][2];
    temp.x4=feature[440][540][3];
    temp.x5=feature[440][540][4];
    temp.x6=feature[440][540][5];
    temp.x7=feature[440][540][6];
    temp.x8=feature[440][540][7];
    temp.x9=feature[440][540][8];
    vecCenter.push_back(temp);
    temp.x1=feature[200][300][0];
    temp.x2=feature[200][300][1];
    temp.x3=feature[200][300][2];
    temp.x4=feature[200][300][3];
    temp.x5=feature[200][300][4];
    temp.x6=feature[200][300][5];
    temp.x7=feature[200][300][6];
    temp.x8=feature[200][300][7];
    temp.x9=feature[200][300][8];
    vecCenter.push_back(temp);
    temp.x1=feature[220][150][0];
    temp.x2=feature[220][150][1];
    temp.x3=feature[220][150][2];
    temp.x4=feature[220][150][3];
    temp.x5=feature[220][150][4];
    temp.x6=feature[220][150][5];
    temp.x7=feature[220][150][6];
    temp.x8=feature[220][150][7];
    temp.x9=feature[220][150][8];
    vecCenter.push_back(temp);
    vector<Point> tempvec;

    for(int i=0;i<cluster_num;i++)
    {
        vecCluster.push_back(tempvec);
    }
    while(fabs(errorSum2-errorSum1)>0.0001)
    {
        for(int i=0;i<vecCluster.size();i++)
        {
            vecCluster[i].clear();
        }
        for(int i=0;i<size_r*size_c;i++)
        {
            mindistance=sqrt(pow(vecPoint[i].x1-vecCenter[0].x1,2)+pow(vecPoint[i].x2-vecCenter[0].x2,2)+pow(vecPoint[i].x3-vecCenter[0].x3,2)
                             +pow(vecPoint[i].x4-vecCenter[0].x4,2)+pow(vecPoint[i].x5-vecCenter[0].x5,2)+pow(vecPoint[i].x6-vecCenter[0].x6,2)
                             +pow(vecPoint[i].x7-vecCenter[0].x7,2)+pow(vecPoint[i].x8-vecCenter[0].x8,2)+pow(vecPoint[i].x9-vecCenter[0].x9,2));
            flag=0;
            for(int k=1;k<cluster_num;k++)
            {
                distance=sqrt(pow(vecPoint[i].x1-vecCenter[k].x1,2)+pow(vecPoint[i].x2-vecCenter[k].x2,2)+pow(vecPoint[i].x3-vecCenter[k].x3,2)
                              +pow(vecPoint[i].x4-vecCenter[k].x4,2)+pow(vecPoint[i].x5-vecCenter[k].x5,2)+pow(vecPoint[i].x6-vecCenter[k].x6,2)
                              +pow(vecPoint[i].x7-vecCenter[k].x7,2)+pow(vecPoint[i].x8-vecCenter[k].x8,2)+pow(vecPoint[i].x9-vecCenter[k].x9,2));
                if(distance<mindistance)
                {
                    flag=k;
                    mindistance=distance;
                }
            }
            vecCluster[flag].push_back(vecPoint[i]);
            int row=floor(i/size_c);
            int col=i%size_c;
            out[row][col]=gray_scale[flag];
        }

        if(round==1)
        {

            errorSum1=0;
            for(int k=0;k<cluster_num;k++)
            {
                for(int i=0;i<vecCluster[k].size();i++)
                {
                    errorSum1+=pow(vecCenter[k].x1-vecCluster[k][i].x1,2)+pow(vecCenter[k].x2-vecCluster[k][i].x2,2)+pow(vecCenter[k].x3-vecCluster[k][i].x3,2)
                               +pow(vecCenter[k].x4-vecCluster[k][i].x4,2)+pow(vecCenter[k].x5-vecCluster[k][i].x5,2)+pow(vecCenter[k].x6-vecCluster[k][i].x6,2)
                               +pow(vecCenter[k].x7-vecCluster[k][i].x7,2)+pow(vecCenter[k].x8-vecCluster[k][i].x8,2)+pow(vecCenter[k].x9-vecCluster[k][i].x9,2);
                }
            }
        }
        else
        {
            errorSum1=errorSum2;
        }

        round++;
        double sum_x1,sum_x2,sum_x3,sum_x4,sum_x5,sum_x6,sum_x7,sum_x8,sum_x9;
        vecCenter.clear();
        for(int k=0;k<cluster_num;k++)
        {
            sum_x1=0;sum_x2=0;sum_x3=0;sum_x4=0;sum_x5=0;sum_x6=0;sum_x7=0;sum_x8=0;sum_x9=0;
            for(int i=0;i<vecCluster[k].size();i++)
            {
                sum_x1+=vecCluster[k][i].x1;
                sum_x2+=vecCluster[k][i].x2;
                sum_x3+=vecCluster[k][i].x3;
                sum_x4+=vecCluster[k][i].x4;
                sum_x5+=vecCluster[k][i].x5;
                sum_x6+=vecCluster[k][i].x6;
                sum_x7+=vecCluster[k][i].x7;
                sum_x8+=vecCluster[k][i].x8;
                sum_x9+=vecCluster[k][i].x9;
            }
            temp.x1=sum_x1/vecCluster[k].size();
            temp.x2=sum_x2/vecCluster[k].size();
            temp.x3=sum_x3/vecCluster[k].size();
            temp.x4=sum_x4/vecCluster[k].size();
            temp.x5=sum_x5/vecCluster[k].size();
            temp.x6=sum_x6/vecCluster[k].size();
            temp.x7=sum_x7/vecCluster[k].size();
            temp.x8=sum_x8/vecCluster[k].size();
            temp.x9=sum_x9/vecCluster[k].size();
            vecCenter.push_back(temp);
        }
        errorSum2=0;
        for(int k=0;k<cluster_num;k++)
        {
            for(int i=0;i<vecCluster[k].size();i++)
            {
                errorSum2+=pow(vecCenter[k].x1-vecCluster[k][i].x1,2)+pow(vecCenter[k].x2-vecCluster[k][i].x2,2)+pow(vecCenter[k].x3-vecCluster[k][i].x3,2)
                           +pow(vecCenter[k].x4-vecCluster[k][i].x4,2)+pow(vecCenter[k].x5-vecCluster[k][i].x5,2)+pow(vecCenter[k].x6-vecCluster[k][i].x6,2)
                           +pow(vecCenter[k].x7-vecCluster[k][i].x7,2)+pow(vecCenter[k].x8-vecCluster[k][i].x8,2)+pow(vecCenter[k].x9-vecCluster[k][i].x9,2);
            }
        }
    }

    FILE *file;
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(out, sizeof(unsigned char), size_r*size_c, file);
    fclose(file);
    return 0;
}
int main(int argc, char *argv[])
{
    int size_r=atoi(argv[4]);int size_c=atoi(argv[3]);
    cout << "readraw IO is working" << endl;

    float* p;

        //cout<<"start iteration time: "<<key<<endl;
        int window=atoi(argv[5]);
        p=feature_3(argc,argv,window,size_r,size_c);
        for (int i = 0; i < size_r; i++)
        {
            for(int j = 0; j < size_c; j++)
            {
                for(int k = 0; k < 9; k++)
                {
                    feature_vec[i][j][k] = *(p + i*(size_c*9)+j*9+k);
                }
            }
        }
        int cluster_num=6;
        k_means(feature_vec,cluster_num,size_r,size_c,argv);

    return 0;
}

