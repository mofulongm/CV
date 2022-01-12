#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include<math.h>

using namespace std;
using namespace cv;

void fun1(const Mat &image) {
    Mat image2;
    image2 = Mat::zeros(image.size(), image.type());
    int H = image.rows, W = image.cols;
    for (int x = 0; x < H; x++) {
        for (int y = 0; y < W; y++) {
            double x_, y_;
            double theta, r;
            double x1, y1;
            x_ = (double) (x - 0.5 * H) / (0.5 * H);   //归一化
            y_ = (double) (y - 0.5 * W) / (0.5 * W);
            r = sqrt(x_ * x_ + y_ * y_);
            theta = (1 - r) * (1 - r);
            if (r >= 1) {
                x1 = x_;
                y1 = y_;
            } else {
                x1 = cos(theta) * x_ - sin(theta) * y_;
                y1 = cos(theta) * y_ + sin(theta) * x_;
            }
            x1 = (x1 + 1) * H *0.5;     //还原归一化的点
            y1 = (y1 + 1) * W *0.5;
            int X = (int) x1;          //左上角的点
            int Y = (int) y1;
            double a, b;
            a = x1 - X;               //求出a和b
            b = y1 - Y;
            for (int c = 0; c < 3; c++) {
                int p1, p2, p3, p4;
                p1 = image.at<Vec3b>(X, Y)[c];
                p2 = image.at<Vec3b>(X + 1, Y)[c];
                p3 = image.at<Vec3b>(X, Y + 1)[c];
                p4 = image.at<Vec3b>(X + 1, Y + 1)[c];
                double pa, pb;
                pa = (1 - a) * p1 + a * p2;
                pb = (1 - a) * p3 + a * p4;
                image2.at<Vec3b>(x, y)[c] = saturate_cast<uchar>((1 - b) * pa + b * pb);
            }
        }
    }
    imshow("E2", image2);
    waitKey();
}

Mat fun2(const Mat &image) {
    Mat image2;
    image2 = Mat::zeros(image.size(), image.type());
    int H = image.rows, W = image.cols;
    for (int x = 0; x < H; x++) {
        for (int y = 0; y < W; y++) {
            double x_, y_;
            double theta, r;
            double x1, y1;
            x_ = (double) (x - 0.5 * H) / (0.5 * H);   //归一化
            y_ = (double) (y - 0.5 * W) / (0.5 * W);
            r = sqrt(x_ * x_ + y_ * y_)*1.001;
            if (r >= 1) {
                x1 = x_;
                y1 = y_;
            } else {
                x1 = x_*r*r*r;
                y1 = y_*r*r*r;
            }
            x1 = (x1 + 1) * H *0.5;     //还原归一化的点
            y1 = (y1 + 1) * W *0.5;
            int X = (int) x1;          //左上角的点
            int Y = (int) y1;
            double a, b;
            a = x1 - X;               //求出a和b
            b = y1 - Y;
            for (int c = 0; c < 3; c++) {
                int p1, p2, p3, p4;
                p1 = image.at<Vec3b>(X, Y)[c];
                p2 = image.at<Vec3b>(X + 1, Y)[c];
                p3 = image.at<Vec3b>(X, Y + 1)[c];
                p4 = image.at<Vec3b>(X + 1, Y + 1)[c];
                double pa, pb;
                pa = (1 - a) * p1 + a * p2;
                pb = (1 - a) * p3 + a * p4;
                image2.at<Vec3b>(x, y)[c] = saturate_cast<uchar>((1 - b) * pa + b * pb);
            }
        }
    }
    return image2;
}

void fun3() {
    VideoCapture capture;
    capture.open(0);
    VideoWriter writer("C:\\Users\\15339\\Desktop\\VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
    if (!capture.isOpened()) {
        cout << "Read video Failed !" << endl;
        exit(0);
    }
    Mat frame;
    namedWindow("video test");

    int frame_num = 800;

    for (int i = 0; i < frame_num - 1; ++i) {
        capture >> frame;
        frame = fun2(frame);
        writer << frame;
        imshow("video test", frame);
        if (waitKey(30) == 'q') {
            break;
        }
    }
    destroyWindow("video test");

    capture.release();
}

int main() {
    Mat image = imread("C:\\Users\\15339\\Desktop\\2.png");
    //fun1(image);
    fun3();
}