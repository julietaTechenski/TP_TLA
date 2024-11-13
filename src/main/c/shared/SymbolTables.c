#include "SymbolTables.h"

/** static variables  **/
static struct GenerateEntryNode * generateList = NULL; 

/** static hashmap for users  **/
static UserHashEntry * usersTableMap = NULL;

/** statis hashmap for groups  **/
static GroupHashEntry * groupsTableMap = NULL;


 /** ------------------------- Generate List managment functions ------------------------- **/

/** Add an entry to the Generate List  **/
void addGenerateEntry(Generate * generate){
    struct GenerateEntry * entry = malloc(sizeof(struct GenerateEntry));
    entry->generate = generate;
    entry->usersMap = copyUsersMap(usersTableMap);   
    entry->groupsMap = copyGroupsMap(groupsTableMap); 

    struct GenerateEntryNode * newNode = malloc(sizeof(struct GenerateEntryNode));
    newNode->entry = entry;
    newNode->next = NULL;

    if (generateList == NULL) {
        generateList = newNode;
    } else {
        struct GenerateEntryNode * current = generateList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


/** Profound copy of User Map **/
UserHashEntry * copyUsersMap(UserHashEntry * usersMap) {
    UserHashEntry * newMap = NULL, *currentUser, *tmp;
    HASH_ITER(hh, usersMap, currentUser, tmp) {
        UserHashEntry * newUser = malloc(sizeof(UserHashEntry));
        newUser->userId = strdup(currentUser->userId);
        newUser->userData = copyUserEntry(currentUser->userData);
        HASH_ADD_KEYPTR(hh, newMap, newUser->userId, strlen(newUser->userId), newUser);
    }
    return newMap;
}

UserEntry * copyUserEntry(UserEntry * originalEntry) {
    if (originalEntry == NULL) {
        return NULL;
    } 

    UserEntry * newEntry = malloc(sizeof(UserEntry));
    newEntry->user = originalEntry->user;
    newEntry->tasksListFirst = copyTaskList(originalEntry->tasksListFirst);
    newEntry->eventsListFirst = copyEventList(originalEntry->eventsListFirst);
    newEntry->groupFirst = copyGroupList(originalEntry->groupFirst);

    return newEntry;
}


/** Profound copy of Group Map **/
GroupHashEntry * copyGroupsMap(GroupHashEntry * groupsMap) {
    GroupHashEntry * newMap = NULL, * currentGroup, * tmp;
    HASH_ITER(hh, groupsMap, currentGroup, tmp) {
        GroupHashEntry * newGroup = malloc(sizeof(GroupHashEntry));
        newGroup->groupId = strdup(currentGroup->groupId);
        newGroup->groupData = copyGroupEntry(currentGroup->groupData); 
        HASH_ADD_KEYPTR(hh, newMap, newGroup->groupId, strlen(newGroup->groupId), newGroup);
    }
    return newMap;
}

GroupEntry * copyGroupEntry(GroupEntry * originalEntry) {
    if (originalEntry == NULL) {
        return NULL;
    } 

    GroupEntry * newEntry = malloc(sizeof(GroupEntry));
    newEntry->group = originalEntry->group;
    newEntry->tasksListFirst = copyTaskList(originalEntry->tasksListFirst);
    newEntry->eventsListFirst = copyEventList(originalEntry->eventsListFirst);

    return newEntry;
} 


/** Profound copy of Auxiliar Nodes **/
TaskNode * copyTaskList(TaskNode * originalTask) {
    if (originalTask == NULL) {
        return NULL;
    }

    TaskNode *newTaskNode = malloc(sizeof(TaskNode));
    newTaskNode->task = originalTask->task; 
    newTaskNode->next = copyTaskList(originalTask->next); 

    return newTaskNode;
}

EventNode * copyEventList(EventNode * originalEvent) {
    if (originalEvent == NULL) {
        return NULL;
    }

    EventNode * newEventNode = malloc(sizeof(EventNode));
    newEventNode->event = originalEvent->event; 
    newEventNode->next = copyEventList(originalEvent->next); 

    return newEventNode;
}

KeyNode * copyGroupList(KeyNode *originalGroup) {
    if (originalGroup == NULL) {
        return NULL;
    }

    KeyNode *newGroupNode = malloc(sizeof(KeyNode));
    newGroupNode->key = strdup(originalGroup->key);
    newGroupNode->next = copyGroupList(originalGroup->next); 

    return newGroupNode;
}


/** Free Generate List  **/
void freeGenerateEntryNodeList() {
    struct GenerateEntryNode * current = generateList;
    while (current) {
        struct GenerateEntryNode * temp = current;
        freeGenerateEntry(current->entry);
        current = current->next;
        free(temp);
    }
    generateList = NULL;
}

void freeGenerateEntry(struct GenerateEntry *entry) {
    if (entry) {
        destroyUsersMap(entry->usersMap);
        destroyGroupsMap(entry->groupsMap);
        free(entry);
    }
}



/** ------------------------- User Map managment functions ------------------------- **/

/** Add an entry to the Users Map  **/
void addUser(User * user) {
    UserHashEntry * newUser = malloc(sizeof(UserHashEntry));
    newUser->userId = strdup(user->name->id);  
    newUser->userData = createUserEntry(user);
    HASH_ADD_KEYPTR(hh, usersTableMap, newUser->userId, strlen(newUser->userId), newUser);
} 

UserEntry * createUserEntry(User * user) {
    UserEntry * newUser = malloc(sizeof(UserEntry));

    newUser->user = user;  
    newUser->tasksListFirst = NULL;
    newUser->eventsListFirst = NULL;
    newUser->groupFirst = NULL;

    return newUser;
}


/** Find an entry in the Users Map  **/
UserEntry * findUser(const char * userId) {
    UserHashEntry * userEntry;
    HASH_FIND_STR(usersTableMap, userId, userEntry);
    return userEntry ? userEntry->userData : NULL;
}


/** Adding a task for a User in the Users Map  **/
void addTaskToUser(const char * userId, CreateTask * task) {
    UserEntry * userEntry = findUser(userId);
    
    if (userEntry == NULL) {
        return;
    }

    addTaskNode(&userEntry->tasksListFirst, task);
}


/** Adding a event for a User in the Users Map  **/
void addEventToUser(const char * userId, CreateEvent * event) {
    UserEntry * userEntry = findUser(userId);
    
    if (userEntry == NULL) {
        return;
    }

    addEventNode(&userEntry->eventsListFirst, event);
}


/** Adding a event for a User in the Users Map  **/
void addGroupsToUser(const char * userId, Groups * groups){
    UserEntry * userEntry = findUser(userId);
    
    if (userEntry == NULL) {
        return;
    }

    if (groups->group_list != NULL) {
            struct GroupsList * currentGroup = groups->group_list;
            while (currentGroup != NULL) {
                addKeyNode(&userEntry->groupFirst, currentGroup->id->id);
                currentGroup = currentGroup->group_list;
            }
        }

}


/** Free Functions for Users Map  **/
void destroyUsersMap(UserHashEntry * usersMap) {
    UserHashEntry * currentEntry, * tmp;

    HASH_ITER(hh, usersMap, currentEntry, tmp) {
        if (currentEntry->userId) {
            free(currentEntry->userId); 
        }
        if (currentEntry->userData) {
            freeUserEntry(currentEntry->userData);
        }
        HASH_DEL(usersMap, currentEntry);
        free(currentEntry); 
    }
}

void deleteUser(char * userId) {
    UserHashEntry * userEntry;
    HASH_FIND_STR(usersTableMap, userId, userEntry);
    if (userEntry) {
        HASH_DEL(usersTableMap, userEntry);
        free(userEntry->userId); 
        freeUserEntry(userEntry->userData);
        free(userEntry);   
    }
}


void freeUserEntry(UserEntry * entry) {
    if (entry == NULL) {
        return;
    }

    freeTaskList(entry->tasksListFirst);
    freeEventList(entry->eventsListFirst);
    freeGroupList(entry->groupFirst);

    free(entry);
}



/** ------------------------- Group Map managment functions ------------------------- **/

/** Add an entry to the Groups Map  **/
void addGroup(Group * group) {
    GroupHashEntry * newGroup = malloc(sizeof(GroupHashEntry));
    newGroup->groupId = strdup(group->name->id);  
    newGroup->groupData = createGroupEntry(group);
    HASH_ADD_KEYPTR(hh, groupsTableMap, newGroup->groupId, strlen(newGroup->groupId), newGroup);
} 

GroupEntry * createGroupEntry(Group * group) {
    GroupEntry * newGroup = malloc(sizeof(GroupEntry));

    newGroup->group = group;
    newGroup->tasksListFirst = NULL;
    newGroup->eventsListFirst = NULL;

    return newGroup;
} 


/** Find an entry in the Groups Map  **/
GroupEntry * findGroup(const char * groupId) {
    GroupHashEntry * groupEntry;
    HASH_FIND_STR(groupsTableMap, groupId, groupEntry);
    return groupEntry ? groupEntry->groupData : NULL;
} 


/** Adding a task for a Group in the Groups Map  **/
void addTaskToGroup(const char * groupId, CreateTask * task) {
    GroupEntry * groupEntry = findGroup(groupId);
    
    if (groupEntry == NULL) {
        return;
    }

    addTaskNode(&groupEntry->tasksListFirst, task);
}


/** Adding a event for a Group in the Groups Map  **/
void addEventToGroup(const char * groupId, CreateEvent * event) {
    GroupEntry * groupEntry = findGroup(groupId);
    
    if (groupEntry == NULL) {
        return;
    }

    addEventNode(&groupEntry->eventsListFirst, event);
}


/** Free Functions for Groups Map  **/
void destroyGroupsMap(GroupHashEntry * groupsMap) {
    GroupHashEntry * currentEntry, * tmp;

    HASH_ITER(hh, groupsMap, currentEntry, tmp) {
        if (currentEntry->groupId) {
            free(currentEntry->groupId); 
        }
        if (currentEntry->groupData) {
            freeGroupEntry(currentEntry->groupData);
        }
        HASH_DEL(groupsMap, currentEntry);
        free(currentEntry); 
    }
}

void deleteGroup(char * groupId) {
    GroupHashEntry * groupEntry;
    HASH_FIND_STR(groupsTableMap, groupId, groupEntry);
    if (groupEntry) {
        HASH_DEL(groupsTableMap, groupEntry);
        free(groupEntry->groupId); 
        freeGroupEntry(groupEntry->groupData);
        free(groupEntry); 
    }
} 

void freeGroupEntry(GroupEntry * entry) {
    if (entry == NULL) {
        return;
    }

    freeTaskList(entry->tasksListFirst);
    freeEventList(entry->eventsListFirst);

    free(entry);
}


/** ------------------------- Add to items to lists ------------------------- **/

void addTaskNode(TaskNode ** head, CreateTask * task) {
    TaskNode * newNode = malloc(sizeof(TaskNode));
    if (newNode == NULL) {
        return;
    }

    newNode->task = task; 
    newNode->next = *head;  
    *head = newNode; 
}

void addEventNode(EventNode ** head, CreateEvent * event) {
    EventNode * newNode = malloc(sizeof(EventNode));
    if (newNode == NULL) {
        return;
    }

    newNode->event = event; 
    newNode->next = *head;  
    *head = newNode; 
}

void addKeyNode(KeyNode ** head, char * key) {
    KeyNode *newNode = malloc(sizeof(KeyNode));
    if (newNode == NULL) {
        return; 
    }

    newNode->key = strdup(key); 
    if (newNode->key == NULL) {
        free(newNode); 
        return;
    }
    newNode->next = *head; 
    *head = newNode; 
}


/** ------------------------- Free functions ------------------------- **/

/** Free functions for lists **/
void freeTaskList(TaskNode * taskList) {
    if (taskList == NULL) {
        return;
    }

    TaskNode *tmp = taskList;
    freeTaskList(taskList->next); 
    free(tmp); 
}

void freeEventList(EventNode * eventList) {
     if (eventList == NULL) {
        return;
    }

    EventNode *tmp = eventList;
    freeEventList(eventList->next); 
    free(tmp); 
}

void freeGroupList(KeyNode * groupList) {
    if (groupList == NULL) {
        return;
    }

    KeyNode *tmp = groupList;
    free(tmp->key);
    freeGroupList(groupList->next);
    free(tmp);
}




