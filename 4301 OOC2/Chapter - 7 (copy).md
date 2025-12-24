# Chapter 7: Mastering Inheritance and Composition

## Core Concepts
[cite_start]Inheritance and composition are the two primary mechanisms for object reuse in Object-Oriented (OO) systems[cite: 562, 564, 566].
- [cite_start]**Inheritance**: Defined by a **"Is-a"** relationship (e.g., a Dog *is a* Mammal)[cite: 572, 606].
    - [cite_start]It involves a true parent/child relationship where the child (subclass) inherits attributes and behaviors directly from the parent (superclass)[cite: 565].
    - [cite_start]Primarily used to move from general to specific (Generalization-Specialization) by factoring out commonality[cite: 686, 693].
- [cite_start]**Composition**: Defined by a **"Has-a"** relationship (e.g., a Car *has an* Engine)[cite: 576].
    - [cite_start]It involves building complex objects by assembling them from other, simpler objects[cite: 574, 575].
    - [cite_start]There is no parent/child relationship; objects are standalone and used as fields within a complex object[cite: 575].

## Deep Dive: Inheritance
### The "Is-a" Rule
- [cite_start]A simple rule to determine valid inheritance: If you can say "Class B **is a** Class A", then inheritance is likely appropriate[cite: 604].
- **Example**: `GoldenRetriever` is a `Dog`. [cite_start]Therefore, `GoldenRetriever` can inherit from `Dog`[cite: 619, 620].

### Benefits of Inheritance
1. [cite_start]**Code Reuse**: Write common code once in a superclass (e.g., `bark` and `pant` in `Dog`) and reuse it in all subclasses (`GoldenRetriever`, `LhasaApso`)[cite: 629].
2. [cite_start]**Maintenance**: Changes to the superclass (e.g., fixing a bug in `bark`) automatically propagate to all subclasses, saving time and reducing errors[cite: 630, 659].
3. [cite_start]**Polymorphism**: Allows generic code to interact with any subclass (e.g., `Shape.draw()`) without knowing the specific type[cite: 440, 468, 523].

### The Pitfalls of Inheritance
- [cite_start]**Weakened Encapsulation**: Inheritance implies strong encapsulation *between* classes but weak encapsulation *between superclass and subclass*[cite: 374, 388].
    - [cite_start]**Ripple Effect**: Changes to a superclass's implementation can break subclasses, even if the public interface remains the same[cite: 375, 389]. [cite_start]This makes testing difficult[cite: 391].
- **The "Flying Bird" Dilemma**:
    - [cite_start]Problem: If a `Bird` class has a `fly` method, a `Penguin` subclass inherits it but shouldn't (penguins waddle, they don't fly)[cite: 663, 665, 670].
    - Solution: Overriding `fly` to do nothing or throw an error is messy. [cite_start]The hierarchy might need refactoring[cite: 666].
- **The "Barking Dog" Dilemma**:
    - Problem: If `Dog` has a `bark` method, it forces all dogs to bark. [cite_start]But the Basenji breed yodels instead of barking[cite: 673, 674, 675].
    - [cite_start]Solution: Refactor into `BarkingDog` and `YodelingDog` subclasses[cite: 678, 680].

### Generalization-Specialization
- [cite_start]The inheritance tree should move from the most general case (root) to the most specific case (leaves)[cite: 689, 690].
- [cite_start]**Factoring Out Commonality**: Identify shared behaviors (like panting) and move them up the hierarchy (to `Dog`), while keeping specific behaviors (like retrieving or guarding) lower down (`GoldenRetriever`)[cite: 694, 697].

## Deep Dive: Composition
### The "Has-a" Rule
- [cite_start]Objects are often composed of other objects[cite: 754].
- **Example**: A `Car` *has an* `Engine`. [cite_start]The engine is a separate object that can exist independently (e.g., be moved to another car)[cite: 576, 757].

### Composition in UML
- [cite_start]Represented by a line with a **diamond** shape on the container side[cite: 308, 310].
- **Aggregation vs. Association**:
    - [cite_start]**Aggregation**: Represented by a diamond (e.g., Engine is part of Car)[cite: 308].
    - [cite_start]**Association**: Represented by a simple line (e.g., a Keyboard is associated with a Computer box)[cite: 309].

### Multi-level Composition
- [cite_start]Composition often has multiple layers[cite: 313].
- **Example**: A `Car` has a `Stereo`. The `Stereo` has a `Radio`. [cite_start]The `Radio` has a `Tuner`[cite: 346, 347].

## Design Trade-offs & Decisions
### Complexity vs. Accuracy
- [cite_start]**The Conundrum**: A more accurate model (e.g., separate classes for `BarkingDog` vs `YodelingDog`) is often more complex[cite: 708, 709].
- **The Goal**: Balance flexibility with simplicity. [cite_start]Don't add complexity if it doesn't provide business value (e.g., if you never breed yodeling dogs, don't model them)[cite: 720, 722].
- **Golden Rule**: Use inheritance for strict "is-a" relationships. Use composition for "has-a" assembly. [cite_start]Many designers favor composition because it is more flexible and avoids inheritance's encapsulation issues[cite: 525, 597].

## Polymorphism
- [cite_start]**Definition**: The ability to send the same message (e.g., `draw`) to different objects and have them respond appropriately according to their specific type[cite: 441, 468].
- [cite_start]**Key Concept**: Objects should be responsible for themselves[cite: 440, 469].
- **Example**:
    - [cite_start]`Shape` defines an abstract `draw` method[cite: 472].
    - [cite_start]`Circle`, `Rectangle`, and `Star` override `draw` with their own implementations[cite: 487, 488, 492].
    - [cite_start]A method like `drawMe(Shape s)` can accept *any* shape and call `s.draw()` without knowing the specific class[cite: 522, 523].