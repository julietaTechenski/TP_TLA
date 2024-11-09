#include "SymbolTables.h"


void addUser(GenerateEntry *entry, char *userId, UserEntry *userData) {
    UserHashEntry *newUser = malloc(sizeof(UserHashEntry));
    newUser->userId = strdup(userId);  
    newUser->userData = userData;
    HASH_ADD_KEYPTR(hh, entry->usersMap, newUser->userId, strlen(newUser->userId), newUser);
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

void addGroup(GenerateEntry * entry, char * groupId, GroupEntry * groupData) {
    GroupHashEntry * newGroup = malloc(sizeof(GroupHashEntry));
    newGroup->groupId = strdup(groupId);  
    newGroup->groupData = groupData;
    HASH_ADD_KEYPTR(hh, entry->groupsMap, newGroup->groupId, strlen(newGroup->groupId), newGroup);
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
UserHashEntry * copyUsersMap(UserHashEntry * usersMap){

}

GroupHashEntry * copyGroupsMap(GroupHashEntry * groupsMap){

}