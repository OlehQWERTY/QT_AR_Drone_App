#!/bin/bash

#############################################################################################

# connect to AR.Drone and start wifi script

echo -e "\x1b[32mConnecting to ardrone2_114574...\x1b[0m" # echo -e "\x1b[31mTest\x1b[0m" - Test red color 

gnome-terminal -e "nmcli c up id 'ardrone2_114574'" --window-with-profile=NAMEOFTHEPROFILE #ardrone2_114574

sleep 4 # waiting for conection to ardrone 

echo "./data/wifi.sh" | telnet 192.168.1.1

#############################################################################################

#connect to ArDronePC

echo -e "\x1b[32mConnecting to ArDronePC...\x1b[0m"

gnome-terminal -e "nmcli c up id 'ArDronePC'" --window-with-profile=NAMEOFTHEPROFILE #ardrone2_114574

sleep 6 # waiting for conection to ardrone 

#############################################################################################

# roscore

echo -e "\x1b[32mStarting roscore...\x1b[0m"

gnome-terminal -e "/opt/ros/indigo/bin/roscore"  --window-with-profile=NAMEOFTHEPROFILE

sleep 4 # waiting roscore launching

#############################################################################################

#start ardrone_autonomy

echo -e "\x1b[32mLaunching ardrone_autonomy...\x1b[0m"

# script for launching ardrone_autonomy
gnome-terminal -e "bash /home/oleg/QT_AR_Drone_App/start\ script/ardrone_autonomy_start.sh"  --window-with-profile=NAMEOFTHEPROFILE

sleep 6

#############################################################################################

# Python script start

echo -e "\x1b[32mLaunching ardrone_odometry.py...\x1b[0m"

cd ~/catkin_ws/src/test1/src

gnome-terminal -e "./ardrone_odometry.py"  --window-with-profile=NAMEOFTHEPROFILE

sleep 3

#############################################################################################

# tum_ardrone start

echo -e "\x1b[32mLaunching tum_ardrone...\x1b[0m"

# script for launching ardrone_autonomy
gnome-terminal -e "bash /home/oleg/QT_AR_Drone_App/start\ script/tum_ardrone_start.sh"  --window-with-profile=NAMEOFTHEPROFILE

sleep 4

#############################################################################################

# my app start

echo -e "\x1b[32mMy app launching...\x1b[0m"

cd ~/git/QT_AR_Drone_App/build-QT_AR_Drone_App-Desktop-Debug/

gnome-terminal -e "sudo ./QT_AR_Drone_App"  --window-with-profile=NAMEOFTHEPROFILE

#############################################################################################
