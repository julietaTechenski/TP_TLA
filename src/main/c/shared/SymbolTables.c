#include "SymbolTables.h"

// static variables

static GenerateEntry *firstGenerate = NULL;
static GenerateEntry *lastGenerate = NULL;

// static hashmap fro users
static UserHashEntry *usersTableMap = NULL;
static GroupHashEntry *groupsTableMap = NULL;
// statis hashmap for groups


/** Data management functions  **/

void addUser(UserHashEntry *entry, char *userId, UserEntry *userData) {
    UserHashEntry *newUser = malloc(sizeof(UserHashEntry));
    newUser->userId = strdup(userId);  
    newUser->userData = userData;
    HASH_ADD_KEYPTR(hh, entry, newUser->userId, strlen(newUser->userId), newUser);
}

UserEntry *findUser(GenerateEntry * entry, char * userId) {
    UserHashEntry * userEntry;
    HASH_FIND_STR(entry->usersMap, userId, userEntry);
    return userEntry ? userEntry->userData : NULL;
}

void deleteUser(GenerateEntry * entry, char * userId) {
    UserHashEntry *userEntry;
    HASH_FIND_STR(entry->usersMap, userId, userEntry);
    if (userEntry) {
        HASH_DEL(entry->usersMap, userEntry);
        free(userEntry->userId); 
        free(userEntry);          
    }
}

void addGroup(GroupHashEntry * entry, char * groupId, GroupEntry * groupData) {
    GroupHashEntry * newGroup = malloc(sizeof(GroupHashEntry));
    newGroup->groupId = strdup(groupId);  
    newGroup->groupData = groupData;
    HASH_ADD_KEYPTR(hh, entry, newGroup->groupId, strlen(newGroup->groupId), newGroup);
}

GroupEntry *findGroup(GenerateEntry * entry, char * groupId) {
    GroupHashEntry * groupEntry;
    HASH_FIND_STR(entry->usersMap, groupId, groupEntry);
    return groupEntry ? groupEntry->groupData : NULL;
}

void deleteGroup(GenerateEntry * entry, char * groupId) {
    GroupHashEntry * groupEntry;
    HASH_FIND_STR(entry->groupsMap, groupId, groupEntry);
    if (groupEntry) {
        HASH_DEL(entry->groupsMap, groupEntry);
        free(groupEntry->groupId); 
        free(groupEntry);          
    }
}


//agregar entreada al generate
void addGenerateEntry(char * fileId, DefType type, KeyNode * usersListFirst, Date * startDate){
    GenerateEntry * entry = malloc(sizeof(GenerateEntry));
    entry->fileId = strdup(fileId);
    entry->usersMap = copyUsersMap(usersTableMap);   //funcion copiado usersMap 
    entry->groupsMap = copyGroupsMap(usersTableMap); //funcion copiado groupsMap
    entry->type = type;
    entry->usersListFirst = usersListFirst;
    entry->startDate = startDate;
}

//copiar contenido hashmap
UserHashEntry *copyUsersMap(UserHashEntry *usersMap) {
    UserHashEntry *newMap = NULL, *currentUser, *tmp;
    HASH_ITER(hh, usersMap, currentUser, tmp) {
        UserHashEntry *newUser = malloc(sizeof(UserHashEntry));
        newUser->userId = strdup(currentUser->userId);
        newUser->userData = currentUser->userData; // save pointer to the data
        HASH_ADD_KEYPTR(hh, newMap, newUser->userId, strlen(newUser->userId), newUser);
    }
    return newMap;
}

GroupHashEntry *copyGroupsMap(GroupHashEntry *groupsMap) {
    GroupHashEntry *newMap = NULL, *currentGroup, *tmp;
    HASH_ITER(hh, groupsMap, currentGroup, tmp) {
        GroupHashEntry *newGroup = malloc(sizeof(GroupHashEntry));
        newGroup->groupId = strdup(currentGroup->groupId);
        newGroup->groupData = currentGroup->groupData; // save pointer to the data
        HASH_ADD_KEYPTR(hh, newMap, newGroup->groupId, strlen(newGroup->groupId), newGroup);
    }
    return newMap;
}



/** Node/Entry creation functions **/

GenerateEntry * createGenerateEntry(char * fileId, DefType type, KeyNode * usersListFirst, Date * startDate) {
    GenerateEntry *newEntry = malloc(sizeof(GenerateEntry));
    newEntry->fileId = strdup(fileId);
    
    newEntry->type = type;
    newEntry->usersListFirst = usersListFirst;
    newEntry->startDate = startDate;

    // copy current static hash maps
    newEntry->usersMap = copyUsersMap(usersTableMap);
    newEntry->groupsMap = copyGroupsMap(groupsTableMap);


    // add to static generateList
    if (firstGenerate == NULL) {
        firstGenerate = newEntry;
    } else {
        lastGenerate->next = newEntry;
    }

    return newEntry;
}

GroupEntry *createGroupEntry(Group * group) {
    GroupEntry *newGroup = malloc(sizeof(GroupEntry));
    newGroup->groupId = strdup(group->name);  //name -> id
    newGroup->tasksListFirst = NULL;
    newGroup->eventsListFirst = NULL;

    newGroup->group = group;  // --- check this

    // add group to static hash map
    addGroup(groupsTableMap, newGroup->groupId, newGroup);

    return newGroup;
}

UserEntry *createUserEntry(User * user) {
    UserEntry *newUser = malloc(sizeof(UserEntry));
    newUser->userId = strdup(user->name);

    newUser->user = user;  // --- check this

    newUser->tasksListFirst = NULL;
    newUser->eventsListFirst = NULL;
    newUser->groupFirst = NULL;

    // add user to static hash map
    addUser(usersTableMap, newUser->userId, newUser);

    return newUser;
}

