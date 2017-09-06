/*Rutuja Jadhav
14BCE0002
Sub: Data Structures and alogrithms (CSE220)
Slot: D2
Submitted to: Prof. Prabhakaran */


#include<iostream>
#include<conio.h>
#include <windows.h>
#include<process.h>
#include<ctype.h>
#include<string.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoxy(int x, int y) 
{ 
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}

void dpgrid();

int X=8,Y=4,count=0,turn=0;

class node
{
   public:
	class node * left;
	class node * right;
	class node * up;
	class node * down;
	int c;
	int f;

  class node * pos[2];
  node *n[2][25];
  
  void init()                
   {
  	int p,i;
  	for(i=0;i<2;i++)
  	{
  	    for(p=0;p<25;p++)
	    {
		   n[i][p]->c=0;
		   n[i][p]->f=0;
	    }
    }
   }
   
   int invalid(string st)
   {
   	    int n=0;
		
		for(int i=0 ;i<st.length(); i++)
		{
			if(isdigit(st[i]))
			{
				n=n*10+(st[i]-'0');
			}
			else
				return -1;
		}
		   
		if(n>=1 && n<=25)
   	    	return n;
   	    else
   	    	return -1;
   }
  
  void initialize()
  {
	int p,q,i;
	for(i=0;i<2;i++)
	{
	    for(p=0;p<25;p++)    //alloting memory for 25 nodes
	    {
		    n[i][p]= new node;
	    }
	
	    for(p=0;p<=4;p++)     //Nullifying the outward-grid connections vertically
	    {
		    n[i][p]->up=NULL;
		    n[i][p+20]->down=NULL;
        }
	
	    for(p=0;p<=20;p=p+5)   //Nullifying the outward-grid connections horizontally
	    {
		    n[i][p]->left=NULL;
		    n[i][p+4]->right=NULL;
	    }
	
	    for(p=0;p<=20;p=p+5)     //Linking all the links horizontally
	    {
		    for(q=0;q<=3;q++)
		    {
			    n[i][p+q]->right=n[i][p+q+1];
			    n[i][p+q+1]->left=n[i][p+q];
		    }
	    }
	    for(p=0;p<=4;p++)     //Linking all the nodes vertically
	    {
		    for(q=0;q<=15;q=q+5)
		    {
			    n[i][p+q]->down=n[i][p+q+5];
			    n[i][p+q+5]->up=n[i][p+q];
		    }
	    }
	    pos[i]=n[i][0];
    }
  }
  
  
  void trav()       //Function to move through the grid
  {
  	string st;
	char ch;
	ch=getch();
	int n;
	while(count<25)
	{
	switch(ch)
	   {
		case 'w' :
		case 'W' : if(pos[turn%2]->up!=NULL)
		           {
		           	   pos[turn%2]=pos[turn%2]->up;
		           	   Y=Y-5;
		           	   gotoxy(X,Y);
		           }
		           break;
		           
		case 'a' :
	    case 'A' : if(pos[turn%2]->left!=NULL)
	               {
	               	   pos[turn%2]=pos[turn%2]->left;
	               	   X=X-9;
	               	   gotoxy(X,Y);
	               }
	               break;
	               
	    case 's' :
	    case 'S' : if(pos[turn%2]->down!=NULL)
	               {
	               	   pos[turn%2]=pos[turn%2]->down;
	               	   Y=Y+5;
	               	   gotoxy(X,Y);
	               }
	               break;
	               
	    case 'd' :
	    case 'D' : if(pos[turn%2]->right!=NULL)
	               {
	               	   pos[turn%2]=pos[turn%2]->right;
	               	   X=X+9;
	               	   gotoxy(X,Y);
	               }
	               break;
	               
	    case 'i' :                                                     //inserting numbers in the grid
	    case 'I' : cin>>st;
	    		   n=invalid(st);
	               if(n==-1)
	               {
	               	   gotoxy(5,30);
		               cout<<"Please enter a valid input";
		               getch();
		               gotoxy(5,30);
		               cout<<"                          ";
		               system("cls");
		               dpgrid();
		           }
		           else
		           {
		           	   pos[turn%2]->c=n;
		           }
	               gotoxy(X,Y);
	               count++;
	               break;
	               
	    /*case ' ' : play();
	               break;*/
	               
	    default :  gotoxy(5,30);
		           cout<<"Please enter a valid input";
				   getch();
		           gotoxy(5,30);
		           cout<<"                          ";
		           system("cls");
		           dpgrid();       
	   }
	  	
	  ch=getch();
    }
    turn++;
    count=0;
    X=8;
    Y=4;
    gotoxy(X,Y);
    system("cls");
    dpgrid();
  }

  
  
  void dpgrid()               //function to display the grid
  {
	int i,j,z=0;
	//system("cls");
	gotoxy(5,29);
	cout<<"Player "<<(turn%2)+1;

	for(i=5;i<=20;i=i+5)
	{
        gotoxy(5,i);
	    cout<<"__________________________________________";
    }
	for(i=12;i<40;i=i+9)
	{
	    for(j=1;j<=25;j++)
	    {
		    gotoxy(i,j);
		    cout<<"|";
	    }
	}
		for(j=4;j<29;j=j+5)
		{
			for(i=8;i<51;i=i+9)
			{
			   gotoxy(i,j);
			   if(n[turn%2][z]->c!=0)
			   cout<<n[turn%2][z]->c;   //Displaying all characters in the grid
		       if(n[turn%2][z]->f==1)
		       cout<<"*";
		       z++;
		    }
		}
	gotoxy(X,Y);
	trav();
  }
  
 /* void play()
  {
  	   trav();*/
}t;

main()
{
	cout<<" Rutuja wishes you a good luck for playing BINGO !";
	cout<<"\nKey bindings:\nW : UP\nS : DOWN\nA : LEFT\nD : RIGHT\nI : INSERT NUMBER\nPress any key to begin";
	getch();
	system("cls");
	t.initialize();
	t.init();
	t.dpgrid();
	getch();
}
