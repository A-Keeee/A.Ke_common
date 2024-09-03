#define BOOST_TYPEOF_EMULATION
#include <vtkAutoInit.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <boost/thread.hpp> 

int main()
{
	std::string filename = "src/thing.pcd";
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(filename, *cloud) == -1)
	{
		std::cout << "error to read point cloud" << std::endl;
		return -1;
	}
	
	/****显示点云****/
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("ShowCloud"));
	viewer->setBackgroundColor(0, 0, 0);

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 255, 255, 255);
	viewer->addPointCloud<pcl::PointXYZ>(cloud, single_color, "cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100000);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}

	return 0;
}



