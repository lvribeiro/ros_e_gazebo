// biblioteca padrão para classes do ROS
#include <ros/ros.h>

int main(int argc, char **argv)
{
	// Inicializa o sistema do ROS
	ros::init(argc, argv, "hello_ros");
	
	// Estabelece este programam como nó do ROS
	ros::NodeHandle nh;
	
	// Envia uma mensagem de log
	ROS_INFO_STREAM("Hello ROS!");
	return 0;
}