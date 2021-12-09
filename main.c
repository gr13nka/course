#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MEM_STEP 5

struct Sentence{
    char* str;
    int size;
};

struct Text{
    struct Sentence **sents;
    int size;
    int n;
};

struct Sentence* readSentence(){
    int size = MEM_STEP;
    int n = 0;
    char temp;
    char* buf = malloc(size * sizeof(char));
    do{
        if (n >= size - 2){
            buf = realloc(buf, size + MEM_STEP);
            size = size + MEM_STEP;
        }           
        temp = getchar();
        buf[n] = temp;
        n++;
    }while(temp != '.' && temp != ';' && temp != '?' && temp != '!');
    buf[n] = '\0';
    
    // sending sentence
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence->str = buf;
    sentence->size = size;
    return sentence;
}

struct Text readText(){
    int size = MEM_STEP;
    struct Sentence** text = malloc(size * sizeof(struct Sentence*));
    int n = 0;
    int nlcount = 0;
    struct Sentence* temp;
    do{
    temp = readSentence();
    
    if (strchr(temp->str, '!') != NULL)
        nlcount++;
    else{
        text[n] = temp;
        n++;
        if (n >= size){
            size = size + 5;
            text = realloc (text, size * sizeof(struct Sentence*));
        }
    }
}while(nlcount < 1);

struct Text txt;
txt.size = size;
txt.sents = text;
txt.n = n;
free(temp);
return txt;
}

void sentProc(struct Sentence* sent, int k, int m){
int len = strlen(sent->str);
char *cur_str = sent->str;
memmove(cur_str+k, cur_str+k+m, len-m-k+1);
}

//удаляет лишнее 
struct Text cleaning(struct Text text){
    for (int i = 0; i < text.n; i++){
        while ((text.sents[i]->str[0] == ' ')||(text.sents[i]->str[0] == '\t')||(text.sents[i]->str[0] == '\n'))
            sentProc(text.sents[i], 0, 1);
    }
return text;
}

int cnt_q(struct Text text){
int cnt = 0;
for (int i = 0; i < text.n; i++){
    if (strchr((text.sents[i]->str), '?') != NULL)
        cnt++;
}
return cnt;
}

struct Text q_del(struct Text text){
    int i = text.n;
    while (i > 0){
        i = i - 1;
        if (strchr((text.sents[i]->str), '?') != NULL){
            int j = i;
            while(j < text.n-1){
                memmove(text.sents[j], text.sents[j+1], 8);
                j++;
            }
   }
}
return text;
}

int main(){
struct Text text = readText();
text = cleaning(text);

int before = text.n; 
int count = cnt_q(text);
text = q_del(text);
int after = (text.n = text.n - count);

for (int i = 0; i < after; i++)
    puts(text.sents[i]->str);

printf("Dragon flew away!\n");
printf("Количество предложений до %d и количество предложений после %d\n", before, after);
return 0;
}


