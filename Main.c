#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StrList.h"

int main(){
    StrList* list = StrList_alloc();
    int num;
    scanf("%d",&num);
    while(num!=0){
        if (num == 1) {
        int numOfWords;
        scanf("%d", &numOfWords);
        for (int i = 0; i < numOfWords; i++) {
            char *str = (char *)malloc(sizeof(char)*100);
            scanf("%s", str);
            StrList_insertLast(list, str);
        }
        } else if(num==2){
            int index;
            scanf("%d", &index);
            char str[100];
            scanf("%s", str);
            StrList_insertAt(list, str, index);
        } else if(num==3){
            StrList_print(list);
            printf("\n");
        }else if(num==4){
            printf("%ld",StrList_size(list));
            printf("\n");
        } else if(num==5){
            int index;
            scanf("%d", &index);
            StrList_printAt(list,index);
            printf("\n");
        }else if(num==6){
            printf("%d", StrList_printLen(list));
            printf("\n");
        } else if(num==7){
            char str[100];
            scanf("%s", str);
            printf("%d",StrList_count(list, str));
            printf("\n");
        } else if(num==8){
            char str[100];
            scanf("%s", str);
            StrList_remove(list, str);
        } else if(num==9){
            int index;
            scanf("%d", &index);
            StrList_removeAt(list, index);
        } else if(num==10){
            StrList_reverse(list);
        }  else if(num==11){
            StrList_free(list);
            list = StrList_alloc();
        } else if(num==12){
            StrList_sort(list);
        } else if(num==13){
            printf("%s", StrList_isSorted(list) ? "true" : "false");
            printf("\n");
        }
        scanf("%d",&num);
    }
    StrList_free(list);
    return 0;
}
