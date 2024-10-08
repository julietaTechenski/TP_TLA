#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS 

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}


Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}


Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

*/

Token BracketLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
    return token;
}

Token CurlyBracketLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
    return token;
}

Token PunctuationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = token;
    return token;
}

void BeginStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token EndStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
	return STRING;
}

void InsideStringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    size_t currentLength = strlen(lexicalAnalyzerContext->semanticValue->string);
    size_t newLength = currentLength + 2; 
    lexicalAnalyzerContext->semanticValue->string = realloc(lexicalAnalyzerContext->semanticValue->string, newLength);
    strncat(lexicalAnalyzerContext->semanticValue->string, yytext, 1);
}


Token WeekdayLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
    return WEEKDAY; 
}

Token DateLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
    return DATE; 
}

Token HourLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
    return HOUR; 
}

Token DefTypeLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
    return DEF_TYPE;
}


Token CommandOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->token = token;
    return token;
}

Token ParametersLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, Token token) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    lexicalAnalyzerContext->semanticValue->token = token;
    return token;
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}