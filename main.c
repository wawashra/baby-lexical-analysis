#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define true 1
#define false 0
#define MAXCHAR 1024
void loodReservedWord();
void printReservedWord();
void printFinallToken();
void loodSpecialSymbol();
void printSpecialSymbol();
void loodOperators();
void printOperators();
int isLangReservedWord(char*);
int isSpecialSymbol(char*);
int isNumber(char*);
int isRNumber(char*);
int isSpaceToken(char*);
int isLangOperators(char);
int isLangOperators2(char,int);
int isAlphabetOrDigt(char);
void lexical_Analyzer();
void lexical_Analyzer2();
int getSpecialSymbolIndex(char*);
int getLangReservedWordIndex(char*);

typedef struct
{
    char name[25];
    int id;
} reservedWord;

typedef struct
{
    char symbol[2];
    int id;
} specialSymbol;

typedef struct
{
    char OPERATORS[1];
    int id;
} operators;

typedef struct
{
    char tokenName[128];
    int id;
    char type[25];
} token;

reservedWord reserved_Word[64];
int rwi = 0;

specialSymbol special_Symbol[32];
int ssi = 0;

operators operator_Word[32];
int owi = 0;

token listToken[256];
int lti = 0;


int lai = 0;
int id = 100;
int main()
{
    loodReservedWord();
    loodSpecialSymbol();
    loodOperators();

    lexical_Analyzer2();

    printFinallToken();

    //printOperators();
    //printReservedWord();
    //printOperators();
    //printSpecialSymbol();
    return 0;
}

void lexical_Analyzer2()
{
    FILE *fp;
    char* filename = "input.txt";
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
    }
    char theGetChar;
    char theToken[32];
    char tmp[5];
    while((theGetChar = fgetc(fp)) != EOF)
    {
        if(isLangOperators(theGetChar) == 1 && theGetChar != '.')
        {
            tmp[1]=theGetChar;
            tmp[2]='\0';
            theToken[lai] = '\0';
            if(isLangReservedWord(theToken) == 1)
            {
                strcpy(listToken[lti].tokenName,theToken);
                listToken[lti].id = getLangReservedWordIndex(theToken);
                strcpy(listToken[lti].type,"Reserved Word");
                lti++;
            }
            else if(isSpecialSymbol(theToken) == 1)
            {
                strcpy(listToken[lti].tokenName,theToken);
                listToken[lti].id = getSpecialSymbolIndex(theToken);
                strcpy(listToken[lti].type,"Special Symbol");
                lti++;

            }
            else if(isNumber(theToken) == 1)
            {
                strcpy(listToken[lti].tokenName,theToken);
                listToken[lti].id = 200;
                strcpy(listToken[lti].type,"Int Number");
                lti++;
            }
            else if(isRNumber(theToken))
            {
                strcpy(listToken[lti].tokenName,theToken);
                listToken[lti].id = 201;
                strcpy(listToken[lti].type,"Real Number");
                lti++;
            }
            else if(isSpaceToken(theToken) == 0)
            {
                strcpy(listToken[lti].tokenName,theToken);
                listToken[lti].id = id;
                strcpy(listToken[lti].type,"User defined");
                lti++;
            }
            if(isSpecialSymbol(tmp) == 1)
            {
                int tmpI=lti -1;
                if(isSpecialSymbol(listToken[tmpI].tokenName) ==1)
                {
                    strcpy(listToken[tmpI].tokenName,tmp);
                    listToken[tmpI].id = getSpecialSymbolIndex(tmp);
                    strcpy(listToken[tmpI].type,"Special Symbol");
                }
            }
            else if(theGetChar != ' '&& isLangOperators2(tmp[0],1) == 0 )
            {

                tmp[0] = theGetChar;
                tmp[1] = '\0';
                strcpy(listToken[lti].tokenName,tmp);
                listToken[lti].id = getSpecialSymbolIndex(tmp);
                strcpy(listToken[lti].type,"Special Symbol");
                lti++;
            }
            lai=0;
        }
        else if((isAlphabetOrDigt(theGetChar) == 1))
        {
            theToken[lai++] = theGetChar;
        }
        tmp[0] = theGetChar;
    }
    theToken[lai-1]='\0';
    strcpy(listToken[lti].tokenName,theToken);
    listToken[lti].id = id;
    strcpy(listToken[lti].type,"User defined");
    lti++;

    listToken[lti].tokenName[0] = '.';
    listToken[lti].tokenName[1] = '\0';
    listToken[lti].id = getSpecialSymbolIndex(listToken[lti].tokenName);
    strcpy(listToken[lti].type,"Special Symbol");
    lti++;
    fclose(fp);
}


void loodReservedWord()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "ReservedWord.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
    }

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        char* token = strtok(str, "#");
        strcpy(reserved_Word[rwi].name,token);
        token = strtok(NULL, "#");
        reserved_Word[rwi].id = atoi(token)+100;
        rwi++;
    }
    fclose(fp);
}

void printReservedWord()
{
    int i;
    for(i = 0; i < rwi ; i++)
    {
        printf("%s --- %d\n",reserved_Word[i].name,reserved_Word[i].id);
    }
}


void loodSpecialSymbol()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "SpecialSymbol.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
    }
    special_Symbol[ssi].symbol[0]='#';
    special_Symbol[ssi].id = 0;
    ssi++;

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        char* token = strtok(str, "#");
        strcpy(special_Symbol[ssi].symbol,token);
        token = strtok(NULL, "#");
        special_Symbol[ssi].id = atoi(token)+50;
        ssi++;
    }
    fclose(fp);
}


void printSpecialSymbol()
{
    int i;
    for(i = 0; i < ssi ; i++)
    {
        printf("%s --- %d\n",special_Symbol[i].symbol,special_Symbol[i].id);
    }
}

void loodOperators()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "Operator.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
    }

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        char* token = strtok(str, "#");
        strcpy(operator_Word[owi].OPERATORS,token);
        token = strtok(NULL, "#");
        operator_Word[owi].id = atoi(token);
        owi++;
    }
    fclose(fp);
}
void printOperators()
{
    int i;
    for(i = 0; i < owi ; i++)
    {
        printf("%s --- %d\n",operator_Word[i].OPERATORS,operator_Word[i].id);
    }
}

void printFinallToken()
{
    int i;
    printf("|Index\t\t|Token\t\t|Type\t\t|Id\n");
    for(i = 0; i < lti ; i++)
    {
        printf("-------------------------------------------------------------------------\n");
        printf("|%d|\t\t|%s|\t\t|%s|\t\t|%d|\n",i,listToken[i].tokenName,listToken[i].type,listToken[i].id);
    }
    printf("-------------------------------------------------------------------------\n");

}

int isLangReservedWord(char* word)
{
    int i;
    for(i = 0 ; i < rwi; i++)
    {
        if(strcmp(word,reserved_Word[i].name) == 0)
            return true;
    }
    return false;
}

int isLangOperators(char word)
{
    int i;
    for(i = 0 ; i < rwi; i++)
    {
        if(operator_Word[i].OPERATORS[0] == word)
            return true;
    }
    return false;
}

int isLangOperators2(char word,int K)
{
    int i;
    for(i = K ; i < rwi; i++)
    {
        if(operator_Word[i].OPERATORS[0] == word)
            return true;
    }
    return false;
}

int isSpecialSymbol(char word[])
{
    int i;
    for(i = 0 ; i < ssi; i++)
    {
        if(strcmp(special_Symbol[i].symbol,word) == 0)
            return true;
    }
    return false;
}

int isSpaceToken(char word[])
{
    int wl = strlen(word);
    if(wl == 0)
        return true;
    int i;
    for(i = 0 ; i < wl; i++)
    {
        if(isspace(word[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

int isNumber(char word[])
{
    int wl = strlen(word);
    if(wl == 0)
        return false;
    int i;
    for(i = 0 ; i<wl; i++)
    {
        if(isdigit(word[i]) ==0)
            return false;
    }
    return true;
}

int isRNumber(char word[])
{
    int wl = strlen(word);
    if(wl == 0)
        return false;
    int i;
    for(i = 0 ; i<wl; i++)
    {
        if(isdigit(word[i]) ==0)
        {
            if(word[i] != '.')
                return false;

        }
    }
    return true;
}
int isAlphabetOrDigt(char word)
{
    if(word >= 97 && word <= 122)
    {
        return true;
    }
    else if(word >= 65 && word <= 90)
    {
        return true;
    }
    else if(word >= 48 && word <= 57)
    {
        return true;
    }
    else if(word == '.')
    {
        return true;
    }
    return false;
}

int getSpecialSymbolIndex(char word[])
{
    int i;
    for(i = 0 ; i < ssi; i++)
    {
        if(strcmp(special_Symbol[i].symbol,word) == 0)
            return i;
    }
    return -1;
}

int getLangReservedWordIndex(char word[])
{
    int i;
    for(i = 0 ; i < rwi; i++)
    {
        if(strcmp(reserved_Word[i].name,word) == 0)
            return i;
    }
    return -1;
}
