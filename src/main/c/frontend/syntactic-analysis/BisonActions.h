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





Ports * PortsSemanticAction(Id * id1, Id * id2);

UsersList * UsersListSemanticAction(User * user, UsersList * usersList);
UsersList * UsersListSemanticAction(Id * id);
Users * UsersSemanticAction(UsersList * UsersList);
Users * UsersSemanticAction();      //
Generate * GenerateSemanticAction(Id * generateId, Id * id, DefType * defType, Users * users, Date * date);
GenerateList * GenerateListSemanticAction(Generate * generate, GenerateList * generateList);
GenerateList * GenerateListSemanticAction(Generate * generate);
UserGroup * UserGroupSemanticAction(Id * id);
UserGroup * UserGroupSemanticAction(Group * group);
CreateTask * CreateTaskSemanticAction(Id * id, UserGroup * userGroup, Date * date, Hour * stTime, Hour * endTime/* Description * description*/);  
CreateEvent * CreateEventSemanticAction(Id * id, UserGroup * userGroup, Date * stDate, Date * endDate);   // por ahi podemos hacer que el tipo sea Event directamente -> lo miso con los otros create consultar
Command * CommandSemanticAction(Group * group);
Command * CommandSemanticAction(User * user);
Command * CommandSemanticAction(CreateEvent * createEvent);
Command * CommandSemanticAction(CreateTask * createTask);
Command * CommandSemanticAction(Ports * ports, PortType portType);
Command * CommandSemanticAction(Define * define);
CommandList * CommandListSemanticAction(Command * command, CommandList * commandList);
CommandList * CommandListSemanticAction(Command * command);
Define * DefineSemanticAction(Id * id, CommandList * commandList);
HourRange * HourRangeSemanticAction(Hour * hour1, Hour * hour2);
HourRanges * HourRangesSemanticAction(HourRange * hourRange, HourRanges * hourRanges);   // TODO: Crear tipo HourRanges y checkear el tipo HOurList
HourRanges * HourRangesSemanticAction(HourRange * hourRange);   // TODO: Crear tipo HourRanges y checkear el tipo HOurList
HourList * HourListSemanticAction(HourRange * hourRange);
WeekdaysList * WeekdaysListSemanticAction(Weekday * Weekday, WeekdaysList * weekdaysList);
Weekdays * WeekdaysSemanticAction(WeekdaysList * weekdaysList);
User * UserSemanticAction(Id * userId, Id * roleId, Weekdays * weekdays, HourList * HourList);    // Weekdays + modifique el range a list 
Group * GroupSemanticAction(Id * id);
Initialize * InitializeSemanticAction(Group * group, Users * users);
Id * IdSemanticAction(const char * value);
Program * ProgramSemanticAction(CompilerState * compilerState, Initialize * initialize, CommandList * commandList, GenerateList * generateList);


#endif
