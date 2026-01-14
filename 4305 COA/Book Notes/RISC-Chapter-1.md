## Terms to Know

**Datapath** - the part of the processor that performs data processing operations such as arithmetic and data movement. 
**Instruction** - A single command that tells the processor what operation to perform. 
**ISA** - The defined set of instructions, data types, registers, and memory model that sw uses to communicate w hw.
**ABI** - Application Binary Interface specifies how compiled programs interact with OS and hw at binary level. 
**Throughput** - Amount of work completed per unit time. 
**Fallacy** - A commonly believed but incorrect assumption about computer performance or design
**Pitfall** - A frequent mistake made when designing or evaluating computer systems. 

## Maths

#### Cost of an IC
$$Cost\,per\,Die = \frac{Cost\,per\,Wafer}{Dies\,per\,Wafer * Yield}$$
$$Dies\,per\,Area = \frac{Wafer\,Area}{Die\,Area}$$
$$Yield = \frac{1}{(1+\left( \frac{Defects\,per\,Area\,*\,Die\,Area}{2} \right))^2}$$
#### Performance v Execution Time

>If computer A runs a program in 10 seconds and computer B runs the same program in 15 seconds, how much faster is A than B?

$$Performance_{x}=\frac{1}{Execution_{x}}$$
> We know that $A$ is $n$ times as fast as $B$ if:
> $$\frac{Performance_{A}}{Performance_{B}}=\frac{ExecutionTime_{B}}{ExecutionTime_{A}}$$

#### CPU Time

>Our favorite program runs in 10 seconds on computer A, which has a 2 GHz clock. We are trying to help a computer designer build a computer, B, which will run this program in 6 seconds. The designer has determined that a substantial increase in the clock rate is possible, but this increase will affect the rest of the CPU design,
causing computer B to require 1.2 times as many clock cycles as
computer A for this program. What clock rate should we tell the
designer to target?

>$$CPU \, time_{A} = \frac{CPU\,Clock\,{Cycles_{A}}}{Clock\,Rate_{A}}$$$$10 \sec = \frac{CPU\,clock\,cycles_{A}}{2*10^9 \frac{cycles}{\sec}}$$

#### CPU Clock Cycles 
$$CPU\,Execution\,Time\,for\,a\,Program=CPU\,Clock\,Cycles\,for\,a\,Program * Clock\,Cycle\,Time$$
Suppose we have two implementations of the same instruction set architecture. Computer A has a clock cycle time of 250 ps and a CPI of 2.0 for some program, and computer B has a clock cycle time of 500 ps and a CPI of 1.2 for the same program. Which computer is
faster for this program and by how much?

$$CPU\,Clock\,Cycles_{A} = 1*2.0$$
$$CPU\,Clock\,Cycles = Instructions\,for\,a\,Program * Avg\,Clock\,Cycles\,per\,Instruction$$
$$CPU\,Time=InstructionCount * CPI * Clock\,Cycle\,Time$$

#### CPI for each Instruction Class

>A compiler designer is trying to decide between two code
sequences for a computer. The hardware designers have supplied
the following facts:
> ![[Pasted image 20260113172633.png]]
> For a particular high-level language statement, the compiler
writer is considering two code sequences that require the following
instruction counts:
![[Pasted image 20260113172704.png]]
Which code sequence executes the most instructions? Which will
be faster? What is the CPI for each sequence?

$$CPU\,Clock\,Cycles = \sum_{i=1}^n(CPI_{i}*C_{i})$$
#### Big Formula
$$Time = \frac{Seconds}{Program}=\frac{Instructions}{Program}* \frac{Clock\,Cycles}{Instructions} * \frac{Seconds}{Clock\,Cycle}$$

#### Power Wall
$$Energy \propto Capacity\,Load *Voltage^2$$
$$Power \propto Capacatitive\,Load*Voltage^2*Frequency\,Switched $$

>Suppose we developed a new, simpler processor that has 85% of
>the capacitive load of the more complex older processor. Further,
>assume that it can adjust voltage so that it can reduce voltage 15%
>compared to processor B, which results in a 15% shrink in
>frequency. What is the impact on dynamic power?
>
$$\frac{Power_{new}}{Power_{old}}=\frac{(Capacitative\,Load*0.85)(Voltage*0.85)^2(Frequency\,Switched*0.85)}{Capacitative\,Load*Voltage^2*Frequency\,Switched}$$
#### Comparing Two Computers with SPECratios
$$n\sqrt{\prod_{j=1}^nExecution\,time\,ratio_{i}}$$
Given the increasing importance of energy and power, SPEC added
a benchmark to measure power. It reports power consumption of
servers at different workload levels, divided into 10% increments,
over a period of time.
![[Pasted image 20260113174113.png]]
$$overallssj\,ops/watt = \frac{\left( \sum_{i=0}^{10}ssjops_{i} \right)}{\left( \sum_{i={10}}^{10}power_{i} \right)}$$
#### Amdahl's Law:
>A rule stating that the performance enhancement possible with a
given improvement is limited by the amount that the improved
feature is used. It is a quantitative version of the law of diminishing
returns.

$$ExecTimeAfterImp=\frac{ExecTimeAffectedByImprovement}{Amount Of\mathrm{Im}provement}+ExecTime \,Unaffected$$
#### Million Instructions per Second
>A measurement of program execution speed based on the number
of millions of instructions. MIPS is computed as the instruction
count divided by the product of the execution time and 10^6

$$MIPS = \frac{Instruction\,Count}{\frac{Instruction\,Count}{Clock\,Rate}*CPI*10^6}=\frac{Clock\,Rate}{CPI*10^6}$$

## Eight Great Ideas in Computer Architecture

1. **Design for Moore's Law**
   IC resources double every 18-24 months. By the end of the project, the existing resources available per chip can easily double or quadruple.
   
2. **Use Abstraction to Simplify Design**
   Hiding the lower-level details to offer simpler model at higher levels.
   
3. **Make the Common Case Fast**
   Enhance the performance better than optimizing the rare case. (implies you know what the common case is- only possible to know after careful experimentation and measurement)
   
4. **Performance and Parallelism**
   More performance by computing operations in parallel
   
5. **Performance via Pipelining**
   A particular pattern of parallelism: instead of completing one instruction fully before starting the next, pipelining breaks instruction execution into stages and processes different instructions in different stages at the same time. 

6. **Performance via Prediction**
   In some cases, it can be faster on avg. to guess and start working rather than wait until you know for sure. 
   
7. **Hierarchy of Memories**
   Cost of memory is often the majority of computer cost. Soo,
   fastest memory per bit at the top, slowest at the bottom. (cache vs ram)
   
8. **Dependability via Redundancy**
   We can make systems dependable by including redundant components that can take over when a failure occurs and to help detect those failures. 
