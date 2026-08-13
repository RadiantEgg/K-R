// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


// // int main(int argc, char **argv)
// // {
// //     int i;
// //     for (i  = 1; i < argc, i++) {
// //         printf("%s%s", argv[i], (i < argc) ? ' ' : '\n');
// //     }
// //     return 0;
// // }

// // int main(int argc, char **argv)
// // {
// //     while (--argc > 0) {
// //         printf("%s%s", *(++argv), (argc > 0) ? " " : "");
// //     }
// //     printf("\n");
// //     return 0;
// // }

// #define MAXLINE 1000
// // int main(int argc, char **argv)
// // {
// //     char line[MAXLINE];
// //     int found = 0;

// //     if (argc != 2)
// //         printf("Usage: find pattern\n");
// //     else {
// //         while (getline(line, MAXLINE) != 0) 
// //             if (strstr(line, argv[1]) != NULL) {
// //                 printf("%s\n, line");
// //                 found = 1;
// //             }
// //     }
// //     return found;
// // }

// int getline(char *line, int max);

// int main(int argc, char **argv)
// {
//     char line[MAXLINE];
//     long lineno = 0;
//     int c, except = 0, number = 0, found = 0;

//     while (--argc > 0 && (*++argv)[0] == '-') {
//         while (c = *++argv[0]) {
//             switch (c) {
//                 case 'x':
//                     except = 1;
//                     break;
//                 case 'n':
//                     number = 1;
//                     break;

//                 default:
//                     printf("Illegal option\n");
//                     break;
//             }
//         }
//     }  
    
//     if (argc != 1)
//         printf("Usage: find -x -n pattern\n");
//     else {
//         while ((getline(line, MAXLINE)) != 0) {
//             lineno++;
//             if (strstr(line, *argv) != NULL ^ except) {
//                 if (number)
//                     printf("%ld:", lineno);
//                 printf("%s\n", line);
//                 found++;
//             }
//         }
//     }
//     return found;
// }

// #include <stdio.h>
// #include <stdlib.h>

// #define MAXOP 100
// #define NUMBER '0'

// int getop(char *);
// void push(double);
// double pop(void);


// int main()
// {
//     int type;
//     double op2;
//     char s[MAXOP];

//     while((type = getop(s)) != EOF) {
//         switch(type) {
//         case NUMBER:
//             push(atof(s));
//             break;

//         case '+':
//             push(pop() + pop());
//             break;
        
//         case '-':
//             op2 = pop();
//             push(pop() - op2);
//             break;
        
//         }
//     }
// }



// #define MAXVAL 100

// int sp = 0;
// double val[MAXVAL];

// void push(double x)
// {
//     if (sp < MAXVAL)
//         val[sp++] = x;
//     else 
//         printf("val: too many numbers\n");
// }

// double pop(void)
// {
//     if (sp > 0)
//         return val[--sp];
    
//     printf("val: empty\n");
// }

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double x)
{
    if (sp < MAXVAL)
        val[sp++] = x;
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
}


int main(int argc, char **argv)
{
    double op2;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "+") == 0) {
            push(pop() + pop());
        } else if (strcmp(argv[i], "-") == 0) {
            op2 = pop();
            push(pop() - op2);
        } else if (strcmp(argv[i], "*") == 0) {
            push(pop() * pop());
        } else if (strcmp(argv[i], "/") == 0) {
            op2 = pop();
            if (abs(op2) < 1e-15) {
                printf("invalid divider\n");
                return 1;
            }
            push(pop() / op2);
        } else {
            push(atof(argv[i]));
        }
    }
    printf("%f\n", pop());
    
    return 0;
}