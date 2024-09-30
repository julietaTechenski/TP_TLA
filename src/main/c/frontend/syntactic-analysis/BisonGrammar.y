%{

#include "BisonActions.h"

%}

// You touch this, and you die.
%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	Token token;

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
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
%token <token> STRING
%token <token> DATE
%token <token> HOUR    // -> 00, 01, 02, ...
%token <token> DEF_TYPE
%token <token> HOURS   // -> hours
%token <token> WEEKDAY
%token <token> OPEN_CURLY_BRACKET
%token <token> CLOSE_CURLY_BRACKET
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




/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV     // more precedence 

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

id: STRING
	;

initialize: group SEMICOLON user SEMICOLON								{ $$ = GroupSemanticAction(..., ...); }
	;

group: CREATE GROUP id													{ $$ = CommandSemanticAction( ... , ... ); }
	;

user: CREATE USER id ROLE id WEEKDAYS weekdays HOURS hour_range
	;

weekdays: OPEN_BRACKET weekday_list CLOSE_BRACKET
	;

weekday_list: WEEKDAY 
	| WEEKDAY COMMA weekday_list
	;	

hour_range: OPEN_BRACKET hour_list CLOSE_BRACKET
	;

hour_list: HOUR HYPHEN HOUR 
	| HOUR HYPHEN HOUR COMMA hour_list
	;

define: DEF id OPEN_CURLY_BRACE command_list CLOSE_CURLY_BRACKET
	;

command_list: command SEMICOLON 
	| command SEMICOLON command_list
	;

command: group 
	| user 
	| create_event 
	| create_task 
	| IMPORT ports 
	| EXPORT ports
	| define
	;

create_event: EVENT id user_group ST_DATE DATE END_DATE DATE
	;

create_task: TASK id user_group SINGLE_DATE DATE ST_TIME HOUR END_TIME HOUR DESCR STRING 
	;

user_group: USER id 
	| GROUP id	
	;

generate_list: generate SEMICOLON 
	| generate SEMICOLON generate_list
	;

generate: GENERATE id FROM id TYPE DEF_TYPE users ST_DATE DATE
	;

users: ALL 
	| OPEN_BRACKET users_list CLOSE_BRACKET
	;

users_list: id 
	| id COMMA users_list
	;

ports: id PATH STRING
	;
