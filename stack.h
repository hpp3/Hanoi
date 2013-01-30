struct NODE {
    int value;
    NODE *next;    
};

class Stack {
    private:
        NODE *head;
        int length;
        
    public:
        Stack();
        Stack(int num);
        ~Stack();
        int get_length();
        int* array();
        void push(int num);
        void pop();
        int top();
};


