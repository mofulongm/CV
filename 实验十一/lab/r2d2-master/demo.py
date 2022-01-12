import numpy as np
import cv2 as cv


if __name__ == '__main__':
    l=np.load('C:/Users/15339/Desktop/计算机视觉/实验/实验十一/lab/r2d2-master/imgs/brooklyn.png.r2d2')
    l1=np.load('C:/Users/15339/Desktop/计算机视觉/实验/实验十一/lab/r2d2-master/imgs/brooklyn1.png.r2d2')
    kp1=[]
    for i in range(5000):
        kp1.append([l["keypoints"][i][0],l["keypoints"][i][1]])
    kp1=np.array(kp1)
    des1=[]
    for i in range(5000):
            des1.append(l["descriptors"][i])
    des1=np.array(des1)
    kp2=[]
    for i in range(5000):
        kp2.append([l1["keypoints"][i][0],l1["keypoints"][i][1]])
    kp2=np.array(kp2)
    des2=[]
    for i in range(5000):
            des2.append(l1["descriptors"][i])
    des2=np.array(des2)

    