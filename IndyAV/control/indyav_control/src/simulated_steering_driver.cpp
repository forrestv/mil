#include <indyav_control/simulated_steering_driver.hpp>
#include <std_msgs/Float64.h>


template<class MSG>
SimulatedSteeringDriver<MSG>::SimulatedSteeringDriver(ros::NodeHandle* _nh,
                                                      const std::string& sub_topic)
{

  nh_ = _nh;

  sub_ = nh_->subscribe(sub_topic, 1, &SimulatedSteeringDriver::Callback, this);

  //get all the controllers from the ros params
  std::string name = "/car";
  ROS_ASSERT_MSG(ros::param::has(name), "no car param namspace");
  name += "/simulated_hardware_controllers";
  ROS_ASSERT_MSG(nh_->hasParam(name), "no simualted hardware controllers param namspace");
  name += "/steering";
  ROS_ASSERT_MSG(nh_->hasParam(name), "no steering param namspace");

  auto left_name = name + "/left";
  ROS_ASSERT_MSG(ros::param::has(left_name), "no left controller");
  pubs_[left_name] = nh_->advertise<std_msgs::Float64>(left_name + "/command", 5);

  auto right_name = name + "/right";
  ROS_ASSERT_MSG(ros::param::has(right_name), "no right controller");
  pubs_[right_name] = nh_->advertise<std_msgs::Float64>(right_name + "/command", 5);

}

template<class MSG>
void SimulatedSteeringDriver<MSG>::Callback(const MSG& _msg)
{
  double cmd_angle = _msg.steering_angle;
  for(auto i = pubs_.begin(); i != pubs_.end(); ++i)
  {
    //TODO: impliment ackerman steering angles
    std_msgs::Float64 msg;
    msg.data = cmd_angle;
    i->second.publish(msg);
  }
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "simulated_steering_driver");
  ros::NodeHandle nh("~");
  std::string input_topic;
  ROS_ASSERT_MSG(nh.getParam("input_topic", input_topic), "No input topic specified");
  auto a = SimulatedSteeringDriver<indyav_control::SteeringStamped>(&nh, input_topic);
  ros::spin();
  return 0;
}


