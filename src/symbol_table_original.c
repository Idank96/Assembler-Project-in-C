#include "global.h"
#include "lists.h"
#include "symbolTable.h"

/*
	- This file manage the symbol-table\linked-list. 	
	- The functions of symbol table are here.
*/

void toSymbolTable(ptr * head, char *symbol_name[STR_SIZE], int * DC, int * IC)
{
	
	ptr temp= (ptr) malloc(sizeof(symbol_node));

	if(!(*symbol))
		return;	

	if(!temp)
	{
		fprintf(stderr, "cannot allocate memory of temp node in add_symbol.(\"symbolTable.c\")");
		exit(0);
	}

	if(extFLAG||dataFLAG||codeFLAG)
		init_symbol(temp);
	else if(entFLAG)
		return;
	
	if(!(isEmpty(head,temp)))
		if(!doubleSymbol(*head,temp))
			add_symbol_end(head,temp);

	return;
}

/*initialize symbol's type and value(address)*/
void init_symbol(ptr temp)
{
	strcpy(temp->name,symbol);	
		
	if(extFLAG){
		strcpy(temp->type,"external");
		temp->value = 0;
	}	
	else if(dataFLAG){
		strcpy(temp->type,"data");
		temp->value = DC;
	}
	else if(codeFLAG){
		strcpy(temp->type,"code");
		temp->value = IC;
	}

	return;
}
/*add symbol to the last of the symbol-table(linked list)*/
void add_symbol_end(ptr * head, ptr temp)
{
	ptr p1, p2;
	p1=*head;

	for(;p1; p1=p1->next)
		p2=p1;
	
	temp->next = p1;
	p2->next = temp;

	return;
}
/*return TRUE if the symbol-table is empty and init the first node in the linked list*/
int isEmpty(ptr * head,ptr temp)
{
	if(!(*head)){
		temp->next=NULL;
		*head=temp;
		return TRUE;
	}

	return FALSE;
}
/*search for symbol that already in the symbol-table, return TRUE if found.*/
int doubleSymbol(ptr head,ptr temp)
{
	while(head)
	{	
		if(!(strcmp(head->name,temp->name))){
			printf("symbol name \"%s\" already exists.\n",temp->name);
			errorFLAG=TRUE;
			return TRUE;
		}
		head = head->next;
	}

	return FALSE;
}


void printSymbolTable(ptr head)
{
	printf("Symbol Table:\n");
	printf("name	value	type\n");
	while(head)
	{	
		printf("%s	%d	%s\n",head->name, head->value, head->type);
		head = head->next;
	}
	puts("--------------");
	return;
}

/*search the entry symbol in the symbol-table, if not found, its an error */
int addEnt()
{
	int found=FALSE;
	ptr h_temp = symbolTable_head;
	while(h_temp)
	{	
		if(!strcmp(h_temp->name,op_array[i_op-1]))
		{
			found = TRUE;
			strcat(h_temp->type , ", entry" );
		}
		h_temp = h_temp->next;
	}
		
	if(!found){
		printf("entry not found\n");
		errorFLAG=TRUE;
		return FALSE;
	}

	return TRUE;		
}
