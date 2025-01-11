#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

// 主函数
int main() {
    string template_image_path = "image/8.JPG"; // 模板图像路径
    string image_folder_path = "image";          // 图像文件夹路径


    // 检查路径是否存在
    if (!fs::exists(template_image_path)) {
        cerr << "模板图像路径不存在: " << template_image_path << endl;
        return -1;
    }
    if (!fs::exists(image_folder_path) || !fs::is_directory(image_folder_path)) {
        cerr << "图像文件夹路径不存在或不是一个文件夹: " << image_folder_path << endl;
        return -1;
    }

    // 读取模板图像
    Mat template_image = imread(template_image_path, IMREAD_COLOR);
    if (template_image.empty()) {
        cerr << "无法读取模板图像: " << template_image_path << endl;
        return -1;
    }

    // 将模板图像转换为灰度图
    Mat template_gray;
    cvtColor(template_image, template_gray, COLOR_BGR2GRAY);

    // 获取模板图像的宽度和高度
    int templ_width = template_gray.cols;
    int templ_height = template_gray.rows;

    // 遍历文件夹中的所有图像
    vector<pair<string, double>> matches; // 存储匹配结果 (文件名, 相似度)

    for (const auto& entry : fs::directory_iterator(image_folder_path)) {
        if (entry.is_regular_file()) {
            string file_path = entry.path().string();
            string filename = entry.path().filename().string();

            // 读取图像
            Mat img = imread(file_path, IMREAD_COLOR);
            if (img.empty()) {
                cerr << "无法读取图像: " << file_path << endl;
                continue;
            }

            // 将源图像转换为灰度图
            Mat img_gray;
            cvtColor(img, img_gray, COLOR_BGR2GRAY);

            // 打印源图像尺寸
            cout << "处理图像: " << filename << " | 尺寸: " << img_gray.cols << "x" << img_gray.rows << endl;

            // 检查模板是否比源图像大
            if (templ_width > img_gray.cols || templ_height > img_gray.rows) {
                cerr << "模板图像比源图像大，跳过图像: " << filename << endl;
                continue;
            }

            // 创建结果矩阵
            int result_cols = img_gray.cols - templ_width + 1;
            int result_rows = img_gray.rows - templ_height + 1;
            Mat result;
            result.create(result_rows, result_cols, CV_32FC1);

            // 进行模板匹配
            matchTemplate(img_gray, template_gray, result, TM_CCOEFF_NORMED);

            // 找到最佳匹配位置和相似度
            double minVal, maxVal;
            Point minLoc, maxLoc;
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

            // 使用 TM_CCOEFF_NORMED 方法时，maxVal 是最佳匹配
            double similarity = maxVal;

            // 存储匹配结果
            matches.emplace_back(filename, similarity);

            // 输出处理信息
            cout << "Processed: " << filename << " | Similarity: " << similarity << endl;

            // //在源图像上绘制匹配区域并显示
            // Rect match_region(maxLoc.x, maxLoc.y, templ_width, templ_height);
            // Mat img_result = img.clone();
            // rectangle(img_result, match_region, Scalar(0, 255, 0), 2, 8, 0);
            // imshow("Match - " + filename, img_result);
            // waitKey(0); // 按任意键继续
            // destroyWindow("Match - " + filename);
        }
    }

    // 排序匹配结果，按照相似度从高到低
    sort(matches.begin(), matches.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });

    // 输出前10个最匹配的结果
    cout << "\nTop 10 matches:" << endl;
    for (size_t i = 0; i < min(matches.size(), size_t(10)); ++i) {
        cout << i + 1 << ". " << matches[i].first << " | Similarity: " << matches[i].second << endl;
    }

    return 0;
}
