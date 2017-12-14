#!/bin/bash
source /opt/ros/indigo/setup.bash
bash roslaunch tum_ardrone tum_ardrone.launch

exec $SHELL
