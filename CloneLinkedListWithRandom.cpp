#include <iostream>
#include <map>

using namespace std;

class node
{
public:
    int data;
    node *next;
    node *random;

    node(int n)
    {
        this->data = n;
        this->next = NULL;
        this->random = NULL;
    }
};

void insert(node *&head, node *&tail, int n)
{
    node *temp = new node(n);
    if (tail == NULL)
        head = temp;
    else
        tail->next = temp;
    tail = temp;
}

void print(node *&head)
{
    node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void printRandom(node *&head)
{
    node *temp = head;
    while (temp != NULL)
    {
        if (temp->random != NULL)
            cout << temp->data << " " << temp->random->data << endl;
        temp = temp->next;
    }
    cout << endl;
}

void SetRandom(node *&head)
{
    node *temp = head;
    node *prev = head;
    int cnt = 1;
    while (temp != NULL)
    {
        if (cnt & 1)
        {
            temp->random = temp->next;
            if (temp->random != NULL)
                temp->random = temp->random->next;
        }
        else
            temp->random = prev;

        if (temp->random != NULL)
            cout << temp->random->data << " ";
        prev = temp;
        temp = temp->next;
        cnt++;
    }
    cout << endl;
}

/*
Approach 1:
We can solve using nested loop having :
Time Complexity : O(n^2)
Space Complexity : O(1)
*/

/*
Approach 2:
Using data structure like we can save the mapping of original node with the clone node.To allocate random pointer in the dummy node using mapping.

Time Complexity : O(n)
Space Complexity : O(n)
*/

// node *Clone(node *&head)
// {
//     // Create a Clone List
//     node *temp = head;
//     node *clone = NULL;
//     node *cloneTail = NULL;

//     while (temp != NULL)
//     {
//         insert(clone, cloneTail, temp->data);
//         temp = temp->next;
//     }

//     // Create a map
//     map<node *, node *> mapping;
//     temp = head;
//     node *clonetemp = clone;
//     while (temp != NULL && clonetemp != NULL)
//     {
//         mapping[temp] = clonetemp;
//         temp = temp->next;
//         clonetemp = clonetemp->next;
//     }

//     temp = head;
//     clonetemp = clone;

//     while (temp != NULL)
//     {
//         clonetemp->random = mapping[temp->random];
//         temp = temp->next;
//         clonetemp = clonetemp->next;
//     }

//     return clone;
// }

/*
Approach 3:
We can chane next links between the nodes to keep track of all the list.
Time Complexity : O(n)
Space Complexity : O(1)
*/

node* Clone(node *head)
{
    // Create a Clone List
    node *temp = head;
    node *cloneHead = NULL;
    node *cloneTail = NULL;
    while (temp != NULL)
    {
        insert(cloneHead, cloneTail, temp->data);
        temp = temp->next;
    }

    // CloneNodes add in between original node
    temp = head;
    node *clonetemp = cloneHead;
    while (temp != NULL && clonetemp != NULL)
    {
        node *next = temp->next;
        temp->next = clonetemp;
        temp = next;

        next = clonetemp->next;
        clonetemp->next = temp;
        clonetemp = next;
    }

    // Random pointer Copy
    temp = head;
    while (temp != NULL)
    {
        if (temp->next != NULL)
            temp->next->random = (temp->random) ? temp->random->next : temp->random;

        temp = temp->next->next;
    }

    // Reverse Changes done in Step 2
    temp = head;
    clonetemp = cloneHead;
    while (temp != NULL && clonetemp != NULL)
    {
        temp->next = clonetemp->next;
        temp = temp->next;

        if (temp != NULL)
            clonetemp->next = temp->next;

        clonetemp = clonetemp->next;
    }

    //Return Head of clone
    return cloneHead;
}

int main()
{
    node *head = NULL;
    node *tail = NULL;
    insert(head, tail, 1);
    insert(head, tail, 2);
    insert(head, tail, 3);
    insert(head, tail, 4);
    insert(head, tail, 5);

    SetRandom(head);

    print(head);
    printRandom(head);

    cout << "Printing clone" << endl;
    node *ans = Clone(head);
    print(ans);
    printRandom(ans);

    return 0;
}
