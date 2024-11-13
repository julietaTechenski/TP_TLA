#ifndef SYMBOL_TABLES_HEADER
#define SYMBOL_TABLES_HEADER

#include "../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "uthash.h"


typedef struct TaskNode TaskNode;
typedef struct EventNode EventNode;

typedef struct KeyNode KeyNode;
typedef struct GenerateEntryNode GenerateEntryNode;
typedef struct UserEntryNode UserEntryNode;

typedef struct UserHashEntry UserHashEntry;
typedef struct GroupHashEntry GroupHashEntry;
typedef struct UserEntry UserEntry;
typedef struct GroupEntry GroupEntry;
typedef struct GenerateEntry GenerateEntry;


// Generate List managment functions
void addGenerateEntry(Generate * generate);
void freeGenerateEntryNodeList();
UserHashEntry * copyUsersMap(UserHashEntry * usersMap);
UserEntry * copyUserEntry(UserEntry * originalEntry);
GroupHashEntry * copyGroupsMap(GroupHashEntry * groupsMap);
GroupEntry * copyGroupEntry(GroupEntry * originalEntry);
TaskNode * copyTaskList(TaskNode * originalTask);
EventNode * copyEventList(EventNode * originalEvent);
KeyNode * copyGroupList(KeyNode *originalGroup);
void freeGenerateEntry(struct GenerateEntry *entry);


// User Map managment functions
void addUser(User * user);
UserEntry * createUserEntry(User * user);
UserEntry * findUser(const char * userId);
void addTaskToUser(const char * userId, CreateTask * task);
void addEventToUser(const char * userId, CreateEvent * event);
void addGroupsToUser(const char * userId, Groups * groups);
void destroyUsersMap(UserHashEntry * usersMap);
void deleteUser(char * userId);
void freeUserEntry(UserEntry *entry);


// Group Map managment functions
void addGroup(Group * group);
GroupEntry * createGroupEntry(Group * group);
GroupEntry * findGroup(const char * groupId);
void addTaskToGroup(const char * groupId, CreateTask * task);
void addEventToGroup(const char * groupId, CreateEvent * event);
void destroyGroupsMap(GroupHashEntry * groupsMap);
void deleteGroup(char * groupId);
void freeGroupEntry(GroupEntry * entry);


// Add to items to lists
void addTaskNode(TaskNode ** head, CreateTask * task);
void addEventNode(EventNode ** head, CreateEvent * event);
void addKeyNode(KeyNode ** head, char * key);


// Free functions
void freeTaskList(TaskNode * taskList);
void freeEventList(EventNode * eventList);
void freeGroupList(KeyNode * groupList);



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

struct UserEntryNode {
    UserEntry * entry;
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
    User * user;
    TaskNode * tasksListFirst;
    EventNode * eventsListFirst;
    KeyNode *groupFirst;
};

struct GroupEntry{
    Group * group;
    TaskNode * tasksListFirst;
    EventNode * eventsListFirst;
};

struct GenerateEntry {
    Generate * generate;
    UserHashEntry * usersMap;      
    GroupHashEntry * groupsMap;      
    GenerateEntryNode * next;
};

#endif
