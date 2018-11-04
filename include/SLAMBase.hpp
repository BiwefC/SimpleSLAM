#ifndef __SLAMBASE_HPP__
#define __SLAMBASE_HPP__

// 各种头文件
// C++标准库
#include <fstream>
#include <vector>
#include <map>
using namespace std;

// Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/eigen.hpp>
// #include <opencv2/nonfree/nonfree.hpp>


// PCL
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

struct CAMERA_INTRINSIC_PARAMETERS
{
    double cx, cy, fx, fy, scale;
};

struct RESULT_OF_PNP
{
    cv::Mat rvec, tvec;
    int inlPoint;
};

class FRAME
{
public:
    int frameID;
    cv::Mat rgb, depth;
    cv::Mat desp;
    std::vector<cv::KeyPoint> feat;

    void ComputeFeatAndDesp(void);
};


PointCloud::Ptr Image2PointCloud(cv::Mat& rgb, cv::Mat& depth, CAMERA_INTRINSIC_PARAMETERS& camera);
cv::Point3f Point2dTo3d(cv::Point3f& point, CAMERA_INTRINSIC_PARAMETERS& camera);
RESULT_OF_PNP MatchAndRansac(FRAME& frame1, FRAME& frame2, CAMERA_INTRINSIC_PARAMETERS& camera);

#endif