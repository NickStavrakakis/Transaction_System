#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structs.h"

void insert_acc(Root *root, char* name, bool out);

void insert_trn(Root *root, char* name_1, char* name_2, int ammount, bool out);

void delete_acc(Root *root, char* name);

void delete_trn(Root *root, char* name_1, char* name_2, int ammount);

void modify(Root *root, char* name_1, char* name_2, int old_ammount, int new_ammount);

void receiving(Root *root, char* name);

void circlefind(Root *root, char *name);

void findcircles(Root *root, char *name, int min);

void traceflow(Root *root, char *from_acc_name, char *to_acc_name, int length);

void exiting(Root *root, char* output);

Account *search(Root *root, char *name);

////////////////////////////////////////

bool load_input_file(Root *root, char *input, int max_acc_leng);

bool call_cmd(Root *root, char *cmd, int max_cmd_leng, char *output);

int count_accounts(Root *root);

int count_transfers(Root *root);

void recursive(Root *root, Account *curr_acc, Account *cycle_acc, char print[(MAX_ACC_LENG+3)*(count_accounts(root))], bool *flag, int min, char target[(MAX_ACC_LENG+3)*(count_accounts(root))], int *curr_length, int length);

void f_recursive_f(Root *root, Account *curr_acc, Account *cycle_acc, char print[(MAX_ACC_LENG+3)*(count_accounts(root))], bool *flag, int min, char target[(MAX_ACC_LENG+3)*(count_accounts(root))], int *curr_length, int length);
