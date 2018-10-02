# -*- coding: utf-8 -*-

import tensorflow as tf
import numpy as np
from tensorflow.examples.tutorials.mnist import input_data
from sklearn.svm import SVC
minist = input_data.read_data_sets('MNIST_data', one_hot=True)
sess = tf.InteractiveSession()
def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)
def classify_svm(train_feature, train_label, test_feature, test_label):
    svc = SVC()
    svc.fit(train_feature, train_label)
    accuracy = svc.score(test_feature, test_label)
    return accuracy
def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)


def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')
def conv2d_2(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='VALID')
def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
def create_numpy_dataset(num_images, train_loader, take_count=-1):
    datasets = []
    labels = []
    if num_images is None:
        num_images = len(train_loader)
    for i, data in enumerate(train_loader):
        data_numpy = data[0].numpy()
        label_numpy = data[1].numpy()

        labels.append(label_numpy)
        if i==(num_images-1):
            break
    datasets = np.array(datasets)
    labels = np.array(labels)

    if len(datasets.shape)==3:
        datasets = np.expand_dims(datasets, axis=1)

    print('Numpy dataset shape is {}'.format(datasets.shape))
    if take_count != -1:
        return datasets[:take_count], labels[:take_count]
    else:
        return datasets, labels
x = tf.placeholder(tf.float32, [None, 784])
y_ = tf.placeholder(tf.float32, [None, 10])
x_image = tf.reshape(x, [-1, 28, 28, 1])


W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)

W_conv3 = weight_variable([5, 5, 32, 64])
b_conv3 = bias_variable([64])
h_conv3 = tf.nn.relu(conv2d_2(h_pool1, W_conv3) + b_conv3)
h_pool3 = max_pool_2x2(h_conv3)
'''
W_conv4 = weight_variable([3, 3, 12, 64])
b_conv4 = bias_variable([64])
h_conv4 = tf.nn.relu(conv2d(h_pool3, W_conv4) + b_conv4)
'''

W_fc1 = weight_variable([5 * 5 * 64, 128])
b_fc1 = bias_variable([128])
h_pool2_flat1 = tf.reshape(h_pool3, [-1, 5 * 5 * 64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat1, W_fc1) + b_fc1)

'''
W_fc2 = weight_variable([80, 60])
b_fc2 = bias_variable([60])
h_pool2_flat2 = tf.reshape(h_fc1, [-1, 80])
h_fc2 = tf.nn.relu(tf.matmul(h_pool2_flat2, W_fc2) + b_fc2)
'''

keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)


W_fc3 = weight_variable([128, 10])
b_fc3 = bias_variable([10])
y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc3) + b_fc3)


cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y_conv),
                                              reduction_indices=[1]))

train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)


correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

tf.global_variables_initializer().run()

for i in range(20000):
    batch = minist.train.next_batch(50)
    if i % 100 == 0:
        train_accuracy = accuracy.eval(feed_dict={x: batch[0], y_: batch[1],
                                                  keep_prob: 1.0})
        print("step %d, training accuracy %g" % (i, train_accuracy))
        f = open("hw4_1_c_train.txt", "a")
        f.write("%g " % (train_accuracy))
        f.close()
        test_accuracy=accuracy.eval(feed_dict={x: minist.test.images,
                                 y_: minist.test.labels, keep_prob: 1.0})
        print("test accuracy %g" % test_accuracy)
        p = open("hw4_1_c_test.txt", "a")
        p.write("%g " % (test_accuracy))
        p.close()
    train_step.run(feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})
train_accuracy = accuracy.eval(feed_dict={x: batch[0], y_: batch[1],
                                              keep_prob: 1.0})
print("final training accuracy %g" % ( train_accuracy))
f = open("hw4_1_c_train.txt", "a")
f.write("%g " % (train_accuracy))
f.close()
test_accuracy=accuracy.eval(feed_dict={x: minist.test.images,
                                 y_: minist.test.labels, keep_prob: 1.0})
print("final test accuracy %g" % test_accuracy)
p = open("hw4_1_c_test.txt", "a")
p.write("%g " % (test_accuracy))
p.close()

