/*
 * global.c - Global variable definitions
 * This file contains the actual definitions of global variables
 * declared in global.h and lists.h with 'extern'
 */

#include "global.h"
#include "lists.h"

/* File handling */
FILE *fd1;
char filename[STR_SIZE];

/* Counters */
int IC, DC, ICF, IDF;

/* Parsing arrays and buffers */
char *str_array[STR_SIZE]; /* the main array to parse */
char line[LINE_SIZE], line_temp[LINE_SIZE];
char symbol[STR_SIZE], command[STR_SIZE];
char src_rst[REGISTER_NAME_SIZE], dst_rst[REGISTER_NAME_SIZE];
char label[LABEL_SIZE];
char data_string[STR_SIZE];
char *op_array[STR_SIZE]; /* array for the operands */

/* Operand and addressing */
int src_method, dst_method, operands_cnt, opnum1, opnum2;

/* Indices */
int i_command; /* current command that need to be analyzed */
int i_data;    /* the current data to parse */
int i_op;      /* number of operand to parse */
int i_word;    /* current word to parse */
int num_of_words;

/* Flags */
int symbolFLAG, dataFLAG, codeFLAG, entFLAG, extFLAG;
int first_opFLAG, second_opFLAG, stringFLAG;
int second_passFLAG, stopFLAG, errorFLAG, end_commaFLAG;

/* Linked list heads from lists.h */
ptr symbolTable_head;
memoryObj_ptr code_head;
memoryObj_ptr data_head;

/* Variables from main.h */
int i = 0;
int cnt_lines = 0;
