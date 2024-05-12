#!/bin/bash
gnome-terminal --geometry 50x10+1050+10 -- bash config.sh & sleep 5
gnome-terminal --geometry 50x10+1050+10 -- bash ServoControl.sh & sleep 1

