#include <list>

template <typename T>
class node
{
   public:
      T nodeValue;      // data held by the node
      node<T> *next;    // next node in the list

      // default constructor with no initial value
      node() : next(NULL)
      {}

      // constructor. initialize nodeValue and next
      node(const T& item, node<T> *nextNode = NULL)
	 :nodeValue(item), next(nextNode)
      {}
};

// Class that stores a linked list.
template <typename T>
class linkedList
{
   public:
      linkedList();     // Creates an empty list
      int numNodes();   // Returns the number of nodes
      linkedList(const linkedList<T> &origList);
   private:
      node<T> *first;
};

// Copy constructor for the linkedList class
template <typename T>
linkedList<T>::linkedList(const linkedList<T> &origList)
{
   node<T> *origListPtr = origList.front;
   node<T> *newListPtr, *prev;

   // Handle the case where the original list is empty
   if (origList.first == NULL)
      first == NULL;
   else
   {
      // Copy the first node in the list
      first = new node<T>(origListPtr->NodeValue, NULL);
      prev = first;
      origListPtr = origListPtr->next;
   }

   // Copy the remaining nodes in the list   
   while(origListPtr != NULL)
   {
      prev->next = new node<T>(origListPtr->NodeValue, NULL);
      prev = prev->next;
      origListPtr = origListPtr->next;
   }
}
