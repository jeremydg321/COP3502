#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp1, *fp2;
int count =0;

struct treeNode {
  char name[20];
  struct treeNode *left;
  struct treeNode *right;
};




  //////////////////////////////////////////////////////////////////////
void in(struct treeNode *node) {


  if (node != NULL) {
    in(node->left);
    fprintf(fp2,"%s ", node->name);
    in(node->right);
  }
}
//////////////////////////////////////////////////////////////////////
  void post(struct treeNode *node) {


  if (node != NULL) {
    post(node->left);

    post(node->right);
    fprintf(fp2,"%s ", node->name);
  }
}
 //////////////////////////////////////////////////////////////////////
void pre(struct treeNode *node) {


  if (node != NULL) {
    fprintf(fp2,"%s ", node->name);
    pre(node->left);

    pre(node->right);
}
}
 //////////////////////////////////////////////////////////////////////
  int countBefore(struct treeNode *node, char*n)
  {
    if (node != NULL) {
    countBefore(node->left,n);
    if(strcmp(node->name,n)==0||strcmp(node->name,n)>1||strcmp(node->name,n)==1)
        return count;
    //printf("%s ", node->name);
    count++;
    countBefore(node->right,n);
    if(strcmp(node->name,n)==0||strcmp(node->name,n)>1)
        return count;
  }

  }

 //////////////////////////////////////////////////////////////////////
int search(struct treeNode *node, char *n) {


  if (node != NULL) {


    if (strcmp(n,node->name) ==0)
      return 1;


    if (strcmp(n,node->name)<=-1)
      return search(node->left, n);

    if (strcmp(n,node->name)>=1)
      return search(node->right, n);

  }
  else
    return 0;
}

//////////////////////////////////////////////////////////////////////
struct treeNode* createNode(char  *n) {


  struct treeNode* temp;
  temp = (struct treeNode*)malloc(sizeof(struct treeNode));
  strcpy(temp->name,n);
  temp->left = NULL;
  temp->right = NULL;

  return temp;
}
//////////////////////////////////////////////////////////////////////
struct treeNode* insertNode(struct treeNode *root,
                         struct treeNode *temp) {


  if (root == NULL)
    return temp;
  else {


    if (strcmp(temp->name, root->name)>=1) {


      if (root->right != NULL)
        root->right = insertNode(root->right, temp);


      else
        root->right = temp;
    }


    else if (strcmp(temp->name, root->name)<=-1){


      if (root->left != NULL)
        root->left = insertNode(root->left, temp);


      else
        root->left = temp;
    }


    return root;
  }
}


//////////////////////////////////////////////////////////////////////

struct treeNode* parent(struct treeNode *root, struct treeNode *node) {


  if (root == NULL || root == node)
    return NULL;


  if (root->left == node || root->right == node)
    return root;


  if (strcmp(node->name,root->name)<=-1)
    return parent(root->left, node);


  else if (strcmp(node->name,root->name)>=1)
    return parent(root->right, node);

  return NULL;

}
 //////////////////////////////////////////////////////////////////////
struct treeNode* minVal(struct treeNode *root) {


  if (root->left == NULL)
    return root;


  else
    return minVal(root->left);
}


//////////////////////////////////////////////////////////////////////
int ifLeaf(struct treeNode *node) {

  return (node->left == NULL && node->right == NULL);
}
//////////////////////////////////////////////////////////////////////
int OnlyLeftChild(struct treeNode *node) {
  return (node->left!= NULL && node->right == NULL);
}
//////////////////////////////////////////////////////////////////////

int OnlyRightChild(struct treeNode *node) {
  return (node->left== NULL && node->right != NULL);
}

//////////////////////////////////////////////////////////////////////
struct treeNode* findNode(struct treeNode *node, char *n) {


  if (node != NULL) {

    if (strcmp(n,node->name)==0)
      return node;


    if (strcmp(n,node->name)<=-1)
      return findNode(node->left, n);


    if (strcmp(n,node->name)>=1)
      return findNode(node->right, n);

  }
  else
    return NULL;
}

//////////////////////////////////////////////////////////////////////


struct treeNode* delete(struct treeNode* root, char *n) {

  struct treeNode *delnode, *temp_node, *save_node;
  struct treeNode *par;
  char save_name[20];

  delnode = findNode(root, n);
  par = parent(root, delnode);


  if (ifLeaf(delnode)) {


    if (par == NULL) {
      free(root);
      return NULL;
    }


    if (strcmp(n , par->name)<=-1)
        {
      free(par->left);
      par->left = NULL;
    }


    else
        {
      free(par->right);
      par->right = NULL;
    }

    return root;
  }
  else if (OnlyLeftChild(delnode)) {


    if (par == NULL) {
      save_node = delnode->left;
      free(delnode);
      return save_node;
    }


    if (strcmp(n , par->name)<=-1)
    {
      save_node = par->left;
      par->left = par->left->left;
      free(save_node);
    }


    else
        {
      save_node = par->right;
      par->right = par->right->left;
      free(save_node);
    }

    return root;

  }

  else if (OnlyRightChild(delnode)) {


    if (par == NULL) {
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }


    if (strcmp(n , par->name)<=-1)
        {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    }


    else
        {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }

    return root;
  }
  else {


temp_node=minVal(delnode->right);

strcpy(save_name,temp_node->name);

delete(root,temp_node->name);

strcpy(delnode->name,save_name);
  }
  return root;
}

  //////////////////////////////////////////////////////////////////////
int main()
{

    int i=0,j = 0,n, s, d;

fp1 = fopen("in.txt", "r");
fp2 = fopen("out.txt", "w");

    char nameN[20][100],nameS[20][100],nameD[20][100];
    struct treeNode *root=NULL, *element;




    fscanf(fp1,"%d %d %d", &n, &s, &d);

    printf("%d %d %d\n", n, s, d);

     while (!feof (fp1)&&i<n)
        {
            fscanf(fp1, "%s ", nameN[j]);
            printf("%s\n",nameN[j]);

            i++;
            j++;
        }
        puts("");
    i=0;
    j=0;
         while (!feof (fp1)&&i<s)
        {
            fscanf(fp1, "%s ", nameS[j]);
            printf("%s\n",nameS[j]);

            ++i;
            ++j;
        }
        puts("");
    i=0;
    j=0;
         while (!feof (fp1)&&i<d)
        {
            fscanf(fp1, "%s ", nameD[j]);
            printf("%s\n",nameD[j]);

            ++i;
            ++j;
        }


for(i=0;i<n;i++)
{


    element= createNode(nameN[i]);




    root = insertNode(root,element);
}

fprintf(fp2,"Preorder: ");
pre(root);
fprintf(fp2,"\n");
fprintf(fp2,"Inorder: ");
in(root);
fprintf(fp2,"\n");
fprintf(fp2,"Postorder: ");
post(root);
fprintf(fp2,"\n");


fprintf(fp2,"Search Phase: \n");

for(i=0;i<s;i++)
{

    if(!search(root,nameS[i]))
        fprintf(fp2,"%s, Not found\n", nameS[i]);
    else
    {
       fprintf(fp2,"%s, Found, ", nameS[i]);

       fprintf(fp2,"Items Before: %d\n",countBefore(root, nameS[i]));
        count = 0;



    }


}



fprintf(fp2,"Delete Phase: \n");

for(i=0;i<d;i++)
{

    if (!search(root, nameD[i]))
        fprintf(fp2,"Sorry that value isn't in the tree to delete.\n");
      else {
         root = delete(root, nameD[i]);
         fprintf(fp2,"%s: Deleted\n",nameD[i]);
      }
}


fprintf(fp2,"Preorder: ");
pre(root);
fprintf(fp2,"\n");
fprintf(fp2,"Inorder: ");
in(root);
fprintf(fp2,"\n");
fprintf(fp2,"Postorder: ");
post(root);
fprintf(fp2,"\n");

fclose(fp1);
fclose(fp2);

printf("\nCheck out.txt");



}
