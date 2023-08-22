//
// Created by Bilal Hodzic on 5/2/23.
//

#include "decode.h"

//Starts 65535
//Starts 11111111111111111111111111111111
//10101011
uint32_t grab_instruct_raw(int index, FILE* file){
    uint32_t instruct;
    int i;
    if(fscanf(file, "%x", &instruct) != 1){
        printf("Fscan faield");
    }
    return instruct;
}
instruction_format_t find_instruct(uint32_t instruct, instruction_linked_list_t *head) {
    uint32_t six_opcode = (instruct >> 26) & 0x3f;
    uint32_t eight_opcode = (instruct >> 24) & 0xff;
    uint32_t eleven_opcode = (instruct >> 21) & 0x7ff;
    uint32_t ten_opcode = (instruct >> 22) & 0x3ff;
    instruction_format_t format = search_list(head, six_opcode, eight_opcode, eleven_opcode, ten_opcode);
    return format;
}

instruction_info_t decode(instruction_format_t format, uint32_t instruct) {
    instruction_info_t finalized;
    finalized.name = format.name;
    finalized.type = format.type;
    if (format.type == 0) {
        finalized.rd = instruct & 0x1f;
        finalized.rn = (instruct >> 5) & 0x1f;
        finalized.rm = (instruct >> 16) & 0x1f;
        finalized.shamt = (instruct >> 10) & 0x3f;
    } else if (format.type == 1) {
        finalized.rd = instruct & 0x1f;
        finalized.rn = (instruct >> 5) & 0x1f;
        if (((instruct >> 21) & 0x1) == 1) {
            int masked = (signed) (instruct >> 10) & 0xfff;
            masked = (signed) (masked ^ 0xfffff000);
            finalized.ALU_immd = masked;
        } else {
            finalized.ALU_immd = (instruct >> 10) & 0xfff;
        }
    } else if (format.type == 2) {
        finalized.rt = instruct & 0x1f;
        finalized.rn = (instruct >> 5) & 0x1f;
        if (((instruct >> 20) & 0x1) == 1) {
            int masked = (signed) (instruct >> 12) & 0x1ff;
            masked = (signed) (masked ^ 0xFffffE00);
            finalized.ALU_immd = masked;
        } else {
            finalized.ALU_immd = (instruct >> 12) & 0x1ff;
        }
    } else if (format.type == 3) {
        if (((instruct >> 25) & 0x1) == 1) {
            int masked = (signed) (instruct & 0x3ffffff);
            masked = (signed) (masked ^ 0xFC000000);
            finalized.ALU_immd = masked;
        } else {
            finalized.ALU_immd = instruct & 0x3ffffff;
        }
    } else if (format.type == 4) {
        finalized.rt = instruct & 0x1f;
        if ((instruct >> 23) & 0x1) {
            int masked = (signed) ((instruct >> 5) & 0x7ffff);
            masked = (signed) (masked ^ 0xFFF80000);
            finalized.ALU_immd = masked;
        } else {
            finalized.ALU_immd = (instruct >> 5) & 0x7ffff;
        }


    }else if (format.type == 5){
	    finalized.rd = instruct & 0x1f;
    }

    return finalized;
}

void print_assembly(instruction_info_t finalized) {
    if (finalized.type == 0) {
        if (strcmp(finalized.name, "LSL") == 0 || strcmp(finalized.name, "LSR") == 0) {
            printf("%s X%d, X%d, #%d\n", finalized.name, finalized.rd, finalized.rn, finalized.shamt);
        } else if (strcmp(finalized.name, "BR") == 0) {
            printf("%s X%d\n", finalized.name, finalized.rn);
        } else {
            printf("%s X%d, X%d, X%d\n", finalized.name, finalized.rd, finalized.rn, finalized.rm);
        }
    } else if (finalized.type == 1) {
        printf("%s X%d, X%d, #%d\n", finalized.name, finalized.rd, finalized.rn, finalized.ALU_immd);
    } else if (finalized.type == 2) {
        printf("%s X%d, [X%d, #%d]\n", finalized.name, finalized.rt, finalized.rn, finalized.ALU_immd);
    } else if (finalized.type == 3) {
        printf("%s #%d\n", finalized.name, finalized.ALU_immd);
    } else if (finalized.type == 4) {
        if (strcmp(finalized.name, "B.") == 0) {
            if (finalized.rt == 0) {
                printf("%sEQ #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 1) {
                printf("%sNE #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 2) {
                printf("%sHS #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 3) {
                printf("%sLO #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 4) {
                printf("%sMI #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 5) {
                printf("%sPL #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 6) {
                printf("%sVS #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 7) {
                printf("%sVC #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 8) {
                printf("%sHI #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 9) {
                printf("%sLS #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 10) {
                printf("%sGE #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 11) {
                printf("%sLT #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 12) {
                printf("%sGT #%d\n", finalized.name, finalized.ALU_immd);
            } else if (finalized.rt == 13) {
                printf("%sLE #%d\n", finalized.name, finalized.ALU_immd);
            }
        } else {
            printf("%s X%d, #%d\n", finalized.name, finalized.rt, finalized.ALU_immd);
        }
    }else if (finalized.type ==5){
	printf("%s X%d\n", finalized.name, finalized.rd);	
    }else if (finalized.type == 6){
	    printf("%s\n", finalized.name);
    }
}
