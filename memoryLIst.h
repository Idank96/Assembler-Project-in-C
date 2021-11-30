#define Cur_Obj temp->word_uni.bits
#define UNKNOWN_ADRESS -1
#define THREE_LEFT 3
#define NO_METHOD -2
#define WORD_SIZE 24
#define MAX_EXT 20

int mem_isEmpty(memoryObj_ptr * head,memoryObj_ptr temp);
memoryObj_ptr init_dataObj(memoryObj_ptr temp, int *DC, char *str_array[STR_SIZE]);
void init_codeObj(memoryObj_ptr temp, int *DC, char *str_array[STR_SIZE]);
void add_to_end(memoryObj_ptr * head, memoryObj_ptr temp);
int extra_word(memoryObj_ptr temp, int * IC);
void add_label_word(memoryObj_ptr temp);
void add_instanceNum_word(memoryObj_ptr temp);
void bin_word(unsigned n);
memoryObj_ptr add_string(memoryObj_ptr temp);
memoryObj_ptr add_data_numbers(memoryObj_ptr head_str);
int find_in_symbolT(memoryObj_ptr h_mem, ptr h_sym);
int isExternal(ptr h_sym);
int pAddress(int address,FILE **file);
int pHexa(int num,FILE **ob);
int ExIsRegister(char *str);
void printEachField(memoryObj_ptr head);
memoryObj_ptr create_object();
int unvalid_extra_word();
void calc_distance(memoryObj_ptr h_mem, ptr h_sym);


struct helpList{
	char name[STR_SIZE];
	int address;
}ext_help_list[MAX_EXT];
