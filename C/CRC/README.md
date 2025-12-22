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