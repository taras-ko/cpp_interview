// Linked List from the "C++ interview" pg. 31
#include <assert.h>
#include <iostream>

class LinkedListIterator;
class LinkedList;

class Node
{
    friend class LinkedListIterator;
    friend class LinkedList;
    Node* m_next;
    int m_elem;
};

class LinkedListIterator
{
public:
    bool operator==(LinkedListIterator i) const;
    bool operator!=(LinkedListIterator i) const;
    void operator++(); // goto next element
    int operator*(); // access elem

private:
    LinkedListIterator(Node* node);
    Node *m_node;
    friend class LinkedList; // so LinkedList can construct a LinkedListIterator
};

class LinkedList
{
public:
    LinkedList(int elem);
    ~LinkedList();

    void append(int elem);
    void prepend(int elem);

    LinkedListIterator begin();
    LinkedListIterator end();

private:
    Node* m_first;
    Node* m_last;
};

inline LinkedList::LinkedList(int elem)
{
    m_first = new Node();
    m_first->m_elem = elem;
    m_first->m_next = nullptr;
    m_last = m_first;
}

inline LinkedList::~LinkedList()
{
    Node* node = m_first;

    do {
        Node* prev_node = node;
        node = node->m_next;

        std::cout << "cleaning node with: " << prev_node->m_elem << std::endl;
        delete prev_node;

    } while (node != nullptr);
}

inline void LinkedList::append(int elem)
{
    auto new_node = new Node();
    new_node->m_elem = elem;

    new_node->m_next = nullptr;

    m_last->m_next = new_node;

    m_last = new_node;
}

inline bool LinkedListIterator::operator==(LinkedListIterator it) const
{
    return m_node == it.m_node;
}

inline bool LinkedListIterator::operator!=(LinkedListIterator it) const
{
    return m_node != it.m_node;
}

inline void LinkedListIterator::operator++()
{
    assert(m_node != nullptr);
    m_node = m_node->m_next;
}

inline int LinkedListIterator::operator*()
{
    assert(m_node != nullptr);
    return m_node->m_elem;
}

inline LinkedListIterator::LinkedListIterator(Node* node)
    : m_node {node}
{}

inline LinkedListIterator LinkedList::begin()
{
    return m_first;
}

inline LinkedListIterator LinkedList::end()
{
    return nullptr;
}

int main()
{
    LinkedList list(-1);

    for (int i=0; i<10; i++)
        list.append(i);

    for (auto it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << std::endl;
}
