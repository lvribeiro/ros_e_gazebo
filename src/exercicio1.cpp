#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;
double destX;
double destY;

double curX, curY, curDir;
void poseCB(const turtlesim::Pose& msg){
	curX = msg.x;
	curY = msg.y;
	curDir = msg.theta;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "exercicio1");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, &poseCB);

	double max_vel;
	ros::param::get("~max_vel", max_vel);
	ROS_INFO_STREAM("Velocidade maxima configurada para " << max_vel);

	ros::Rate rate(100);
	geometry_msgs::Twist msg;
	while (ros::ok()){
		cout << "Entre com o destino X Y\n";
		cin >> destX >> destY;	
		while (ros::ok()){
			double dx, dy, dist, theta, z;
			ros::spinOnce();
			dx = destX - curX;
			dy = destY - curY;
			dist = hypot(dx, dy); // distancia ate destino
			theta = atan2(dy,dx); // orientacao [0-2pi]	 
			z = theta - curDir; // correcao necessaria

			if (dist < 0.1) break;

			msg.linear.x = (dist > 1? max_vel : max_vel/2.0);
			msg.angular.z = z;

			pub.publish(msg);
			rate.sleep();
		}
	}
	return 0;
} 