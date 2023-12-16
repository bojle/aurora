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

## IR

```
struct IR {
    uint8_t opcode;
    uint8_t operand;
};

struct IR program[];

program[0] = 101001;
inst_push(1010101);

int i = program[0];
int i = inst_at(0);

void inst_push(struct IR *inst);
void inst_at(int idx);

program[0] // 1st instruction

jmp start -> program[idx] == 101 00111
                             opc opr
```

## Backend

```
void backend_write(struct IR *inst);
void backend_program_write();

char *backend_disasseble(uint8_t inst);

10-0101010 -> lda 01

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
not_10:
    print no
    jmp exit
is_10:
    print 10
exit:

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
