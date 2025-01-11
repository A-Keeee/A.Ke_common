#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
using namespace std;
using namespace cv;

// 函数：查找图像中的轮廓
vector<vector<Point>> findContoursInImage(const Mat& image)
{
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);  // 转为灰度图

    Mat thresh;
    threshold(gray, thresh, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);  // 二值化

    vector<vector<Point>> contours;
    findContours(thresh, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);  // 查找轮廓

    vector<vector<Point>> validContours;
    for (const auto& contour : contours)
    {
        double area = contourArea(contour);  // 计算轮廓面积
        if (area > 1000)  // 过滤小的轮廓
        {
            validContours.push_back(contour);
        }
    }

    return validContours;
}

// 函数：计算两幅图像的Hu矩匹配度
double calculateHuMomentsDistance(const vector<vector<Point>>& contours1, const vector<vector<Point>>& contours2)
{
    Moments m1 = moments(contours1[0]);
    Mat hu1;
    HuMoments(m1, hu1);

    Moments m2 = moments(contours2[0]);
    Mat hu2;
    HuMoments(m2, hu2);

    // 计算Hu矩之间的距离
    return matchShapes(hu1, hu2, CONTOURS_MATCH_I1, 0);
}

int main()
{
    string query_image_path = "src/8.JPG";  // 查询图像路径
    string image_folder_path = "image";  // 图像文件夹路径

    // 读取查询图像
    Mat query_image = imread(query_image_path);
    if (query_image.empty())
    {
        cout << "查询图像读取失败！" << endl;
        return -1;
    }

    // 查找查询图像的轮廓
    vector<vector<Point>> query_contours = findContoursInImage(query_image);
    if (query_contours.empty())
    {
        cout << "查询图像没有有效轮廓！" << endl;
        return -1;
    }

    double min_distance = DBL_MAX;
    string most_similar_image = "";

    // 遍历文件夹中的所有图像
    for (const auto& entry : std::filesystem::directory_iterator(image_folder_path))
    {
        if (entry.is_regular_file())
        {
            string file_path = entry.path().string();
            Mat img = imread(file_path);
            if (img.empty())
            {
                cout << "无法读取图像: " << file_path << endl;
                continue;
            }

            // 查找图像的轮廓
            vector<vector<Point>> img_contours = findContoursInImage(img);
            if (img_contours.empty())
            {
                continue;  // 跳过没有有效轮廓的图像
            }

            // 计算Hu矩匹配度（距离）
            double dist = calculateHuMomentsDistance(query_contours, img_contours);
            cout << "Processed: " << file_path << " | Distance: " << dist << endl;

            // 更新最相似图像
            if (dist < min_distance)
            {
                min_distance = dist;
                most_similar_image = file_path;
            }
        }
    }

    // 输出最相似的图像
    if (!most_similar_image.empty())
    {
        cout << "最相似的图像: " << most_similar_image << " | 最小距离: " << min_distance << endl;

        // 显示最相似的图像
        Mat similar_image = imread(most_similar_image);
        imshow("Most Similar Image", similar_image);
        waitKey(0);
    }
    else
    {
        cout << "没有找到相似的图像！" << endl;
    }

    return 0;
}
