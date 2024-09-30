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
%token <token> STRINGS
%token <token> DATE
%token <token> HOUR    // -> 00, 01, 02, ...
%token <token> DEF_TYPE
%token <token> HOURS   // -> hours
%token <token> WEEKDAYS
%token <token> OPEN_CURLY_BRACE
%token <token> CLOSE_CURLY_BRACE
%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> EVENT
%token <token> DEF
%token <token> SEMICOLON // -> recomendación: Si es algo que siempre se debe agregar, conviene ponerlo en el no-terminal padre que las agrupa
%token <token> PATH
%token <token> GROUP
%token <token> USER
%token <token> ROLE
%token <token> ST_DATE
%token <token> END_DATE
%token <token> ST_TIME
%token <token> END_TIME
%token <token> TASK
%token <token> DESC
%token <token> USERS
%token <token> GENERATE
%token <token> FROM
%token <token> TYPE
%token <token> ALL
%token <token> IMPORT
%token <token> EXPORT
%token <token> DASH

%token <token> UNKNOWN



/** Non-terminals. */

/*

create_first ---> group

*/


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


program: group command generate										{ $$ = ProgramSemanticAction(currentCompilerState(),$1, $2, $3); }
	;

group: 																{ $$ = GroupSemanticAction(..., ...); }
	;

command: 															{ $$ = CommandSemanticAction( ... , ... ); }
	;
