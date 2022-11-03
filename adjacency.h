#include <iostream>


using namespace std;


template <class Type >
class vertex
{
	struct node
	{
		Type item ;
		node * link ;
	};
public :
	class edgeIterator
	{
	public :
		friend class vertex ;
		edgeIterator ();
		edgeIterator ( node *);
		edgeIterator operator ++();
		Type operator *();
		bool operator ==( const edgeIterator& );
		bool operator !=( const edgeIterator &);

	private :
		node * current ;
	};
	vertex ();
	vertex ( const vertex < Type >&);
	const vertex & operator =( const vertex < Type >&);
	~ vertex ();
	edgeIterator begin ();
	edgeIterator end ();
	void addEdge ( const Type &);

private :
	node * neighbors ;
};




/*function_identifier: intialize variables 
*parameters: none
*return value: none*/
template<class Type>
vertex<Type>::edgeIterator::edgeIterator(){

    current = NULL;
}

/*function_identifier: set current to edge
nparameters: none 
*return value: none*/
template< class Type>
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node * edge){

    current = edge;
}

/*function_identifier: set current to current->next
*parameters: none
*return value: *this */
template< class Type>
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(){

	current = current->link;
	return *this;
}

/*function_identifier: 
*parameters: 
*return value: */
template< class Type>
Type vertex<Type>::edgeIterator::operator*(){

	return current->item;
}

/*function_identifier: return true if *htis iterator points tp same node as rhs object,
* otherwise trturn false
*parameters: rhs
*return value: true, false */
template< class Type>
bool vertex<Type>::edgeIterator::operator ==( const vertex<Type>::edgeIterator& rhs ){


	return current == rhs.current;
}


/*function_identifier: return false if *htis iterator points tp same node as rhs object,
* otherwise return true
*parameters: rhs
*return value: true, false */
template< class Type>
bool vertex<Type>::edgeIterator::operator !=( const vertex<Type>::edgeIterator& rhs ){


	return current != rhs.current;
}

/*function_identifier: initalize  variables
*parameters: none
*return value: none*/
template< class Type>
vertex<Type>::vertex() {

	neighbors = NULL;
}

/*function_identifier: perform a deep copy 
*parameters: copy
*return value: none */
template< class Type>
vertex<Type>::vertex(const vertex<Type>& copy) {
	
	for ( node * n = copy.neighbors; n !=NULL; n= n->link){
        
        node * newN = new node;
        newN->item = n->item;
	} 

}


/*function_identifier: deep copy
*parameters: rhs
*return value: none*/
template< class Type>
const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& rhs) {

    this->~vertex();
    node ** ptr = &neighbors;
	for ( node * n = rhs.neighbors; n !=NULL; n= n->link){
        
        node * newN = new node;
        newN->item = n->item;
        *ptr = newN;
        ptr = &newN->link;
	}
    *ptr = NULL;
    return *this;
}

/*function_identifier: deallocates all nodes in neighbor list 
*parameters: none
*return value: none*/
template< class Type>
vertex<Type>::~vertex(){
	
	// neighbors is the head of the list
	while ( neighbors != nullptr){
		
		node * next = neighbors->link;
		delete neighbors;
		neighbors = next;
	}

}

/*function_identifier: return head of linked list
*parameters: none
*return value: none */
template< class Type>
typename vertex<Type>::edgeIterator vertex<Type>::begin() {

	return edgeIterator(neighbors);
}

/*function_identifier: return tail of linked list
*parameters: none 
*return value:none */
template< class Type>
typename vertex<Type>::edgeIterator vertex<Type>::end() {

	return edgeIterator(NULL);
}

/*function_identifier: add a head to the linked list
*parameters: edge
*return value: none */
template< class Type>
void vertex<Type>::addEdge(const Type& edge){

    node * headInsert = new node;
    headInsert->item = edge;
    
    headInsert->link = neighbors;
    neighbors = headInsert;

}
