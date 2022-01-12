#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat image, image2, result;
int k;

void modify(int, void *) {
    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {
            double diff = 0;
            for (int c = 0; c < 3; c++) {

                diff += pow((image.at<Vec3b>(x, y)[c] - image2.at<Vec3b>(x, y)[c]), 2);
            }
            diff = sqrt(diff);
            if (diff > k)
                for (int c = 0; c < 3; c++)
                    result.at<Vec3b>(x, y)[c] = 255;
            else
                for (int c = 0; c < 3; c++)
                    result.at<Vec3b>(x, y)[c] = 0;
        }
    }
    imshow("1",result);
}

int main() {
    namedWindow("1", CV_WINDOW_AUTOSIZE);
    image = imread("C:\\Users\\15339\\Desktop\\02.jpg");
    image2 = imread("C:\\Users\\15339\\Desktop\\02_bg.jpg");
    result = Mat::zeros(image.size(), image.type());
    k = 100;
    createTrackbar("k", "1", &k, 500, modify);
    modify(k, 0);
    waitKey();

}
