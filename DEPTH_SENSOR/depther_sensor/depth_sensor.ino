#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <Wire.h>

ros::NodeHandle nh;

void callback_func(const std_msgs::String& mesg)
{
   char c = Wire.read(); 
   Serial.println(c);
}


ros::Publisher depth_info("depth_sensor", &mesg);


void setup()
{
   
   nh.initNode();
   
   nh.advertise(depth_info);
   
   int count =0;
   
   Serial.begin(9600);

}


void loop()
{
   
   count++;
   
   mesg = "Hello" + count.str();
   
   depth_info.publish(&mesg);
   
   nh.spinOnce();
   
   Serial.println(mesg);
   
   delay(500);
  
}
