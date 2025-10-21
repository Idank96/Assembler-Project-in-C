/**
 * @file file_handler.h
 * @brief File I/O operations for assembler
 *
 * This module handles opening input files and creating output files
 * (.ob, .ent, .ext) with proper formatting.
 */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "assembler_context.h"

/**
 * @brief Open input assembly file
 *
 * @param ctx Assembler context
 * @param filename Filename (without .as extension)
 * @return TRUE on success, FALSE on error
 */
int open_input_file(assembler_context_t *ctx, const char *filename);

/**
 * @brief Close input file
 *
 * @param ctx Assembler context
 */
void close_input_file(assembler_context_t *ctx);

/**
 * @brief Create all output files (.ob, .ent, .ext)
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int create_output_files(assembler_context_t *ctx);

/**
 * @brief Create object file (.ob)
 *
 * @param ctx Assembler context
 * @param file Output file pointer
 */
void create_object_file(assembler_context_t *ctx, FILE *file);

/**
 * @brief Create entry file (.ent)
 *
 * @param ctx Assembler context
 * @param file Output file pointer
 */
void create_entry_file(assembler_context_t *ctx, FILE *file);

/**
 * @brief Create extern file (.ext)
 *
 * @param ctx Assembler context
 * @param file Output file pointer
 */
void create_extern_file(assembler_context_t *ctx, FILE *file);

/**
 * @brief Write memory image to file
 *
 * @param head Memory image head
 * @param file Output file
 */
void write_memory_to_file(memory_obj_ptr_t head, FILE *file);

/**
 * @brief Write entry symbols to file
 *
 * @param head Symbol table head
 * @param file Output file
 */
void write_entries_to_file(symbol_ptr_t head, FILE *file);

/**
 * @brief Write external references to file
 *
 * @param ext_refs External references array
 * @param count Number of references
 * @param file Output file
 */
void write_externals_to_file(ext_reference_t *ext_refs, int count, FILE *file);

/**
 * @brief Print word in hexadecimal format
 *
 * @param value Word value
 * @param file Output file
 */
void print_hex_word(int value, FILE *file);

/**
 * @brief Print address with leading zeros
 *
 * @param address Address value
 * @param file Output file
 */
void print_address(int address, FILE *file);

#endif /* FILE_HANDLER_H */
