#define NUM_OF_COMMANDS 16
#define MAX_METHOD_SIZE 4
#define OP_SIZE 5
#define NUM_OF_REGISTERS 8
#define MISS -1
typedef struct command command_s;

struct command{
	int num;
	char name[OP_SIZE];
	int opcode;
	int funct;
	int operands_num;
	int source_method[MAX_METHOD_SIZE];
	int destination_method[MAX_METHOD_SIZE];
};

extern command_s commands_array[NUM_OF_COMMANDS];


#define NUM_OF_DATAS 4
typedef struct data data_s;
struct data{
	char name[STR_SIZE];
};
extern data_s data_arr[NUM_OF_DATAS];

typedef struct registers registers_struct;

struct registers{
	char *name;
	word_union data;
};

extern registers_struct rgstrs_arr[NUM_OF_REGISTERS];

enum methods{first, second, third, fourth};


