int skipLine(char *str);
char *getE(char *str);
void splitLine(char line[LINE_SIZE]);
int isSymbol();
int second_parse(char line[LINE_SIZE]);
int extOrEnt(char *str);
void findError(char *str);
void valid_op();
int delete_start_comma(char *str);
int get_data_param(char *str_array[STR_SIZE]);
int get_code_param(char *str_array[STR_SIZE]);
int isData(char *str);
int isCode(char *str);
int addEnt();
int CodeOrData();

#define ERROR -2
