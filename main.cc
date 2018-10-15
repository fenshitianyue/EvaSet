#include <iostream>
//采用泛型编程的方式实现了一个支持交集，并集，差集，添加，删除方法的 set
//规定这个集合不能包含相同元素

//实现一个不包含重复数值域单链表
//插入的时候按序插入

//链表的节点
template<class T>
struct ListNode{
  ListNode<T>* _next;
  T _elem;
  ListNode():_elem(0) {} //缺省构造函数
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
  //下面这两个函数的实现有些 low，后面有时间我重新实现一下
  List(const List<T>& l){
    Node* tmp = l._head; 
    if(tmp != NULL){
      _head = new Node;
      _head->_elem = tmp->_elem;
      _head->_next = NULL;
      tmp = tmp->_next;
      Node* head = _head; //定义一个指针指向链表的头
      while(tmp != NULL){
        _head->_next = new Node;
        _head->_next->_elem = tmp->_elem;
        _head->_next->_next = NULL;
        _head = _head->_next;
        tmp = tmp->_next;
      }
      _head = head; //此时_head已经走到了链表的倒数倒数第一个节点，需要将头指针重新指向链表的头
    }//end if
  }//end List(const List<t>& l)
  List<T>& operator=(const List<T>& l){
    if(&l == this){
      return *this;
    }
    this->Clear(); //销毁掉原来的空间
    Node* tmp = l._head;
    if(NULL == tmp){ //如果赋值的链表为空，则直接返回被赋值的链表
      return *this;
    }
    _head = new Node;
    _head->_elem = tmp->_elem;
    _head->_next = NULL;
    tmp = tmp->_next;
    Node* head = _head;
    while(tmp != NULL){
      _head->_next = new Node;
      _head->_next->_elem = tmp->_elem;
      _head->_next->_next = NULL;
      _head = _head->_next;
      tmp = tmp->_next;
    }
    _head = head;
    return *this; 
  }
  void Clear();
  void Print();
  void Insert(const T& elem);
  void Del(const T& elem);
  //set要使用的接口
  List<T> ListAnd(const List<T>& l);
  List<T> ListDifference(const List<T>& l);
  List<T> ListUnion(const List<T>& l);
private:
  Node* _head;
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
void List<T>::Del(const T& elem){
  Node* tmp = _head;
  Node* pre = NULL;
  while(tmp != NULL && tmp->_elem != elem){
    pre = tmp;
    tmp = tmp->_next;
  }
  if(tmp != NULL && tmp == _head){
    pre = _head;
    _head = _head->_next;
    delete pre;
  }else if(tmp != NULL){
    pre->_next = tmp->_next; 
    delete tmp;
  }
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
    }//2.找到了大于 elem 的节点
    else if(cur == _head){ //如果cur是头节点,则头插
      Node* new_node = new Node;
      new_node->_elem = elem;
      new_node->_next = cur;
      _head = new_node;
    }
    else{
      Node* new_node = new Node;
      new_node->_elem = elem;
      new_node->_next = cur;
      pre->_next = new_node;
    }//end else_2
  }//end else_1
}//end Insert()

template<class T>
List<T> List<T>::ListAnd(const List<T>& l){ 
  //拿着第一个链表中的节点遍历第二个链表
  Node* p1 = _head;
  Node* p2 = l._head;
  List<T> new_list;
  while(p1 != NULL){
    while(p2 != NULL && p1->_elem != p2->_elem){
      p2 = p2->_next; 
    }
    if(p2 != NULL){// 如果p2不为空，说明找到了，则将这个这个数据插入到新链表中
      new_list.Insert(p1->_elem);
    }
    //否则说明没找到
    p2 = l._head; //将p2重新指向第二个链表的头部
    p1 = p1->_next;
  }
  return new_list;
}

template<class T>
List<T> List<T>::ListDifference(const List<T>& l){
  Node* p1 = _head;
  Node* p2 = l._head;
  List<T> new_list;
  //将链表1中包含而链表2中不包含的数据插入到新链表中
  while(p1 != NULL){
    while(p2 != NULL && p1->_elem != p2->_elem){
      p2 = p2->_next; 
    }
    if(NULL == p2){ //如果链表2为空，说明此数据链表2中没有
      new_list.Insert(p1->_elem);
    }
    p2 = l._head; //将p2重新指向第二个链表的头部
    p1 = p1->_next;
  }
  return new_list; 
}
template<class T>
List<T> List<T>::ListUnion(const List<T>& l){
  Node* p1 = _head;
  Node* p2 = l._head;
  List<T> new_list;
  //先将链表1中的数据都插入到新链表中
  while(p1 != NULL){
    new_list.Insert(p1->_elem);
    p1 = p1->_next;
  }
  Node* p3 = new_list._head;
  while(p2 != NULL){
    while(p3 != NULL && p2->_elem != p3->_elem){
      p3 = p3->_next;
    }
    if(NULL == p3){//说明链表2中的元素新链表中没有，将链表2的当前节点中的数据插入到新链表中
      new_list.Insert(p2->_elem);
    }
    p3 = new_list._head;
    p2 = p2->_next;
  }
  return new_list; 
}

template<class T>
class Set{
public:
  Set(){}
  List<T> Get(){
    return _elem;
  }
  void Add(const T& elem){
    _elem.Insert(elem);
  }
  void Del(const T& elem){
    _elem.Del(elem);
  }
  void Print(){
    _elem.Print();
  }
  Set<T> And(const Set<T>& s){
    Set<T> result;
    result._elem = _elem.ListAnd(s._elem);
    return result;
  } 
  Set<T> Union(const Set<T>& s){
    Set<T> result;
    result._elem = _elem.ListUnion(s._elem);
    return result;
  }
  Set<T> Difference(const Set<T>& s){
    Set<T> result;
    result._elem = _elem.ListDifference(s._elem); 
    //result.Print();
    return result; //此时 result 的数据 _elem 是空的
  }

private:
  List<T> _elem;
};


//测试用例
int main() {
  Set<int> s1;
  s1.Add(1);
  s1.Add(3);
  s1.Add(5);
  s1.Add(7);
  std::cout << "--集合1--" << std::endl;
  s1.Print();
  Set<int> s2; 
  s2.Add(2);
  s2.Add(4);
  s2.Add(6);
  s2.Add(8);
  std::cout << "--集合2--" << std::endl;
  s2.Print();
  Set<int> result; 
  std::cout << "--集合的交集--" << std::endl;
  result = s1.And(s2);
  result.Print();
  std::cout << "--集合的差集--" << std::endl;
  result = s1.Difference(s2);
  result.Print();
  std::cout << "--集合的并集--" << std::endl;
  result = s1.Union(s2);
  result.Print();
  return 0;
}
