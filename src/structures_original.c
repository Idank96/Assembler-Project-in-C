#include "global.h"
#include "structers.h"


command_s commands_array[NUM_OF_COMMANDS]={
		{0,"mov",0,0,2,{0,1,3},{1,3,MISS}},
		{1,"cmp",1,0,2,{0,1,3},{0,1,3}},
		{2,"add",2,1,2,{0,1,3},{1,3,MISS}},
		{3,"sub",2,2,2,{0,1,3},{1,3,MISS}},
		{4,"lea",4,0,2,{1,MISS,MISS},{1,3,MISS}},
		{5,"clr",5,1,1,{MISS,MISS,MISS},{1,3,MISS}},
		{6,"not",5,2,1,{MISS,MISS,MISS},{1,3,MISS}},
		{7,"inc",5,3,1,{MISS,MISS,MISS},{1,3,MISS}},
		{8,"dec",5,4,1,{MISS,MISS,MISS},{1,3,MISS}},
		{9,"jmp",9,1,1,{MISS,MISS,MISS},{1,2,MISS}},
		{10,"bne",9,2,1,{MISS,MISS,MISS},{1,2,MISS}},
		{11,"jsr",9,3,1,{MISS,MISS,MISS},{1,2,MISS}},
		{12,"red",12,0,1,{MISS,MISS,MISS},{1,3,MISS}},
		{13,"prn",13,0,1,{MISS,MISS,MISS},{0,1,3}},
		{14,"rts",14,0,0,{MISS,MISS,MISS},{MISS,MISS,MISS}},
		{15,"stop",15,0,0,{MISS,MISS,MISS},{MISS,MISS,MISS}}
};

data_s data_arr[DATA_TYPES_NUM]={
		{".data"},
		{".string"},
		{".entry"},
		{".extern"}
};

registers_struct rgstrs_arr[NUM_OF_REGISTERS]={ {"r0"},{"r1"},{"r2"},{"r3"},{"r4"},{"r5"},{"r6"},{"r7"} };
