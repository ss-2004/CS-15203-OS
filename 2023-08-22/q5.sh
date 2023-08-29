#!/bin/bash

#Write a menu driven shell script for the following options:
#i. Number of presently active users
#ii. Displaying some desired number of lines from top of a file
#iii. Updating the access time of a given file to current time
#If the user gives some invalid choice, it should prompt “Invalid option” message.

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
        echo "Active users : $active_users"
        echo
        ;;
    2)
        read -p "Enter filename : " filename
        read -p "Enter number of lines to display : " num
        if [ -f "$filename" ]; then
            echo "Top $num lines from $filename : "
            head -n $num "$filename"
            echo
        else
            echo "File not found!"
            echo
        fi
        ;;
    3)
        read -p "Enter filename : " filename
        if [ -f "$filename" ]; then
            touch "$filename"
            echo "Access time updated succesfully!"
            echo
        else
            echo "File not found!"
            echo
        fi
        ;;
    4)
        echo "Exiting program"
        echo
        exit 0
        ;;
    *)
        echo "INVALID CHOICE!"
        echo
        ;;
    esac
done
