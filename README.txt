COMP 2401 

Final Project 

Darsh Vikas Patel (101323400)

Vipra Hareshbhai Gajera (101271761)



##PURPOSE

The purpose of this project is to build a program in C which is a full communication stimulation where we are creating a house comprising of different rooms and a ghost that wanders in the house leaving evidence of different types and 4 hunters that enter the house and go into different rooms looking for evidence. This stimulation ends with either the hunters winning (upon finding the right set of evidence) or the ghost winning (upon scaring all the hunters)

This project makes use of a lot of C concepts such as static allocation, dynamic allocation, different data structures like linked lists and array, pointers and multi threading. There will be 1 ghost thread and 4 hunter threads running at the same time accessing different functions at random which reflect different actions like moving, leaving evidence and doing nothing. A Ghost can either move between rooms (if a hunter is not present in the room), leave evidence or do nothing. Similarly, a hunter can move around rooms, collect evidence and review collected evidence. We also have a bore counter for the ghost and a bore and fear counter for the hunters that gets updated according to how many times hunters and the ghost end up together in a room.



## LIST OF FILES

- main.c - 

This file contains the main functions and the main threads for the ghost and the 4 hunters. The main function will initialize the house, rooms and the ghost and take input for the hunters and then run 5 threads which will choose to apply different functions selected randomly. 


- house.c -

 This file contains functions to initialize the house,  create rooms at the start of the stimulation, add the rooms to the house, a function to connect specific rooms to each other inside the house and initialize a shared evidence list for the hunters to share. It also contains functions to clean up the house containing different function deallocating dynamic memory and a function for cleaning up the shared evidence lis t

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

- CHATGPT.txt - 

This file contains the details of use of AI for the assignment If any.

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



## AI USAGE 

There is a separate document attached called ChatGPT.txt outlining all the places AI was used in this assignment. 



          








