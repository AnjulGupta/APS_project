#include<stdio.h>
#include<malloc.h>

#include<bits/stdc++.h>

using namespace std;


//node structure
struct node 
{
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
}*H=NULL,*Hr=NULL;


//node creation 
struct node* create_node(int k) 
{
    struct node* p;
    //p = (struct node*) malloc(sizeof(struct node));
    p=new node;
    p->n = k;
    return p;
}


//heap initialisation 
struct node* initialise_heap() 
{
    struct node* np;
    np = NULL;
    return np;
}
 
//merging two heaps 
struct node* simply_merging(struct node* H1, struct node* H2) 
{
    //cout<<"simply merging";


    struct node* H = initialise_heap();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
   
        if (y!=NULL && z != NULL && y->degree <= z->degree)
            H = y;
        else if (y!=NULL && z != NULL && y->degree > z->degree)
            H = z;
        else if (z==NULL )
            H = y;
        else
            H = z;
    
    while (y != NULL && z != NULL) 
    {
        if (y->degree < z->degree) 
        {
            y = y->sibling;
        } 
        else if (y->degree == z->degree) 
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } 
        else 
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
   
    return H;
}

//merging two same degree nodes
int linking_same_degnodes(struct node* y, struct node* z) 
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
 

// union of two heaps 
struct node* union_of_heaps (struct node* H1, struct node* H2) 
{
   // cout<<"union_of_heaps";
    
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = initialise_heap();
    // struct node* H = new node;
    H = simply_merging(H1, H2);
    if (H == NULL)
        return H;
   
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
   
    while (next_x != NULL) 
    {
        if ((x->degree != next_x->degree) ) 
        {
            prev_x = x;
            x = next_x;
        } 
        else if ((x->degree == next_x->degree) && (next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree)
        {
             prev_x = x;
             x = next_x;
        }
        else 
        {
            if (x->n <= next_x->n) 
            {
                x->sibling = next_x->sibling;
                linking_same_degnodes(next_x, x);
            } 
            else 
            {
                if (prev_x == NULL)
                { 
                    H = next_x;
                }
                else
                {
                    prev_x->sibling = next_x;
                }

                linking_same_degnodes(x, next_x);
                x = next_x;
            }
        }
        
        next_x = x->sibling;
    }
    return H;
}

//insert operation 
struct node* insert(struct node* H, struct node* x) 
{
     struct node* H1 = initialise_heap();
    // struct node* H1 = new node;

    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = union_of_heaps(H, H1);
    return H;
}


//printing only root elements 
int display_root_elements(struct node* H) 
{
    struct node* p;
    if (H == NULL) {
        printf("\nheap is empty");
        return 0;
    }
    printf("\nroots are-\n");
    p = H;
    while (p != NULL) {
        printf("%d", p->n);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
}
 

//extracting min node operation 
struct node* extract_min_node(struct node* H1) 
{
    int min;
    struct node* t = NULL;
    struct node* x = H1;
    struct node *Hr;
    struct node* p;
    Hr = NULL;
    if (x == NULL) 
    {
        printf("\nnode not found");
        return x;
    }

    p = x;
    
    ///
    min=p->n;

    while (p->sibling != NULL) 
    {
        if ((p->sibling)->n < min) 
        {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }

        p = p->sibling;
    }
    
    ///
  //  cout<<"min : "<<x->n<<"\n";

    ///removing the extracred node from sibling
    ///and making next to extracted as sibling
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;


   
    
    // if (x->child != NULL) 
    // {
    //     reverting_list(x->child);
    //     (x->child)->sibling = NULL;

    // }


    vector<node *>v;
    struct node *temp=x->child;
    while(temp!=NULL)
    {
        v.push_back(temp);
        temp=temp->sibling;
    }
    reverse(v.begin(), v.end());
  
    cout<<"all anath child : ";
    for(int i=0;i<v.size();i++)
    {
        cout<<v[i]->n<<" ";
    }
    cout<<endl;

    for(int i=0;i<v.size();i++)
    {
       v[i]->parent=NULL; 
       H=insert(H, v[i]);
       //cout<<;
    }


    // Hr=x->child;
    
    // H = union_of_heaps(H1, Hr);

    return x;
}
 

//reverting children in list once root deleted 
void reverting_list(struct node* y) 
{
    if (y->sibling != NULL) {
        reverting_list(y->sibling);
        (y->sibling)->sibling = y;
    } 
    // else 
    // {
        Hr = y;
    // }
}

//search operation 
struct node* search_element(struct node* H, int k) 
{
    struct node* x = H;
    struct node* p = NULL;
    if (x->n == k) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = search_element(x->child, k);
    }
 
    if (x->sibling != NULL && p == NULL) {
        p = search_element(x->sibling, k);
    }
    return p;
}
 
int decrease_key(struct node* H, int i, int k) 
{
    int temp;
    struct node* p;
    struct node* y;
    struct node* z;
    p = search_element(H, i);
    if (p == NULL) {
        printf("\ninvalid choice\n");
        return 0;
    }
    if (k > p->n) {
        printf("\nnew key cannot be greater than previous key ");
        return 0;
    }
    p->n = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->n < z->n) {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    printf("\nkey reduced!");
}
 
int delete_key(struct node* H, int k) 
{
    struct node* np;
    if (H == NULL) {
        printf("\nheap is empty");
        return 0;
    }
 
    decrease_key(H, k, -1000);
    np = extract_min_node(H);
    if (np != NULL)
        printf("\nnode deleted");
}


// print function for Binomial Tree 
void printTree(node *h) 
{ 
    while (h) 
    { 
        cout << h->n << " "; 
        printTree(h->child); 
        h = h->sibling; 
    }
  //  cout<<endl; 
} 
  
// print function for binomial heap 
void printHeap(struct node *H) 
{ 
    while(H!=NULL)
    {
       // while (it != _heap.end()) 
        // { 
            printTree(H); 
        
        // }

        H=H->sibling; 
    }
} 


 
int main() {
    int i, n, m, option,nkey;
    struct node* p;
    struct node* np;
    char ch;
    cout<<"enter initial number of elements :";
    cin>>n;
    cout<<"enter elements :\n";
    for (i = 1; i <= n; i++) 
    {
        cin>>m;
        np = create_node(m);
        H = insert(H, np);
    }

    display_root_elements(H);
    cout<<"cuurent heap is: ";
    printTree(H);
    cout<<endl;
    
    do 
    {
        cout<<"enter choice: \n";
        cout<<"1)insert 2)extract min key 3)decrease key 4)delete 5)quit 6)print heap \n";
        cin>>option;
        switch (option) {
        case 1:
            do {
                cout<<"enter element:";
                cin>>m;
                p = create_node(m);
                H = insert(H, p);
                display_root_elements(H);
                cout<<"cuurent heap is: ";
                printTree(H);
                cout<<endl;
                cout<<"\ninsert more(y): \n";
                // fflush(stdin);
                cin>>ch;
            } while (ch == 'Y' || ch == 'y');
         break;
        case 2:
            do {
                // printf("\nEXTRACTING THE MINIMUM KEY NODE");
                p = extract_min_node(H);
                if (p != NULL)
                    cout<<"\n extracted min node is : "<<p->n;
                // printf("\nNOW THE HEAP IS:\n");
                display_root_elements(H);
                cout<<"cuurent heap is: ";
                printTree(H);
                cout<<endl;
                cout<<"\nextract more(y): \n";
                cin>>ch;
            } while (ch == 'Y' || ch == 'y');
            break;
        case 3:
            do {
                cout<<"enter old key : ";
                cin>>m;
                cout<<"enter new key : ";
                cin>>nkey;
                decrease_key(H, m, nkey);
                cout<<"root elements :\n ";
                display_root_elements(H);
                cout<<"cuurent heap is: ";
                printTree(H);
                cout<<endl;
                cout<<"\ndecrease key more(y): \n";
                cin>>ch;
            } while (ch == 'Y' || ch == 'y');
            break;
        case 4:
            do {
                cout<<"enter key : ";
                cin>>m;
                delete_key(H, m);
                display_root_elements(H);
                cout<<"cuurent heap is: ";
                printTree(H);
                cout<<endl;
                printf("\ndelete more(y/Y)\n");

                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'Y');
            break;
        case 5:
            printf("\nexited\n");
            break;
        case 6:
                cout<<"cuurent heap is: ";
                printTree(H);
                cout<<endl;
             break;
        default:
            printf("\nwrong choice\n");
        }
    } while (option!= 5);
}