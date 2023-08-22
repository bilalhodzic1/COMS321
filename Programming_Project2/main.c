#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include "decode.h"
#include "inputter.h"

int main(int arc, char *argv[]) {
    //0 is R
    //1 is I
    //2 is D
    //3 is B
    //4 is CB
    //5 is PRNT
    //6 is SIngle word instructions
    //Couldnt be bothered to load instructions from a file so all are hard coded manually below
    char *name = "ADD";
    int type = 0;
    uint32_t eleven_opcode = 0x458;
    instruction_linked_list_t *head = init_list_node(name, 0, 0, eleven_opcode, 0, type);
    name = "ADDI";
    type = 1;
    uint32_t ten_opcode = 0x244;
    add_to_list(head, init_list_node(name, 0, 0, 0, ten_opcode, type));
    name = "AND";
    type = 0;
    eleven_opcode = 0x450;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "ANDI";
    type = 1;
    ten_opcode = 0x248;
    add_to_list(head, init_list_node(name, 0, 0, 0, ten_opcode, type));
    name = "B";
    type = 3;
    uint32_t six_opcode = 0x05;
    add_to_list(head, init_list_node(name, six_opcode, 0, 0, 0, type));
    name = "B.";
    type = 4;
    uint32_t eight_opcode = 0x54;
    add_to_list(head, init_list_node(name, 0, eight_opcode, 0, 0, type));
    name = "BL";
    type = 3;
    six_opcode = 0x25;
    add_to_list(head, init_list_node(name, six_opcode, 0, 0, 0, type));
    name = "BR";
    type = 0;
    eleven_opcode = 0x6B0;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "CBNZ";
    type = 4;
    eight_opcode = 0xB5;
    add_to_list(head, init_list_node(name, 0, eight_opcode, 0, 0, type));
    name = "CBZ";
    type = 4;
    eight_opcode = 0xB4;
    add_to_list(head, init_list_node(name, 0, eight_opcode, 0, 0, type));
    name = "EOR";
    type = 0;
    eleven_opcode = 0x650;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "EORI";
    type = 1;
    ten_opcode = 0x348 & 0x3ff;
    add_to_list(head, init_list_node(name, 0, 0, 0, ten_opcode, type));
    name = "LDUR";
    type = 2;
    eleven_opcode = 0x7C2;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "LSL";
    type = 0;
    eleven_opcode = 0x69B;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "LSR";
    type = 0;
    eleven_opcode = 0x69A;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "ORR";
    type = 0;
    eleven_opcode = 0x550;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "ORRI";
    type = 1;
    ten_opcode = 0x2C8;
    add_to_list(head, init_list_node(name, 0, 0, 0, ten_opcode, type));
    name = "STUR";
    type = 2;
    eleven_opcode = 0x7C0;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "SUB";
    type = 0;
    eleven_opcode = 0x658;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "SUBI";
    type = 1;
    ten_opcode = 0x344;
    add_to_list(head, init_list_node(name, 0, 0, 0, ten_opcode, type));
    name = "SUBIS";
    type = 1;
    ten_opcode = 0x3C4;
    add_to_list(head, init_list_node(name, 0, 0, 0, ten_opcode, type));
    name = "SUBS";
    type = 0;
    eleven_opcode = 0x758;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "MUL";
    type = 0;
    eleven_opcode = 0x4D8;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "PRNT";
    type = 5;
    eleven_opcode = 0x7FD;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "PRNL";
    type = 6;
    eleven_opcode = 0x7FC;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "DUMP";
    type = 6;
    eleven_opcode = 0x7FE;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));
    name = "HALT";
    type = 6;
    eleven_opcode = 0x7ff;
    add_to_list(head, init_list_node(name, 0, 0, eleven_opcode, 0, type));

    FILE* file = fopen(argv[1], "rb");
    int i = 0;
    //2432732129
  //  print_assembly(decode(find_instruct(instruct, head), instruct));

   // instruct = grab_instruct_raw(i ,file);
    uint32_t value;

//    fp = fopen(argv[1], "rb");
//    if (fp == NULL) {
//        printf("Error: Unable to open file\n");
//        return 1;
//    }

    // Loop through the file
    
    while (fread(&value, sizeof(value), 1, file) == 1) {
        print_assembly(decode(find_instruct(be32toh(value),head),be32toh(value)));
       // printf("%u\n", be32toh(value));
    }

    fclose(file);
//    uint32_t new_instruct = 0x8B1103EB;
//    uint32_t i_type_instruct = 0xD201F1D6;
//    uint32_t d_type_instruct = 0xF8420189;
//    uint32_t b_type_instruct = 0x17FFFFD6;
//    uint32_t cb_type_instruct = 0xB400022A;
//    uint32_t lsl_instruct = 0xD3603D29;
//    uint32_t STUR_instruct = 0xF8040221;
//    instruction_format_t format = find_instruct(new_instruct, head);
//    print_assembly(decode(format, new_instruct));
//    print_assembly(decode(find_instruct(i_type_instruct, head), i_type_instruct));
//    print_assembly(decode(find_instruct(d_type_instruct, head), d_type_instruct));
//    print_assembly(decode(find_instruct(b_type_instruct, head), b_type_instruct));
//    print_assembly(decode(find_instruct(cb_type_instruct, head), cb_type_instruct));
//    print_assembly(decode(find_instruct(lsl_instruct, head), lsl_instruct));
//    print_assembly(decode(find_instruct(STUR_instruct, head), STUR_instruct));



    //free(head);
    return 0;
}

