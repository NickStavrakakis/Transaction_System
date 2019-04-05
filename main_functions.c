#include "functions.h"

void insert_acc(Root *root, char* name, bool out){
    //check if an account exists with that name
    if(search(root, name)){
        printf("Node |%s| Exists;\n", name);
        return;
    }

    //allocating memory for the new account
    Account *new_acc = (Account*)malloc(sizeof(Account));
    //current account points to the first account of the list
    Account *curr_acc = root->acc_begin;

    //if the root of accounts is empty, add him on the first place
    if(root->acc_begin == NULL){
        root->acc_begin = new_acc;
    }
    else{ // if not, search for the end of the list and then add the current account in the end
        while(curr_acc->next_acc != NULL){ //while the accounts list is not in the end
            curr_acc = curr_acc->next_acc;
        }
        curr_acc->next_acc = new_acc;
    }

    //inserting the right info in the new account
    new_acc->next_acc = NULL;
    strcpy(new_acc->name, name);
    if(out)
        printf("Inserted |%s|\n", new_acc->name);
    return;
}

void insert_trn(Root *root, char* name_1, char* name_2, int ammount, bool out){

    //check if an accounts exist, if not, then add them
    if(search(root, name_1)==NULL){
        insert_acc(root, name_1, false);
    }
    if(search(root, name_2)==NULL){
        insert_acc(root, name_2, false);
    }

    //allocating memory for the new transfer
    Transfer *new_trn = (Transfer*)malloc(sizeof(Transfer));
    //current transfer points to the first account of the list
    Transfer *curr_trn = root->trn_begin;

    //if the root of transfers is empty, add the current transfer on the first place
    if(root->trn_begin == NULL){
        root->trn_begin = new_trn;
    }
    else{ // if not, search for the end of the list and then add the current transfer in the end
        while(curr_trn->next_trn != NULL){ //while the transfers list is not in the end
            curr_trn = curr_trn->next_trn;
        }
        curr_trn->next_trn = new_trn;
    }

    //inserting the right info in the new account
    new_trn->from_acc = search(root, name_1);
    new_trn->to_acc = search(root, name_2);
    new_trn->ammount = ammount;
    new_trn->next_trn = NULL;
    if(out)
        printf("Inserted |%s|->%d->|%s|\n", (new_trn->from_acc)->name, new_trn->ammount, (new_trn->to_acc)->name);
    return;
}

void delete_trn(Root *root, char* name_1, char* name_2, int ammount){
    //check if an accounts exist
    if(search(root, name_1)==NULL){
        printf("|%s| does not exist - abort-l;\n", name_1);
        return;
    }
    if(search(root, name_2)==NULL){
        printf("|%s| does not exist - abort-l;\n", name_2);
        return;
    }
    Transfer *curr_trn = root->trn_begin;
    //if the transfer is the first transfer
    if((curr_trn->from_acc==search(root, name_1)) && (curr_trn->to_acc==search(root, name_2))){
        if(ammount!=-1){ //if user has given the ammount of the transfer we want to delete
            if(curr_trn->ammount==ammount){
                printf("Del-vertex |%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
                root->trn_begin = curr_trn->next_trn;
                free(curr_trn);
                return;
            }
        }
        else{  //if not, delete the first transfer
            printf("Del-vertex |%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
            root->trn_begin = curr_trn->next_trn;
            free(curr_trn);
        }
    }
    //if the transfer is not the first transfer
    Transfer *prev_trn = curr_trn;
    curr_trn = curr_trn->next_trn;
    while(curr_trn!=NULL){ //while the transfers list is not in the end
        if((curr_trn->from_acc==search(root, name_1)) && (curr_trn->to_acc==search(root, name_2))){
            if(ammount!=-1){ //if user has given the ammount of the transfer we want to delete
                if(curr_trn->ammount==ammount){
                    printf("Del-vertex |%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
                    prev_trn->next_trn = curr_trn->next_trn;
                    free(curr_trn);
                    return;
                }
            }
            else{  //if not, delete the first transfer you will find
                printf("Del-vertex |%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
                prev_trn->next_trn = curr_trn->next_trn;
                free(curr_trn);
                return;
            }
        }
        prev_trn = curr_trn;
        curr_trn = curr_trn->next_trn;
    }
    printf("|%s|->%d->|%s| does not exist - abort-l;\n", name_1, ammount, name_2);
    return;
}

void delete_acc(Root *root, char* name){
    if(search(root, name)==NULL){
        printf("Node |%s| does not exist - abort-d;\n", name);
        return;
    }

    Transfer *curr_trn = root->trn_begin;
    //delete first all the transfers that include these accounts
    while(curr_trn!=NULL){ //while the transfers list is not in the end
        if(curr_trn->from_acc==search(root, name)){
            delete_trn(root, name, (curr_trn->to_acc)->name, (curr_trn->ammount));
        }
        else if(curr_trn->to_acc==search(root, name)){
            delete_trn(root, (curr_trn->from_acc)->name, name, (curr_trn->ammount));
        }
        curr_trn = curr_trn->next_trn;
    }

    Account *curr_acc = root->acc_begin;
    //if the account is the first account
    if(strcmp(curr_acc->name, name)==0){
        root->acc_begin = curr_acc->next_acc;
        printf("Deleted |%s|\n", curr_acc->name);
        free(curr_acc);
        return;
    }

    Account *prev_acc = curr_acc;
    curr_acc = curr_acc->next_acc;
    //if the account is not the first account
    do{
        if(strcmp(curr_acc->name, name)==0){
            prev_acc->next_acc = curr_acc->next_acc;
            printf("Deleted |%s|\n", curr_acc->name);
            free(curr_acc);
            return;
        }
        else{
            prev_acc = curr_acc;
            curr_acc = curr_acc->next_acc;
        }
    }while(curr_acc!=NULL); //while the accounts list is not in the end
}

void modify(Root *root, char* name_1, char* name_2, int old_ammount, int new_ammount){
    if(search(root, name_1)==NULL){
        printf("|%s| does not exist - abort-m;\n", name_1);
        return;
    }
    if(search(root, name_2)==NULL){
        printf("|%s| does not exist - abort-m;\n", name_2);
        return;
    }

    Transfer* curr_trn = (Transfer*)malloc(sizeof(Transfer));
    curr_trn = root->trn_begin;

    while(curr_trn!=NULL){ //while the transfers list is not in the end
        if((curr_trn->from_acc==search(root, name_1)) && (curr_trn->ammount==old_ammount) && (curr_trn->to_acc==search(root, name_2))){
            curr_trn->ammount=new_ammount;
            printf("Del-vertex |%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
            return;
        }
        else{
            curr_trn = curr_trn->next_trn;
        }
    }

    printf("|%s|->%d->|%s| does not exist - abort-m;\n", name_1, old_ammount, name_2);
    return;
}

void receiving(Root *root, char* name){
    if(search(root, name)==NULL){
        printf("|%s| does not exist - abort-r;\n", name);
        return;
    }
    Transfer* curr_trn = (Transfer*)malloc(sizeof(Transfer));
    curr_trn = root->trn_begin;
    bool has_trn = false;
    while(curr_trn!=NULL){ //while the transfers list is not in the end
        if(strcmp((curr_trn->to_acc)->name, name)==0){
            if(has_trn==false){
                printf("Rec-edges |%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
                has_trn = true;
            }
            else{
                printf("|%s|->%d->|%s|\n", (curr_trn->from_acc)->name, curr_trn->ammount, (curr_trn->to_acc)->name);
            }
        }
        curr_trn = curr_trn->next_trn;
    }
    if(has_trn==false){
        printf("No-rec-edges %s\n", name);
    }
    return;
}

void circlefind(Root *root, char *name){
    Account *cycle_acc = search(root, name);
    if(cycle_acc==NULL){
        printf("|%s| does not exist - abort-c;\n", name);
        return;
    }
    char for_print[(MAX_ACC_LENG+3)*(count_accounts(root))];
    strcpy(for_print,"\0");
    bool flag = false;
    int x=0;
    // run the recursive function to find all the paths
    printf("Cir-found ");
    recursive(root, cycle_acc, cycle_acc, for_print, &flag, -1, "", &x, -1);
    if(!flag)
        printf("No-circle-found |%s|\n", name);
    return;
}

void findcircles(Root *root, char *name, int min){
    if(search(root, name)==NULL){
        printf("|%s| does not exist - abort-f;\n", name);
        return;
    }
    char for_print[(MAX_ACC_LENG+3)*(count_accounts(root))];
    strcpy(for_print,"\0");

    bool flag = false;
    int x=0;
    printf("Cir-found ");
    f_recursive_f(root, search(root, name), search(root, name), for_print, &flag, min, name, &x, -1);
    if(!flag){
        printf("No-circle-found involving |%s| %d\n", name, min);
    }
    return;
}

void traceflow(Root *root, char *from_acc_name, char *to_acc_name, int length){
    Account *from_acc = search(root, from_acc_name);
    if(from_acc==NULL){
        printf("|%s| does not exist - abort-l;\n", from_acc_name);
        return;
    }
    Account *to_acc = search(root, to_acc_name);
    if(to_acc==NULL){
        printf("|%s| does not exist - abort-l;\n", to_acc_name);
        return;
    }
    char for_print[(MAX_ACC_LENG+3)*(count_accounts(root))];
    strcpy(for_print,"\0");
    bool flag = false;
    int x=0;
    // run the recursive function to find all the paths
    printf("Tra-found ");
    recursive(root, search(root, from_acc_name), search(root, to_acc_name), for_print, &flag, -1, "", &x, length);
    if(!flag)
        printf("No-trace from |%s| to |%s|\n", from_acc_name, to_acc_name);
    return;
}

void exiting(Root *root, char* output){

    if(output[0]!='\0'){
        FILE *fp = fopen(output,"w+");
        if(fp==NULL){
            printf("Problem writing the graph in to the output file\n");
            return;
        }
        Account *curr_acc = root->acc_begin;
        Transfer *curr_trn = root->trn_begin;
        while(curr_acc!=NULL){
            fprintf(fp, "|%s|\n", curr_acc->name);
            curr_trn = root->trn_begin;
            while(curr_trn != NULL){
                if(strcmp(curr_acc->name, (curr_trn->from_acc)->name)==0){
                    fprintf(fp, "  -%d->|%s|\n", curr_trn->ammount, (curr_trn->to_acc)->name);
                }
                curr_trn = curr_trn->next_trn;
            }
            fprintf(fp, "\n");
            curr_acc = curr_acc->next_acc;
        }
        fclose(fp);
    }
    printf("exit program\n");

    return;
}
