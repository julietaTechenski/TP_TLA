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
Users * UsersSemanticAction();      //
Generate * GenerateSemanticAction(Id * generateId, Id * id, int defType, Users * users, Date * date);
GenerateList * GenerateListAddGenerateSemanticAction(Generate * generate, GenerateList * generateList);
GenerateList * GenerateListSemanticAction(Generate * generate);
UserGroup * UserGroupFromUserSemanticAction(Id * user);
UserGroup * UserGroupFromGroupSemanticAction(Id * group);
CreateTask * CreateTaskSemanticAction(Id * id, UserGroup * userGroup, Date * date, Time * stTime, Time * endTime, char * description); 
CreateEvent * CreateEventSemanticAction(Id * id, UserGroup * userGroup, Date * stDate, Date * endDate);  
Command * CommandGroupSemanticAction(Group * group);
Command * CommandUserSemanticAction(User * user);
Command * CommandCreateEventSemanticAction(CreateEvent * createEvent);
Command * CommandCreateTaskSemanticAction(CreateTask * createTask);
Command * CommandPortsSemanticAction(Ports * ports, PortType portType);
Command * CommandDefineSemanticAction(Define * define);
CommandList * CommandListAddCommandSemanticAction(Command * command, CommandList * commandList);
CommandList * CommandListSemanticAction(Command * command);
Define * DefineSemanticAction(Id * id, CommandList * commandList);
HourRange * HourRangeSemanticAction(Time * hour1, Time * hour2);
HourRanges * HourRangesAddHourRangeSemanticAction(HourRange * hourRange, HourRanges * hourRanges);
HourRanges * HourRangesSemanticAction(HourRange * hourRange);
HourList * HourListSemanticAction(HourRanges * hourRanges);
User * UserSemanticAction(Id * userId, Id * roleId, Weekdays * weekdays, HourList * HourList);
Group * GroupSemanticAction(Id * id);
Initialize * InitializeSemanticAction(Group * group, User * user);
Id * IdSemanticAction(const char * value);
Program * ProgramSemanticAction(CompilerState * compilerState, Initialize * initialize, CommandList * commandList, GenerateList * generateList);
Ports * PortsSemanticAction(Id * id1, Id * id2);
WeekdayList * WeekdaysListAddWeekdaySemanticAction(Weekday weekday, WeekdayList * weekdaysList);
WeekdayList * WeekdaysListSemanticAction(Weekday Weekday);
Weekdays * WeekdaysSemanticAction(WeekdayList * weekdaysList);


#endif
