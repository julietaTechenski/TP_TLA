#ifndef SYMBOL_TABLES_HEADER
#define SYMBOL_TABLES_HEADER

#include "../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "uthash.h"

#define ERROR 1
#define SUCCESS 0

typedef struct TaskNode TaskNode;
typedef struct EventNode EventNode;
typedef struct CodeBlocksEntryNode CodeBlocksEntryNode;
typedef struct KeyNode KeyNode;
typedef struct GenerateEntryNode GenerateEntryNode;
typedef struct UserEntryNode UserEntryNode;

typedef struct UserHashEntry UserHashEntry;
typedef struct GroupHashEntry GroupHashEntry;
typedef struct CodeBlocksHashEntry CodeBlocksHashEntry;
typedef struct UserEntry UserEntry;
typedef struct GroupEntry GroupEntry;
typedef struct GenerateEntry GenerateEntry;
typedef struct CodeBlocksEntry CodeBlocksEntry;
typedef struct DoubleEndKeyNodeList DoubleEndKeyNodeList;


// Generate List managment functions
int addGenerateEntry(Generate * generate);
void destroyGenerateList();
GenerateEntryNode * getGenerateList();


// User Map managment functions
int addUser(User * user);
UserEntry * findUser(const char * userId);
int addTaskToUser(const char * userId, CreateTask * task);
int addEventToUser(const char * userId, CreateEvent * event);
int addGroupsToUser(const char * userId, Groups * groups);
void destroyUsersTableMap();
void deleteUser(char * userId);


// Group Map managment functions
int addGroup(Group * group);
GroupEntry * findGroup(const char * groupId);
int addTaskToGroup(const char * groupId, CreateTask * task);
int addEventToGroup(const char * groupId, CreateEvent * event);
void destroyGroupsTableMap();
void deleteGroup(char * groupId);

// Code Blocks List managment functions
int addUserToCodeBlockUsersMap(const char * codeBlockId, User * user);
int addGroupToCodeBlockUsersMap(const char * codeBlockId, Group * group);
int addCodeBlockEntry(const char * codeBlockId);
int addGenerateEntryToCodeBlock(const char * codeBlockId, Generate * generate);
int addTaskToGroupToCodeBlock(const char * defineId, const char * groupId, CreateTask * task);
int addTaskToUserToCodeBlock(const char * defineId, const char * groupId, CreateTask * task);
int addEventToGroupToCodeBlock(const char * defineId, const char * groupId, CreateEvent * event);
int addEventToUserToCodeBlock(const char * defineId, const char * groupId, CreateEvent * event);
int addGroupsToUserInCodeBlock(const char * defineId, const char * userId, Groups * groups);
void destroyCodeBlock();

// Destroy everything
void destroySymbolTables();


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

struct CodeBlocksEntryNode {
    CodeBlocksEntry * block;
    CodeBlocksEntryNode * next;
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

struct CodeBlocksHashEntry{
    char * codeBlocksId;         
    CodeBlocksEntry * codeBlocksData;      
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

struct CodeBlocksEntry {
    char * id;
    struct GenerateEntryNode * generateList;
    UserHashEntry * usersTableMap;     
    GroupHashEntry * groupsTableMap;   
    CodeBlocksHashEntry * codeBlocks;
};

#endif
