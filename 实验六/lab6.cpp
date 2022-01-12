#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int sum_r[1000][1000][300];


void modify(Mat input, Mat output) {

    int theta, y0, x0, y_r, x_r;
    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {
            if (input.at<uchar>(x, y) != 0)
            for (int r = 50; r < 150; r += 3) {
                y0 = x0 = -1;
                for (theta = 0; theta < 360; theta += 3) {
                    x_r = (int) x - r * cos(theta * CV_PI / 180);
                    y_r = (int) y - r * sin(theta * CV_PI / 180);
                    if (y_r > 0 && y_r < output.cols && x_r > 0 && x_r < output.rows && y0 != y_r && x0 != x_r) {
                        sum_r[y_r][x_r][r]++;
                        y0 = y_r;
                        x0 = x_r;
                    }
                }
            }
        }
    }
    for (int i = 0; i < output.rows; i+=3) {
        for (int j = 0; j < output.cols; j+=3) {
            for (int r = 50; r < 150; r += 3) {
                if (sum_r[i][j][r] > 25)
                    circle(output, Point(i, j), r, Scalar(0, 0, 255), 1);
            }
        }
    }

    imshow("3", output);
}




int main() {
    Mat imge = imread("C://Users//15339//Desktop//Natural Image Dataset//6.jpg");
    Mat input, edge;
    cvtColor(imge, input, COLOR_BGR2GRAY);
    GaussianBlur(input, input, Size(3, 3), 3, 3);
    Canny(input, edge, 60, 160);
    modify(edge,imge);
    waitKey(0);
    return 0;
}
