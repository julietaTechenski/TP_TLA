%{

#include "FlexActions.h"

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
%x MULTILINE_COMMENT


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

\"                                  { BEGIN(STRING); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<STRING>([^\"]*)                    { return StringLexemeAction(createLexicalAnalyzerContext()); }
<STRING>\"                          { EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }

"monday"|"tuesday"|"wednesday"|"thursday"|"friday"|"saturday"|"sunday"              { return WeekdayLexemeAction(createLexicalAnalyzerContext());     }


[[:digit:]]{4}"-"[[:digit:]]{2}"-"[[:digit:]]{2}                                    { return DateLexemeAction(createLexicalAnalyzerContext());      }


[[:digit:]]{2}":"[[:digit:]]{2}                                                     { return HourLexemeAction(createLexicalAnalyzerContext());      }

"weekly"|"monthly"|"yearly"                                                         { return DefTypeLexemeAction(createLexicalAnalyzerContext());    } 


"import"                            { return PortLexemeAction(createLexicalAnalyzerContext()); }

"export"                            { return PortLexemeAction(createLexicalAnalyzerContext()); }


"event"                             { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), EVENT); }

"define"                            { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), DEF); }


"create"                            { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), CREATE); }

"task"                              { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), TASK); }

"generate"                          { return CommandOperatorLexemeAction(createLexicalAnalyzerContext(), GENERATE); }




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

"users"                              { return ParametersLexemeAction(createLexicalAnalyzerContext(), USERS); }

"decription"                        { return ParametersLexemeAction(createLexicalAnalyzerContext(), DESCR); }


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


