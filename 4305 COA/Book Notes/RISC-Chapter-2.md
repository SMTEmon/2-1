Only topics covered in [[4305 COA/Notes/Lecture 3]]

### Stuff to Know About
x86, CISC, RISC, RISC-V Operands, RISC-V Instruction Categories

### Base Integer ISA of RISC-V Includes:

1. `add`, `sub`
2. shifts (`sll`, `srl`, `sra`)
3. logical ops (`and`, `or`, `xor`)
4. loads/ stores
5. branches

### Basic Arithmetic Operations

>[!Problem-1]
>Compile the following C program into RISC-V Assembly Language
>$$a=b+c$$
>$$d=a-e$$
>
>Solution: 
>$$add\;a,b,c$$
>$$sub\;d, a, e$$

>Add a, b, c indicates that we add b and c, and store it in a

>[!Problem 1 with Registers]
>Compile the following C program into RISC-V Assembly Language where a, b, c, d, e are assigned to x19, x20, x21, x22, and x23 respectively
>$$a=b+c$$
>$$d=a-e$$
>
>Solution:
>
>$$add\;x19, x20, x21$$
>$$sub\;x22, x20, x23$$

Note that for adding constants, we use `addi`. A constant is often called an immediate or `imm`.

>Example usecase for $x = y + 5;$
`addi x10, x11, 5`

`addi` uses a 12-bit signed immediate. So even signed inputs are valid within $-2048\;and +2047$ 

>Increment and Decrement $i++$
>`addi i, i, 1`
>`addi i, i, -1`

>Copy a register
>`addi x5, x6, 0`

Note that x0 is hardwired to zero in RISC-V. No exceptions. So, we can also write this as:
>`addi x5, x6, x0`

and it would still be completely valid. 

### Memory Operations

- Let’s assume that A is an array of 100 doublewords and that the compiler has associated the variables g and h with the registers x20 and x21. Let’s also assume that the starting address, or base address, of the array is in x22. Compile this C assignment statement: `g = h + A[8];` Then, let's store the value in `A[12]`

```
ld x9, 64(x22) 
add x20, x21, x9
sd x9, 96(x22)
```

	Breakdown: 
	Here, ld = load doubleword (64 bits or, 8 bytes)
	x9 is a temporary memory location in register
	64(x22) means go to the address: x22 + 64 // 64 is called the BYTE OFFSET
									so in other words, we are accessing
									an address 64 bytes from the initial

$$byte\,offset = index\,*\,sizeOfElement$$
	
	so the syntax at play for ld:   ld <where to load from> <what to load>
								sd <what to store> <where to store into>
	
	Again, while storing, we find that the offset for A[12] is 12*8 = 96

### Representing Instructions

There are 6 types of Instruction Formats: 
1. R-Format: Register
2. I-Format: Immediates, Loads
3. S-Format: Store Instructions
4. U-Format: Branch Instructions
5. SB-Format: Instructions with Upper Immediates
6. UJ-Format: Jump Instructions
### R-Format Instructions

Every instruction is encoded as a 32-bit instruction word. Let's see a quick example:

$$add\;x9,\,x20,\,x22$$

| func7  | rs2    | rs1    | func3  | rd     | opcode |
| ------ | ------ | ------ | ------ | ------ | ------ |
| 7 bits | 5 bits | 5 bits | 3 bits | 5 bits | 7 bits |
the command add uses R-type instruction format. which is identified through the opcode. 
opcode: which type of instruction is it? (arithmetic)
rd : destination register (where to store) 5 bits because 32 registers
rs1: first input register/ register source 1
rs2: second rs
func3: which operation within arithmetic instructions? (add)
func7: some instructions share the same opcode AND func3
### I-Format Instruction

#### Immediate I

| 12        | 5   | 3     | 5   | 7      |
| --------- | --- | ----- | --- | ------ |
| imm[11:0] | rs1 | func3 | rd  | opcode |
opcode: identifies the instruction
rs1: specifies register operand
rd: destination register
immediate (12): 12 bit immediates $[-2^{11},2^{11})$


#### Load I

`lw x14, 8(x2)`

| imm=+8<br>12 bits        | rs1<br>5 bits | func3<br>3 bits<br> | rd=14<br>destination <br>register | opcode |
| ------------------------ | ------------- | ------------------- | --------------------------------- | ------ |
| offset[11:0]<br>(signed) | base<br>      | width               | dst                               | LOAD   |
### S-Format Instruction

| imm[11:5]<br>7 bits | rs2<br>5 bits  | rs1<br>5 bits         | func3<br>3 bits | imm[4:0]<br>5 bits | opcode<br>7 bits |
| ------------------- | -------------- | --------------------- | --------------- | ------------------ | ---------------- |
| byte offset         | value to Store | base address register | store size      | byte offset        | STORE            |
**why is the imm split?** 
Because RISC-V wants to reuse the same bit positions for fields across different instruction formats. As rd exists in I-type and S-type has no rd, so RISC-V reuses the same positions for rs2 and splits the immediate. 

### Logical Operations 

#### Shift (Right/ Left)
`slli x11, x19, 4` // reg x11 = reg x19 << 4 bits

| func6  | imm    | rs1    | func3  | rd     | opcode |
| ------ | ------ | ------ | ------ | ------ | ------ |
| 6 bits | 6 bits | 5 bits | 3 bits | 5 bits | 7 bits |

---

#### AND Instruction

**Assembly example:**

```asm
and x11, x19, x20   # x11 = x19 & x20
```

**Instruction format:**

- This is an **R-type instruction**
- Uses **func7 (7 bits)**, **rs2 (5 bits)**, **rs1 (5 bits)**, **func3 (3 bits)**, **rd (5 bits)**, **opcode (7 bits)**

|func7|rs2|rs1|func3|rd|opcode|
|---|---|---|---|---|---|
|0000000|5 bits|5 bits|111|5 bits|0110011|

---

#### OR Instruction

**Assembly example:**

```asm
or x11, x19, x20   # x11 = x19 | x20
```

|func7|rs2|rs1|func3|rd|opcode|
|---|---|---|---|---|---|
|0000000|5 bits|5 bits|110|5 bits|0110011|

#### XOR Instruction

**Assembly example:**

```asm
xor x11, x19, x20   # x11 = x19 ^ x20
```

|func7|rs2|rs1|func3|rd|opcode|
|---|---|---|---|---|---|
|0000000|5 bits|5 bits|100|5 bits|0110011|

### Branch Instructions

#### BEQ — Branch if Equal

**Assembly example:**

```asm
beq x11, x12, label   # if (x11 == x12) goto label
```

**SB-type instruction table (12-bit signed offset)**:

|imm[12]|imm[10:5]|rs2|rs1|func3|imm[4:1]|imm[11]|opcode|
|---|---|---|---|---|---|---|---|
|1 bit|6 bits|5 bits|5 bits|000|4 bits|1 bit|1100011|

#### BNE — Branch if Not Equal

**Assembly example:**

```asm
bne x11, x12, label   # if (x11 != x12) goto label
```

|imm[12]|imm[10:5]|rs2|rs1|func3|imm[4:1]|imm[11]|opcode|
|---|---|---|---|---|---|---|---|
|1 bit|6 bits|5 bits|5 bits|001|4 bits|1 bit|1100011|

#### BLT — Branch if Less Than (signed)

**Assembly example:**

```asm
blt x11, x12, label   # if (x11 < x12) goto label
```

|imm[12]|imm[10:5]|rs2|rs1|func3|imm[4:1]|imm[11]|opcode|
|---|---|---|---|---|---|---|---|
|1 bit|6 bits|5 bits|5 bits|100|4 bits|1 bit|1100011|

#### BGE — Branch if Greater or Equal (signed)

**Assembly example:**

```asm
bge x11, x12, label   # if (x11 >= x12) goto label
```

|imm[12]|imm[10:5]|rs2|rs1|func3|imm[4:1]|imm[11]|opcode|
|---|---|---|---|---|---|---|---|
|1 bit|6 bits|5 bits|5 bits|101|4 bits|1 bit|1100011|

#### BLTU — Branch if Less Than Unsigned

**Assembly example:**

```asm
bltu x11, x12, label   # if (x11 < x12) unsigned
```

|imm[12]|imm[10:5]|rs2|rs1|func3|imm[4:1]|imm[11]|opcode|
|---|---|---|---|---|---|---|---|
|1 bit|6 bits|5 bits|5 bits|110|4 bits|1 bit|1100011|

#### BGEU — Branch if Greater or Equal Unsigned

**Assembly example:**

```asm
bgeu x11, x12, label   # if (x11 >= x12) unsigned
```

|imm[12]|imm[10:5]|rs2|rs1|func3|imm[4:1]|imm[11]|opcode|
|---|---|---|---|---|---|---|---|
|1 bit|6 bits|5 bits|5 bits|111|4 bits|1 bit|1100011|
