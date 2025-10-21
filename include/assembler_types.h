/**
 * @file assembler_types.h
 * @brief Core type definitions and constants for the two-pass assembler
 *
 * This file contains all fundamental types, constants, and enumerations
 * used throughout the assembler project.
 */

#ifndef ASSEMBLER_TYPES_H
#define ASSEMBLER_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ========== Constants ========== */

#define STR_SIZE 32
#define LABEL_SIZE 31
#define LINE_SIZE 80
#define WORD_SIZE 24
#define MEMORY_START 100
#define REGISTERS_NUM 8
#define REGISTER_NAME_SIZE 2
#define DATA_TYPES_NUM 4
#define CODE_TYPES_NUM 16
#define NUM_OF_COMMANDS 16
#define MAX_METHOD_SIZE 4
#define OP_SIZE 5
#define NUM_OF_REGISTERS 8
#define THREE_LEFT 2
#define UNKNOWN_ADRESS -1
#define NUM_OF_METHODS 4

/* Boolean values */
#define FALSE 0
#define TRUE 1
#define ERROR -1
#define MISS -1

/* Default values */
#define NO_METHOD -2
#define DEFAULT -999

/* ========== Enumerations ========== */

/**
 * @brief Addressing methods for operands
 */
typedef enum {
    METHOD_IMMEDIATE = 0,    /* #number */
    METHOD_DIRECT = 1,       /* label */
    METHOD_JUMP = 2,         /* &label */
    METHOD_REGISTER = 3      /* register */
} addressing_method_e;

/**
 * @brief Error codes returned by assembler functions
 */
typedef enum {
    ERROR_NONE = 0,
    ERROR_MEMORY_ALLOC,
    ERROR_FILE_OPEN,
    ERROR_INVALID_LABEL,
    ERROR_DUPLICATE_SYMBOL,
    ERROR_INVALID_OPERAND,
    ERROR_INVALID_COMMAND,
    ERROR_MISSING_COMMA,
    ERROR_EXTRA_COMMA,
    ERROR_LABEL_TOO_LONG,
    ERROR_ENTRY_NOT_FOUND,
    ERROR_MISSING_QUOTE,
    ERROR_OPERANDS_MISSING,
    ERROR_TOO_MANY_OPERANDS,
    ERROR_INVALID_ADDRESSING
} error_code_e;

/* ========== Type Definitions ========== */

/**
 * @brief 24-bit word union for machine code representation
 *
 * This union allows accessing the word as either a raw index
 * or as individual bit fields representing instruction components.
 */
typedef union {
    unsigned int index;
    struct {
        unsigned int E:1;             /* External bit */
        unsigned int R:1;             /* Relocatable bit */
        unsigned int A:1;             /* Absolute bit */
        unsigned int funct:5;         /* Function code */
        unsigned int register_d:3;    /* Destination register */
        unsigned int destination_m:2; /* Destination method */
        unsigned int register_s:3;    /* Source register */
        unsigned int source_m:2;      /* Source method */
        unsigned int opcode:6;        /* Operation code */
    } bits;
} word_union_t;

/**
 * @brief Symbol table node structure
 */
typedef struct symbol_node {
    char name[STR_SIZE];          /* Symbol name */
    int value;                     /* Symbol address/value */
    char type[STR_SIZE];          /* Symbol type (code/data/external/entry) */
    struct symbol_node *next;     /* Next node in linked list */
} symbol_node_t;

typedef symbol_node_t* symbol_ptr_t;

/**
 * @brief Memory object node for code/data image
 */
typedef struct memory_obj_node {
    int address;                       /* Memory address */
    char line[LINE_SIZE];             /* Associated label/line */
    word_union_t word_uni;            /* The 24-bit word */
    struct memory_obj_node *next;     /* Next node in linked list */
} memory_obj_node_t;

typedef memory_obj_node_t* memory_obj_ptr_t;

/**
 * @brief Command structure defining assembly instruction
 */
typedef struct {
    int num;                                    /* Command number */
    char name[OP_SIZE];                        /* Command mnemonic */
    int opcode;                                /* Operation code */
    int funct;                                 /* Function code */
    int operands_num;                          /* Number of operands */
    int source_method[MAX_METHOD_SIZE];        /* Valid source methods */
    int destination_method[MAX_METHOD_SIZE];   /* Valid destination methods */
} command_t;

/**
 * @brief Data directive structure
 */
typedef struct {
    char name[STR_SIZE];    /* Directive name (.data, .string, etc.) */
} data_directive_t;

/**
 * @brief Register structure
 */
typedef struct {
    char *name;             /* Register name */
    word_union_t data;      /* Register data */
} register_t;

/**
 * @brief External reference helper structure
 */
typedef struct {
    char name[STR_SIZE];    /* Symbol name */
    int address;            /* Address where used */
} ext_reference_t;

/* ========== Global Data Arrays ========== */

extern command_t g_commands_array[NUM_OF_COMMANDS];
extern data_directive_t g_data_directives[DATA_TYPES_NUM];
extern register_t g_registers[NUM_OF_REGISTERS];

#endif /* ASSEMBLER_TYPES_H */
