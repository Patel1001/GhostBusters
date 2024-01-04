//101271761 -  Vipra Hareshbhai Gajera
//101323400 -  Darsh Vikas Patel

#include "defs.h"

/* 
  Function: initMainRoomList
  Purpose:  initialising the main room linked list of the house dynamically 
    In/Out: RoomListType* room- this room list will be initialised by setting head and tail null 
*/
void initMainRoomList(RoomListType *room){
    room->head = NULL;
    room->tail = NULL;
}


/* 
  Function: createRoom
  Purpose:  initialising the room structure dynamically and setting the data to default
    Input : char* name- to name the new room with this given name
*/
RoomType* createRoom(char *name){
    RoomType *pointer = (RoomType*) malloc (sizeof(RoomType));
    if (pointer == NULL){
        printf("Memory is not allocated properly to the room\n");
    }
    strcpy(pointer->roomName,name);
    initConnectRoomList(&pointer->connectedRooms);
    initEvidenceRoomList(&pointer->evidenceList);
    pointer->count = C_0;
    initHunterInRoom(&pointer->huntersInRoom);
    pointer->ghostPointer = NULL;
    pointer->count_hunters = C_0;

    sem_init(&pointer->roomSemaphore, C_0, C_1);  //initialising the semaphore for each room
    return pointer;
}


/* 
  Function: initHunterInRoom
  Purpose:  initialising the hunters in room linked list dynamically
    In/Out: HunterListType** list- this hunter list will be created by setting null values to the head and tail
*/
void initHunterInRoom(HunterListType **list){
    HunterListType *pointer = (HunterListType*) malloc (sizeof(HunterListType));
    pointer->head = NULL;
    pointer->tail = NULL;
    *list = pointer;
}


/* 
  Function: initConnectRoomList
  Purpose:  initialising the connected room linked list dynamically(i.e. the rooms that the particular room is connected to)
    In/Out: RoomListType** list- this room list will be created by setting null values to the head and tail
*/
void initConnectRoomList(RoomListType **list){
    RoomListType *pointer = (RoomListType*) malloc(sizeof(RoomListType));
    pointer->head = NULL;
    pointer->tail = NULL;
    *list = pointer;
}


/* 
  Function: initEvidenceRoomList
  Purpose:  initialising the evidence room linked list dynamically(i.e. the evidence that are left in the room by the ghost)
    In/Out: EviListType** list- this evidence list will be created by setting null values to the head and tail
*/
void initEvidenceRoomList(EviListType **list){
    EviListType *pointer = (EviListType*) malloc(sizeof(EviListType));
    pointer->head = NULL;
    pointer->tail = NULL;
    *list = pointer;
}



/* 
  Function: addRoom
  Purpose:  adding the room to the house (main room list in the house structure)
    In/Out: RoomListType* list- this room list will be updated by adding the room
    Input : RoomType*     room- this is the room that will be added at the tail of the list
*/
void addRoom(RoomListType *list,RoomType *room){
    //adding room to the main room list
    RoomNodeType *nodePointer = (RoomNodeType*) malloc(sizeof(RoomNodeType));
    if (nodePointer == NULL){
        printf("Memory is not allocated properly for adding room.\n");
    }
    nodePointer->roomData = room;
    nodePointer->next = NULL;

    if (list->head == NULL){
        list->head = nodePointer;
        list->tail = nodePointer;
    }
    else{
        list->tail->next = nodePointer;
        list->tail = nodePointer;
    }
}


/* 
  Function: connectRooms
  Purpose:  connecting one room with the help of other using another helper function
    In/Out: RoomType* room1- this room will be added to the end of connected list of room2 
    In/Out: RoomType* room2- this room will be added to the end of connected list of room1 
*/
void connectRooms(RoomType *room1, RoomType *room2){
    RoomNodeType *nodePointer = (RoomNodeType*) malloc(sizeof(RoomNodeType));
    if (nodePointer == NULL){
        printf("Memory is not allocated properly for adding room 1 to room 2.\n");
    }
    connection(room1,room2,nodePointer);

    RoomNodeType *nodePointerReverse = (RoomNodeType*) malloc(sizeof(RoomNodeType));
    if (nodePointerReverse == NULL){
        printf("Memory is not allocated properly for adding room 2 to room 1.\n");
    }
    connection(room2,room1,nodePointerReverse);
}

//helper function for connecting two rooms
/* 
  Function: connectRooms
  Purpose:  connecting one room with the help of other using another helper function
    In/Out: RoomType* room- this room will be added to the end of connected list of roomToConnect
    In/Out: RoomType* roomToConnect- this room will be added to the end of connected list of room 
    Input : RoomNodeType* node- the node to add the room dynamically
*/
void connection(RoomType *room,RoomType *roomToConnect, RoomNodeType *node){
    node->roomData = roomToConnect;
    node->next = NULL;
    
    if (room->connectedRooms->head == NULL){
        room->connectedRooms->head = node;
        room->connectedRooms->tail = node;
    }
    else{
        room->connectedRooms->tail->next = node;
        room->connectedRooms->tail =  node;
    }
    room->count++;
}


/* 
  Function: findRoom
  Purpose:  find room randomly from one to other which are connected to each other
    Input : RoomType* curRoom- from this room to other using the connected list of this room
    Input : HouseType* house- the rooms of this house
  Returns : RoomType* - the new room that is connected to this room (same room if the connected list is empty)
*/
RoomType* findRoom(RoomType *curRoom,HouseType *house){
    if (curRoom->count != C_0){
        int randomRoom = randInt(C_1,curRoom->count + C_1);
        RoomNodeType *newRoom = curRoom->connectedRooms->head;
        if (randomRoom > C_1){
            for (int i = 2;i < randomRoom+C_1;i++){
                newRoom = newRoom->next;
            }
        }
        char *name = newRoom->roomData->roomName;
        RoomNodeType *findRoom = house->rooms.head;
        while (findRoom != NULL){
            if (strcmp(findRoom->roomData->roomName,name) == C_0){
                break;
            }
            else{
                findRoom = findRoom->next;
            }
        }
        return findRoom->roomData;

    }
    return curRoom;
}


/* 
  Function: cleanUpRoomData
  Purpose:  freeing the dynamically allocated data of the room  List strcuture
    In/Out: RoomListType* list- this room data will be freed from the heap
*/
void cleanUpRoomData(RoomListType *list){
  RoomNodeType *currNode = list->head;
  RoomNodeType *nextNode;
  
  while (currNode != NULL) {
    nextNode = currNode->next;
    cleanConnectedRooms(currNode->roomData->connectedRooms);
    cleanEvidenceInRoom(currNode->roomData->evidenceList);
    cleanHuntersInRoom(currNode->roomData->huntersInRoom);
    free(currNode->roomData);
    currNode = nextNode;
  }
}


/* 
  Function: cleanUpRoomList
  Purpose:  freeing the dynamically allocated nodes of the room List strcuture 
    In/Out: RoomListType* list- this room list will be freed from the heap
*/
void cleanupRoomList(RoomListType *list){
  RoomNodeType *currNode = list->head;
  RoomNodeType *nextNode;
  
  while (currNode != NULL){
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
}


/* 
  Function: cleanConnectedRooms
  Purpose:  freeing the dynamically allocated nodes of the room  List strcuture
    In/Out: RoomListType* list- this room will be freed from the heap
*/
void cleanConnectedRooms(RoomListType *list){
  RoomNodeType *currNode = list->head;
  RoomNodeType *nextNode;
  
  while (currNode != NULL){
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
  free(list);
}


/* 
  Function: cleanEvidenceInRoom
  Purpose:  freeing the dynamically allocated evidences' (nodes) left by the ghost in the room 
    In/Out: EviListType* list- this evidence list will be freed from the heap
*/
void cleanEvidenceInRoom(EviListType *list){
  EviNodeType *currNode = list->head;
  EviNodeType *nextNode;
  
  while (currNode != NULL){
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
  free(list);
}


/* 
  Function: cleanHuntersInRoom
  Purpose:  freeing the dynamically allocated hunters' (nodes) in the room if there are any left in the hunters list
    In/Out: HunterListType* list- this hunter list will be freed from the heap
*/
void cleanHuntersInRoom(HunterListType *list){
  HunterNodeType *currNode = list->head;
  HunterNodeType *nextNode;
  
  while (currNode != NULL){
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
  free(list);
}

