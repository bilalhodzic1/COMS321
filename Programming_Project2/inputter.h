//
// Created by Bilal Hodzic on 5/2/23.
//

#ifndef PROGRAMMING_PROJECT2_INPUTTER_H
#define PROGRAMMING_PROJECT2_INPUTTER_H
#include <stdint.h>
#include <stdio.h>


typedef struct instruction_format{
    uint32_t six_opcode;
    uint32_t eight_opcode;
    uint32_t eleven_opcode;
    uint32_t ten_opcode;
    char* name;
    int type;
}  instruction_format_t;
typedef struct instruction_linked_list instruction_linked_list_t;

struct instruction_linked_list{
    instruction_linked_list_t* next;
    instruction_format_t data;
};
//Removed function does not work
//instruction_linked_list_t* load_instructions(char* filename);
instruction_format_t search_list(instruction_linked_list_t* head, uint32_t six_opcode, uint32_t eight_opcode, uint32_t eleven_opcode, uint32_t ten_opcode);
void add_to_list(instruction_linked_list_t* head, instruction_linked_list_t* new_node);
instruction_linked_list_t* init_list_node(char* name, uint32_t six_opcode, uint32_t eight_opcode, uint32_t eleven_opcode,uint32_t ten_opcode, int type);

#endif //PROGRAMMING_PROJECT2_INPUTTER_H
