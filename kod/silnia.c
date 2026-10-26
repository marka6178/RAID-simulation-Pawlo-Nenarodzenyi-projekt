#include <stdio.h>

int silnia(int a,int i,int sum){
    if(a >= i){
        sum *= i;
        printf("%d ",sum);
        return silnia(a,i+1,sum);
    }
    else{
        return sum;
    }
}

int main(){
    int n = silnia(5,1,1);
    printf("%d", silnia(5,1,1));
    return 0;
}