# GhostBusters





## Project Overview:

This project, developed as the final project (made in teams of 2) for Systems programming class , is a multi-threaded simulation of a ghost hunt within a house. The simulation involves four hunters equipped with devices to detect evidence, a ghost that moves between rooms and leaves evidence, and rooms connected in a layout resembling the "Willow Street House" from Phasmaphobia. The code extensively utilizes concepts from systems programming, including dynamically and statically allocated memory, linked lists, static arrays of pointers, multi-threaded programming using pthread, and Makefiles for compilation.

## Functionality:

The program creates a house layout with interconnected rooms and simulates the movement and actions of the ghost and hunters within these rooms. Each hunter has specific actions they can take, including collecting evidence, reviewing shared evidence, and moving between connected rooms. The ghost moves, leaves evidence, and monitors its boredom level. Logging for every action and event is facilitated via logger.c, providing comprehensive tracking of the simulation's progression.

## Implemented Concepts:

The code implements dynamically and statically allocated memory management, utilizing linked lists for room connections, semaphore-based synchronization to manage shared data between threads, and pthread functions for multi-threaded behavior of the ghost and individual hunters. Makefiles are used to compile the code, and thorough documentation is provided for each function, adhering to good design principles. The program's modularity is emphasized with 15-35 reusable functions, encapsulating specific functionalities for extended program use.


## LIST OF FILES

- main.c - 

This file contains the main functions and the main threads for the ghost and the 4 hunters. The main function will initialize the house, rooms and the ghost and take input for the hunters and then run 5 threads which will choose to apply different functions selected randomly. 


- house.c -

 This file contains functions to initialize the house,  create rooms at the start of the stimulation, add the rooms to the house, a function to connect specific rooms to each other inside the house and initialize a shared evidence list for the hunters to share. It also contains functions to clean up the house containing different function deallocating dynamic memory and a function for cleaning up the shared evidence list

- ghost.c -

This file contains all functions related to the ghost such as initialization  and all the different actions that a ghost can perform such as move, leave evidence and do nothing. It also contains a function checking if a ghost is present in a room.

- room.c - 

This contains all the functions relating to the the rooms of the house such as initialization, initializing all the fields of the room   structure as the connected rooms, list of hunters in the room, the evidence list as well as the functions to clean up all the fields of the stuct that were dynamically allocated at the end of the program . 

- hunter.c - 

This file contains all the function relating to the hunter such as initialization and all the actions that a hunter can perform such as 
Moving, collecting evidence and reviewing the evidence collected. It also contains a function placing them in the van at the start of the program and a function that detects if a hunter is in a particular room. 

- logger.c 

This file was already provided with functions to log every actions performed by the ghost and the hunters. This file has not been changed.

- utils.c - 

This file was already provided containing  some helper functions like randInt and EvidencetoString that we have use din our program. This file has also not been changed 

- defs.h - 

 This file contains all the forward declarations to functions we will use in all files, and all the structures that will be used and the constants that would be used as well.

- README.txt - 

This text file contains the explanation on what the purpose of the code is and how to compile and run the code, the list of files in the folder and student name and id of the students in the group. 


- MakeFile 

This file takes care of compiling the program by separating compiling and linking of the code with a clean target to remove object files and executables.



## COMPILING - 


Step 1 - 


Download the zip file from submissions (you can save the file on desktop for example). 
Next, open the terminal and go to the directory where the file has been saved. Then we 
Will unzip the file using the command - 

              unzip COMP2401_PATEL_DARSH_101323400_GAJERA_VIPRA_101271761_Final_Project.zip


Step 2 - 

After unzipping the file navigate to the directory containing all the files (for eg. If the file is stored in the desktop then move to desktop directory by doing command - cd Desktop)

Step 3- 


Next we will compile the code. We have a Makefile so all we have to do to compile is write the command - 

 make

This command will access the makeFile which will check and compile all the files to run the program, If you want to get rid of of all the object files and executables,  you can use the command 

clean make


Step 4- 

To run the file, simply write the command - 

./fp

However if you want to run it with valgrind you can also do -

 valgrind ./fp

If we want the detailed version of valgrind we can also do the command - 

 valgrind --leak-check=full ./fp


## USAGE INSTRUCTIONS

Upon running the code, the house and the ghost will be initialized and the user will be asked for input for the name of all 4 hunters. Once all 4 names have been entered, the stimulation will start where all 5 threads (1 for ghost and 4 for hunters) will run and perform different actions on random and the actions will be printed on the screen one by one. And once all the actions are done, the program will print who the winner of the game was and their reason for winning. It will also print of any hunter exited and the reason why. 






