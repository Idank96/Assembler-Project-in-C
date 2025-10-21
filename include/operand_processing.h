/**
 * @file operand_processing.h
 * @brief Operand parsing and validation
 *
 * This module handles parsing of different operand types
 * (immediate, direct, jump, register) and validates addressing modes.
 */

#ifndef OPERAND_PROCESSING_H
#define OPERAND_PROCESSING_H

#include "assembler_context.h"

/**
 * @brief Process code command operands
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int process_code_operands(assembler_context_t *ctx);

/**
 * @brief Process data directive operands
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int process_data_operands(assembler_context_t *ctx);

/**
 * @brief Check if operand is a register
 *
 * @param ctx Assembler context
 * @param operand Operand string
 * @return TRUE if register, FALSE otherwise
 */
int is_register_operand(assembler_context_t *ctx, const char *operand);

/**
 * @brief Check if operand is a label
 *
 * @param ctx Assembler context
 * @param operand Operand string
 * @return TRUE if label, FALSE otherwise
 */
int is_label_operand(assembler_context_t *ctx, const char *operand);

/**
 * @brief Check if operand is immediate number
 *
 * @param ctx Assembler context
 * @param operand Operand string
 * @return TRUE if immediate, FALSE otherwise
 */
int is_immediate_operand(assembler_context_t *ctx, const char *operand);

/**
 * @brief Check if operand is jump operand (&label)
 *
 * @param ctx Assembler context
 * @param operand Operand string
 * @return TRUE if jump operand, FALSE otherwise
 */
int is_jump_operand(assembler_context_t *ctx, const char *operand);

/**
 * @brief Process string data
 *
 * @param ctx Assembler context
 * @param str String with quotes
 * @return TRUE on success, FALSE on error
 */
int process_string_data(assembler_context_t *ctx, const char *str);

/**
 * @brief Process numeric data
 *
 * @param ctx Assembler context
 * @param str Number string
 * @return TRUE on success, FALSE on error
 */
int process_numeric_data(assembler_context_t *ctx, const char *str);

/**
 * @brief Validate source addressing method
 *
 * @param ctx Assembler context
 * @return TRUE if valid, FALSE otherwise
 */
int validate_source_addressing(assembler_context_t *ctx);

/**
 * @brief Validate destination addressing method
 *
 * @param ctx Assembler context
 * @return TRUE if valid, FALSE otherwise
 */
int validate_dest_addressing(assembler_context_t *ctx);

/**
 * @brief Check if operand needs extra word
 *
 * @param ctx Assembler context
 * @param operand_index Index of operand
 * @return TRUE if extra word needed, FALSE otherwise
 */
int needs_extra_word(assembler_context_t *ctx, int operand_index);

#endif /* OPERAND_PROCESSING_H */
