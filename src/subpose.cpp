#include <ros/ros.h>
#include <turtlesim/Pose.h>

void poseMessageReceived(const turtlesim::Pose &msg)
{
	ROS_INFO("Position = (%.2lf, %.2lf) Direction = %.2lf", msg.x, msg.y, msg.theta);
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "subscribe_to_pose");
	ros::NodeHandle nh;
	
	ros::Subscriber sub = nh.subscribe("turtle1/pose", 10, poseMessageReceived);

	ros::spin();
	return 0;
}