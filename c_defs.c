/**********************************************************************
 * c_defs.c
 *
 * Compute C language-specific constructs.
 *
; Copyright 2009 by Dustin Laurence.  Distributed under the terms of
; the LGPLv3.
;
 **********************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define BUFSIZE 1024
char* strupper(char* str)
{
    static char buffer[BUFSIZE];
    int i;

    for(i=0;(str[i]!='\0'&&i<(BUFSIZE-1));i++) buffer[i] = toupper(str[i]);
    buffer[i] = '\0';
    return buffer; // =8-O
}

int
main(int argc, char *argv[])
{
    puts("#ifndef C_DEFS_LLH");
    puts("#define C_DEFS_LLH");
    putchar('\n');
    puts(";**********************************************************************");
    puts("; THIS FILE IS AUTOMATICALLY GENERATED BY c_defs.  DO NOT EDIT; CHANGE");
    puts("; THE SOURCE CODE IN c_defs.c.");
    puts(";**********************************************************************");
    putchar('\n');
    puts(";**********************************************************************");
    puts("; c_defs.llh");
    putchar('\n');
    puts("; Make C language quantities visible in LLVM code.");
    putchar('\n');
    puts(";**********************************************************************");
    putchar('\n');
    puts("; C and unix types");

    // LLVM's unit of size is the bit, not the byte as in C
    // CHAR_BIT is already defined for us--yes, there are computers whose bytes
    // are not octets.  Somewhere.  Maybe even still running.

    #define bitsof(type)      (sizeof(type)*CHAR_BIT)
    #define IMPORT_TYPE(type) \
        (printf("%%c_%s = type i%d\n", #type, bitsof(type)), \
         printf("#define C_%s_SIZEOF %d\n", strupper(#type), sizeof(type)), \
         printf("#define C_%s_BITSOF %d\n", strupper(#type), bitsof(type)), \
         putchar('\n'))

    IMPORT_TYPE(char);
    IMPORT_TYPE(int);
    IMPORT_TYPE(intptr_t);
    IMPORT_TYPE(size_t);
#if 0
    printf("#define C_CHAR_BITS %d\n", bitsof(char));
    printf("%%c_char = type i%d\n", CHAR_BIT);

    #define INT_BITS (sizeof(int)*CHAR_BIT)
    printf("#define C_INT_SIZEOF %d\n", sizeof(int));
    printf("#define C_INT_BITS %d\n", sizeof(int)*CHAR_BIT);
    printf("%%c_int  = type i%d\n", sizeof(int)*CHAR_BIT);

    #define INTPTR_BITS (sizeof(intptr_t)*CHAR_BIT)
    printf("#define C_INTPTR_BITS %d\n", INTPTR_BITS);
    printf("%%c_intptr_t  = type i%d\n", INTPTR_BITS);
#endif

    puts("; C stdio constants");
    printf("#define C_EOF %d\n", EOF);
    printf("#define C_STDIN_FD %d\n", fileno(stdin));
    printf("#define C_STDOUT_FD %d\n", fileno(stdout));
    printf("#define C_STDERR_FD %d\n", fileno(stderr));
    putchar('\n');

    puts("#endif");

    return 0;
}

