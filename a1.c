// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguage {
	int id;
	char* language;
	int year;
	char* creator;
	char* paradigm;
	double popularityIndex;

	int isDeleted; // internal field, not accessible to user
} language_t;

// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field

typedef struct operatingSystems {
	int id;
	char* name;
	int year;
	char* developer;
	char* kernelType;

	int isDeleted;
} opSys_t;

typedef struct databases {
	int id;
	char* name;
	int year;
	char* type;
	char* developer;

	int isDeleted;
} databases_t;


// step 2: create typedef struct for storing metadata

typedef struct metadata {
	int count;
	int nextIndex;
	int maxCount;
} metadata_t;

// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases
language_t* programmingLanguages; 									//DECLARATIONS
opSys_t* operatingSystems;
databases_t* databases;

// step 4: declare 3 metadata structs, one for each table

metadata_t progLanguagesMeta;
metadata_t opSystemsMeta;
metadata_t DBMeta;

// step 5: jump to L167


// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}

// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.
void setup(char* table, int numRows) {															//passing in reference to first element in array

	if(strcmp(table, "programmingLanguages") == 0){
		if (progLanguagesMeta.maxCount != 0) {
			for(int i = 0; i < progLanguagesMeta.count; i++){
				free(programmingLanguages[i].language);
				free(programmingLanguages[i].creator);
				free(programmingLanguages[i].paradigm);
			}
			free(programmingLanguages);
		}
		programmingLanguages = (language_t *)malloc(sizeof(language_t) * numRows); //array of structs = table
		progLanguagesMeta.maxCount = numRows; //the max count of metadata is the number of structs aka numRows

		progLanguagesMeta.count = 0;
		progLanguagesMeta.nextIndex = 0;

		} else if(strcmp(table, "operatingSystems") == 0){
			if (opSystemsMeta.maxCount != 0) {
				for(int i = 0; i < opSystemsMeta.count; i++){
					free(operatingSystems[i].name);
					free(operatingSystems[i].developer);
					free(operatingSystems[i].kernelType);
				}

				free(operatingSystems);
			}
				operatingSystems = (opSys_t *)malloc(sizeof(opSys_t) * numRows);
				opSystemsMeta.maxCount = numRows;

				opSystemsMeta.count = 0;
				opSystemsMeta.nextIndex = 0;



			} else if(strcmp(table, "databases") == 0){
					if (DBMeta.maxCount != 0) {
						for(int i = 0; i < DBMeta.count; i++){
							free(databases[i].name);
							free(databases[i].type);
							free(databases[i].developer);
						}
						free(databases);
					}
					databases = (databases_t *)malloc(sizeof(databases_t) * numRows);
					DBMeta.maxCount = numRows;

					DBMeta.count = 0;
					DBMeta.nextIndex = 0;

				}
	

	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("setup complete\n");
}

// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {		//double pointer array of strings, string is alr a pointer	

	if(strcmp(args[1], "programmingLanguages") == 0){
		if(progLanguagesMeta.nextIndex < progLanguagesMeta.maxCount){
			language_t ProgStruct = {}; //programmingLanguagues struct named ProgStruct

				ProgStruct.id = atoi(args[2]);
				ProgStruct.year = atoi(args[4]);
				ProgStruct.popularityIndex = atof(args[7]);

	
				ProgStruct.language = (char *)malloc((sizeof(char) * strlen(args[3])) + 1); //pointer - malloc pointer
				strcpy(ProgStruct.language, args[3]);  //copy pointer of args[3] to progstruct pointer

				//same thing as strdup that args to that index of the table at that id

				ProgStruct.creator = (char *)malloc((sizeof(char) * strlen(args[5])) + 1);
				strcpy(ProgStruct.creator, args[5]);

				ProgStruct.paradigm = (char *)malloc((sizeof(char) * strlen(args[6])) + 1);
				strcpy(ProgStruct.paradigm, args[6]);

				programmingLanguages[progLanguagesMeta.nextIndex] = ProgStruct; //array of type struct - first index, put an array into it
				progLanguagesMeta.count++;
				progLanguagesMeta.nextIndex++;
			
		
			} else {
				fprintf(stderr, "cannot insert due to insufficient capacity.\n");
				return;

				} 

					//arrays are malloced and global, so can use in any method
					//ProgStruct is local so is deleted after function ends -- but a copy is in the array 

		} else if(strcmp(args[1], "operatingSystems") == 0){ //same as *args
				
				if(opSystemsMeta.nextIndex < opSystemsMeta.maxCount){
					opSys_t OpSys = {};

					OpSys.id = atoi(args[2]);
					OpSys.year = atoi(args[4]);

					OpSys.name = (char *)malloc((sizeof(char) * strlen(args[3]) + 1));
					strcpy(OpSys.name, args[3]);

					OpSys.developer = (char *)malloc((sizeof(char) * strlen(args[5]) + 1));
					strcpy(OpSys.developer, args[5]);

					OpSys.kernelType = (char *)malloc((sizeof(char) * strlen(args[6]) + 1));
					strcpy(OpSys.kernelType, args[6]);
					operatingSystems[opSystemsMeta.nextIndex] = OpSys; //array of type struct - first index, put an array into it
					opSystemsMeta.count++;
					opSystemsMeta.nextIndex++;
					

				} else {
					fprintf(stderr, "cannot insert due to insufficient capacity.\n");
					return;
				} 

			} else if(strcmp(args[1], "databases") == 0){

				if(DBMeta.nextIndex < DBMeta.maxCount){
					databases_t DataB = {};

					DataB.id = atoi(args[2]);
					DataB.year = atoi(args[4]);


					DataB.name = (char *)malloc((sizeof(char) * strlen(args[3])) + 1);
					strcpy(DataB.name, args[3]);

					DataB.type = (char *)malloc((sizeof(char) * strlen(args[5])) + 1);
					strcpy(DataB.type, args[5]);

					DataB.developer = (char *)malloc((sizeof(char) * strlen(args[6])) + 1);
					strcpy(DataB.developer, args[6]);

					databases[DBMeta.nextIndex] = DataB; //array of type struct - first index, put an array into it
					DBMeta.count++;
					DBMeta.nextIndex++;
				
				} else {

					fprintf(stderr, "cannot insert due to insufficient capacity.\n");
					return;
				}
			}
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("insert complete\n");
}

// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record. 
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {

	if(strcmp(table, "programmingLanguages") == 0){
		for(int i = 0; i < progLanguagesMeta.nextIndex; i++){ //.maxCount would mean u would access id of nothing if not all spots filled
			if(programmingLanguages[i].id == id){ //finding the struct
				programmingLanguages[i].isDeleted = 1;
			}
		}
	} else if(strcmp(table, "operatingSystems") == 0){ 
		for(int i = 0; i < opSystemsMeta.nextIndex; i++){
			if(operatingSystems[i].id == id){ 
				operatingSystems[i].isDeleted = 1;
			}
		}		
	} else if(strcmp(table, "databases") == 0){
		for(int i = 0; i < DBMeta.nextIndex; i++){
			if(databases[i].id == id){ 
				databases[i].isDeleted = 1;
			}
		}
	}


	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("delete complete\n");
}

// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {

	if(strcmp(args[1], "programmingLanguages") == 0){

		for(int i = 0; i < progLanguagesMeta.maxCount; i++){
			if(programmingLanguages[i].id == atoi(args[2])) {
				free(programmingLanguages[i].language);
				free(programmingLanguages[i].creator);
				free(programmingLanguages[i].paradigm);

				programmingLanguages[i].id = atoi(args[3]);
				programmingLanguages[i].language = strdup(args[4]);
				programmingLanguages[i].year = atoi(args[5]);
				programmingLanguages[i].creator = strdup(args[6]);
				programmingLanguages[i].paradigm = strdup(args[7]);
				programmingLanguages[i].popularityIndex = atof(args[8]);
			}
		}
		} else if (strcmp(args[1], "operatingSystems") == 0){ 
			for(int i = 0; i < opSystemsMeta.maxCount; i++){
				if(operatingSystems[i].id == atoi(args[2])){
					free(operatingSystems[i].name);
					free(operatingSystems[i].developer);
					free(operatingSystems[i].kernelType);

					operatingSystems[i].id = atoi(args[3]);
					operatingSystems[i].name = strdup(args[4]);
					operatingSystems[i].year = atoi(args[5]);
					operatingSystems[i].developer = strdup(args[6]);
					operatingSystems[i].kernelType = strdup(args[7]);
				}
			}
		} else if(strcmp(args[1], "databases") == 0){
			for(int i = 0; i < DBMeta.maxCount; i++){
					if(databases[i].id == atoi(args[2])){
						free(databases[i].name);
						free(databases[i].type);
						free(databases[i].developer);

						databases[i].id = atoi(args[3]);
						databases[i].name = strdup(args[4]);
						databases[i].year = atoi(args[5]);
						databases[i].type = strdup(args[6]);
						databases[i].developer = strdup(args[7]);
					}
			}
		}
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
	if(strcmp(table, "programmingLanguages") == 0){
		printf("id,language,year,creator,paradigm,popularityIndex\n");
		for(int i = 0; i < progLanguagesMeta.nextIndex; i++){
			if(programmingLanguages[i].isDeleted == 0){
				printf("%d,%s,%d,%s,%s,%lf\n", programmingLanguages[i].id, programmingLanguages[i].language, 
				programmingLanguages[i].year,programmingLanguages[i].creator, programmingLanguages[i].paradigm,programmingLanguages[i].popularityIndex);
			}
		}

	} else if(strcmp(table, "operatingSystems") == 0){
		printf("id,name,year,developer,kernelType\n");
		for(int i = 0; i < opSystemsMeta.nextIndex; i++){
			if(operatingSystems[i].isDeleted == 0){
				printf("%d,%s,%d,%s,%s\n", operatingSystems[i].id, operatingSystems[i].name, 
				operatingSystems[i].year,operatingSystems[i].developer, operatingSystems[i].kernelType);
			}
		}

	} else if(strcmp(table, "databases") == 0){
		printf("id,name,year,type,developer\n");
		for(int i = 0; i < DBMeta.nextIndex; i++){
			if(databases[i].isDeleted == 0){
				printf("%d,%s,%d,%s,%s\n", databases[i].id, databases[i].name, 
				databases[i].year,databases[i].type, databases[i].developer);
			}
		}
	}
}

// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {
	for(int i = 0; i < progLanguagesMeta.count; i++){
		free(programmingLanguages[i].language);
		free(programmingLanguages[i].creator);
		free(programmingLanguages[i].paradigm);
	}
	free(programmingLanguages);

	for(int i = 0; i < opSystemsMeta.count; i++){
		free(operatingSystems[i].name);
		free(operatingSystems[i].developer);
		free(operatingSystems[i].kernelType);
	}
	free(operatingSystems);

	for(int i = 0; i < DBMeta.count; i++){
		free(databases[i].name);
		free(databases[i].type);
		free(databases[i].developer);
	}
	free(databases);

	exit(0);
	
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
	char* cmd = args[0];
	if (strcmp(cmd, "setup") == 0) {
		setup(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "insert") == 0) {
		insert(args);
	} else if (strcmp(cmd, "delete") == 0) {
		delete(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "modify") == 0) {
		modify(args);
	} else if (strcmp(cmd, "get") == 0) {
		get(args[1]);
	} else if (strcmp(cmd, "exit") == 0) {
		exitProgram();
	} else {
		printf("\n");
	}
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
	progLanguagesMeta.count = 0;
	progLanguagesMeta.maxCount = 0;
	progLanguagesMeta.nextIndex = 0;

	opSystemsMeta.count = 0;
	opSystemsMeta.maxCount = 0;
	opSystemsMeta.nextIndex = 0;

	DBMeta.count = 0;
	DBMeta.maxCount = 0;
	DBMeta.nextIndex = 0;
}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
	char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
	printf("Usage: \n");
	printf("setup {table} {numRows}\n");
	printf("insert {table} {data}\n");
	printf("delete {table} {id}\n");
	printf("modify {table} {id} {data}\n");
	printf("get {table}\n\n");
	initializeMetadata();
    while (1) {
        printf("CS211> ");
		fflush(stdout);
        
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
        
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (bytes_read == 0) {
			printf("\n");
            break;
        }
        
        // Null-terminate the input
        input[bytes_read] = '\0';

		char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
		int arg_count;

		splitInput(input, args, &arg_count);
        
        // Execute the user's command
        execute_cmd(args, arg_count);
		free(args);
    }
}


int main() {
	cmd_loop();
}