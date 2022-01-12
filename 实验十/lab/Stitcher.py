import numpy as np
import cv2 as cv
import cv2 as cv2
import imutils
from PIL import Image
 

class Stitcher:

    def stitch(self,imgs, ratio = 0.5, reprojThresh = 4.0, showMatches = False):
        (img2, img1) = imgs
        # im11=img1.shape[0]
        # im12=img1.shape[1]
        # im21=img2.shape[0]
        # im22=img2.shape[1]
        # img1 = cv.resize(img1, (max(im12,im22),max(im11,im21)), interpolation=cv.INTER_AREA)
        # img2 = cv.resize(img2, (max(im12,im22),max(im11,im21)), interpolation=cv.INTER_AREA)
        #获取关键点和描述符
        (kp1, des1) = self.detectAndDescribe(img1)
        (kp2, des2) = self.detectAndDescribe(img2)

        R = self.matchKeyPoints(kp1, kp2, des1, des2, ratio, reprojThresh)
        #如果没有足够的最佳匹配点，M为None
        if R is None:
            return  None
        (good, H, mask) = R
        #对img1透视变换，M是ROI区域矩阵， 变换后的大小是(img1.w+img2.w, img1.h)
        result = cv.warpPerspective(img1, H, (img1.shape[1] + img2.shape[1], img1.shape[0]))
        #将img2的值赋给结果图像
        result[0:img2.shape[0], 0:img2.shape[1]] = img2

        if showMatches:
            vis = self.drawMatches(img1, img2, kp1, kp2, good, mask)
            return (result, vis)

        return result


    def detectAndDescribe(self,img):       
        sift = cv.xfeatures2d.SIFT_create()
        (kps, des) = sift.detectAndCompute(img, None)
        kps = np.float32([kp.pt for kp in kps]) 
        return (kps, des)

    def matchKeyPoints(self,kp1, kp2, des1, des2, ratio, reprojThresh):
        matcher = cv.DescriptorMatcher_create('BruteForce')
        matches = matcher.knnMatch(des1, des2, 2)  
        # for l in matches:
        #     print(l[0].queryIdx)
        #获取理想匹配
        good = []
        for m in matches:
            if len(m) == 2 and  m[0].distance < ratio * m[1].distance:
                good.append((m[0].trainIdx, m[0].queryIdx))

        #透视变换
        if len(good) > 4:
            #获取关键点的坐标
            src_pts = np.float32([kp1[i] for (_, i) in good])
            dst_pts = np.float32([kp2[i] for (i, _) in good])

            #通过两个图像的关键点计算变换矩阵
            (H, mask) = cv.findHomography(src_pts, dst_pts, cv.RANSAC, reprojThresh)

            #返回最佳匹配点、变换矩阵和掩模
            return (good, H, mask)
        #如果不满足最少四个 就返回None
        return None

    def drawMatches(self,img1, img2, kp1, kp2, metches,mask):
        (hA,wA) = img1.shape[:2]
        (hB,wB) = img2.shape[:2]
        vis = np.zeros((max(hA,hB), wA+wB, 3), dtype='uint8')
        vis[0:hA, 0:wA] = img1
        vis[0:hB, wA:] = img2
        cv.imshow("123",vis)
        for ((trainIdx, queryIdx),s) in zip(metches, mask):
            if s == 1:
                ptA = (int(kp1[queryIdx][0]), int(kp1[queryIdx][1]))
                ptB = (int(kp2[trainIdx][0])+wA, int(kp2[trainIdx][1]))
                cv.line(vis, ptA, ptB, (0, 255, 0), 1)

        return vis

