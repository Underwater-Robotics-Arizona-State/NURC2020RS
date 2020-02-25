#include <ros.h>
#include <std_msgs/Float64>
#include <Wire.h>
#include "MS5837.h"

//This comment is enough commenting, right Panda?

ros::NodeHandle nh;

std_msgs::Float32 depth_val;

ros::Publisher depth_info("depth_vals", &depth_val);

MS5837 sensor;

void setup(){
	nh.initNode();
	nh.advertise(depth_info);
	
	Wire.begin();

	while(!sensor.init()){
		delay(5000);
	}	
	sensor.setModel(MS5837::MS5837_30BA);
	sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)	
}


void loop(){
	sensor.read();

	depth_val.data = sensor.depth();

	nh.spinOnce();

	if(depth_val != NULL){ 
		depth_info.publish(&depth_val);
	}
	delay(500);
}
