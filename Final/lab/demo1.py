import cv2

img1=cv2.imread("C://Users//15339//Desktop//CV//Lab//Final//lab//image//phone.png")
# img2=cv2.imread("C://Users//15339//Desktop//CV//Lab//Final//lab//image//phone1.png")
cap = cv2.VideoCapture('C://Users//15339//Desktop//CV//Lab//Final//lab//video//tv.mp4')        # 打开摄像头
# cap=cv2.VideoCapture(0)
i=0
while True:
    ret, img2 = cap.read()   
    orb=cv2.AKAZE_create()

    kp1,des1=orb.detectAndCompute(img1,None)
    kp2,des2=orb.detectAndCompute(img2,None)

    imgKp1=cv2.drawKeypoints(img1,kp1,None)
    imgKp2=cv2.drawKeypoints(img2,kp2,None)

    bf=cv2.BFMatcher()
    matches=bf.knnMatch(des1,des2,k=2)

    good=[]
    for m,n in matches:
        if m.distance<0.75*n.distance:
            good.append([m])

    img3=cv2.drawMatchesKnn(img1,kp1,img2,kp2,good,None,flags=2)

    cv2.imshow("3",img3)
    if cv2.waitKey(1) & 0xFF == ord('q'):  # 按q退出
        break
     
cap.release()  
cv2.waitKey(0)
cv2.destroyAllWindows()


