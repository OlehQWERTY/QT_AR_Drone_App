#!/bin/bash
# connect to AR.Drone and start wifi script

echo 'Connecting to ardrone2_114574...'

gnome-terminal -e "nmcli c up id 'ardrone2_114574'" --window-with-profile=NAMEOFTHEPROFILE #ardrone2_114574

sleep 4 # waiting for conection to ardrone 

echo "./data/wifi.sh" | telnet 192.168.1.1

#connect to ArDronePC

echo 'Connecting to ArDronePC...'

gnome-terminal -e "nmcli c up id 'ArDronePC'" --window-with-profile=NAMEOFTHEPROFILE #ardrone2_114574

sleep 6 # waiting for conection to ardrone 

# roscore

echo 'Starting roscore...'

gnome-terminal -e "/opt/ros/indigo/bin/roscore"  --window-with-profile=NAMEOFTHEPROFILE

sleep 4 # waiting roscore launching

# start arduino ide

echo 'Launching Arduino...'

cd ~/arduino-1.8.3

gnome-terminal -e "./arduino"  --window-with-profile=NAMEOFTHEPROFILE # I can't write ./arduino & exit - start with closing terminal (arduino still working)

#start ardrone_autonomy

read -p "Are you ready (make shure that you have launched arduino serial monitor)? " -n 1 -r
echo    # (optional) move to a new line
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    exit 1
fi

ls --all

echo 'Launching ardrone...'
# script for launching ardrone_autonomy
gnome-terminal -e "bash /home/oleg/QT_AR_Drone_App/start\ script/ardrone_autonomy_start.sh"  --window-with-profile=NAMEOFTHEPROFILE

sleep 6

# gnome-terminal -e "rosrun ardrone_autonomy ardrone_driver -ip 10.42.0.5"  --window-with-profile=NAMEOFTHEPROFILE

# Python script start
echo 'Launching ardrone...'

cd ~/catkin_ws/src/test1/src

gnome-terminal -e "./ardrone_odometry.py"  --window-with-profile=NAMEOFTHEPROFILE

sleep 3

# my app start

cd ~/git/QT_AR_Drone_App/build-QT_AR_Drone_App-Desktop-Debug/

gnome-terminal -e "sudo ./QT_AR_Drone_App"  --window-with-profile=NAMEOFTHEPROFILE

# tum_ardrone start

echo 'Launching ardrone...'
# script for launching ardrone_autonomy
gnome-terminal -e "bash /home/oleg/QT_AR_Drone_App/start\ script/tum_ardrone_start.sh"  --window-with-profile=NAMEOFTHEPROFILE

sleep 4




# sleep 5

# gnome-terminal -e "ls --all"  --window-with-profile=NAMEOFTHEPROFILE

# sleep 5

# gnome-terminal -e ls catckin_ws  --window-with-profile=NAMEOFTHEPROFILE

# sleep 5

# gnome-terminal --window-with-profile=NAMEOFTHEPROFILE -e "ls --all" 

# nmcli c up id 'foxi'

# sleep 5

# nmcli c down id 'foxi'

# nmcli c up id 'ArDronePC' # connect to ArDronePC wifi