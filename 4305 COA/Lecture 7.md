
## Input-Output Devices Classification

External devices are classified into **three categories**:

1. **Human readable**: For communicating with computer users
    
    - Examples: video display terminals, printers
2. **Machine readable**: For communicating with equipment
    
    - Examples: magnetic disks, tape systems, sensors, actuators
3. **Communication**: For communicating with remote devices
    
    - Examples: wifi, modem

**Key Point**: Different devices have different requirements regarding peripheral logic, peripheral speed, and peripheral data protocol.

## Why Can't We Directly Connect I/O Devices to System Bus?

**Answer: NO, we cannot directly connect I/O devices to the system bus.**

### Three Main Reasons:

**1. Wide Variety of Peripherals**

- Each peripheral has its own method of operation
- Impractical to incorporate diverse set of logic within the processor

**2. Data Transfer Rate Mismatch**

- Peripherals often operate much slower than processor speed or memory
- Impractical to use high-speed system bus to communicate directly
- Transfer rate may also be faster than memory/processor
- Mismatch would lead to inefficiencies if not managed properly

**3. Data Format Differences**

- Peripherals use different communication protocols
- Data format not necessarily the same as the computer
- Word length not necessarily the same as the computer
- Processor would have to convert these back-and-forth

## Solution: I/O Module

Since processor speed is usually faster than peripherals, there's no need to slow down the processor for I/O interaction.

**Solution: Create a separate entity called the I/O Module**

### I/O Module Responsibilities:

- Manage communication with peripherals
- Store data input/output from and to peripherals
- Detect errors

## Main Components of an External Device

1. **Control Signals**: Determine the function the device will perform
    
    - Send data to I/O module
    - Accept data from I/O module
    - Report status
    - Perform device-specific functions (e.g., position a disk head)
2. **Data Signals**: Set of bits to be sent to or received from the I/O module
    
3. **Status Signals**: Indicate the state of the device
    
    - Example: READY/NOT-READY to show whether device is ready for data transfer
4. **Control Logic**: Controls the device in response to direction from I/O module
    
5. **Transducer**: Converts data
    
    - From electrical to other forms of energy during output
    - From other forms to electrical during input
6. **Buffer**: To hold data
    

## Major Functions of an I/O Module

### 1. Control and Timing

- Processor may communicate with external devices in unpredictable patterns depending on program's I/O needs
- I/O function includes control and timing requirement to coordinate flow of traffic between resources

### 2. Processor Communication

**a. Command Decoding**: I/O module accepts and decodes commands from processor

- Example commands for disk drive: READ sector, WRITE sector, SEEK track number, SCAN sector ID

**b. Data**: Exchanged between processor and I/O module via data bus

**c. Status Reporting**: Important to know I/O module status

- I/O module may not be ready because of working on previous I/O command
- This needs to be reported with a status signal

**d. Address Recognition**: I/O module has one unique address for each peripheral it controls

### 3. Device Communication

- Commands
- Status information
- Data

### 4. Data Buffering

High transfer rate exists between main memory and processor, but it's lower for external devices.

**From Memory to I/O Module**:

- Data sent from main memory to I/O module are buffered in the module
- Then sent to peripheral device at a data rate the device can sustain

**From I/O Module to Memory**:

- Data are buffered from peripheral so as not to tie up memory in a slow transfer operation
- If I/O device operates at a rate higher than memory access rate, I/O module performs needed buffering operation

### 5. Error Correction

- Mechanical and electrical malfunctions reported by device (e.g., paper jam, bad disk track)
- Unintentional bit changes during device transmission

## I/O Module Structure

### Organization:

- Module connects to computer through a set of signal lines
- Data transferred to and from module are buffered in **data registers**
- **Status registers** provide status information and function as control registers to accept processor control info
- Logic within module interacts with processor via control lines:
    - Processor uses control lines to issue commands to I/O module
    - Some control lines may be used by I/O module (e.g., arbitration and status signals)
- Module must be able to recognize and generate addresses for each device it controls
- I/O module contains logic specific for a set of interfaces

## I/O Commands

To execute an I/O-related instruction, processor needs to issue:

1. **An address** specifying the particular I/O module and external device
2. **An I/O command** which can be of four types:

### Four Types of I/O Commands:

**1. Control**: Used to activate a peripheral and tell it what to do

- Example: Rewind magnetic tape

**2. Test**: Tests I/O module and its peripherals

- Is the peripheral powered on?
- Is the peripheral available for use?
- Has the most recent I/O operation completed?
- Did any errors occur?

**3. Read**: I/O module obtains a data item from the peripheral

- Processor requests I/O module to place data on bus (data is placed in internal buffer)

**4. Write**: I/O module writes a data item to the peripheral

- I/O module reads data from bus
- I/O module transmits data to peripheral

## I/O Transfer Modes

There are **three main I/O transfer modes**:

1. **Programmed I/O**: I/O-to-memory transfer through processor
    
2. **Interrupt-Driven I/O**: I/O-to-memory transfer through processor
    
3. **Direct Memory Access (DMA)**: Direct I/O-to-memory transfer
    

---

## 1. Programmed I/O

### How It Works:

When a program is in execution and an I/O related instruction is encountered:

1. Processor issues a command to the appropriate I/O module
2. I/O module performs the requested action and sets appropriate bits in I/O status register
3. **Processor is not interrupted by I/O module after it is ready**
4. Processor periodically checks (polls) the status of the I/O module

### Process Flow:

- CPU to I/O module (issue command)
- CPU reads status periodically
- If error occurred, handle it
- CPU reads from I/O module
- CPU writes to memory

### Disadvantages:

- Processor has to wait a long time for the I/O module
- Processor must repeatedly interrogate the status of I/O module while waiting
- If processor is faster than I/O module: wasteful of processor time
- Performance of entire system is severely degraded

---

## 2. Interrupt-Driven I/O

### How It Works:

When a program is in execution and an I/O related instruction is encountered:

1. After issuing command to I/O module, **processor returns to perform other useful work** instead of waiting
2. Processor is interrupted when task is done by I/O module

### From I/O Module's Point of View:

- Module waits for processor to request data
- When request is made:
    - Module interacts with peripheral
    - Once data is completely buffered, data are placed on data bus
- An interrupt signal is sent to processor over a control line
- Module becomes available for another I/O operation

### From Processor's Point of View:

1. A READ command is issued to I/O module
2. Processor goes off to do something else
3. Processor checks for interrupts at the end of each instruction cycle
4. When interrupt from I/O module occurs:
    - Processor saves program context
    - Processor proceeds to read data from I/O module
    - Processor stores data in memory
5. Processor restores previous program context
6. Processor resumes execution of previous program

### Process Flow:

- CPU to I/O module, continues other work
- Interrupt occurs and CPU reads the status
- If error occurred, handle it
- CPU reads from I/O module
- CPU writes to memory

### Disadvantage:

**For each transfer of data, it involves the processor**

---

## Interrupt-Based Design Issues

### Issue 1: How does the processor determine which device issued the interrupt?

**Three Solutions:**

**Solution 1: Multiple Interrupt Lines**

- Most straightforward approach
- Impractical to dedicate more than a few bus lines to interrupt lines
- Likely that each line will have multiple I/O modules attached to it
- Not very practical

**Solution 2: Software Poll**

- Processor calls an interrupt routine that polls each I/O module
- I/O module responds positively if it set the interrupt
- **Disadvantage**: Time consuming

**Solution 3: Daisy Chain Method**

- All I/O modules share a common interrupt request line
- When interruption is detected, an interrupt acknowledge (ACK) is sent
- ACK goes through the I/O modules until it gets to the requesting module
- Requesting module responds by placing a word on the data lines
- Word is either:
    - Address of the I/O module, OR
    - Address of an adequate interruption handling technique

### Issue 2: If multiple interrupts have occurred, how does the processor decide which one to process?

**Two Solutions:**

**Solution 1: Multiple Interrupt Lines**

- Each line can have a predetermined priority
- Just choose the highest priority interrupt line

**Solution 2: Software Poll/Daisy Chain**

- In Software Poll: The order in which the modules are polled determines the priority
- In Daisy Chain: The order of modules on a daisy chain determines their priority

---

## 3. Direct Memory Access (DMA)

### Concept:

**Copying data directly to memory, bypassing the processor**

### Key Features:

- Memory accesses are performed by DMA module
- Unburdens the processor
- Combine with interruption scheme for optimum efficiency

### How It Works:

**DMA Module**: An additional module on the system bus

**Process:**

1. **Processor issues commands to DMA module** with the following information:
    
    - Whether to READ or WRITE (using read/write control lines)
    - Address of I/O device involved (using data lines)
    - Starting location of memory to read or write
    - The number of words to read/write
2. **DMA module transfers entire block of data** (bypassing the processor)
    
3. **Processor is only involved at the beginning and ending** of the transfer, as DMA module interrupts the processor after finishing transfer only
    

### Advantages:

- Processor freed up during data transfer
- More efficient for large block transfers
- Better system performance

---

## Summary Comparison of I/O Transfer Modes

|Mode|Processor Involvement|Efficiency|Best For|
|---|---|---|---|
|**Programmed I/O**|Continuous (polling)|Low|Simple, small transfers|
|**Interrupt-Driven I/O**|At start and interrupt|Medium|Moderate transfers|
|**DMA**|Only at start and end|High|Large block transfers|

---

**Reference**: Computer Organization and Architecture by William Stallings, 10th edition

---

## Key Points to Remember for Exam:

1. **Three reasons why I/O devices can't connect directly to system bus**
2. **Five main functions of I/O module** (Control/Timing, Processor Communication, Device Communication, Data Buffering, Error Correction)
3. **Four types of I/O commands** (Control, Test, Read, Write)
4. **Three I/O transfer modes** and their characteristics
5. **Two interrupt-based design issues** and their solutions
6. **DMA advantages** over other methods