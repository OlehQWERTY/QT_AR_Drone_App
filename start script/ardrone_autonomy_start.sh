#!/bin/bash
source /opt/ros/indigo/setup.bash
bash rosrun ardrone_autonomy ardrone_driver -ip 10.42.0.5 #"/opt/ros/indigo/bin/roscore"

exec $SHELL
