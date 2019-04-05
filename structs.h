#define MAX_ACC_LENG 50

typedef struct Root{
    struct Account* acc_begin;
    struct Transfer* trn_begin;
} Root;

typedef struct Account{
    char name[MAX_ACC_LENG];
    struct Account* next_acc;
    bool visited;
} Account;

typedef struct Transfer{
    struct Account* from_acc;
    int ammount;
    struct Account* to_acc;
    struct Transfer* next_trn;
    bool visited;
} Transfer;
