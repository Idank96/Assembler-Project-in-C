#define P_All		\
					for (i=0; i < num_of_words; i++){ printf("%s ", (str_array[i])); } 					\
					puts("");																		\
					for(i=0;op_array[i];i++){ printf("op_array[%d]: %s ", i, op_array[i]); }	\
					puts("");\
					printf("symbol:%s data:%s code:%s i_command: %d i_data: %d src_rst:%s dst_rst:%s label:%s opnum1:%d opnum2:%d",symbol,data,code,i_command,i_data,src_rst,dst_rst,label,opnum1,opnum2);\
					printf("src_method:%d dst_method:%d\n\n",src_method,dst_method);

#define MEMORY_START 100
#define NO_METHOD -2
#define DEFAULT -999
int i=0;
int cnt_lines;

void first_pass();
void second_pass();
void freeAll();
void openfile();
int parseLines(char line[LINE_SIZE]);
void to_memory_image(char *str_array[STR_SIZE],memoryObj_ptr *code_head, int *DC, int *IC);
void addIC(memoryObj_ptr code_head, ptr symbol_head);
int update_memory_image();
void exe_files(char *name);
void toSymbolTable(ptr * head, char *symbol_name[STR_SIZE], int * DC, int * IC);
void printSymbolTable(ptr head);
void printDataImg(memoryObj_ptr head);
void connnectLists();
void error(int cnt_lines);
