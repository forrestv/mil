#include <ros/ros.h>
#include <vector>
#include <algorithm>
#include <navigator_msgs/DockShapes.h>
#include <navigator_msgs/GetDockShape.h>
#include <navigator_msgs/GetDockShapes.h>
#include "TrackedShape.h"

using namespace std;
class ShapeTracker
{
  private:
    ros::ServiceServer getShapesService;
    ros::Publisher allFoundShapesPublish;
    vector<TrackedShape> shapes;
    bool active;
    static bool validRequest(string& color, string& shape);
  public:
    ShapeTracker();
    void setActive(bool a);
    bool getShapesCallback(navigator_msgs::GetDockShapes::Request &req,navigator_msgs::GetDockShapes::Response &res);
    void init(ros::NodeHandle& nh);
    void addShape(navigator_msgs::DockShape& s);
    void addShapes(navigator_msgs::DockShapes& newShapes);
};
