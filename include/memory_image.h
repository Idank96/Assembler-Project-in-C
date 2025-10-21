/**
 * @file memory_image.h
 * @brief Memory image management for code and data segments
 *
 * This module manages the memory image linked lists for both
 * code and data segments of the assembled program.
 */

#ifndef MEMORY_IMAGE_H
#define MEMORY_IMAGE_H

#include "assembler_context.h"

/**
 * @brief Add instruction/data to memory image
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int add_to_memory_image(assembler_context_t *ctx);

/**
 * @brief Initialize code object word
 *
 * @param node Memory object node
 * @param ctx Assembler context
 */
void init_code_object(memory_obj_node_t *node, assembler_context_t *ctx);

/**
 * @brief Initialize data object word
 *
 * @param node Memory object node
 * @param ctx Assembler context
 * @return Pointer to created data chain
 */
memory_obj_ptr_t init_data_object(memory_obj_node_t *node, assembler_context_t *ctx);

/**
 * @brief Create memory object node
 *
 * @return Pointer to new node or NULL on error
 */
memory_obj_ptr_t create_memory_object(void);

/**
 * @brief Append memory object to end of list
 *
 * @param head Pointer to head of memory image
 * @param node Node to append
 */
void append_memory_object(memory_obj_ptr_t *head, memory_obj_ptr_t node);

/**
 * @brief Check if memory image is empty
 *
 * @param head Pointer to head of memory image
 * @param node Node to potentially make first node
 * @return TRUE if was empty, FALSE otherwise
 */
int is_memory_image_empty(memory_obj_ptr_t *head, memory_obj_ptr_t node);

/**
 * @brief Add extra word for operand
 *
 * @param node Current node
 * @param ctx Assembler context
 * @return TRUE if extra word added, FALSE otherwise
 */
int add_extra_word(memory_obj_ptr_t node, assembler_context_t *ctx);

/**
 * @brief Add label word (unknown address initially)
 *
 * @param node Memory object node
 * @param label Label name
 */
void add_label_word(memory_obj_ptr_t node, const char *label);

/**
 * @brief Add immediate number word
 *
 * @param node Memory object node
 * @param value Immediate value
 */
void add_immediate_word(memory_obj_ptr_t node, int value);

/**
 * @brief Add data numbers to memory
 *
 * @param ctx Assembler context
 * @return Pointer to data chain head
 */
memory_obj_ptr_t add_data_numbers(assembler_context_t *ctx);

/**
 * @brief Add string data to memory
 *
 * @param ctx Assembler context
 * @param str String to add
 * @return Pointer to data chain head
 */
memory_obj_ptr_t add_string_data(assembler_context_t *ctx, const char *str);

/**
 * @brief Update memory image addresses in second pass
 *
 * @param ctx Assembler context
 * @return TRUE on success, FALSE on error
 */
int update_memory_addresses(assembler_context_t *ctx);

/**
 * @brief Connect code and data image lists
 *
 * @param code_head Code image head
 * @param data_head Data image head
 */
void connect_memory_images(memory_obj_ptr_t code_head, memory_obj_ptr_t data_head);

/**
 * @brief Calculate distance for jump instruction
 *
 * @param node Memory object node
 * @param symbol_value Target symbol value
 */
void calculate_jump_distance(memory_obj_ptr_t node, int symbol_value);

/**
 * @brief Check if symbol is external
 *
 * @param symbol Symbol node
 * @return TRUE if external, FALSE otherwise
 */
int is_external_symbol(const symbol_node_t *symbol);

/**
 * @brief Print memory image (debugging)
 *
 * @param head Head of memory image
 */
void print_memory_image(const memory_obj_ptr_t head);

/**
 * @brief Free memory image
 *
 * @param head Head of memory image
 */
void free_memory_image(memory_obj_ptr_t head);

#endif /* MEMORY_IMAGE_H */
