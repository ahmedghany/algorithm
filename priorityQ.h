#include <iostream>

using  namespace std;

template <class Type>
class priorityQ
{

public :
	priorityQ (int = 10);
	priorityQ ( const priorityQ < Type >&);
	~ priorityQ ();
	const priorityQ < Type >& operator =( priorityQ < Type >);
	void insert ( const Type &);
	void deleteHighestPriority ();
	Type getHighestPriority () const ;
	bool isEmpty () const ;
	void bubbleUp (int );
	void bubbleDown (int );
	int getSize () const ;

private :
	int capacity ;
	int items ;
	Type * heapArray ;
};



/*function_identifier: intialize values
*paarmeters: capacity
*return value: none */
template <class Type>
priorityQ<Type>::priorityQ( int capacity){
    
    this->capacity = capacity;
    items = 0;
    
    heapArray = new Type[capacity+1];
}

/*function_identifier: deep copy
*paarmeters: copy
*return value: none */
template <class Type>
priorityQ<Type>::priorityQ (const priorityQ<Type>& copy){

    ~priorityQ();
    *this = copy;
}


/*function_identifier: destructor
*paarmeters: none
*return value: none */
template <class Type>
priorityQ<Type>::~priorityQ (){
        
    for (int i=0; i < items; i++)
            
        deleteHighestPriority();
    
    delete[] heapArray;
}

/*function_identifier: assignment operaor
*paarmeters: rhs
*return value: *this */
template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(priorityQ<Type> rhs){

    std::swap(*this, rhs);
    return *this;
}

/*function_identifier: insert an element to the heap array and buuble up
*paarmeters: element
*return value: none */
template <class Type>
void priorityQ<Type>::insert(const Type& element){
    
    if (items == capacity){
        
        capacity *= 2;
        Type * newArray = new  Type[capacity+1];
        
        for (int i=1; i <= items ; i++)
            newArray[i] = heapArray[i];
        
        delete[] heapArray;
        heapArray = newArray;
    }

    items++;
    heapArray[items] = element;
    bubbleUp(items);
}

/*function_identifier: delete an element and bubble down
*paarmeters: none
*return value: none */
template <class Type>
void priorityQ<Type>::deleteHighestPriority(){
    
    if (isEmpty())
        return;
    
    heapArray[1] = heapArray[items];
    items--;
    bubbleDown(1);
}

/*function_identifier: return the highest priority item
*paarmeters: none
*return value: highest element in heap Array */
template <class Type>
Type priorityQ<Type>::getHighestPriority() const{

    return heapArray[1];
}

/*function_identifier:
*paarmeters: 
*return value: */
template <class Type>
bool priorityQ<Type>::isEmpty () const{

    return items == 0;
}

/*function_identifier: bubble up an element of heap array
*parameters: index
*return value: none */
template <class Type>
void priorityQ<Type>::bubbleUp (int index){
    
    if ( index == 1)
        return;
    
    int parent = index/2;

    if ( heapArray[index] > heapArray[parent]){
        
        Type tmp = heapArray[parent];
        heapArray[parent] = heapArray[index];
        heapArray[index] = tmp;
        bubbleUp(parent);

    }

}

/*function_identifier: buuble down an element of heap array
*parameters: index
*return value: none */
template <class Type>
void priorityQ<Type>::bubbleDown (int index){

    if ( (2 * index) > items)
        return;
    
    int leftChild = 2 * index, rightChild = 2 * index + 1;
    int maxIndex = index;

    if ( heapArray[leftChild] > heapArray[index])
        maxIndex = leftChild;

    if ( rightChild <= items &&  heapArray[rightChild] > heapArray[maxIndex])
        maxIndex = rightChild;

    if ( maxIndex != index){

        Type tmp = heapArray[index];
        heapArray[index] = heapArray[maxIndex];
        heapArray[maxIndex] = tmp;
        bubbleDown(maxIndex);
    }

}

/*function_identifier: get the amount of elements
*paarmeters: none
*return value: items*/
template <class Type>
int priorityQ<Type>::getSize() const{
    return items;
}
