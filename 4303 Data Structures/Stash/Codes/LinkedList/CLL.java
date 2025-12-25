public class CLL {

    static CLL head = null;

    int value;
    CLL next;

    public CLL(int value) {
        this.value = value;
        this.next = null;
    }

    public CLL(int value, CLL next) {
        this.value = value;
        this.next = next;
    }
}
