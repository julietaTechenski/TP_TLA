#include "Generator.h"

 /** ------------------------- Global Variables  ------------------------- **/

int backgroundColorsIndex = 0;
static const char * backgroundColors[100] = {
    "#FF5733", "#33FF57", "#5733FF", "#FF33A1", "#33FFD7", 
    "#FFDA33", "#33FFDA", "#DA33FF", "#FFD733", "#33DAFF", 
    "#FF8000", "#00FF80", "#8000FF", "#FF0080", "#00FF8A", 
    "#FFD700", "#00FFD7", "#D700FF", "#FF0077", "#7F00FF", 
    "#FF6347", "#4682B4", "#8A2BE2", "#FF4500", "#2E8B57", 
    "#D2691E", "#A52A2A", "#8B4513", "#B22222", "#556B2F", 
    "#8B008B", "#006400", "#2F4F4F", "#B8860B", "#228B22", 
    "#9932CC", "#8B0000", "#D3D3D3", "#B0E0E6", "#20B2AA", 
    "#FF1493", "#FF00FF", "#C71585", "#8B0000", "#F08080", 
	"#BDB76B", "#FF8C00", "#A9A9A9", "#0066CC", "#8B0000", 
    "#8A2BE2", "#5F9EA0", "#D2691E", "#DC143C", "#00008B", 
    "#008B8B", "#B8860B", "#A52A2A", "#5C4033", "#D3D3D3", 
    "#FFD700", "#FF00FF", "#00BFFF", "#8B4513", "#D8BFD8", 
    "#FF6347", "#B22222", "#8FBC8F", "#B0E0E6", "#B22222", 
    "#9ACD32", "#DAA520", "#FF7F50", "#3CB371", "#D3D3D3", 
    "#F08080", "#ADFF2F", "#E9967A", "#C71585", "#DB7093", 
    "#FFE4E1", "#FF4500", "#E6E6FA", "#800080", "#98FB98", 
    "#8B0000", "#FFFF00", "#7FFF00", "#20B2AA", "#FF6347", 
    "#F0E68C", "#E6A8D7", "#D3D3D3", "#C71585", "#F5F5F5", 
    "#32CD32", "#00FF7F", "#7CFC00", "#FA8072", "#DDA0DD"
};

typedef struct {
    char * userName;
    const char * color;
} UserColorPair;

UserColorPair usersWithColors[100]; 
int usersWithColorsIndex = 0;

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
static void addTasksAndEvents(GenerateEntry * generateEntry, FILE *file);
static void addGroupsTasksAndEvents(GenerateEntry * generateEntry, FILE *file, UserEntry * user, GroupHashEntry ** processesGroups, int first);


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
	"			 initialDate: '%d-%02d-%02d',\n"
    "            headerToolbar: {\n"
    "                left: '',\n"
    "                center: 'title',\n"
    "                right: ''\n"
    "            },\n"
    "            events: [\n", generateEntry->generate->start_date->day, generateEntry->generate->start_date->month, generateEntry->generate->start_date->year);

	addTasksAndEvents(generateEntry, file);


    fprintf(file,
    	"	            ],\n"
		"            eventTimeFormat: { \n"
		"               hour: 'numeric', \n"
		"               minute: '2-digit',\n"
		"               hour12: false, \n"
		"               meridiem: false \n"
		"            }\n"
		"        });\n\n"
		"        calendar.render();\n"
		"    });\n");

    _generateInfo(generateEntry, file);
    return;
}


static void _generateMonthly(GenerateEntry * generateEntry, FILE *file){
	fprintf(file, 
	"<script>\n"
    "	document.addEventListener('DOMContentLoaded', function() {\n"
    "   	var calendarEl = document.getElementById('calendar');\n"
	"	 	var startDate = '%d-%02d-%02d';  \n"
	"	 	var endDate = new Date(startDate); \n"
	" 	 	endDate.setFullYear(endDate.getFullYear() + 1); \n"
	"  	 	var formattedEndDate = endDate.toISOString().split('T')[0]; \n"
    "   	var calendar = new FullCalendar.Calendar(calendarEl, {\n"
    "       	initialView: 'dayGridMonth',\n"
	" 			initialDate: startDate, \n"
    "    		validRange: { 			\n"
    "         		start: startDate, 		\n"
    "        		end: formattedEndDate 		\n"
    "  		 	},	\n"
    "        	headerToolbar: {		\n"
    "           	left: '',	\n"
    "            	center: 'title',	\n"
    "           	right: ''	\n"
    "        	},\n"
    "        	locale: 'es',\n"
    "        	events: [\n", generateEntry->generate->start_date->day, generateEntry->generate->start_date->month, generateEntry->generate->start_date->year);

	addTasksAndEvents(generateEntry, file);



	fprintf(file,
    	"	            ],\n"
		"	   eventTimeFormat: { \n"
		"	        hour: 'numeric', \n"
		"	        minute: '2-digit',\n"
		"	        hour12: false, \n"
		"	        meridiem: false \n"
		"	    }\n"
		"    });\n\n"
		"    calendar.render();\n"
		"});\n");
	_generateInfo(generateEntry, file);
	return;
}

void _generateYearly(GenerateEntry * generateEntry, FILE *file){
	fprintf(file,
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
		"<script>\n"
		"    document.addEventListener('DOMContentLoaded', function() {\n"
		"       var calendarEl = document.getElementById('calendar');\n\n"
		"	    var startDate = '%d-%02d-%02d';  \n"
		"   	var endDate = new Date(startDate); \n"
		" 	    endDate.setFullYear(endDate.getFullYear() + 1); \n"
		"  	    var formattedEndDate = endDate.toISOString().split('T')[0]; \n"
		"       var calendar = new FullCalendar.Calendar(calendarEl, {\n"
		"           timeZone: 'UTC',\n"
		"           initialView: 'multiMonth',\n"
		"		    initialDate: startDate,   \n"
    	"    	    validRange: { 			   \n"
    	"         		start: startDate, 		\n"
    	"        		end: formattedEndDate 		\n"
    	"  		    },	\n"
		"       headerToolbar: {\n"
		"           left: '',\n"
		"           center: 'title',\n"
		"           right: ''\n"
		"       },\n"
		"       views: { 							\n"
		"		    multiMonth: {	  				\n"
    	"    	 	    duration: { months: 12 }	\n"
    	"         	} 								\n"
    	"  		},	\n"
		"       locale: 'es',\n"
		"       editable: true,\n"
		"       events: [\n", generateEntry->generate->start_date->day, generateEntry->generate->start_date->month, generateEntry->generate->start_date->year);

		addTasksAndEvents(generateEntry, file);

			//fprintf(file,"            { title: 'Presentación del proyecto X', start: '2024-11-16T14:00:00', end: '2024-11-16T15:30:00' },\n");
			//fprintf(file,"            { title: 'Clase de Yoga', daysOfWeek: [2, 4], startTime: '18:00:00', endTime: '19:00:00' },\n");
			//fprintf(file,"            { title: 'Taller de Fotografía', start: '2024-11-18', end: '2024-11-19', allDay: true },\n");
			//fprintf(file,"            { title: 'Cumpleaños de Andrea', start: '2024-11-21', allDay: true },\n");
			//fprintf(file,"            { title: 'Revisión de presupuesto', start: '2024-11-22T10:00:00', end: '2024-11-22T12:00:00' },\n");
			//fprintf(file,"            { title: 'Cena de fin de año', start: '2024-11-30T20:00:00', end: '2024-11-30T23:30:00' }\n");
	
		fprintf(file,
    	"	            ],\n"
		"	   eventTimeFormat: { \n"
		"	        hour: 'numeric', \n"
		"	        minute: '2-digit',\n"
		"	        hour12: false, \n"
		"	        meridiem: false \n"
		"	    }\n"
		"    });\n\n"
		"    calendar.render();\n"
		"});\n"
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
			"    <div id='users'></div>\n"
            "</body>\n");
	logDebugging(_logger, "Prologue generated.");
}

void _generateEpilogue(FILE *file) {
    fprintf(file, 
        "    document.addEventListener('DOMContentLoaded', function() {\n"
        "       var usersDiv = document.getElementById('users');\n"
        "       usersDiv.innerHTML = '';\n");

    for (int i = 0; i < usersWithColorsIndex; i++) {
        fprintf(file, 
            "       var userDiv = document.createElement('div');\n"
            "       userDiv.style.display = 'flex';\n"          
            "       userDiv.style.alignItems = 'center';\n"     
            
            "       var colorBlock = document.createElement('div');\n"
            "       colorBlock.style.width = '20px';\n"          
            "       colorBlock.style.height = '20px';\n"         
            "       colorBlock.style.backgroundColor = '%s';\n"  
            "       colorBlock.style.marginRight = '10px';\n"     

            "       var nameText = document.createElement('span');\n"
            "       nameText.innerText = '%s';\n"                 
            "       nameText.style.color = '#000000';\n"           

            "       userDiv.appendChild(colorBlock);\n"
            "       userDiv.appendChild(nameText);\n"
            "       usersDiv.appendChild(userDiv);\n", 
            usersWithColors[i].color, 
            usersWithColors[i].userName);
    }

    fprintf(file, 
        "   });\n"
        "</script>\n");

    fprintf(file, "</html>\n");

    fclose(file);
    logDebugging(_logger, "Epilogue generated.");
}


void addTasksAndEvents(GenerateEntry * generateEntry, FILE *file) {
    GroupHashEntry * processesGroups = NULL;
    
    UsersList * users = generateEntry->generate->users->user_list;
    int first = 1; 

    int userIndex = backgroundColorsIndex;
    backgroundColorsIndex++;
    while(users != NULL) {
        UserEntry * user = findUserInMap(users->id->id, generateEntry->usersMap);

		const char * color = backgroundColors[userIndex % 50];
        usersWithColors[usersWithColorsIndex].userName = users->id->id;
        usersWithColors[usersWithColorsIndex].color = color;
        usersWithColorsIndex++;

        EventNode * userEvents = user->eventsListFirst;

        while (userEvents != NULL) {
            if (!first) {
                fprintf(file, ",\n");
            } else {
                first = 0;
            }
            CreateEvent * event = userEvents->event;
            fprintf(file, "                { title: '%s', start: '%d-%02d-%02dT00:00:00', end: '%d-%02d-%02dT00:00:00',", 
                    event->id->id, event->start_date->day, event->start_date->month, event->start_date->year, 
                    event->end_date->day, event->end_date->month, event->end_date->year);
        
			if(generateEntry->generate->def_type == WEEKLY) {
				fprintf(file, "  display: 'background', backgroundColor: '%s' }", color);
			} else {
				fprintf(file, "  color: '%s' }", color);
			} 

            userEvents = userEvents->next;
        }

        TaskNode * userTasks = user->tasksListFirst;
        while (userTasks != NULL) {
            if (!first) {
                fprintf(file, ",\n");
            } else {
                first = 0;
            }
            CreateTask * task = userTasks->task;
            fprintf(file, "                { title: '%s', start: '%d-%02d-%02dT%02d:%02d:00', end: '%d-%02d-%02dT%02d:%02d:00',", 
                    task->id->id, task->date->day, task->date->month, task->date->year, task->start_time->hour, task->start_time->minute, 
                    task->date->day, task->date->month, task->date->year, task->end_time->hour, task->end_time->minute);
            
			if(generateEntry->generate->def_type == WEEKLY) {
				fprintf(file, "  display: 'background', backgroundColor: '%s' }", color);
			} else {
				fprintf(file, "  color: '%s' }", color);
			}
			
			userTasks = userTasks->next;
        }
        
        addGroupsTasksAndEvents(generateEntry, file, user, &(processesGroups), first);

        userIndex = backgroundColorsIndex;
        backgroundColorsIndex++;
        users = users->user_list;
    }

    destroyGroupsMap(processesGroups);
}

void addGroupsTasksAndEvents(GenerateEntry * generateEntry, FILE *file, UserEntry * user, GroupHashEntry ** processesGroups, int first) {
    KeyNode * groups = user->groupFirst;
    int groupIndex = backgroundColorsIndex;
    backgroundColorsIndex++;

    while(groups != NULL) {
        if(findGroupInMap(groups->key, *processesGroups) == NULL) {
			GroupEntry * group = findGroupInMap(groups->key, generateEntry->groupsMap);
            addGroupToGroupMap(group->group, processesGroups); 
			const char * color = backgroundColors[groupIndex % 50];
       		usersWithColors[usersWithColorsIndex].userName = group->group->name->id;
        	usersWithColors[usersWithColorsIndex].color = color;
        	usersWithColorsIndex++;

            EventNode * groupEvents = group->eventsListFirst;
            while (groupEvents != NULL) {
                if (!first) {
                    fprintf(file, ",\n");
                } else {
                    first = 0;
                }
                CreateEvent * event = groupEvents->event;
                fprintf(file, "                { title: '%s', start: '%d-%02d-%02dT00:00:00', end: '%02d-%02d-%02dT00:00:00', ", 
                        event->id->id, event->start_date->day, event->start_date->month, event->start_date->year, 
                        event->end_date->day, event->end_date->month, event->end_date->year);

				if(generateEntry->generate->def_type == WEEKLY) {
					fprintf(file, "  display: 'background', backgroundColor: '%s' }", color);
				} else {
					fprintf(file, "  color: '%s' }", color);
				}

                groupEvents = groupEvents->next;
            }

            // Tareas del grupo
            TaskNode * groupTasks = group->tasksListFirst;
            while (groupTasks != NULL) {
                if (!first) {
                    fprintf(file, ",\n");
                } else {
                    first = 0;
                }
                CreateTask * task = groupTasks->task;
                fprintf(file, "                { title: '%s', start: '%d-%02d-%02dT%02d:%02d:00', end: '%d-%02d-%02dT%02d:%02d:00', ", 
                        task->id->id, task->date->day, task->date->month, task->date->year, task->start_time->hour, task->start_time->minute, 
                        task->date->day, task->date->month, task->date->year, task->end_time->hour, task->end_time->minute);
                
				if(generateEntry->generate->def_type == WEEKLY) {
					fprintf(file, "  display: 'background', backgroundColor: '%s' }", color);
				} else {
					fprintf(file, "  color: '%s' }", color);
				}
				groupTasks = groupTasks->next;
            }
        }

        groupIndex = backgroundColorsIndex;
        backgroundColorsIndex++;
        groups = groups->next;
    }
}

 /** ------------------------- Implementation of public functions ------------------------- **/

void generate(CompilerState * compilerState) {
	// CHANGE LOG FOR PROD
	logInformation(_logger, "Generating final output...");

	GenerateEntryNode * current = getGenerateList();
    
	int i = 1;

	while(current != NULL) {
		char filename[50];
        snprintf(filename, sizeof(filename), "%s.html", current->entry->generate->id->id);

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

	// CHANGE LOG FOR PROD
	logInformation(_logger, "Generation is done.");
}