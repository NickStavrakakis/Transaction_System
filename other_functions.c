#include "functions.h"


//search if the given name exists, if yes return its account
Account *search(Root *root, char *name){
    Account *current = root->acc_begin;
    while(current != NULL){
        if(strcmp(current->name, name)==0){
            return current;
        }
        current = current->next_acc;
    }
    return NULL;
}

bool load_input_file(Root *root, char *input, int max_acc_leng){
    char buffer[1024], *line, *record, acc_1[max_acc_leng], acc_2[max_acc_leng];
    int trn;
    FILE *fp = fopen(input,"r");
//printf("loading %s\n\n", input);
    if(fp==NULL){
        printf("The given input file doesn't exist\n");
        return false;
    }
    while((line=fgets(buffer,sizeof(buffer),fp))!=NULL){
        record = strtok(line,";");
        while(record != NULL){
            sscanf(record, "%s %s %d", acc_1, acc_2, &trn);
            insert_trn(root, acc_1, acc_2, trn, false);
        //    printf("\n");
            record = strtok(NULL,";");
        }
    }
    fclose(fp);
    return true;
}

//helpfull function
int count_accounts(Root *root){
    Account* curr_acc = (Account*)malloc(sizeof(Account));
    curr_acc = root->acc_begin;
    int count = 0;
    while(curr_acc!=NULL){
        count++;
        curr_acc = curr_acc->next_acc;
    }
    return count;
}

//helpfull function
int count_transfers(Root *root){
    Transfer* curr_trn = (Transfer*)malloc(sizeof(Transfer));
    curr_trn = root->trn_begin;
    int count = 0;
    while(curr_trn!=NULL){
        count++;
        curr_trn = curr_trn->next_trn;
    }
    return count;
}

//see readme
void recursive(Root *root, Account *curr_acc, Account *cycle_acc, char print[(MAX_ACC_LENG+3)*(count_accounts(root))], bool *flag, int min, char target[(MAX_ACC_LENG+3)*(count_accounts(root))], int *curr_length, int length){
    (*curr_length)++;
    Transfer *curr_trn = root->trn_begin;
    char for_print[(MAX_ACC_LENG+3)*(count_accounts(root))], str[MAX_ACC_LENG*2], old_str[(MAX_ACC_LENG+3)*(count_accounts(root))];
    str[0]='\0', old_str[0]='\0';
    strcpy(for_print, print);
    while(curr_trn!=NULL){
        if((curr_trn->from_acc == curr_acc)&&(curr_trn->ammount>min)){
            if(curr_acc->visited == false){
                curr_acc->visited = true;
                strcpy(old_str, for_print);
                str[0]='\0';
                sprintf(str, "|%s|->%d->", (curr_trn->from_acc)->name, curr_trn->ammount);
                strcat(for_print, str);
                recursive(root, curr_trn->to_acc, cycle_acc, for_print, flag, min, target, curr_length, length);
                curr_acc->visited = false;
                (*curr_length)--;
            }
            if((curr_trn->to_acc == cycle_acc) && (for_print[0]!='\0')){
                str[0]='\0';
                sprintf(str, "|%s|", target);

                if(min!=-1){
                    if(strstr(for_print, target)){
                        printf("%s|%s|\n", for_print, (curr_trn->to_acc)->name);
                        *flag = true;
                    }
                }
                else{
                    if((length==-1)||(*curr_length)<=length){
                        printf("%s|%s|\n", for_print, (curr_trn->to_acc)->name);
                        *flag = true;
                    }
                }
            }
            strcpy(for_print, old_str);
        }
        curr_trn = curr_trn->next_trn;
    }
    return;
}

void f_recursive_f(Root *root, Account *curr_acc, Account *cycle_acc, char print[(MAX_ACC_LENG+3)*(count_accounts(root))], bool *flag, int min, char target[(MAX_ACC_LENG+3)*(count_accounts(root))], int *curr_length, int length){
    (*curr_length)++;
    Transfer *curr_trn = root->trn_begin;
    char for_print[(MAX_ACC_LENG+3)*(count_accounts(root))], str[MAX_ACC_LENG*2], old_str[(MAX_ACC_LENG+3)*(count_accounts(root))];
    str[0]='\0', old_str[0]='\0';
    strcpy(for_print, print);
    while(curr_trn!=NULL){
        if((curr_trn->from_acc == curr_acc)&&(curr_trn->ammount>min)){
            if(curr_trn->visited == false){
                curr_trn->visited = true;
                strcpy(old_str, for_print);
                str[0]='\0';
                sprintf(str, "|%s|->%d->", (curr_trn->from_acc)->name, curr_trn->ammount);
                strcat(for_print, str);
                f_recursive_f(root, curr_trn->to_acc, cycle_acc, for_print, flag, min, target, curr_length, length);
                curr_trn->visited = false;
                (*curr_length)--;
            }
            if((curr_trn->to_acc == cycle_acc) && (for_print[0]!='\0')){
                str[0]='\0';
                sprintf(str, "|%s|", target);
                if(min!=-1){
                    if(strstr(for_print, target)){
                        printf("%s|%s|\n", for_print, (curr_trn->to_acc)->name);
                        *flag = true;
                    }
                }
                else{
                    if((length==-1)||(*curr_length)<=length){
                        printf("%s|%s|\n", for_print, (curr_trn->to_acc)->name);
                        *flag = true;
                    }
                }
            }
            strcpy(for_print, old_str);
        }
        curr_trn = curr_trn->next_trn;
    }
    return;
}

//here we get the user input and execute the right command
bool call_cmd(Root *root, char *cmd, int max_cmd_leng, char *output){
    char arg1[MAX_ACC_LENG], arg2[MAX_ACC_LENG], arg3[MAX_ACC_LENG];
    arg1[0] = '\0';
    arg2[0] = '\0';
    arg3[0] = '\0';
    int arg4 = -1, arg5 = -1;
    sscanf(cmd, "%s %s %s %d %d", arg1, arg2, arg3, &arg4, &arg5);
    if(strcmp(arg1, "i")==0){
        if((arg2[0]!='\0') && (arg3[0]=='\0')){
            insert_acc(root, arg2, true);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "n")==0){
        if((arg2[0]!='\0') && (arg3[0]!='\0') && (arg4!=-1) && (arg5==-1)){
            insert_trn(root, arg2, arg3, arg4, true);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "d")==0){
        if((arg2[0]!='\0') && (arg3[0]=='\0')){
            delete_acc(root, arg2);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "l")==0){
        if((arg2[0]!='\0') && (arg3[0]!='\0') && (arg4!=-1) && (arg5==-1)){
            delete_trn(root, arg2, arg3, arg4);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "m")==0){
        if((arg2[0]!='\0') && (arg3[0]!='\0') && (arg4!=-1) && (arg5!=-1)){
            modify(root, arg2, arg3, arg4, arg5);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "r")==0){
        if((arg2[0]!='\0') && (arg3[0]=='\0')){
            receiving(root, arg2);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "c")==0){
        if((arg2[0]!='\0') && (arg3[0]=='\0')){
            circlefind(root, arg2);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "f")==0){
        if((arg2[0]!='\0') && (arg3[0]!='\0') && (arg4==-1) && (arg5==-1)){
            findcircles(root, arg2, atoi(arg3));
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "t")==0){
        if((arg2[0]!='\0') && (arg3[0]!='\0') && (arg4!=-1) && (arg5==-1)){
            traceflow(root, arg2, arg3, arg4);
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    if(strcmp(arg1, "e")==0){
        if(arg2[0]=='\0'){
            exiting(root, output);
            return false;
        }
        else{
            printf("- Invalid command\n");
        }
        return true;
    }
    else{
        printf("- Invalid command\n");
        return true;
    }
}
