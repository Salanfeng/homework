#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#define maxN 1000
char word[maxN][35];
int is_letter(char x);
char to_upper(char x);
int comp(const void *p1,const void *p2) {
	return strcmp((char *)p1,(char *)p2);
}
int main()
{
    FILE *sin,*sout;
    sin=fopen("article.txt", "r");
    char temp_c;
    temp_c=fgetc(sin);
    int pos=0;
    int word_pos=0;
    int flag=1;
    while(temp_c!=EOF){
        if(is_letter(temp_c)){
            flag=0;
            temp_c=to_upper(temp_c);
            word[pos][word_pos]=temp_c;
            word_pos++;
        }
        else{
            if(flag!=1)
                pos++;
            flag=1;
            word_pos=0;
        }
        temp_c=fgetc(sin);
    }
    qsort(word,pos,sizeof(word[0]),comp);
    for(int i=0;i<pos;i++){
        int num=1;
        int look=i+1;
        while(strcmp(word[i],word[look])==0){
            num++;
            look++;
        }
        printf("%s %d\n",word[i],num);
        i=look-1;
    }
    return 0;
}

int is_letter(char x)
{
    if(x>='a'&&x<='z') return 1;
    else if(x>='A'&&x<='Z') return 1;
    else return 0;
}

char to_upper(char x)
{
    if(x>='A'&&x<='Z') return x+32;
    else return x;
}

