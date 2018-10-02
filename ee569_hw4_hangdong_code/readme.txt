#EE569 Homework Assignment #4
#Date April 25,2018
#Name: Hang Dong
#ID: 8151308667
#EMAIL: donghang@usc.edu
#copy right reserved by author.
SYSTEM: OS X10.13.1
IDE: pycharm
LANGUAGE: python

//problem1_____________________________________________________
//problem1_b
File name:hw4_1_b.py
Function:Apply CNN to build up Lenet5 network. to recognize Mnist dataset. Specifically, this network structure has two convolution layers followed by max-pooling layers separately.
After that its followed by three full connected layers and at the last layer applied soft-max to classify the data. Whats is more, I applied drop-out between each full connected layer
to make sure its non-linear. 
Parameter:
          Learning rate: line 92(train_step = tf.train.AdamOptimizer(0.5e-4).minimize(cross_entropy))
          Iteration times: line 99(for i in range(20000))
          Batch size: line 100(batch = minist.train.next_batch(50))
          Bias: line 18(initial = tf.constant(0.1, shape=shape))
    
//problem1_c
File name:hw4_1_c.py
Function:Apply CNN to build up my network that improved from Lenet5 network. to recognize Mnist dataset. Specifically, this network structure still has two convolution layers followed by max-pooling layers separately.
After that its followed by only two full connected layers and at the last layer applied soft-max to classify the data. Whats is more, I applied drop-out between each full connected layer
to make sure its non-linear. 
Parameter:
          Learning rate: line 95(train_step = tf.train.AdamOptimizer(0.5e-4).minimize(cross_entropy))
          Iteration times: line 103(for i in range(20000))
          Batch size: line 104(batch = minist.train.next_batch(50))
          Bias: line 18(initial = tf.constant(0.1, shape=shape))
//problem2_____________________________________________________
File name:saak.py(the main file, other are support functions)
Function:Apply saak transform to recognize Mnist dataset and apply SVM/RF to classify get the final accuracy of test. Specifically, using Saak transform repeatedly to build up data as size 1*1*N, where N means the dimension of feature. Then do feature reduction and classify to recognize data. 
Parameter:
          Number of training data: line 414(num_images = 50000)
          Number of testing data: line 424( num_test = 10000)
          PCA size:line 118(fit_pca_shape(datasets,depth, start_dim = 32):)

Associated with other functions .py files included in file Saak.
//_______________________________
Thanks for your time and have a good day! 