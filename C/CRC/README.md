This is my personal project. It is a minimalistic C compiler that turns
C code into RISC-V assembly. Special java executable file is provided,
which will simulate running the compiled c program. Of course, writing
a full C compiler is quite difficult and might take years, this is why 
my C compiler will be very limited from the start and will possibly 
have kind of extensions that standard GCC compiler does not support.
Compiler will be implemented in C using input/output stream libraries. 

I will update my compiler slowly and write about what has been updated
here. Starting from now: 

1) Initial commit: created simple input - output files and added 
venus.jar to the directory with addition to a C file, in which, compiler 
will be implemented. 

2) commit 1/12/2025: Figured out a way to take out all the raw tokens out of the input.c file,
put them all in the single memory block and count the number of tokens.

3) commit 9/12/2025: Added modules needed for the program, fully implemented one particular module. 
Also added empty Makefile and extra folder for testing modules(as some modules will be expanded and implementations changed, we need good tests). Also added a vector.c and vector.h files, which is my
implementation of vector written for some assignment. Additionally, structured files a little and added
new .txt file for the analysis and thinking.

4) commit 15/12/2025: Improved a structure of Data module, wrote the .h file for the Mr_Assembler(for the support of variable declaration, assignment and read). Created two new modules, which will implement particular types of vectors(vector for storing char* - s and vector for storing new variable struct type objects). Added a new module, which is responsible fully for writing
assembly instructions.

5) commit 19/12/2025: Fully implemented string and variable vectors using my vector written for
assignment and added full test functionality to be able to test it out when implementation changes(planning to change linear search to binary search so that addition and reading is 
O(logn) instead of O(n). This will be a huge boost for larger input .c files). Added a way for
a client to provide .c files to compile in console and implemented input proofing. Partly Solved the problem of extra whitespaces being read during tokenization of the file. removed duplicate h files from test subdirectory. 

6) commit 22/12/2025: Fully solved the problem of whitespaces not getting cleaned good enough. Fully 
implemented the functionality of Mr_Assembler and wrote appropriate tests. Added overflow detection. 
Wrote a Makefile to quickly recompile compilator, if binary is somehow broken. Made minimal corrections and
modifications. 

7) commit 28/12/2025: Added a new method to instructions module, that generates assembly instructions for operating on two variables, that is x + y, x - y, x / y, x * y. Also added a test in instructions-test.c function. Made small improvemenets. 

8) commit 28/12/2025: Added a new method to Mr_Assembler. Implemented new pseudo - function. CRC_PRINT. That temporarily allows us to print 
the variable contents with endline onto the terminal. Made minor changes and modifications. 

9) commit 29/12/2025: Added two new methods to Mr_Compilator that take care of scopes({; and };). Changed the name of the good sir from assembler to compilator, as it is its real role. Made few bug removals and improvements. 

10) commit 30/12/2025: Added a new module that filters tokens, before Mr_Compilator handles it. Added a way to compile complex expressions
via using posfix and dual - stack approach.    

11) commit 15/01/2026: Added a support for expressions, where operators and numbers are not correctly spaced 
out(such as int x=3+5+4+(2+3)). Added a support for commenting(must start with /* and end with */)

12) commit 16/01/2026: Added a simple if statement support

13) commit 19/01/2026: Refactored operation priority get function via adding functionality to Data module. 
Made minor improvements. 

14) commit 20/01/2026: Added logical operator support, fixed few bugs. Also tried to implement the unary + and -, but not fully, currently user must specify
that + or - operation is unary like this(U+ or U-)

15) commit 20/01/2026: Added compilation to output file. Created a little bash script to compile and run the code 
automatically. fixed some bugs. 

16) commit 23/01/2026: Added while loop support. Made minor improvements and refactoring. 

17) commit 25/01/2026: Added void return type function support. 

18) commit 25/01/2026: Added a full test suite(wrote bash scripts). 