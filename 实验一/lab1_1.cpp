#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
Mat image, image2;
int b=0,k=57;

void modify(int, void *) {
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            for (int c = 0; c < 3; c++) {
                double t=1/(1+exp((-1.0*image.at<Vec3b>(x, y)[c]+128)/k));//S型函数，就是对比度
                image2.at<Vec3b>(x, y)[c] = saturate_cast<uchar>(t*(
                        image.at<Vec3b>(x, y)[c])+b);//线性函数，其中斜率为对比度，截距为整张图加的值
            }
        }
    }
    imshow("1", image2);
}

int main() {
    namedWindow("1", CV_WINDOW_AUTOSIZE);
    image = imread("C:\\Users\\15339\\Pictures\\Saved Pictures\\R-C.jpg");
    

    createTrackbar("b", "1", &b, 300, modify);
    createTrackbar("k", "1", &k, 500, modify);
    waitKey();
}
