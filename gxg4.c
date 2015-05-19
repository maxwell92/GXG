//程序用来统计某个文件里的词频，并将出现频率高于50%的单词输出

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define BUFSIZE 1000

typedef struct wd{
    char *content;
    int count;
    float freq;
    struct wd *next;
}WORDS;


int CheckRepeat(char *src, int len,WORDS *words) {

    WORDS *ptr;
    ptr = words;

    while(NULL != ptr->next) {
        if(len == strlen(ptr->content)) {
            if(!strcmp(ptr->content, src)) {
                ptr->count++;
                return 1;
            }
            else {
                ptr = ptr->next;
            }
        }
        else {
            ptr = ptr->next;
        }
   }
    return 0;
}

int main() {

    FILE *fp;
    WORDS *words,*nwords;
    char *p;
    int len = 0;
    char *buf,*tmp;

    int sum = 0; //the sum of all words
    int cntWords=0,cntChar=0;

    words = (WORDS *)malloc(sizeof(WORDS));
    words->next = NULL;
    words->count = 0;
    words->content = NULL;

    p = (char *)malloc(sizeof(char));
    buf = (char *)malloc(BUFSIZE * sizeof(char));

    fp = fopen("text.txt","r");

    if(NULL == fp) {
        printf("file open error! please check your file!\n");
        exit(-1);
    }

    while(1) {
        if(NULL == fgets(buf,BUFSIZE,fp)) {
            break;
        }
        p = buf;

        while(1) {
            if('\0' == *p)
                break;
            if((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9')) {
                cntWords++;
                p++;
            }
            else {
                cntChar++;
                if(cntWords != 0) {
                      len = cntWords;
                      tmp = (char *)malloc(len*sizeof(char));
                      memcpy(tmp,buf,len);
                    if(!CheckRepeat(tmp,len,words)) {
                        memset(tmp,'\0',len);
                        nwords = (WORDS *)malloc(sizeof(WORDS));
                        nwords->content = (char *)malloc(len * sizeof(char));
                        nwords->next = NULL;
                        nwords->count = 0;
                        nwords->freq = 0.0;
                        memcpy(nwords->content,buf,len);
                        nwords->count++;
                        nwords->next = words;
                        words = nwords;
                    }
                    cntWords = 0;
                }
                p++;
                buf = p;
            }
        }
    }

   WORDS *ptr;
   ptr = words;
   while(NULL != ptr->next) {
    sum += ptr->count;
    ptr = ptr->next;
   }

   printf("the total number of words is %d \n",sum);

    ptr = words;
    while(NULL != ptr->next) {
    //printf("the count of word \"%s\" is %d\n",ptr->content, ptr->count);
    ptr->freq = ptr->count  * 1.0/ sum;
    printf("the frequent of word \"%s\" is %.2f\n",ptr->content,ptr->freq);
    ptr = ptr->next;
   }

    return 0;
}

