/**
 * @file assembler.h
 * @brief Main assembler interface and two-pass algorithm
 *
 * This module implements the main two-pass assembly algorithm.
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "assembler_context.h"

/**
 * @brief Assemble a single file
 *
 * Performs both passes of assembly on the given file.
 *
 * @param filename Input filename (without .as extension)
 * @param output_dir Output directory for generated files
 * @return TRUE on success, FALSE on error
 */
int assemble_file(const char *filename, const char *output_dir);

/**
 * @brief Perform first pass of assembly
 *
 * First pass:
 * - Parse each line
 * - Build symbol table
 * - Build code and data images with unknown addresses
 * - Check for syntax errors
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int first_pass(assembler_context_t *ctx);

/**
 * @brief Perform second pass of assembly
 *
 * Second pass:
 * - Resolve all symbol addresses
 * - Update memory image with actual addresses
 * - Process .entry directives
 * - Generate output files
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int second_pass(assembler_context_t *ctx);

/**
 * @brief Handle error in current line
 *
 * @param ctx Assembler context
 */
void handle_error(assembler_context_t *ctx);

/**
 * @brief Print error message
 *
 * @param ctx Assembler context
 * @param error Error code
 * @param message Additional message
 */
void print_error(const assembler_context_t *ctx, error_code_e error, const char *message);

#endif /* ASSEMBLER_H */
