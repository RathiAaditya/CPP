/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <iostream>
#include<bits/stdc++.h>
using namespace std;
class CircleList;

typedef int Elem;				// element type
class CNode {					    // circularly linked list node
private:
    Elem elem;					    // linked list element value
    CNode* next;				    // next item in the list
    friend class CL;		// provide CircleList access
};

class CL {				    // a circularly linked list
public:
    CL();				    // constructor
    ~CL();				    // destructor
    bool empty() const;				// is list empty?
    const Elem& front() const;		// element at cursor
    const Elem& back() const;		// element following cursor
    void advance();				    // advance cursor
    void add(const Elem& e);		// add after cursor
    void remove();				    // remove node after cursor
    void traverse();                // traverse the list
private:
    CNode* cursor;				    // the cursor 
};
CL::CL()
{
    cursor=NULL;
}
bool CL:: empty() const
{
    return cursor==NULL;
}
 const Elem &CL:: front() const 
{
    return cursor->next->elem;
}
const Elem &CL:: back() const
{
    return cursor->elem;    
}
void CL:: advance()
{
    cursor=cursor->next;
}
void CL ::add(const Elem&e)
{
    CNode *v= new CNode;
    v->elem =e;
    if(cursor==NULL)
    {
        v->next=v;
        cursor=v;
    }
    else
    {
        v->next=cursor->next;
        cursor->next=v;
        cursor=v;
    }
}
void CL::remove()
{
    CNode *old = cursor->next;
    if(old==cursor)
    {
        cursor=NULL;
    }
    else
    {
        cursor->next=old->next;
    }
    delete old;
}
void CL::traverse()
{
    CNode *temp=cursor->next;
        while(temp!=cursor)
        {
            cout<<temp->elem<<" ";
            temp=temp->next;
        }
        cout<<temp->elem;
        cout<<endl;
}
CL::~CL()
{
    while(!empty())
    remove();
}

int main(){
   int n; cin>>n;
   CL cl;
   for(int i=1;i<=n;i++)
  {
      cl.add(i);
  }

   for(int i=0;i<n-1;i++)
   {
      cl.advance();
      cl.remove();
   }
   cl.traverse();
}