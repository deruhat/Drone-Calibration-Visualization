#include <iostream>
#include <string>
#include <sstream>
#include <ros/ros.h>
#include <geometry_msgs/Point.h>

using namespace std;

int main(int argc, char** argv){
	// ROS INITIALIZATION: announce node to ROS
	ros::init(argc, argv, "compassInput");
	ros::start();
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point>("data", 1000);
	ros::Rate loop_rate(10);
	geometry_msgs::Point point;
	float angle = 0;
	while(ros::ok())
	{
		ROS_INFO_STREAM("Please enter x to test the compass:");
		cin >> angle;
		point.x = angle;
		ROS_INFO_STREAM("Please enter y to test the compass:");
		cin >> angle;
		point.y = angle;
		ROS_INFO_STREAM("Please enter z to test the compass:");
		cin >> angle;
		point.z = angle;
		chatter_pub.publish(point);
		cout << endl << "You entered:-\n" << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << endl << endl;
	}
	ros::spin();
	ros::shutdown();
	return 0;
}
