
typedef struct symbol * ptr;
typedef struct symbol symbol_node;

struct symbol {
	char name[STR_SIZE];
	int value;
	char type[STR_SIZE];
    ptr next;
};

ptr symbolTable_head;

typedef struct memoryObj * memoryObj_ptr;
typedef struct memoryObj memoryObj_node;

struct memoryObj{
	int address;
	char line[LINE_SIZE];
	word_union word_uni;
    memoryObj_ptr next;
};

memoryObj_ptr code_head; 
memoryObj_ptr data_head; 
