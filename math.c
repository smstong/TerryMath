/******************************************************************************
 * Kids' math 
 *
 *
 * ***************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * argv[1] : type of math
 *         -   a+b
 *         -   a-b
 *         -   a+b+c
 *         -   a-b-c
 *         -   a+b-c
 *         -   a-b+c
 *         -  other: mix of the above
 *
 * argv[2] : difficulty
 *         -n: a,b,c <=n, like:
 *             - 10: a,b,c <=10
 *             - 20: a,b,c <=20
 * */

#define MAX_N (5)                  /* the max numbers involved */
#define RAND_NUMBER(max) ((int)( ((float)rand()) / (RAND_MAX) * (max) ))
static char g_signs[MAX_N+1];      /* decoded g_signs, g_signs[0]==0 means mix */
static int g_difficulty;
static int g_questionCount = 40;   /* total account of questions */

void generate(void);

int main(int argc, char** argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage:\n\t%s type_of_math difficulty\n", argv[0]);
        fprintf(stderr, "Example:\n\t%s a+b-c 20\n", argv[0]);
        fprintf(stderr, "Note:\n\ttype_of_math: a+b, a-b, a+b+c, a-b-c, a+b-c, a-b+c, mix\n");
        fprintf(stderr, "\tdifficulty: 10, 20, ...\n");
        return 1;
    }
    if (validate_exp(argv[1])) {
        g_signs[0] = '\0'; /* assume type = mix */
    }
    int difficulty = atoi(argv[2]);
    if (difficulty < 10 ) {
        difficulty = 10;
    }
    g_difficulty = difficulty;
    generate(); 
    return 0;
}
/* parse like "a+b+c" format */
int validate_exp(char* exp)
{
    char* p = exp;
    int ok = 0;
    int i = 0;
    while(*p){
        if( (*p != ' ')  && 
           (*p != '+') &&
            (*p != '-') &&
            (*p != '\t'))
        {
            ok = 1; 
        }
        
        if((*p == '+') || (*p == '-') ) {
            if (ok == 0) return 1;
            g_signs[i++] = *p; 
            ok = 0;
        }
        if( *(p+1) == '\0' ) {
            if (ok == 0) return 1;
        }
        p++;
    }
    g_signs[i] = '\0';
    return 0;
}

/* print title on top of page */
void print_title(void)
{
    time_t now;
    time(&now);
    struct tm * tmNow = localtime(&now);

    printf("\tTerry's Math Test for %d-%d-%d",
            tmNow->tm_year+1900, tmNow->tm_mon+1, tmNow->tm_mday);
}

void do_generate_one_question(char* signs, int difficulty)
{   
    int number = RAND_NUMBER(difficulty);
    printf("%-3d", number);
    int result = number;
    while(*signs != 0) {

        number = RAND_NUMBER(difficulty);
        int rb = result;
        if( *signs == '+') {
            result += number;
        } else {
            result -= number;
        }
        if(result < 0) {
            result = rb;
            continue;
        }
        printf("%c %-3d", *signs, number);
        signs++;
    }
    printf("=");
    //printf("%3d", result);
}
void generate_one_question(char* signs, int difficulty)
{
    int i = 0;
    if (strlen(signs)==0) {
        //mix
        static char* SIGNS[] = {
            "+",
            "-",
            "++",
            "+-",
            "-+",
            "+"
        };
        int iSigns = RAND_NUMBER(sizeof(SIGNS)/sizeof(SIGNS[0])-1);
        //printf("\n%d:%s\n", iSigns, SIGNS[iSigns]);
        do_generate_one_question(SIGNS[iSigns], difficulty);
    }else{
        do_generate_one_question(signs, difficulty);
    }
}
void generate(void)
{
    int i=0;
    srand(time(NULL));
    print_title();
    printf("\n-----------------------------------------------");
    printf("\n\n");
    for(i=0; i<g_questionCount; i++) {
        generate_one_question(g_signs, g_difficulty);
        if(i%2==1) {
            printf("\n");
        }else{
            printf("\t\t");
        }
    }
}
