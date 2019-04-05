#include "functions.h"

int main(int argc, char *argv[]){
    //printf("\n- Program started\n\n");
    //root has the first structs of accounts list and transfers list
    Root root;
    root.acc_begin = NULL;
    root.trn_begin = NULL;
    //check for wrong-format parameters
    if( (argc==2) || (argc==4) ){
        printf("wrong parameters\n");
        return 0 ;
    }
    //check for input parameters
    char *output = "\0";
    if(argc!=1){
        if((strcmp(argv[1], "-i")==0)){
            if ((load_input_file(&root, argv[2], MAX_ACC_LENG)==false)){
                return 0;
            }
            if(argc>4){
                if((strcmp(argv[1], "-i")==0) && (strcmp(argv[3], "-i")!=0)){
                    output = argv[4];
                }
            }
        }
        else if((strcmp(argv[1], "-i")!=0)){
            output = argv[2];
            if(argc>4){
                if(strcmp(argv[3], "-i")==0){
                    if (load_input_file(&root, argv[4], MAX_ACC_LENG)==false){
                        return 0;
                    }
                }
            }
        }
        else{
            printf("error with the parameters\n");
            return 0;
        }
    }
    int max_cmd_leng = 2+2*MAX_ACC_LENG;
    char cmd[max_cmd_leng];
    bool flag;
    do{
        fflush(stdin);
        fgets(cmd, max_cmd_leng, stdin); //cmd = user input
        flag = call_cmd(&root, cmd, max_cmd_leng, output);
        printf("\n");
    }while(flag);

    //freeing the memory
    Transfer *prev_trn;
    Transfer *curr_trn;
    curr_trn=root.trn_begin;
    while(curr_trn!=NULL){
        prev_trn=curr_trn;
        curr_trn=curr_trn->next_trn;
        free(prev_trn);
    }
    Account *prev_acc;
    Account *curr_acc;
    curr_acc=root.acc_begin;
    while(curr_acc!=NULL){
        prev_acc=curr_acc;
        curr_acc=curr_acc->next_acc;
        free(prev_acc);
    }
    free(curr_trn);
    free(curr_acc);

    return 1;
}
