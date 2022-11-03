template <class Type>
class myStack
{
public:
	myStack();
	myStack(const myStack<Type>&);
	const myStack<Type>& operator=(const myStack<Type>&);
	~myStack();

	void push(const Type&);
	void pop();
	Type top() const;
	bool isEmpty() const;

private:
	struct node
	{
		Type item;
		node *next;
	};

	node *topOfmyStack;
};


/*function_identifier: intialize variables
*paarmeters: none
*return value:none */
template <class Type>
myStack<Type>::myStack()
{
    topOfmyStack = NULL;
}

/*function_identifier: deep copy of the copy object to *this object
*paarmeters:
*return value:none */
template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy)
{
    topOfmyStack = NULL;
    *this = copy;
}

/*function_identifier: deep copy of rhs to *this object
*paarmeters: none
*return value:none */
template<class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs)
{
    this->~myStack();
    
    node *top = rhs.topOfmyStack;
    node *ourItem;
    
    node **nextPtr = &topOfmyStack;

    while ( top != NULL){
        ourItem = new node;
        
        *nextPtr = ourItem;
        ourItem->item = top->item;
        nextPtr = &ourItem->next;

        top = top->next;
    }
    
    *nextPtr = NULL;

    return *this;
}

/*function_identifier: dellocates the stack object
*paarmeters: none 
*return value:none */
template<class Type>
myStack<Type>::~myStack()
{
    while ( topOfmyStack != NULL){
        
        node *link = topOfmyStack->next;
        delete topOfmyStack;
        topOfmyStack = link;
        
    }
}

/*function_identifier: pushes a new node to the top of the stack
*paarmeters: insert
*return value:none */
template <class Type>
void myStack<Type>::push(const Type& insert)
{
    node *tmp = new node;
    tmp->item = insert;
    tmp->next = topOfmyStack;
    topOfmyStack = tmp;
}

/*function_identifier: remove stack top
*paarmeters: none
*return value:none */
template <class Type>
void myStack<Type>::pop()
{
    if (isEmpty())
        return; 

    node *tmp = topOfmyStack;
    topOfmyStack = topOfmyStack->next;
    delete tmp;
   
}

/*function_identifier: return the item of top node
*paarmeters: none
*return value: item of the top node */
template <class Type>
Type myStack<Type>::top() const
{
    return topOfmyStack->item;
}

/*function_identifier: check if stack is empty
*paarmeters: none
*return value: true, false */
template <class Type>
bool myStack<Type>::isEmpty() const
{
	return topOfmyStack == NULL;
}
