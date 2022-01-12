#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int label[10000][10000];
int num = 0;
int uList[100000];
int Rank[100000];


void init(int n) {
    for (int i = 0; i <= n; i++) {
        uList[i] = i;
        Rank[i] = 1;
    }
}

int find(int x) {
    return x == uList[x] ? x : (uList[x] = find(uList[x]));
}

void merge(int i, int j) {
    int x = find(i);
    int y = find(j);
    if (Rank[x] <= Rank[y])
        uList[x] = y;
    else
        uList[y] = x;
    if (Rank[x] == Rank[y] && x != y)
        Rank[y]++;
}

void modify(Mat &input) {
    init(20000);
    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {
            int k = input.at<uchar>(x, y);
            if (k != 0) {
                if (x == 0)//第一行
                {
                    if (y == 0) {
                        num++;
                        label[x][y] = num;
                    } else {
                        int l = input.at<uchar>(x, y - 1);
                        if (l != 0)
                            label[x][y] = label[x][y - 1];
                        else {
                            num++;
                            label[x][y] = num;
                        }
                    }
                } else {
                    if (y == 0)//最左边   最左边的只需要和上面、右上的比较
                    {
                        int above = input.at<uchar>(x - 1, y);
                        int u_r = input.at<uchar>(x - 1, y + 1);
                        if (above != 0)
                            label[x][y] = label[x - 1][y];
                        else if (u_r != 0)
                            label[x][y] = label[x - 1][y + 1];
                        else {
                            num++;
                            label[x][y] = num;
                        }
                        if (above != 0 && u_r != 0 && (label[x - 1][y] != label[x - 1][y + 1]))//加入并查集
                            merge(label[x - 1][y], label[x - 1][y + 1]);

                    } else if (y == input.cols - 1)//最右边  最右边的只需要和左边、左上、上面的比较
                    {
                        int l = input.at<uchar>(x, y - 1);
                        int u_l = input.at<uchar>(x - 1, y - 1);
                        int above = input.at<uchar>(x - 1, y);
                        if (l != 0)
                            label[x][y] = label[x][y - 1];
                        else if (u_l != 0)
                            label[x][y] = label[x - 1][y - 1];
                        else if (above != 0)
                            label[x][y] = label[x - 1][y];
                        else {
                            num++;
                            label[x][y] = num;
                        }
                    } else//中间
                    {
                        int l = input.at<uchar>(x, y - 1);
                        int u_l = input.at<uchar>(x - 1, y - 1);
                        int above = input.at<uchar>(x - 1, y);
                        int u_r = input.at<uchar>(x - 1, y + 1);
                        if (l != 0 && u_r != 0) {               //如果左边和右上的都不为0
                            if (label[x][y - 1] <= label[x - 1][y + 1]) {//标记当前位置为最小的标记
                                label[x][y] = label[x][y - 1];
                            } else {
                                label[x][y] = label[x - 1][y + 1];
                            }
                            if (label[x][y - 1] != label[x - 1][y + 1])   //如果左边和右上的标记不是一样的，则加入并查集
                                merge(label[x][y - 1], label[x - 1][y + 1]);
                        } else if (u_l != 0 && u_r != 0) {             //如果左上和右上的都不为0
                            if (label[x - 1][y - 1] <= label[x - 1][y + 1]) {//标记当前位置为最小的标记
                                label[x][y] = label[x - 1][y - 1];
                            } else {
                                label[x][y] = label[x - 1][y + 1];
                            }
                            if (label[x - 1][y - 1] != label[x - 1][y + 1])//如果左上和右上的标记不是一样的，则加入并查集
                                merge(label[x - 1][y - 1], label[x - 1][y + 1]);
                        } else if (l != 0)
                            label[x][y] = label[x][y - 1];
                        else if (u_l != 0)
                            label[x][y] = label[x - 1][y - 1];
                        else if (above != 0)
                            label[x][y] = label[x - 1][y];
                        else if (u_r != 0)
                            label[x][y] = label[x - 1][y + 1];
                        else {
                            num++;
                            label[x][y] = num;
                        }
                    }
                }
            }
        }
    }
    cout<<"未合并时的连通域个数:" << num<<endl;
    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {
            label[x][y] = find(label[x][y]);  //合并连通域
        }
    }
    //cout<<label[input.rows-1][input.cols-1]<<endl;
    int label_sum[100000];
    int max_i = 0;
    int max = -1000;
    int sum1[100000];
    int sum = 0;
    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {
            if (label[x][y] != 0)  //记录每个连通域的面积
                sum1[label[x][y]]++;
            if (label[x][y] == find(label[x][y]) && label_sum[label[x][y]] == 0) {//统计总共有多少个连通域
                sum++;
                label_sum[label[x][y]]++;
            }
        }
    }
    for (int i = 0; i < 15000; i++) {//找到面积最大的连通域的标记
        if (max <= sum1[i]) {
            max = sum1[i];
            max_i = i;
        }
    }
    cout<<"最大面积的连通域标记为:"<<max_i<<endl;
    cout<<"总连通域:"<<sum-1<<endl;
    //Mat image = imread("C:\\Users\\15339\\Desktop\\horse_mask.png");
    Mat image = imread("C:\\Users\\15339\\Desktop\\1.png");
    Mat out;
    Mat gray_image;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    threshold(gray_image, out, 127, 255, THRESH_BINARY);
    Mat out1;
    out1 = Mat::zeros(out.size(), out.type());
    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {//输出最大面积的连通域
            if (label[x][y] == max_i)
                out1.at<uchar>(x, y) = 255;
        }
    }
    imshow("e", out1);
}

void ex1() {
    //Mat image = imread("C:\\Users\\15339\\Desktop\\horse_mask.png");
    Mat image = imread("C:\\Users\\15339\\Desktop\\1.png");
    Mat out;
    Mat gray_image;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    threshold(gray_image, out, 127, 255, THRESH_BINARY);
    modify(out);
    imshow("e1", out);
    waitKey();
}

void ex2() {
    Mat image = imread("C:\\Users\\15339\\Desktop\\hand.png");
    Mat out;
    Mat gray_image;
    cvtColor(image, gray_image, CV_BGR2GRAY);
    threshold(gray_image, out, 145, 255, THRESH_BINARY);
    Mat output;
    distanceTransform(out, output, DIST_L2, 3,CV_32F);
    normalize(output, output, 0, 1, NORM_MINMAX);
    imshow("hand", output);
    waitKey();
}

int main() {
    ex2();
}