//Gino Benitez
#include <stdio.h>
#include <stdlib.h>

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

	//opening input and output files
  	f = fopen (argv[1], "r");
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

    // setting tiny virtual machine variables to 0
    int bp = sp + 1;
    pc = 0;
    l = 0;
    m = 0;
    op= 0;
  
    int flag = 1;
  
    while (flag)
    {   
        //if pc reaches max break
        if(pc >=512 ) break;
    
        // opcode
        op = pas[pc];
      
        // instruction register
        l = pas[pc +1];
      
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
                fprintf (wr,"ADD\n");
                // *====*
                // |TODO|
                // *====*
                break;
            case 3:// DONE
                fprintf (wr,"LOD\n");
                sp = sp + 1;
                pas[sp] = pas[base(bp, l) + m];
                break;
            case 4:
                fprintf (wr,"STO\n");
                pas[base(bp, l) + m] = pas[sp];
                sp = sp + 1;
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

    }
    // Close files and exit program
    fclose (f);
    fclose(wr);
    return 0; 
}
