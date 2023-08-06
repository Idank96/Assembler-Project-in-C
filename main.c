#include "global.h"
#include "lists.h"
#include "main.h"

/*	This is an assembler with 2 passes.
	please read the README file	*/

int main(int argc, char *argv[])
{
	int i_argv=1;
	while(--argc>0){
		strcpy(filename,argv[i_argv++]);
		openfile();
		first_pass();
		second_pass();
		fclose(fd1);
	}
	return 0;
}
/*	-	parse each line
	-	add command to symbol-table (linked list) if needed.
	-	add command to memory-image (linked list).
	-	if an error is found - continue to search for more and exit before the second pass. */
void first_pass()
{
	cnt_lines = 0;
	symbolTable_head = NULL;
	code_head = NULL;
	data_head = NULL;
	IC = 100, DC = 0;
	src_method=dst_method = NO_METHOD;
	opnum1 = opnum2 = DEFAULT;

	while(fgets(line,LINE_SIZE,fd1)!=NULL){
		cnt_lines++;
		if(parseLines(line)){
			/*P_All;*/ 
			toSymbolTable(&symbolTable_head,str_array,&DC,&IC);
			to_memory_image(str_array,&code_head,&DC,&IC);	
			freeAll();
		}
		error(cnt_lines);
	}	
	if(!stopFLAG){
		connnectLists();
		addIC(code_head,symbolTable_head);
	}
		
	printf("FIRST PASS: DONE\n");
	return;
}

void second_pass()
{	
	if(stopFLAG){
		stopFLAG=FALSE;
		printf("not create files\n");
		return;
	}

	cnt_lines=0;	
	second_passFLAG=TRUE;
	rewind(fd1);	
	
	while(fgets(line,LINE_SIZE,fd1)!=NULL){
		cnt_lines++;
		parseLines(line);
		update_memory_image();
		freeAll();
		error(cnt_lines);
	}

	
	exe_files(filename);
	second_passFLAG=FALSE;
	printf("SECOND PASS: DONE\n");

	stopFLAG=FALSE;
	second_passFLAG=FALSE;	
	/*
	printSymbolTable(symbolTable_head);	
	printDataImg(code_head);
	*/
	return;
}
/*check if error occured and turn on stopFLAG*/
void error(int cnt_lines)
{
	if(errorFLAG){
		stopFLAG=TRUE;
		printf("wrong line: %d\n\n",cnt_lines);
		errorFLAG=FALSE;
		freeAll();		
	}
	return;
}

/* 	- init first character of arrays to '\0'
	- init flags to FALSE
	etc. */
void freeAll()
{
	int i;
	for(i=0;op_array[i]!=NULL;i++)
		*op_array[i]='\0';	
	for(i=0;str_array[i]!=NULL;i++)
		*str_array[i]='\0';

	i_command=i_data=i_op=i_word=operands_cnt=0;
	opnum1=opnum2=DEFAULT;
	src_method=dst_method=NO_METHOD;
	*label=*command=*src_rst=*dst_rst=*line_temp='\0';
	memset(symbol,0,STR_SIZE);
	symbolFLAG = dataFLAG = codeFLAG = entFLAG = extFLAG = first_opFLAG = second_opFLAG = FALSE;
	return;
}

/* if the address of object in memory is less then MEMORY_START(100) so add IC so it will be at the end of memory-image list. */
void addIC(memoryObj_ptr code_head, ptr symbol_head)
{
	IDF=DC,ICF=IC-MEMORY_START;
	while(code_head){
		if((code_head->address)<MEMORY_START)
			(code_head->address)+=(IC);
		code_head=code_head->next;		
	}
	while(symbol_head){
		if((symbol_head->value)<MEMORY_START&&strcmp(symbol_head->type,"external"))
			(symbol_head->value)+=(IC);
		symbol_head=symbol_head->next;
	}
	return;
}
