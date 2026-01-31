package LinkedList;

public class SLL {

    static SLL head = null;

    int value;
    SLL next;

    public SLL(int value) {
        this.value = value;
        this.next = null;
    }

    public SLL(int value, SLL next) {
        this.value = value;
        this.next = next;
    }

    public static void add(int value) {
        SLL newNode = new SLL(value);
        if (head == null) {
            head = newNode;
        } else {
            SLL current = head;
            while (current.next != null)
                current = current.next;
            current.next = newNode;
        }
    }

    public static void printList() {
        SLL current = head;
        while (current != null) {
            System.out.println(current.value);
            current = current.next;
        }
    }

    public static void deletefirst(int value) {
        if (head == null) {
            System.err.println("List is empty");
            return;
        } else if (head.value == value) {
            head = head.next;
            return;
        }

        else {
            for (SLL current = head; current != null; current = current.next) {

                if (current.next == null)
                    break;

                if (current.next.value == value) {
                    current.next = current.next.next;
                    return;
                }

            }
            System.err.println("Value not found in the list");
        }
    }

    public static void insertAt(int index, int value) {
        SLL newNode = new SLL(value);
        if (index == 0) {
            newNode.next = head;
            head = newNode;
            return;
        }
        SLL current = head;

        for (int i = 0; i < index - 1; i++) {
            if (current == null) {
                System.err.println("Index out of bounds");
                return;
            }
            current = current.next;
        }

        if (current != null) {
            newNode.next = current.next;
            current.next = newNode;
        }
    }
}
