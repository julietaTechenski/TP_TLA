#include "SymbolTables.h"

/** static variables  **/
static struct GenerateEntryNode * generateList = NULL; 

/** static hashmap for users  **/
static UserHashEntry * usersTableMap = NULL;

/** static hashmap for groups  **/
static GroupHashEntry * groupsTableMap = NULL;

/** static hashmap for code blocks information **/
static CodeBlocksHashEntry * clodeBlocksTableMap = NULL;


 /** ------------------------- Definition of private functions ------------------------- **/

 // Generate List managment functions
int addGenerateEntryInGenerateList(Generate * generate, GenerateEntryNode ** generateLi, UserHashEntry * usersMap, GroupHashEntry * groupsMap);
static UserHashEntry * copyUsersMap(UserHashEntry * usersMap);
static UserEntry * copyUserEntry(UserEntry * originalEntry);
static GroupHashEntry * copyGroupsMap(GroupHashEntry * groupsMap);
static GroupEntry * copyGroupEntry(GroupEntry * originalEntry);
static TaskNode * copyTaskList(TaskNode * originalTask);
static EventNode * copyEventList(EventNode * originalEvent);
static KeyNode * copyGroupList(KeyNode * originalGroup);
static void freeGenerateEntry(struct GenerateEntry * entry);
void freeGenerateEntryNodeList(GenerateEntryNode * generateLi);


// User Map managment functions
static int addUserToUserMap(User * user, UserHashEntry ** usersMap);
static UserEntry * createUserEntry(User * user);
static UserEntry * findUserInMap(const char * userId, UserHashEntry * usersMap);
static int addEventToUserInUsersMap(const char * userId, CreateEvent * event, UserHashEntry ** usersMap);
static int addGroupsToUserInUsersMap(const char * userId, Groups * groups, UserHashEntry ** usersMap, GroupHashEntry ** groupsMap);
static int addTaskToUserInUsersMap(const char * userId, CreateTask * task, UserHashEntry ** usersMap);
static void destroyUsersMap(UserHashEntry * usersMap);
static void deleteUserInUserMap(char * userId, UserHashEntry * usersMap);
static void freeUserEntry(UserEntry *entry);


// Group Map managment functions
static int addGroupToGroupMap(Group * group, GroupHashEntry ** groupsMap);
static GroupEntry * createGroupEntry(Group * group);
static GroupEntry * findGroupInMap(const char * groupId, GroupHashEntry * groupsMap);
static int addTaskToGroupInGroupsMap(const char * groupId, CreateTask * task, GroupHashEntry ** groupsMap);
static int addEventToGroupInGroupsMap(const char * groupId, CreateEvent * event, GroupHashEntry ** groupsMap);
static void destroyGroupsMap(GroupHashEntry * groupsMap);
static void deleteGroupInGroupMap(char * groupId, GroupHashEntry * groupsMap);
static void freeGroupEntry(GroupEntry * entry);


// Code Blocks List managment functions
CodeBlocksEntry * createCodeBlocksEntry(const char * codeBlockId);
CodeBlocksEntry * findCodeBlock(const char * codeBlockId);


// Add to items to lists
static void addTaskNode(TaskNode ** head, CreateTask * task);
static void addEventNode(EventNode ** head, CreateEvent * event);
static void addKeyNode(KeyNode ** head, char * key);


// Free functions
static void freeTaskList(TaskNode * taskList);
static void freeEventList(EventNode * eventList);
static void freeGroupList(KeyNode * groupList);


 /** ------------------------- Generate List managment functions ------------------------- **/

/** Add an entry to the Generate List  **/
int addGenerateEntry(Generate * generate){
    return addGenerateEntryInGenerateList(generate, &(generateList), usersTableMap, groupsTableMap);
}

int addGenerateEntryInGenerateList(Generate * generate, GenerateEntryNode ** generateLi, UserHashEntry * usersMap, GroupHashEntry * groupsMap){
    // TODO : verify is block of code exists
    UserHashEntry * current_user, *tmp;
    
    HASH_ITER(hh, usersTableMap, current_user, tmp) {
        printf("User ID: %s, User Data: %s\n", current_user->userId, current_user->userData->user->role->id);
    }

    // Verify that the generate users exist
    UsersList * current = generate->users->user_list;
    while(current != NULL) {
        UserEntry * userEntry = findUserInMap(current->id->id, usersMap);
		if(userEntry == NULL) {
            // TODO: finish excecution ; as of now, it does not create the generate
            printf("User with ID %s not found in usersTableMap\n", current->id->id);
            return ERROR;
        }
        current = current->user_list;
    }

    struct GenerateEntry * entry = malloc(sizeof(struct GenerateEntry));
    entry->generate = generate;
    entry->usersMap = copyUsersMap(usersMap);   
    entry->groupsMap = copyGroupsMap(groupsMap); 

    struct GenerateEntryNode * newNode = malloc(sizeof(struct GenerateEntryNode));
    newNode->entry = entry;
    newNode->next = NULL;

    if (*generateLi == NULL) {
        *generateLi = newNode;
    } else {
        struct GenerateEntryNode * current = *generateLi;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    return SUCCESS;
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


/** Gets the list of Generates  **/
GenerateEntryNode * getGenerateList() {
    return generateList;
}


/** Free Generate List  **/
void freeGenerateEntryNodeList(GenerateEntryNode * generateLi) {
    struct GenerateEntryNode * current = generateLi;
    while (current) {
        struct GenerateEntryNode * temp = current;
        freeGenerateEntry(current->entry);
        current = current->next;
        free(temp);
    }
    generateLi = NULL;
}

void destroyGenerateList(){
    freeGenerateEntryNodeList(generateList);
}

void freeGenerateEntry(struct GenerateEntry * entry) {
    if (entry) {
        destroyUsersMap(entry->usersMap);
        destroyGroupsMap(entry->groupsMap);
        free(entry);
    }
}


/** ------------------------- Users Table Map managment functions ------------------------- **/

/** Add an entry to the Users Table Map  **/
int addUser(User * user) {
    return addUserToUserMap(user, &(usersTableMap));
} 

/** Find an entry in the Users Table Map  **/
UserEntry * findUser(const char * userId) {
    return findUserInMap(userId, usersTableMap);
}

/** Adding a task for a User in the Users Table Map  **/
int addTaskToUser(const char * userId, CreateTask * task) {
    return addTaskToUserInUsersMap(userId, task, &(usersTableMap));
}

/** Adding a event for a User in the Users Table Map  **/
int addEventToUser(const char * userId, CreateEvent * event) {
    return addEventToUserInUsersMap(userId, event, &(usersTableMap));
}

/** Adding a event for a User in the Users Table Map  **/
int addGroupsToUser(const char * userId, Groups * groups) {
    return addGroupsToUserInUsersMap(userId, groups, &(usersTableMap), &(groupsTableMap));
}

/** Free function for Users Table Map  **/
void destroyUsersTableMap(){
    destroyUsersMap(usersTableMap);
}

void deleteUser(char * userId) {
    return deleteUserInUserMap(userId, usersTableMap);
}


/** ------------------------- Group Table Map managment functions ------------------------- **/

/** Add an entry to the Groups Map  **/
int addGroup(Group * group) {
    return addGroupToGroupMap(group, &(groupsTableMap));
} 

/** Find an entry in the Groups Map  **/
GroupEntry * findGroup(const char * groupId) {
    return findGroupInMap(groupId, groupsTableMap);
} 

/** Adding a task for a Group in the Groups Map  **/
int addTaskToGroup(const char * groupId, CreateTask * task) {
    addTaskToGroupInGroupsMap(groupId, task, &(groupsTableMap));
}

/** Adding a event for a Group in the Groups Map  **/
int addEventToGroup(const char * groupId, CreateEvent * event) {
    return addEventToGroupInGroupsMap(groupId, event, &(groupsTableMap));
}

/** Free Functions for Groups Table Map  **/
void destroyGroupsTableMap(){
    destroyGroupsMap(groupsTableMap);
}

void deleteGroup(char * groupId) {
    return deleteGroupInGroupMap(groupId, groupsTableMap);
} 


/** ------------------------- Users Map managment functions ------------------------- **/

/** Add an entry any the Users Map  **/
int addUserToUserMap(User * user, UserHashEntry ** usersMap) {
    UserEntry * userEntry = findUserInMap(user->name->id, *usersMap);
    if(userEntry != NULL) {
        return ERROR;
    }

    UserHashEntry * newUser = malloc(sizeof(UserHashEntry));
    newUser->userId = strdup(user->name->id);  
    newUser->userData = createUserEntry(user);
    HASH_ADD_KEYPTR(hh, *usersMap, newUser->userId, strlen(newUser->userId), newUser);

    return SUCCESS;
}

UserEntry * createUserEntry(User * user) {
    UserEntry * newUser = malloc(sizeof(UserEntry));

    newUser->user = user;  
    newUser->tasksListFirst = NULL;
    newUser->eventsListFirst = NULL;
    newUser->groupFirst = NULL;

    return newUser;
}


/** Find an entry in any Users Map  **/
UserEntry * findUserInMap(const char * userId, UserHashEntry * usersMap) {
    UserHashEntry * userEntry;
    HASH_FIND_STR(usersMap, userId, userEntry);
    return userEntry ? userEntry->userData : NULL;
}


/** Add an task to any Users Map  **/
int addTaskToUserInUsersMap(const char * userId, CreateTask * task, UserHashEntry ** usersMap) {
    UserEntry * userEntry = findUserInMap(userId, *usersMap);
    
    if (userEntry == NULL) {
        // TODO : finish excecution
        return ERROR;
    }

    addTaskNode(&userEntry->tasksListFirst, task);
    return SUCCESS;
}


/** Add an event to any Users Map  **/
int addEventToUserInUsersMap(const char * userId, CreateEvent * event, UserHashEntry ** usersMap) {
    UserEntry * userEntry = findUserInMap(userId, *usersMap);
    
    if (userEntry == NULL) {
        return ERROR;
    }

    addEventNode(&userEntry->eventsListFirst, event);

    return SUCCESS;
}


/** Add an event to any Users Map  **/
int addGroupsToUserInUsersMap(const char * userId, Groups * groups, UserHashEntry ** usersMap, GroupHashEntry ** groupsMap) {
    GroupsList * current = groups->group_list;
    while(current != NULL) {
        GroupEntry * groupEntry = findGroupInMap(current->id->id, *groupsMap);
        if(groupEntry == NULL) {
            return ERROR;
        }
        current = current->group_list;
    }    
    
    UserEntry * userEntry = findUserInMap(userId, *usersMap);
    if (userEntry == NULL) {
        return ERROR;
    }

    if (groups->group_list != NULL) {
            struct GroupsList * currentGroup = groups->group_list;
            while (currentGroup != NULL) {
                addKeyNode(&userEntry->groupFirst, currentGroup->id->id);
                currentGroup = currentGroup->group_list;
            }
        }

    return SUCCESS; 
}



/** Free Functions for any Users Map  **/
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

void deleteUserInUserMap(char * userId, UserHashEntry * usersMap) {
    UserHashEntry * userEntry;
    HASH_FIND_STR(usersMap, userId, userEntry);
    if (userEntry) {
        HASH_DEL(usersMap, userEntry);
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

/** Add an entry any Group Map  **/
int addGroupToGroupMap(Group * group, GroupHashEntry ** groupsMap) {
    GroupEntry * groupEntry = findGroupInMap(group->name->id, *groupsMap);
    if(groupEntry != NULL) {
        return ERROR;
    }

    GroupHashEntry * newGroup = malloc(sizeof(GroupHashEntry));
    newGroup->groupId = strdup(group->name->id);  
    newGroup->groupData = createGroupEntry(group);
    HASH_ADD_KEYPTR(hh, *groupsMap, newGroup->groupId, strlen(newGroup->groupId), newGroup);

    return SUCCESS;
}

GroupEntry * createGroupEntry(Group * group) {
    GroupEntry * newGroup = malloc(sizeof(GroupEntry));

    newGroup->group = group;
    newGroup->tasksListFirst = NULL;
    newGroup->eventsListFirst = NULL;

    return newGroup;
} 


/** Find an entry any Group Map  **/
GroupEntry * findGroupInMap(const char * groupId, GroupHashEntry * groupsMap) {
    GroupHashEntry * groupEntry;
    HASH_FIND_STR(groupsMap, groupId, groupEntry);
    return groupEntry ? groupEntry->groupData : NULL;
}


/** Add task in any Group Map  **/
int addTaskToGroupInGroupsMap(const char * groupId, CreateTask * task, GroupHashEntry ** groupsMap) {
    GroupEntry * groupEntry = findGroupInMap(groupId, *groupsMap);
    
    if (groupEntry == NULL) {
        return ERROR;  // TODO : finish excecution
    }

    addTaskNode(&groupEntry->tasksListFirst, task);
    
    return SUCCESS;
}


/** Add event in any Group Map  **/
int addEventToGroupInGroupsMap(const char * groupId, CreateEvent * event, GroupHashEntry ** groupsMap) {
    GroupEntry * groupEntry = findGroupInMap(groupId, *groupsMap);
    
    if (groupEntry == NULL) {
        return ERROR;  // TODO : finish excecution
    }

    addEventNode(&groupEntry->eventsListFirst, event);

    return SUCCESS;
}


/** Free Functions for any Users Map  **/
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

void deleteGroupInGroupMap(char * groupId, GroupHashEntry * groupsMap) {
    GroupHashEntry * groupEntry;
    HASH_FIND_STR(groupsMap, groupId, groupEntry);
    if (groupEntry) {
        HASH_DEL(groupsMap, groupEntry);
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


/** ------------------------- Code Blocks List managment functions ------------------------- **/

int addCodeBlockEntry(const char * codeBlockId) {
    CodeBlocksHashEntry * entry = NULL;

    HASH_FIND_STR(clodeBlocksTableMap, codeBlockId, entry);
    if (entry != NULL) {
        return ERROR; 
    }

    entry = malloc(sizeof(CodeBlocksHashEntry));
    entry->codeBlocksId = strdup(codeBlockId);
    entry->codeBlocksData = createCodeBlocksEntry(codeBlockId); 

    HASH_ADD_KEYPTR(hh, clodeBlocksTableMap, entry->codeBlocksId, strlen(entry->codeBlocksId), entry);

    return SUCCESS;
}

CodeBlocksEntry * createCodeBlocksEntry(const char * codeBlockId) {
    CodeBlocksEntry * newEntry = malloc(sizeof(CodeBlocksEntry));
    newEntry->id = strdup(codeBlockId);
    newEntry->generateList = NULL;     
    newEntry->usersTableMap = NULL;
    newEntry->groupsTableMap = NULL;

    return newEntry;
}

CodeBlocksEntry * findCodeBlock(const char * codeBlockId) {
    CodeBlocksHashEntry * codeBlockEntry;
    HASH_FIND_STR(clodeBlocksTableMap, codeBlockId, codeBlockEntry);
    return codeBlockEntry ? codeBlockEntry->codeBlocksData : NULL;
}

int addUserToCodeBlockUsersMap(const char * codeBlockId, User * user) {
    CodeBlocksEntry * codeBlock = findCodeBlock(codeBlockId);
    if (codeBlock == NULL) {
        return ERROR;
    }

    return addUserToUserMap(user, &(codeBlock->usersTableMap));
}

int addGroupToCodeBlockUsersMap(const char * codeBlockId, Group * group) {
    CodeBlocksEntry * codeBlock = findCodeBlock(codeBlockId);
    if (codeBlock == NULL) {
        return ERROR;
    }

    return addGroupToGroupMap(group, &(codeBlock->groupsTableMap));
}

int addGenerateEntryToCodeBlock(const char * codeBlockId, Generate * generate) {
    CodeBlocksEntry * codeBlock = findCodeBlock(codeBlockId);
    if (codeBlock == NULL) {
        return ERROR;
    }
    
    return addGenerateEntryInGenerateList(generate, &(codeBlock->generateList), codeBlock->usersTableMap, codeBlock->groupsTableMap);
}

void destroyCodeBlock() {
    CodeBlocksHashEntry * current, * tmp;
    HASH_ITER(hh, clodeBlocksTableMap, current, tmp) {
        HASH_DEL(clodeBlocksTableMap, current);

        free(current->codeBlocksId);  
        destroyGenerateList(current->codeBlocksData->generateList);
        destroyUsersMap(current->codeBlocksData->usersTableMap);
        destroyGroupsMap(current->codeBlocksData->groupsTableMap);
        free(current->codeBlocksData);
        free(current); 
    }
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




