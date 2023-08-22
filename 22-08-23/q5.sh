#!/bin/bash

while true; do
	echo "Enter : "
	echo "1. For Number of Active users"
	echo "2. For displaying number of lines from top of file"
	echo "3. For Updating access time of file to current time"
	echo "4. For Exit"
	read -p "Enter your choice: " choice
	
	case $choice in 
		1) 
			active_users=$(who | wc -l)
			echo "Active users : $active_users\n"
			;;
		2)
			read -p "Enter filename : " filename
			read -p "Enter number of lines to display : " num
			if [ -f filename ]; then
				echo "Top $num lines from $filename : "	
				head -n $num "$filename"
				echo "\n"
			else
				echo "File not found!\n"	
			fi
			;;
		3)
			read -p "Enter filename : " filename
			if [ -f filename ]; then
				touch "$filename"
				echo "Access time updated succesfully\n"
			else
				echo "File not found!\n"	
			fi
			;;
		4)
			echo "Exiting program\n"
			exit 0
			;;
		*)
			echo "INVALID CHOICE!\n"
			;;
	esac
done	
		
