import cv2
import numpy as np
 
 
def stitch(image):
    # 图像拼接
    # stitcher = cv2.createStitcher(False)  # OpenCV 3.X.X.X使用该方法
    # stitcher = cv2.Stitcher_create(cv2.Stitcher_PANORAMA)  # OpenCV 4.X.X.X使用该方法，cv2.Stitcher_create()也可以
    # status, pano = stitcher.stitch(image)
    pano=cv2.imread("C:\\Users\\15339\\Desktop\\result.png")
    
    stitched = cv2.copyMakeBorder(pano, 10, 10, 10, 10, cv2.BORDER_CONSTANT, (0, 0, 0))
    gray = cv2.cvtColor(stitched, cv2.COLOR_BGR2GRAY)
    thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY)[1]
    cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
    print(cnts[0])

    # 轮廓最小正矩形
    mask = np.zeros(thresh.shape, dtype="uint8")
    (x, y, w, h) = cv2.boundingRect(cnts[0])  # 取出list中的轮廓二值图，类型为numpy.ndarray
    print((x, y, w, h))
    cv2.rectangle(mask, (x, y), (x + w, y + h), 255, -1)

    # 腐蚀处理，直到minRect的像素值都为0
    minRect = mask.copy()
    sub = mask.copy()
    while cv2.countNonZero(sub) > 0:
        minRect = cv2.erode(minRect, None)
        sub = cv2.subtract(minRect, thresh)

    # 提取minRect轮廓并裁剪
    cnts = cv2.findContours(minRect, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
    (x, y, w, h) = cv2.boundingRect(cnts[0])
    stitched = stitched[y:y + h, x:x + w]
    

    cv2.imshow('stitched', stitched)
    cv2.imwrite('stitched.png', stitched)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
 
 
if __name__ == "__main__":
    imageA=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\01.png")
    imageB=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\02.png")
    imageC=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\03.png")
    image = imageA, imageB
    stitch(image)