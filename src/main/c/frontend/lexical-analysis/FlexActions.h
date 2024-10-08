#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

Token BracketLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token CurlyBracketLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token PunctuationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token WeekdayLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token DateLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token HourLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token DefTypeLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token CommandOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
Token ParametersLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token);
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif
