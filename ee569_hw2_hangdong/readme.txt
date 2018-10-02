#EE569 Homework Assignment #2
#Date February 23,2018
#Name: Hang Dong
#ID: 8151308667
#EMAIL: donghang@usc.edu
#copy right reserved by author.
SYSTEM: OS X10.13.1
IDE: CLION
LANGUAGE: C++
COMPILER: g++

//problem1_____________________________________________________
//Problem_1_a_1:
File name:hw2_1_a.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
Function: Warping the rectangular image to a round shape.
Using format：
g++ hw2_1_a.cpp -o hw2_1_a
./hw2_1_a image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size

//Problem_1_a_2:
File name:hw2_1_a_r.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
Function: Reverse the warping image to its original image
Using format：
g++ hw2_1_a_r.cpp -o hw2_1_a_r
./hw2_1_a_r image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size

//Problem_1_b:
File name:hw2_1_b.cpp
Input:image_left.raw image_middle.raw image_right.raw  image_row_size image_column_sizee
Output:output.raw
Function: Image Stitching and build up panorama image. 
Using format：
g++ hw2_1_b.cpp -o hw2_1_b
./hw2_1_b image_l.raw image_m.raw image_r.raw image1_row_size image1_column_size output.raw

//problem2_____________________________________________________
Problem_2_a_1:
File name:hw2_2_a_1.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
size_r=number of rows; size_c=number of columns;
Function: Fixed thresholding method to build up half-toning.
Using format：
g++ hw2_2_a_1.cpp -o hw2_2_a_1
./hw2_2_a_1 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size 

Problem_2_a_2:
File name:hw2_2_a_2.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function: Random thresholding method to build up half-toning.
Using format：
g++ hw2_2_a_2.cpp -o hw2_2_a_2
./hw2_2_a_2 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size

Problem_2_a_3:
File name:hw2_2_a_3.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size N
Output:output.raw
N the scale of the I matrix, In this problem can select 2/4/8
Size_r=number of rows; Size_c=number of columns;
Function: Dithering Matrix method to build up half-toning.
Using format：
g++ hw2_2_a_3.cpp -o hw2_2_a_3
./hw2_2_a_3 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size
Note need change in code to select use different I matrix. Ex: I2,I4,I8.

Problem_2_a_4:
File name:hw2_2_a_4.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size 
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function: My own method to build up 4 levels display image.
Using format：
g++ hw2_2_a_4.cpp -o hw2_2_a_4
./hw2_2_a_4 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size N

Problem_2_b_1:
File name:hw2_2_b_1.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
size_r=number of rows; size_c=number of columns;
Function: Floyd-Steinberg’s error diffusion method to build up half-toning.
Using format：
g++ hw2_2_b_1.cpp -o hw2_2_b_1
./hw2_2_b_1 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size 

Problem_2_b_2:
File name:hw2_2_b_2.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
size_r=number of rows; size_c=number of columns;
Function: JJN error diffusion method to build up half-toning.
Using format：
g++ hw2_2_b_2.cpp -o hw2_2_b_2
./hw2_2_b_2 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size 

Problem_2_b_3:
File name:hw2_2_b_3.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
size_r=number of rows; size_c=number of columns;
Function: stucki error diffusion method to build up half-toning.
Using format：
g++ hw2_2_b_3.cpp -o hw2_2_b_3
./hw2_2_b_3 image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size 

Problem_2_c_1:
File name:hw2_2_c.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function: Separable Error Diffusion method to build up color half-toning image.
Using format：
g++ hw2_2_c.cpp -o hw2_2_c
./hw2_2_c image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size

Problem_2_c_2:
File name:hw2_2_c_mbvq.cpp
Input:image1.raw Byte_per_pixel image1_row_size image1_column_size
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function: MBVQ-based Error diffusion method to build up color half-toning image.
Using format：
g++ hw2_2_c_mbvq.cpp -o hw2_2_c_mbvq
./hw2_2_c_mbvq image1.raw  output.raw  Byte_per_pixel image1_row_size image1_column_size

//problem3_____________________________________________________
Problem_3_c_1:
File name:hw2_3_a.cpp
Input:image1.raw  image1_row_size image1_column_size
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function: counting star and find the number of differnet size.
Using format：
g++ hw2_3_a.cpp -o hw2_3_a
./hw2_3_a image1.raw  output.raw  image1_row_size image1_column_size

Problem_3_c_2:
File name:hw2_3_b.cpp
Input:image1.raw  image1_row_size image1_column_size
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function:Thinning method to get the Skeletonizing main structure of the input image.  
Using format：
g++ hw2_3_b.cpp -o hw2_3_b
./hw2_3_b image1.raw  output.raw  image1_row_size image1_column_size

Problem_3_c_3:
File name:hw2_3_c.cpp
Input:image1.raw  image1_row_size image1_column_size
Output:output.raw
Size_r=number of rows; Size_c=number of columns;
Function:Skeletonizing method to get the Skeletonizing main structure of the input image.  
Using format：
g++ hw2_3_c.cpp -o hw2_3_c
./hw2_3_c image1.raw  output.raw  image1_row_size image1_column_size

Problem_3_c_4:
File name:hw2_3_d.cpp
Input:image1.raw  image1_row_size image1_column_size
Output:output.raw output1.raw
Size_r=number of rows; Size_c=number of columns;
Function:Find the number of pieces and identify unique pieces.  
Using format：
g++ hw2_3_d.cpp -o hw2_3_d
./hw2_3_d image1.raw  output.raw  image1_row_size image1_column_size output1.raw


//_______________________________
Thanks for your time and have a good day!