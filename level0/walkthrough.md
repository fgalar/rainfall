# Rainfall - Level 0

## Privileges

	-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0

Owner of the file is level1, and these permission will execute all functions with owner permissions.

## The vulnerability
```
0x08048f4a <+138>:	movl   $0x80c5348,(%esp)
0x08048f51 <+145>:	call   0x8054640 <execv>
```

We can see at 0x80c5348 :
```
(gdb) p (char *) 0x80c5348
$2 = 0x80c5348 "/bin/sh"
```

## Executable analyse

```assembly
0x08048ed9 <+25>:	cmp    $0x1a7,%eax
0x08048ede <+30>:	jne    0x8048f58 <main+152>
```
Here if $eax is not equal to '0x1a7' then we are kicked from program with a dramatic "No!"

So we need to set $eax equal to integer '423' in order to continue the execution.
Let's see what happen in our executable ...

### 1 - Assembly convention
```assembly
0x08048ec0 <+0>:	  push   %ebp
0x08048ec1 <+1>:	  mov    %esp,%ebp
0x08048ec3 <+3>:	  and    $0xfffffff0,%esp
0x08048ec6 <+6>:	  sub    $0x20,%esp
```
Save pointer of the calling stack  
Create the new pointer of called function  
Stack alignment  
Save 32 bytes space

```assembly
0x08048ec9 <+9>:	  mov    0xc(%ebp),%eax
0x08048ecc <+12>:	  add    $0x4,%eax
0x08048ecf <+15>:	  mov    (%eax),%eax
0x08048ed1 <+17>:	  mov    %eax,(%esp)
0x08048ed4 <+20>:	  call   0x8049710 <atoi>
```
Get atoi of Argv[1]

![stack3.png](ressources/stack.svg)
