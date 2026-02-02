In PostgresSQL:

`BYTEA` -> `byte[]` -> Small binary data
`TEXT/ VARCHAR` -> `String` -> Can be huge, but limited by mem
`OID` -> `java.sql.Blob / Clob` -> Used for very large files

- `Blob` : Binary Large Object
- `Clob` : Character Large Object

Why special?
- You cannot read/ write them all at once if huge
- Must use streams (`InputStream`/ `Reader`)

```
ResultSet rs = stmt.executeQuery("SELECT resume FROM employee WHERE id = 101");
if (rs.next()) {
    Blob resumeBlob = rs.getBlob("resume");
    InputStream is = resumeBlob.getBinaryStream();

    // read byte-by-byte or in chunks
    byte[] buffer = new byte[4096];
    int bytesRead;
    while ((bytesRead = is.read(buffer)) != -1) {
        // process buffer
    }
    is.close();
}
```

---

```
PreparedStatement ps = con.prepareStatement(
    "UPDATE employee SET resume = ? WHERE id = ?"
);
File file = new File("resume.pdf");
FileInputStream fis = new FileInputStream(file);
ps.setBinaryStream(1, fis, (int) file.length());
ps.setInt(2, 101);
ps.executeUpdate();
fis.close();
```

