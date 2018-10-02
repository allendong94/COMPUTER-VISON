#EE569 Homework Assignment #3
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
//Problem_1_a:
File name:hw3_1_a.cpp
Input:texture1.raw texture2.raw texture3.raw texture4.raw texture5.raw texture6.raw texture7.raw texture8.raw texture9.raw texture10.raw texture11.raw texture12.rawOutput:output.raw
Function: texture classification
Using format：
g++ hw3_1_a.cpp -o hw3_1_a
./hw3_1_a texture1.raw texture2.raw texture3.raw texture4.raw texture5.raw texture6.raw texture7.raw texture8.raw texture9.raw texture10.raw texture11.raw texture12.raw//raw  Byte_per_pixel image1_row_size image1_column_size

//Problem_1_b:
File name:hw3_1_b.cpp
Input: comb.raw output.raw size_row size_col window_size
Output:output1.raw
Function: Image segmentation. 
Using format：
g++ hw3_1_b.cpp -o hw3_1_b
./hw3_1_b comb.raw output1.raw 600 450 13

//Problem_1_c:
File name:hw3_1_c.cpp
Input: comb.raw output.raw size_row size_col 
Output:output2.raw
Function: optimization of segmentation result.
Using format：
g++ hw3_1_c.cpp -o hw3_1_c
./hw3_1_c output1.raw output2.raw 600 450 
//problem2_____________________________________________________
Problem_2_a_1:
File name:hw3_2_a.cpp
Input:Boat.raw size_col size_row
Output:output.raw
size_r=number of rows; size_c=number of colunms;
Function: Sobel edge detector
Using format：
g++ hw3_2_a.cpp -o hw3_2_a
./hw3_2_a Boat.raw output.raw 321 481 

Problem_2_a_2:
File name:hw3_2_b.cpp
Input:Boat.raw size_col size_row
Output:output.raw
size_r=number of rows; size_c=number of columns;
Function: LOG edge detector
Using format：
g++ hw3_2_b.cpp -o hw3_2_b
./hw3_2_b Boat.raw output.raw 321 481 

//problem3_____________________________________________________
Problem_3_a:
File name:hw3_3_a.cpp
Function: Find match points by SIFT or SURF
Using format：
g++ hw3_3_a.cpp -o hw3_3_a
./hw3_3_a 

Problem_3_b:
File name:hw3_3_b.cpp
Function: Build up image matching by SIFT or SURF 
Using format：
g++ hw3_3_b.cpp -o hw3_3_b
./hw3_3_b 

Problem_3_c:
File name:hw3_3_c.cpp
Input:bumblebee.jpg Optimus_Prime.jpg ferrari1.jpg ferrari_2.jpg
Function:Build up bag of words and classify image to similar cluster
Using format：
g++ hw3_3_c.cpp -o hw3_3_c
./hw3_3_c bumblebee.jpg Optimus_Prime.jpg ferrari1.jpg ferrari_2.jpg
//_______________________________
Thanks for your time and have a good day!