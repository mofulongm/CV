from Stitcher import Stitcher
import cv2

def my_stitcher():
    imageA=cv2.imread("C:\\Users\\15339\\Desktop\\result12.png")
    # imageA=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\01.png")
    imageB=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\02.png")
    imageC=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\03.png")
    # imageA = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\brooklyn.png")
    # imageB = cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\brooklyn1.png")
    stitcher=Stitcher()
    # (result,vis)=stitcher.stitch([stitcher.stitch([imageA,imageB]),imageC],showMatches=True)
    (result,vis)=stitcher.stitch([imageA,imageB],showMatches=True)
    cv2.imshow("vis",vis)
    cv2.imshow("result",result)
    # cv2.imwrite("C:\\Users\\15339\\Desktop\\vis.png",vis)
    cv2.imwrite("C:\\Users\\15339\\Desktop\\result.png",result)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def stitcher():
    imageA=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\01.png")
    imageB=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\02.png")
    imageC=cv2.imread("C:\\Users\\15339\\Desktop\\pictures\\03.png")
 
    stitcher = cv2.Stitcher.create(cv2.Stitcher_PANORAMA)  
 
    (stauts,pano) = stitcher.stitch((imageA, imageB,imageC))
    cv2.imshow('pano', pano)
    cv2.waitKey(0)


if __name__ == "__main__":
    # stitcher();
     my_stitcher();
    




