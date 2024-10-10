#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

/*
Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);
*/

UsersList * UsersListSemanticAction(Id * id);
UsersList * UsersListAddUserSemanticAction(Id * user, UsersList * usersList);   
Users * UsersListToUsersSemanticAction(UsersList * usersList);
Users * UsersSemanticAction();      
Generate * GenerateSemanticAction(Id *generateId, Id *id, int defType, Users *users, char *date);
GenerateList * GenerateListAddGenerateSemanticAction(Generate * generate, GenerateList * generateList);
GenerateList * GenerateListSemanticAction(Generate * generate);
UserGroup * UserGroupFromUserSemanticAction(Id * user);
UserGroup * UserGroupFromGroupSemanticAction(Id * group);
CreateTask * CreateTaskSemanticAction(Id *id, UserGroup *userGroup, char *date, char * stTime, char * endTime, char * description); 
CreateEvent * CreateEventSemanticAction(Id * id, UserGroup * userGroup, char * stDate, char * endDate);  
Command * CommandGroupSemanticAction(Group * group);
Command * CommandUserSemanticAction(User * user);
Command * CommandCreateEventSemanticAction(CreateEvent * createEvent);
Command * CommandCreateTaskSemanticAction(CreateTask * createTask);
Command * CommandPortsSemanticAction(Ports * ports);
Command * CommandDefineSemanticAction(Define * define);
CommandList * CommandListAddCommandSemanticAction(Command * command, CommandList * commandList);
CommandList * CommandListSemanticAction(Command * command);
Define * DefineSemanticAction(Id * id, CommandList * commandList);
HourRange * HourRangeSemanticAction(char * hour1, char * hour2);
HourRanges * HourRangesAddHourRangeSemanticAction(HourRange * hourRange, HourRanges * hourRanges);
HourRanges * HourRangesSemanticAction(HourRange * hourRange);
HourList * HourListSemanticAction(HourRanges * hourRanges);
User * UserSemanticAction(Id * userId, Id * roleId, Weekdays * weekdays, HourList * HourList);
Group * GroupSemanticAction(Id * id);
Initialize * InitializeSemanticAction(Group * group, User * user);
Id * IdSemanticAction(const char * value);
Program * ProgramSemanticAction(CompilerState * compilerState, Initialize * initialize, CommandList * commandList, GenerateList * generateList);
Ports * PortsSemanticAction(PortType portType ,Id * id1, Id * id2);
WeekdayList * WeekdaysListAddWeekdaySemanticAction(int weekday, WeekdayList * weekdaysList);
WeekdayList * WeekdaysListSemanticAction(int weekday);
Weekdays * WeekdaysSemanticAction(WeekdayList * weekdaysList);


/* Type convert functions */
Time * StringToTime(const char * time);
Date * StringToDate(const char * date);

#endif
