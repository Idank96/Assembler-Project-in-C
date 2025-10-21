/**
 * @file parser.h
 * @brief Line parsing and tokenization functions
 *
 * This module handles parsing of assembly source lines,
 * tokenization, and identification of symbols, commands, and operands.
 */

#ifndef PARSER_H
#define PARSER_H

#include "assembler_context.h"

/**
 * @brief Parse a single line of assembly code
 *
 * @param ctx Assembler context
 * @param line Line to parse
 * @return TRUE if line parsed successfully, FALSE otherwise
 */
int parse_line(assembler_context_t *ctx, const char *line);

/**
 * @brief Check if line should be skipped (empty or comment)
 *
 * @param line Line to check
 * @return TRUE if line should be skipped, FALSE otherwise
 */
int should_skip_line(const char *line);

/**
 * @brief Split line into words
 *
 * @param ctx Assembler context
 * @param line Line to split
 */
void split_line(assembler_context_t *ctx, char *line);

/**
 * @brief Check if current word is a symbol definition
 *
 * @param ctx Assembler context
 * @return TRUE if symbol, ERROR if invalid, FALSE otherwise
 */
int is_symbol_definition(assembler_context_t *ctx);

/**
 * @brief Check if word is a data directive
 *
 * @param ctx Assembler context
 * @param word Word to check
 * @return TRUE if data directive, FALSE otherwise
 */
int is_data_directive(assembler_context_t *ctx, const char *word);

/**
 * @brief Check if word is a code command
 *
 * @param ctx Assembler context
 * @param word Word to check
 * @return TRUE if code command, FALSE otherwise
 */
int is_code_command(assembler_context_t *ctx, const char *word);

/**
 * @brief Check if word is .entry or .extern directive
 *
 * @param ctx Assembler context
 * @param word Word to check
 * @return TRUE if entry/extern, FALSE otherwise
 */
int is_entry_or_extern(assembler_context_t *ctx, const char *word);

/**
 * @brief Parse second pass specific items
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int parse_second_pass(assembler_context_t *ctx);

/**
 * @brief Process comma between operands
 *
 * @param ctx Assembler context
 * @param word Word to check
 * @return Number of commas deleted, ERROR on invalid comma
 */
int process_comma(assembler_context_t *ctx, char *word);

/**
 * @brief Validate label name
 *
 * @param label Label to validate
 * @return TRUE if valid, FALSE otherwise
 */
int is_valid_label(const char *label);

#endif /* PARSER_H */
