/**
 * @file assembler_context.h
 * @brief Assembler context structure and state management
 *
 * This file defines the main assembler context structure that encapsulates
 * all state needed during assembly, eliminating the need for global variables.
 */

#ifndef ASSEMBLER_CONTEXT_H
#define ASSEMBLER_CONTEXT_H

#include "assembler_types.h"

/**
 * @brief Main assembler context structure
 *
 * This structure contains all state information for the assembler,
 * including symbol tables, memory images, and parsing state.
 */
typedef struct {
    /* File handling */
    FILE *input_file;
    char filename[STR_SIZE];
    char output_dir[STR_SIZE];

    /* Memory images */
    symbol_ptr_t symbol_table_head;
    memory_obj_ptr_t code_image_head;
    memory_obj_ptr_t data_image_head;

    /* Counters */
    int instruction_counter;      /* IC - instruction counter */
    int data_counter;             /* DC - data counter */
    int instruction_counter_final;/* ICF - final IC */
    int data_counter_final;       /* IDF - final DC */
    int line_number;              /* Current line being processed */

    /* Current line parsing state */
    char current_line[LINE_SIZE];
    char temp_line[LINE_SIZE];
    char *parsed_words[STR_SIZE];      /* Array of parsed words */
    char *operands[STR_SIZE];          /* Array of operands */
    int num_words;
    int current_word_index;
    int operand_index;
    int operand_count;

    /* Current symbol/command state */
    char symbol[STR_SIZE];
    char command[STR_SIZE];
    char source_register[REGISTER_NAME_SIZE];
    char dest_register[REGISTER_NAME_SIZE];
    char label[LABEL_SIZE];

    /* Addressing methods */
    int source_method;
    int dest_method;
    int operand_num1;
    int operand_num2;

    /* Current command/data index */
    int current_command_index;
    int current_data_index;

    /* Flags */
    int has_symbol;
    int is_data;
    int is_code;
    int is_entry;
    int is_extern;
    int first_operand_found;
    int second_operand_found;
    int is_string;
    int second_pass_active;
    int stop_flag;            /* Stop processing due to errors */
    int error_flag;           /* Error in current line */
    int end_comma_flag;

    /* External references */
    ext_reference_t ext_references[STR_SIZE];
    int ext_ref_count;

    /* Error tracking */
    error_code_e last_error;
    char error_message[LINE_SIZE];

} assembler_context_t;

/**
 * @brief Initialize assembler context
 *
 * @param ctx Pointer to assembler context
 */
void assembler_context_init(assembler_context_t *ctx);

/**
 * @brief Free all resources in assembler context
 *
 * @param ctx Pointer to assembler context
 */
void assembler_context_cleanup(assembler_context_t *ctx);

/**
 * @brief Reset parsing state for new line
 *
 * @param ctx Pointer to assembler context
 */
void assembler_context_reset_line(assembler_context_t *ctx);

/**
 * @brief Set error in context
 *
 * @param ctx Pointer to assembler context
 * @param error Error code
 * @param message Error message
 */
void assembler_context_set_error(assembler_context_t *ctx, error_code_e error, const char *message);

#endif /* ASSEMBLER_CONTEXT_H */
