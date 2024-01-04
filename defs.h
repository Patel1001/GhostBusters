//101271761 -  Vipra Hareshbhai Gajera
//101323400 -  Darsh Vikas Patel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_STR         64
#define MAX_RUNS        50
#define BOREDOM_MAX     100
#define C_TRUE          1
#define C_FALSE         0
#define HUNTER_WAIT     5000
#define GHOST_WAIT      600
#define NUM_HUNTERS     4
#define FEAR_MAX        10
#define LOGGING         C_TRUE

#define C_0             0
#define MAX_EVI         4

#define C_1             1
#define C_2             2
#define C_3             3
#define C_4             4
#define C_5             5

#define MAX_ROOMS       13



typedef enum EvidenceType EvidenceType;
typedef enum GhostClass GhostClass;
typedef struct Room RoomType;
typedef struct RoomList RoomListType;
typedef struct RoomNode RoomNodeType;
typedef struct EviList EviListType;
typedef struct EviNode EviNodeType;
typedef struct House HouseType;
typedef struct Hunter HunterType;
typedef struct HunterList HunterListType;
typedef struct HunterNode HunterNodeType;
typedef struct Ghost GhostType;

typedef struct GhostInHouse GhostInHouse;
typedef struct ThreadArgs ThreadArgs;

enum EvidenceType { EMF, TEMPERATURE, FINGERPRINTS, SOUND, EV_COUNT, EV_UNKNOWN };
enum GhostClass { POLTERGEIST, BANSHEE, BULLIES, PHANTOM, GHOST_COUNT, GH_UNKNOWN };
enum LoggerDetails { LOG_FEAR, LOG_BORED, LOG_EVIDENCE, LOG_SUFFICIENT, LOG_INSUFFICIENT, LOG_UNKNOWN };

//room strcuture
struct Room{
    char roomName[MAX_STR]; // name of the room 
    struct RoomList *connectedRooms; // which room it is connected to 
    struct EviList *evidenceList; // for evidence left in the room
    int count; //counter for size of connectionlist;

    HunterListType *huntersInRoom;//Collection of Hunters in the room currently 
    GhostType *ghostPointer; //pointer to the Ghost
    int count_hunters; // to count the number of hunters in the room at present

    //semaphore 
    sem_t roomSemaphore;
};


struct RoomNode {
  struct RoomNode *next;
  RoomType *roomData;
}; //RoomNodeType


struct RoomList{
   RoomNodeType *head;
   RoomNodeType *tail;
}; //RoomListType


//evidence
struct EviNode {
  struct EviNode *next;
  EvidenceType eviData;
}; //EviNodeType


struct EviList{
   EviNodeType *head;
   EviNodeType *tail;
}; //EviListType


struct Ghost{
  GhostClass ghost_type;
  RoomType *ghostRoom;//pointer to the room it is present
  int boredom;
};


//hunter
struct Hunter{    
    int fearCount;
    int boreCount;  
    RoomType *pointToCurRoom; //pointer to room
    char hunterName[MAX_STR];
    EvidenceType hunterEvi; //evidenceType of the hunter
    EviNodeType *pointerToSharedEvi;//to point the shared data/evidence
};

struct HunterList{
  HunterNodeType *head;
  HunterNodeType *tail;
};

struct HunterNode{
  struct HunterNode *next;
  HunterType *hunterData;
};

//house
struct House{
    //collection of hunters
    HunterType hunters[NUM_HUNTERS];
    RoomListType rooms;
    EviListType sharedList; 
    int hunterSize; //size of hunters in the house
};//HouseType


//extra structs for threads 
struct GhostInHouse{
  HouseType house;
  GhostType ghost;
};

struct ThreadArgs{
  HunterType Hunter;
  HouseType House;
};


// Helper Utilies
int randInt(int,int);        // Pseudo-random number generator function
float randFloat(float, float);  // Pseudo-random float generator function
enum GhostClass randomGhost();  // Return a randomly selected a ghost type
void ghostToString(enum GhostClass, char*); // Convert a ghost type to a string, stored in output paremeter
void evidenceToString(enum EvidenceType, char*); // Convert an evidence type to a string, stored in output parameter

// Logging Utilities
void l_hunterInit(char* name, enum EvidenceType equipment);
void l_hunterMove(char* name, char* room);
void l_hunterReview(char* name, enum LoggerDetails reviewResult);
void l_hunterCollect(char* name, enum EvidenceType evidence, char* room);
void l_hunterExit(char* name, enum LoggerDetails reason);
void l_ghostInit(enum GhostClass type, char* room);
void l_ghostMove(char* room);
void l_ghostEvidence(enum EvidenceType evidence, char* room);
void l_ghostExit(enum LoggerDetails reason);



//room file declarations
void initMainRoomList(RoomListType *room);
RoomType* createRoom(char *name);
void initHunterInRoom(HunterListType **list);
void initConnectRoomList(RoomListType **list);
void initEvidenceRoomList(EviListType **list);
void addRoom(RoomListType *list,RoomType *room);
void connectRooms(RoomType *room, RoomType *roomToConnect);
void connection(RoomType *room,RoomType *roomToConnect, RoomNodeType *node);
RoomType* findRoom(RoomType *curRoom,HouseType *house);

void cleanUpRoomData(RoomListType *list);
void cleanupRoomList(RoomListType *list);
void cleanConnectedRooms(RoomListType *list);
void cleanEvidenceInRoom(EviListType *list);
void cleanHuntersInRoom(HunterListType *list);



//hunter file declarations
void initHunter(HunterType *hunter_type,char *hunter, enum EvidenceType equipment,RoomNodeType *pointer,HouseType *house);
RoomType* moveHunterRoom(HunterType *hunter,HouseType *house);
int collectEvidence(RoomType *room,HunterType *hunter,HouseType *house);
int reviewEvidenceList(HouseType *house,HunterType *hunter);
void deleteHunter(HunterType *hunter,HouseType *house);
int hunterPresence(GhostType *ghost);
void initHunterInVan(HouseType *house,HunterType *hunter);


//house file decalarations
void populateRooms(HouseType* house);
void initSharedList(EviListType *eviList);
void initHouse(HouseType *house);
void cleanHouse(HouseType *house);
void CleanUpSharedEvidenceList(EviListType *list);


//ghost file declarations
void initGhost(GhostType *ghost,HouseType *house);
RoomType* moveghostRoom(GhostType *ghost,HouseType *house);
void leaveEvidence(GhostType *ghost);
void doNothing();
int ghostPresence(RoomType *room);

//main file declarations
void* ghost_thread(void*);
void* hunter_thread(void*);