#include<stdio.h>
#include<stdlib.h>
typedef long long unsigned U;
typedef unsigned u;
u X[111111],Y[111111],W[111111],N[111111],l;
u B[111111],S[111111],D[111111],Q[222222],Qi;
U V[111111];
int F(const void*x,const void*y)
{
    if(W[*(u*)x]>W[*(u*)y])return 1;
    if(W[*(u*)x]<W[*(u*)y])return-1;
    return 0;
}
u Z(u v)
{
    u lo=0,hi=l,mi;
    while((mi=(lo+hi)>>1)>lo)
    {
        if(B[mi]>v)hi=mi;
        else lo=mi;
    }
    return lo;
}
int main()
{
    u n,q,i=-1,j,k,x,y;U r=0;l=1;
    for(scanf("%u%u",&n,&q);++i<n-1;S[D[N[i]=i]=i]=1)scanf("%u%u%u",X+i,Y+i,W+i);
    for(;i<=n;W[i++]=-1)S[D[N[i]=i]=i]=1;
    qsort(N,n-1,sizeof(u),F);
    for(i=-1;(k=W[N[++i]])!=-1u;)
    {
        for(x=X[N[i]];D[x]!=x;x=D[x])Q[Qi++]=x;
        for(y=Y[N[i]];D[y]!=y;y=D[y])Q[Qi++]=y;
        r+=S[x]*(U)S[y];
        if(x>y){D[x]=y;S[y]+=S[x];x=y;}
        else{D[y]=x;S[x]+=S[y];}
        while(Qi)D[Q[--Qi]]=x;
        if(k!=W[N[i+1]]){B[l]=k;V[l++]=r;}
    }
    while(q--)
    {
        scanf("%u%u",&i,&j);
        x=Z(i);y=Z(j);
        if(B[x]==i)--x;
        printf("%llun",V[y]-V[x]);
    }
    return 0;
}