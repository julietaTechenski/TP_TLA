%{

#include "BisonActions.h"

%}

// You touch this, and you die.
%define api.value.union.name SemanticValue

%union {
	/** Terminals. */
	int integer;
	Token token;
	char * string;

	/** Non-terminals. */
	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
	Define * define;
	Id * id;
	CreateEvent * create_event;
	CreateTask * create_task;
	Ports * ports;
	Weekdays * weekdays;
	WeekdayList * weekday_list;
	HourRange * hour_range;
	HourRanges * hour_ranges;
	HourList * hour_list;
	Users * users;
	UsersList * users_list;
	Generate * generate;
	Command * command;
	Group * group;
	Initialize * initialize;
	User * user;
	UserGroup * user_group;
	CommandList * command_list;
	GenerateList * generate_list;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach. To use this mechanism, the AST must be translated into
 * another structure.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/



/** Terminals. */
/*%token <integer> INTEGER
%token <token> ADD
%token <token> CLOSE_PARENTHESIS
%token <token> DIV
%token <token> MUL
%token <token> OPEN_PARENTHESIS
%token <token> SUB

%token <token> UNKNOWN
 Non-terminals.
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program

*/


/** Terminals. */
%token <string> STRING
%token <string> DATE
%token <string> HOUR    // -> 00, 01, 02, ...
%token <integer> DEF_TYPE
%token <integer> WEEKDAY
%token <token> WEEKDAYS
%token <token> HOURS   // -> hours
%token <token> OPEN_CURLY_BRACE
%token <token> CLOSE_CURLY_BRACE
%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> COMMA
%token <token> EVENT
%token <token> DEF
%token <token> SEMICOLON // -> recomendación: Si es algo que siempre se debe agregar, conviene ponerlo en el no-terminal padre que las agrupa
%token <token> PATH
%token <token> GROUP
%token <token> USER
%token <token> ROLE
%token <token> ST_DATE
%token <token> END_DATE
%token <token> SINGLE_DATE
%token <token> ST_TIME
%token <token> END_TIME
%token <token> TASK
%token <token> DESCR
%token <token> USERS
%token <token> GENERATE
%token <token> CREATE
%token <token> FROM
%token <token> TYPE
%token <token> ALL
%token <token> IMPORT
%token <token> EXPORT
%token <token> HYPHEN
%token <token> UNKNOWN



/** Non-terminals. */

%type <define> define
%type <id> id
%type <create_event> create_event
%type <create_task> create_task
%type <ports> ports
%type <weekdays> weekdays
%type <weekday_list> weekday_list
%type <hour_range> hour_range
%type <hour_ranges> hour_ranges
%type <hour_list> hour_list
%type <users> users
%type <users_list> users_list
%type <generate> generate
%type <command> command
%type <group> group
%type <program> program
%type <initialize> initialize
%type <user> user
%type <user_group> user_group
%type <command_list> command_list
%type <generate_list> generate_list




/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html

 %left ADD SUB
 %left MUL DIV     // more precedence 

 */


%%

// IMPORTANT: To use λ in the following grammar, use the %empty symbol.
/*
program: expression													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor														{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

%%*/


program: initialize command_list generate_list							{ $$ = ProgramSemanticAction(currentCompilerState(),$1, $2, $3); }
	;

id: STRING																{ $$ = IdSemanticAction($1); }
	;

initialize: group SEMICOLON user SEMICOLON								{ $$ = InitializeSemanticAction($1, $2); }
	;

group: CREATE GROUP id													{ $$ = GroupSemanticAction($1); }
	;

user: CREATE USER id ROLE id WEEKDAYS weekdays HOURS hour_list			{ $$ = UserSemanticAction($1, $2, $3, $4); }   // ***  esto esta raro WEEKDAY  y WEEKDAY tienen dos significados
	;

weekdays: OPEN_BRACKET weekday_list CLOSE_BRACKET						{ $$ = WeekdaysSemanticAction($1); }		//
	;

weekday_list: WEEKDAY													{ $$ = WeekdayListSemanticAction(WEEKDAY); }		// ***
	| WEEKDAY COMMA weekday_list										{ $$ = WeekdayListSemanticAction(WEEKDAY, $1); }		//
	;	


hour_list: OPEN_BRACKET hour_ranges CLOSE_BRACKET						{ $$ = HourListSemanticAction($1); }
	;


hour_ranges: hour_range													{ $$ = HourRangesSemanticAction($1); }
	| hour_range COMMA hour_ranges										{ $$ = HourRangesSemanticAction($1, $2); }
	;


hour_range: HOUR HYPHEN HOUR											{ $$ = HourRangeSemanticAction($1, $3); }   //
	;


define: DEF id OPEN_CURLY_BRACE command_list CLOSE_CURLY_BRACE			{ $$ = DefineSemanticAction($1, $2); }
	;

command_list: command SEMICOLON 										{ $$ = CommandListSemanticAction($1); }
	| command SEMICOLON command_list									{ $$ = CommandListSemanticAction($1, $2); }
	;

command: group															{ $$ = CommandSemanticAction($1); }															
	| user 																{ $$ = CommandSemanticAction($1); }
	| create_event 														{ $$ = CommandSemanticAction($1); }
	| create_task														{ $$ = CommandSemanticAction($1); }		
	| IMPORT ports 														{ $$ = CommandSemanticAction($1, IMPORT); }
	| EXPORT ports														{ $$ = CommandSemanticAction($1, EXPORT); }
	| define															{ $$ = CommandSemanticAction($1); }
	;

create_event: EVENT id user_group ST_DATE DATE END_DATE DATE	 		{ $$ = CreateEventSemanticAction($1, $2, DATE, DATE); }	     //
	;

create_task: TASK id user_group SINGLE_DATE DATE ST_TIME HOUR END_TIME HOUR DESCR STRING	{ $$ = CreateTaskSemanticAction($1, $2, $3, $4, $5/*, $6*/); }  // description
	;

user_group: USER id														{ $$ = UserGroupSemanticAction($1); }
	| GROUP id															{ $$ = UserGroupSemanticAction($1); }
	;

generate_list: generate SEMICOLON 						 		 		{ $$ = GenerateListSemanticAction($1); }
	| generate SEMICOLON generate_list									{ $$ = GenerateListSemanticAction($1, $2); }
	;

generate: GENERATE id FROM id TYPE DEF_TYPE USERS users ST_DATE DATE	{ $$ = GenerateSemanticAction($1, $2, DEF_TYPE, $3, DATE); }
	;

users: ALL																{ $$ = UsersSemanticAction(); }			//
	| OPEN_BRACKET users_list CLOSE_BRACKET								{ $$ = UsersSemanticAction($1); }
	;

users_list: id 															{ $$ = UsersListSemanticAction($1); }
	| id COMMA users_list												{ $$ = UsersListSemanticAction($1, $2); }
	;

ports: id PATH id														{ $$ = PortsSemanticAction($1, $3); }
	;
