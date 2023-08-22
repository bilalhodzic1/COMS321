//
// Created by Bilal Hodzic on 5/3/23.
//
#include "inputter.h"
#include <stdio.h>
#include <stdlib.h>



instruction_linked_list_t* init_list_node(char *name, uint32_t six_opcode, uint32_t eight_opcode, uint32_t eleven_opcode, uint32_t ten_opcode,
               int type) {
    instruction_format_t data;
    instruction_linked_list_t *node = malloc(sizeof(instruction_linked_list_t));
    data.eight_opcode = eight_opcode;
    data.six_opcode = six_opcode;
    data.name = malloc(sizeof(name));
    data.name = name;
    data.eleven_opcode = eleven_opcode;
    data.ten_opcode = ten_opcode;
    data.type = type;
    node->data = data;
    return node;
}

void add_to_list(instruction_linked_list_t *head, instruction_linked_list_t *new_node) {
    instruction_linked_list_t *finder = head;
    while (finder->next != NULL) {
        finder = finder->next;
    }
    finder->next = new_node;
}

instruction_format_t search_list(instruction_linked_list_t *head, uint32_t six_opcode,
                                 uint32_t eight_opcode, uint32_t eleven_opcode, uint32_t ten_opcode) {
    instruction_linked_list_t *finder = head;
    do {
        if (six_opcode == finder->data.six_opcode || eight_opcode == finder->data.eight_opcode ||
            eleven_opcode == finder->data.eleven_opcode || ten_opcode == finder->data.ten_opcode) {
            return finder->data;
        } else {
            finder = finder->next;
        }
    } while (finder != NULL);
    instruction_format_t blank;
    return blank;
}
//Removed function does not work
//instruction_linked_list_t* load_instructions(char* filename){
//    instruction_linked_list_t* head;
//    FILE *file = fopen(filename, "r");
//    char c;
//    int line_count = 0;
//    fclose(file);
//    file = fopen(filename, "r");
//    int i;
//    for(i = 0; i <  6; i++){
//        char* name = malloc(4 * sizeof(char));
//        int type;
//        uint32_t six_opcode;
//        uint32_t eight_opcode;
//        uint32_t ten_opcode;
//        uint32_t eleven_opcode;
//        fscanf(file, "%s, %d, %x, %x, %x, %x", name, &type, &six_opcode, &eight_opcode,
//               &ten_opcode, &eleven_opcode);
//        if(head == NULL) {
//            head = init_list_node(name, six_opcode, eight_opcode, eleven_opcode, ten_opcode, type);
//        }else{
//            add_to_list(head, init_list_node(name, six_opcode, eight_opcode, eleven_opcode, ten_opcode, type));
//        }
//    }
//    return head;
//}