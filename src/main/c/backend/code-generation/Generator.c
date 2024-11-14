#include "Generator.h"

 /** ------------------------- Module Internal State ------------------------- **/

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}


 /** ------------------------- Definition of private functions ------------------------- **/
static void _generateType(GenerateEntry * generateEntry);
static void _generateWeekly(GenerateEntry * generateEntry);
static void _generateMonthly(GenerateEntry * generateEntry);
static void _generateYearly(GenerateEntry * generateEntry);
static void _generateInfo(GenerateEntry * generateEntry);


 /** ------------------------- Implementation of private functions ------------------------- **/


void _generateType(GenerateEntry * generateEntry) {
	switch(generateEntry->generate->def_type) {
		case(WEEKLY):
			_generateWeekly(generateEntry);
			// CHANGE LOG FOR PROD
			logInformation(_logger, "Generating WEEKLY calendar...\n");
			_generateWeekly(generateEntry);
			break;
		case(MONTHLY):
			_generateMonthly(generateEntry);
			// CHANGE LOG FOR PROD
			logInformation(_logger, "Generating MONTHLY calendar...\n");
			_generateMonthly(generateEntry);
			break;
		case(YEARLY):
			_generateYearly(generateEntry);
			// CHANGE LOG FOR PROD
			logInformation(_logger, "Generating YEARLY calendar\n");
			_generateYearly(generateEntry);
			break;
		default:
			printf("Invalid option...\n");
            break;
	}
}

void _generateWeekly(GenerateEntry * generateEntry){
	_generateInfo(generateEntry);
	return;
}

void _generateMonthly(GenerateEntry * generateEntry){
	_generateInfo(generateEntry);
	return;
}

void _generateYearly(GenerateEntry * generateEntry){
	_generateInfo(generateEntry);
	return;
}

void _generateInfo(GenerateEntry * generateEntry){
	Generate * generate = generateEntry->generate;
	UserHashEntry * usersMap = generateEntry->usersMap;
	GroupHashEntry * groupsMap = generateEntry->groupsMap;

	logInformation(_logger, "Generate id %s", generate->id->id);
	logInformation(_logger ,"Generate start date %d - %d - %d", generate->start_date->day, generate->start_date->month, generate->start_date->year);
	logInformation(_logger, "Generate user name %s", generate->user_name != NULL ? generate->user_name->id : "NO CODE BLOCK");
	logInformation(_logger, "Generate the first of the list %s", generate->users->user_list->id->id);

}



 /** ------------------------- Implementation of public functions ------------------------- **/

void generate(CompilerState * compilerState) {
	// CHANGE LOG FOR PROD
	logInformation(_logger, "Generating final output...");

	GenerateEntryNode * current = getGenerateList();

	while(current != NULL) {
		_generateType(current->entry);
		current = current->next;
	}

	freeGenerateEntryNodeList();
	destroyUsersTableMap();
	destroyGroupsTableMap();

	// CHANGE LOG FOR PROD
	logInformation(_logger, "Generation is done.");
}