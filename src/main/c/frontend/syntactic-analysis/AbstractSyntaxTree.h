#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

struct Constant {
	int value;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
	};
	ExpressionType type;
};





//---------------------------------------------------
/*
%type <define> define
%type <id> id
%type <create> create
%type <create_event> create_event
%type <create_task> create_task
%type <ports> ports
%type <weekdays> weekdays
%type <weekday_list> weekday_list
%type <hour_range> hour_range
%type <hour_list> hour_list
%type <users> users
%type <users_list> users_list
%type <generate> generate
%type <command> command
%type <group> group
%type <program> program
%type <initialize> initialize
%type <user> user
%type <group> group
*/

typedef enum Weekday Weekday;
typedef enum DefType DefType;
typedef enum PortType PortType;
typedef enum CommandType CommandType;
typedef enum UsersType UsersType;
typedef enum UserGroupType UserGroupType;
typedef enum GroupsType GroupsType;
typedef struct Hour Hour;
typedef struct Date Date;
typedef struct Minute Minute;
typedef struct Time Time;

enum Weekday {
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
};

enum DefType {
	// Es provisorio, hay que agregar todos
	MONTHLY,
	WEEKLY,	
	YEARLY
};


enum CommandType {
	C_GROUP,
	C_USER,
	C_EVENT,
	C_TASK,
	C_IMPORT,
	C_DEFINE,
	C_GENERATE,
	C_ADD
};

enum UsersType {
	USERS_ALL,
	USERS_LIST
};

enum UserGroupType {
	GROUP_USER,
	GROUP_GROUP
};

enum GroupsType {
	GROUPS_ALL,
	GROUPS_LIST
};

struct Date{
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

struct Time {
	unsigned int hour;
	unsigned int minute;
};



//---------------------------------------------------
typedef struct Program Program;
typedef struct Initialize Initialize;
typedef struct Id Id;
typedef struct Group Group;
typedef struct User User;
typedef struct Weekdays Weekdays;
typedef struct WeekdayList WeekdayList;
typedef struct HourList HourList;
typedef struct HourRange HourRange;
typedef struct HourRanges HourRanges;
typedef struct CommandList CommandList;
typedef struct Define Define;
typedef struct Command Command;
typedef struct UserGroup UserGroup;
typedef struct CreateEvent CreateEvent;
typedef struct CreateTask CreateTask;
typedef struct Generate Generate;
typedef struct Users Users;
typedef struct UsersList UsersList;
typedef struct Import Import;
typedef struct Add Add;
typedef struct Groups Groups;
typedef struct GroupsList GroupsList;

struct Program {
	CommandList * command_list;
};

struct Id{
	char * id;
};


struct Group{
	Id * name;
};

struct User{
	Id * name;
	Id * role;
	Weekdays * weekdays; 
	HourList * hour_list;
};

struct Weekdays {
	WeekdayList * weekdays_list;
};

struct WeekdayList{
	Weekday weekday;
	WeekdayList * weekday_list;	//Finish if NULL
};

struct HourRange {
	Time * start;
	Time * finish;
};

struct HourList{
	HourRanges * hour_ranges;
};

struct HourRanges {
	HourRange * hour_range;
	HourRanges * hour_ranges;	//Finish if NULL
};

struct Define{
	Id * id;
	CommandList * command_list;
};

struct CommandList {
	Command * command;
	CommandList * command_list;	//Finish if NULL
};

struct Command {
	union 
	{
		Group * group;
		User * user;
		CreateEvent * create_event;
		CreateTask * create_task;
		Import * import;
		Define * define;
		Generate * generate;
		Add * add;
	};
	CommandType type;
};

struct UserGroup {
	union 
	{
		Id * user;
		Id * group;
	};
	UserGroupType type;
};

struct CreateEvent {
	Id * id;
	UserGroup * user_group;
	Date * start_date;
	Date * end_date;
};

struct CreateTask {
	Id * id;
	UserGroup * user_group;
	Date * date;
	Time * start_time;
	Time * end_time;	
	char * description;	
};			



struct Generate {
	Id * id;
	Id * user_name;
	DefType def_type;
	Users * users;
	Date * start_date;
};


struct Users {
	UsersList * user_list;
	UsersType type;
};

struct UsersList {
	Id * id;
	UsersList * user_list; //Finish if NULL
};

struct Add {
	Id * user;
	Groups * groups;
};

struct Groups {
	GroupsList * group_list;
	GroupsType type;
};


struct GroupsList {
	Id * id;
	GroupsList * group_list; //Finish if NULL
};

struct Import {
	CommandList * command_list;
};

/**
 * Node recursive destructors.
 */
/*
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
*/
void releaseProgram(Program * program);
void releaseCommandList(CommandList * commandList);
void releaseCommand(Command * command);
void releaseGroup(Group * group);
void releaseUser(User * user);
void releaseCreateEvent(CreateEvent * createEvent);
void releaseCreateTask(CreateTask * createTask);
void releaseImport(Import * import);
void releaseDefine(Define * define);
void releaseGenerate(Generate * generate);
void releaseAdd(Add * add);
void releaseWeekdays(Weekdays * weekdays);
void releaseWeekdayList(WeekdayList * weekdayList);
void releaseHourList(HourList * hourList);
void releaseUsers(Users * users);
void releaseUserGroup(UserGroup * userGroup);
void releaseDate(Date * date);
void releaseTime(Time * time);
void releaseGroups(Groups * groups);
void releaseUsersList(UsersList * usersList);
void releaseGroupsList(GroupsList * groupsList);
void releaseHourRanges(HourRanges * hourRanges);
void releaseHourRange(HourRange * hourRange);
void releaseId(Id * id);
#endif
