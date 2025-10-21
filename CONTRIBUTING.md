# Contributing to the Two-Pass Assembler

Thank you for your interest in contributing to this project! This document provides guidelines for contributing to the assembler codebase.

## Code Style Guidelines

### Naming Conventions
- **Functions**: `snake_case` (e.g., `parse_line()`, `add_symbol()`)
- **Variables**: `snake_case` (e.g., `instruction_counter`, `symbol_table`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MAX_SIZE`, `DEFAULT_VALUE`)
- **Types**: `snake_case_t` suffix (e.g., `symbol_node_t`, `command_t`)
- **Macros**: `UPPER_SNAKE_CASE` (e.g., `LINE_SIZE`, `MEMORY_START`)

### File Organization
- **Headers**: Place in `include/` or `utils/` directory
- **Source**: Place in `src/` or `code/` directory
- **One module per file**: Each .c/.h pair should represent a cohesive module

### Code Formatting
```c
/* Function example */
int parse_line(assembler_context_t *ctx, const char *line) {
    int result;

    /* Check parameters */
    if (!ctx || !line) {
        return ERROR;
    }

    /* Process line */
    result = process(ctx, line);

    return result;
}
```

### Documentation
- Add function documentation for all public functions
- Use clear, descriptive comments
- Document complex algorithms
- Keep comments up-to-date with code changes

Example:
```c
/**
 * @brief Parse a single line of assembly code
 *
 * This function tokenizes the input line and identifies
 * symbols, commands, and operands.
 *
 * @param ctx Assembler context containing parsing state
 * @param line Input line to parse (null-terminated)
 * @return TRUE on success, FALSE on error
 */
int parse_line(assembler_context_t *ctx, const char *line);
```

## Compiler Flags

All code must compile without warnings or errors using:
```bash
gcc -Wall -Wextra -ansi -pedantic -g
```

### Required Compliance
- **ANSI C**: Use only ANSI C features (C89/C90)
- **No warnings**: Code must compile cleanly
- **Portable**: Avoid platform-specific code

## Testing

### Before Submitting
1. **Build**: Ensure `make clean && make` succeeds
2. **Test**: Run `make test` and verify all tests pass
3. **Memory**: Check for leaks with valgrind
   ```bash
   valgrind --leak-check=full ./assembler test_file
   ```

### Writing Tests
- Create `.as` test files in `tests/` directory
- Include both valid and invalid input cases
- Document expected behavior
- Test edge cases

## Pull Request Process

1. **Branch**: Create a feature branch
   ```bash
   git checkout -b feature/my-new-feature
   ```

2. **Commit**: Use descriptive commit messages
   ```bash
   git commit -m "Add support for new addressing mode"
   ```

3. **Test**: Verify all tests pass

4. **Document**: Update documentation if needed

5. **Submit**: Create pull request with description

### Commit Message Format
```
Short summary (50 chars or less)

Detailed explanation if needed. Wrap at 72 characters.
Explain the problem being solved and how this commit
addresses it.
```

## Adding New Features

### New Instructions
1. Add to `commands_array` in `structers.c`
2. Define opcode and function code
3. Specify valid addressing modes
4. Update documentation
5. Add test cases

### New Addressing Modes
1. Update `addressing_method_e` enum
2. Add parsing logic in appropriate module
3. Update validation functions
4. Test with all applicable instructions

### New Directives
1. Add to `g_data_directives` array
2. Implement processing logic
3. Update parser to recognize directive
4. Add tests

## Code Review Checklist

Before submitting code, verify:

- [ ] Code compiles without warnings
- [ ] No memory leaks (valgrind clean)
- [ ] Functions are documented
- [ ] Tests added for new features
- [ ] Existing tests still pass
- [ ] Error handling is robust
- [ ] Edge cases are handled
- [ ] Code follows style guidelines
- [ ] Documentation is updated

## Bug Reports

When reporting bugs, include:
- Assembler version/commit
- Input file that triggers bug
- Expected behavior
- Actual behavior
- Error messages
- System information (OS, compiler version)

## Feature Requests

For feature requests, describe:
- Use case and motivation
- Proposed behavior
- Examples of how it would work
- Any relevant assembly language precedents

## Questions

For questions about:
- **Architecture**: See `ARCHITECTURE.md`
- **Usage**: See `README.md`
- **Code**: Check inline documentation and comments

## License

By contributing, you agree that your contributions will be licensed under the same license as the project.

## Contact

For major changes, please open an issue first to discuss the proposed changes.

---

Thank you for contributing to make this assembler better!
