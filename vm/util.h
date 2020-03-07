#ifndef UTIL_H_G3U7SPJM
#define UTIL_H_G3U7SPJM
#include "vm.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_ir_to_op(char* ins)
{
    for (int i = 0; i < SYSCALL_NUM; ++i) {
        if (strcmp(ins, op_dict[i].ir_s) == 0)
            return op_dict[i].ir;
    }
    return ERR_UNKONWN_INSTRUCTION;
}

char* get_op_to_ir(int* ins)
{
    int op = *ins;
    for (int i = 0; i < SYSCALL_NUM; ++i) {
        if (op == op_dict[i].ir)
            return op_dict[i].ir_s;
    }
    return NULL;
}

struct str_t* get_str_entry(int hash)
{
    for (struct str_t* i = str_tbl; i < ts_str_tbl; ++i) {
        if (i->hash == hash)
            return i;
    }
    return NULL;
}

struct sym_t* get_sym_entry(int hash)
{
    for (struct sym_t* i = sym_tbl; i < ts_sym_tbl; ++i) {
        if (i->hash == hash)
            return i;
    }
    return NULL;
}

struct sym_t* get_sym_entry_by_str(char* str)
{
    for (struct sym_t* i = sym_tbl; i < ts_sym_tbl; ++i) {
        if (strcmp(i->s, str) == 0)
            return i;
    }
    return NULL;
}

struct code_t* get_code_entry(int line)
{
    for (struct code_t* i = code; i < ts_code; ++i) {
        if (i->line == line)
            return i;
    }
    return NULL;
}

int fetch_args(intptr_t* sp, intptr_t* args, int32_t nu_args)
{
    struct str_t* tstr;
    intptr_t* ptr = args;
    for (int i = nu_args - 1; i >= 0; --i) {
        tstr = get_str_entry(sp[i]);
        if (tstr != NULL) {
            *ptr++ = (intptr_t)tstr->str;
        } else {
            *ptr++ = sp[i];
        }
    }
    return 0;
}

int print_code(struct code_t* start, struct code_t* end)
{
    for (struct code_t* i = start; i < end; ++i) {
        if (i->ir <= ADJ)
            printf("%% %d = %s %d\n", i->line, get_op_to_ir(&i->ir), i->arg);
        else
            printf("%% %d = %s\n", i->line, get_op_to_ir(&i->ir));
    }
    return 0;
}

int print_all_symbol(struct sym_t* start, struct sym_t* end)
{
    for (struct sym_t* i = start; i < end; ++i) {
        printf("@%s = %d %d\n", i->s, i->type, i->hash);
    }
    return 0;
}

int print_all_str(struct str_t* start, struct str_t* end)
{
    for (struct str_t* i = start; i < end; ++i) {
        printf("@.str.%d = %d \"%s\",%d\n", i->nu, i->len, i->str, i->hash);
    }
    return 0;
}

#endif /* end of include guard: UTIL_H_G3U7SPJM */
