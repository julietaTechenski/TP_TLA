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
}

/*
FUNCIONES DE SEMANTICA
*/

/**
 * Creates a new Program structure with the given components.
 */
Program *ProgramSemanticAction(CompilerState *compilerState, Initialize *initialize, CommandList *commandList, GenerateList *generateList) {
	Program *program = calloc(1, sizeof(Program));
	program->initialize = initialize;
	program->command_list = commandList;
	program->generate_list = generateList;
	compilerState->abstractSyntaxtTree = program;
	return program;
}




/**
 * Creates a new Ports structure with the given IDs.
 */
///////////////////////////
Ports *PortsSemanticAction(Id *id1, Id *id2) {
	Ports *ports = calloc(1, sizeof(Ports));
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

///////////////////////////
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
///////////////////////////    all
Users *UsersSemanticAction() {
	Users *users = calloc(1, sizeof(Users));
	users->all = NULL;
	users->user_list = NULL;
	return users;
}

/**
 * Creates a new Generate structure with the given components.
 */
Generate *GenerateSemanticAction(Id *generateId, Id *id, DefType * defType, Users *users, Date *date) {
	Generate *generate = calloc(1, sizeof(Generate));
	generate->id = generateId;
	generate->users = id;
	generate->def_type = defType;
	generate->users = users;
	generate->start_date = date;
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
 * Creates a new UserGroup structure with the given ID.
 */
UserGroup * UserGroupSemanticAction(Id *id) {
	UserGroup * userGroup = calloc(1, sizeof(UserGroup));
	userGroup->group = id;
	return userGroup;
}

/**
 * Creates a new UserGroup structure from an existing Group.
 */
UserGroup *UserGroupFromGroupSemanticAction(Group *group) {
	UserGroup *userGroup = calloc(1, sizeof(UserGroup));
	userGroup->group = group;
	return userGroup;
}

/**
 * Creates a new CreateTask structure with the given components.
 */
CreateTask *CreateTaskSemanticAction(Id *id, UserGroup *userGroup, Date *date, Time * stTime, Time * endTime, char * description) {
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
CreateEvent *CreateEventSemanticAction(Id *id, UserGroup *userGroup, Date *stDate, Date *endDate) {
	CreateEvent *createEvent = calloc(1, sizeof(CreateEvent));
	createEvent->id = id;
	createEvent->user_group = userGroup;
	createEvent->start_date = stDate;
	createEvent->end_date = endDate;
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
 * Creates a new Command structure for Ports with the given PortType.
 */
Command *CommandPortsSemanticAction(Ports *ports, PortType portType) {
	Command *command = calloc(1, sizeof(Command));
	if(portType == IMPORT){
		command->import_ports = ports;
	}
	else{
		command->export_ports = ports;
	}
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
HourRange *HourRangeSemanticAction(Time * start, Time *finish) {
	HourRange *hourRange = calloc(1, sizeof(HourRange));
	hourRange->start = start;
	hourRange->finish = finish;
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
///////////////////////////
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
 * Creates a new Initialize structure with the given components.
 */
/////////////////////////// tipo USer inicializando users
Initialize *InitializeSemanticAction(Group *group, Users *users) {
	Initialize *initialize = calloc(1, sizeof(Initialize));
	initialize->group = group;
	initialize->user = users;
	return initialize;
}

/**
 * Creates a new Id structure with the given value.
 */
Id *IdSemanticAction(const char *value) {
	Id *id = calloc(1, sizeof(Id));
	id->id = strdup(value);
	return id;
}
