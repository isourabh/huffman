#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
  unsigned char c :8;
}code_gen;
struct node1{
  char data;
  int f;
  struct node1 *left;
  struct node1 *right;
  struct node1 *p;
};
int len;
typedef struct node1 node;
char e[50][10];
void decode(char en[50], node * root,int u);
char get_letter(char code[], node *root);
void encode(char data[], char en[],char codes[128][10]);
char convert_string_char(char code[]);
void inorder(node *);
node * extract_min( node **);
void sort_list(node **);
node  * create_node(char , int);
void sort(char *, int *, int );
void find_code(node *, char *, char[128][10]);
main()
{
  char data[50],ch,codes[128][10],code[10],en[50],dn[50];
  node *new;
  int temp,i,freq[128]={0},u=0;
  char a[128];// to hold unique letter
  int b[128];// to hold coressponding frequencies
  node *list[128],*x,*y;
  strcpy(code,"");
  printf("enter a string to compress \n");
  gets(data);
  i=0;
  while(data[i]!='\0')
    {
      temp=data[i];
      freq[temp]++;
      i++;
    }
  for(i=0;i<128;i++)
    {
      if(freq[i]!=0)
	{
	  ch=i;
	  printf("%c \n",ch);
	  a[u]=ch;
	  b[u]=freq[i];
	  u++;
	  sort(a,b,u);
	  //new=make_node(ch,freq[i]);
	  //add_to_list(new);
	}
    }
  len=u;
  printf("printing sorted list\n");
  for(i=0;i<u;i++)
    {
      new=create_node(a[i],b[i]);
      list[i]=new;
    }
  for(i=0;i<u;i++)
    {
      x=list[i];
      printf("%c %d\n",x->data,x->f);
    }
  for(i=0;i<u-1;i++)
    {
      x=extract_min(list);
      y=extract_min(list);
      new=create_node('\0',0);
      new->left=x;
      new->right=y;
      new->f=x->f + y->f;
      x->p=new;
      y->p=new;
      list[len]=new;
      len++;
      sort_list(list);
    }
  x=list[0];
  printf("%c %d\n",x->data,x->f);
  printf("-----printing tree-----\n");
  inorder(list[0]);
  find_code(list[0],code,codes);
  len=u;
  encode(data,en,codes);
  printf("printing encoded data in compressed format\n");
  for(i=0;i<strlen(data);i++)
    printf("%c",en[i]);
  printf("\nprinting encoded data in uncompressed format\n");
  for(i=0;i<strlen(data);i++)
    puts(e[i]);
  printf("decoding\n");
  decode(en,list[0],strlen(data));
  printf("\n done!! \n");
}
void decode(char en[50], node * root,int u)
{
  char code[10],ch;
  int i=0;
  while(i<u)
    {
      strcpy(code,e[i]);
      ch=get_letter(code,root);
      printf("%c",ch);
      i++;
    }
}
char get_letter(char code[], node *root)
{
  int j=0;
  while(root->left!=NULL || root->right!=NULL)
    {
      if(code[j]=='0')
	root=root->left;
      else
	root=root->right;
      j++;
    }
  return root->data;
  
}
void encode(char data[], char en[],char codes[128][10])
{
  int i=0,temp;
  char code[10];
  while(i<strlen(data))
    {
      temp=data[i];
      strcpy(code,codes[temp]);
      strcpy(e[i],code);
      //fwrite(code,10*sizeof(char),1,
      en[i]=convert_string_char(code);
      i++;
    }
}
char convert_string_char(char code[10])
{
  int i=0;
  char c=0;
  while(code[i]!='\0')
    {
      if(code[i]=='1')
	{
	  c=c*2;
	  c=c+1;
	}
      else
	{
	  c=c*2;
	}
      i++;
    }
  return c;
}
void find_code(node *root,char code[],char codes[128][10])
{
  char temp[10];
  if(root->left==NULL && root->right==NULL)
    {
      strcpy(codes[(int)(root->data)],code);
      printf("code for %c is %s\n",root->data,code);
    }
  if(root->right!=NULL)
    {
      strcpy(temp,code);
      strcat(temp,"1");
      find_code(root->right,temp,codes);
    }
  if(root->left!=NULL)
    {
      strcpy(temp,code);
      strcat(temp,"0");
      find_code(root->left,temp,codes);
    }
}
void inorder(node *root)
{
  if(root!=NULL)
    {
      inorder(root->left);
      printf("%c %d\n",root->data,root->f);
      inorder(root->right);
    }
}

node * extract_min(node **list)
{
  node *temp;
  temp = list[0];
  list[0]=list[len-1];
  //free(list[len-1]);
  list[len-1]=NULL;
  len--;
  sort_list(list);
  return temp;
}
void sort_list(node **list)
{
  int i,j;
  node *x,*y;
  for(i=0;i<len;i++)
    {
      for(j=0;j<len-1;j++)
	{
	  //printf("wtf\n");
	  x=list[j];
	  y=list[j+1];
	  if(x->f > y->f)
	    {
	      list[j]=y;
	      list[j+1]=x;
	    }
	}
    }
  //printf("done sorting list\n");
}
node * create_node(char ch, int freq)
{
  node *new;
  new=(node *)malloc(sizeof(node));
  new->data=ch;
  new->f=freq;
  new->left=NULL;
  new->right=NULL;
  new->p=NULL;
}

void sort(char a[],int b[],int u)
{
  int i,j,temp;
  char ch;
  for(i=0;i<u;i++)
    {
      for(j=0;j<u-1;j++)
	{
	  if(b[j]>b[j+1])
	    {
	      temp=b[j+1];
	      ch=a[j+1];
	      b[j+1]=b[j];
	      a[j+1]=a[j];
	      b[j]=temp;
	      a[j]=ch;
	    }
	}
    }
}

