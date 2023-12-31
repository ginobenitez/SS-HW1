// ====================
// COP3402 - Homework 1
// By:
//      Gino Benitez
//      Juan Penuela
// ====================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 512

// File pointers
FILE *f;
FILE *wr;
int pas[512];

// Base function
int base(int BP, int L)
{
    int arb = BP;
    while (L > 0)
    {
        arb = pas[arb];
        //fprintf(wr, "%d\n", pas[arb]);
        L--;
    }
    
    //fprintf(wr,"\n");
    return arb;
}

int main (int argc, char *argv[])
{
    // Program Counter, Lexicographical Level, operation
    int pc, l, m;
    int op;

	// Opening input and output files
  	f = fopen (argv[1], "r"); // <-- For submission
  	wr = fopen("outputfile.txt", "w");

    // Print Names to file
  	fprintf(wr, "Gino Benitez, Juan Penuela\n");

    // Stack Pointer and Buffer
  	int sp = 0;
	char buf [100];

 	// While file has a line
    while (fgets(buf,100,f))
    {
        //scan in the integers only
        sscanf (buf, "%d %d %d", &(pas[sp]), &(pas[sp+1]), &pas[sp+2]);
      	sp += 3;
    }

    for(int i = sp; i < MAX_SIZE; i++)
        pas[i]= 0;    

    sp = sp - 1;
    // Setting tiny virtual machine variables to 0
    int bp = sp + 1;
    int initialbp = bp;
    pc = 0;
    l = 0;
    m = 0;
    op= 0;
    bool val;
    int flag = 1;

    // Print values
    printf("\t\tPC\tBP\tSP\tstack\n");
    fprintf(wr, "\t\t\t\tPC\tBP\tSP\tstack\n");
    fprintf(wr, "Initial values: %d\t%d\t%d\n\n", pc, bp,sp);

    while (flag)
    {   
        // If pc reaches max break
        if(pc >= 512) break;
    
        // Opcode
        op = pas[pc];
      
        // Instruction register
        l = pas[pc + 1];
      
        // Increment pc by 2
        m = pas[pc + 2];
	    pc = pc + 3;

        // Opcode cases
        switch (op)
	    {
	        case 1:
                printf ("\tLIT  ");
                fprintf (wr,"\tLIT  ");
                sp = sp + 1;
                pas[sp] = m;
                break;
	        case 2:
                switch(m)
                {
                    case 0:
                        printf("\tRTN  ");
                        fprintf(wr,"\tRTN  ");
                        sp = bp - 1;
                        bp = pas[sp + 2];
                        pc = pas[sp  + 3];
                        break;
                    case 1:
                        printf("\tADD  ");
                        fprintf(wr,"\tADD  ");
                        pas[sp - 1] = pas[sp -1] + pas[sp];
                        sp = sp - 1;
                        break;
                    case 2:
                        printf("\tSUB  ");
                        fprintf(wr,"\tSUB  ");
                        pas[sp - 1] = pas[sp -1] - pas[sp];
                        sp = sp - 1;
                        break;
                    case 3:
                        printf("\tMUL  ");
                        fprintf(wr,"\tMUL  ");
                        pas[sp - 1] = pas[sp -1] * pas[sp];
                        sp = sp - 1;
                        break;
                    case 4:
                        printf("\tDIV  ");
                        fprintf(wr,"\tDIV  ");
                        pas[sp - 1] = pas[sp -1] / pas[sp];
                        sp = sp - 1;
                        break;
                    case 5:
                        printf("\tEQL  ");
                        fprintf(wr,"\tEQL  ");
                        val = (pas[sp -1] == pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 6:
                        printf("\tNEQ  ");
                        fprintf(wr,"\tNEQ  ");
                        val = (pas[sp -1] != pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 7:
                        printf("\tLSS  ");
                        fprintf(wr,"\tLSS  ");
                        val = (pas[sp -1] < pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 8:
                        printf("\tLEQ  ");                    
                        fprintf(wr,"\tLEQ  ");
                        val = (pas[sp -1] <= pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 9:
                        printf("\tGTR  ");
                        fprintf(wr,"\tGTR  ");
                        val = (pas[sp -1] > pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 10:
                        printf("\tGEQ  ");
                        fprintf(wr,"\tGEQ  ");
                        val = (pas[sp -1] >= pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                }
                break;
            case 3:
                printf ("\tLOD  ");
                fprintf (wr,"\tLOD  ");
                sp = sp + 1;
                pas[sp] = pas[base(bp, l) + m];
                break;
            case 4:
                printf ("\tSTO  ");
                fprintf (wr,"\tSTO  ");
                pas[base(bp, l) + m] = pas[sp];
                sp = sp - 1;
                break;
            case 5:
                printf ("\tCAL  ");
                fprintf (wr,"\tCAL  ");
                pas[sp + 1] = base(bp, l);
                pas[sp + 2] = bp;
                pas[sp + 3] = pc;
                bp = sp + 1;
                pc = m;
                break;
            case 6:
                printf ("\tINC  ");
                fprintf (wr,"\tINC  ");
                int val = sp;
                sp = sp + m;
                break;
            case 7:
                printf("\tJMP  ");
                fprintf(wr, "\tJMP  ");
                pc = m;
                break;
            case 8:
                printf("\tJPC  ");
                fprintf(wr, "\tJPC  ");
                if (pas[sp] == 0)
                    {pc = m;}
                sp = sp - 1;
                break;
            case 9:
                if(m == 1)
                {
                    printf("Output result is: %d\n", pas[sp]);
                    fprintf(wr,"Output result is: %d\n", pas[sp]);
                    sp = sp - 1;
                }
                else if(m == 2)
                {
                    sp = sp + 1;
                    printf("Please Enter an Integer: ");
                    scanf("%d", &pas[sp]);
                    fprintf(wr,"Please Enter an Integer: %d\n", pas[sp]);
                }
                else if (m == 3)
                    flag = 0;
                
                printf("\tSYS  ");
                fprintf(wr, "\tSYS  ");
                break;
	    }
        
        // Print Output
        printf("%d\t%d\t%d\t%d \t%d\t", l, m, pc, bp, sp);
        fprintf(wr,"%d\t%d\t%d\t%d\t%d\t", l, m, pc, bp, sp);
        
        for(int x = initialbp; x <= sp; x++)
        {
            int curr = pas[x];

            if(x != initialbp && x % 6 == 0)
            {
                printf("|  ");
                fprintf(wr,  "| " );
            }
            printf("%d ", pas[x]);
            fprintf(wr,"%d ", pas[x]);
        }
        printf("\n");
        fprintf(wr,"\n");
    }
    
    // Close files and exit program
    fclose (f);
    fclose(wr);
    return 0; 
}
