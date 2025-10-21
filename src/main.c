/**
 * @file main.c
 * @brief Main entry point for the two-pass assembler
 *
 * This is a professional two-pass assembler for a custom assembly language.
 * It processes assembly source files and generates object, entry, and extern files.
 *
 * @author Refactored for professional C coding standards
 * @date 2025
 */

#include "assembler.h"
#include "assembler_context.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_OUTPUT_DIR "./tests/"

/**
 * @brief Main program entry point
 *
 * @param argc Argument count
 * @param argv Argument vector (filenames without .as extension)
 * @return 0 on success, 1 on error
 */
int main(int argc, char *argv[]) {
    int i;
    int success_count = 0;
    int error_count = 0;

    /* Check for input files */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        fprintf(stderr, "Note: Do not include the .as extension\n");
        return 1;
    }

    printf("=================================================\n");
    printf("  Two-Pass Assembler - Professional Edition\n");
    printf("=================================================\n\n");

    /* Process each input file */
    for (i = 1; i < argc; i++) {
        printf("Processing file: %s.as\n", argv[i]);
        printf("-------------------------------------------------\n");

        if (assemble_file(argv[i], DEFAULT_OUTPUT_DIR)) {
            printf("SUCCESS: %s.as assembled successfully\n\n", argv[i]);
            success_count++;
        } else {
            printf("ERROR: Failed to assemble %s.as\n\n", argv[i]);
            error_count++;
        }
    }

    /* Print summary */
    printf("=================================================\n");
    printf("  Assembly Summary\n");
    printf("=================================================\n");
    printf("Total files processed: %d\n", argc - 1);
    printf("Successful: %d\n", success_count);
    printf("Failed: %d\n", error_count);
    printf("=================================================\n");

    return (error_count > 0) ? 1 : 0;
}
