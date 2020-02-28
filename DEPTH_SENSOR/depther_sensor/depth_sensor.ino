#include <ros.h>					//IMPORT ROS LIBRARY
#include <std_msgs/Float64>				//IMPORT ROS MESSAGES FLOAT 64 FOR DEPTH VALUES
#include <Wire.h>					//IMPORT WIRE LIBRARY FOR I2C
#include "MS5837.h"					//IMPORT DEPTH SENSOR LIBRARY
							//
ros::NodeHandle nh;					//CREATE NODE HANDLE OBJECT FOR PUBLISHING FLOAT VALUES
							//
std_msgs::Float32 depth_val;				//CREATE FLOAT VALUE VARIABLE TO PUBLISH TO ROSTOPIC
							//
ros::Publisher depth_info("depth_vals", &depth_val);	//CREATE PUBLISHER OBJECT THAT PUBLISHES TO "depth_vals" ROSTOPIC
							//
MS5837 sensor;						//CREATE SENSOR OBJECT FOR DEPTH SENSOR
							//
void setup(){						//ARDUINO SETUP FUNCTION
	nh.initNode();					//INITIALIZE ROS NODE
	nh.advertise(depth_info);			//ADVERTISE ROS NODE
							//
	Wire.begin();					//BEGIN WIRE TRANSMISSION
							//
	while(!sensor.init()){				//CHECK FOR DEPTH SENSOR
		delay(5000);				//WAIT 5 SECONDS BEFORE TRYING AGAIN
	}						//
	sensor.setModel(MS5837::MS5837_30BA);		//SET MODEL OF DEPTH SENSOR
	sensor.setFluidDensity(997); 			//kg/m^3 (freshwater, 1029 for seawater)	
}							//
							//
void loop(){						//ARDUINO LOOP FUNCTION
	sensor.read();					//UPDATE SENSOR VALUES
							//
	depth_val.data = sensor.depth();		//GET DEPTH SENSOR DEPTH VALUE
							//
	nh.spinOnce();					//SPIN ROS NODE HANDLER
							//
	if(depth_val != NULL){ 				//CHECK IF 'depth_val' IS NULL
		depth_info.publish(&depth_val);		//PUBLISH DEPTH VALUES
	}						//
	delay(500);					//WAIT 0.5 SECONDS (WILL BE DEPRECATED FOR ACTUAL USE)
}							//
