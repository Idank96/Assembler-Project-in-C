#ifndef global

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_SIZE 32
#define LABEL_SIZE 31
#define LINE_SIZE 80
#define FALSE 0
#define TRUE 1
#define REGISTERS_NUM 8
#define REGISTER_NAME_SIZE 2
#define DATA_TYPES_NUM 4
#define CODE_TYPES_NUM 16

/*24 bits word.*/
typedef union word word_union;
typedef union word word_node;
union word{
		unsigned index;
		struct{	
			unsigned int E:1;
			unsigned int R:1;
			unsigned int A:1;
			unsigned int funct:5;
			unsigned int register_d:3;
			unsigned int destination_m:2;
			unsigned int register_s:3;
			unsigned int source_m:2;
			unsigned int opcode:6;
		}bits;
};	

/*global variables*/
FILE *fd1;
char filename[STR_SIZE];
int IC, DC, ICF, IDF;
char *str_array[STR_SIZE]/*the main array to parse*/, line[LINE_SIZE], line_temp[LINE_SIZE];	
char symbol[STR_SIZE], command[STR_SIZE], src_rst[REGISTER_NAME_SIZE], dst_rst[REGISTER_NAME_SIZE], label[LABEL_SIZE]; /*store values*/
char data_string[STR_SIZE];
char *op_array[STR_SIZE]; /*array for the operands*/
int src_method,dst_method,operands_cnt,opnum1,opnum2;
int i_command; /*current command that need to be analyzed*/
int i_data; /*the current data to parse*/
int i_op; /*number of operand to parse*/
int i_word; /*current word to parse*/
int num_of_words;
int symbolFLAG, dataFLAG, codeFLAG, entFLAG, extFLAG,first_opFLAG,second_opFLAG, stringFLAG, second_passFLAG,stopFLAG, errorFLAG,end_commaFLAG;


#endif
