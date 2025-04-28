# CS300 portfolio - Reflection of Project 1 and Project 2

## What was the problem you were solving in the projects for this course?
ABCU needed a program for academic advisors to look up courses and their prerequisites. The main tasks were loading data, listing courses in order, and finding specific course info.

## How did you approach the problem? Consider why data structures are important to understand.
I chose a Binary Search Tree because it keeps data sorted automatically, making it efficient to print in order. Also, searching is faster than a list. Data structures are important because picking the right one makes the program work smoothly, especially with lots of data. If you use the wrong structure, things can get slow or complicated.

## How did you overcome any roadblocks you encountered while going through the activities or project?
When I first tried inserting courses into the BST, sometimes it didn't sort right. I had to check how the insertion worked, making sure each course was compared correctly by their course numbers. Also, handling user input errors was tricky, like when someone enters a wrong file name. Adding checks for file opening and input validation helped fix that.

## How has your work on this project expanded your approach to designing software and developing programs?
This project made me think more about planning before coding. Using a BST required setting up the structure properly from the start. I also learned to break the problem into smaller parts, like separating the BST logic from file handling and the user interface. It's easier to manage that way.

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
I leaned hard into comments and modular functions. Instead of one giant chunk of code, things like trim(), split(), and displayCourse() became reusable tools. Naming variables clearly (like courseNumber instead of cn) also made the code self-documenting.


