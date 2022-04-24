## Project 1:

reverse.c: Prints out a file's lines in reverse order.
The "line" struct is used for creating a linked list of lines.
The program checks that the number of arguments is 2-3. If the input and output files are the same, the program prints an error.
Reads lines from a file using the "getline" function. Each read line is duplicated with "strdup" and their pointers are put into new structs.
The "print_output" function goes through the linked list and prints the lines to the stream in its first parameter.

<br>

## Project 2:

my-cat.c: print out contents in file(s)
For each argument, opens the corresponding file, reads every line with "fgets" and prints them.

my-grep.c: find term in file(s) or stdin
For each argument, opens the corresponding file, reads every line with "getline" and searches for a term with "strstr". 
All lines that include the term are printed out to stdout.

my-zip.c: compress a file with run-length encoding
For each argument, opens the corresponding file and reads every line with "getline". 
The program goes through the lines character by character, counting how many times each one appears in a row. If the next character is a different one,
the counter is reset and the currently inspected character is changed to the next one.
The characters and their numbers are written to stdout as binary with "fwrite"

my-unzip.c: decompress a file compressed with run-length encoding
For each argument, opens the corresponding file and reads the contents with "fread".
The program looks for a 4-byte number (n), and if it finds one it reads the following 1-byte character. It then prints out the character n times to stdout 
and attempts to read the next number.

<br>

## Project 4:

Xv6 operating system with an added system call "getreadcount" to get the number of times a certain system call (default: read) has been used.

Also adds a new program "getrc.c" that prints out the counter's value. It can be given two arguments, the first one resets the counter if the argument's 
value is not 0. The second argument changes the system call which is being counted if its value is a valid system call number (1-22).

The "proc" structure has an added int variable "readcount". The global counter is a variable in "syscall.c" which is copied into the current process' 
readcount variable when "getrc" is used. This is done so that the counter's value can be returned by the system call by using "myproc()->readcount".   

### How to compile:
1. install qemu
2. use command "chmod u+rwx -R xv6-readcounter/" inside the "project-4" folder
3. use command "make qemu" inside the "xv6-readcounter/" folder
