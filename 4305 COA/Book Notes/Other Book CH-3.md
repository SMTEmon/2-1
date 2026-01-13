Most computers are designed based on the concepts developed by *John Von Neumann*.
The 3 key concepts are:
1. Ability to write/ read data from memory
2. Ability to execute instruction sequentially
3. Ability to process inputs/ outputs

### Stuff We Need
#### CPU
- An instruction interpreter capable of generating control signals
- A general-purpose module for Arithmetic/ Logic Functions
#### I/O Module
- A Module that contains basic components for accepting data and instructions in some form and converting them into an internal form of signals usable by the system
- Another means to send back the produced results to us. 
#### Main Memory
- A place to store both instructions and data as operations on data may require access to more than just one element at a time in a predetermined sequence. 
- Also we need to store information when a program jumps around instead of executing instructions sequentially. 

### CPU Internal Registers

1. **PC** : Program Counter - Specifies the memory address of the next instruction to be executed. 
2. **IR**: Instruction Register - Holds the instruction currently being executed or decoded. 
3. **MAR**: Memory Address Register - Specifies memory address to be read/ written on. 
4. **MBR**: Memory Buffer Register - Contains the data to be written into memory/ receives the data from memory
5. **I/OAR**: I/O Address Register: Specifies a particular I/O Device
6. **I/OBR**: I/O Buffer Register: Used for exchange of data between I/O Module and CPU

### Categories 
- **Processor-memory**
	- Data may be transferred from processor to memory or from memory to processor.
- **Processor-I/O**
	- Data may be transferred to or from a peripheral device by transferring between the processor and an I/O module. 
- **Data Processing**
	- The processor may perform some arithmetic or logic operation on data.
- **Control**
	- An instruction may specify that the sequence of execution be altered.
	  
>[!Question] 
>Assume that the program counter is set to memory location 300, where the
location address refers to a 16-bit word. The processor will next fetch the
instruction at location 300. After the execution of this instruction, it will
fetch instructions from locations 301, 302, 303, and so on.
>
>The program adds the contents of the memory word at address 940 to the
contents of the memory word at address 941 and stores the result in the
latter location. What will be the steps?
Below is a **simple, standard fetch–execute justification table**, assuming a **basic accumulator-based CPU** (typical in intro computer architecture problems).

### Assumptions (explicit, so the steps make sense)

- Memory is **16-bit word-addressable**
- PC increments by **1 word** after each fetch
- Instructions are **one word**
    
- CPU has:
    
    - **PC** (Program Counter)
    - **IR** (Instruction Register)
    - **AC** (Accumulator)
        
- Instruction set (conceptual):
    
    - `LOAD addr` → AC ← M[addr]
    - `ADD addr` → AC ← AC + M[addr]
    - `STORE addr` → M[addr] ← AC
        

---

## Program (starting at address 300)

|Address|Instruction|Meaning|
|--:|---|---|
|300|`LOAD 940`|Load M[940] into AC|
|301|`ADD 941`|Add M[941] to AC|
|302|`STORE 941`|Store AC into M[941]|

## Step-by-step execution table

|Step|PC|Instruction Location|Instruction Fetched|Data / Action|
|--:|--:|--:|---|---|
|1|300|300|`LOAD 940`|IR ← M[300]|
|2|300|—|Execute `LOAD 940`|AC ← M[940]|
|3|301|301|`ADD 941`|IR ← M[301]|
|4|301|—|Execute `ADD 941`|AC ← AC + M[941]|
|5|302|302|`STORE 941`|IR ← M[302]|
|6|302|—|Execute `STORE 941`|M[941] ← AC|
|7|303|—|Next fetch|PC now points to 303|

## Final result

- Memory location **941** now contains:
$$ 
M[941] = M[941] + M[940]  
$$
- PC is ready to fetch the next instruction at **303**


## States of an Instruction Cycle

1. ==**IAC: Instruction Address Calculation**==- Determine the address of the next instruction to be exec
2. ==**IF: Instruction Fetch-**== Read instruction from memory into the processor
3. ==**IOD: Instruction Operation Decoding**==- Determine type of operation to be performed and operand(s) to be used. 
4. ==**OAC**==: Operand Address Calculation- Determine the address of the operand
5. ==**OF**==: Operand Fetch- Fetch the operand from memory or read it in from I/O
6. ==**DO**==: Data Operation- Perform the operation indicated in the instruction
7. ==**OS**==: Operand Store- Write the result into memory or to I/O.

>[!Question]
>A processor includes an instruction, expressed symbolically as “ADD B,A”,
that stores the sum of the contents of memory locations B and A into
memory location A.

$$ADD\;B,\,A$$

$$IAC → IF → IOD → OAC → OF → OAC → OF → DO → OS$$

| Step | State   | Action                                |
| ---: | ------- | ------------------------------------- |
|    1 | **IAC** | PC → MAR                              |
|    2 | **IF**  | IR ← M[MAR], PC ← PC + 1              |
|    3 | **IOD** | Decode ADD, identify operands A and B |
|    4 | **OAC** | MAR ← A                               |
|    5 | **OF**  | Operand1 ← M[A]                       |
|    6 | **OAC** | MAR ← B                               |
|    7 | **OF**  | Operand2 ← M[B]                       |
|    8 | **DO**  | Result ← Operand1 + Operand2          |
|    9 | **OS**  | M[A] ← Result                         |

>[!Question]
>Consider a system with three I/O devices: a printer, a disk, and a
communications line, with increasing priorities of 2, 4, and 5, respectively.
A user program begins at t = 0. At t = 10, a printer interrupt occurs. While
this routine is still executing, at t = 15, a communications interrupt occurs.
Again while this communication routine is executing, a disk interrupt occurs
at t = 20.
How will the interrupts be handled?

| Time | Event                       | CPU Action                                    | Notes                     |
| ---- | --------------------------- | --------------------------------------------- | ------------------------- |
| 0    | User program starts         | CPU executes user program                     | -                         |
| 10   | Printer interrupt           | Preempt user program, start Printer ISR       | Priority 2 > user program |
| 15   | Communications interrupt    | Preempt Printer ISR, start Communications ISR | Priority 5 > 2            |
| 20   | Disk interrupt              | Held pending                                  | Priority 4 < 5            |
| t1   | Communications ISR finishes | Start Disk ISR                                | Resume from queue         |
| t2   | Disk ISR finishes           | Resume Printer ISR                            | Resume saved context      |
| t3   | Printer ISR finishes        | Resume user program                           | Resume saved context      |

## Stuff

|Topic|Key Points|
|---|---|
|**Interconnection**|Connects CPU, memory, I/O; enables communication; bus or P2P.|
|**Bus Interconnection**|Shared communication path; simple, cost-effective; only one device at a time.|
|**Bus Structure (3 functional groups)**|1. Data lines – carry data 2. Address lines – specify memory/I/O location 3. Control lines – coordinate operations (read/write, clock, interrupt).|
|**Data Lines**|Transfer actual data; width = data size (8/16/32-bit).|
|**Address Lines**|Carry memory/I/O addresses; width = addressable locations.|
|**Control Lines**|Signals for operation control; e.g., Read, Write, Memory/I/O select, Interrupt, Clock.|
|**Bus Length**|Physical distance; longer → slower, timing issues.|
|**Bus Capacity**|Maximum data transfer rate (bits/sec); depends on width and speed.|
|**P2P Interconnection**|Dedicated link between two devices; higher speed, less contention; used in PCIe, QPI.|
|**QPI (QuickPath Interconnect)**|Intel high-speed P2P interconnect; replaces FSB; connects CPU → CPU/memory/I/O.|
|**QPI Layers**|1. Physical – electrical signaling 2. Link – data packets, error detection 3. Protocol – transaction-level handling.|
|**PCI Express (PCIe)**|High-speed serial P2P bus for I/O; uses lanes (x1, x4, x16); scalable, low-latency; replaces PCI/PCI-X.|