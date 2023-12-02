## Instructions

Instruction bitwidth: 8
Opcode: 3
Operand: 5

```
lda
add
str
mul
sub
jmp
cmp
not
```

## Memory

2^5 = 32 unique addresses (Bytes) is the max memory we have. No program may
exceed this limit!

**Open Problem**: How do we run programs greater than 32B?

## Code samples

Psuedo:

```
if (a == 10)
    printf("10")
else 
    print("no")
```

Assembly:

```
start:
    lda a
    cmp 10          ; cmp_flag = 1
    jmp is_10
not_10
    print no
    jmp exit
is_10
    print 10
exit

```

    
Psuedo:
```
for (i = 0; i < 10; ++i) 
    print hello
```

Assembly:

```
start
    lda 10

loop:
    cmp 0
    jmp exit

print
    print hello

decr
    sub 1
    jmp loop

exit
    exit
```


Psuedo:
```
while (1) 
    print hello
```

Assembly:
```
start
    print hello
    jmp start
```
