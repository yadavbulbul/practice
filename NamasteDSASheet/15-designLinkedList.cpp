class Node {
public:
    int val;
    Node* next;

    Node(int val) {
        this->val = val;
        this->next = nullptr;
    }
};

class MyLinkedList {
public:
    Node* head;
    MyLinkedList() {
        head=nullptr;
    }
    
    int get(int index) {
        int i=0;
        Node* temp = head;
        while(i<index && temp!=nullptr){
            temp=temp->next;
            i++;
        }
        if(temp==nullptr){
            return -1;
        }
        return temp->val;
    }
    
    void addAtHead(int val) {
        Node* toBeAdded = new Node(val);
        toBeAdded->next=head;
        head=toBeAdded;
    }
    
    void addAtTail(int val) {
        Node* toBeAdded = new Node(val);

        // what if head == nullptr?
        if(head==nullptr){
            head=toBeAdded;
            return;
        }

        Node* temp = head;

        // traverse until last node
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        temp->next=toBeAdded;

        // connect last node to toBeAdded
    }
    
    void addAtIndex(int index, int val) {
        if (index == 0) {
            addAtHead(val);
            return;
        }
        Node* toBeAdded = new Node(val);
        Node* temp = head;
        int i = 0;
        while(i<index-1 && temp!=nullptr){
            temp=temp->next;
            i++;
        }
        if (temp == nullptr) {
            return;
        }

        toBeAdded->next=temp->next;
        temp->next=toBeAdded;
    }


    void deleteAtIndex(int index) {

    Node* temp = head;

    // invalid index / empty list
    if (head == nullptr) {
        return;
    }

    // deleting head
    if (index == 0) {
        head = head->next;
        return;
    }

    int i = 1;

    // move temp to node before the target
    while (i < index && temp->next != nullptr) {
        temp = temp->next;
        i++;
    }

    // index is invalid
    if (i != index || temp->next == nullptr) {
        return;
    }

    // delete target
    temp->next = temp->next->next;
}
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */