#include <iostream>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <string>
#include "Test.h"
#include <vector>
#include <iomanip>

using namespace std;


class SinglyLinkedListNode
{
public:
	int data;
	SinglyLinkedListNode* next;
    SinglyLinkedListNode(int _data)
    {
        data = _data;
        next = nullptr;
    }
    
};
struct SinglyLinkedList {
    SinglyLinkedListNode* head; // con trỏ tới nút đầu danh sách
    long size; // số nút trong danh sách, nếu cần
    /* Constructor mặc định tạo danh sách rỗng */
    SinglyLinkedList() {
        head = NULL;
        size = 0;
    }
    

    bool isEmpty() { return head == NULL; }
    
};



SinglyLinkedListNode* AddFirst(SinglyLinkedListNode* llist, int data)
{
    SinglyLinkedListNode* newNode = new SinglyLinkedListNode(data);
    newNode->next = llist;
    llist = newNode;
    return llist;
}

void DeleteFirst(SinglyLinkedListNode* llist)
{
    SinglyLinkedListNode* p;
    p = llist;
    llist = llist->next;
    delete p;
}

void PrintLinkedList(SinglyLinkedListNode* head)
{
    
    SinglyLinkedListNode* p;
    p = head;
    while (p != nullptr)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    SinglyLinkedListNode* pre;
    pre = nullptr;
    SinglyLinkedListNode* curr;
    curr = llist;
    SinglyLinkedListNode* next;
    next = NULL;

    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    llist = pre;
    return llist;
}

SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) 
{
    SinglyLinkedListNode* newNode = NULL;
    SinglyLinkedListNode* p = head1;
    SinglyLinkedListNode* q = head2;

    while (p != NULL && q != NULL)
    {
        if (p->data < q->data)
        {
            newNode = AddFirst(newNode, p->data);
            p = p->next;
        }
        else
        {
            newNode = AddFirst(newNode, q->data);
            q = q->next;

        }  
    }

    if (p == NULL && q != NULL)
    {
        while (q != NULL)
        {
            newNode = AddFirst(newNode, q->data);
            q = q->next;
        }
    }
    else if (p != NULL && q == NULL)
    {
        while (p != NULL)
        {
            newNode = AddFirst(newNode, p->data);
            p = p->next;
        }
    }

    newNode = reverse(newNode);
    return newNode;
}


void truncate(char a[], int n)
{
    int length = 0;
    while (true)
    {
        if (a[length] == NULL)
        {
            break;
        }
        length++;
    }
    //cout << length;
    if (n >= length) return;

    a[n] = '\0';

}


bool is_palindrome(char a[])
{
    bool check = true;
    int length = 0;
    while (true)
    {
        if (a[length] == NULL)
        {
            break;
        }
        length++;
    }
    for (int i = 0; i < length / 2; i++)
    {
        if (a[i] != a[length - i - 1])
        {
            check = false;
            break;
        }
    }
    return check;
}




struct String
{
    char* str;
    int n;
    String(const char* s)
    {
        n = 0;
        while (s[n] != '\0')
        {
            n++;
        }
        str = new char[n];
        for (int i = 0; i < n; i++)
        {
            str[i] = s[i];
        }
    }

    void Print()
    {
        for (int i = 0; i < n; i++)
        {
            cout << str[i];    
        }
    }

    void append(const char* s)
    {
        int length2 = 0;
        while (s[length2] != '\0')
        {
            length2++;
        }

        char* newStr = new char[n + length2];
        for (int i = 0; i < n; i++)
        {
            newStr[i] = str[i];
        }
        for (int i = n; i < n + length2; i++)
        {
            newStr[i] = s[i - n];
        }

        n = n + length2;
        delete[] str;
        str = newStr;

    }

    ~String()
    {

    }


};





int main()
{
    char* s = new char[10];
    //cin >> s;
    //cout << s;
    String g("hello");
    g.append(" there!");
    g.Print();


    /*int min = 1;
    int max = 7;
    SinglyLinkedListNode* llist1 = new SinglyLinkedListNode(max);
    SinglyLinkedListNode* llist2 = new SinglyLinkedListNode(max - 1);
    for (int i = max - 2; i >= min; i--)
    {
        if (i % 2 == 1)
        {
            llist1 = AddFirst(llist1, i);

        }
        else
        {
            llist2 = AddFirst(llist2, i);

        }
    }
	
    PrintLinkedList(llist1);
    PrintLinkedList(llist2);

    SinglyLinkedListNode* llist3;
    llist3 = mergeLists(llist1, llist2);
    PrintLinkedList(llist3);*/



	return 0;

}



