#include "global.h"
#include "structers.h"
#include "code.h"

/*
	for each operand:
	- delete end-comma if found
	- if the word itself is comma put '\0' instead.
	- check whether operand is register, label, number, or jump operand
	  and set the variable src\dst-method according to first operand or seond operand
*/
int get_code_param(char *str_array[STR_SIZE])
{
	delete_end_comma(str_array[i_word]);

	op_array[i_op] = (char *)malloc(STR_SIZE);	

	if(isComma(str_array[i_word]))
	{
		str_array[i_word]='\0';
		return FALSE;
	}
	else if(isRegister(str_array[i_word]));
	else if(isLabel(str_array[i_word]));
	else if(is_op_num(str_array[i_word]));	
	else if(is_jump_op(str_array[i_word]));
	else if(errorFLAG)
		return FALSE;
	else{
		printf("unvalid operand\n");
		return FALSE;
	}
	/*if op found && command no need more operands*/
	if(!commands_array[i_command].operands_num)
		printf("too many operands\n");
		
	i_word++;
	return TRUE;
}

/*check whether operand is register according to rgstrs_arr and set method variable */
int isRegister(char *str)
{	
	int i;
	
	for(i=0;i<REGISTERS_NUM;i++)
	{	
		if(!(strcmp(rgstrs_arr[i].name,str)))
		{
			strcpy(op_array[i_op],str);
			if(!first_opFLAG && commands_array[i_command].operands_num>=2){
				strcpy(src_rst,++str);
				src_method=fourth;
			}
			else{
				strcpy(dst_rst,++str);
				dst_method=fourth;
			}
			return TRUE;	
		}
	}
	if(*str=='r' && isdigit(*(++str))){
		printf("register name not exist\n");
		errorFLAG=TRUE;
		return FALSE;
	}	

	return FALSE;
}
/*check whether operand is label(and check if valid) and set method variable */
int isLabel(char *str)
{
	int i;
	
	for(i=0; i<=LABEL_SIZE && str[i]!='\0' ;i++){
		if(i==LABEL_SIZE){ /*bigger then 31 characters*/
			printf("label can't be bigger then 31 characters\n");	
			errorFLAG=TRUE;
			return FALSE;	
		}	
		else if(!(isalpha(str[i]))&&!(isdigit(str[i])))
			return FALSE;
	}
	strcpy(op_array[i_op],str);
	if(!first_opFLAG && commands_array[i_command].operands_num>=2){
		strcpy(label,str);
		src_method=second;
	}
	else{
		strcpy(label,str);
		dst_method=second;
	}
	return TRUE;
}
/*check whether operand is jump operand and set method variable */
int is_jump_op(char *str)
{
	if(*(str++)!='&')
		return FALSE;
	if(!(isLabel(str)))
		return FALSE;

	if(!first_opFLAG && commands_array[i_command].operands_num>=2)
		src_method = third;
	else
		dst_method=third;
		
	return TRUE;
}
/*
	check whether operand is number operand and set method variable 
	check if starts with #.
*/
int is_op_num(char *str)
{
		
	if(*(str++)!='#')
		return FALSE;

	strcpy(op_array[i_op],str);
	
	if(!first_opFLAG && commands_array[i_command].operands_num>=2){ 
		opnum1=atoi(str);
		src_method = first;
	}
	else{
		opnum2=atoi(str);
		dst_method=first;
	}

	return TRUE;
}


/*validate that the source method is match to one of command's source methods*/
int valid_srcMethod(char *op_str)
{
	int i;
	for(i=0;i<NUM_OF_METHODS-1;i++)
		if((commands_array[i_command].source_method[i]==src_method))
			return TRUE;
	printf("src_method not valid to command\n");
	errorFLAG=TRUE;
	return FALSE;
}

/*validate that the destination method is match to one of command's destination methods*/
int valid_dstMethod(char *op_str)
{
	int i;
	for(i=0;i<NUM_OF_METHODS-1;i++)
		if((commands_array[i_command].destination_method[i]==dst_method))
			return TRUE;
	printf("dst_method not valid to command\n");
	errorFLAG=TRUE;
	return FALSE;
}

/*
	 if command need 2 parameters and first operand didn't found - get source method.
	 if command need 1 parameter leave the source method with zeros and set get distance method.
*/
void valid_op()
{
	if(!first_opFLAG && commands_array[i_command].operands_num>=2){	
		first_opFLAG=TRUE;
		valid_srcMethod(op_array[i_op]);
	}
	else if (!second_opFLAG){
		second_opFLAG=TRUE;
		valid_dstMethod(op_array[i_op]);
	}
		return;
}
