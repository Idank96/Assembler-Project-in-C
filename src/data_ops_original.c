#include "global.h"
#include "data.h"
#include "structers.h"

/*	check whether operand is data or string.
	if data, loop on operands */
int get_data_param(char *str_array[STR_SIZE])
{
	if(is_data_data(str_array[i_word]))
		for(;str_array[i_word]&&*str_array[i_word]!='\0';i_word++){
			op_array[i_op] = (char *)malloc(STR_SIZE);
			op_array[i_op++] = get_op(str_array[i_word]);
		}
	else if(is_string_data(str_array[i_word]));

	return TRUE;
}

/* check if its a string with quotation marks (delete them and put the string into op_array) */

int is_string_data(char *str)
{
	int c;
	char *temp;
 
	if(strcmp(command,data_arr[i_data].name))	
		return FALSE;
	
	if((c=*str)!='"')
	{
		printf("missing \"\n");	
		errorFLAG=TRUE;
		return FALSE;	
	}		
	*str='\0';
	temp=++str;
	for(c=(*str);(c=*str)!='\0';str++);

	if((c=*(--str))!='"'){
		printf("missing \"\n");
		errorFLAG=TRUE;
		return FALSE;
	}
	*str='\0';
	op_array[i_op] = (char *)malloc(STR_SIZE);
	strcpy(op_array[i_op],temp);

	stringFLAG=TRUE;
	return TRUE;
}

/* if operand is digit */
int is_data_data(char *str)
{
	int c=*str;

	if(signFound(str));
	else if(!isdigit(c))
		return FALSE;
	
	return TRUE;
	
}

/*if operand starts with sign or*/
int signFound(char *str)
{
	int c=*str;	
	if(c=='-'||c=='+')
		return TRUE;
	
	return FALSE;
}

/*get operand*/
char *get_op(char *str)
{
	int c;
	char *temp = str;
	delete_end_comma(str);

	while((c=*temp)!='\0')
	{
		if(signFound(str));
		else if(!isdigit(c))	
			return FALSE;	
		temp++;
	}	
	return str;	
}
