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
        L--;
    }
    return arb;
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
  
    while (flag)
    {   
        //if pc reaches max break
        if(pc >=512 ) break;
    
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
                fprintf (wr,"LIT\n");
                sp = sp + 1;
                pas[sp] = m;
                break;
	        case 2:
                fprintf (wr,"OPR\n");
                switch(m){
                    case 0:
                        fprintf(wr,"RTN\n");
                        sp = bp - 1;
                        bp = pas[sp = 2];
                        pc = pas[sp  + 3];
                        break;
                    case 1:
                        fprintf(wr,"ADD\n");
                        pas[sp - 1] = pas[sp -1] + pas[sp];
                        sp = sp - 1;
                        break;
                    case 2:
                        fprintf(wr,"SUB\n");
                        pas[sp - 1] = pas[sp -1] - pas[sp];
                        sp = sp - 1;
                        break;
                    case 3:
                        fprintf(wr,"MUL\n");
                        pas[sp - 1] = pas[sp -1] * pas[sp];
                        sp = sp - 1;
                        break;
                    case 4:
                        fprintf(wr,"DIV\n");
                        pas[sp - 1] = pas[sp -1] / pas[sp];
                        sp = sp - 1;
                        break;
                    case 5:
                        fprintf(wr,"EQL\n");
                        val = (pas[sp -1] == pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 6:
                        fprintf(wr,"NEQ\n");
                        val = (pas[sp -1] != pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 7:
                        fprintf(wr,"LSS\n");
                        val = (pas[sp -1] < pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 8:
                        fprintf(wr,"LEQ\n");
                        val = (pas[sp -1] <= pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 9:
                        fprintf(wr,"GTR\n");
                        val = (pas[sp -1] > pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                    case 10:
                        fprintf(wr,"GEQ\n");
                        val = (pas[sp -1] >= pas[sp]);
                        pas[sp - 1] = val;
                        sp = sp - 1;
                        break;
                }
                break;
            case 3:// DONE
                fprintf (wr,"LOD\n");
                sp = sp + 1;
                pas[sp] = pas[base(bp, l) + m];
                break;
            case 4:
                fprintf (wr,"STO\n");
                pas[base(bp, l) + m] = pas[sp];
                sp = sp - 1;
                break;
            case 5:
                fprintf (wr,"CAL\n");
                pas[sp + 1] = base(bp, l);
                pas[sp + 2] = bp;
                pas[sp + 3] = pc;
                bp = sp + 1;
                pc = m;
                break;
            case 6:
                fprintf (wr,"INC\n");
                sp = sp + m;
                break;
            case 7:
                pc = m;
                break;
            case 8:
                if (pas[sp] == 0)
                    pc = m;
                sp = sp - 1;
                break;
            case 9:
                if(m == 1){
                    fprintf(wr,"%d\n", pas[sp]);
                    sp = sp - 1;
                }
                else if(m == 2){
                    sp = sp + 1;
                    printf("Please Enter an Integer: ");
                    scanf("%d", &pas[sp]);
                    fprintf(wr,"Please Enter an Integer: %d\n", pas[sp]);
                }
                else if (m ==3){
                    flag = 0;
                }
                // *====*
                // |TODO|
                // *====*
                break;
	    }

    // Print Output
    /* fprintf (wr,"PC = %d | A = %d | DM = [", vm->pc, vm->a);
    for (int i = 0; i < 10; i++)
        {
            if (i != 9)
                fprintf (wr,"%d, ", vm->dm[i]);  
            else
                fprintf (wr,"%d", vm->dm[i]);   
            fprintf (wr,"]\n");
        } */
        printf("%d %d %d\n", pc, bp, sp);
        fprintf(wr,"%d %d %d\n", pc, bp, sp);
    }
    // Close files and exit program
    fclose (f);
    fclose(wr);
    return 0; 
}
