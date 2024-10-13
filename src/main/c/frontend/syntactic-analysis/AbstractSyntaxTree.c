#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/*
void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		free(constant);
	}
}

void releaseExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case ADDITION:
			case DIVISION:
			case MULTIPLICATION:
			case SUBTRACTION:
				releaseExpression(expression->leftExpression);
				releaseExpression(expression->rightExpression);
				break;
			case FACTOR:
				releaseFactor(expression->factor);
				break;
		}
		free(expression);
	}
}

void releaseFactor(Factor * factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case CONSTANT:
				releaseConstant(factor->constant);
				break;
			case EXPRESSION:
				releaseExpression(factor->expression);
				break;
		}
		free(factor);
	}
}


void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseExpression(program->expression);
		free(program);
	}
}
*/

/** PUBLIC FUNCTIONS */

void releaseProgram(Program * program){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseCommandList(program->command_list);
		free(program);
	}
}

void releaseCommandList(CommandList * commandList){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (commandList != NULL) {
		releaseCommand(commandList->command);
		releaseCommandList(commandList->command_list);
		free(commandList);
	}
}

void releaseCommand(Command * command){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (command != NULL) {
		switch (command->type) {
			case C_GROUP:
				releaseGroup(command->group);
				break;
			case C_USER:
				releaseUser(command->user);
				break;
			case C_EVENT:
				releaseCreateEvent(command->create_event);
				break;
			case C_TASK:
				releaseCreateTask(command->create_task);
				break;
			case C_IMPORT:
				releaseImport(command->import);
				break;
			case C_DEFINE:
				releaseDefine(command->define);
				break;
			case C_GENERATE:
				releaseGenerate(command->generate);
				break;
			case C_ADD:
				releaseAdd(command->add);
				break;
		}
		free(command);
	}
}


void releaseGroup(Group * group){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (group != NULL) {
		if (group->name != NULL) {
			releaseId(group->name);
		}
		free(group);
	}
}

void releaseUser(User * user){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (user != NULL) {
		if(user->name != NULL){
			releaseId(user->name);
		}
		if(user->role != NULL){
			releaseId(user->role);
		}
		releaseWeekdays(user->weekdays);
		releaseHourList(user->hour_list);
		free(user);
	}
}

void releaseCreateEvent(CreateEvent * createEvent){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (createEvent != NULL) {
		if (createEvent->id != NULL) {
			releaseId(createEvent->id);
		}
		releaseUserGroup(createEvent->user_group);
		releaseDate(createEvent->start_date);
		releaseDate(createEvent->end_date);
		free(createEvent);
	}
}


void releaseCreateTask(CreateTask * createTask){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (createTask != NULL) {
		if (createTask->id != NULL) {
			releaseId(createTask->id);
		}
		releaseUserGroup(createTask->user_group);
		releaseDate(createTask->date);
		releaseTime(createTask->start_time);
		releaseTime(createTask->end_time);
		if (createTask->description != NULL) {
			free(createTask->description);
		}
		free(createTask);
	}
}


void releaseImport(Import * import){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (import != NULL) {
		if(import->command_list != NULL) {
			releaseCommandList(import->command_list);
		}
		free(import);
	}
}


void releaseDefine(Define * define){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (define != NULL) {
		if (define->id != NULL) {
			releaseId(define->id);
		}
		releaseCommandList(define->command_list);
		free(define);
	}
}


void releaseGenerate(Generate * generate){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (generate != NULL) {
		if (generate->id != NULL) {
			releaseId(generate->id);
		}
		if (generate->user_name != NULL) {
			releaseId(generate->user_name);
		}
		releaseUsers(generate->users);
		releaseDate(generate->start_date);
		free(generate);
	}
}


void releaseAdd(Add * add){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (add != NULL) {
		if (add->user != NULL) {
			releaseId(add->user);
		}
		releaseGroups(add->groups);
		free(add);
	}
}


void releaseId(Id * id){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (id != NULL) {
		if (id->id != NULL) {
			free(id->id);
		}
		free(id);
	}
}


void releaseWeekdays(Weekdays * weekdays){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (weekdays != NULL) {
		releaseWeekdayList(weekdays->weekdays_list);
		free(weekdays);
	}
}



void releaseWeekdayList(WeekdayList * weekdayList){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (weekdayList != NULL) {
		releaseWeekdayList(weekdayList->weekday_list);
		free(weekdayList);
	}
}


void releaseHourList(HourList * hourList){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (hourList != NULL) {
		if (hourList->hour_ranges != NULL) {
			releaseHourRanges(hourList->hour_ranges);
		}
		free(hourList);
	}
}

void releaseUsers(Users * users){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (users != NULL) {
		if (users->type == USERS_LIST) {
			releaseUsersList(users->user_list);
		}
		free(users);
	}
}

void releaseUserGroup(UserGroup * userGroup){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (userGroup != NULL) {
		if (userGroup->type == GROUP_GROUP) {
			releaseId(userGroup->group);
		}
		else if (userGroup->type == GROUP_USER) {
			releaseId(userGroup->user);
		}
		free(userGroup);
	}
}


void releaseDate(Date * date){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (date != NULL) {
		free(date);
	}
}


void releaseTime(Time * time){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (time != NULL) {
		free(time);
	}
}


void releaseGroups(Groups * groups){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (groups != NULL) {
		if(groups->type == GROUPS_LIST){
			releaseGroupsList(groups->group_list);
		}
		free(groups);
	}
}


void releaseUsersList(UsersList * usersList){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (usersList != NULL) {
		if (usersList->id != NULL) {
			releaseId(usersList->id);
		}
		if (usersList->user_list != NULL) {
			releaseUsersList(usersList->user_list);
		}
		free(usersList);
	}
}

void releaseGroupsList(GroupsList * groupsList){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (groupsList != NULL) {
		if (groupsList->id != NULL) {
			releaseId(groupsList->id);
		}
		if (groupsList->group_list != NULL) {
			releaseGroupsList(groupsList->group_list);
		}
		free(groupsList);
	}
}

void releaseHourRanges(HourRanges * hourRanges){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (hourRanges != NULL) {
		if (hourRanges->hour_range != NULL) {
			releaseHourRange(hourRanges->hour_range);
		}
		if (hourRanges->hour_ranges != NULL) {
			releaseHourRanges(hourRanges->hour_ranges);
		}
		free(hourRanges);
	}
}

void releaseHourRange(HourRange * hourRange){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (hourRange != NULL) {
		if (hourRange->start != NULL) {
			releaseTime(hourRange->start);
		}
		if (hourRange->finish != NULL) {
			releaseTime(hourRange->finish);
		}
		free(hourRange);
	}
}