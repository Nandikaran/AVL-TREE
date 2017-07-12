#include<stdio.h>
#include<stdlib.h>
typedef struct t_node_tag
{
    int data;
    struct t_node_tag* left;
    struct t_node_tag* right;
}t_node;
t_node* InitTree(t_node* root);
t_node* InsertTree(t_node* root, int d);
void PrintTree(t_node* root);
int HeightTree(t_node* root);
t_node* CheckAVL(t_node* root);
t_node* RotateLeft(t_node* ptr);
t_node* RotateRight(t_node* ptr);
t_node* RemoveNode(t_node* root, t_node* p, int n);
t_node* DeleteTree(t_node* root, int d);

t_node* InsertTree(t_node* root, int d)
{
    t_node* ptr, *nptr;
    int flag=0;
    nptr=(t_node*)malloc(sizeof(t_node));
    nptr->data=d;
    nptr->left=NULL;
    nptr->right=NULL;
    ptr=root;
    if(ptr==NULL)
    {
        root=nptr;
    }
    else
    {
        while(ptr!=NULL&&flag==0)
        {
            if(ptr->data>=d)
            {
                if(ptr->left==NULL)
                {
                    ptr->left=nptr;
                    flag=1;
                }
                else
                {
                    ptr=ptr->left;
                }
            }
            else
            {
                if(ptr->right==NULL)
                {
                    ptr->right=nptr;
                    flag=1;
                }
                else
                {
                    ptr=ptr->right;
                }
            }
        }
    }
    return root;
}
t_node* InitTree(t_node* root)
{
    int d;
    FILE* fptr=fopen("data.txt","r");
    fseek(fptr, 0, SEEK_END);
    unsigned long len=ftell(fptr);
    if(len>0)
    {
        rewind(fptr);
        while(!feof(fptr))
        {
            fscanf(fptr,"%d",&d);
            root=InsertTree(root,d);
            root=CheckAVL(root);
        }
    }

    fclose(fptr);
    return root;
}
void PrintTree(t_node* root)
{
    t_node* ptr=root;
    if(ptr!=NULL)
    {
        PrintTree(ptr->left);
        printf("%d, ",ptr->data);
        PrintTree(ptr->right);
    }
}

int HeightTree(t_node* root)
{
    t_node* ptr=root;
    int lh, rh, retval=-1;
    if(ptr!=NULL)
    {
        lh=HeightTree(ptr->left);
        rh=HeightTree(ptr->right);
        if(lh>rh)
        {
            retval=1+lh;
        }
        else
        {
            retval=1+rh;
        }
    }
    return retval;
}

t_node* CheckAVL(t_node* root)
{
    t_node* ptr=root;
    int lh, rh;
    if(ptr!=NULL)
    {
        ptr->left=CheckAVL(ptr->left);
        ptr->right=CheckAVL(ptr->right);
        lh=HeightTree(ptr->left);
        rh=HeightTree(ptr->right);
        if(lh-rh>1)
        {
            lh=HeightTree((ptr->left)->left);
            rh=HeightTree((ptr->left)->right);
            if(lh-rh>0)
            {
                ptr=RotateRight(ptr);
            }
            else if(lh-rh<0)
            {
                ptr->left=RotateLeft(ptr->left);
                ptr=RotateRight(ptr);
            }
            else if(lh-rh==0)
            {
                ptr=RotateRight(ptr);
            }
        }
        else if(lh-rh<(-1))
        {
            lh=HeightTree((ptr->right)->left)+1;
            rh=HeightTree((ptr->right)->right)+1;
            if(lh-rh<0)
            {
                ptr=RotateLeft(ptr);
            }
            else if(lh-rh>0)
            {
                ptr->right=RotateRight(ptr->right);
                ptr=RotateLeft(ptr);
            }
            else if(lh-rh==0)
            {
                ptr=RotateLeft(ptr);
            }
        }
    }
    return ptr;
}

t_node* DeleteTree(t_node* root, int d)
{
    int n=0;
    t_node* p=root;
    if(p!=NULL)
    {
        if(p->data==d)
        {
            if(p->left==NULL&&p->right==NULL)
            {
                n=1;
            }
            else if(p->left==NULL&&p->right!=NULL)
            {
                n=2;
            }
            else if(p->left!=NULL&&p->right==NULL)
            {
                n=3;
            }
            else
            {
                n=4;
            }

        }
        else
        {
            while((p->left)->data!=d&&(p->right)->data!=d&&p!=NULL)
            {
                if(p->data>d)
                {
                    p=p->left;
                }
                else
                {
                    p=p->right;
                }
            }
            if(p==NULL)
            {
                n=0;
            }
            else
            {
                if((p->left)->data==d&&(p->left)->left==NULL&&(p->left)->right==NULL)
                {
                    n=5;
                }
                else if((p->right)->data==d&&(p->right)->left==NULL&&(p->right)->right==NULL)
                {
                    n=6;
                }
                else if((p->left)->data==d&&(p->left)->left!=NULL&&(p->left)->right==NULL)
                {
                    n=7;
                }
                else if((p->left)->data==d&&(p->left)->left==NULL&&(p->left)->right!=NULL)
                {
                    n=8;
                }
                else if((p->right)->data==d&&(p->right)->left==NULL&&(p->right)->right!=NULL)
                {
                    n=9;
                }
                else if((p->right)->data==d&&(p->right)->left!=NULL&&(p->right)->right==NULL)
                {
                    n=10;
                }
                else if((p->left)->data==d&&(p->left)->left!=NULL&&(p->left)->right!=NULL)
                {
                    n=11;
                }
                else if((p->right)->data==d&&(p->right)->left!=NULL&&(p->right)->right!=NULL)
                {
                    n=12;
                }
            }
        }

        root=RemoveNode(root,p,n);
        root=CheckAVL(root);
    }
    return root;
}

t_node* RemoveNode(t_node* root, t_node* p, int n)
{
    t_node* ptr, *temp, *prev;
    switch(n)
    {
    case 1:
        temp=root;
        root=NULL;
        free(temp);
        break;
    case 2:
        temp=root;
        root=root->right;
        free(temp);
        break;
    case 3:
        temp=root;
        root=root->left;
        free(temp);
        break;
    case 4:
        temp=root;
        ptr=temp->left;
        prev=ptr;
        while(ptr->right!=NULL)
        {
            prev=ptr;
            ptr=ptr->right;
        }
        if(prev==ptr)
        {
            ptr->right=temp->right;
        }
        else
        {
            prev->right=ptr->left;
            ptr->right=temp->right;
            ptr->left=temp->left;
        }
        root=ptr;
        free(temp);
        break;
    case 5:
        temp=p->left;
        p->left=NULL;
        free(temp);
        break;
    case 6:
        temp=p->right;
        p->right=NULL;
        free(temp);
        break;
    case 7:
        temp=p->left;
        p->left=(p->left)->left;
        free(temp);
        break;
    case 8:
        temp=p->left;
        p->left=(p->left)->right;
        free(temp);
        break;
    case 9:
        temp=p->right;
        p->right=(p->right)->right;
        free(temp);
        break;
    case 10:
        temp=p->right;
        p->right=(p->right)->left;
        free(temp);
        break;
    case 11:
        temp=p->left;
        ptr=temp->left;
        prev=ptr;
        while(ptr->right!=NULL)
        {
            prev=ptr;
            ptr=ptr->right;
        }
        if(prev==ptr)
        {
            ptr->right=temp->right;
        }
        else
        {
            prev->right=ptr->left;
            ptr->right=temp->right;
            ptr->left=temp->left;
        }
        p->left=ptr;
        free(temp);
        break;
    case 12:
        temp=p->right;
        ptr=temp->left;
        prev=ptr;
        while(ptr->right!=NULL)
        {
            prev=ptr;
            ptr=ptr->right;
        }
        if(prev==ptr)
        {
            ptr->right=temp->right;
        }
        else
        {
            prev->right=ptr->left;
            ptr->right=temp->right;
            ptr->left=temp->left;
        }
        p->right=ptr;
        free(temp);
        break;
    default:
        break;
    }
    return root;
}

t_node* RotateLeft(t_node* ptr)
{
    t_node* tmp=ptr->right;
    ptr->right=tmp->left;
    tmp->left=ptr;
    return tmp;
}
t_node* RotateRight(t_node* ptr)
{
    t_node* tmp=ptr->left;
    ptr->left=tmp->right;
    tmp->right=ptr;
    return tmp;
}

void main()
{
    int h,d,flag=1;
    t_node* root=NULL;
    root=InitTree(root);
    PrintTree(root);
    h=HeightTree(root);
    printf("\nHeight of Tree : %d\n",h);
    while(flag==1)
    {
        printf("\nenter the value you want to delete\n");
        scanf("%d",&d);
        root=DeleteTree(root,d);
        PrintTree(root);
        printf("\ndo you want to delete again\nYES: 1\nNO: 0\n");
        scanf("%d",&flag);
    }
}
