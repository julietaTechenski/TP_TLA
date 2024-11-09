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


void addUser(GenerateEntry *entry, char *userId, UserEntry *userData);
UserEntry *findUser(GenerateEntry * entry, char * userId);
void deleteUser(GenerateEntry * entry, char * userId);
void addGroup(GenerateEntry * entry, char * groupId, GroupEntry * groupData);
GroupEntry *findGroup(GenerateEntry * entry, char * groupId);
void deleteGroup(GenerateEntry * entry, char * groupId);

UserHashEntry * copyUsersMap(UserHashEntry * usersMap);
GroupHashEntry * copyGroupsMap(GroupHashEntry * groupsMap);

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
    GroupHashEntry * groupsMap;      
    DefType type;
    KeyNode * usersListFirst;
    Date * startDate;
};


GenerateEntryNode * generateListFirst;
UserHashEntry * usersTableMap;
GroupHashEntry * groupsTableMap;


#endif
