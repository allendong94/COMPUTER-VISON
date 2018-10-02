#EE569 Homework Assignment #1
#Date January 31,2018
#Name: Hang Dong
#ID: 8151308667
#EMAIL: donghang@usc.edu
#copy right reserved by author.
SYSTEM: OS X10.13.1
IDE: CLION
LANGUAGE: C++
COMPILER: g++

//problem1_____________________________________________________
//Problem_1_a_1_1:
File name:hw1_1_a_lightness.cpp
Input:image1.raw Byte_per_pixel image1_size
Output:output.raw
Function: RGB to grayscale by lightness method
Using format：
g++ hw1_1_a_lightness.cpp -o hw1_1_a_lightness
./hw1_1_a_lightness image1.raw  output.raw  Byte_per_pixel image1_size

//Problem_1_a_1_2:
File name:hw1_1_a_avg.cpp
Input:image1.raw Byte_per_pixel image1_size
Output:output.raw
Function: RGB to grayscale by lightness method
Using format：
g++ hw1_1_a_avg.cpp -o hw1_1_a_avg
./hw1_1_a_avg image1.raw  output.raw  Byte_per_pixel image1_size

//Problem_1_a_1_3:
File name:hw1_1_a_luminosity.cpp
Input:image1.raw Byte_per_pixel image1_size
Output:output.raw
Function: RGB to grayscale by lightness method
Using format：
g++ hw1_1_a_luminosity.cpp -o hw1_1_a_luminosity
./hw1_1_a_luminosity image1.raw  output.raw  Byte_per_pixel image1_size

Problem_1_a_2:
File name:hw1_1_a_cmyk.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: RGB to CMY(K)
Using format：
g++ hw1_1_a_cmyk.cpp -o hw1_1_a_cmyk
./hw1_1_a_cmyk image1.raw  output.raw  Byte_per_pixel

Problem_1_b:
File name:hw1_1_b_resize.cpp
Input:image1.raw Byte_per_pixel image1_size
The image new size need change in the code.
resize=new size of the image1
Output:output.raw
Function: Resize the image1 to another size.
Using format：
g++ hw1_1_b_resize.cpp -o hw1_1_b_resize
./hw1_1_b_resize image1.raw  output.raw  Byte_per_pixel image1_size

//problem2_____________________________________________________
Problem_2_a_method_a:
File name:hw1_2_a_tf.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Equalization the input image1.
Using format：
g++ hw1_2_a_tf.cpp -o hw1_2_a_tf
./hw1_2_a_tf image1.raw  output.raw  Byte_per_pixel

Problem_2_a_method_b:
File name:hw1_2_a_bucket.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Equalization the input image1.
Using format：
g++ hw1_2_a_bucket.cpp -o hw1_2_a_bucket
./hw1_2_a_bucket image1.raw  output.raw  Byte_per_pixel

Problem_2_a_method_b:
File name:hw1_2_a_tf.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Equalization the input image1.
Using format：
g++ hw1_2_a_tf.cpp -o hw1_2_a_tf
./hw1_2_a_tf image1.raw  output.raw  Byte_per_pixel

Problem_2_b_Quantization:
File name:hw1_2_b.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
The Quantization value need change in the code.
M=number of values in each chanel.
Function: Quantize the input image1 from 256 to other(4 or 8).
Using format：
g++ hw1_2_b.cpp -o hw1_2_b
./hw1_2_b image1.raw  output.raw  Byte_per_pixel

Problem_2_b_OIL_effect:
File name:hw1_2_b_2.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
The Quantization value need change in the code.
M=number of values in each chanel.
The NxN neighborhood size need change in the code.
matrix_size=The N for NxN neighborhood
Function: Quantize the input image1 from 256 to other(4 or 8).
Using format：
g++ hw1_2_b_2.cpp -o hw1_2_b_2
./hw1_2_b_2 image1.raw  output.raw  Byte_per_pixel

Problem_2_c:
File name:hw1_2_c.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Implement film effect to image1.
Using format：
g++ hw1_2_c.cpp -o hw1_2_c
./hw1_2_c image1.raw  output.raw  Byte_per_pixel

//problem3_____________________________________________________
Problem_3_a_gaussian:
File name:hw1_3_1_gassian.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Implement gaussian-filter to de-noise in image1.
Using format：
g++ hw1_3_1_gassian.cpp -o hw1_3_1_gassian
./hw1_3_1_gassian image1.raw  output.raw  Byte_per_pixel

Problem_3_a_mean:
File name:hw1_3_1_mean.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The NxN window size need change in the code.
matrix_size=The N for NxN window
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Implement mean-filter to de-noise in image1.
Using format：
g++ hw1_3_1_mean.cpp -o hw1_3_1_mean
./hw1_3_1_mean image1.raw  output.raw  Byte_per_pixel

Problem_3_a_mid:
File name:hw1_3_1_mid.cpp
Input:image1.raw Byte_per_pixel
Output:output.raw
The NxN window size need change in the code.
matrix_size=The N for NxN window
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Implement median-filter to de-noise in image1.
Using format：
g++ hw1_3_1_mid.cpp -o hw1_3_1_mid
./hw1_3_1_mid image1.raw  output.raw  Byte_per_pixel

psnr:
File name:psnr.cpp
Input:image1.raw Byte_per_pixel
Output:PSNR for each chanel and average
NOTE:image1 and image2 should be same size.
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: Calculate the PSNR by image1 and image2.
Using format：
g++ psnr.cpp -o psnr
./psnr image1.raw  image2.raw  Byte_per_pixel

dataoutput:
File dataoutput.cpp
Input:image1.raw Byte_per_pixel
Output:out.txt
The image size need change in the code.
Size_r=number of rows; Size_c=number of columns;
Function: calculate the histogram of cumulative histogram of image1.
Using format：
g++ dataoutput.cpp -o dataoutput
./dataoutput image1.raw  Byte_per_pixel

File name:draw_hist.m
Function: draw the histogram of input txt data;
Input:.txt
//_______________________________
Thanks for your time and have a good day!