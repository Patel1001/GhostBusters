//101271761 -  Vipra Hareshbhai Gajera
//101323400 -  Darsh Vikas Patel

#include "defs.h"


/* 
  Function: initHunter
  Purpose:  initialising the hunter by setting the default values and printing it using logger function, and plaing them in Van
  Params: 
    In/Out: EviListType* eviList- setting all the values of the huntr field to default
*/
void initHunter(HunterType *hunter_type,char *hunter, enum EvidenceType equipment,RoomNodeType *pointer,HouseType *house) {
    hunter_type->boreCount = C_0;
    hunter_type->fearCount = C_0;
    strcpy(hunter_type->hunterName,hunter);
    hunter_type->hunterEvi = equipment;
    hunter_type->pointToCurRoom = pointer->roomData;
    hunter_type->pointerToSharedEvi = house->sharedList.head;   //shared evidence list pointer

    l_hunterInit(hunter,equipment); //logger function
    initHunterInVan(house,hunter_type);
}


/* 
  Function: moveHunterRoom
  Purpose:  moving the hunter from one room to another by finding the current room and going to other randomly
  Params: 
    In/Out: HunterType* hunter- moving this hunter from one room to another
    Input : HouseType*  house- finding rooms from the given house
  Returns : RoomType* - the room that the hunter will be (new if changed otherwise the same)
*/
RoomType* moveHunterRoom(HunterType *hunter, HouseType *house) {
    // Find the current room node where the hunter is present
    RoomType *curRoomNode = hunter->pointToCurRoom;

    // Step 1: Remove the hunter from the current room's huntersInRoom list
    // Find and delete the hunter from the current room's huntersInRoom list
    HunterNodeType *curHunterNode = curRoomNode->huntersInRoom->head;
    HunterNodeType *prevHunterNode = NULL;
    while (curHunterNode != NULL) {
        if (curHunterNode->hunterData == hunter) {
            if (prevHunterNode == NULL) {
                // If the hunter to be removed is the head of the list
                curRoomNode->huntersInRoom->head = curHunterNode->next;
                free(curHunterNode);
            } else {
                prevHunterNode->next = curHunterNode->next;
                free(curHunterNode);
            }
            break;
        }
        prevHunterNode = curHunterNode;
        curHunterNode = curHunterNode->next;
    }
    curRoomNode->count_hunters --;  //number of hunters in the room counter
    // Step 2: Move the hunter to the new room
    RoomType *newRoomNode = findRoom(curRoomNode,house);

    // Update the hunter's current room pointer to the new room
    hunter->pointToCurRoom = newRoomNode;
    // Step 3: Add the hunter to the new room's huntersInRoom list
    // Create a new node for the hunter
    HunterNodeType *newHunterNode = (HunterNodeType*) malloc(sizeof(HunterNodeType));
    if (newHunterNode == NULL){
        printf("Memory was not allocated properly\n");
    }
    newHunterNode->hunterData = hunter;
    newHunterNode->next = NULL;

    // Add the hunter node to the new room's huntersInRoom list
    if (newRoomNode->huntersInRoom->head == NULL) {
        // If the list is empty
        newRoomNode->huntersInRoom->head = newHunterNode;
        newRoomNode->huntersInRoom->tail = newHunterNode;
    } else {
        newRoomNode->huntersInRoom->tail->next = newHunterNode;
        newRoomNode->huntersInRoom->tail = newHunterNode;
    }
    l_hunterMove(hunter->hunterName,newRoomNode->roomName);
    newRoomNode->count_hunters++;
    return newRoomNode;
}


/* 
  Function: collectEvidence
  Purpose:  collecting the evidence from the room in which the hunter is present in if it matches the type of the evidence hunter has
  Params: 
    Input : RoomType* room- collecting evidence from this room
    Input : HunterType*  hunter- this particular hunter will collect the evidence
    In/Out: HouseType* house- collecting and adding the evidence to the shared evidence list of this house
   Returns: int - if the evidence was collected then true , else false
*/
int collectEvidence(RoomType *room,HunterType *hunter, HouseType *house){
    //if same then it will collect from the list

    EviNodeType *evidence = room->evidenceList->head;
    EviNodeType *prevEvidence = NULL;
    while (evidence != NULL){
        if (evidence->eviData == hunter->hunterEvi){
            if (prevEvidence == NULL){
                room->evidenceList->head = evidence->next;
            }
            else if (evidence == room->evidenceList->tail){
                room->evidenceList->tail = prevEvidence;
            }
            else{
                prevEvidence->next = evidence->next;
            }
            EviNodeType *newEv = (EviNodeType*) malloc (sizeof(EviNodeType));
            newEv->eviData = hunter->hunterEvi;
            newEv->next = NULL;
            EviNodeType *curNode = house->sharedList.head;
            if (curNode == NULL){
                house->sharedList.head = newEv;
                house->sharedList.tail = newEv;
            }
            else{
                house->sharedList.tail->next = newEv;
                house->sharedList.tail = newEv;
            }
            //logger function
            l_hunterCollect(hunter->hunterName,hunter->hunterEvi,hunter->pointToCurRoom->roomName);
            return C_TRUE;  //returning true if collected
            break;
        }
        prevEvidence = evidence;
        evidence = evidence->next;
    }
    return C_FALSE;
}


/* 
  Function: reviewEvidenceList
  Purpose:  reviewing the evidence to exit if there are three unique evidences collected / present in the shared evidence list
    In/Out: HouseType*  house- to review and exit from the hunters list (if found three unique evidences left by the ghost)
    In/Out: HunterType* hunter- this hunter will review the evidence list and decide to exit or not
  Returns: int - true (1) if the hunter exits from the house (as 3 unique evidences were found), else false(0)
*/
int reviewEvidenceList(HouseType *house,HunterType *hunter){

    EviNodeType *pointer = house->sharedList.head;
    int arr[MAX_EVI] = {0}; //to store the number of each evidencetype in the array [ev1,ev2,ev3,ev4]
    while (pointer != NULL){
        if (pointer->eviData >= C_0 && pointer->eviData <= C_3){
            arr[pointer->eviData]++;       //to go through 4 evidences and counting how many times they appeared
        }
        pointer = pointer->next;
    }
    
    int count = 0;
    for (int i = 0; i < NUM_HUNTERS;i++){
        if (arr[i] == C_0){
            count++;
        }
    } 

    EviNodeType *newNode = house->sharedList.head;
    while (newNode != NULL){
        char str[MAX_STR];
        evidenceToString(newNode->eviData,str);
        newNode = newNode->next;
    }
    enum LoggerDetails result = C_5;
    if (count > C_1){               //if there not 3 unique evidences then continue
        result = C_4;
        l_hunterReview(hunter->hunterName,result);
        return C_FALSE;
    }
    else{
        //hunter remove below              //else that hunter will exit
        deleteHunter(hunter,house);
        result = C_3;
        l_hunterReview(hunter->hunterName,result);//using logger function
        return C_TRUE;
    }
}

/* 
  Function: deleteHunter
  Purpose:  deleting the hunter from the house with hunters array if wants to exit
    In/Out: HunterType* hunter- this hunter will be deleted 
    In/Out: HouseType*  house- the house from which the hunter will be deleted
*/
void deleteHunter(HunterType *hunter,HouseType *house){
    for (int i = 0; i < house->hunterSize;i++){
        if (strcmp(house->hunters[i].hunterName,hunter->hunterName) == C_0){
            for (int j = i; j < house->hunterSize - C_1; j ++){
                house->hunters[j] = house->hunters[j+C_1];
            }
            house->hunterSize--;
            hunter->pointToCurRoom->count_hunters--;
            break;
        }
    }
}


/* 
  Function: hunterPresence
  Purpose:  to check if there are any hunters present in the room where the ghost is present
    Input : GhostType* ghost- to check from this ghost location to see for the hunters' presence 
  Returns: int - if there are any hunters present (1) else (0)
*/
int hunterPresence(GhostType *ghost){
    if (ghost->ghostRoom->count_hunters == 0){
        return C_FALSE; //if there are no hunters in the room where the ghost is presence
    }
    return C_TRUE;
}

/* 
  Function: initHunterInVan
  Purpose:  to initialise the hunters dynamically and add it to the Van's hunters list
    In/Out: HouseType*  house- the house in which the room Van is present
    In/Out: HunterType* hunter- this hunter will be initialised 
*/
void initHunterInVan(HouseType *house, HunterType *hunter){
        HunterNodeType *newHunter = (HunterNodeType*) malloc(sizeof(HunterNodeType));
        newHunter->hunterData = hunter;
        newHunter->next = NULL; 

        HunterNodeType *node = house->rooms.head->roomData->huntersInRoom->head;
        if (node == NULL){
            house->rooms.head->roomData->huntersInRoom->head = newHunter;
            house->rooms.head->roomData->huntersInRoom->tail = newHunter;
        }
        else{
            house->rooms.head->roomData->huntersInRoom->tail->next = newHunter;
            house->rooms.head->roomData->huntersInRoom->tail = newHunter;
        }
}