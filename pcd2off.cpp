// STL
#include <iostream>
#include <fstream>
#include <string>

// PCL 
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>

int main (int argc, char** argv)
{
  // Load input file into a PointCloud<T> with an appropriate type
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
  pcl::io::loadPCDFile (argv[1], *cloud);
  //* the data should be available in cloud

  std::cout << "Pre size with NAN: " << cloud->points.size () << std::endl;  
  std::vector<int> indices;
  pcl::removeNaNFromPointCloud(*cloud, *cloud, indices);
  std::cout << "Post size with out NAN: " << cloud->points.size () << std::endl;

  std::cerr << "Saved " << cloud->points.size () << " data points to test_pcd.pcd." << std::endl;
  pcl::io::savePCDFileASCII("clean_file.pcd",*cloud);

  std::ofstream file;
  std::string s = strtok(strtok(argv[1], "."),"/");
  std::cout << "token: " << s << std::endl;
  file.open(s+".off");
  file << "OFF\n";
  file << std::to_string(cloud->points.size ());
  file << "\t";
  file << "0\t";
  file << "0\n";
  for (size_t i = 0; i < 4; ++i)
  {
    file << cloud->points[i].x;
    file << "\t";
    file << cloud->points[i].y;
    file << "\t";
    file << cloud->points[i].z;
    file << "\n";
  }
  file.close();

  return 0;
}