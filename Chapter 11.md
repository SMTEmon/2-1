> [!note]
> Head to [[XML]] for intro to XML 

# XML and Object-Oriented Languages: Summary Notes

## 1. The Concept of "Portable Information"
* **Definition:** XML acts as a bridge to provide "portable information" across different platforms and languages.
* **OO Integration:** Object-Oriented (OO) languages like **Java, C#, and VB** interact with XML to handle data exchange between disparate systems.
* **The Problem:** Different companies (e.g., Alpha Co. and Beta Co.) often use different database vendors (Oracle vs. SQL Server) and different internal data schemas, making direct connection impossible.
* **The Solution:** Instead of a proprietary connection, XML provides a **general specification** that all suppliers can conform to.

---

## 2. The Data Exchange Workflow
To transfer data between two different systems, the process generally follows these steps:
1.  **Extraction:** An application (written in an OO language) extracts data from the source database (e.g., SQL Server).
2.  **Generation:** The application formats that data into an **XML document** based on an agreed-upon standard.
3.  **Transmission:** The XML document is sent over the network/Internet.
4.  **Parsing:** The receiving company uses a **parser** to read the XML.
5.  **Conversion:** The parser converts the XML data into the format required by the destination database (e.g., Oracle).



---

## 3. Parsers
* **Role:** A program that reads a document and extracts specific information based on grammar rules.
* **Analogy:** Similar to a compiler, which parses code to ensure it follows appropriate syntax (e.g., checking a `print` statement).
* **Function in XML:** It validates the document against a set of rules and makes the data accessible to the application.

---

## 4. Document Validation (DTD)
To ensure both companies speak the same "language," they use a **Document Type Definition (DTD)**. This defines the structure and nesting of the data.

### Example DTD Structure (from Listing 11.1):
* **Supplier Object:** The root element containing `name` and `address`.
* **Nesting:** Data is hierarchical (e.g., `address` contains `street`, `city`, `state`, and `zip`).
* **Key Syntax:** * `#PCDATA`: Refers to "Parsed Character Data" (the actual text content).
    * `+`: Indicates that an element (like `street`) can appear one or more times.

### Data Specification Table
| Object Category | Fields / Elements |
| :--- | :--- |
| **Supplier** | name, address |
| **Name** | companyname |
| **Address** | street, city, state, zip |
| **Product** | type, price, count |

---

> **Key Takeaway:** XML provides the **structure** for the data, while Object-Oriented languages provide the **logic** to move, process, and store that data across different environments.


# Validating the Document with the Document Type Definition (DTD)

>[!note] Document Validity
> An XML document that specifies a DTD is either valid or invalid based on the DTD. If a document does not specify a DTD, the XML document is not judged either valid or invalid. An XML document can specify a DTD internally or externally. Because external DTDs provide a very powerful mechanism, we will use an external DTD here. The DTD is where you define the tags that describe your data. When you create an XML document, you can only use tags that are predefined. All XML documents are checked for validity. The XML processor reads the DTD and determines whether the document is valid. If the document is not valid, a syntax error is produced.


```xml
<!— DTD for supplier document —>
<!ELEMENT supplier ( name, address)>
<!ELEMENT name ( companyname)>
<!ELEMENT companyname ( #PCDATA)>
<!ELEMENT address ( street+, city, state, zip)>
<!ELEMENT street ( #PCDATA)>
<!ELEMENT city ( #PCDATA)>
<!ELEMENT state ( #PCDATA)>
<!ELEMENT zip ( #PCDATA)>
```
The DTD defines how the XML document is constructed. It is composed of tags that look very similar to HTML tags. The first line is an XML comment.
```xml
<!ELEMENT supplier ( name, address, product)>
```

This tag defines an element called supplier. As specified in the DTD above, a
supplier contains a name, an address, and a product. Thus, when an XML parser actually parses an XML document, the document must be a supplier, which contains a name, an address, and a product.

The ``<companyname>`` element is then defined to be a data element designated by ``#PCDATA``.


> [!help] PCDATA
> PCDATA stands for Parsed Character Data and is simply standard character information parsed from the text file. Any numbers, such as integers, will need to be converted by the parser.

### Integrating the DTD into the XML Document

> [!example] Raw XML Source 
> ```xml
> <?xml version="1.0" standalone="no"?>
> <!DOCTYPE supplier SYSTEM "supplier.dtd">
> > <supplier>
>   <name>
>     <companyname>The Beta Company</companyname>
>   </name>
>   <address>
>     <street>12000 ontario st</street>
>     <city>cleveland</city>
>     <state>OH</state>
>     <zip>24388</zip>
>   </address>
>   <product>
>     <type>Vacuum Cleaner</type>
>     <price>50.00</price>
>     <count>20</count>
>   </product>
> </supplier>
> ```


Note that the second line ties this document to the supplier DTD that we defined earlier. ``<!DOCTYPE supplier SYSTEM “supplier.dtd”>``

### Implementation: Linking CSS to XML

```xml
<?xml version=”1.0” standalone=”no”?>
<?xml-stylesheet href=”supplier.css” type=”text/css” ?>
<?xml-stylesheet type="text/css" href="styles.css"?>
<!— The XML data —>
<name>
    <companyname>The Beta Company</companyname>
  </name>
  <address>
    <street>12000 ontario st</street>
    <city>cleveland</city>
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

