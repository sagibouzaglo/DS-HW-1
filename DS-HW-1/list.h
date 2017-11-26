#ifndef EX4_LIST_H
#define EX4_LIST_H

#include <stdlib.h>
#include <array>
#include "Exceptions.h"
template <class T>
class List{
    /**------------------Private-----------*/
    template<class N>
    class Node{
        Node<N>* previous;
        N data;
        Node<N>* next;
        friend class Iterator;
        friend class List;
    public:
        /** Empty Constructor for node
        * @return
        * A new Unlinked node
        */
        Node<N>():previous(nullptr),data(),next(nullptr){}
        /** Data Constructor for node
        * @param data to be put in list
        * @return
        * A new Unlinked node with Data assigned
        */
        Node<N>(const N& data):previous(nullptr),data(data),next(nullptr){}
        /** Destructor for node**/
        ~Node<N>()= default;
        /** Copy Constructor for node
        * @param node to be copied
        * @return an copied object, this.
        */
        Node<N>(const Node<N>& node):previous(node.previous),
                                     data(node.data),next(node.next){}
        /** assignment for Node
        * @param the node to be assigned
        * @return
        * A new Unlinked node
        */
        Node<N>& operator=(const Node<N>& node){
            if(this == &node) {
                return *this;
            }
            this->data=node.data;
            this->next=node.next;
            this->previous=node.previous;
            return *this;
        }
    };
    /**---------------End of namespace Node--------------------*/
/**---------------Private List Parts--------------------*/
    Node<T>* start;
    Node<T>* finish;
    int size;
public:
    /**---------------Public List Parts--------------------*/
    /**---------------internal iterator class--------------------*/
    class Iterator {
        Node<T>* current;
        const List<T> *list;
        /** Empty Constructor for Iterator as private
        * @param
        * @return
        */
        Iterator(const List<T>& list1):current(list1.start),list(&list1){}
    public:
        friend class List<T>;
        //Iterator destructor
        ~Iterator()= default;
        //Iterator copy constructor
        Iterator(const Iterator& iterator)= default;
        //Iterator assignment operator
        Iterator& operator=(const Iterator& iterator)= default;
        /** Operator*() for iterator
        * @param iterator object
        */
        T& operator*() const{
            if(this->current==nullptr) {
                throw mtm::ListExceptions::ElementNotFound();
            }
            return this->current->data;
        }
        /** ++iterator
       * @param iterator object
       */
        Iterator& operator++(){
            if(this->current==nullptr){
                return *this;
            }
            this->current=this->current->next;
            return *this;
        }
        /** iterator++
       * @param iterator object
       */
        Iterator operator++(int){
            Iterator temp_itearator=(*this);
            ++(*this);
            return temp_itearator;
        }
        /** --iterator
        * @param iterator object
        */
        Iterator operator--(){
            //if --for list.end
            if(*this==(this->list->end())){
                this->current=this->list->finish;
                return *this;
            }
            //if --for list.begin- undefiend
            if(this->current==nullptr || this->current->previous==nullptr){
                return *this;
            }
            this->current=this->current->previous;
            return *this;
        }
        /** iterator--  for iterator
        * @param iterator object
        */
        Iterator operator--(int){
            if(*this==this->list->begin()){
                return *this;
            }
            Iterator temp_itearator=(*this);
            --(*this);
            return temp_itearator;
        }
        /** Operator==  for iterator
      * @param iterator to be checked to
      */
        bool operator==(const Iterator& iterator) const{
            return ((this->list==iterator.list) &&
                    this->current==iterator.current);
        }
        /** Operator!=  for iterator
      * @param iterator to be checked to
      */
        bool operator!=(const Iterator& iterator) const{
            return !(*this==iterator);
        }

    };
    /**---------------End of internal  Iterator--------------------*/
/**---------------Implementation of list functions--------------------*/
    /** Empty Constructor for list
    * @return a new empty list */
    List<T>():start(nullptr),finish(nullptr),size(0){}
    /** Copy Constructor for list
    * @param The list to be copied
    * @return The object as a copy of the parameter list
    */
    List<T>(const List& list):start(nullptr),finish(nullptr),size(0){
        for(Iterator it=list.begin();it!=list.end();++it){
            this->insert(it.current->data);
        }
    }
    /** Destructor  for list */
    ~List<T>(){
        while(this->size>0){
            remove(this->begin());
        }
    }
    /** List Operator=
    * @param The list to be copied
    * @return The object as a copy of the parameter list
    */
    List& operator=(const List& list){
        if(this == &list) {
            return *this;
        }
        while(this->size>0){
            remove(this->begin());
        }
        for(Iterator it=list.begin();it!=list.end();++it){
            this->insert(it.current->data);
        }
        return *this;
    }
    /** List Operator==
    * @param The list to be matched
    * @return true if same; flase if not;
    */
    bool operator==(const List& list) const{
        Iterator it1=this->begin();
        Iterator it2=list.begin();
        while(it1!=this->end() && it2!=list.end()){
            if(it1.current->data!=it2.current->data){
                return false;
            }
            it1++;
            it2++;
        }
        if( (it1==this->end()) && (it2==list.end()) ){
            return true;
        }
        return false;
    }
    /** List Operator!=
    * @param The list to be matched
    * @return true if same; flase if not;
    */
    bool operator!=(const List& list){
        return !((*(this))==list);
    }
    /** list.begin() Function
    * @return iterator to start of list
    */
    Iterator begin() const{
        Iterator iterator(*this);
        iterator.current=this->start;
        return iterator;
    }
    /** list.end() Function
    * @return iterator to end of the this list..is not a real data
    */
    Iterator end() const{
        Iterator iterator(*this);
        iterator.current=nullptr;
        return iterator;
    }
    /** List insert to end
    * @param The data to be inserted
    */
    void insert(const T& data,Iterator iterator){
        if(iterator.list!=this){ //not an iterator for this list
            throw mtm::ListExceptions::ElementNotFound();
        }
        T new_data=data;
        Node<T>* new_node= new Node<T>(new_data);
        if(this->getSize()==0){//an empty list
            this->start=new_node;
            this->finish=new_node;
            this->size++;
            return;
        }
        if(iterator==this->end()){
            this->finish->next=new_node;
            new_node->previous=this->finish;
            this->finish=new_node;
            this->size++;
            return;
        }
        if(iterator==this->begin()){
            this->begin().current->previous=new_node;
            new_node->next=this->begin().current;
            this->start=new_node;
            this->size++;
            return;
        }
        //iterator for middle of the list
        new_node->next=iterator.current;
        new_node->previous=iterator.current->previous;
        iterator.current->previous->next=new_node;
        iterator.current->previous=new_node;
        this->size++;
        return;
    }
    /** List insert to end
    * @param The data to be inserted
    */
    void insert(const T& data){
        insert(data,this->end());
    }
    /** remove current data from list
    * @param iterator of list
    * @throws mtm::ListExceptions::ElementNotFound() if something went wrong
    */
    void remove(Iterator iterator){
        if(iterator.list !=this || this->size<=0 || iterator==this->end()){
            throw mtm::ListExceptions::ElementNotFound();
        }
        if(iterator==this->begin()){//start of list
            if(this->size==1){//only node
                this->start= nullptr;
                this->finish= nullptr;
                delete iterator.current;
                (this->size)--;
                return;
            }
            else{// more then 1 element
                this->start=iterator.current->next;
                iterator.current->next->previous=nullptr;
                delete iterator.current;
                (this->size)--;
                return;
            }
        }
        iterator.current->previous->next=iterator.current->next;
        if(iterator.current->next==nullptr){
            this->finish=iterator.current->previous;
        } else{
            iterator.current->next->previous=iterator.current->previous;
        }
        delete iterator.current;
        this->size--;
    }
    int getSize(){
        return this->size;
    }
    /** remove current data from list
    * @param iterator of list
    * @throws mtm::ListExceptions::ElementNotFound() if something went wrong
    */
    template <typename Predicate>
    Iterator find(const Predicate& predicate){
        for(Iterator it=this->begin();it!=this->end();++it){
            if(predicate(it.current->data)){
                return it;
            }
        }
        return this->end();
    }
    template <class Compare>
    void sort(const Compare& compare){
        List<T> new_list;
         int list_size=this->size;
        for (int i=1;i<list_size;i++){
            Iterator min_it(*this);
            for(Iterator it=(++(this->begin()));it!=this->end();++it){
                if(compare(it.current->data,min_it.current->data)){
                    min_it=it;
                }
            }
            new_list.insert(min_it.current->data);
            this->remove(min_it);
        }
        new_list.insert(this->begin().current->data);
        this->remove(this->begin());
        (*this)=new_list;
    }
    /** remove current data from list
    * @param iterator of list
    * @throws mtm::ListExceptions::ElementNotFound() if something went wrong
    */

};

/**------------------------Node Implemantion------------------------------*/

/**------------------------Node Decleration-----------------------------------*/

/**------------------------Node Implemantion----------------------------------*/
#endif //EX4_LIST_H
