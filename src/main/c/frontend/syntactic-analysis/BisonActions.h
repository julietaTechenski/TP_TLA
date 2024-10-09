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
UsersList * UsersListAddUserSemanticAction(User * user, UsersList * usersList);
Users * UsersListToUsersSemanticAction(UsersList * usersList);
Users * UsersSemanticAction();      //
Generate * GenerateSemanticAction(Id * generateId, Id * id, int defType, Users * users, char * date);
GenerateList * GenerateListAddGenerateSemanticAction(Generate * generate, GenerateList * generateList);
GenerateList * GenerateListSemanticAction(Generate * generate);
UserGroup * UserGroupSemanticAction(Id * id);
UserGroup * UserGroupFromGroupSemanticAction(Group * group);
CreateTask * CreateTaskSemanticAction(Id * id, UserGroup * userGroup, char * date, char * stTime, char * endTime, char * description);  /* Description * description*/
CreateEvent * CreateEventSemanticAction(Id * id, UserGroup * userGroup, char * stDate, char * endDate);   // por ahi podemos hacer que el tipo sea Event directamente -> lo miso con los otros create consultar
Command * CommandGroupSemanticAction(Group * group);
Command * CommandUserSemanticAction(User * user);
Command * CommandCreateEventSemanticAction(CreateEvent * createEvent);
Command * CommandCreateTaskSemanticAction(CreateTask * createTask);
Command * CommandPortsSemanticAction(Ports * ports, PortType portType);
Command * CommandDefineSemanticAction(Define * define);
CommandList * CommandListAddCommandSemanticAction(Command * command, CommandList * commandList);
CommandList * CommandListSemanticAction(Command * command);
Define * DefineSemanticAction(Id * id, CommandList * commandList);


// faltan de aca para abajo mirar que esten bien 

HourRange * HourRangeSemanticAction(char * hour1, char * hour2);
HourRange * HourRangesAddHourRangeSemanticAction(HourRange * hourRange, HourRanges * hourRanges);   // TODO: Crear tipo HourRanges y checkear el tipo HOurList
//HourRange * HourRangesSemanticAction(HourRange * hourRange);   // TODO: Crear tipo HourRanges y checkear el tipo HOurList
HourList * HourListSemanticAction(HourRange * hourRange);
WeekdayList * WeekdaysListSemanticAction(int Weekday, WeekdayList * weekdaysList);
//WeekdaysList * WeekdaysListSemanticAction(int Weekday);
//WeekdaysList * WeekdaysSemanticAction(WeekdaysList * weekdaysList);
User * UserSemanticAction(Id * userId, Id * roleId, Weekdays * weekdays, HourList * HourList);    // Weekdays + modifique el range a list 
Group * GroupSemanticAction(Id * id);
Initialize * InitializeSemanticAction(Group * group, Users * users);
Id * IdSemanticAction(const char * value);
Program * ProgramSemanticAction(CompilerState * compilerState, Initialize * initialize, CommandList * commandList, GenerateList * generateList);
Ports * PortsSemanticAction(Id * id1, Id * id2);


#endif
