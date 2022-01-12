#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include<ctime>

using namespace std;
using namespace cv;

Mat image, image2;
Mat imag, imag2;
int b = 1;
int k = 1;
int l = 1;

void Gaussian(const Mat &input, Mat &output, double sigma) {
    double sum = 0;
    int d = int(6 * sigma - 1), center;
    double kernel[1000];
    center = d / 2;
    for (int i = 0; i < d; ++i) {//求卷积核
        kernel[i] = exp((-1 * (i - center) * (i - center)) / (2 * sigma * sigma)) / (2 * 3.14 * sigma * sigma);
        sum += kernel[i];
    }
    for (int i = 0; i < d; ++i) kernel[i] /= sum;

    output = Mat::zeros(input.size(), input.type());
    int H = output.rows, W = output.cols;


    for (int x = 0; x < H; ++x) {    //对行进行
        for (int y = 0; y < W; ++y) {
            for (int c = 0; c < 3; ++c) {
                sum = 0;
                for (int p = 0; p < d; ++p) {
                    int q = p  - center+y;
                    if (q < 0) q = 0;
                    if (q >= W) q = W - 1;
                    sum += (double) input.at<Vec3b>(x, q)[c] * kernel[p];
                }
                output.at<Vec3b>(x, y)[c] = saturate_cast<uchar>(sum);
            }
        }
    }

    for (int x = 0; x < H; ++x) {   //对列进行
        for (int y = 0; y < W; ++y) {
            for (int c = 0; c < 3; ++c) {
                sum = 0;
                for (int p = 0; p < d; ++p) {
                    int q = p  - center+x;
                    if (q < 0) q = 0;
                    if (q >= H) q = H - 1;
                    sum += (double) output.at<Vec3b>(q, y)[c] * kernel[p];
                }
                output.at<Vec3b>(x, y)[c] = saturate_cast<uchar>(sum);
            }
        }
    }

}

void MeanFilter(const Mat &input, Mat &output, int window_size) {
    output = Mat::zeros(input.size(), input.type());
    int H = input.rows, W = input.cols;
    int sum[H][W];
    for (int c = 0; c < 3; c++) {   //求取积分图
        for (int x = 0; x < H; x++) {
            int sum1 = 0;
            for (int y = 0; y < W; y++) {
                sum1 += input.at<Vec3b>(x, y)[c];
                if (x == 0)
                    sum[x][y] = sum1;
                else
                    sum[x][y] = sum[x - 1][y] + sum1;
            }
        }
        int l = 2 * window_size + 1;    //套公式计算
        for (int x = 0; x < H; x++) {
            for (int y = 0; y < W; y++) {
                int xt, xb, yl, yr;
                xt = x - window_size - 1;
                xb = x + window_size;
                yl = y - window_size - 1;
                yr = y + window_size;
                if (xt < 0)
                    xt = 0;
                if (xb >= H)
                    xb = H - 1;
                if (yl < 0)
                    yl = 0;
                if (yr >= W)
                    yr = W - 1;
                output.at<Vec3b>(x, y)[c] = saturate_cast<uchar>((sum[xb][yr] + sum[xt][yl] - sum[xb][yl] - sum[xt][yr]) / (l * l));
            }
        }
    }

}

void modify1(int, void *) {
    image = imread("C:\\Users\\15339\\Desktop\\2.png");
    Gaussian(image, image2, (double) b);
    imshow("E3_1", image2);
}

void modify2(int, void *) {
    image = imread("C:\\Users\\15339\\Desktop\\2.png");
    MeanFilter(image, image2, k);
    imshow("E3_2", image2);
}

void modify3(int, void *) {
    image = imread("C:\\Users\\15339\\Desktop\\2.png");
    image2 = Mat::zeros(image2.size(), image2.type());
    boxFilter(image, image2, -1, Size(l, l));
    imshow("E3_3", image2);
}

void lab1() {
    namedWindow("E3_1", CV_WINDOW_AUTOSIZE);
    createTrackbar("Gaussian", "E3_1", &b, 10, modify1);
    modify1(0, 0);
}

void lab2() {
    namedWindow("E3_2", CV_WINDOW_AUTOSIZE);
    createTrackbar("MeanFilter", "E3_2", &k, 10, modify2);
    modify2(0, 0);
}

void lab3() {
    namedWindow("E3_3", CV_WINDOW_AUTOSIZE);
    createTrackbar("boxFilter", "E3_3", &l, 10, modify3);
    modify3(0, 0);
}


int main() {
    clock_t start, finish;
    start = clock();
    lab2();
    finish = clock();
    cout << finish - start << endl;
    waitKey();

}