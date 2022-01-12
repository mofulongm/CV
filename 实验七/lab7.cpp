#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include<ctime>

using namespace std;
using namespace cv;

int threshold1 = 30;
int threshold2 = 30;

void modify1(int, void *) {
    Mat imag = imread("C:\\Users\\15339\\Desktop\\pictures\\1234.png");
    Mat input;
    cvtColor(imag, input, COLOR_RGB2GRAY);
    input.convertTo(input, CV_64F);
    Mat Ix, Iy, Ixx, Iyy, Ixy, output;
    output = input.clone();
    Sobel(input, Ix, -1, 1, 0);
    Sobel(input, Iy, -1, 0, 1);
    Ixx = Ix.mul(Ix);
    Ixy = Ix.mul(Iy);
    Iyy = Iy.mul(Iy);
    GaussianBlur(Ixx, Ixx, Size(11, 11), 1, 1);
    GaussianBlur(Ixy, Ixy, Size(11, 11), 1, 1);
    GaussianBlur(Iyy, Iyy, Size(11, 11), 1, 1);
    for (int x = 0; x < output.rows; x++) {
        for (int y = 0; y < output.cols; y++) {
            double det_M = Ixx.at<double>(x, y) * Iyy.at<double>(x, y) - Ixy.at<double>(x, y) * Ixy.at<double>(x, y);
            double trace_M = Ixx.at<double>(x, y) + Iyy.at<double>(x, y);
            double r = det_M - 0.05 * trace_M * trace_M;
            if ((int) r > (threshold2*2000000)) {
                circle(imag, Point(x, y), 2, Scalar(10, 10, 255), 2);
            }
        }
    }
    imshow("窗口1", imag);
}

void modify2(int, void *) {
    Mat imag = imread("C:\\Users\\15339\\Desktop\\pictures\\1234.png");
    Mat input;
    Mat dstImage;
    Mat normImage;
    cvtColor(imag, input, COLOR_RGB2GRAY);
    dstImage = Mat::zeros(imag.size(), CV_32FC1);
    cornerHarris(input, dstImage, 2, 3, 0.04, BORDER_DEFAULT);
    normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    for (int i = 0; i < normImage.rows; i++) {
        for (int j = 0; j < normImage.cols; j++) {
            if ((int) normImage.at<float>(i, j) > threshold1 + 80) {
                circle(imag, Point(i, j), 2, Scalar(10, 10, 255), 2);
            }
        }
    }
    imshow("窗口2", imag);
}

void modify_demo() {
    namedWindow("窗口1", WINDOW_AUTOSIZE);
    createTrackbar("阀值：", "窗口1", &threshold2, 175, modify1);
    modify1(0, NULL);
}

void modify_test() {
    namedWindow("窗口2", WINDOW_AUTOSIZE);
    createTrackbar("阀值：", "窗口2", &threshold1, 175, modify2);
    modify2(0, NULL);
}

int main() {
    clock_t start, finish;
    start = clock();
    modify_demo();
    finish = clock();
    cout << "time1:" << finish - start << endl;
    start = clock();
    modify_test();
    finish = clock();
    cout << "time2:" << finish - start << endl;
    waitKey();
}
