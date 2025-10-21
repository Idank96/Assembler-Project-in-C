#include "global.h"
#include "files.h"
#define NUM_OF_FILES 3

char dir[STR_SIZE]="./tests/"; /*please read README file if you want to create the output files in another file*/

/* opening the file:
	- check that no type-file(with '.') is called from command-line 
	- using strcat to contcatenates '.as' to the filename and than contcatenates this name to the folder name ('dir') 
	- then, search for the file in the folder in 'dir'. 
*/
void openfile()
{
	char *to_open = malloc(LINE_SIZE);
	char *dir_filename=malloc (LINE_SIZE);
	char *p=filename;
	int c;
	strcpy(to_open,filename);

	for(c=*p;c;c=*(p+1),p++)	
		if(c=='.'){
			printf("cannot open file\n");
			exit(1);
		}

	strcat(to_open,".as");
	strcpy(dir_filename,dir);
	strcat(dir_filename,to_open);
	printf("\n\n\nfile: %s\n\n\n\n",to_open);
	if(!(fd1 = fopen(dir_filename,"r"))){
			printf("cannot open file\n");
			exit(0);			
			}
	free(dir_filename);
	return;
}

/*create 3 files using function pointer to 3 function, every time create other file*/

void exe_files(char *name)
{
	FILE *file;
	int i;
	char temp[LINE_SIZE],*dir_filename;
	char *type[NUM_OF_FILES] = {".ob",".ent",".ext"};
	void (*pf[NUM_OF_FILES])(FILE**) = {creat_obj_file,creat_ent_file,creat_ext_file};
	
	for(i=0;i<NUM_OF_FILES;i++)
	{	dir_filename = malloc(LINE_SIZE);
		strcpy(dir_filename,dir);
		strcpy(temp,name);
		strcat(temp,type[i]);
		strcat(dir_filename,temp);
		if(!(file = fopen(dir_filename,"w"))){
			printf("cannot open file\n");
			exit(0);			
		}		
		(*pf[i])(&file);	
	}

	return;
}

/*
------------------------------------------------
-- wMemory, wEntry, wExternal in memoryList.c --
------------------------------------------------
*/
void creat_obj_file(FILE **file){
	fprintf(*file,"\t\t\t\t%d %d\n",ICF,IDF);
	wMemory(file);	
	return;
}
void creat_ent_file(FILE **file){
	wEntry(file);
	return;
}

void creat_ext_file(FILE **file){
	wExternal(file);
	return;
}
