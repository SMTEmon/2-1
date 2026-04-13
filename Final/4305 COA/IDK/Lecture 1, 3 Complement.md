### 1. Complementing the Processor and Pipelining (Lectures 4 & 5)

- **The "Why" Behind Design:** Lecture 3 introduces the design principles that shape the RISC-V datapath. For instance, **"Simplicity favors regularity"** is the reason all RISC-V instructions are 32 bits long, which simplifies the Instruction Fetch (IF) stage in your pipelined datapath.
- **ISA as the Blueprint:** Lecture 3 defines the **Instruction Set Architecture (ISA)** as the interface between hardware and software. You cannot build the control unit or the ALU control in Lecture 4 without first understanding the **instruction formats** (R, I, S, etc.) and **opcodes** defined in Lecture 3.
- **Pipelining Foundations:** Lecture 1 introduces "Performance via Pipelining" as one of the **Eight Great Ideas**. It sets the expectation that overlapping instructions improves throughput, a concept you then explored in technical detail during Lecture 5.
- **The Performance Equation:** Lecture 1 establishes that performance depends on **Instruction Count, CPI, and Clock Cycle Time**. Lecture 3 explains how the ISA affects the instruction count, while Lecture 4/5 shows how implementation choices (like single-cycle vs. pipelining) determine the CPI and clock speed.

### 2. Complementing the Memory Hierarchy (Lecture 6)

- **The Principle of Locality:** Lecture 1 introduces the "Hierarchy of Memories" as a strategy to provide a trade-off between **speed, capacity, and cost**. Lecture 6 then expands on this by explaining exactly _how_ caches use temporal and spatial locality to make the "common case fast".
- **Registers vs. Memory:** Lecture 3 highlights that **"Smaller is faster"**, explaining why we use a limited number of 32 registers instead of always accessing main memory. This justifies the top level of the memory hierarchy you studied in Lecture 6.

### 3. Complementing Parallel Processors (Lecture 8)

- **The Power Wall:** Lecture 1 explains the **"Power Wall"**—the physical limit where we could no longer increase clock speeds due to heat dissipation. This provides the historical and physical context for **Lecture 8**, which focuses on the shift from uniprocessors to multiprocessors to continue improving performance.
- **Amdahl’s Law:** Lecture 1 introduces the mathematical foundation for Amdahl’s Law, warning that improving only one part of a system has diminishing returns. Lecture 8 then applies this math to specific **scaling challenges** (strong vs. weak scaling) and load balancing in multicore systems.

### 4. Overarching Design Philosophy

- **Abstraction:** Lecture 1 emphasizes **"Using Abstraction to Simplify Design"**. The ISA you studied in Lecture 3 is the ultimate abstraction, allowing software programmers to write code without needing to know the complex pipelining or cache details you learned in later lectures.
- **Common Case Fast:** This idea from Lecture 1 is seen in Lecture 3 through the use of **Immediate Operands** (addi), which avoid a slow memory load for small constants, and again in Lecture 6 through the use of **Caches**.

**Revision Tip:** When you look at a hardware diagram from Lecture 4 or 5, remember that it is simply the physical "Organization" built to satisfy the "Architecture" (ISA) and "Great Ideas" established in Lectures 1 and 3.