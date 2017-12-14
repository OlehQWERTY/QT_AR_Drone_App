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

# start arduino ide (or next step)

# echo 'Launching Arduino...'

# cd ~/arduino-1.8.3

# gnome-terminal -e "./arduino"  --window-with-profile=NAMEOFTHEPROFILE # I can't write ./arduino & exit - start with closing terminal (arduino still working)

#############################################################################################

# simple YES or NO bash dialog

read -p "Is led 13 blinking? Make shure that you have launched arduino serial monitor (if you chose another start option with arduino IDE). " -n 1 -r
echo    # (optional) move to a new line
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    exit 1
fi

ls --all
#############################################################################################

# init com betwen PC and Arduino (or previous step) (arduino doesn't want to start data sending before wired connection between PC and Arduino started)
# || - i case if first command return error perform second command (&& - if first successful perform second ; - start bouth anyway)
# /dev/ttyACM0 or /dev/ttyACM1 usual connection name for arduino

echo -e "\x1b[32mConnection to ArduinoYun...\x1b[0m"

stty -F /dev/ttyACM0 raw ispeed 115200 ospeed 115200 -ignpar cs8 -cstopb -echo || stty -F /dev/ttyACM1 raw ispeed 115200 ospeed 115200 -ignpar cs8 -cstopb -echo # connection parameters

gnome-terminal -e "cat /dev/ttyACM0 || cat /dev/ttyACM1"  --window-with-profile=NAMEOFTHEPROFILE

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
