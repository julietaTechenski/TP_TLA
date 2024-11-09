#ifndef SYMBOL_TABLES_HEADER
#define SYMBOL_TABLES_HEADER

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "uthash.h"


typedef struct KeyNode KeyNode;
typedef struct TaskNode TaskNode;
typedef struct EventNode EventNode;
typedef struct GenerateEntryNode GenerateEntryNode;
typedef struct UserHashEntry UserHashEntry;
typedef struct GroupHashEntry GroupHashEntry;
typedef struct UserEntry UserEntry;
typedef struct GroupEntry GroupEntry;
typedef struct GenerateEntry GenerateEntry;


// Definition of nodes
struct KeyNode {
	char * key;
    struct KeyNode * next;
};

struct TaskNode {
    CreateTask * task;
    struct TaskNode * next;
};

struct EventNode {
    CreateEvent * event;
    struct EventNode * next;
};

struct GenerateEntryNode {
    GenerateEntry * entry;
    struct GenerateEntryNode * next;
};


// Definition of HashMap entries
struct UserHashEntry{
    char * userId;        
    UserEntry * userData;    
    UT_hash_handle hh;     
};

struct GroupHashEntry{
    char * groupId;         
    GroupEntry * groupData;      
    UT_hash_handle hh;     
};


// Definition of entries
struct UserEntry{
    char * userId;
    TaskNode * tasksListFirst;
    EventNode * eventsListFirst;
    KeyNode *groupFirst;
};

struct GroupEntry{
    char * groupId;
    TaskNode * tasksListFirst;
    EventNode * eventsListFirst;
};

struct GenerateEntry {
	char * fileId;                  
    UserHashEntry * usersMap;      
    GroupHashEntry * groupMap;      
    DefType type;
    KeyNode * usersListFisrt;
    Date * startDate;
};


GenerateEntryNode * generateListFirst;


#endif
