import cv2
from time import *
import matplotlib.pyplot as plt


def sift():
    img1 = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\hero.jpg")
    img2 = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\hero2.jpg")
    img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    sift = cv2.xfeatures2d.SIFT_create()
    t1 = time()
    keypoints_1, descriptors_1 = sift.detectAndCompute(img1, None)    #得出关键点和关键点的各个特征向量（其中特征向量为128维）

    keypoints_2, descriptors_2 = sift.detectAndCompute(img2, None)
    bf = cv2.BFMatcher(cv2.NORM_L1, crossCheck=True)   
    matches = bf.match(descriptors_1, descriptors_2)       #将两张图的关键点进行匹配
    t2 = time()
    img3 = cv2.drawMatches(img1, keypoints_1, img2,
                           keypoints_2, matches[:100], img2, flags=2)      #输出其中的100对关键点
    plt.imshow(img3)
    plt.show()
    t3 = t2-t1
    print(t3)


def surf():
    img1 = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\hero.jpg")
    img2 = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\hero2.jpg")
    # img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    # img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    surf = cv2.xfeatures2d.SURF_create()
    t1 = time()
    keypoints_1, descriptors_1 = surf.detectAndCompute(img1, None)
    keypoints_2, descriptors_2 = surf.detectAndCompute(img2, None)
    bf = cv2.BFMatcher(cv2.NORM_L1, crossCheck=True)
    matches = bf.match(descriptors_1, descriptors_2)
    t2 = time()
    img3 = cv2.drawMatches(img1, keypoints_1, img2,
                           keypoints_2, matches[:100], img2, flags=2)
    plt.imshow(img3)
    plt.show()
    t3 = t2-t1
    print(t3)


def orb():
    img1 = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\hero.jpg")
    img2 = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\hero2.jpg")
    img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    img2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    orb = cv2.ORB_create()
    t1 = time()
    keypoints_1, descriptors_1 = orb.detectAndCompute(img1, None)
    keypoints_2, descriptors_2 = orb.detectAndCompute(img2, None)
    bf = cv2.BFMatcher(cv2.NORM_L1, crossCheck=True)
    matches = bf.match(descriptors_1, descriptors_2)
    t2 = time()
    img3 = cv2.drawMatches(img1, keypoints_1, img2,
                           keypoints_2, matches[:100], img2, flags=2)
    plt.imshow(img3)
    plt.show()
    t3 = t2-t1
    print(t3)

def main():
    # sift()
    surf()
    # orb()

if __name__ == "__main__":
    main()
