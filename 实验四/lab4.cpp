#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


bool g_bDrawing = false;
int f[5][10000];
int b[5][10000];
int sum_f[5][258], sum_b[5][258];
int sum1 = 0, sum2 = 0;
long long s[10000][10000];
long long ss[10000][10000];
Point g_nCurrPoint;

void onMouse(int event, int x, int y, int flag, void *) {
    //Mat &img = *(cv::Mat *) param;

    switch (event) {
        //移动鼠标的时候
        case CV_EVENT_MOUSEMOVE: {
            g_nCurrPoint = Point(x, y);

        }
            break;
            //点击鼠标左键时
        case CV_EVENT_LBUTTONDOWN: {
            g_bDrawing = true;
            g_nCurrPoint = Point(x, y);
        }
            break;
            //松开鼠标左键时
        case CV_EVENT_LBUTTONUP: {
            g_bDrawing = false;
        }
            break;
    }
}

void modify1() {
    Mat srcImage = imread("C:\\Users\\15339\\Desktop\\2.png");
    Mat tempImage;
    int c = srcImage.channels();
    srcImage.copyTo(tempImage);
    Mat input = imread("C:\\Users\\15339\\Desktop\\2.png");
    namedWindow("【鼠标事件窗口】", CV_WINDOW_AUTOSIZE);
    setMouseCallback("【鼠标事件窗口】", onMouse, &srcImage);


    char key;
    int k = 0;
    while (true) {
        if (g_bDrawing) {
            circle(srcImage, g_nCurrPoint, 0, Scalar(255, 0, 0), 10);
            if (s[g_nCurrPoint.x][g_nCurrPoint.y] == 0) {
                for (int i = 0; i < c; i++) {
//                    cout<<g_nCurrPoint.x<<endl;
//                    cout<<g_nCurrPoint.y<<endl;
                    f[i][k] = input.at<Vec3b>(g_nCurrPoint.x, g_nCurrPoint.y)[i];
//                    cout<<(input.at<Vec3b>(g_nCurrPoint.x, g_nCurrPoint.y)[i])<<endl;
                    sum_f[i][f[i][k]]++;
                    sum1++;
                }
                s[g_nCurrPoint.x][g_nCurrPoint.y] = 1;
                k++;
            }
        }
        imshow("【鼠标事件窗口】", srcImage);

        key = waitKey(2);
        if (key == '2') {
            //cout<<k<<endl;
            k = 0;
            break;
        }

        if (key == '1') {
            srcImage = imread("C:\\Users\\15339\\Desktop\\2.png");
        }
    }

    namedWindow("【鼠标事件窗口】", 0);
    setMouseCallback("【鼠标事件窗口】", onMouse, (void *) &srcImage);
    while (true) {
        if (g_bDrawing) {
            circle(srcImage, g_nCurrPoint, 0, Scalar(0, 255, 0), 10);
            if (ss[g_nCurrPoint.x][g_nCurrPoint.y] == 0) {
                for (int i = 0; i < c; i++) {
                    b[i][k] = input.at<Vec3b>(g_nCurrPoint.x, g_nCurrPoint.y)[i];
                    sum_b[i][b[i][k]]++;
                    sum2++;
                }
                ss[g_nCurrPoint.x][g_nCurrPoint.y] = 1;
                k++;
            }
        }
        imshow("【鼠标事件窗口】", srcImage);

        key = waitKey(2);
        if (key == '2') {
            k = 0;
            break;
        }

        if (key == '1') {
            srcImage = imread("C:\\Users\\15339\\Desktop\\2.png");
        }
    }

}

void modify2() {
    Mat input = imread("C:\\Users\\15339\\Desktop\\2.png");
    Mat output;
    int c = input.channels();
    output = Mat::zeros(input.size(), input.type());
    namedWindow("E4", CV_WINDOW_AUTOSIZE);
    //imshow("E4", output);
    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {
            double ff = 1, bb = 1;
            int o = 0;
            for (int i = 0; i < c; i++) {
                if (s[x][y] == 1)
                    output.at<Vec3b>(x, y)[i] = 255;
                else if (ss[x][y] == 1)
                    output.at<Vec3b>(x, y)[i] = 0;
                else {
                    o = 1;
                    double l1 = 0, l2 = 0;
                    int l = input.at<Vec3b>(x, y)[i];
                    l1 = (double) sum_f[i][l] / (double) sum1;
                    if (i == 1) {
                        ff = ff + l1;
                        l2 = (double) sum_b[i][l] / (double) sum2;
                        bb = bb + 0.6*l2;
                    } else {
                        ff = ff + 0.2 * l1;
                        l2 = (double) sum_b[i][l] / (double) sum2;
                        bb = bb + 0.2 * l2;
                    }
                }
            }
//            cout<<ff<<endl;
//            cout<<bb<<endl;
            if (o == 1) {
                if (ff <= bb) {
                    for (int i = 0; i < c; i++)
                        output.at<Vec3b>(x, y)[i] = 0;
                } else
                    for (int i = 0; i < c; i++)
                        output.at<Vec3b>(x, y)[i] = 255;
            }
        }
    }
    imshow("E4", output);
}

int main() {
    modify1();
    modify2();
//    cout<<sum1<<endl;
//    int lm=0;
//    for(int i=0;i<256;i++)
//        lm=lm+sum_f[1][i];
//    cout<<lm<<endl;
    waitKey();
    return 0;
}