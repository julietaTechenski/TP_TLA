%{

#include "FlexActions.h"

static YY_BUFFER_STATE importedExpressionBufferState = NULL;

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x STRING
%x IMPORT_EXPRESSION


/**
 * Reusable patterns.
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%



"["									{ return BracketLexemeAction(createLexicalAnalyzerContext(), OPEN_BRACKET); }
"]"									{ return BracketLexemeAction(createLexicalAnalyzerContext(), CLOSE_BRACKET); }

"{"									{ return CurlyBracketLexemeAction(createLexicalAnalyzerContext(), OPEN_CURLY_BRACE); }
"}"									{ return CurlyBracketLexemeAction(createLexicalAnalyzerContext(), CLOSE_CURLY_BRACE); }

";"                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext(), SEMICOLON); }

","                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext(), COMMA); }

"-"                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext(), HYPHEN); }

\"                                  { BEGIN(STRING); BeginStringLexemeAction(createLexicalAnalyzerContext()); }
<STRING>([^\"]*)                    { return StringLexemeAction(createLexicalAnalyzerContext()); }
<STRING>\"                          { EndStringLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }

"monday"                            { return WeekdayLexemeAction(createLexicalAnalyzerContext(), MONDAY);     }
"tuesday"                           { return WeekdayLexemeAction(createLexicalAnalyzerContext(), TUESDAY);     }
"wednesday"                         { return WeekdayLexemeAction(createLexicalAnalyzerContext(), WEDNESDAY);     }
"thursday"                          { return WeekdayLexemeAction(createLexicalAnalyzerContext(), THURSDAY);     }
"friday"                            { return WeekdayLexemeAction(createLexicalAnalyzerContext(), FRIDAY);     }
"saturday"                          { return WeekdayLexemeAction(createLexicalAnalyzerContext(), SATURDAY);     }
"sunday"                            { return WeekdayLexemeAction(createLexicalAnalyzerContext(), SUNDAY);     }


[[:digit:]]{4}"-"[[:digit:]]{2}"-"[[:digit:]]{2}                                    { return DateLexemeAction(createLexicalAnalyzerContext());      }


[[:digit:]]{2}":"[[:digit:]]{2}                                                     { return HourLexemeAction(createLexicalAnalyzerContext());      }

"weekly"                            { return DefTypeLexemeAction(createLexicalAnalyzerContext(), WEEKLY);    } 
"monthly"                           { return DefTypeLexemeAction(createLexicalAnalyzerContext(), MONTHLY);   } 
"yearly"                            { return DefTypeLexemeAction(createLexicalAnalyzerContext(), YEARLY);    }                         


"import"                            { return PortLexemeAction(createLexicalAnalyzerContext(), IMPORT_ENUM); }
"export"                            { return PortLexemeAction(createLexicalAnalyzerContext(), EXPORT_ENUM); }


"event"                             { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), EVENT); }

"define"                            { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), DEF); }

"create"                            { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), CREATE); }

"task"                              { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), TASK); }

"generate"                          { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), GENERATE); }

"add"                               { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), ADD); }



"hours"                             { return ParametersLexemeAction(createLexicalAnalyzerContext(), HOURS); }

"group"                             { return ParametersLexemeAction(createLexicalAnalyzerContext(), GROUP); }

"user"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), USER); }

"weekdays"                          { return ParametersLexemeAction(createLexicalAnalyzerContext(), WEEKDAYS); }

"path"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), PATH); }

"role"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), ROLE); }

"start_date"                        { return ParametersLexemeAction(createLexicalAnalyzerContext(), ST_DATE); }

"end_date"                          { return ParametersLexemeAction(createLexicalAnalyzerContext(), END_DATE); }

"date"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), SINGLE_DATE); }

"start_time"                        { return ParametersLexemeAction(createLexicalAnalyzerContext(), ST_TIME); }

"end_time"                          { return ParametersLexemeAction(createLexicalAnalyzerContext(), END_TIME); }

"from"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), FROM); }

"type"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), TYPE); }

"all"                               { return ParametersLexemeAction(createLexicalAnalyzerContext(), EVERY); }

"users"                             { return ParametersLexemeAction(createLexicalAnalyzerContext(), USERS); }

"groups"                             { return ParametersLexemeAction(createLexicalAnalyzerContext(), GROUPS); }

"description"                        { return ParametersLexemeAction(createLexicalAnalyzerContext(), DESCR); }

"to"                                { return ParametersLexemeAction(createLexicalAnalyzerContext(), TO); }

"<"									{
										printf("%s", "Context-switch to IMPORT_EXPRESSION.\n");
										BEGIN(IMPORT_EXPRESSION);
									}

<IMPORT_EXPRESSION>[^<>]+			{
										LexicalAnalyzerContext * lexicalAnalyzerContext = createLexicalAnalyzerContext();
										printf("Creating next buffer to consume from file '%s'.\n", lexicalAnalyzerContext->lexeme);
										yyin = fopen(lexicalAnalyzerContext->lexeme, "r");
										importedExpressionBufferState = yy_create_buffer(yyin, YY_BUF_SIZE);
									}

<IMPORT_EXPRESSION>">"				{
										printf("%s", "Loading next buffer from imported expression.\n");
										yypush_buffer_state(importedExpressionBufferState);
										BEGIN(INITIAL);
									}

<IMPORT_EXPRESSION>.				{
										printf("%s", "Syntax error inside import expression.\n");
										return UnknownLexemeAction(createLexicalAnalyzerContext());
									}

<<EOF>>								{
										printf("%s", "EOF, poping buffer.\n");
										yypop_buffer_state();
										if (!YY_CURRENT_BUFFER) {
											yyterminate();
										}
									}

%%

/*

 %x MULTILINE_COMMENT

EXAMPLE

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"/*""			{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), SUB); }
"*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), MUL); }
"/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), DIV); }
"+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext(), ADD); }

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), OPEN_PARENTHESIS); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext(), CLOSE_PARENTHESIS); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }


"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"/*"			    { EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }


*/

#include "FlexExport.h"


