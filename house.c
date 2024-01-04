//101271761 -  Vipra Hareshbhai Gajera
//101323400 -  Darsh Vikas Patel

#include "defs.h"

/* 
  Function: populateRooms
  Purpose:  to populate the rooms by creating, connecting the rooms to the house
  Params: 
    In/Out: HouseType* house- adding all the rooms to this house
*/
void populateRooms(HouseType* house) {
    // First, create each room

    // createRoom assumes that we dynamically allocate a room, initializes the values, and returns a RoomType*
    // create functions are pretty typical, but it means errors are harder to return aside from NULL
    struct Room* van                = createRoom("Van");
    struct Room* hallway            = createRoom("Hallway");
    struct Room* master_bedroom     = createRoom("Master Bedroom");
    struct Room* boys_bedroom       = createRoom("Boy's Bedroom");
    struct Room* bathroom           = createRoom("Bathroom");
    struct Room* basement           = createRoom("Basement");
    struct Room* basement_hallway   = createRoom("Basement Hallway");
    struct Room* right_storage_room = createRoom("Right Storage Room");
    struct Room* left_storage_room  = createRoom("Left Storage Room");
    struct Room* kitchen            = createRoom("Kitchen");
    struct Room* living_room        = createRoom("Living Room");
    struct Room* garage             = createRoom("Garage");
    struct Room* utility_room       = createRoom("Utility Room");

    // This adds each room to each other's room lists
    // All rooms are two-way connections
    connectRooms(van, hallway);
    connectRooms(hallway, master_bedroom);
    connectRooms(hallway, boys_bedroom);
    connectRooms(hallway, bathroom);
    connectRooms(hallway, kitchen);
    connectRooms(hallway, basement);
    connectRooms(basement, basement_hallway);
    connectRooms(basement_hallway, right_storage_room);
    connectRooms(basement_hallway, left_storage_room);
    connectRooms(kitchen, living_room);
    connectRooms(kitchen, garage);
    connectRooms(garage, utility_room);

    // Add each room to the house's room list
    //house added
    initMainRoomList(&house->rooms);

    
    addRoom(&house->rooms, van);
    addRoom(&house->rooms, hallway);
    addRoom(&house->rooms, master_bedroom);
    addRoom(&house->rooms, boys_bedroom);
    addRoom(&house->rooms, bathroom);
    addRoom(&house->rooms, basement);
    addRoom(&house->rooms, basement_hallway);
    addRoom(&house->rooms, right_storage_room);
    addRoom(&house->rooms, left_storage_room);
    addRoom(&house->rooms, kitchen);
    addRoom(&house->rooms, living_room);
    addRoom(&house->rooms, garage);
    addRoom(&house->rooms, utility_room);
}


/* 
  Function: initSharedList
  Purpose:  linked list for the shared evidences among hunters to review at any point
  Params: 
    In/Out: EviListType* eviList- setting all the nodes to null
*/
void initSharedList(EviListType *eviList){
    
    eviList->head = NULL;
    eviList->tail = NULL;
}


/* 
  Function: initHouse
  Purpose:  to initialise the house by initialising the main room list and the shared evidence list 
  Params: 
    In/Out: HouseType* house- initialising this given house with the rooms and evidence list
*/
void initHouse(HouseType *house){
    initMainRoomList(&house->rooms);
    initSharedList(&house->sharedList);
}


/* 
  Function: cleanHouse
  Purpose:  to free the data stored in heap of the house
  Params: 
    In/Out: HouseType* house- cleaning the given house by freeing up the rooms and evidence list
*/
void cleanHouse(HouseType *house){
    //cleanHunters(&house->hunters);
    CleanUpSharedEvidenceList(&house->sharedList);
    cleanUpRoomData(&house->rooms);
    cleanupRoomList(&house->rooms);
}

/* 
  Function: cleanUpSharedEvidenceList
  Purpose:  to free the shared evidence list stored in heap of the house
  Params: 
    In/Out: EviListType* list- cleaning the given list by freeing up the nodes
*/
void CleanUpSharedEvidenceList(EviListType *list){
  EviNodeType *currNode = list->head;
  EviNodeType *nextNode;
  
  while (currNode != NULL){
    nextNode = currNode->next;  
    free(currNode);
    currNode = nextNode;
  }
}