#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

/*
Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}

Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->expression = expression;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}*/

/*
FUNCIONES DE SEMANTICA
*/

/**
 * Creates a new Program structure with the given components.
 */
Program * ProgramSemanticAction(CompilerState * compilerState, CommandList * commandList){
	Program *program = calloc(1, sizeof(Program));
	program->command_list = commandList;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}




/**
 * Creates a new Ports structure with the given IDs.
 */
Import *ImportSemanticAction(CommandList * command_list) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Import *import = calloc(1, sizeof(Import));
	import->command_list= command_list;
	return import;
}

/**
 * Creates a new UsersList structure with a single user ID.
 */
UsersList *UsersListSemanticAction(Id * id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UsersList *usersList = calloc(1, sizeof(UsersList));
	usersList->id = id;
	usersList->user_list = NULL;
	return usersList;
}

/**
 * Adds a user to an existing UsersList.
 */

UsersList *UsersListAddUserSemanticAction(Id * user, UsersList * usersList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UsersList *newUserList = calloc(1, sizeof(UsersList));
	newUserList->id = user;
	newUserList->user_list = usersList;
	return newUserList;
}

/**
 * Converts a UsersList to a Users structure.
 */
Users * UsersListToUsersSemanticAction(UsersList * usersList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Users *users = calloc(1, sizeof(Users));
	users->user_list = usersList;
	users->type = USERS_LIST;
	return users;
}

/**
 * Creates a new empty Users structure.
 */
Users *UsersSemanticAction() {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Users *users = calloc(1, sizeof(Users));
	users->type = USERS_ALL;
	return users;
}

/**
 * Creates a new GroupsList structure with a single group ID.
 */
GroupsList * GroupsListSemanticAction(Id * id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GroupsList * groupsList = calloc(1, sizeof(GroupsList));
	groupsList->id = id;
	groupsList->group_list = NULL;
	return groupsList;
}

/**
 * Adds a group to an existing GroupsList.
 */

GroupsList * GroupsListAddGroupSemanticAction(Id * group, GroupsList * groupsList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GroupsList * newGroupsList = calloc(1, sizeof(GroupsList));
	newGroupsList->id = group;
	newGroupsList->group_list = groupsList;
	return newGroupsList;
}

/**
 * Converts a GroupsList to a Groups structure.
 */
Groups * GroupsListToGroupsSemanticAction(GroupsList * groupsList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Groups * groups = calloc(1, sizeof(Groups));
	groups->group_list = groupsList;
	groups->type = GROUPS_LIST;
	return groups;
}

/**
 * Creates a new empty Groups structure.
 */
Groups * GroupsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Groups * groups = calloc(1, sizeof(Groups));
	groups->type = ALL;
	return groups;
}

/**
 * Creates a new Generate structure with the given components.
 */
Generate *GenerateSemanticAction(Id * generateId, Id * id, DefType defType, Users * users, Date * date) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Generate *generate = calloc(1, sizeof(Generate));
	generate->id = generateId;
	generate->user_name = id;
	generate->def_type = defType;  // convierte int a su valor del enum
	generate->users = users;
	generate->start_date = date;
	return generate;
}



/**
 * Creates a new UserGroup structure with the given group ID.
 */
UserGroup * UserGroupFromGroupSemanticAction(Id * group) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserGroup * userGroup = calloc(1, sizeof(UserGroup));
	userGroup->group = group;
	userGroup->type = GROUP_GROUP;
	return userGroup;
}

/**
 * Creates a new UserGroup structure with the given user ID.
 */
UserGroup * UserGroupFromUserSemanticAction(Id * user) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserGroup * userGroup = calloc(1, sizeof(UserGroup));
	userGroup->user = user;
	userGroup->type = GROUP_USER;
	return userGroup;
}

/**
 * Creates a new CreateTask structure with the given components.
 */
CreateTask *CreateTaskSemanticAction(Id * id, UserGroup * userGroup, Date * date, Time * stTime, Time * endTime, char * description) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CreateTask *createTask = calloc(1, sizeof(CreateTask));
	createTask->id = id;
	createTask->user_group = userGroup;
	createTask->date = date;
	createTask->start_time = stTime;
	createTask->end_time = endTime;
	createTask->description = description;
	return createTask;
}

/**
 * Creates a new CreateEvent structure with the given components.
 */
CreateEvent *CreateEventSemanticAction(Id * id, UserGroup * userGroup, Date * stDate, Date * endDate) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CreateEvent *createEvent = calloc(1, sizeof(CreateEvent));
	createEvent->id = id;
	createEvent->user_group = userGroup;
	createEvent->start_date = stDate;
	createEvent->end_date = endDate;
	return createEvent;
}

/**
 * Creates a new Add structure with the given components.
 */
Add * AddSemanticAction(Id * user, Groups * groups) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Add * add = calloc(1, sizeof(Add));
	add->user = user;
	add->groups = groups;
	return add;
}

/**
 * Creates a new Command structure from a Group.
 */
Command *CommandGroupSemanticAction(Group * group) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->group = group;
	command->type = C_GROUP;
	return command;
}

/**
 * Creates a new Command structure from a User.
 */
Command *CommandUserSemanticAction(User * user) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->user = user;
	command->type = C_USER;
	return command;
}

/**
 * Creates a new Command structure from a CreateEvent.
 */
Command *CommandCreateEventSemanticAction(CreateEvent * createEvent) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->create_event = createEvent;
	command->type = C_EVENT;
	return command;
}

/**
 * Creates a new Command structure from a CreateTask.
 */
Command *CommandCreateTaskSemanticAction(CreateTask * createTask) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->create_task = createTask;
	command->type = C_TASK;
	return command;
}

/**
 * Creates a new Command structure for Ports.
 */
Command *CommandImportSemanticAction(Import * import) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Command *command = calloc(1, sizeof(Command));
	command->import = import;
	command->type = C_IMPORT;
	return command;
}

/**
 * Creates a new Command structure from a Define.
 */
Command *CommandDefineSemanticAction(Define * define) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->define = define;
	command->type = C_DEFINE;
	return command;
}

Command *CommandGenerateSemanticAction(Generate *generate){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->generate = generate;
	command->type = C_GENERATE;
    return command;
}

Command *CommandAddSemanticAction(Add * add){	
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Command *command = calloc(1, sizeof(Command));
	command->add = add;
	command->type = C_ADD;
    return command;
}

/**
 * Adds a Command to an existing CommandList.
 */
CommandList *CommandListAddCommandSemanticAction(Command * command, CommandList * commandList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CommandList *newCommandList = calloc(1, sizeof(CommandList));
	newCommandList->command = command;
	newCommandList->command_list = commandList;
	return newCommandList;
}

/**
 * Creates a new CommandList with a single Command.
 */
CommandList *CommandListSemanticAction(Command * command) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CommandList *commandList = calloc(1, sizeof(CommandList));
	commandList->command = command;
	commandList->command = NULL;
	return commandList;
}

/**
 * Creates a new Define structure with the given components.
 */
Define *DefineSemanticAction(Id *id, CommandList * commandList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Define *define = calloc(1, sizeof(Define));
	define->id = id;
	define->command_list = commandList;
	return define;
}

/**
 * Creates a new HourRange structure with the given hours.
 */
HourRange *HourRangeSemanticAction(Time * start, Time * finish) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HourRange *hourRange = calloc(1, sizeof(HourRange));
	hourRange->start = start;
	hourRange->finish = finish;
	return hourRange;
}

/**
 * Adds an HourRange to an existing HourRanges.
 */
HourRanges *HourRangesAddHourRangeSemanticAction(HourRange * hourRange, HourRanges * hourRanges) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HourRanges *newHourRanges = calloc(1, sizeof(HourRanges));
	newHourRanges->hour_range = hourRange;
	newHourRanges->hour_ranges = hourRanges;
	return newHourRanges;
}

/**
 * Creates an HourRanges from an HourRange.
 */
HourRanges *HourRangesSemanticAction(HourRange * hourRange) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HourRanges *newHourRanges = calloc(1, sizeof(HourRanges));
	newHourRanges->hour_range = hourRange;
	newHourRanges->hour_ranges = NULL;
	return newHourRanges;
}


/**
 * Creates a new HourList with a single HourRange.
 */
HourList *HourListSemanticAction(HourRanges * hourRanges) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HourList *hourList = calloc(1, sizeof(HourList));
	hourList->hour_ranges = hourRanges;
	return hourList;
}

/**
 * Creates a new User structure with the given components.
 */
User *UserSemanticAction(Id * userId, Id * roleId, Weekdays * weekdays, HourList * hourList) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	User *user = calloc(1, sizeof(User));
	user->name = userId;
	user->role = roleId;
	user->weekdays = weekdays;
	user->hour_list = hourList;
	return user;
}

/**
 * Creates a new Group structure with the given ID.
 */
Group *GroupSemanticAction(Id *id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Group *group = calloc(1, sizeof(Group));
	group->name = id;
	return group;
}

/**
 * Creates a new Id structure with the given value.
 */
Id *IdSemanticAction(const char * value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Id *id = calloc(1, sizeof(Id));
	id->id = strdup(value);
	return id;
}

/**
 * Adds a Weekday to an existing WeekdayList.
 */

WeekdayList * WeekdaysListAddWeekdaySemanticAction(Weekday weekday, WeekdayList * weekdaysList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	WeekdayList * newWeekdayList = calloc(1, sizeof(WeekdayList));
	newWeekdayList->weekday = weekday;  // convierte int a su valor del enum
	newWeekdayList->weekday_list = weekdaysList;
	return newWeekdayList;
}

/**
 * Creates a new WeekdayList with a single Weekday.
 */

WeekdayList * WeekdaysListSemanticAction(Weekday weekday){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	WeekdayList * newWeekdayList = calloc(1, sizeof(WeekdayList));
	newWeekdayList->weekday = weekday;
	newWeekdayList->weekday_list = NULL;
	return newWeekdayList;
}

/**
 * Creates a new Weekdays structure with the given WeekdayList.
 */
Weekdays * WeekdaysSemanticAction(WeekdayList * weekdaysList){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Weekdays * weekdays = calloc(1, sizeof(Weekdays));
	weekdays->weekdays_list = weekdaysList;
	return weekdays;
}
