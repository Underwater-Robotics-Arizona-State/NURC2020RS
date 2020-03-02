#include <ros.h>									 //ROS LIBRARY
#include <std_msgs/Float64>							 //FLOAT 64 FOR DEPTH VALUES
#include <Wire.h>									 //WIRE LIBRARY FOR I2C
#include "MS5837.h"									 //DEPTH SENSOR LIBRARY

ros::NodeHandle nh;									 //CREATE NODE HANDLE OBJECT FOR PUBLISHING FLOAT VALUES

std_msgs::Float32 depth_val;						 //CREATE FLOAT VALUE VARIABLE TO PUBLISH TO ROSTOPIC

ros::Publisher depth_info("depth_vals", &depth_val); //CREATE PUBLISHER OBJECT THAT PUBLISHES TO "depth_vals" ROSTOPIC

MS5837 sensor;										 //CREATE SENSOR OBJECT FOR DEPTH SENSOR

void setup()
{
	nh.initNode();
	nh.advertise(depth_info);

	Wire.begin();			  						//BEGIN WIRE TRANSMISSION

	while (!sensor.init())							//CHECK FOR DEPTH SENSOR TO CONNECT BEFORE CONTINUING
	{
		delay(5000);
	}
	sensor.setModel(MS5837::MS5837_30BA); 			//SET MODEL OF DEPTH SENSOR
	sensor.setFluidDensity(997);		  			//kg/m^3 (997 FOR FRESHWATER, 1029 FOR SEAWATER)
}

void loop()
{
	sensor.read();
	depth_val.data = sensor.depth(); 				//GET DEPTH SENSOR DEPTH VALUE

	nh.spinOnce();

	if (depth_val != NULL)
	{
		depth_info.publish(&depth_val); 			//PUBLISH DEPTH VALUES
	}
	delay(500);										//WAIT 0.5 SECONDS (WILL BE DEPRECATED FOR ACTUAL USE)
}
