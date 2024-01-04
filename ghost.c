//101271761 -  Vipra Hareshbhai Gajera
//101323400 -  Darsh Vikas Patel

#include "defs.h"

/* 
  Function: initGhost
  Purpose:  to initialise the ghost
  Params: 
    In/Out: GhostType* ghost- setting all the data values to default
    Input : HouseType* house- setting the pointers from the house data 
*/
void initGhost(GhostType *ghost,HouseType *house){
    ghost->boredom = C_0;
    ghost->ghost_type = randInt(C_0 , C_4);
    RoomNodeType *pointer = house->rooms.head;
    int roomNumber = randInt(C_2 , MAX_ROOMS + C_1);//MN
    for (int i = 1; i < roomNumber; i ++){
        pointer = pointer->next;
    }
    ghost->ghostRoom = pointer->roomData;
    pointer->roomData->ghostPointer = ghost;

    l_ghostInit(ghost->ghost_type,ghost->ghostRoom->roomName);//using logger function
}


/* 
  Function: moveghostRoom
  Purpose:  to move the ghost from one room to other randomly if and only if there are no hunters present in the current room otherwise
            choosing from leaving evidence or doing nothing
  Params: 
    In/Out: GhostType* ghost- moving this ghost
    Input : HouseType* house- getting the pointers from the house data for the rooms
  Returns : RoomType*- the new room that the ghost moved to (or the same room if not moved)
*/
RoomType* moveghostRoom(GhostType *ghost,HouseType *house){

    RoomType *curRoom = ghost->ghostRoom;
    if (curRoom->count_hunters == C_0){
    //if (curRoom->huntersInRoom->head == NULL){ 
        RoomType *newRoom = findRoom(curRoom,house);
        ghost->ghostRoom->ghostPointer = NULL; //prev ghost pointer to null
        ghost->ghostRoom = newRoom;         //changing to new room
        ghost->ghostRoom->ghostPointer = ghost; //new room with ghost as a pointer
        //ghost->boredom++;
        
        l_ghostMove(newRoom->roomName);//using logger function
        curRoom = newRoom;
    }
    else{
        HunterNodeType *newHunter = ghost->ghostRoom->huntersInRoom->head;
        while (newHunter != NULL){
            newHunter->hunterData->fearCount++;
            newHunter = newHunter->next;
        }
        int ranNum = randInt(C_1,C_3);   //if there are hunters in the new room
        if (ranNum == C_2){
            leaveEvidence(ghost);
        }
        else{
            doNothing(ghost);
        }
    }
    return ghost->ghostRoom;
}


/* 
  Function: leaveEvidence
  Purpose:  to leave the evidence (3 out of 4) according to the type of the ghost
  Params: 
    Input: GhostType* ghost- leaving the evidence with the enum ghostclass data type
*/
void leaveEvidence( GhostType *ghost){

    //to randomly select the evidence to leave
    int randomNumber  = randInt(C_0 , C_3);
    if (ghost->ghost_type == C_0){
        //0 1 2 types
        randomNumber = randomNumber;
    }
    else if (ghost->ghost_type == C_1){
        // 0 1 3 types
        if (randomNumber == C_2){
            randomNumber = C_3;
        }
    }
    else if (ghost->ghost_type == C_2){
        //0 2 3 types
        if (randomNumber == C_1){
            randomNumber = C_2;
        }
        else if (randomNumber == C_2){
            randomNumber = C_3;
        }
    }
    else if (ghost->ghost_type == C_3){
        //1 2 3 types
        randomNumber = randomNumber + C_1;
    }

    //leaving evidence as adding to the rooms evidence list
    RoomType *room = ghost->ghostRoom;
    EvidenceType evidence = (EvidenceType) randomNumber;
    EviNodeType *newEvi = (EviNodeType*) malloc(sizeof(EviNodeType));

    newEvi->eviData = evidence;
    newEvi->next = NULL;
    if (room->evidenceList->head == NULL){
        room->evidenceList->head = newEvi;
        room->evidenceList->tail = newEvi;
    }
    else{
        room->evidenceList->tail->next = newEvi;
        room->evidenceList->tail = newEvi;
    }
    l_ghostEvidence(evidence,ghost->ghostRoom->roomName);//using logger function
}

/* 
  Function: doNothing
  Purpose:  to do nothing when called as it is one of the things that a ghost can do
*/
void doNothing(){
    return;              //do nothing function for the ghost
}

/* 
  Function: ghostPresence
  Purpose:  to check for the presence of the ghost in the room
  Params: 
    Input : RoomType* room- checking if this room has ghost or not
  Returns: True : if there is ghost otherwise false
*/
int ghostPresence(RoomType *room){
    if (room->ghostPointer != NULL){
        return C_TRUE; //if there are ghosts present in the room
    }
    return C_FALSE;
}
