
# SS-HW1

====================
COP3402 - Homework 1
 By:
     Gino Benitez
     Juan Penuela
====================

Virtual Machine Program Instructions

1. On the terminal of your local computer or Eustis, please type "gcc vm.c"
   
2. Afterwards please type "./a.out elf.txt" having the input file aftwerwards is crucial as the program reads the command line to
 access the inpur file.

4. In the input file, please do not add any comments on the top or both of the list of numbers. Comments should only be placed on the
 side after each line of numbers. The virtual machine takes three numbers at a time. So when adding instructions, you must only add
three numbers per line. No more than three and no less than three.

5. If all goes well, the virtual machine will print to an outout.txt file please look at that to see the results after instructions
end.

Example:

correct:
gcc vm.c
./a.out elf.txt

incorrect:
gcc vm.c elf.txt
./a./out

correct:
elf.txt
7 0 45 //comment
7 0 6  //comment
6 0 4  //comment
1 0 4  //comment
1 0 3  //comment
2 0 3  //comment
4 1 4  //comment
1 0 14  //comment
3 1 4  //comment
2 0 7  //comment
8 0 39  //comment
1 0 7  //comment
7 0 42  //comment
1 0 5  //comment
2 0 0  //comment
6 0 5  //comment
9 0 2  //comment
5 0 6  //comment
9 0 1  //comment
9 0 3  //comment

incorrect:
//comment
7 0 45
7 0 6
6 0 4
1 0 4
1 0 3
2 0 3
4 1 4
1 0 14
3 1 4
2 0 7
8 0 39
1 0 7
7 0 42
1 0 5
2 0 0
6 0 5
9 0 2
5 0 6
9 0 1
9 0 3
//comment
