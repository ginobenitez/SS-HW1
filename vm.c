//Gino Benitez
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//file pointers
FILE *f;
FILE *wr;
int pas[512];// Array

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

void printing(int BP, int L, int SP){
    
    int arb = BP;
    
    if(L <= 0){
        printf(wr, "\n");
        return;
    }
    
    for(int i = arb; i <= SP; i ++){
            fprintf(wr, "%d ", pas[i]);
        }
        
    if(L > 1){
            fprintf(wr, "| ");
        }
    
    arb = pas[arb];
    return printing(arb, L-1, SP);
}

int main (int argc, char *argv[])
{
    int pc, l, m;// Program Counter, Lexicographical Level, operation
    int op;

    // juan do not remove argv[1] lol
    /*argv[1]*/

	//opening input and output files
  	f = fopen ("elf.txt", "r");
  	wr = fopen("outputfile.txt", "w");
  	fprintf(wr, "Gino Benitez\n");

  	int sp = 0; // Stack Pointer
	char buf [100]; //buffer for input

 	//while file has a line
    while (fgets(buf,100,f))
    {
        //scan in the integers only
        sscanf (buf, "%d %d %d", &(pas[sp]), &(pas[sp+1]), &pas[sp+2]);
      	sp+=3;
    }

    sp = sp - 1;
    // setting tiny virtual machine variables to 0
    int bp = sp + 1;
    pc = 0;
    l = 0;
    m = 0;
    op= 0;

    bool val;
  
    int flag = 1;
    fprintf(wr, "\t\t\t\tPC\tBP\tSP\tstack\n");
    fprintf(wr, "Initial values: %d\t%d\t%d\n\n", pc, bp,sp);
    while (flag)
    {   
        //if pc reaches max break
        if(pc >= 512) break;
    
        // opcode
        op = pas[pc];
      
        // instruction register
        l = pas[pc + 1];
      
        //increment pc by 2
        m = pas[pc + 2];

	    pc = pc + 3;

        //opcode cases
        switch (op)
	    {
	        case 1:
                fprintf (wr,"\tLIT  ");
                sp = sp + 1;
                pas[sp] = m;
                break;
	        case 2:
                
                switch(m)
                {
                    case 0:
                        fprintf(wr,"\tRTN  ");
                        sp = bp - 1;
                        bp = pas[sp + 2];
                        pc = pas[sp  + 3];
                        break;
                    case 1:
                        fprintf(wr,"\tADD  ");
                        pas[sp - 1] = pas[sp -1] + pas[sp];
                        sp = sp - 1;
                        break;
                    case 2:
                        fprintf(wr,"\tSUB  ");
                        pas[sp - 1] = pas[sp -1] - pas[sp];
                        sp = sp - 1;
                        break;
                    case 3:
                        fprintf(wr,"\tMUL  ");
                        pas[sp - 1] = pas[sp -1] * pas[sp];
                        sp = sp - 1;
                        break;
                    case 4:
                        fprintf(wr,"\tDIV  ");
                        pas[sp - 1] = pas[sp -1] / pas[sp];
                        sp = sp - 1;
                        break;
                    case 5:
                        fprintf(wr,"\tEQL  ");
                        val = (pas[sp -1] == pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 6:
                        fprintf(wr,"\tNEQ  ");
                        val = (pas[sp -1] != pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 7:
                        fprintf(wr,"\tLSS  ");
                        val = (pas[sp -1] < pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 8:
                        fprintf(wr,"\tLEQ  ");
                        val = (pas[sp -1] <= pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 9:
                        fprintf(wr,"\tGTR  ");
                        val = (pas[sp -1] > pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 10:
                        fprintf(wr,"\tGEQ  ");
                        val = (pas[sp -1] >= pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                }
                break;
            case 3:// DONE
                fprintf (wr,"\tLOD  ");
                sp = sp + 1;
                pas[sp] = pas[base(bp, l) + m];
                break;
            case 4:
                fprintf (wr,"\tSTO  ");
                pas[base(bp, l) + m] = pas[sp];
                sp = sp - 1;
                break;
            case 5:
                fprintf (wr,"\tCAL  ");
                pas[sp + 1] = base(bp, l);
                pas[sp + 2] = bp;
                pas[sp + 3] = pc;
                bp = sp + 1;
                pc = m;
                break;
            case 6:
                fprintf (wr,"\tINC  ");
                sp = sp + m;
                break;
            case 7:
                fprintf(wr, "\tJMP  ");
                pc = m;
                break;
            case 8:
                fprintf(wr, "\tJPC  ");
                if (pas[sp] == 0)
                    pc = m;
                sp = sp - 1;
                break;
            case 9:
                if(m == 1)
                {
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

                fprintf(wr, "\tSYS  ");
                break;
	    }
        // Print Output
        printf("%d\t%d\t%d\t%d \t%d\n", l, m, pc, bp, sp);
        fprintf(wr,"%d\t%d\t%d\t%d \t%d  ", l, m, pc, bp, sp);
        
        //int x = bp;
        
        /*for(int x = bp; x <= sp; x++){
            fprintf(wr,"%d ", pas[x]);
        }
        
            fprintf(wr,"\n");*/
        printing(bp,l,sp);
    }
    // Close files and exit program
    fclose (f);
    fclose(wr);
    return 0; 
}
