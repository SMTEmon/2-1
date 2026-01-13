## 1. Introduction to Instruction Set Architecture (ISA)

### What is ISA?

- **Language of the computer**: The fundamental way computers understand and execute instructions
- **Interface between hardware and software**: Acts as a bridge that allows software to communicate with hardware
- **Abstract model of a computer**: Provides a conceptual framework without worrying about physical implementation details
- **Operational specifications**: Defines what operations the CPU can perform and how it performs them

### Importance of ISA

**Compatibility and Portability**

- Programs written for one ISA can run on any processor implementing that ISA
- Allows software to be portable across different hardware implementations

**High-level Abstraction**

- Hides complex hardware details from programmers
- Allows focus on logic rather than hardware specifics

**Performance Optimization**

- Well-designed ISAs enable efficient compilation
- Allow hardware designers to optimize performance while maintaining compatibility

### Common ISA Families

- **RISC-V**: Open-source, modern design
- **MIPS**: Educational and embedded systems
- **x86**: Intel/AMD processors (desktops, laptops, servers)
- **ARM**: Mobile devices, embedded systems
- **PowerPC**: Previously used in game consoles and servers

**Note**: ISAs are usually similar to ensure simplicity of equipment design.

---

## 2. CISC vs RISC Architecture

### CISC (Complex Instruction Set Computer)

**Characteristics:**

- **Variable instruction length**: Instructions can be different sizes
- **Powerful instructions**: Single instructions can perform complex operations
- **Multiple clock cycles**: Instructions may take more than one clock cycle to execute
- **Example**: x86 architecture

**Advantages:**

- Fewer instructions needed for complex tasks
- Better code density (smaller program size)

**Disadvantages:**

- Complex hardware implementation
- Variable execution times

### RISC (Reduced Instruction Set Computer)

**Characteristics:**

- **Fixed-length instructions**: All instructions are the same size
- **Simpler instructions**: Each instruction performs a simple operation
- **Single clock cycle**: Most instructions execute in one clock cycle
- **Example**: RISC-V, ARM, MIPS

**Advantages:**

- Simpler hardware design
- Predictable execution time
- Easier to pipeline
- Higher clock speeds possible

**Disadvantages:**

- More instructions needed for complex tasks
- Larger program size

---

## 3. RISC-V Architecture

### History and Philosophy

- **Origin**: Developed at UC Berkeley starting in 2010
- **Open-source**: Free to use, no licensing fees
- **Variants**: Offers both 32-bit and 64-bit versions
- **Design Goals**:
    - Simplicity over complexity
    - Performance optimization
    - Academic and commercial neutrality

### RISC-V Operands

**1. Registers (32 total)**

- Designated as x0 through x31
- Fast, on-chip storage
- Used for immediate computation

**2. Memory**

- Slower than registers but much larger
- Used for arrays, structures, and dynamic data

### RISC-V Operation Categories

1. **Arithmetic**: Addition, subtraction, etc.
2. **Data Transfer**: Load and store operations
3. **Logical**: AND, OR, XOR, shifts
4. **Conditional Branch**: Decision-making instructions
5. **Unconditional Branch**: Jumping to different code locations

---

## 4. Arithmetic Instructions

### ADD Instruction

```assembly
add a, b, c
```

**Format**: `add dst, src1, src2`

**Functionality:**

- Adds the values in registers b and c
- Stores the result in register a
- Performs: `a = b + c`

**Design Principles:**

- **One operation per instruction**: Simplifies hardware
- **Exactly three variables**: Maintains regularity
- **Follows "Simplicity favors regularity"**: Consistent format makes hardware design easier

### Examples

**Example 1: Simple Addition and Subtraction**

```c
// C code
a = b + c;
d = a - e;
```

```assembly
# RISC-V assembly
add a, b, c
sub d, a, e
```

**Example 2: Complex Expression**

```c
// C code
f = (g + h) - (i + j);
```

```assembly
# RISC-V assembly (without registers)
add t0, g, h      # t0 = g + h
add t1, i, j      # t1 = i + j
sub f, t0, t1     # f = t0 - t1
```

---

## 5. RISC-V Registers

### Register Specifications

- **Total count**: 32 registers (x0 to x31)
- **Size**: 64 bits per register (in 64-bit RISC-V)
- **Requirement**: All three operands in arithmetic instructions must be registers

### Design Principle: "Smaller is Faster"

- **Limited number improves speed**: Fewer registers mean shorter access times
- **Tradeoff**: Must balance between having enough registers and maintaining fast clock cycles
- **Hardware consideration**: More registers require more complex circuitry and longer signal paths

### Register Usage Example

```c
// C code
f = (g + h) - (i + j);
```

**Register Assignment:**

- f → x19
- g → x20
- h → x21
- i → x22
- j → x23

```assembly
# RISC-V assembly with registers
add x5, x20, x21     # x5 = g + h
add x6, x22, x23     # x6 = i + j
sub x19, x5, x6      # f = (g + h) - (i + j)
```

---

## 6. Memory Operations

### Why Use Memory?

**Registers are limited** (only 32), but we need to store:

- **Arrays**: Collections of data elements
- **Structures**: Complex data types
- **Dynamic data**: Data allocated at runtime

### Memory Characteristics in RISC-V

- **Little Endian**: Least significant byte stored at lowest address
- **No alignment requirement**: Words don't need to be aligned to word boundaries
- **Byte-addressable**: Each byte has a unique address

### Endianness

**Definition**: The order in which bytes are stored in memory

**Big Endian:**

- Most significant byte stored first (at lowest address)
- Example: Number 0x12345678 stored as: 12 34 56 78
- Used in: PowerPC, some network protocols

**Little Endian:**

- Least significant byte stored first (at lowest address)
- Example: Number 0x12345678 stored as: 78 56 34 12
- Used in: x86, x86-64, ARM, **RISC-V**

**Which is Better?**

- Depends on context
- Network protocols often use big-endian
- Most modern processors use little-endian
- Some systems are **bi-endian** (can switch between both)

### Data Transfer Instructions

**Load Doubleword (ld)**

```assembly
ld x9, 64(x22)
```

- **Syntax**: `ld destination, offset(base_register)`
- **Function**: Loads 8 bytes from memory into a register
- **Address calculation**: Memory address = base_register + offset

**Store Doubleword (sd)**

```assembly
sd x9, 96(x22)
```

- **Syntax**: `sd source, offset(base_register)`
- **Function**: Stores 8 bytes from register to memory
- **Address calculation**: Memory address = base_register + offset

### Memory Access Examples

**Example 1: Loading from Array**

```c
// C code
g = h + A[8];
```

**Assumptions:**

- g is in x20
- h is in x21
- Base address of A is in x22
- Array contains doublewords (8 bytes each)

```assembly
# RISC-V assembly
ld x9, 64(x22)        # Load A[8], offset = 8 × 8 = 64 bytes
add x20, x21, x9      # g = h + A[8]
```

**Example 2: Storing to Array**

```c
// C code
A[12] = h + A[8];
```

```assembly
# RISC-V assembly
ld x9, 64(x22)        # Load A[8]
add x9, x21, x9       # x9 = h + A[8]
sd x9, 96(x22)        # Store to A[12], offset = 12 × 8 = 96
```

### Registers vs Memory

**Advantages of Registers:**

- **Faster access**: Registers are on the CPU chip
- **Higher throughput**: Can access multiple registers simultaneously
- **Fewer instructions**: Direct operations without load/store

**Disadvantages of Memory:**

- **Slower access**: Must travel to/from main memory
- **More instructions**: Requires load before use, store after computation
- **Lower throughput**: Memory bandwidth is limited

**Compiler Strategy:**

- Use registers for frequently accessed variables
- "Spill" less frequently used variables to memory
- Cache helps bridge the speed gap

---

## 7. Immediate Operands

### Purpose

**Make common cases fast**: Small constants appear frequently in programs

### Advantages

- **Avoid memory access**: No need to load constant from memory
- **Faster execution**: One instruction instead of load + operation
- **Common use cases**: Incrementing counters, array indexing

### Example: Add Immediate

```assembly
addi x22, x22, 4      # x22 = x22 + 4
```

**Syntax**: `addi destination, source, immediate_value`

**Usage scenarios:**

- Loop counters
- Array pointer advancement
- Stack pointer manipulation

---

## 8. Number Representations

### Why Binary?

- Electronic circuits naturally have two states (on/off)
- Reliable and simple to implement
- All data ultimately stored as sequences of 0s and 1s

### Unsigned Binary Integers

**Characteristics:**

- Represents only non-negative numbers
- **Range for n bits**: 0 to 2^n - 1
- **64-bit range**: 0 to 18,446,744,073,709,551,615

**Example:**

```
0000 0000 ... 001011₂ = 11₁₀
```

### Signed Binary Integers

**2's Complement Representation:**

- Standard method for representing signed numbers
- **Range for n bits**: -2^(n-1) to 2^(n-1) - 1
- **64-bit range**: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807

**Key Properties:**

- Most significant bit (MSB) indicates sign
    - 0 = positive
    - 1 = negative
- Arithmetic operations work naturally
- Only one representation for zero

**Example:**

```
1111 1111 ... 111100₂ = -4₁₀
```

### When to Use Each?

- **Unsigned**: Counts, array indices, memory addresses
- **Signed**: Mathematical calculations, differences, general arithmetic

---

## 9. Stored-Program Concept

### Revolutionary Idea

**Instructions are data!**

**Implications:**

- Programs stored in memory as numbers
- Same memory holds both instructions and data
- Programs can be modified like data
- Enables modern computing flexibility

**Convention:**

- Establish standard for interpreting bit patterns as instructions
- Different patterns mean different operations

---

## 10. Instruction Encoding

### Machine Code

- **Definition**: Binary representation of instructions
- All instructions encoded as numbers
- Processor decodes these numbers to perform operations

### RISC-V Instruction Format

- **Fixed size**: All instructions are 32 bits
- **Multiple formats**: Different instruction types use different layouts
- **Regularity principle**: Maintains simplicity while allowing flexibility

### Design Principle: "Good Design Demands Good Compromises"

- **Decision**: Keep all instructions same length BUT use different formats
- **Benefits**:
    - Simpler hardware (fixed length)
    - Easier compilation
    - Flexibility for different operation types

---

## 11. Instruction Formats

### Overview: 6 Format Types

1. **R-Format**: Register operations
2. **I-Format**: Immediate values and loads
3. **S-Format**: Store operations
4. **SB-Format**: Branch instructions
5. **U-Format**: Upper immediate values
6. **UJ-Format**: Jump instructions

---

## 12. R-Format Instructions

### Structure

```
| funct7 (7) | rs2 (5) | rs1 (5) | funct3 (3) | rd (5) | opcode (7) |
```

Total: 7 + 5 + 5 + 3 + 5 + 7 = 32 bits

### Field Meanings

**opcode (7 bits):**

- Partially specifies the operation
- Identifies instruction category

**funct3 (3 bits) + funct7 (7 bits):**

- Combined with opcode to fully specify operation
- Allows multiple operations within same category

**rs1 (5 bits):**

- First source register (source register 1)
- Specifies which of 32 registers to use

**rs2 (5 bits):**

- Second source register
- Provides second operand

**rd (5 bits):**

- Destination register
- Receives the result of computation

### Example: add x9, x20, x21

```
| 0000000 | 10101 | 10100 | 000 | 01001 | 0110011 |
  funct7    rs2     rs1    f3    rd      opcode
```

Breaking it down:

- funct7 = 0000000 (add operation)
- rs2 = 10101 (x21 = register 21)
- rs1 = 10100 (x20 = register 20)
- funct3 = 000 (add specification)
- rd = 01001 (x9 = register 9)
- opcode = 0110011 (R-type arithmetic)

### All RV32 R-Format Instructions

- add, sub (addition, subtraction)
- sll, srl, sra (shift left logical, shift right logical, shift right arithmetic)
- and, or, xor (logical operations)
- slt, sltu (set less than, set less than unsigned)

---

## 13. I-Format Instructions

### Purpose

Used for:

- **Immediate operations**: Operations with constants
- **Load operations**: Reading from memory

### Structure

```
| immediate[11:0] (12) | rs1 (5) | funct3 (3) | rd (5) | opcode (7) |
```

Total: 12 + 5 + 3 + 5 + 7 = 32 bits

### Key Differences from R-Format

- **12-bit immediate**: Replaces rs2 and funct7 fields
- **Two registers max**: Only 1 source (rs1) and 1 destination (rd)
- **Signed immediate**: Can represent negative values

### I-Format 'Immediate' Instructions

**Field Meanings:**

- **opcode (7)**: Specifies instruction type
- **rs1 (5)**: Source register operand
- **rd (5)**: Destination register
- **immediate (12)**:
    - 12-bit signed number
    - Range: -2048 to +2047 (-2^11 to 2^11 - 1)

**Example: addi x15, x1, -50**

```
| 111111001110 | 00001 | 000 | 01111 | 0010011 |
  immediate      rs1    f3    rd      opcode
```

Breaking it down:

- immediate = 111111001110 (-50 in 2's complement)
- rs1 = 00001 (x1)
- funct3 = 000 (addi)
- rd = 01111 (x15)
- opcode = 0010011 (I-type immediate)

### I-Format 'Load' Instructions

**Memory Address Calculation:**

```
Address = rs1 + immediate (offset)
```

**Field Usage:**

- **rs1**: Base address register
- **immediate**: Signed offset from base
- **rd**: Destination register for loaded value

**Example: lw x14, 8(x2)**

```
| 000000001000 | 00010 | 010 | 01110 | 0000011 |
  offset=8       rs1=x2  f3   rd=x14  opcode
```

Breaking it down:

- offset = 000000001000 (8 in binary)
- rs1 = 00010 (x2, contains base address)
- funct3 = 010 (word load)
- rd = 01110 (x14, receives loaded value)
- opcode = 0000011 (load instruction)

**Process:**

1. Add offset (8) to value in x2
2. Access memory at calculated address
3. Load word into x14

### All RV32 I-Format Instructions

**Immediate Operations:**

- addi (add immediate)
- slti, sltiu (set less than immediate)
- andi, ori, xori (logical operations with immediate)
- slli, srli, srai (shift immediate)

**Load Operations:**

- lb, lbu (load byte, load byte unsigned)
- lh, lhu (load halfword, load halfword unsigned)
- lw (load word)
- ld (load doubleword)

---

## 14. S-Format Instructions

### Purpose

Used exclusively for **store operations** (writing to memory)

### Structure

```
| imm[11:5] (7) | rs2 (5) | rs1 (5) | funct3 (3) | imm[4:0] (5) | opcode (7) |
```

Total: 7 + 5 + 5 + 3 + 5 + 7 = 32 bits

### Key Characteristics

**Two Source Registers:**

- **rs1**: Base memory address
- **rs2**: Data to be stored

**No Destination Register:**

- No rd field (unlike R-format and I-format)
- Data goes to memory, not a register

**Split Immediate Field:**

- **Why split?** To keep rs1, rs2, and funct3 in same positions as other formats
- **imm[11:5]**: Upper 7 bits
- **imm[4:0]**: Lower 5 bits
- **Benefit**: Simplifies hardware decoder design

### Memory Address Calculation

```
Address = rs1 + immediate (offset)
```

### Example: sw x14, 8(x2)

```
| 0000000 | 01110 | 00010 | 010 | 01000 | 0100011 |
  imm[11:5] rs2=x14 rs1=x2 f3   imm[4:0] opcode
```

Breaking it down:

- imm[11:5] = 0000000 (upper bits of offset 8)
- rs2 = 01110 (x14, contains data to store)
- rs1 = 00010 (x2, contains base address)
- funct3 = 010 (word store)
- imm[4:0] = 01000 (lower bits of offset 8)
- opcode = 0100011 (store instruction)

**Complete offset**: 0000000 | 01000 = 000000001000 = 8

**Process:**

1. Add offset (8) to value in x2
2. Take value from x14
3. Store to calculated memory address

### All RV32 S-Format Instructions

- sb (store byte - 1 byte)
- sh (store halfword - 2 bytes)
- sw (store word - 4 bytes)
- sd (store doubleword - 8 bytes)

---

## 15. Complete Problem Example

### Problem Statement

```c
// Given:
// x10 = base address of array A
// x21 = h
// Assignment:
A[30] = h + A[30] + 1;
```

### Assembly Code

```assembly
ld x9, 240(x10)      # Load A[30] into x9
add x9, x21, x9      # x9 = h + A[30]
addi x9, x9, 1       # x9 = h + A[30] + 1
sd x9, 240(x10)      # Store back to A[30]
```

**Note:** Offset = 30 × 8 = 240 bytes (each array element is 8 bytes)

### Machine Code Translation

**Instruction 1: ld x9, 240(x10)**

- Format: I-type (load)
- immediate = 240 = 000011110000
- rs1 = x10 = 01010
- funct3 = 011 (doubleword)
- rd = x9 = 01001
- opcode = 0000011

Binary: `000011110000 01010 011 01001 0000011`

**Instruction 2: add x9, x21, x9**

- Format: R-type
- funct7 = 0000000
- rs2 = x9 = 01001
- rs1 = x21 = 10101
- funct3 = 000
- rd = x9 = 01001
- opcode = 0110011

Binary: `0000000 01001 10101 000 01001 0110011`

**Instruction 3: addi x9, x9, 1**

- Format: I-type (immediate)
- immediate = 1 = 000000000001
- rs1 = x9 = 01001
- funct3 = 000
- rd = x9 = 01001
- opcode = 0010011

Binary: `000000000001 01001 000 01001 0010011`

**Instruction 4: sd x9, 240(x10)**

- Format: S-type
- imm[11:5] = 0000111 (upper 7 bits of 240)
- rs2 = x9 = 01001
- rs1 = x10 = 01010
- funct3 = 011 (doubleword)
- imm[4:0] = 10000 (lower 5 bits of 240)
- opcode = 0100011

Binary: `0000111 01001 01010 011 10000 0100011`

---

## 16. Logical Operations

### Purpose

**Operating on individual bits or fields of bits within a word**

Applications:

- Masking specific bits
- Setting/clearing bits
- Bit manipulation
- Bitwise computations

---

## 17. Shift Operations

### Types of Shifts

**1. Shift Left Logical (slli)**

```assembly
slli x11, x19, 4     # x11 = x19 << 4 bits
```

**Operation:**

- Shifts all bits to the left
- Fills emptied right bits with 0s
- **Mathematical effect**: Multiplying by 2^i (where i = shift amount)
- Example: `slli x11, x19, 4` multiplies x19 by 16

**2. Shift Right Logical (srli)**

```assembly
srli x11, x19, 4     # x11 = x19 >> 4 bits
```

**Operation:**

- Shifts all bits to the right
- Fills emptied left bits with 0s
- **Mathematical effect**: Dividing by 2^i (unsigned division)
- Example: `srli x11, x19, 4` divides x19 by 16

### Format

- Uses **I-type format**
- Immediate field specifies shift amount
- Shift amount is typically 0-63 for 64-bit operations

### Register Variants

- **sll, srl, sra**: Take shift amount from a register instead of immediate
- Syntax: `sll rd, rs1, rs2` (shift rs1 left by amount in rs2)

### Arithmetic Shift

**sra (Shift Right Arithmetic)**

- Preserves sign bit
- Fills left with copies of sign bit
- Used for signed division by powers of 2

**Example:**

```assembly
slli x11, x19, 4     # Multiply x19 by 16
srli x11, x19, 2     # Divide x19 by 4 (unsigned)
sra x11, x19, 2      # Divide x19 by 4 (signed)
```

---

## 18. AND Operation

### Function

**Calculates 1 only if there is 1 in BOTH operands**

### Truth Table

```
A   B   A AND B
0   0      0
0   1      0
1   0      0
1   1      1
```

### Primary Use: Masking Bits

- **Select specific bits**: Keep certain bits, clear others to 0
- **Extract fields**: Isolate portions of a word

### Example

```assembly
and x9, x10, x11     # x9 = x10 & x11
```

**Practical Example - Masking:**

```
x10 = 1010 1100 1111 0011
x11 = 0000 0000 1111 1111  (mask for lower 8 bits)
x9  = 0000 0000 1111 0011  (result: only lower 8 bits preserved)
```

---

## 19. OR Operation

### Function

**Calculates 1 if there is 1 in EITHER operand**

### Truth Table

```
A   B   A OR B
0   0     0
0   1     1
1   0     1
1   1     1
```

### Primary Use: Including Bits

- **Set specific bits to 1**: Force certain bits high
- **Leave others unchanged**: Preserve existing values

### Example

```assembly
or x9, x10, x11      # x9 = x10 | x11
```

**Practical Example - Setting Bits:**

```
x10 = 1010 1100 0000 0000
x11 = 0000 0000 1111 1111  (set lower 8 bits)
x9  = 1010 1100 1111 1111  (result: lower 8 bits set to 1)
```

---

## 20. XOR Operation

### Function

**Calculates 1 only if values are DIFFERENT in the two operands**

### Truth Table

```
A   B   A XOR B
0   0      0
0   1      1
1   0      1
1   1      0
```

### Primary Use: Toggle and NOT Operations

- **Toggle bits**: Flip specific bits
- **NOT operation**: XOR with all 1s
- **Comparison**: XOR result of 0 means values are equal

### Example

```assembly
xor x9, x10, x12     # x9 = x10 ^ x12
```

**Practical Example - Toggle:**

```
x10 = 1010 1100 1111 0000
x12 = 0000 0000 1111 1111  (toggle lower 8 bits)
x9  = 1010 1100 0000 1111  (result: lower 8 bits flipped)
```

**NOT operation:**

```assembly
# To negate all bits in x10:
xor x9, x10, x11     # where x11 = all 1s
```

---

## 21. Conditional Branch Instructions

### Purpose

**Make decisions in programs** - execute different code based on conditions

### Basic Branch Instructions

**1. Branch if Equal (beq)**

```assembly
beq rs1, rs2, Label
```

- If rs1 == rs2, jump to Label
- Otherwise, continue to next instruction

**2. Branch if Not Equal (bne)**

```assembly
bne rs1, rs2, Label
```

- If rs1 != rs2, jump to Label
- Otherwise, continue to next instruction

### IF Statement Example

**C Code:**

```c
if (i == j)
    f = g + h;
else
    f = g - h;
```

**Register Assignment:**

- i → x22, j → x23
- f → x19, g → x20, h → x21

**RISC-V Assembly:**

```assembly
       bne x22, x23, Else    # if i != j, go to Else
       add x19, x20, x21     # f = g + h
       beq x0, x0, Exit      # unconditional jump to Exit
Else:  sub x19, x20, x21     # f = g - h
Exit:  ...
```

**Note:** `beq x0, x0, Exit` is always true (x0 always equals x0), creating an unconditional branch.

### WHILE Loop Example

**C Code:**

```c
while (i != j) {
    i += 1;
}
```

**RISC-V Assembly:**

```assembly
Loop:  beq x22, x24, Exit    # if i == j, exit loop
       addi x22, x22, 1      # i = i + 1
       beq x0, x0, Loop      # jump back to Loop
Exit:  ...
```

### Additional Branch Instructions

**Comparison Operations:**

- **blt rs1, rs2, Label**: Branch if rs1 < rs2 (signed)
- **bge rs1, rs2, Label**: Branch if rs1 ≥ rs2 (signed)
- **bltu rs1, rs2, Label**: Branch if rs1 < rs2 (unsigned)
- **bgeu rs1, rs2, Label**: Branch if rs1 ≥ rs2 (unsigned)

### Case/Switch Statements

Simplest implementation: Convert to chain of if-then-else statements

---

## 22. Branch Instructions: Detailed Mechanics

### Program Counter (PC)

- **Register that holds address of current instruction**
- Normally increments by 4 (for 32-bit instructions)
- Modified by branch instructions

### Branch Behavior

**Branch Not Taken:**

```
PC = PC + 4  (execute next sequential instruction)
```

**Branch Taken:**

```
PC = PC + Offset  (jump to target address)
```

### Branch Target Address

**Definition:** The address where execution continues if branch is taken

**Calculation (PC-Relative Addressing):**

```
Branch Target Address = PC + Offset
```

**Why PC-relative?**

- Makes code position-independent
- Enables relocatable code
- Offset is relative to current position

### Address Calculation Example

```assembly
       bne x22, x23, Else    # PC = 4
       add x19, x20, x21     # PC = 8
       beq x0, x0, Exit      # PC = 12
Else:  sub x19, x20, x21     # PC = 16
Exit:  ...                   # PC = 20
```

**For `bne x22, x23, Else` at PC = 4:**

- Target is at PC = 16
- Offset = 16 - 4 = 12 bytes
- Need to skip 3 instructions (12 bytes)

### Offset Calculation

```
Offset = Target Address - Current PC
Offset = Number of instructions to skip × 4
```

---

## 23. SB-Format (Branch Format)

### Structure

```
| imm[12] | imm[10:5] | rs2 | rs1 | funct3 | imm[4:1] | imm[11] | opcode |
    1         6         5     5      3          4         1         7
```

### 12-Bit Immediate Field

**These 12 bits store the offset for branching**

### Clever Optimization: Implicit Bit 0

**Observation:**

- 32-bit instructions are always 4-byte aligned
- Valid PC values: 0, 4, 8, 12, 16, 20...
- In binary: ...0000, ...0100, ...1000, ...1100
- **Least significant bit is ALWAYS 0**

**Optimization:**

- Don't store bit 0 (always 0)
- Store bits [12:1] instead of [11:0]
- **Effective range**: 13 bits worth of addressing
- Multiply effective range by 2

### Bit Arrangement

**Immediate bits stored as:**

- imm[12]: bit 31 (sign bit)
- imm[10:5]: bits 30-25
- imm[4:1]: bits 11-8
- imm[11]: bit 7

**Why this strange order?**

- Keeps opcode, funct3, rs1, rs2 in standard positions
- Simplifies hardware decoder
- Allows sign bit to be in consistent position

### Example: bne x22, x23, 0xC

**Offset = 12 (0x0C)**

**Binary representation:**

```
12 in binary: 0000 0000 1100
```

**Since we skip bit 0:**

```
Store bits [12:1]: 0000 0000 0110 (shift right by 1)
                   000000000110
```

**SB-Format encoding:**

```
0 000000 10111 10110 001 0110 0 1100011
│   │      │     │    │    │   │    │
│   │      │     │    │    │   │    └─ opcode (branch)
│   │      │     │    │    │   └────── imm[11]
│   │      │     │    │    └────────── imm[4:1]
│   │      │     │    └─────────────── funct3 (bne)
│   │      │     └──────────────────── rs1 (x22)
│   │      └────────────────────────── rs2 (x23)
│   └───────────────────────────────── imm[10:5]
└───────────────────────────────────── imm[12] (sign)
```

### Reconstruction Process

**When hardware executes:**

1. Extract immediate bits from instruction
2. Assemble: imm[12:1]
3. Add implicit 0 as bit 0: imm[12:0]
4. Sign-extend to full width
5. Add to PC

---

## 24. RISC-V Addressing Summary

### 1. Register Addressing

**Operand is in a register**

```assembly
add x9, x20, x21
```

- Direct access to register contents
- Fastest addressing mode

### 2. Immediate Addressing

**Operand is a constant within the instruction**

```assembly
addi x9, x20, 100
```

- Constant encoded in instruction
- No memory access needed

### 3. Base (Displacement) Addressing

**Operand in memory, address = register + constant**

```assembly
ld x9, 64(x20)
sd x9, 96(x20)
```

- Used for array access, structure fields
- Base register + offset

### 4. PC-Relative Addressing

**Address = PC + offset**

```assembly
beq x9, x10, Label
```

- Used for branches
- Position-independent code
- Offset encoded in instruction

---

## 25. Comparison with x86 Architecture

### Number of Registers

**x86 (80386):**

- Only 8 general-purpose registers
- Limited register availability

**RISC-V:**

- 32 general-purpose registers
- 4× more registers = fewer memory accesses

### Source/Destination Operands

**x86:**

- One operand must act as both source and destination
- Example: `add eax, ebx` → `eax = eax + ebx`
- Destructive operations

**RISC-V:**

- Separate registers for source and destination
- Example: `add x9, x20, x21` → `x9 = x20 + x21`
- Non-destructive, preserves original values

### Memory Operands

**x86 (CISC philosophy):**

- Any instruction may have one operand in memory
- Example: `add eax, [memory]`
- Complex addressing modes

**RISC-V (RISC philosophy):**

- Only load/store instructions access memory
- Arithmetic operations only on registers
- Load-store architecture

### Summary Table

|Feature|x86 (CISC)|RISC-V (RISC)|
|---|---|---|
|Registers|8|32|
|Instruction Length|Variable|Fixed (32-bit)|
|Memory Access|Any instruction|Load/Store only|
|Operand Reuse|Forced|Optional|
|Complexity|High|Low|

---

## 26. Common Fallacies

### Fallacy 1: More Powerful Instructions = Higher Performance

**The Claim:**

- Complex instructions require fewer total instructions
- Fewer instructions should mean better performance

**The Reality:**

- **Complex instructions are hard to implement**
    
    - Require more transistors
    - Longer design time
    - More testing needed
- **May slow down ALL instructions**
    
    - Complex circuitry increases critical path
    - Even simple operations become slower
    - Higher clock cycle time
- **Compilers are effective**
    
    - Modern compilers generate efficient code from simple instructions
    - Optimization techniques work well with regular instruction sets
    - Predictable performance

**Conclusion:** Simplicity often leads to better overall performance.

### Fallacy 2: Assembly Language Gives Highest Performance

**The Claim:**

- Hand-written assembly is faster than compiled code
- Programmers can optimize better than compilers

**The Reality:**

- **Modern compilers are sophisticated**
    
    - Advanced optimization algorithms
    - Global optimization across entire programs
    - Machine-specific optimizations
- **Compiler advantages:**
    
    - Can analyze entire program flow
    - Apply complex transformations
    - Adapt to specific processor features
    - Consistent optimization
- **Assembly disadvantages:**
    
    - More lines of code = more bugs
    - Time-consuming to write and maintain
    - Less portable across processors
    - Harder to optimize globally
    - Lower productivity

**Exceptions:**

- Critical inner loops (rare)
- Special hardware features not exposed by compiler
- Embedded systems with specific constraints

**Conclusion:** Use high-level languages; resort to assembly only when profiling shows specific bottlenecks.

---

## Summary of Design Principles

### 1. Simplicity Favors Regularity

- Consistent instruction format
- All arithmetic instructions have 3 operands
- Makes hardware simpler and faster

### 2. Smaller is Faster

- Limited number of registers (32)
- Faster access time
- Lower power consumption

### 3. Make the Common Case Fast

- Immediate operands for constants
- PC-relative addressing for branches
- Optimize frequent operations

### 4. Good Design Demands Good Compromises

- Multiple instruction formats (R, I, S, SB, U, UJ)
- Balance between simplicity and functionality
- Fixed length with format variety

---

## Key Takeaways

1. **ISA is the contract** between hardware and software
2. **RISC philosophy** emphasizes simplicity and regularity
3. **Registers are fast** but limited; memory is large but slow
4. **All instructions are 32 bits** in RISC-V for hardware simplicity
5. **Different formats** handle different instruction types efficiently
6. **Load-store architecture** separates computation from memory access
7. **2's complement** is standard for signed integers
8. **PC-relative addressing** enables position-independent code
9. **Compilers matter** more than individual instruction power
10. **Design tradeoffs** balance multiple competing goals

This comprehensive set of notes covers all topics from the lecture on Instruction Set Architecture, providing detailed explanations, examples, and practical insights for understanding RISC-V and ISA concepts.