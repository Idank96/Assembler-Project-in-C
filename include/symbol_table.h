/**
 * @file symbol_table.h
 * @brief Symbol table management functions
 *
 * This module manages the symbol table, which stores labels,
 * external symbols, and entry points.
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "assembler_context.h"

/**
 * @brief Add symbol to symbol table
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int add_symbol_to_table(assembler_context_t *ctx);

/**
 * @brief Initialize symbol node
 *
 * @param node Symbol node to initialize
 * @param ctx Assembler context
 */
void init_symbol_node(symbol_node_t *node, assembler_context_t *ctx);

/**
 * @brief Append symbol to end of symbol table
 *
 * @param head Pointer to head of symbol table
 * @param node Node to append
 */
void append_symbol(symbol_ptr_t *head, symbol_node_t *node);

/**
 * @brief Check if symbol table is empty
 *
 * @param head Pointer to head of symbol table
 * @param node Node to potentially make first node
 * @return TRUE if was empty, FALSE otherwise
 */
int is_symbol_table_empty(symbol_ptr_t *head, symbol_node_t *node);

/**
 * @brief Check for duplicate symbol
 *
 * @param head Head of symbol table
 * @param node Node to check
 * @return TRUE if duplicate found, FALSE otherwise
 */
int is_duplicate_symbol(symbol_ptr_t head, const symbol_node_t *node);

/**
 * @brief Find symbol by name
 *
 * @param head Head of symbol table
 * @param name Symbol name to find
 * @return Pointer to symbol node or NULL if not found
 */
symbol_ptr_t find_symbol(symbol_ptr_t head, const char *name);

/**
 * @brief Mark symbol as entry point
 *
 * @param ctx Assembler context
 * @param name Symbol name
 * @return TRUE on success, FALSE if symbol not found
 */
int mark_symbol_as_entry(assembler_context_t *ctx, const char *name);

/**
 * @brief Update symbol addresses by adding IC
 *
 * @param code_head Code image head
 * @param symbol_head Symbol table head
 * @param ic Instruction counter to add
 */
void update_symbol_addresses(memory_obj_ptr_t code_head, symbol_ptr_t symbol_head, int ic);

/**
 * @brief Print symbol table (debugging)
 *
 * @param head Head of symbol table
 */
void print_symbol_table(const symbol_ptr_t head);

/**
 * @brief Free symbol table
 *
 * @param head Head of symbol table
 */
void free_symbol_table(symbol_ptr_t head);

#endif /* SYMBOL_TABLE_H */
