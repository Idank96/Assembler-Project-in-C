/**
 * @file assembler_types.c
 * @brief Implementation of global data arrays for assembler
 */

#include "assembler_types.h"

/**
 * @brief Array of all supported assembly commands
 *
 * Each command specifies its opcode, function code, number of operands,
 * and valid addressing methods for source and destination operands.
 */
command_t g_commands_array[NUM_OF_COMMANDS] = {
    /* num, name,   opcode, funct, ops, source_methods,                  dest_methods */
    {0,  "mov",  0,  0,  2,  {METHOD_IMMEDIATE, METHOD_DIRECT, METHOD_REGISTER, MISS}, {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {1,  "cmp",  1,  0,  2,  {METHOD_IMMEDIATE, METHOD_DIRECT, METHOD_REGISTER, MISS}, {METHOD_IMMEDIATE, METHOD_DIRECT, METHOD_REGISTER, MISS}},
    {2,  "add",  2,  1,  2,  {METHOD_IMMEDIATE, METHOD_DIRECT, METHOD_REGISTER, MISS}, {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {3,  "sub",  2,  2,  2,  {METHOD_IMMEDIATE, METHOD_DIRECT, METHOD_REGISTER, MISS}, {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {4,  "lea",  4,  0,  2,  {METHOD_DIRECT, MISS, MISS, MISS},                        {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {5,  "clr",  5,  1,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {6,  "not",  5,  2,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {7,  "inc",  5,  3,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {8,  "dec",  5,  4,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {9,  "jmp",  9,  1,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_JUMP, MISS, MISS}},
    {10, "bne",  9,  2,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_JUMP, MISS, MISS}},
    {11, "jsr",  9,  3,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_JUMP, MISS, MISS}},
    {12, "red",  12, 0,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_DIRECT, METHOD_REGISTER, MISS, MISS}},
    {13, "prn",  13, 0,  1,  {MISS, MISS, MISS, MISS},                                 {METHOD_IMMEDIATE, METHOD_DIRECT, METHOD_REGISTER, MISS}},
    {14, "rts",  14, 0,  0,  {MISS, MISS, MISS, MISS},                                 {MISS, MISS, MISS, MISS}},
    {15, "stop", 15, 0,  0,  {MISS, MISS, MISS, MISS},                                 {MISS, MISS, MISS, MISS}}
};

/**
 * @brief Array of data directives
 */
data_directive_t g_data_directives[DATA_TYPES_NUM] = {
    {".data"},
    {".string"},
    {".entry"},
    {".extern"}
};

/**
 * @brief Array of available registers
 */
register_t g_registers[NUM_OF_REGISTERS] = {
    {"r0"}, {"r1"}, {"r2"}, {"r3"},
    {"r4"}, {"r5"}, {"r6"}, {"r7"}
};
