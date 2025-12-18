#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct trieNode{
    struct trieNode **dic;
    int lw;
}tNode;

tNode *root;

int addStr(char *s){
    tNode *t;
    char c;
    t=root;
    while(*s){
        c = *s - 'a';
        s++;
        if(t->dic == NULL) t->dic=(tNode**)calloc(10,sizeof(tNode));
        if(t->dic[c] && t->dic[c]->lw) return 1;
        if((*s==0)&&(t->dic[c]!=NULL)) return 1;
        if(t->dic[c]==NULL) t->dic[c]=(tNode*)calloc(1,sizeof(tNode*));
        if(*s==0) t->dic[c]->lw=1;
        else t=t->dic[c];
    }
    return 0;
}

int main() {
    int n,m=0;
    char str[61];
    root=(tNode*)calloc(1,sizeof(tNode));
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%s",str);
        m=addStr(str);
        if(m) break;
    }
    if(m) printf("BAD SETn%sn",str);
    else printf("GOOD SETn");
    return 0;
}