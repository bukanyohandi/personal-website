class Node:
    def __init__(self, element, pointer):
        self.element = element
        self.pointer = pointer

class SinglyLinkedList:
    def __init__(self):
        self.head = None
    def empty(self):
        return self.head == None
    def insert(self, data):
        if not self.empty():
            self.tail.pointer = Node(data,None)
            self.tail = self.tail.pointer
        else:
            self.head = Node(data, None)
            self.tail = self.head
        print('"' + data + '" is inserted.')
    def ith(self, i):
        tmp = self.head
        if self.recursive_count(tmp) < i:
            return None
        for j in range(i):
            tmp = tmp.pointer
        return tmp
    def printed(self):
        tmp = self.head
        printedList = ""
        for i in range(self.recursive_count(self.head)):
            printedList += '"' + tmp.element + '" '
            tmp = tmp.pointer
        return printedList
    def quickSort(self, Node, left, right):
        ql, qr = left - 1, right - 1
        if ql < qr :
            key = self.ith(ql).element
            while True:
                if ql >= qr:
                    break 
                while self.ith(qr).element >= key:
                    if ql >= qr:
                        break
                    qr -= 1
                self.ith(ql).element = self.ith(qr).element
                while self.ith(ql).element <= key:
                    if ql >= qr:
                        break
                    ql += 1
                self.ith(qr).element = self.ith(ql).element
            self.ith(ql).element = key
            self.quickSort(Node, left, ql)
            self.quickSort(Node, qr + 2, right)
        return Node
    def recursive_count(self, Node):
        if Node == None:
            return 0
        return 1 + self.recursive_count(Node.pointer)
    def sort(self, Node):
        tmp = self.quickSort(Node, 1, self.recursive_count(Node))
        self.head = tmp

sll = SinglyLinkedList()
sll.insert("This")
sll.insert("Singly Linked List")
sll.insert("Is Made")
sll.insert("By: Yohandi")
sll.sort(sll.head)
print("Sorted result:", sll.printed())