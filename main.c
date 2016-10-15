#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
//
// Created by Cem Yeniceri on 13/10/16.
//

#define STACK_MAX 100
typedef struct Stack {
    char s[STACK_MAX];
    int top;
}Stack;

int is_full(Stack *st);
int is_empty(Stack *st);
void push(Stack *st, char item);
char pop(Stack *st);
void remove_all_elements(Stack *st);
int is_array_size_compatible(char arr[], int r, int t);
Stack *move_array_to_stack(char arr[]);
Stack *move_stack_to_stack(Stack *src, int n);
Stack *create_stack();
int is_stack_compatibleIter(Stack *st);
int compare_stack_to_stack(Stack *st1, Stack *st2, int n);
int is_stack_compatibleRecHelper(Stack *st, int isCompatible);
int is_stack_compatibleRec(Stack *st);


int is_full(Stack *st) {
    if (st ->top >= strlen(st->s) - 1)
        return 0;// full
    else
        return 1; // available
}

int is_empty(Stack *st) {
    if (st->top == -1)
        return 0; //true
    else
        return 1;//false
}

void push(Stack *st, char item) {
    st->top++;
    st->s[st->top] = item;
}

char pop(Stack *st) {
    char item;
    item = st->s[st->top];
    st->top--;
    return (item);
}

void remove_all_elements(Stack *st) {
    st->top = -1;
}

static int r;
static int t;

int is_array_size_compatible(char arr[], int r, int t){

    int n = strlen(arr);
    if(n%(r+t)==0)
        return 0;
    else
        return 1;
}

Stack *move_array_to_stack(char arr[]){

    Stack *newStack = create_stack();

    int count = 1;
    for (int i = 0; i < strlen(arr); ++i) {

        if(count<=r)
            push(newStack, arr[i]);

        if(count%(r+t)==0)
            count=0;

        count++;
    }
    return newStack;
}

Stack *move_stack_to_stack(Stack *src, int n){

    Stack *target = create_stack();

    for (int i = 0; i < n; ++i) {
        push(target, pop(src));
    }
    return target;
}

Stack *create_stack(){
    Stack *newStack;
    newStack = malloc(sizeof(struct Stack));
    newStack->top=-1;
    newStack->s[0] = '\0';
    return newStack;
}

int compare_stack_to_stack(Stack *st1, Stack *st2, int n){
    int isCompatible = 0;
    for (int i = 0; i < n; ++i) {
        if(pop(st1)!= pop(st2)){
            isCompatible = 1;
            break;
        }
    }
    return isCompatible;
}

int is_stack_compatibleIter(Stack *st){

    int isCompatible = 0;

    while(is_empty(st)==1 && st->top != r-1){
        Stack *s2 = move_stack_to_stack(st, r);
        if(compare_stack_to_stack(st, s2, r)==1){
            isCompatible = 1;
            break;
        }
    }
    return isCompatible;
}

int is_stack_compatibleRec(Stack *st){

    return is_stack_compatibleRecHelper(st, 0);
}

int is_stack_compatibleRecHelper(Stack *st, int isCompatible){

    if((is_empty(st)==1 && st->top != r-1) || isCompatible==1)
        return isCompatible;
    else{
        Stack *s2 = move_stack_to_stack(st, r);
        if(compare_stack_to_stack(st, s2, r)==1){
            isCompatible = 1;
            return is_stack_compatibleRecHelper(st, isCompatible);
        }
    }
}



int main(){

    char str[100];

    printf("Please determine r: ");
    scanf("%d", &r);

    printf("Please determine t: ");
    scanf("%d", &t);

    printf("Enter any string up to 100 character \n");
    scanf("%s", &str);

    int isSizeCompatible = is_array_size_compatible(str, r, t);

    if(isSizeCompatible != 0){
        printf("Array size is not compatible");
        return 0;
    }

    Stack *s1ForIter = move_array_to_stack(str);
    Stack *s2ForRec = move_array_to_stack(str);

    if(is_stack_compatibleIter(s1ForIter) == 0)
        printf("Input is compatible for encryption --(Iter)..\n");
    else
        printf("Input is not compatible for encryption --(Iter)..\n");

    if(is_stack_compatibleRec(s2ForRec) == 0)
        printf("Input is compatible for encryption --(Rec)..\n");
    else
        printf("Input is not compatible for encryption --(Rec)..\n");

    return 0;
}