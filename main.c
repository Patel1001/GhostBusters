//101271761 -  Vipra Hareshbhai Gajera
//101323400 -  Darsh Vikas Patel
#include "defs.h"

int main()
{
    // Initialize the random number generator
    srand(time(NULL));

    //initialising and populating the house
    HouseType house;
    initHouse(&house);
    populateRooms(&house);

    GhostType ghost;
    initGhost(&ghost,&house);

    for (int i = 0; i < NUM_HUNTERS ; i ++){
        char name[MAX_STR];
        printf("Enter name of hunter %d : ",i+C_1);
        scanf("%10s", name);  // Using %99s to avoid buffer overflow
        while(getchar() != '\n');
        initHunter(&house.hunters[i],name,i,house.rooms.head,&house);
    }
    house.hunterSize = NUM_HUNTERS;
    house.rooms.head->roomData->count_hunters = NUM_HUNTERS; //storing hunters in first room


    GhostInHouse newParam = {house,ghost};

    pthread_t t1;
    pthread_create(&t1,NULL,ghost_thread,&newParam);
    
    pthread_t t2[NUM_HUNTERS];

    // Allocating an array of ThreadArgs structures
    ThreadArgs thread_args_array[NUM_HUNTERS];

    for (int i = 0; i < NUM_HUNTERS; i++) {
            // Initializing the ThreadArgs structure for each thread
            thread_args_array[i].Hunter = newParam.house.hunters[i];
            thread_args_array[i].House = newParam.house;

            // Creating a thread and passing the structure as an argument
            pthread_create(&t2[i], NULL,hunter_thread, (void*)&thread_args_array[i]);
    }

    //waiting for the thread to finish
    pthread_join(t1,NULL);
    for (int i = 0; i < NUM_HUNTERS; i++) {
        pthread_join(t2[i], NULL);
    }


    cleanHouse(&house);
    return 0;
}


/* 
  Function: ghost_thread
  Purpose:  the ghost thread function to operate the various functions of ghost
  Params: 
    Input: void* args-  to work with the thread with the given void parameter of the structure defined
*/
void* ghost_thread(void *args){
    GhostInHouse *value = (GhostInHouse*) args;

    enum LoggerDetails result = C_5;
    while (value->ghost.boredom < BOREDOM_MAX) {
        if (hunterPresence(&value->ghost) ==  C_TRUE){
            value->ghost.boredom = C_0;
        }
        if (value->ghost.boredom >= BOREDOM_MAX-C_1){
            result = C_1;
            l_ghostExit(result);
            break;
        }
        sem_wait(&value->ghost.ghostRoom->roomSemaphore);
        // Randomly select an action
        int action = randInt(C_0, C_3);
        if (action == C_0){
            moveghostRoom(&value->ghost,&value->house);
        }
        else if (action == C_1){
            leaveEvidence(&value->ghost);
        }
        else if (action == C_2){
            doNothing();
        }
        sem_post(&value->ghost.ghostRoom->roomSemaphore);


    
       /* we have* used GHOST_WAIT here as it was given predefined and we did not want to lose marks by not using it 
         but using this might not show you all the output as  with these number, the output goes very fast.
          So please also run it with usleep(100000) to see all the threads running simultanieously */

        usleep(GHOST_WAIT); // can use usleep(100000) to see all the thread outputs
    }
    pthread_exit(NULL);
}


/* 
  Function: hunter_thread
  Purpose:  the hunter thread function to operate the various functions of all 4 hunters randomly
  Params: 
    Input: void* args-  to work with the thread with the given void parameter of the structure defined
*/
void* hunter_thread(void* args){

    ThreadArgs *value = (ThreadArgs*) args;
    HouseType house = value->House;
    HunterType hunter = value->Hunter;
    enum LoggerDetails result = C_5;

    while (hunter.boreCount < BOREDOM_MAX && hunter.fearCount < FEAR_MAX){

        if (ghostPresence(hunter.pointToCurRoom) == C_TRUE){
            hunter.fearCount++;
            hunter.boreCount = C_0;
        }
        else{
            hunter.boreCount++;
        }
        if (result >= C_0 && result <= C_2){
            l_hunterExit(hunter.hunterName,result);
            break;
        }
        if (hunter.boreCount >= BOREDOM_MAX - C_1){
            result = C_0;
            continue;
        }
        if (hunter.fearCount >= FEAR_MAX - C_1){ 
            result = C_1;
            continue;
        }

        int hunterAction = randInt(C_0,C_3);

        sem_wait(&hunter.pointToCurRoom->roomSemaphore);
        if (hunterAction == C_0){
            moveHunterRoom(&hunter,&house);
        }
        else if (hunterAction == C_1){
            collectEvidence(hunter.pointToCurRoom,&hunter,&house);

        }
        else if (hunterAction == C_2){
            int reviewResult = reviewEvidenceList(&house,&hunter);
            if (reviewResult == C_TRUE){
                result = C_2;
                continue;
            }
        }
        sem_post(&hunter.pointToCurRoom->roomSemaphore);


        /*
        we have* used HUNTER_WAIT here as it was given predefined and we did not want to lose marks by not using it 
         but using this might not show you all the output as  with these number, the output goes very fast.
          So please also run it with usleep(100000) to see all the threads running simultanieously */

        usleep(HUNTER_WAIT);
    }
    pthread_exit(NULL);
}

