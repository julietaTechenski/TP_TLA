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
Generate * GenerateSemanticAction(Id *generateId, Id *id, DefType defType, Users *users, Date *date);
UserGroup * UserGroupFromUserSemanticAction(Id * user);
UserGroup * UserGroupFromGroupSemanticAction(Id * group);
CreateTask * CreateTaskSemanticAction(Id * id, UserGroup * userGroup, Date * date, Time * stTime, Time * endTime, char * description); 
CreateEvent * CreateEventSemanticAction(Id * id, UserGroup * userGroup, Date * stDate, Date * endDate);  
Command * CommandGroupSemanticAction(Group * group);
Command * CommandUserSemanticAction(User * user);
Command * CommandCreateEventSemanticAction(CreateEvent * createEvent);
Command * CommandCreateTaskSemanticAction(CreateTask * createTask);
Command * CommandPortsSemanticAction(Ports * ports);
Command * CommandDefineSemanticAction(Define * define);
Command * CommandGenerateSemanticAction(Generate * generateList);
Command * CommandAddSemanticAction(Add * add);
CommandList * CommandListAddCommandSemanticAction(Command * command, CommandList * commandList);
CommandList * CommandListSemanticAction(Command * command);
Define * DefineSemanticAction(Id * id, CommandList * commandList);
HourRange * HourRangeSemanticAction(Time * hour1, Time * hour2);
HourRanges * HourRangesAddHourRangeSemanticAction(HourRange * hourRange, HourRanges * hourRanges);
HourRanges * HourRangesSemanticAction(HourRange * hourRange);
HourList * HourListSemanticAction(HourRanges * hourRanges);
User * UserSemanticAction(Id * userId, Id * roleId, Weekdays * weekdays, HourList * HourList);
Group * GroupSemanticAction(Id * id);
Id * IdSemanticAction(const char * value);
Program * ProgramSemanticAction(CompilerState * compilerState, CommandList * commandList);
Ports * PortsSemanticAction(PortType portType ,Id * id1, Id * id2);
WeekdayList * WeekdaysListAddWeekdaySemanticAction(Weekday weekday, WeekdayList * weekdaysList);
WeekdayList * WeekdaysListSemanticAction(Weekday weekday);
Weekdays * WeekdaysSemanticAction(WeekdayList * weekdaysList);
Add * AddSemanticAction(Id * user, Groups * groups);
GroupsList * GroupsListSemanticAction(Id * id);
GroupsList * GroupsListAddGroupSemanticAction(Id * group, GroupsList * groupsList);   
Groups * GroupsListToGroupsSemanticAction(GroupsList * groupsList);
Groups * GroupsSemanticAction();     

#endif
