#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StrList.h"

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

void insertWordsToList(StrList* list, char* input, int numWords) {
    char* token = strtok(input, " ");
    int count = 0;
    while (token != NULL && count < numWords) {
        StrList_insertLast(list, token);
        token = strtok(NULL, " ");
        count++;
    }
}

int main(){
    StrList* list = StrList_alloc();
    int num;
    scanf("%d",&num);
    while(num!=0){
        if (num == 1) {
        int numOfWords;
        scanf("%d", &numOfWords);
        char* str = inputString(stdin, 100);
        insertWordsToList(list, str, numOfWords);
        } else if(num==2){
            int index;
            scanf("%d", &index);
            char* str = inputString(stdin, 100);
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
            char* str = inputString(stdin, 100);
            printf("%d",StrList_count(list, str));
            printf("\n");
        } else if(num==8){
            char* str = inputString(stdin, 100);
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
