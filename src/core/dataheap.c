#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dataheap.h"

char * get_jid(char *str){

        regex_t regex;
        regmatch_t pmatch;
        int reti;
        
        reti = regcomp(&regex,"[a-z]+@[a-z0-9\\-]+\\.[a-z]{1,5}", REG_EXTENDED);
        if( reti ){ return NULL; }

        reti = regexec(&regex,str, 1, &pmatch, 0);
        if( !reti ){
                int size = pmatch.rm_eo - pmatch.rm_so;
                char *pom = malloc(size+1);
                strncpy (pom, str  ,size);
                pom[size]='\0';
   	        regfree(&regex);
                return pom;
        }
        else if( reti == REG_NOMATCH ){
   	        regfree(&regex);
                return NULL;                
        }
}

void strtrim(char *dest,const char *src){
    for (; *src; src++){
        if (*src != ' '){
            *dest++ = *src;
        }
    }
    *dest = '\0';
}

