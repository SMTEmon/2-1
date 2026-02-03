package LinkedList;

public class DLL {

    static DLL head = null;

    int value;
    DLL next;
    DLL prev;

    public DLL(int value) {
        this.value = value;
        this.next = null;
        this.prev = null;
    }

    public DLL(int value, DLL next, DLL prev) {
        this.value = value;
        this.next = next;
        this.prev = prev;
    }

    public static void add(int value) {
        DLL newNode = new DLL(value);
        if (head == null) {
            head = newNode;
            return;
        }

        DLL current = head;

        while (current.next != null) {
            current = current.next;
        }

        current.next = newNode;
        newNode.prev = current;

    }

    public static void printList() {
        for (DLL current = head; current != null; current = current.next) {
            System.out.println(current.value);
        }
    }

    public static void deleteFirst(int value) {

        if (head == null) {
            System.err.println("List is empty.");
            return;
        }

        DLL current = head;

        if (head.value == value) {
            if (head.next != null)
                head.next.prev = null;
            head = head.next;
            return;
        }

        while (current != null) {
            if (current.value == value) {

                if (current.next != null) {
                    current.prev.next = current.next;
                    current.next.prev = current.prev;
                } else {
                    current.prev.next = null;
                }

                return;
            }
            current = current.next;
        }
        System.err.println("Node does not exist");
    }

    public static void insertAt(int index, int value) {
        if (head == null) {
            System.err.println("Linklist was empty. Added the value.");
            add(value);
            return;
        }

        DLL newNode = new DLL(value);
        DLL current = head;

        if (index == 0) {
            newNode.next = head;
            head.prev = newNode;
            head = newNode;
            return;
        }

        for (int i = 0; i < index - 1; i++) {
            current = current.next;
            if (current == null) {
                System.err.println("Index out of bounds. Adding the value to the end.");
                add(value);
                return;
            }
        }

        if (current.next != null)
            current.next.prev = newNode;

        newNode.next = current.next;
        current.next = newNode;

        newNode.prev = current;

    }
}
