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
static void _generateType(GenerateEntry * generateEntry, FILE *file);
static void _generateWeekly(GenerateEntry * generateEntry, FILE *file);
static void _generateMonthly(GenerateEntry * generateEntry, FILE *file);
static void _generateYearly(GenerateEntry * generateEntry, FILE *file);
static void _generateInfo(GenerateEntry * generateEntry, FILE *file);
static void _generatePrologue(FILE *file);
void _generateEpilogue(FILE *file);


 /** ------------------------- Implementation of private functions ------------------------- **/


static void _generateType(GenerateEntry * generateEntry, FILE *file) {
	switch(generateEntry->generate->def_type) {
		case(WEEKLY):
			// CHANGE LOG FOR PROD
			logInformation(_logger, "Generating WEEKLY calendar...");
			_generateWeekly(generateEntry, file);
			break;
		case(MONTHLY):
			// CHANGE LOG FOR PROD
			logInformation(_logger, "Generating MONTHLY calendar...");
			_generateMonthly(generateEntry, file);
			break;
		case(YEARLY):
			// CHANGE LOG FOR PROD
			logInformation(_logger, "Generating YEARLY calendar\n");
			_generateYearly(generateEntry, file);
			break;
		default:
			printf("Invalid option...\n");
            break;
	}
}

static void _generateWeekly(GenerateEntry * generateEntry, FILE *file){
	fprintf(file,
	"<script>\n"
    "    document.addEventListener('DOMContentLoaded', function() {\n"
    "        var calendarEl = document.getElementById('calendar');\n\n"
    "        var calendar = new FullCalendar.Calendar(calendarEl, {\n"
    "            timeZone: 'UTC',\n"
    "            initialView: 'timeGridWeek',\n"
    "            locale: 'es',\n"
    "            headerToolbar: {\n"
    "                left: '',\n"
    "                center: 'title',\n"
    "                right: ''\n"
    "            },\n"
    "            views: {\n"
    "                timeGridWeek: {\n"
    "                    dayHeaderFormat: { weekday: 'long' },\n"
    "                    titleFormat: { year: 'numeric', month: 'long' }\n"
    "                }\n"
    "            },\n"
    "            events: [\n");

	// iteracion en la lista de eventos del generate
	
	int first = 1;
	while(/*events*/0){
		if(!first){
			fprintf(file,",\n");
		} else {
			first = 0;
		}
		fprintf(file,"                { title: 'Tarea 1', daysOfWeek: [1], startTime: '10:00', endTime: '12:00' }");
	}

	fprintf(file,
    "            ]\n"
    "        });\n\n"
    "        calendar.render();\n"
    "    });\n\n"
	"</script>\n"
    "<style>\n"
    "    .fc-col-header-cell-cushion {\n"
    "        display: none;\n"
    "    }\n\n"
    "    .fc-day-number {\n"
    "        display: none;\n"
    "    }\n"
	"</style>\n"
	);

	_generateInfo(generateEntry, file);
	return;
}

static void _generateMonthly(GenerateEntry * generateEntry, FILE *file){
	printf(
	"<script>\n"
    "	document.addEventListener('DOMContentLoaded', function() {\n"
    "   	var calendarEl = document.getElementById('calendar');\n"
    "   	var calendar = new FullCalendar.Calendar(calendarEl, {\n"
    "       	initialView: 'dayGridMonth',\n"
    "        	headerToolbar: {\n"
    "           	left: '',\n"
    "            	center: 'title',\n"
    "           	right: ''\n"
    "        	},\n"
    "        	locale: 'es',\n"
    "        	events: [\n");

	int first = 1;
	while(/*iterar events*/0){
		if(!first){
			fprintf(file,",\n");
		} else {
			first = 0;
		}


		fprintf(file,"	            { title: 'Evento 3', start: '2024-11-12T10:30:00', end: '2024-11-14T12:30:00' }\n");
		//fprintf(file,"	            { title: 'Evento 1', start: '2024-11-04' }\n");
		//fprintf(file,"	            { title: 'Evento 2', start: '2024-11-10', allDay: true }\n");
	}


	fprintf(file,
    "	        ]\n"
    "	    });\n"
    "	    calendar.render();\n"
    "	});\n"
	"</script>\n");

	_generateInfo(generateEntry, file);
	return;
}

void _generateYearly(GenerateEntry * generateEntry, FILE *file){
	fprintf(file,
		"<script>\n"
		"document.addEventListener('DOMContentLoaded', function() {\n"
		"    var calendarEl = document.getElementById('calendar');\n\n"
		"    var calendar = new FullCalendar.Calendar(calendarEl, {\n"
		"        timeZone: 'UTC',\n"
		"        initialView: 'multiMonthYear',\n"
		"        headerToolbar: {\n"
		"            left: '',\n"
		"            center: 'title',\n"
		"            right: ''\n"
		"        },\n"
		"        locale: 'es',\n"
		"        editable: true,\n"
		"        events: [\n");

		int first = 1;
		while(/*iterar events*/0){
			if(!first){
				fprintf(file,",\n");
			} else {
				first = 0;
			}

			

			fprintf(file,"            { title: 'Reunión con equipo de diseño', start: '2024-11-15T09:00:00', end: '2024-11-15T11:00:00' }\n");
			//fprintf(file,"            { title: 'Presentación del proyecto X', start: '2024-11-16T14:00:00', end: '2024-11-16T15:30:00' },\n");
			//fprintf(file,"            { title: 'Clase de Yoga', daysOfWeek: [2, 4], startTime: '18:00:00', endTime: '19:00:00' },\n");
			//fprintf(file,"            { title: 'Taller de Fotografía', start: '2024-11-18', end: '2024-11-19', allDay: true },\n");
			//fprintf(file,"            { title: 'Cumpleaños de Andrea', start: '2024-11-21', allDay: true },\n");
			//fprintf(file,"            { title: 'Revisión de presupuesto', start: '2024-11-22T10:00:00', end: '2024-11-22T12:00:00' },\n");
			//fprintf(file,"            { title: 'Cena de fin de año', start: '2024-11-30T20:00:00', end: '2024-11-30T23:30:00' }\n");
		}

		fprintf(file,
		""
		"    });\n\n"
		"    calendar.render();\n"
		"});\n"
		"</script>\n\n"
		"<style>\n"
		"html, body {\n"
		"    margin: 0;\n"
		"    padding: 0;\n"
		"    font-family: Arial, Helvetica Neue, Helvetica, sans-serif;\n"
		"    font-size: 14px;\n"
		"}\n\n"
		"#calendar {\n"
		"    max-width: 1200px;\n"
		"    margin: 40px auto;\n"
		"}\n"
		"</style>\n"
	);


	_generateInfo(generateEntry, file);
	return;
}

void _generateInfo(GenerateEntry * generateEntry, FILE *file){
	Generate * generate = generateEntry->generate;
	UserHashEntry * usersMap = generateEntry->usersMap;
	GroupHashEntry * groupsMap = generateEntry->groupsMap;

	logInformation(_logger, "Generate id %s", generate->id->id);
	logInformation(_logger ,"Generate start date %d - %d - %d", generate->start_date->day, generate->start_date->month, generate->start_date->year);
	logInformation(_logger, "Generate user name %s", generate->user_name != NULL ? generate->user_name->id : "NO CODE BLOCK");
	logInformation(_logger, "Generate the first of the list %s", generate->users->user_list->id->id);

}

void _generatePrologue(FILE *file){
	fprintf(file,
            "<!DOCTYPE html>\n"
            "<html lang='es'>\n"
            "<head>\n"
            "    <meta charset='utf-8'>\n"
            "    <link href='https://cdn.jsdelivr.net/npm/fullcalendar@5.11.0/main.min.css' rel='stylesheet'>\n"
            "    <script src='https://cdn.jsdelivr.net/npm/fullcalendar@5.11.0/main.min.js'></script>\n"
            "    <title>Calendario</title>\n"
            "</head>\n"
            "<body>\n"
            "    <div id='calendar'></div>\n"
            "</body>\n");
	logDebugging(_logger, "Prologue generated.");
}


void _generateEpilogue(FILE *file) {
    fprintf(file,"</html>\n");

	fclose(file);
	logDebugging(_logger, "Epilogue generated.");
}

 /** ------------------------- Implementation of public functions ------------------------- **/

void generate(CompilerState * compilerState) {
	// CHANGE LOG FOR PROD
	logInformation(_logger, "Generating final output...");

	GenerateEntryNode * current = getGenerateList();
    
	int i = 1;

	while(current != NULL) {
		char filename[50];
        snprintf(filename, sizeof(filename), "calendar_%d.html", i);

		FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file %s\n", filename);
            exit(1);
        }

        _generatePrologue(file);
		_generateType(current->entry, file);
		_generateEpilogue(file);

		current = current->next;
		logInformation(_logger, "Calendar %d generated.", i++);
	}

	destroyGenerateList();
	destroyUsersTableMap();
	destroyGroupsTableMap();
	destroyCodeBlock();

	// CHANGE LOG FOR PROD
	logInformation(_logger, "Generation is done.");
}