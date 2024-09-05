#include <rclcpp/rclcpp.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/visualization/pcl_visualizer.h>

class PointCloudFilter : public rclcpp::Node
{
public:
    PointCloudFilter() : Node("pointcloud_filter")
    {
        // 加载点云数据
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);

        if (pcl::io::loadPCDFile<pcl::PointXYZ>("src/thing_three.pcd", *cloud) == -1)
        {
            RCLCPP_ERROR(this->get_logger(), "无法读取PCD文件");
            return;
        }
        RCLCPP_INFO(this->get_logger(), "加载了 %d 个点的数据", cloud->width * cloud->height);

        // 创建滤波器对象
        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
        sor.setInputCloud(cloud);
        sor.setMeanK(50);  // 设置考虑的临近点数
        sor.setStddevMulThresh(1.0); // 设置标准差阈值

        // 应用滤波器
        sor.filter(*cloud_filtered);
        RCLCPP_INFO(this->get_logger(), "保留了内部点的滤波点云");

        // 创建PCLVisualizer对象来显示点云
        pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
        viewer->setBackgroundColor(0, 0, 0);
        viewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "filtered cloud");
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "filtered cloud");
        viewer->addCoordinateSystem(1.0);
        viewer->initCameraParameters();

        // 保持窗口打开直到用户关闭
        while (!viewer->wasStopped())
        {
            viewer->spinOnce(100000);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PointCloudFilter>());
    rclcpp::shutdown();
    return 0;
}

