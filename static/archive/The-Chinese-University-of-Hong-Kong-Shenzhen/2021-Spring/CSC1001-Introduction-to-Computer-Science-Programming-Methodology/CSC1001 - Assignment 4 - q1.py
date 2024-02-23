class Node:
    def __init__ (self, element, pointer):
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
    def recursive_count(self, Node):
        if Node == None:
            return 0
        return 1 + self.recursive_count(Node.pointer)
        
sll = SinglyLinkedList()
sll.insert("This")
sll.insert("Singly Linked List")
sll.insert("Is Made")
sll.insert("By: Yohandi")
print("The function recursive_count() returns:", sll.recursive_count(sll.head))