###############################################################################
# Professional Makefile for Two-Pass Assembler
# Improved organization and modern build system
###############################################################################

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -g -O2
LDFLAGS =

# Directories
CODE_DIR = code
UTILS_DIR = utils
OBJ_DIR = object_files
BIN_DIR = .

# Target executable
TARGET = $(BIN_DIR)/assembler

# Source files
SRCS = $(CODE_DIR)/main.c \
       $(CODE_DIR)/global.c \
       $(CODE_DIR)/symbolTable.c \
       $(CODE_DIR)/parseLines.c \
       $(CODE_DIR)/memoryList.c \
       $(CODE_DIR)/code.c \
       $(CODE_DIR)/data.c \
       $(CODE_DIR)/structers.c \
       $(CODE_DIR)/files.c

# Object files
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/global.o \
       $(OBJ_DIR)/symbolTable.o \
       $(OBJ_DIR)/parseLines.o \
       $(OBJ_DIR)/memoryList.o \
       $(OBJ_DIR)/code.o \
       $(OBJ_DIR)/data.o \
       $(OBJ_DIR)/structers.o \
       $(OBJ_DIR)/files.o

# Header dependencies
HEADERS = $(UTILS_DIR)/global.h \
          $(UTILS_DIR)/lists.h \
          $(UTILS_DIR)/main.h \
          $(UTILS_DIR)/symbolTable.h \
          $(UTILS_DIR)/parseLines.h \
          $(UTILS_DIR)/memoryLIst.h \
          $(UTILS_DIR)/code.h \
          $(UTILS_DIR)/data.h \
          $(UTILS_DIR)/structers.h \
          $(UTILS_DIR)/files.h

# Include path
INCLUDES = -I$(UTILS_DIR)

# Colors for prettier output
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m # No Color

###############################################################################
# Phony targets
###############################################################################
.PHONY: all clean rebuild help info test

###############################################################################
# Build rules
###############################################################################

# Default target
all: banner $(TARGET) success

banner:
	@echo "$(BLUE)=================================================$(NC)"
	@echo "$(BLUE)  Building Two-Pass Assembler$(NC)"
	@echo "$(BLUE)=================================================$(NC)"

success:
	@echo "$(GREEN)=================================================$(NC)"
	@echo "$(GREEN)  Build Complete!$(NC)"
	@echo "$(GREEN)  Executable: $(TARGET)$(NC)"
	@echo "$(GREEN)=================================================$(NC)"

# Link
$(TARGET): $(OBJS)
	@echo "$(YELLOW)Linking $@...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compile individual object files
$(OBJ_DIR)/main.o: $(CODE_DIR)/main.c $(UTILS_DIR)/global.h $(UTILS_DIR)/lists.h $(UTILS_DIR)/main.h
	@echo "$(BLUE)Compiling main.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/global.o: $(CODE_DIR)/global.c $(UTILS_DIR)/global.h
	@echo "$(BLUE)Compiling global.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/symbolTable.o: $(CODE_DIR)/symbolTable.c $(UTILS_DIR)/global.h $(UTILS_DIR)/lists.h $(UTILS_DIR)/symbolTable.h
	@echo "$(BLUE)Compiling symbolTable.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/parseLines.o: $(CODE_DIR)/parseLines.c $(UTILS_DIR)/global.h $(UTILS_DIR)/parseLines.h $(UTILS_DIR)/structers.h
	@echo "$(BLUE)Compiling parseLines.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/memoryList.o: $(CODE_DIR)/memoryList.c $(UTILS_DIR)/global.h $(UTILS_DIR)/lists.h $(UTILS_DIR)/memoryLIst.h $(UTILS_DIR)/structers.h
	@echo "$(BLUE)Compiling memoryList.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/code.o: $(CODE_DIR)/code.c $(UTILS_DIR)/global.h $(UTILS_DIR)/code.h $(UTILS_DIR)/structers.h
	@echo "$(BLUE)Compiling code.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/data.o: $(CODE_DIR)/data.c $(UTILS_DIR)/global.h $(UTILS_DIR)/data.h $(UTILS_DIR)/structers.h
	@echo "$(BLUE)Compiling data.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/structers.o: $(CODE_DIR)/structers.c $(UTILS_DIR)/global.h $(UTILS_DIR)/structers.h
	@echo "$(BLUE)Compiling structers.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/files.o: $(CODE_DIR)/files.c $(UTILS_DIR)/global.h $(UTILS_DIR)/files.h
	@echo "$(BLUE)Compiling files.c...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

###############################################################################
# Utility targets
###############################################################################

# Clean build artifacts
clean:
	@echo "$(YELLOW)Cleaning build artifacts...$(NC)"
	@rm -f $(OBJS) $(TARGET)
	@rm -f tests/*.ob tests/*.ent tests/*.ext
	@echo "$(GREEN)Clean complete!$(NC)"

# Rebuild from scratch
rebuild: clean all

# Show build information
info:
	@echo "$(BLUE)=================================================$(NC)"
	@echo "$(BLUE)  Build Configuration$(NC)"
	@echo "$(BLUE)=================================================$(NC)"
	@echo "Compiler:      $(CC)"
	@echo "Flags:         $(CFLAGS)"
	@echo "Target:        $(TARGET)"
	@echo "Source Dir:    $(CODE_DIR)"
	@echo "Header Dir:    $(UTILS_DIR)"
	@echo "Object Dir:    $(OBJ_DIR)"
	@echo "$(BLUE)=================================================$(NC)"

# Run a test build
test: all
	@echo "$(BLUE)Running assembler test...$(NC)"
	@if [ -d tests ] && [ -n "$$(ls -A tests/*.as 2>/dev/null)" ]; then \
		for f in tests/*.as; do \
			base=$$(basename $$f .as); \
			echo "$(YELLOW)Assembling: $$base$(NC)"; \
			./$(TARGET) $$base || true; \
		done; \
		echo "$(GREEN)Test complete!$(NC)"; \
	else \
		echo "$(YELLOW)No test files found in tests/ directory$(NC)"; \
	fi

# Display help
help:
	@echo "$(BLUE)Available targets:$(NC)"
	@echo "  $(GREEN)all$(NC)      - Build the assembler (default)"
	@echo "  $(GREEN)clean$(NC)    - Remove build artifacts"
	@echo "  $(GREEN)rebuild$(NC)  - Clean and build from scratch"
	@echo "  $(GREEN)test$(NC)     - Run assembler on test files"
	@echo "  $(GREEN)info$(NC)     - Display build configuration"
	@echo "  $(GREEN)help$(NC)     - Display this help message"
	@echo ""
	@echo "$(BLUE)Usage:$(NC)"
	@echo "  make          # Build the assembler"
	@echo "  make clean    # Clean up"
	@echo "  make test     # Run tests"
