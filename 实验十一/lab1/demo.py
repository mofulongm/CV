import numpy as np
import cv2 as cv


l=np.load('C:/Users/15339/Desktop/计算机视觉/实验/实验十一/lab/r2d2-master/imgs/8-1.png.r2d2')
p=np.load('C:/Users/15339/Desktop/计算机视觉/实验/实验十一/lab/r2d2-master/imgs/8-2.png.r2d2')
kp1=[]
for i in range(300):
    kp1.append([l["keypoints"][i][0],l["keypoints"][i][1]])
kp1=np.array(kp1)
des1=[]
for i in range(300):
        des1.append(l["descriptors"][i])
des1=np.array(des1)

kp2=[]
for i in range(300):
    kp2.append([p["keypoints"][i][0],p["keypoints"][i][1]])
kp2=np.array(kp2)
des2=[]
for i in range(300):
        des2.append(p["descriptors"][i])
des2=np.array(des2)

import matplotlib.pyplot as plt

img1 = cv.imread("C:\\Users\\15339\\Desktop\\pictures\\8-1.png")
img2 = cv.imread("C:\\Users\\15339\\Desktop\\pictures\\8-2.png")
matcher = cv.DescriptorMatcher_create('BruteForce')
matches = matcher.match(des1, des2)  
good = []
now=[]
# for m in matches:
#     print(m[1].trainIdx)
# for m in matches:
#     if len(m) == 2 and  m[0].distance <= m[1].distance:
#             if m[0].trainIdx not in now:
#                 now.append(m[0].trainIdx)
#                 good.append((m[0].trainIdx, m[0].queryIdx))
(hA,wA) = img1.shape[:2]
(hB,wB) = img2.shape[:2]
vis = np.zeros((max(hA,hB), wA+wB, 3), dtype='uint8')
vis[0:hA, 0:wA] = img1
vis[0:hB, wA:] = img2
# for (queryIdx,trainIdx) in good:
#         ptA = (int(kp1[queryIdx][0]), int(kp1[queryIdx][1]))
#         ptB = (int(kp2[trainIdx][0])+wA, int(kp2[trainIdx][1]))
#         cv.line(vis, ptA, ptB, (0, 255, 0), 1)
# cv.imshow("vis",vis)
# cv.waitKey(0)
# cv.destroyAllWindows()
for m in matches:
        ptA = (int(kp1[m.trainIdx][0]), int(kp1[m.queryIdx][1]))
        ptB = (int(kp2[m.trainIdx][0]+wA), int(kp2[m.queryIdx][1]))
        cv.line(vis, ptA, ptB, (0, 255, 0), 1)
cv.imshow("vis",vis)
cv.waitKey(0)
cv.destroyAllWindows()