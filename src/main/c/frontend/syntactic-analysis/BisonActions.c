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
	return program;
}




/**
 * Creates a new Ports structure with the given IDs.
 */
Ports *PortsSemanticAction(PortType portType, Id * id1, Id * id2) {
	Ports *ports = calloc(1, sizeof(Ports));
	ports->port_type = (PortType)portType;
	ports->name = id1;
	ports->path = id2;
	return ports;
}

/**
 * Creates a new UsersList structure with a single user ID.
 */
UsersList *UsersListSemanticAction(Id *id) {
	UsersList *usersList = calloc(1, sizeof(UsersList));
	usersList->id = id;
	usersList->user_list = NULL;
	return usersList;
}

/**
 * Adds a user to an existing UsersList.
 */

UsersList *UsersListAddUserSemanticAction(Id * user, UsersList *usersList) {
	UsersList *newUserList = calloc(1, sizeof(UsersList));
	newUserList->id = user;
	newUserList->user_list = usersList;
	return newUserList;
}

/**
 * Converts a UsersList to a Users structure.
 */
Users * UsersListToUsersSemanticAction(UsersList *usersList) {
	Users *users = calloc(1, sizeof(Users));
	users->user_list = usersList;
	return users;
}

/**
 * Creates a new empty Users structure.
 */
Users *UsersSemanticAction() {
	Users *users = calloc(1, sizeof(Users));
	users->all = NULL;
	users->user_list = NULL;
	return users;
}

/**
 * Creates a new Generate structure with the given components.
 */
Generate *GenerateSemanticAction(Id *generateId, Id *id, int defType, Users *users, char *date) {
	Generate *generate = calloc(1, sizeof(Generate));
	generate->id = generateId;
	generate->user_name = id;
	generate->def_type = (DefType)defType;  // convierte int a su valor del enum
	generate->users = users;
	generate->start_date = StringToDate(date);
	return generate;
}

/**
 * Adds a Generate to an existing GenerateList.
 */
GenerateList *GenerateListAddGenerateSemanticAction(Generate *generate, GenerateList *generateList) {
	GenerateList *newGenerateList = calloc(1, sizeof(GenerateList));
	newGenerateList->Generate = generate;
	newGenerateList->generate_list = generateList;
	return newGenerateList;
}

/**
 * Creates a new GenerateList with a single Generate.
 */
GenerateList *GenerateListSemanticAction(Generate *generate) {
	GenerateList *generateList = calloc(1, sizeof(GenerateList));
	generateList->Generate = generate;
	generateList->generate_list = NULL;
	return generateList;
}

/**
 * Creates a new UserGroup structure with the given group ID.
 */
UserGroup * UserGroupFromGroupSemanticAction(Id *group) {
	UserGroup * userGroup = calloc(1, sizeof(UserGroup));
	userGroup->group = group;
	return userGroup;
}

/**
 * Creates a new UserGroup structure with the given user ID.
 */
UserGroup * UserGroupFromUserSemanticAction(Id *user) {
	UserGroup * userGroup = calloc(1, sizeof(UserGroup));
	userGroup->user = user;
	return userGroup;
}

/**
 * Creates a new CreateTask structure with the given components.
 */
CreateTask *CreateTaskSemanticAction(Id *id, UserGroup *userGroup, char *date, char * stTime, char * endTime, char * description) {
	CreateTask *createTask = calloc(1, sizeof(CreateTask));
	createTask->id = id;
	createTask->user_group = userGroup;
	createTask->date = StringToDate(date);
	createTask->start_time = StringToTime(stTime);
	createTask->end_time = StringToTime(endTime);
	createTask->description = description;
	return createTask;
}

/**
 * Creates a new CreateEvent structure with the given components.
 */
CreateEvent *CreateEventSemanticAction(Id * id, UserGroup * userGroup, char * stDate, char * endDate) {
	CreateEvent *createEvent = calloc(1, sizeof(CreateEvent));
	createEvent->id = id;
	createEvent->user_group = userGroup;
	createEvent->start_date = StringToDate(stDate);
	createEvent->end_date = StringToDate(endDate);
	return createEvent;
}

/**
 * Creates a new Command structure from a Group.
 */
Command *CommandGroupSemanticAction(Group *group) {
	Command *command = calloc(1, sizeof(Command));
	command->group = group;
	return command;
}

/**
 * Creates a new Command structure from a User.
 */
Command *CommandUserSemanticAction(User *user) {
	Command *command = calloc(1, sizeof(Command));
	command->user = user;
	return command;
}

/**
 * Creates a new Command structure from a CreateEvent.
 */
Command *CommandCreateEventSemanticAction(CreateEvent *createEvent) {
	Command *command = calloc(1, sizeof(Command));
	command->create_event = createEvent;
	return command;
}

/**
 * Creates a new Command structure from a CreateTask.
 */
Command *CommandCreateTaskSemanticAction(CreateTask *createTask) {
	Command *command = calloc(1, sizeof(Command));
	command->create_task = createTask;
	return command;
}

/**
 * Creates a new Command structure for Ports.
 */
Command *CommandPortsSemanticAction(Ports *ports) {
    Command *command = calloc(1, sizeof(Command));
	command->ports = ports;
	return command;
}

/**
 * Creates a new Command structure from a Define.
 */
Command *CommandDefineSemanticAction(Define *define) {
	Command *command = calloc(1, sizeof(Command));
	command->define = define;
	return command;
}

Command *CommandGenerateListSemanticAction(GenerateList *generateList){
	Command *command = calloc(1, sizeof(Command));
	command->generate_list = generateList;
    return command;
}

/**
 * Adds a Command to an existing CommandList.
 */
CommandList *CommandListAddCommandSemanticAction(Command *command, CommandList *commandList) {
	CommandList *newCommandList = calloc(1, sizeof(CommandList));
	newCommandList->command = command;
	newCommandList->command_list = commandList;
	return newCommandList;
}

/**
 * Creates a new CommandList with a single Command.
 */
CommandList *CommandListSemanticAction(Command *command) {
	CommandList *commandList = calloc(1, sizeof(CommandList));
	commandList->command = command;
	commandList->command = NULL;
	return commandList;
}

/**
 * Creates a new Define structure with the given components.
 */
Define *DefineSemanticAction(Id *id, CommandList *commandList) {
	Define *define = calloc(1, sizeof(Define));
	define->id = id;
	define->command_list = commandList;
	return define;
}

/**
 * Creates a new HourRange structure with the given hours.
 */
HourRange *HourRangeSemanticAction(char * start, char *finish) {
	HourRange *hourRange = calloc(1, sizeof(HourRange));
	hourRange->start = StringToTime(start);
	hourRange->finish = StringToTime(finish);;
	return hourRange;
}

/**
 * Adds an HourRange to an existing HourRanges.
 */
HourRanges *HourRangesAddHourRangeSemanticAction(HourRange *hourRange, HourRanges *hourRanges) {
	HourRanges *newHourRanges = calloc(1, sizeof(HourRanges));
	newHourRanges->hour_range = hourRange;
	newHourRanges->hour_ranges = hourRanges;
	return newHourRanges;
}

/**
 * Creates an HourRanges from an HourRange.
 */
HourRanges *HourRangesSemanticAction(HourRange *hourRange) {
	HourRanges *newHourRanges = calloc(1, sizeof(HourRanges));
	newHourRanges->hour_range = hourRange;
	newHourRanges->hour_ranges = NULL;
	return newHourRanges;
}


/**
 * Creates a new HourList with a single HourRange.
 */
HourList *HourListSemanticAction(HourRanges *hourRanges) {
	HourList *hourList = calloc(1, sizeof(HourList));
	hourList->hour_ranges = hourRanges;
	return hourList;
}

/**
 * Creates a new User structure with the given components.
 */
User *UserSemanticAction(Id *userId, Id *roleId, Weekdays *weekdays, HourList *hourList) {
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
	Group *group = calloc(1, sizeof(Group));
	group->name = id;
	return group;
}

/**
 * Creates a new Id structure with the given value.
 */
Id *IdSemanticAction(const char *value) {
	Id *id = calloc(1, sizeof(Id));
	id->id = strdup(value);
	return id;
}

/**
 * Adds a Weekday to an existing WeekdayList.
 */

WeekdayList * WeekdaysListAddWeekdaySemanticAction(int weekday, WeekdayList * weekdaysList){
	WeekdayList * newWeekdayList = calloc(1, sizeof(WeekdayList));
	newWeekdayList->weekday = (Weekday)weekday;  // convierte int a su valor del enum
	newWeekdayList->weekday_list = weekdaysList;
	return newWeekdayList;
}

/**
 * Creates a new WeekdayList with a single Weekday.
 */

WeekdayList * WeekdaysListSemanticAction(int weekday){
	WeekdayList * newWeekdayList = calloc(1, sizeof(WeekdayList));
	newWeekdayList->weekday = (Weekday)weekday;
	newWeekdayList->weekday_list = NULL;
	return newWeekdayList;
}

/**
 * Creates a new Weekdays structure with the given WeekdayList.
 */
Weekdays * WeekdaysSemanticAction(WeekdayList * weekdaysList){
	Weekdays * weekdays = calloc(1, sizeof(Weekdays));
	weekdays->weekdays_list = weekdaysList;
	return weekdays;
}





/*** TYPE CONVERT FUNCTIONS */

/**
 * Converts a string to a Time structure.
 */
Time *StringToTime(const char *time) {
	int hours, minutes;
	if (sscanf(time, "%d:%d", &hours, &minutes) != 2) {
		fprintf(stderr, "Error: Formato de hora no válido: %s\n", time);
		return NULL;
	}
	Time * time_ = calloc(1, sizeof(Time));
	time_->hour = hours;
	time_->minute = minutes;
	return time_;
}

/**
 * Converts a string to a Date structure.
 */

Date *StringToDate(const char *date) {
	int day, month, year;
	if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3) {
		fprintf(stderr, "Error: Formato de fecha no válido: %s\n", date);
		return NULL;
	}
	Date * date_ = calloc(1, sizeof(Date));
	date_->day = day;
	date_->month = month;
	date_->year = year;
	return date_;
}