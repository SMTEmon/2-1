### 💡 How To Study This
1. **Do NOT just read the text.** Pipelining is a deeply *visual* topic. 
2. **Side-by-Side Method:** Have these Obsidian notes open on one half of your screen, and **open your PDF slides on the other half**. 
3. Whenever my notes say *(See Slide X)*, look at the diagram. You need to trace the lines with your finger/mouse to understand how the data moves.
4. **External Resource:** If my text and the slide diagrams still don't make sense, pause and watch **"Pipelining - Neso Academy"** or **"Computer Architecture - Crash Course Computer Science #11"** on YouTube. 

***

# 📝 RISC-V Pipelining & Hazards

**Tags:** #ComputerArchitecture #RISC-V #Pipelining #Hazards
**Source:** Lecture 5 - Computer Organization and Architecture

## 1. What is Pipelining? (The Laundry Analogy)
Imagine doing 4 loads of laundry. 
* **Sequential (Single-Cycle):** You wash, dry, fold, and put away Load 1. Only after Load 1 is 100% finished do you start washing Load 2. This takes forever (8 hours).
* **Pipelined:** You put Load 1 in the washer. When Load 1 moves to the dryer, the washer is empty, so you *immediately* put Load 2 in the washer. 

> [!important] The Golden Rules of Pipelining
> 1. Pipelining **DOES NOT** make a single instruction execute faster. (One load of laundry still takes 2 hours).
> 2. Pipelining increases **Throughput** (number of instructions finished per second). By overlapping them, all 4 loads finish in 3.5 hours instead of 8.
> 3. **Ideal Speed-up = Number of stages.** (e.g., A 5-stage pipeline can theoretically be 5x faster than a non-pipelined system).

**Clock Cycle Rule:** 
In a sequential execution, the clock cycle must be as long as the *entire* instruction (e.g., 800ps). In a pipelined execution, the clock cycle only needs to be as long as the **slowest stage** (e.g., 200ps).

---

## 2. The 5 Stages of a RISC-V Instruction
Every instruction in RISC-V is broken down into 5 specific stages that flow left-to-right.

1. **IF (Instruction Fetch):** Grab the instruction from memory using the Program Counter (PC). Update PC to `PC + 4`.
2. **ID (Instruction Decode & Register Read):** Figure out what the instruction means. Read the data from the source registers. Generate control signals.
3. **EX (Execute / Address Calculation):** Use the ALU (Arithmetic Logic Unit). E.g., add two numbers, or calculate a memory address.
4. **MEM (Data Memory Access):** If it's a `Load` or `Store`, read from or write to Data Memory. (If it's an `add` or `sub`, this stage does basically nothing).
5. **WB (Write-Back):** Write the final result back into the destination register.

*(Exceptions to left-to-right flow: WB writes data "backward" to the register file, and IF updates the PC "backward" for loops/branches).*

---

## 3. Pipeline Registers (The Traffic Lights)
Because multiple instructions are moving through the datapath at the same time, we need to prevent them from crashing into each other. 

We place **Pipeline Registers** between every stage to hold the data temporarily while the clock ticks.
* `IF/ID` Register
* `ID/EX` Register
* `EX/MEM` Register
* `MEM/WB` Register
*(Note: There is no pipeline register after WB because the data is already safely written into the actual CPU register).*

### 🛑 The "Destination Register" Catch
Look at a `Load` instruction: `ld x10, 40(x1)`.
It writes to `x10` at the very end (Stage 5 - WB). But how does Stage 5 know to write to `x10`? 
* **Solution:** The destination register number (`x10`) must be passed along like a baton through EVERY pipeline register (`IF/ID` -> `ID/EX` -> `EX/MEM` -> `MEM/WB`). Only in the WB stage is it finally used. *(See slides 27-28)*.

### 🎛️ Control Signals
Control signals tell the CPU what to do (Read memory? Write register? Add or Subtract?). 
Instead of calculating these in every stage, we **calculate all 7 control signals during the ID stage**, put them in the pipeline registers, and carry them along with the instruction to the later stages. *(See Slide 36)*.

---

## 4. Pipeline Hazards
Pipelining is great until instructions get in each other's way. This is called a **Hazard**. There are three main types (your lecture focuses heavily on Data Hazards).

### A. Structural Hazards
The hardware can't support the combination of instructions. 
* *Example:* If the CPU only had ONE memory block instead of separate Instruction Memory and Data Memory. Stage 1 (IF) would try to fetch an instruction at the exact same time Stage 4 (MEM) tries to read data. They would crash.

### B. Data Hazards
This happens when an instruction depends on the result of a *previous* instruction that hasn't finished yet.
```assembly
sub x2, x1, x3   // x2 is updated here (but not actually written until stage 5)
and x12, x2, x5  // This instruction needs x2 in stage 2!
```
By the time `and` needs to read `x2` in the Decode stage, `sub` is only in the Execute stage. The new value of `x2` hasn't been written back yet!

#### Solution 1: Forwarding (Bypassing)
Instead of waiting for the data to be written all the way back to the register file, we build "shortcuts" in the hardware. We grab the data directly from the ALU output (`EX/MEM` register) or Memory output (`MEM/WB` register) and feed it directly into the ALU input of the current instruction. *(See Slides 41-42)*

**Hardware Needed:** Multiplexers (Muxes) before the ALU, controlled by a Forwarding Unit.
* `ForwardA / ForwardB = 00`: Normal (gets data from ID/EX register).
* `ForwardA / ForwardB = 10`: Forward from the EX stage (prior instruction).
* `ForwardA / ForwardB = 01`: Forward from the MEM stage (instruction from 2 cycles ago).

> [!warning] The Double Data Hazard
> What if two instructions in a row write to the same register?
> `add x1, x1, x2`
> `add x1, x1, x3`
> `add x1, x1, x4` <- Which `x1` does this use?
> **Rule:** The EX hazard has priority over the MEM hazard. The forwarding unit will look at the most recent instruction first. *(See Slide 46 for the complex boolean logic)*.

#### Solution 2: Stalling (Inserting a "Bubble")
Forwarding can't fix everything. 
Look at the **Load-Use Hazard**:
```assembly
lw x2, 20(x1)   // x2 is fetched from memory in Stage 4 (MEM)
and x4, x2, x5  // Needs x2 in Stage 3 (EX)
```
Even with forwarding, the data isn't fetched from memory until Stage 4, but the next instruction needs it in Stage 3. **We cannot forward backward in time.**

**How to fix it:** The Hazard Detection Unit pauses the pipeline.
1. It forces the control signals of the dependent instruction to `0`. This turns the instruction into a **nop** (no operation / bubble). It literally does nothing for one cycle.
2. It prevents the `PC` and `IF/ID` registers from updating. This forces the dependent instruction to just sit and wait for one clock cycle.
3. Once the `lw` instruction finishes the MEM stage, the data can now be forwarded, and the pipeline resumes. *(See Slide 51 for a great visual of the "bubble")*.