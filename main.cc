#include <iostream>

//实现一个不包含重复数值域单链表
//插入的时候按序插入

template<class T>
struct ListNode{
  ListNode<T>* _next;
  T _elem;
  ListNode(const T& x):_elem(x), _next(NULL) {}
};

template<class T>
class List{
  typedef ListNode<T> Node;
public:
  List():_head(NULL){} //缺省构造函数
  ~List(){
    Clear();
  }

  void Clear();
  void Print();
  void Insert(const T& elem);
private:
  Node _head;
};

template<class T>
void List<T>::Clear(){
  Node* cur = _head;
  while(NULL != cur){
    Node* next = cur->_next;
    delete cur;
    cur = next;
  }
  _head = NULL;
}

template<class T>
void List<T>::Print(){
  Node* cur = _head;
  while(NULL != cur){
    std::cout<< cur->_elem <<" ";
    cur = cur->_next;
  }
  std::cout<<std::endl;
}

template<class T>
void List<T>::Insert(const T& elem){
  if(NULL == _head){
    _head = new Node;
    _head->_elem = elem;
    _head->_next = NULL;
  }else{
    Node* cur = _head;
    Node* pre = NULL;
    while(cur != NULL && cur->_elem <= elem){ //重载 <=, 以支持数据域比较
      pre = cur;
      cur = cur->_next; 
    }
    //出了循环有两种可能：
    //1.找遍了链表也没有找到大于 elem 的数据(即cur == NULL)
    //此时将新节点插入到 pre 的后面即可
    if(NULL == cur){
      pre->_next = new Node;
      pre->_next->_elem = elem;
      pre->_next->_next = NULL;
    }else{
    //2.找到了大于 elem 的节点
    //此时 cur 的前一个节点的位置即插入新节点的位置
      Node* new_node = new Node;
      new_node->_elem = elem;
      new_node->_next = cur;
      pre->_next = new_node;
    }//end else_2
  }//end else_1
}//end Insert()


class Set{
public:
  Set(){}

private:
  List<int> _elem;
};





int main() {
  
  return 0;
}
