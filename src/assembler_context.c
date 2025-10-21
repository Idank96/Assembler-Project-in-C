/**
 * @file assembler_context.c
 * @brief Implementation of assembler context management functions
 */

#include "assembler_context.h"
#include <string.h>

/**
 * @brief Initialize assembler context to default values
 */
void assembler_context_init(assembler_context_t *ctx) {
    int i;

    /* File handling */
    ctx->input_file = NULL;
    memset(ctx->filename, 0, STR_SIZE);
    strcpy(ctx->output_dir, "./");

    /* Memory images */
    ctx->symbol_table_head = NULL;
    ctx->code_image_head = NULL;
    ctx->data_image_head = NULL;

    /* Counters */
    ctx->instruction_counter = MEMORY_START;
    ctx->data_counter = 0;
    ctx->instruction_counter_final = 0;
    ctx->data_counter_final = 0;
    ctx->line_number = 0;

    /* Current line state */
    memset(ctx->current_line, 0, LINE_SIZE);
    memset(ctx->temp_line, 0, LINE_SIZE);
    ctx->num_words = 0;
    ctx->current_word_index = 0;
    ctx->operand_index = 0;
    ctx->operand_count = 0;

    /* Initialize parsed words array */
    for (i = 0; i < STR_SIZE; i++) {
        ctx->parsed_words[i] = NULL;
        ctx->operands[i] = NULL;
    }

    /* Current symbol/command state */
    memset(ctx->symbol, 0, STR_SIZE);
    memset(ctx->command, 0, STR_SIZE);
    memset(ctx->source_register, 0, REGISTER_NAME_SIZE);
    memset(ctx->dest_register, 0, REGISTER_NAME_SIZE);
    memset(ctx->label, 0, LABEL_SIZE);

    /* Addressing methods */
    ctx->source_method = NO_METHOD;
    ctx->dest_method = NO_METHOD;
    ctx->operand_num1 = DEFAULT;
    ctx->operand_num2 = DEFAULT;

    /* Current indices */
    ctx->current_command_index = 0;
    ctx->current_data_index = 0;

    /* Flags */
    ctx->has_symbol = FALSE;
    ctx->is_data = FALSE;
    ctx->is_code = FALSE;
    ctx->is_entry = FALSE;
    ctx->is_extern = FALSE;
    ctx->first_operand_found = FALSE;
    ctx->second_operand_found = FALSE;
    ctx->is_string = FALSE;
    ctx->second_pass_active = FALSE;
    ctx->stop_flag = FALSE;
    ctx->error_flag = FALSE;
    ctx->end_comma_flag = FALSE;

    /* External references */
    memset(ctx->ext_references, 0, sizeof(ext_reference_t) * STR_SIZE);
    ctx->ext_ref_count = 0;

    /* Error tracking */
    ctx->last_error = ERROR_NONE;
    memset(ctx->error_message, 0, LINE_SIZE);
}

/**
 * @brief Free all resources in assembler context
 */
void assembler_context_cleanup(assembler_context_t *ctx) {
    int i;

    /* Close file if open */
    if (ctx->input_file) {
        fclose(ctx->input_file);
        ctx->input_file = NULL;
    }

    /* Free parsed words */
    for (i = 0; i < STR_SIZE; i++) {
        if (ctx->parsed_words[i]) {
            free(ctx->parsed_words[i]);
            ctx->parsed_words[i] = NULL;
        }
        if (ctx->operands[i]) {
            free(ctx->operands[i]);
            ctx->operands[i] = NULL;
        }
    }

    /* Free symbol table */
    while (ctx->symbol_table_head) {
        symbol_ptr_t temp = ctx->symbol_table_head;
        ctx->symbol_table_head = ctx->symbol_table_head->next;
        free(temp);
    }

    /* Free memory images */
    while (ctx->code_image_head) {
        memory_obj_ptr_t temp = ctx->code_image_head;
        ctx->code_image_head = ctx->code_image_head->next;
        free(temp);
    }

    while (ctx->data_image_head) {
        memory_obj_ptr_t temp = ctx->data_image_head;
        ctx->data_image_head = ctx->data_image_head->next;
        free(temp);
    }
}

/**
 * @brief Reset parsing state for new line
 */
void assembler_context_reset_line(assembler_context_t *ctx) {
    int i;

    /* Free previous parsed words */
    for (i = 0; i < ctx->num_words && i < STR_SIZE; i++) {
        if (ctx->parsed_words[i]) {
            free(ctx->parsed_words[i]);
            ctx->parsed_words[i] = NULL;
        }
    }

    /* Free previous operands (but keep the array) */
    for (i = 0; i < ctx->operand_index && i < STR_SIZE; i++) {
        if (ctx->operands[i]) {
            /* Don't free - operands might point to parsed_words */
            ctx->operands[i] = NULL;
        }
    }

    /* Reset indices and counts */
    ctx->num_words = 0;
    ctx->current_word_index = 0;
    ctx->operand_index = 0;
    ctx->operand_count = 0;

    /* Reset current symbol/command state */
    memset(ctx->symbol, 0, STR_SIZE);
    memset(ctx->command, 0, STR_SIZE);
    memset(ctx->source_register, 0, REGISTER_NAME_SIZE);
    memset(ctx->dest_register, 0, REGISTER_NAME_SIZE);
    memset(ctx->label, 0, LABEL_SIZE);

    /* Reset addressing methods */
    ctx->source_method = NO_METHOD;
    ctx->dest_method = NO_METHOD;
    ctx->operand_num1 = DEFAULT;
    ctx->operand_num2 = DEFAULT;

    /* Reset flags */
    ctx->has_symbol = FALSE;
    ctx->is_data = FALSE;
    ctx->is_code = FALSE;
    ctx->is_entry = FALSE;
    ctx->is_extern = FALSE;
    ctx->first_operand_found = FALSE;
    ctx->second_operand_found = FALSE;
    ctx->is_string = FALSE;
    ctx->end_comma_flag = FALSE;
    ctx->error_flag = FALSE;

    /* Don't reset error message yet - might need it for reporting */
}

/**
 * @brief Set error in context
 */
void assembler_context_set_error(assembler_context_t *ctx, error_code_e error, const char *message) {
    ctx->error_flag = TRUE;
    ctx->last_error = error;
    if (message) {
        strncpy(ctx->error_message, message, LINE_SIZE - 1);
        ctx->error_message[LINE_SIZE - 1] = '\0';
    }
}
