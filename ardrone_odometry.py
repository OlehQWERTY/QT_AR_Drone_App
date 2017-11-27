#!/usr/bin/env python

import roslib
import rospy

roslib.load_manifest('test1')

from nav_msgs.msg import Odometry
from std_msgs.msg import Int32

odometryData = ''
#x_pos = 0.0
#y_pos = 0.0
#z_pos = 0.0

def ReceiveData(data):
	global odometryData
	odometryData = (str(int(data.header.stamp.to_sec())) + ',' + str(data.pose.pose.position.x) + ',' + str(data.pose.pose.position.y) + ',' + str(data.pose.pose.position.z))


rospy.init_node('subscriber_test1_and_ardrone_odometry')

sub_Odometry = rospy.Subscriber('/ardrone/odometry', Odometry, ReceiveData)

r = rospy.Rate(1) # 1hz
while not rospy.is_shutdown():
  	print odometryData + '\n'
	f = open('odometryData.txt', 'w')
	f.write(odometryData + '\n')#+ '\n'
	f.close()

	r.sleep()
