//Gino Benitez
#include <stdio.h>
#include <stdlib.h>

//file pointers
FILE *f;
FILE *wr;

//struct for tiny virtual machine
typedef struct
{

  
} tinyMachine;

int main (int argc, char *argv[])
{
    //tiny virtual machine creation
  //tinyMachine *vm = malloc (sizeof (tinyMachine));
  
  int pc, l, m;
  
  int pas[512];
  
  int op;

//opening input and output files
  f = fopen (argv[1], "r");
  wr = fopen("outputfile.txt", "w");
  
  fprintf(wr, "Gino Benitez\n");

  int sp = 0;
  
  //buffer for input
  char buf [100];
 //while file has a line
  while (fgets(buf,100,f))
    {
        //scan in the integers only
        sscanf (buf, "%d %d %d", &(pas[sp]), &(pas[sp+1]), &pas[sp+2]);
      sp+=3;
    }

// setting tiny virtual machine variables to 0
  int bp = sp - 1;
  pc = 0;
  l = 0;
  m = 0;
  op= 0;
  

  int control = 1;
  
  while (control == 1)
    {   
        //if pc reaches max break
        if(pc >=512 ){break;}
    
    // opcode
      op = pas[pc];
      
    // instruction register
      l = pas[pc +1];
      
      //increment pc by 2
      m = pas[pc + 2];
    
    //opcode cases
      switch (op)
	{
	case 1:
	  fprintf (wr,"LIT\n");
	  //mule = vm->MAR;
	  sp = sp - 1;
	  pas[sp] = m;
	  //printf("%d\n", vm->MDR);
	  //vm->a = vm->MDR;
	  break;
	case 2:
	  fprintf (wr,"ADD\n");
	  vm->MAR = ir;
	  vm->MDR = vm->dm[vm->MAR];
	  vm->a += vm->MDR;
	  break;

	case 3:
	  fprintf (wr,"STORE\n");
	  vm->MAR = ir;
	  vm->MDR = vm->a;
	  vm->dm[vm->MAR] = vm->MDR;
	  break;
	case 4:
	  fprintf (wr,"SUB\n");
	  vm->MAR = ir;
	  vm->MDR = vm->dm[vm->MAR];
	  vm->a -= vm->MDR;
	  break;
	case 5:
	  fprintf (wr,"IN\n");
	  printf ("Input a value:");
	  scanf ("%d", &(vm->a));
	  fprintf(wr,"Input a value:%d\n",vm->a);
	  break;
	case 6:
	  fprintf (wr,"OUT\n");
	  fprintf(wr,"Output value:%d\n",vm->a);
	  break;
	case 7:
	fprintf(wr, "HALT\n");
	  control = 0;
	  break;
	case 8:
	fprintf(wr, "JMP\n");
	  vm->pc = ir;
	  break;
	case 9:
	fprintf(wr, "SKIPZ\n");
	  if (vm->a == 0)
	    {
	      vm->pc += 2;
	    }
	  break;
	case 10:
	fprintf(wr, "SKIPG\n");
	  if (vm->a > 0)
	    {
	      vm->pc += 2;
	    }
	  break;
	case 11:
	fprintf(wr, "SKIPL\n");
	  if (vm->a < 0)
	    {
	      vm->pc += 2;
	    }
	  break;
	}

      fprintf (wr,"PC = %d | A = %d | DM = [", vm->pc, vm->a);

      for (int i = 0; i < 10; i++)
	{
	  if (i != 9)
	    {
	      fprintf (wr,"%d, ", vm->dm[i]);
	    }
	  else
	    {
	      fprintf (wr,"%d", vm->dm[i]);
	    }
	}
      fprintf (wr,"]\n");
    }

  fclose (f);
  fclose(wr);
  return 0;
}
