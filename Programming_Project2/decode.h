//
// Created by Bilal Hodzic on 5/2/23.
//

#ifndef PROGRAMMING_PROJECT2_DECODE_H
#define PROGRAMMING_PROJECT2_DECODE_H
#include <stdint.h>
#include "inputter.h"
#include <stdio.h>
#include <string.h>
typedef struct instruction_info{
    char* name;
    int type;
    uint32_t rd;
    uint32_t rn;
    uint32_t rm;
    uint32_t rt;
    signed int ALU_immd;
    uint32_t shamt;
}instruction_info_t;

uint32_t grab_instruct_raw(int index, FILE* file);
instruction_format_t find_instruct(uint32_t instruct, instruction_linked_list_t* head);
instruction_info_t decode(instruction_format_t format, uint32_t instruct);
void print_assembly(instruction_info_t finalized_instruct);



#endif //PROGRAMMING_PROJECT2_DECODE_H
