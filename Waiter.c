#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DSTACK 2
#define OP1    0
#define OP2    1

int sp[3];
int *stack[3];

void initS(int n) {    
    for (int i=0;i<3;++i) {
        stack[i]= (int *) malloc(sizeof(int)*n);
        sp[i]=0;
    } 
}  

void pushS(int i, int v) {
    stack[i][sp[i]++]=v;    
}

int popS(int i) {    
    return stack[i][--sp[i]];
}


void closeS() {
    for (int i=0;i<3;++i) free(stack[i]);
}

int emptyS(int i) {
    return sp[i]==0;
}

int itemsS(int i) {
    return sp[i];
}

int isPrime(int n) {
    
    
    for (int i=2;i*i<=n;++i) {
        if (n%i==0) return 0;
    } 
    
    
    return 1;
    
    
}

int nextPrime(int n) {
    
    ++n;
    
    while(!isPrime(n))
        ++n;
    
    return n;
}



int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    
    int n, q;
    int i;
    int v;
    int ins, outs, prime;
 
    scanf("%d %d",&n,&q);
    
    int items[q];
    
    initS(n); // init stack
    
    for (i=0;i<n;++i) {
        scanf("%d",&v);
        pushS(0,v); // stack 0
    }
    
    ins=0;
    outs=1;
    prime=2;

    for(i=0;i<q;++i) {
        
        while(!emptyS(ins)) {
            int v= popS(ins);
            if (v%prime==0) pushS(DSTACK,v); //stack2 
            else pushS(outs,v); 
        }    
        
        items[i]=itemsS(DSTACK);
        
        // SWAP stacks
        int tmp=ins;
        ins=outs;
        outs=tmp;
        
        prime=nextPrime(prime);
        
        while(!emptyS(DSTACK)) {
            v= popS(DSTACK);
            printf("%dn",v);
        } 
    }
    
    while(!emptyS(ins)) {
        v= popS(ins);
        printf("%dn",v);
    }
    
    closeS();
    
    return 0;
}