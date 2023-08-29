#!/bin/bash

#Q4
#Write a menu driven shell script for the following options:
#i. Merging the contents of two files into another
#ii. Searching a pattern from a file
#If the user gives some invalid choice, it should prompt “Invalid option” message.

while true; do
    echo "Enter : "
    echo "1. For Merging two files"
    echo "2. For Searching pattern from file"
    echo "3. For Exit"
    read -p "Enter your choice: " choice

    case $choice in
    1)
        read -p "Enter 1st filename : " file1
        read -p "Enter 2nd filename : " file2
        read -p "Enter merged filename : " merged_file
        if [[ -f "$file1" ]] && [[ -f "$file2" ]]; then
            cat "$file1" "$file2" >"$merged_file"
            echo "$file1 & $file2 merged into $merged_file"
            echo
        else
            echo "File 1 OR 2 not found!"
            echo
        fi
        ;;
    2)
        read -p "Enter the filename : " file
        read -p "Enter pattern to search : " ptrn
        if [[ -f "$file" ]]; then
            if grep "$ptrn" "$file"; then
                echo "$ptrn found in $file"
                echo
            else
                echo "$ptrn NOT FOUND!"
                echo
            fi
        else
            echo "File not found!"
            echo
        fi
        ;;
    3)
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
