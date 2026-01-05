**Tags:** #XML #OOP #DataPortability #SoftwareArchitecture #Interoperability

## 1. Introduction: The Portability Equation
Object-Oriented (OO) technology has advanced not just in code portability, but in data portability.

*   **Code Portability:**
    *   **Java:** Uses bytecodes and the JVM to run on any platform.
    *   **.NET:** Uses assemblies to allow interoperability between languages (C#, VB.NET).
*   **Data Portability (The Missing Half):**
    *   Programs process data to create information.
    *   **XML (Extensible Markup Language)** provides the standard mechanism for defining and transporting data between potentially disparate systems.

---

## 2. The Business Problem: Incompatible Data
Historically, businesses struggle with diverse storage formats (e.g., Oracle vs. SQL Server).

### The Scenario
*   **Alpha Company:** Uses an **Oracle** database for Sales.
*   **Beta Company:** Uses a **SQL Server** database for Purchasing.
*   **Goal:** Electronic commerce (Alpha selling to Beta) without direct database connections.
*   **Solution:** Use XML as the intermediary "portable data" layer.

### XML Application Directions
Data moves in two primary directions within the enterprise and industry:

#### 1. Vertical Applications (Vocabularies)
Vertical applications focus on **depth** within a single industry. They are designed by and for specialists to capture the complex, unique nuances of their specific field.

*   **Logic:** A bank and a restaurant have completely different data needs. They create specialized XML tags (vocabularies) that only make sense within their "silo."
*   **Examples:**
    *   **FpML (Financial Products Markup Language):** Used exclusively by the financial industry to describe complex derivatives and structured products.
    *   **RecipeML:** Used by the food, hotels, and publishing industries to define ingredients, cooking times, and portions.
*   **Outcome:** High precision and seamless data exchange between different companies within the same sector.

#### 2. Horizontal Applications
Horizontal applications focus on **breadth** across multiple industries. They address business functions that are universal, regardless of what the company actually produces or sells.

*   **Logic:** Every business—whether it’s a hospital, a law firm, or a factory—needs to perform certain functions like billing, shipping, or inventory management. Horizontal XML standards provide a "common language" for these tasks.
*   **Example (E-commerce):** An XML standard for an **Electronic Invoice** or a **Purchase Order** is horizontal. A car manufacturer (Automotive) can send the same XML invoice format to a shipping company (Transportation) because the *function* of billing is identical across both.
*   **Outcome:** Global interoperability, allowing diverse industries to communicate efficiently for shared business processes.

> [!note] Definition: Silo
> In an industrial context, a **silo** refers to an isolated environment or a distinct sector that operates independently.
> - **Isolation:** Data/standards within one silo (e.g., Finance) don't naturally mix with another (e.g., Healthcare).
> - **Vertical Flow:** Vertical applications are designed to work strictly *inside* these walls.
> - **Breaking the Silo:** Horizontal applications allow data to flow "sideways" between these separate towers.

### Summary: Vertical vs. Horizontal

| Feature | Vertical Applications | Horizontal Applications |
| :--- | :--- | :--- |
| **Focus** | Industry-specific (The "Who") | Function-specific (The "What") |
| **Scope** | Narrow and Deep | Broad and Universal |
| **Goal** | Domain expertise & precision | Interoperability & efficiency |
| **Direction** | Within an industry "silo" | Across different industry "silos" |

> [!INFO] Visualizing Data Movement
> **Figure 11.1 Representation:** Data flows horizontally across departments (Accounting, Management) and vertically through specific industries (Manufacturing, Transportation).

---

## 3. XML vs. HTML
Both are descendants of **SGML** (Standard Generalized Markup Language, standardized in the 1980s).

| Feature              | HTML (Hypertext Markup Language)               | XML (Extensible Markup Language)              |
| :------------------- | :--------------------------------------------- | :-------------------------------------------- |
| **Primary Function** | **Present** and format data.                   | **Describe** and define data.                 |
| **Tags**             | Predefined (e.g., `<body>`, `<font>`).         | User-defined (e.g., `<supplier>`, `<price>`). |
| **Strictness**       | Loose. Browsers "guess" if tags aren't closed. | Strict. Must be "Well-Formed."                |
| **Ownership**        | Open Standard.                                 | Open Standard (W3C).                          |
| **Validation**       | No inherent data verification.                 | Can be validated via DTD.                     |

### Key Differences Explained
1.  **Primary Function:**
    *   **HTML (Presentation):** Focuses on **how** the data looks. It instructs the browser to render text as bold, blue, or arranged in a table.
    *   **XML (Description):** Focuses on **what** the data is. It describes the meaning of the content (e.g., `<price>`, `<author>`) for storage and transport, independent of display.

2.  **Validation:**
    *   **HTML (Loose):** Browsers are forgiving. If tags are missing or incorrectly nested, the browser "guesses" how to display the content rather than crashing or showing an error. It does not verify if the data content is logical.
    *   **XML (Strict):** Can be strictly validated using a **DTD** or Schema.
        *   **Well-Formed:** Follows basic syntax rules.
        *   **Valid:** Conforms to specific structural rules (e.g., a `<supplier>` tag *must* contain an `<address>` tag). If it violates these rules, the parser rejects it.

### Advantages of XML
1.  **Well-Formed:** Strict syntax ensures reliability.
2.  **Validity:** Can use a DTD (Document Type Definition) to enforce rules.
3.  **Open Technology:** Embraced by Microsoft, IBM, Sun, etc.

---

## 4. Architecture: Sharing Data
To share data between Alpha and Beta companies, a "Parser" is used.

**The Workflow:**
1.  **Alpha Co:** Extracts data from SQL Server.
2.  **Alpha App:** Uses a parser/writer to convert data to **XML**.
3.  **Transport:** XML is sent over the Internet.
4.  **Beta Co:** Receives XML.
5.  **Beta App:** Uses a **Parser** to read XML and extract data.
6.  **Beta Co:** Inserts data into Oracle Database.

### Visual: Application-to-Application Data Transfer
(Based on Figure 11.2)

```mermaid
flowchart LR
    subgraph Alpha Company
    A[SQL Server DB] -->|Extract| B(App/Parser)
    B -->|Generate| C[XML Document]
    end

    C -.->|Internet Transfer| D[XML Document]

    subgraph Beta Company
    D -->|Read| E(App/Parser)
    E -->|Insert| F[Oracle DB]
    end
```

> **Definition: Parser**
> A program that reads a document, checks for syntax/grammar rules, and extracts specific information. Compilers also use parsers.

---

## 5. Validating XML: The DTD
XML documents can be checked for structural correctness using a **Document Type Definition (DTD)**.

> [!note] Document Validity
> An XML document that specifies a DTD is either valid or invalid based on the DTD. If a document does not specify a DTD, the XML document is not judged either valid or invalid. An XML document can specify a DTD internally or externally. Because external DTDs provide a very powerful mechanism, we will use an external DTD here. The DTD is where you define the tags that describe your data. When you create an XML document, you can only use tags that are predefined. All XML documents are checked for validity. The XML processor reads the DTD and determines whether the document is valid. If the document is not valid, a syntax error is produced.

*   **Well-Formed:** The XML follows basic syntax (tags nested correctly, root element exists).
*   **Valid:** The XML specifically conforms to the rules defined in a DTD.

### Data Specification Table
| Object Category | Fields / Elements |
| :--- | :--- |
| **Supplier** | name, address |
| **Name** | companyname |
| **Address** | street, city, state, zip |
| **Product** | type, price, count |

### Example: The Supplier DTD
We want to transfer a Supplier object containing a Name, Address, and Product info.

**The Data Structure (Tree):**
*   Supplier
    *   Name
        *   CompanyName
    *   Address
        *   Street, City, State, Zip
    *   Product
        *   Type, Price, Count

**Code: `supplier.dtd`**
```xml
<!-- DTD for supplier document -->
<!ELEMENT supplier ( name, address, product)>
<!ELEMENT name ( companyname)>
<!ELEMENT companyname ( #PCDATA)>
<!ELEMENT address ( street+, city, state, zip)>
<!ELEMENT street ( #PCDATA)>
<!ELEMENT city ( #PCDATA)>
<!ELEMENT state ( #PCDATA)>
<!ELEMENT zip ( #PCDATA)>
<!ELEMENT product ( type, price, count)>
<!ELEMENT type ( #PCDATA)>
<!ELEMENT price ( #PCDATA)>
<!ELEMENT count ( #PCDATA)>
```

> [!help] PCDATA
> PCDATA stands for Parsed Character Data and is simply standard character information parsed from the text file. Any numbers, such as integers, will need to be converted by the parser.

> [!TIP] DTD Occurrence Indicators (Cardinality)
> In the DTD example `<!ELEMENT address ( street+, city, state, zip)>`, symbols are used to define how many times an element can appear:
>
> | Symbol | Name | Meaning | Frequency |
> | :--- | :--- | :--- | :--- |
> | **(None)** | Default | Exactly one | 1 |
> | **`?`** | Question Mark | Zero or one (Optional) | 0 or 1 |
> | **`*`** | Asterisk | Zero or more (Optional & Repeatable) | 0, 1, 2... |
> | **`+`** | Plus Sign | **One or more (Mandatory & Repeatable)** | **1, 2, 3...** |
>
> **Example Analysis: `street+`**
> - **Mandatory:** Every `<address>` must have at least one `<street>` tag.
> - **Repeatable:** Allows for multi-line addresses (e.g., `<street>Line 1</street>`, `<street>Line 2</street>`).

---

## 6. The XML Document
The actual data file (`.xml`) must link to the DTD to be validated.

**Code: `beta.xml`**
```xml
<?xml version="1.0" standalone="no" ?>
<!DOCTYPE supplier SYSTEM "supplier.dtd">
<!-- The Beta Company -->
<supplier>
    <name>
        <companyname>The Beta Company</companyname>
    </name>
    <address>
        <street>12000 Ontario St</street>
        <city>Cleveland</city>
        <state>OH</state>
        <zip>24388</zip>
    </address>
    <product>
        <type>Vacuum Cleaner</type>
        <price>50.00</price>
        <count>20</count>
    </product>
</supplier>
```

### Abstraction in XML
*   **Abstract Tags:** Tags like `<address>` contain no data themselves; they only contain other tags.
*   **Concrete Tags:** Tags like `<street>` contain the actual data (PCDATA).

---

## 7. Tools and Error Handling

### XML Notepad
A tool (formerly from Microsoft) used to visualize XML structure and validate against DTDs.
*   **Visualizing:** Shows a tree view (Structure) and data view (Values).
*   **Validation:** If you remove a required tag (e.g., `<name>`) from the XML, XML Notepad throws a specific error:
    > *Element content is invalid according to the DTD/Schema. Expecting: address.*    

![[Pasted image 20260105113912.png]]

### Browser Behavior
*   Browsers (like Internet Explorer) can display XML files.
*   **Crucial Difference:** Browsers generally check if a document is *well-formed*, but they may **not** strictly validate against the DTD by default. They will display an invalid file (missing tags) without error, whereas a validating parser (like XML Notepad) will stop the process.

---

## 8. Formatting XML with CSS
XML defines data, but offers no native presentation. To display it nicely to a user, **Cascading Style Sheets (CSS)** can be used.

### The Mechanism
Add a processing instruction to the top of the XML file:
```xml
<?xml-stylesheet href="supplier.css" type="text/css" ?>
```

**What this line does:**
It acts as a bridge between the raw data and the visual presentation. Since XML doesn't know *how* to look (only *what* it is), this instruction tells the application (browser) to load a separate file for styling rules.

*   **`<?xml-stylesheet ... ?>`**: Identifies this line as a processing instruction for linking a stylesheet.
*   **`href="supplier.css"`**: Points to the location of the external CSS file.
*   **`type="text/css"`**: Informs the parser that the stylesheet is written in CSS format.

![[Pasted image 20260105120129.png]]
### Example CSS (`supplier.css`)
This tells the browser how to render specific XML custom tags.

```css
companyname {
    font-family: Arial, sans-serif;
    font-size: 24pt;
    color: blue;
    display: block; /* Forces a new line */
}

street {
    font-family: "Times New Roman", serif;
    font-size: 12pt;
    color: red;
    display: block;
}

city {
    font-family: "Courier New", serif;
    font-size: 18pt;
    color: black;
    display: block;
}

zip {
    font-family: "Arial Black", sans-serif;
    font-size: 6pt;
    color: green;
    display: block;
}
```

### The Result
When `beta.xml` is opened in a browser with the CSS linked, instead of seeing the raw code tree, the user sees:
*   "The Beta Company" in large Blue Arial text.
*   "12000 Ontario St" in Red Times New Roman.
*   Etc.
![[Pasted image 20260105120159.png]]

---

## 9. Conclusion
*   **Object-Oriented Development** encompasses both Code and Data.
*   **Data** is the driver of business; moving it efficiently is paramount.
*   **XML** is the industry standard for independent applications to share data efficiently and securely.
*   Combining XML (Storage/Transport), DTDs (Validation), and CSS (Presentation) provides a robust portable data system.