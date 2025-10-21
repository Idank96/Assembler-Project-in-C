#include "global.h"
#include "parseLines.h"
#include "structers.h"


int i;
int commas;
char *wrong_str;
/*
	parseline:
			-	skip line
			-	split line to 'str_array'(global)
			-	after initialize 'str_array', if we are in the second pass, go to second_parse.
			-	op_array used to store the operands
	
*/
int parseLines(char line[LINE_SIZE])
{
		commas = i_word = i_op = num_of_words = 0; /*'i_word' used to look for the current word in str_array. 	*/
		if(skipLine(line))
			return FALSE;

		splitLine(line);

		if((symbolFLAG = isSymbol())== TRUE)
			i_word++;
		else if(symbolFLAG == ERROR)
			return FALSE;

		
		if(second_passFLAG){
			if(!(second_parse(line)))
				return ERROR;
			return FALSE;
		}
		
		if(extOrEnt(str_array[i_word]))
		{	
			op_array[i_op] = (char *)malloc(STR_SIZE);
			op_array[i_op++] = getE(str_array[i_word]);
		}			
		else if(isData(str_array[i_word])){
			i_word++;
			get_data_param(str_array);	
		}
		else if(isCode(str_array[i_word]))
		{	
			i_word++;
			for(operands_cnt=commands_array[i_command].operands_num ; operands_cnt>0 ; operands_cnt--)
			{	
				commas=delete_start_comma(str_array[i_word]);
				if(errorFLAG || commas==ERROR || *str_array[i_word]=='\0'){
					break;
				}
				if(get_code_param(str_array)){
					valid_op();
					i_op++;/*to insert the next operand to the next adress in "op_array"*/
				}
			}
			if(operands_cnt>0){
				if(!errorFLAG){
					printf("operands missing\n");
					errorFLAG=TRUE;
				}
				return FALSE;
			}	
				
			/*check if there are too much operands*/
		}	
		else{
			findError(str_array[i_word]);
			return FALSE;
		}
		
		/*free(wrong_str);*/
			
	return TRUE;
}

/*check if it is a symbol...*/
char *getE(char *str)
{
	strcpy(symbol,str_array[i_word]);
	symbolFLAG=TRUE;
	i_word++;
	return str;

}

/*
	split the line into array of strings (str_array) with strtok() function
	if its the last word of the line, replace '\n' with '\0'
*/

void splitLine(char line[LINE_SIZE])
{
	int i=0;	
	char *token=strtok(line," \t");

	str_array[i] = (char *) malloc((strlen(token)+1)*sizeof(char*));
	strcpy(str_array[i],token);

	while(token!=NULL)
	{
   		token = strtok(NULL," \t");
		if(token!=NULL){
			str_array[++i] = (char *) malloc((strlen(token)+1)*sizeof(char*));
			strcpy(str_array[i],token);
		}
	}	
	num_of_words+=(i+1);
	/*go to end of last string and switch '\n' to '\0' */
	token = (str_array[i]);	
	while(*(++token)!='\n');
	*token='\0';
	return;
}

/* if line starts with ';' or its empty  return TRUE to skip the line*/
int skipLine(char *str)
{
	if((*str==';') || !(strcmp(str,"\n")))
			return TRUE;
	return FALSE;
}

/*
	check if comma is between spaces or at the beginning of an operand.
	error when: comma before the first operand \ too many commas  between operands.
	if valid - skip it.
*/
int delete_start_comma(char *str)
{
	char temp_str[STR_SIZE];
	char *ptr=temp_str;
	strcpy(temp_str,str);

	if(*(ptr++)==',')
	{
		if(!first_opFLAG){ /*first operand not initialized*/
			printf("comma before first operand\n");
			errorFLAG=TRUE;
			return ERROR;
		}

		if(*ptr=='\0')
			i_word++;
		else if(*ptr==',')
		{
			printf("too many commas\n");
			errorFLAG=TRUE;
			return ERROR;
		}
		
		strcpy(str,ptr);
			return 1;
	}


	return 0;
}

/*delete the last comma of operand and set end_commaFLAG TRUE;*/

void delete_end_comma(char *str)
{
	while(*(++str)!='\0'); /*go to end of string to search ','*/
	/*delete','*/	
	if(*(--str)==',')
	{
		commas++;
		*str='\0';
		end_commaFLAG=TRUE;
	}
	return;
}

/*check if current word is comma*/
int isComma(char *str)
{
	char temp_str[STR_SIZE];
	char *ptr=temp_str;
	strcpy(temp_str,str);
		
	if(*(ptr++)==',')
	{
		if(*(ptr)=='\0')
		{
			i_word++;
			return TRUE;
		}
	}
	return FALSE;
}		

/*
	Check if current word is symbol:
	- if its not code or data or letter - return FALSE
	- if ':' found at the end of the string delete it and put '\0', else return ERROR
*/
int isSymbol()
{
	char temp_str[STR_SIZE];
	char *ptr_str = str_array[i_word];
	strcpy(temp_str,str_array[i_word]);
	
	if(!isalpha(*ptr_str)||CodeOrData(str_array[i_word]))
		return FALSE;
		
	while(*(++ptr_str)!='\0'); /*go to end of string to search ':'*/
	
	/*delete':'*/
	if(*(--ptr_str)==':'){
		*ptr_str='\0';
		strcpy(symbol,str_array[i_word]);
		symbolFLAG=TRUE;
		return TRUE;
	}
	else
	{	
		if(!CodeOrData(str_array[i_word])){
			printf("erorr in label name\n");
			errorFLAG=TRUE;
			return ERROR;	
		}
	}
	return FALSE;
}
/* if current word is code or data*/
int CodeOrData()
{
	int i;

	for(i=0 ;i<DATA_TYPES_NUM; i++)
		if(!strcmp(str_array[i_word],data_arr[i].name))
			return TRUE;

	for(i=0 ;i<NUM_OF_COMMANDS; i++)
		if(!strcmp(str_array[i_word],commands_array[i].name))
			return TRUE;

	return FALSE;

}

/*
	- check if current word is data
	- set i_data to the number of the data.
	- turn on dataFLAG
	- copy data to command array
*/
int isData(char *str)
{	
	int i;

	for(i=0 ;i<DATA_TYPES_NUM; i++)
	{
		if(!strcmp(str,data_arr[i].name))
		{
			strcpy(command,str);
			dataFLAG=TRUE;
			i_data=i;
			return TRUE;		
		}
	}
	return FALSE;
}

/*
	- check if current word is data
	- set i_command to the number of the code.
	- turn on codeFLAG
	- copy code to command array
*/
int isCode(char *str)
{
	int i;

	for(i=0 ;i<NUM_OF_COMMANDS; i++)
	{
		if(!strcmp(str,commands_array[i].name))
		{
			strcpy(command,str);
			codeFLAG=TRUE;
			i_command=i;;
			return TRUE;
		}		
	}

	return FALSE;
}

/*find more errors*/
void findError(char *str)
{
	int c=*str;
	if(c==',')
	{
		commas++;
		if(symbolFLAG){
			printf("Comma between symbol and command\n");
			errorFLAG=TRUE;
		}
	}
	
	if(isalpha(c)){
		printf("Command not recognized\n");
		errorFLAG=TRUE;
	}
		
	i_word++;
	return;
}

/*
	if str is:  extern - turn on extern-flag
				entry - turn on entry-flag
				else - return FALSE;


*/
int extOrEnt(char *str)
{
	if(!strcmp(str,".extern"))
		extFLAG=TRUE;
	else if (!strcmp(str,".entry"))
		entFLAG=TRUE;
	else
		return FALSE;

	i_word++;
	return TRUE;
}

/*if its an entry , add "entry" to symbol-table-type*/
int second_parse(char line[LINE_SIZE])
{
	if(extOrEnt(str_array[i_word]))
		{
			if(entFLAG)
			{
				op_array[i_op] = (char *)malloc(STR_SIZE);
				op_array[i_op++] = getE(str_array[i_word]);
				if(!(addEnt()))
					return FALSE;
			}
		}
	
	return TRUE;
}
