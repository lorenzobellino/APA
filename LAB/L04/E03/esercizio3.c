#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

char * cerca_regexp(char *src, char *regexp);

int main(int argc, char *argv){

FILE *f;
char regexp[128], line[256], final_regexp[56];
char *c = NULL;
int i;

printf("inserisci regexp\n");
scanf("%s", regexp);
f=fopen("testo.txt","r");
if(f==NULL) return 0;
fgets(line,256,f);
fclose(f);

for(i=0;i<strlen(line) && c==NULL;i++){
    c = cerca_regexp(line+i,regexp);
}
if(c==NULL) printf("nontrovatonulla\n");
else{
    printf("\n\nmem_index |0x%x| , string | %s |\n\n\n",c,c);
}
return 0;
}

char * cerca_regexp(char *src, char *regexp){
    char *c=src;
if(*regexp!='\0'){
    switch(*regexp){
        case '.':
            c = cerca_regexp((c+1), (regexp+1));
        break;
        
        case '[':
            if(*(regexp+1)=='^'){
                regexp+=2;
                while(isalpha(*regexp) && *c!=*regexp){
                (regexp++);
                }
                if((isalpha(*regexp))) return NULL;
                else c = cerca_regexp(c+1,regexp+1);
            }
        else{
            regexp++;
            while(isalpha(*regexp) && *c!=*regexp){
                (regexp++);
            }
            if(!(isalpha(*regexp))) return NULL;
            else {
                while(*regexp != ']'){
                    (regexp++);
                }
                c = cerca_regexp(c,regexp);
            }
        }
        break;

        case '\\':
            if(islower(*(regexp+1))&&islower(*(c))) c = cerca_regexp(c+1,regexp+2);
            else if(isupper(*(regexp+1))&&isupper(*(c))) c = cerca_regexp(c+1,regexp+2);
            else return NULL;
        break;
        
        case ']':
            c = cerca_regexp((c+1), (regexp+1));
        break;
        
        default:
            if(*c == *regexp) c = cerca_regexp((c+1), (regexp+1));
            else return NULL;
        break;
    
    } 
}
    
if (c==NULL) return NULL;
else return src;
}