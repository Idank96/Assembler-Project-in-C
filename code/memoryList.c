#include "global.h"
#include "lists.h"
#include "structers.h"
#include "memoryList.h"

/*
	- this file manage the memory-image\linked-list. 	
	- all the functions of the memory-image are here.
*/


int i_temp;  /*used to loop on the operan_array*/
int count_extra_words;

/* init data or code and add it to memory-image(linked list) */
void to_memory_image(char *str_array[STR_SIZE], memoryObj_ptr *code_head, int *DC, int *IC)
{
	int n_of_op;
	memoryObj_ptr temp = create_object();
	count_extra_words=i_temp=0;

	if(dataFLAG)
	{
		temp = init_dataObj(temp,DC,str_array);	
		if(!(mem_isEmpty(&data_head,temp)))
			add_to_end(&data_head,temp);
	}
	else if(codeFLAG)
	{
		init_codeObj(temp,IC,str_array);

		if(!(mem_isEmpty(code_head,temp)))
			add_to_end(code_head,temp);

		for(n_of_op=i_op ; n_of_op>0 ; n_of_op--){
			if(extra_word(temp,IC))
				temp=temp->next;
		}	
	}	
	count_extra_words=i_temp=0;
	return;
}
/*
	- initialize the first word of the command (the extra word is seperate) 
	- Cur_Obj is a macro( 'temp->word_uni.bits')
*/
void init_codeObj(memoryObj_ptr temp, int * IC, char *str_array[STR_SIZE])
{		
	temp->address = *IC;
	(*IC)++;
	Cur_Obj.opcode=commands_array[i_command].opcode;
	(src_method==NO_METHOD)? (Cur_Obj.source_m=0):(Cur_Obj.source_m=src_method);
	(dst_method==NO_METHOD)? (Cur_Obj.destination_m=0):(Cur_Obj.destination_m=dst_method);
	Cur_Obj.register_s=atoi(src_rst);
	Cur_Obj.register_d=atoi(dst_rst);
	Cur_Obj.funct=commands_array[i_command].funct;
	Cur_Obj.A=1;
	Cur_Obj.R=0;
	Cur_Obj.E=0;
	return;
}
/*call to add_string() or add_data_numbers() to initialize the data-words*/
memoryObj_ptr init_dataObj(memoryObj_ptr temp, int * DC, char *str_array[STR_SIZE])
{			
	if(stringFLAG){
		temp = add_string(temp);	
		stringFLAG=FALSE;	
	}
	else
		temp = add_data_numbers(temp);	

	return temp;
}
/*return TRUE if the memory image is empty and init the first node in the linked list*/
int mem_isEmpty(memoryObj_ptr * head, memoryObj_ptr temp)
{
	if(!(*head))
	{
		if(codeFLAG){
			temp->next=NULL;
			*head=temp;
			return TRUE;	
		}			
		else{
			*head=temp;
			return TRUE;
		}
	}
	return FALSE;
}
/*add memory object to the last of the memory-image(linked list)*/
void add_to_end(memoryObj_ptr * head, memoryObj_ptr temp)
{
	memoryObj_ptr p1, p2;

	p1=*head;
	for(;p1; p1=p1->next)
		p2=p1;
	
	if(codeFLAG){
		temp->next = p1;
		p2->next = temp;
	}
	else
		p2->next = temp;

	return;
}

/*init instance number as a word*/
void add_instanceNum_word(memoryObj_ptr temp_word)
{
	temp_word->word_uni.index = (atoi(op_array[i_temp])<<THREE_LEFT);
	temp_word->word_uni.bits.A=1;
	return;
}

/*	- init set label as deafult (UNKNOWN_ADRESS) until the second pass initialize it.
	- save the label */
void add_label_word(memoryObj_ptr temp_word)
{	
	temp_word->word_uni.index = UNKNOWN_ADRESS;
	strcpy(temp_word->line,label);
	return;
}

/*	- add all data numbers operands to the memory-image
	- loop on the op_array until its over.	*/
memoryObj_ptr add_data_numbers(memoryObj_ptr head_num)
{
	int i=0;
	memoryObj_ptr p1, p2;
	p1 = (memoryObj_ptr)calloc(i_op+1,sizeof(memoryObj_node));
	head_num=p1;

	if(i_op==1){
		p1->word_uni.index=atoi(op_array[i]);
		p1->address = DC;
		DC++;
		p1->next = NULL;
		return head_num;
	}

	p2 = (p1+1);
	for(;i<i_op;i++){
		p1->word_uni.index=atoi(op_array[i]);	
		p1->address = DC;
		DC++;
		p1->next=p2;
		p1=p2;
		if(i<i_op-1)
			p2++;	
	}
	p1--;	
	p1->next = NULL;
	return head_num;
}

/*	- add each char of the string as a word (24bit) 
	- loop on op_array's characters */
memoryObj_ptr add_string(memoryObj_ptr head_str)
{
	int i=0;
	int str_len = (strlen(op_array[i])+1);	
	memoryObj_ptr p1, p2;
	
	p1 =(memoryObj_ptr)calloc(str_len,sizeof(memoryObj_node));
	head_str=p1;
	p2 = (p1+1);
	
	for(;i<(str_len-1);i++){
		p1->word_uni.index=(int)*(*op_array+i);		
		p1->address = DC;
		DC++;
		p1->next = p2;
		p1=p2;
		if((i+1)<(str_len-1))
			p2++;
	}
	/* for the last '\0' of string: */
	p1->word_uni.index=(int)('\0');
	p1->address = DC;
	DC++;	
	p1->next = NULL;
	return head_str; 
}
/*add one extra word.*/
int extra_word(memoryObj_ptr temp, int * IC)
{
	memoryObj_ptr temp_word = create_object();
	if(count_extra_words>2){
		printf("too many extra words");
		return FALSE;
	}

	if(unvalid_extra_word()){
		i_temp++;
		return FALSE;
	}

	temp->next = temp_word;
	temp_word->address = *IC;
	(*IC)++;
	count_extra_words++;

	if(isalpha(*op_array[i_temp]))
		add_label_word(temp_word);
	else
		add_instanceNum_word(temp_word);
	
	i_temp++;
	return TRUE;
}

/*extra word canot exist if source method or destenation method */
int unvalid_extra_word()
{
	if((src_method==fourth && dst_method==fourth)||(src_method==NO_METHOD && dst_method==fourth)||ExIsRegister(op_array[i_temp]))
		return TRUE;
	
	return FALSE;
}

int ExIsRegister(char *str)
{	
	int i;
	for(i=0;i<REGISTERS_NUM;i++)
		if(!(strcmp(rgstrs_arr[i].name,str)))
			 return TRUE;
	return FALSE;
}

/*
	This function loop on the memory-image and symbol-table.
	- if current destination method is the third, its mean that it is a jump code and need to calaulate distance to label
	- initialize the extern-help-list for create the .ext file
	- turn on R or E bit.
*/
int update_memory_image()
{
	int third_method=FALSE;
	memoryObj_ptr h_mem = code_head;
	ptr h_sym = symbolTable_head;
	int i=0;

	while(h_mem)
	{
		if(h_mem->word_uni.bits.destination_m==third) third_method=TRUE;/*check the destination_method of the *first word**/

		if(h_mem->word_uni.index==UNKNOWN_ADRESS) /*from here, the current memory word is UNKNOWN_ADRESS(-1)*/
		{
			while(h_sym)
			{
				if(find_in_symbolT(h_mem,h_sym))
				{
					if(third_method){
						calc_distance(h_mem,h_sym);
						third_method=FALSE;
						break;
					}
					
					h_mem->word_uni.index=(h_sym->value<<THREE_LEFT);
					if(isExternal(h_sym)){
						strcpy(ext_help_list[i].name,h_sym->name);
						ext_help_list[i].address=h_mem->address;
						i++;
						h_mem->word_uni.bits.E|=1;		
					}			
					else
						h_mem->word_uni.bits.R|=1;
					break;
				}	
				h_sym=h_sym->next;	
			}	
		}		
		h_sym=symbolTable_head;		
		h_mem=h_mem->next;
	}

	return TRUE;
}

/* calc distanse from current h_mem to his adress acording to address in the symbol-table */
void calc_distance(memoryObj_ptr h_mem, ptr h_sym)
{
	h_mem->word_uni.index=(h_sym->value)-(h_mem->address)+1;
	h_mem->word_uni.index<<=THREE_LEFT;
	h_mem->word_uni.bits.A|=1;
	return;
}

int isExternal(ptr h_sym)
{
	if(!strcmp(h_sym->type,"external"))
		return TRUE;

	return FALSE;
}

int find_in_symbolT(memoryObj_ptr h_mem, ptr h_sym )
{
	if(!strcmp(h_mem->line,h_sym->name))
		return TRUE;

	return FALSE;
}

/*
-------------------------------------
-----Functions for write to files----
-------------------------------------
*/

/*write the memory-image list to file*/
void wMemory(FILE **file)
{
	memoryObj_ptr h_mem = code_head;

	while(h_mem){
		fprintf(*file,"\t\t\t");
		pAddress(h_mem->address,file);
		fprintf(*file,"%d ",h_mem->address);
		pHexa(h_mem->word_uni.index,file);
		h_mem=h_mem->next;
	}
	return;
}
/*write to file the 24 bit word in hexa*/
int pHexa(int num,FILE **ob)
{
	char temp[STR_SIZE];
    sprintf(temp, "%06x", num);
	if(num<0){
		fprintf(*ob,"%s\n",temp+2);
		return 0;	
	}

	fprintf(*ob,"%s\n",temp);
	return 0;
}
/*write '0' to the address if its less then 1000000*/
int pAddress(int address,FILE **file)
{
	if(address==0)
		return FALSE;

	while(address<1000000){
		fprintf(*file,"%d",0);
		address*=10;
	}
	
	return TRUE;
}
/*write to file the name and the address of entry according to symbol-table*/
void wEntry(FILE **file)
{
	ptr h_sym = symbolTable_head;
	
	while(h_sym)
	{
		if(strstr(h_sym->type,"entry")){	
			fprintf(*file,"%s ",h_sym->name);
			pAddress(h_sym->value,file);
			fprintf(*file,"%d",h_sym->value);
			fprintf(*file,"\n");
		}
		h_sym=h_sym->next;
	}
	return;
}

/*write to file the name and the address of external label according to external help list*/
void wExternal(FILE **file)
{
	int i=0;
	memoryObj_ptr h_mem = code_head;

	while(h_mem)
	{
		if(h_mem->word_uni.bits.E && !(isalnum(h_mem->word_uni.index)) && h_mem->word_uni.index!=0 && ext_help_list[i].address!=0 ){		
			fprintf(*file,"%s ",ext_help_list[i].name);
			pAddress(ext_help_list[i].address,file);	
			fprintf(*file,"%d\n",ext_help_list[i].address);
			i++;
		}
		h_mem=h_mem->next;
	}
	return;
}

memoryObj_ptr create_object()
{
	memoryObj_ptr temp = (memoryObj_ptr) malloc(sizeof(memoryObj_node));
	if(!temp){
		fprintf(stderr, "cannot allocate memory of mem_obj_temp in dataImg.(\"memoryImage.c\")");
		exit(0);
	}
	return temp;	
}

void connnectLists()
{
	memoryObj_ptr h_code = code_head;
	add_to_end(&h_code,data_head);
	return;
}

/*----------------------------
-----Functions for debug------
-----------------------------*/

void printDataImg(memoryObj_ptr head)
{
	printf("Data Image:\n");
	printf("adress		Code\n");
	while(head){	
		printf("%d	",head->address);
		bin_word(head->word_uni.index);
		printf("	%x",head->word_uni.index);
		printf("		");
		printf("%s ",head->line);
		puts("");
		head = head->next;
	}
	puts("--------------");
	return;
}

void bin_word(unsigned n) { 
    unsigned i; 
    for (i=1<<(WORD_SIZE-1) ; i>0 ; i=i/2) 
        (n & i)? printf("1"): printf("0"); 
}

void printEachField(memoryObj_ptr head){
	printf("%d	",head->address);
	printf("opcode: %d\n",head->word_uni.bits.opcode);
	return;
}
