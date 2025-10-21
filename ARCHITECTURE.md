## Assembler Architecture

### Overview
This is a professional two-pass assembler implementation in C following ANSI C standards. The architecture is modular, maintainable, and follows software engineering best practices.

### Module Structure

#### 1. **Main Module** (`main.c`)
- **Purpose**: Entry point and file processing loop
- **Responsibilities**:
  - Command-line argument parsing
  - File iteration
  - Orchestration of first and second passes
  - High-level error reporting

#### 2. **Parser Module** (`parseLines.c`)
- **Purpose**: Line-by-line parsing and tokenization
- **Responsibilities**:
  - Split lines into tokens
  - Identify symbols, commands, and operands
  - Handle comments and empty lines
  - Validate syntax
  - Manage commas between operands

**Key Functions**:
- `parseLines()` - Main parsing entry point
- `splitLine()` - Tokenize line into words
- `isSymbol()` - Check if token is symbol definition
- `isCode()` / `isData()` - Identify directive type

#### 3. **Symbol Table Module** (`symbolTable.c`)
- **Purpose**: Manage symbol table as linked list
- **Responsibilities**:
  - Add symbols with addresses
  - Check for duplicates
  - Mark entry/extern symbols
  - Update addresses in second pass

**Data Structure**:
```c
struct symbol {
    char name[STR_SIZE];
    int value;           // Address
    char type[STR_SIZE]; // "code", "data", "external", "entry"
    ptr next;
};
```

#### 4. **Memory Image Module** (`memoryList.c`)
- **Purpose**: Build and maintain code/data memory images
- **Responsibilities**:
  - Create instruction words
  - Handle extra words for operands
  - Manage data storage (.data, .string)
  - Update addresses in second pass
  - Generate output formatting

**Data Structure**:
```c
struct memoryObj {
    int address;
    char line[LINE_SIZE];     // Associated label
    word_union word_uni;      // 24-bit instruction/data
    memoryObj_ptr next;
};
```

#### 5. **Code Operations Module** (`code.c`)
- **Purpose**: Process code instructions and operands
- **Responsibilities**:
  - Parse operands (register, immediate, direct, jump)
  - Determine addressing methods
  - Validate operand types against commands
  - Set source/destination methods

**Addressing Methods**:
- **Method 0**: Immediate (`#N`)
- **Method 1**: Direct (`LABEL`)
- **Method 2**: Jump (`&LABEL`)
- **Method 3**: Register (`rN`)

#### 6. **Data Operations Module** (`data.c`)
- **Purpose**: Process data directives
- **Responsibilities**:
  - Parse `.data` numeric values
  - Parse `.string` character arrays
  - Handle signed numbers
  - Validate data format

#### 7. **File Handler Module** (`files.c`)
- **Purpose**: File I/O operations
- **Responsibilities**:
  - Open input `.as` files
  - Create output `.ob`, `.ent`, `.ext` files
  - Format hexadecimal output
  - Handle file paths

#### 8. **Structures Module** (`structers.c`)
- **Purpose**: Define global data arrays
- **Responsibilities**:
  - Define all 16 assembly commands
  - Define data directives
  - Define registers r0-r7
  - Specify valid addressing modes per command

### Data Flow

```
Input (.as file)
    ↓
[First Pass]
    ↓
Lexical Analysis (parseLines)
    ↓
Symbol Table ← Add Symbols
    ↓
Memory Image ← Add Code/Data (with unknown addresses)
    ↓
Error Check → Stop if errors
    ↓
[Second Pass]
    ↓
Resolve Addresses
    ↓
Update Memory Image
    ↓
Track External References
    ↓
[Output Generation]
    ↓
.ob (Object Code)
.ent (Entry Points)
.ext (External References)
```

### Algorithm Details

#### First Pass Algorithm
```
FOR each line in input file:
    1. Skip if comment or empty
    2. Split into tokens
    3. Check for symbol definition
    4. Identify command/directive type
    5. Parse operands
    6. Add to symbol table if needed
    7. Add to memory image with IC/DC
    8. Check for errors
    9. Increment IC or DC
```

#### Second Pass Algorithm
```
Rewind input file
FOR each line in input file:
    1. Parse line again
    2. For .entry directives: mark symbols
    3. For unknown addresses: resolve using symbol table
    4. Update E/R/A bits
    5. Track external references
Generate output files
```

### Word Format (24 bits)

```
Instruction Word:
[23-18] opcode  (6 bits)
[17-16] source_m (2 bits)
[15-13] register_s (3 bits)
[12-11] dest_m (2 bits)
[10-8]  register_d (3 bits)
[7-3]   funct (5 bits)
[2]     A (absolute)
[1]     R (relocatable)
[0]     E (external)
```

### Error Handling

The assembler detects and reports:
- Invalid label names
- Duplicate symbol definitions
- Undefined symbols
- Invalid operand types
- Incorrect addressing modes
- Missing/extra commas
- Syntax errors

Errors include line numbers for easy debugging.

### Memory Organization

```
[100...] - Code Image (IC starts at 100)
[0...]   - Data Image (DC starts at 0)
```

In second pass, Data Image addresses are adjusted by adding IC.

### Key Design Decisions

1. **Linked Lists**: Symbol table and memory images use linked lists for dynamic sizing
2. **Two-Pass**: Required for forward references (labels defined after use)
3. **Union Type**: 24-bit word accessed as integer or bitfields
4. **Global Arrays**: Commands and directives in global arrays for easy lookup
5. **Modular Design**: Each module has specific responsibility
6. **Error Recovery**: Continue checking for more errors after first error

### Extensibility

To add new instructions:
1. Add to `commands_array` in `structers.c`
2. Specify addressing modes
3. No code changes needed if modes already supported

To add new addressing modes:
1. Update `enum methods` in `structers.h`
2. Add parsing logic in `code.c`
3. Update validation functions

### Performance Characteristics

- **Time Complexity**: O(n*m) where n=lines, m=symbols (small symbol tables)
- **Space Complexity**: O(n) for linked lists
- **File I/O**: Two full reads of input file (unavoidable for two-pass)

### Testing Strategy

1. **Unit Tests**: Test individual modules
2. **Integration Tests**: Test complete assembly of sample files
3. **Error Tests**: Verify error detection and messages
4. **Edge Cases**: Empty files, maximum label length, etc.

### Code Quality Metrics

- **ANSI C Compliance**: Yes (-ansi -pedantic)
- **Warning-Free**: Yes (-Wall -Wextra -Werror)
- **Memory Leaks**: None (verified with valgrind)
- **Code Coverage**: High (all instructions tested)
- **Documentation**: Comprehensive inline and external

---

This architecture provides a solid foundation for a maintainable, extensible assembler implementation.
