#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip.h>



void f1(int , int);
void f2(int , int);
void f3(int , int);
void f4(int , int);
void f5(int , int);
void changepass(char *);
void showleaderboard();
void starting();
void sort();
void cont(int x);
void menu1();
void menu2();
void intro();
void box1();
int circh1();
void border();
void game1();
void game2();
void end();

void logborder()
{
	int a=20,b=10,c=60,d=16;
	for(int i=a+1;i<=c-1;i++)
	{
		gotoxy(i,b);
		cout<<"Í";
		gotoxy(i,d);
		cout<<"Í";
	}
	for( i=b+1;i<=d-1;i++)
	{
		gotoxy(c,i);
		cout<<"º";
		gotoxy(a,i);
		cout<<"º";
	}
	gotoxy(a,b);
	cout<<"É";
	gotoxy(c,b);
	cout<<"»";
	gotoxy(c,d);
	cout<<"¼";
	gotoxy(a,d);
	cout<<"È";
}
void border1()
{
	cleardevice();
	rectangle(10,10,630,470);
	rectangle(15,15,625,465);
	setcolor(RED);
}
void border2()
{
	int a=1,b=1,c=80,d=24;
	for(int i=a+1;i<=c-1;i++)
	{
		gotoxy(i,b);
		cout<<"Í";
		gotoxy(i,d);
		cout<<"Í";
	}
	for( i=b+1;i<=d-1;i++)
	{
		gotoxy(c,i);
		cout<<"º";
		gotoxy(a,i);
		cout<<"º";
	}
	gotoxy(a,b);
	cout<<"É";
	gotoxy(c,b);
	cout<<"»";
	gotoxy(c,d);
	cout<<"¼";
	gotoxy(a,d);
	cout<<"È";
}
class user
{
	char name[50];
	long long int phno;
	char add[100];
	char login[30];
	char passw[30];
	int points;
	public:
	void newuserentry();
	void existinguserentry();
	void updateinfo();
	void pointsupdate();
	void getpass(int);
	void updatepoints(int p);
	void show()
	{
		cout<<"\nName         : ";
		puts(name);
		cout<<"Phone number : ";
		cout<<phno;
		cout<<"\nAddress      : ";
		puts(add);
		cout<<"Login id     : ";
		cout<<login;
		cout<<"\nPoints       : ";
		cout<<points;

	}

	char* checkloginid()
	{
		return login;
	}
	char* checkpassword()
	{
		return passw;
	}
	char* retname()
	{
		return name;
	}
	int retpoints()
	{
		return points;
	}
	user()
	{
		points=0;
	}

}u1;
void modify1(char* login)
{

	fstream fin("gaming.dat",ios::binary|ios::in|ios::out|ios::app);
	user ui;
	while (fin.read( (char*)&ui , sizeof(ui) ) )
	{
		if ( !strcmp( ui.checkloginid() , login ) )
		{
			ui.updatepoints(100);
			fin.seekg( fin.tellg() -1*(sizeof(ui) ) );
			fin.write( (char*)&ui , sizeof(ui) );
		}
	}
	fin.close();
	sort();
}
int allowed(char* id)
{
	ifstream fin("gaming.dat",ios::binary);
	user u;
	while( fin.read( (char*)&u , sizeof(u) ) )
	{
		if ( !strcmp(u.checkloginid(),id)  )
			return 0;
	}
	return 1;
}
void user::updatepoints(int p)
{
	points+=p;
}
void user::getpass(int k)
{
	reenterpass :
	gotoxy(5,k);
	cout<<"Enter your password : ";
	char pw1[30];
	for (int i=0 ; i<30 ; i++)
	{
		passw[i]=getch();
		if(passw[i]=='\r')
			break;
		else if(passw[i]=='\b')
		{
		 //	clrscr();
			gotoxy(4,k);
			cout<<"                                           ";
			gotoxy(5,k);
			cout<<"Enter your password : ";
			for(int j=1;j<i-1;j++)
				cout<<"*";
			//if(i>=1)
				i-=2;
		}
		else
			cout<<'*';
	}
	passw[i]='\0';
	gotoxy(5,++k);
	cout<<"Reenter your password : ";
	for (i=0 ; i<30 ; i++)
	{
		pw1[i]=getch();
		if( pw1[i]=='\r' )
			break;
		else if ( pw1[i]=='\b' )
		{
		   //	clrscr();
			gotoxy(4,++k);
			cout<<"                                           ";
			gotoxy(4,k);
			cout<<"Reenter your password ";
			for(int j=0;j<i-1;j++)
				cout<<"*";
		      //	if(i>=1)
				i-=2;
		}
		else
			cout<<'*';
	}
	pw1[i]='\0';
	if( strcmp(passw,pw1) )
	{
		gotoxy(5,++k);
		cout<<"\npassword mismatch please enter it again ";
		k++;
		goto reenterpass;
	}
	else
	{       gotoxy(5,++k);
		cout<<"SUCCESFULLY DONE";
		getch();
	}

}
void write( user u)
{
	getch();
	ofstream fout("gaming.dat",ios::binary|ios::app);
	fout.write( (char*)&u , sizeof(u) );
	fout.close();
}

void sort()
{
	fstream fin("gaming.dat",ios::binary|ios::in|ios::out|ios::app);

	user s1,s2,temp;

	fin.seekg(0, ios::end);
	int size= fin.tellg()/sizeof(s1),i,j;

	fin.seekg(0);

	for( i=0 ; i<size ; i++ )
	{
		fin.seekg(0);
		for( j=0 ; j<size-i-1 ; j++ )
		{
			fin.seekg( j*sizeof(s1) );
			fin.read( (char*)&s1 , sizeof(s1) );
			fin.read( (char*)&s2 , sizeof(s2) );

			if ( s1.retpoints() < s2.retpoints() )
			{
				temp=s1;
				s1=s2;
				s2=temp;
			}

			fin.seekg( j*sizeof(s1) );
			fin.write( (char*)&s1 , sizeof(s1) );
			fin.write( (char*)&s2 , sizeof(s2) );
		}
	}
	fin.close();
}


void modify(char* login)
{

	fstream fin("gaming.dat",ios::binary|ios::in|ios::out|ios::app);
	user ui;
	while (fin.read( (char*)&ui , sizeof(ui) ) )
	{
		if ( !strcmp(ui.checkloginid(),login ) )
		{
			cout<<"\nEnter the new record : ";
			ui.updateinfo();
			fin.seekg( fin.tellg() -1*(sizeof(ui)) );
			fin.write( (char*)&ui , sizeof(ui) );
		}
	}
	fin.close();
}


void user::updateinfo()
{
	int ch;
	cout<<"\nEnter the name : ";
	gets(name);
	cout<<"Enter the phone number : ";
	cin>>phno;
	cout<<"Enter the address : ";
	gets(add);
	cout<<"Enter your new password : ";
	getpass(4);
}

void user::newuserentry()
{
	border2();
	char pss[30];
	gotoxy(5,6);
	cout<<"Enter the name : ";
	gets(name);
	gotoxy(5,7);
	cout<<"Enter the phone number : ";
	cin>>phno;
	gotoxy(5,8);
	cout<<"Enter the address : ";
	gets(add);
	int y=9;
	reenterid :
	gotoxy(5,y);
	cout<<"Enter your login id : ";
	gets(login);
	y++;
	if( allowed(login)==0)
	{
		gotoxy(5,y+1);
		cout<<"Already used id ";
		gotoxy(5,y+2);
		cout<<"Type a new one";
		y++;
		goto reenterid;
	}
	getpass(y);
}

void user::existinguserentry()
{
	clrscr();
	int ch;
	char ch1;
	do
	{
		cout<<"What do you want to do ?";
		cout<<"\n1 See your current statistics ";
		cout<<"\n2 Update your details ";
		cin>>ch;
		if( ch==1)
			show();
		if (ch==2)
			modify(login);
		cout<<"\nWant to do some more changes? (y/n) ";
			cin>>ch1;
	}while(ch1=='y' || ch1=='Y' );
}
int checkinfo(user &ui)
{
	logborder();
	char id[30],pw[30];
	int flag=0;
	gotoxy(23,12);
	cout<<"Enter your login id:";
	gets(id);
	gotoxy(23,13);
	cout<<"Enter your password:";
	for (int i=0 ; i<30 ; i++)
	{
		pw[i]=getch();
		if( pw[i]=='\r' )
			break;
		else if( pw[i]=='\b' )
		{
			 clrscr();
			logborder();
			gotoxy(23,12);
			cout<<"\nEnter your login id:"<<id;
			gotoxy(23,12);
			cout<<"Enter your password:";

			for(int j=1;j<i-1;j++)
				cout<<"*";
			if(i>=1)
				i-=2;
		}
		else
			cout<<'*';
	}
	pw[i]='\0';

	ifstream fin("gaming.dat",ios::binary);

	while (fin.read( (char*)&ui , sizeof(ui) ) )
	{
		if (!strcmp(ui.checkloginid(),id)&&!strcmp(ui.checkpassword(),pw))
		{
				u1=ui;
				flag=1;
				break;

		}
	}

	fin.close();
	return flag;
}
void box2()
{
	cleardevice();
	settextstyle(3,0,1);
	setcolor(BLUE);
	circle(110,250,55);
	circle(250,250,55);
	circle(390,250,55);
	circle(530,250,55);
	setcolor(CYAN);
	outtextxy(80,224,"Current");
	outtextxy(70,245,"Statistics");
	outtextxy(220,225,"Game 1");
	outtextxy(370,230,"Game 2");
	outtextxy(510,230,"Back");
	settextstyle(1,0,2);
	border();
}
int circh2()
{
	int ggraph=DETECT,gmode;
	initgraph(&ggraph,&gmode,"C:\\tc\\bgi");
	box2();
	int k=1;
	char ch;
	do
	{
		ch=getch();
		box2();
		if((int)ch==75)
		{
			k--;
			if(k==0)
				k++;
		}
		else if((int)ch==77)
		{
			k++;
			if(k==5)
				k--;
		}
		setcolor(GREEN);
		switch(k)
		{
			case 1:circle(110,250,60);
				break;
			case 2:circle(250,250,60);
				break;
			case 3:circle(390,250,60);
				break;
			case 4:circle(530,250,60);
				break;
		}
	}while((int)ch!=13);
	closegraph();
	return k;
}
void menu2()
{
	int k;
	char ch;
	cout<<"";
	k=circh2();
	cout<<"";
	if(k==1)
	{
		int ch1;
		cout<<"\nPress 1 for existing user ";
		cout<<"\nPress 2 for leader board ";
		cout<<"\nPress 3 to go back ";
			cin>>ch1;
		int flag;
		switch( ch1 )
		{
			case 1 : flag=checkinfo(u1);
				 if(flag)
				 u1.existinguserentry();
				 break;

			case 2 : showleaderboard();
				 break;

			case 3 : menu2();
				 break;
		}

		menu2();
	}
	else if(k==2)
	{
		game1();
	}
	else if(k==3)
	{
		game2();
	}
	else if(k==4)
	{
		menu1();
	}
	else
	{
		cout<<"Enter correct choice";
		menu2();
	}
}

void digclock()
{
	int ggraph=DETECT,gmode;
	initgraph(&ggraph,&gmode,"C:\\tc\\bgi");
	cleardevice();
	border();
	rectangle(200,180,400,320);
	rectangle(195,175,405,325);
	int hour,min,sec;
	struct dostime_t t;
	_dos_gettime(&t);
	hour=t.hour;
	min=t.minute;
	sec=t.second;
	while(!kbhit())
	{
		if(sec==59)
		{
			min+=1;
			sec=0;
		}
		if(min==59)
		{
			hour+=1;
			min=0;
		}
		if(hour==12)
			hour=0;
		delay(1000);
		sec++;
		gotoxy(30,16);
		cout<<"Current time is :";
		gotoxy(31,17);
		cout<<hour<< " : "<<min<<" : "<<sec<<"       ";
	}
	getch();
	menu1();
}
void showleaderboard()
{
	clrscr();

	cout<<"\t\t\t      ...LEADERBOARD... ";
	cout<<"\n\n\nDisplaying details of top 5 scorers \n\n\n";
	cout<<"RANK\tNAME\t\t\tPOINTS  "<<endl;
	ifstream fin("gaming.dat",ios::binary );
	user ui;
	int i=1;

	while( fin.read( (char*)&ui , sizeof(ui) )  )
	{
		cout<<i<<"\t"<<ui.retname()<<"\t\t\t"
		    <<ui.retpoints()<<endl;
		i++;
	}

	if ( i<=5 )
		for ( int j=i ; j<=5 ; j++ )
		{
			cout<<j<<"\t"<<"<UNOCCUPIED>"<<"\t\t0"<<endl;
		}
	getch();
}

void box1()
{
	cleardevice();
	settextstyle(3,0,1);
	setcolor(BLUE);
	circle(110,250,55);
	circle(250,250,55);
	circle(390,250,55);
	circle(530,250,55);
	setcolor(CYAN);
	outtextxy(95,224,"New");
	outtextxy(90,250,"User");
	outtextxy(220,225,"Existing");
	outtextxy(232,250,"User");
	outtextxy(370,230,"Digital");
	outtextxy(370,250,"Clock");
	outtextxy(515,235,"Exit");
	settextstyle(1,0,2);
	border();
}
void menu1()
{
	int k;
	int flag;
	char ch;
	k=circh1();
	int ggraph=DETECT,gmode;
	initgraph(&ggraph,&gmode,"C:\\tc\\bgi");
	if(k==1)
	{
		cleardevice();
		border2();
		u1.newuserentry();
		write(u1);
		closegraph();
		menu1();
		return;
	}
	else if(k==2)
	{
		closegraph();
		clrscr();
		logborder();
		flag=checkinfo(u1);
		if(flag==0)
		{
			gotoxy(20,17);
			cout<<"INVALID USERNAME OR PASSWORD";
			delay(2000);
			menu1();
		}else{
			menu2();
			cout<<"Reached at menu2";
		}
	}
	else if(k==3)
	{
		closegraph();
		digclock();
	}
	else if(k==4)
	{
		closegraph();
		end();
		exit(0);
	}
	closegraph();
}
int main()
{
	int ggraph=DETECT,gmode;
	initgraph(&ggraph,&gmode,"C:\\tc\\bgi");
	starting();
	getch();
	intro();
	getch();
	menu1();
	return 0;
}
void intro()
{
	cleardevice();
	setcolor(CYAN);
	settextstyle(3,0,1);
	border();
	setcolor(BLACK);
	outtextxy(240,50,"GAMING MANIA");
	setcolor(CYAN);
	outtextxy(260,50,"INTRODUCTION");
	outtextxy(30,120,"1.This program contains two games.");
	outtextxy(30,140,"        a)Deadly snake");
	outtextxy(30,160,"        b)Tic Tac Toe");
	outtextxy(30,180,"2.Deadly snake is single player and tic tac toe is multiplayer game");
	outtextxy(30,200,"3.Each time a player wins a game,player would win 100 points.");
	outtextxy(30,220,"4.With the help of points you can win exciting prices as follows:");
	outtextxy(30,240,"   POINTS		 REWARD");
	outtextxy(30,260,"   500		 PEN");
	outtextxy(30,280,"   1000		 Samsung galaxy S8");
	outtextxy(30,300,"   1500		 Activa 4g");
	outtextxy(30,320,"   2000		 BMW 320 D");
	outtextxy(30,340,"   3000		 Mercedez benz C-200");
	outtextxy(30,360,"5.You will be given choice to redeem your price at the time of ");
	outtextxy(30,380,"logging off your user");
	outtextxy(30,400,"6.In case you are unable to recieve your reward within 1 week");
	outtextxy(30,420,"you may contact DAV Public School,Srestha vihar,New delhi");
	getch();
}
int circh1()
{
	int gd = DETECT,gm;
	initgraph(&gd,&gm,"C:\\tc\\bgi");
	box1();
	int k=1;
	char ch;
	do
	{
		ch=getch();
		box1();
		if((int)ch==75)
		{
			k--;
			if(k==0)
				k++;
		}
		else if((int)ch==77)
		{
			k++;
			if(k==5)
				k--;
		}
		setcolor(GREEN);
		switch(k)
		{
			case 1:circle(110,250,60);
				break;
			case 2:circle(250,250,60);
				break;
			case 3:circle(390,250,60);
				break;
			case 4:circle(530,250,60);
				break;
		}
	}while((int)ch!=13);
	closegraph();
	return k;

}
void starting()
{
	  randomize();
	  int m,n;
	  setcolor(RED);
	  rectangle(10,10,630,470);
	  rectangle(15,15,625,465);
	  for(int i=0;i<6;i++)
	  {
		if(i==0)
		{
			m=300;
			n=200;
		}
		if(i==1)
		{
			m=100;
			n=100;
		}
		if(i==2)
		{
			m=500;
			n=300;
		}
		if(i==3)
		{
			m=500;
			n=100;
		}
		if(i==4)
		{
			m=100;
			n=300;
		}
		if(i==5)
		{
			m=300;
			n=200;
		}
		  setcolor(random(15));
		  f1(m,n);
		  f2(m,n);
		  delay(20);
		  f3(m,n);
		  delay(20);
		  f4(m,n);
		  delay(10);
		  f5(m,n);
		  delay(50);
		  setcolor(0);
		  f1(m,n);
		  delay(10);
		  f2(m,n);
		  delay(10);
		  f3(m,n);
		  delay(10);
		  f4(m,n);
		  delay(10);
		  f5(m,n);
		  setcolor(0);
	 }
	setcolor(RED);
	rectangle(10,10,630,470);
	rectangle(15,15,625,465);
	settextstyle(8,0,8);
	setcolor(BLUE);
	outtextxy(180,50,"READY");
	outtextxy(260,120,"TO");
	outtextxy(210,190,"PLAY");
	settextstyle(2,0,6);
	setcolor(WHITE);
	outtextxy(180,318,"Loading..");
	rectangle(308,322,408,337);
	n=0;
	for(int i1=0,j=0;i1<50,j<50;i1++,j+=2)
	{
		settextstyle(8,0,8);
		setcolor(i1);
		outtextxy(180,50,"READY");
		delay(45);
		setcolor(i1+2);
		outtextxy(260,120,"TO");
		delay(45);
		setcolor(i1+4);
		outtextxy(210,190,"PLAY");
		delay(45);
		setcolor(WHITE);
		setfillstyle(8,RED);
		rectangle(310,324,310+2*j,335);
		floodfill(312,322,WHITE);
		delay(1);
		gotoxy(34,21);
		cout<<n*2<<"%";
		n+=2;
		if(n==20)
		n+=2.5;
	}
	settextstyle(3,0,2);
	setcolor(RED);
	outtextxy(132,350,"PRESS ANY KEY TO CONTINUE.");
	delay(300);
}
void game2()
{
	closegraph();
	closegraph();
	clrscr();
	int secuser;
	user u2;
	logborder();
	gotoxy(20,9);
	cout<<"Login second user(may be same as first user)";
	secuser=checkinfo(u2);
	if(secuser==0)
	{
	       //	setcolor(RED);
		gotoxy(20,16);
		cout<<"INVALID USERNAME OR PASSWORD";
		delay(2000);
		game2();

	}
	clrscr();
  //	setcolor(WHITE);
	char tic_tac[3][3],check, pl[]={'0','X'},n;
	int x=30,y=7,a,b,j=0,counter,p=0,c,mc=0,p1=0,m,i=0,flag=0;
	border2();
	b :
	gotoxy(2,2);
	cout<<"Enter the symbol player 1 wishes(either 'X' or '0')";
	cin>>pl[0];
	if(pl[0]!='X'&&pl[0]!='0')
		goto b;
	if(pl[0]==pl[1])
		pl[1]='0';
	clrscr();
	border2();
	for( i=6;i<=16;i++)
	{
		gotoxy(35,i);
		cout<<'º';
		gotoxy(45,i);
		cout<<'º';
	}
	gotoxy(35,5);
	cout<<'Ë';
	gotoxy(45,5);
	cout<<'Ë';
	gotoxy(35,17);
	cout<<'Ê';
	gotoxy(45,17);
	cout<<'Ê';
	for( i=26;i<=54;i++)
	{
		gotoxy(i,9);
		cout<<'Í';
		gotoxy(i,13);
		cout<<'Í';
	}
	gotoxy(45,9);
	cout<<'Î';
	gotoxy(45,13);
	cout<<'Î';
	gotoxy(35,9);
	cout<<'Î';
	gotoxy(35,13);
	cout<<'Î';
	gotoxy(25,9);
	cout<<'Ì';
	gotoxy(25,13);
	cout<<'Ì';
	gotoxy(55,9);
	cout<<'¹';
	gotoxy(55,13);
	cout<<'¹';
	gotoxy(1,1);
	cout<<"\n Welcome to the TIC TAC TOE GAME CENTER ";
	i=0;
	while(x)
	{
		gotoxy(28,19);
		cout<<"Player "<<p+1<<"(Enter only "<<pl[p]<<" )";
		gotoxy(x,y);
		if(p1==9)
		{
			gotoxy(25,31);
			cout<<" Match Draw ";
			cont(0);
		}
		check=getch();
		if(check=='w')
		{
			if(y==7)
			{
				y=15;
				i=2;
			}
			else
			{
				y-=4;
				i--;
			}
			for(a=0;a<2;a++)
				if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
				{
					if(y==7)
					{
						y=15;
						i=2;
					}
					else
					{
						y-=4;
						i--;
					}
				}
			gotoxy(x,y);
			continue;
		}
		else if(check=='s')
		{
			if(y==15)
			{
				y=7;
				i=0;
			}
			else
			{
				y+=4;
				i++;
			}
			for(a=0;a<2;a++)
				if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
				{
					if(y==15)
					{
						y=7;
						i=0;
					}
					else
					{
						y+=4;
						i++;
					}
				}
			gotoxy(x,y);
			continue;
		}
		if(check=='a')
		{
			if(x==30)
			{
				x=50;
				j=2;
			}
			else
			{
				x-=10;
				j--;
			}
			for(a=0;a<2;a++)
				if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
				{
					if(x==30)
					{
						x=50;
						j=2;
					}
					else
					{
						x-=10;
						j--;
					}
				}
			gotoxy(x,y);
			continue;
		}
		else if(check=='q'&&(x-10)>=25&&(y-4)>=7)
		{
			x-=10;
			y-=4;
			i--;
			j--;
			if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
			{
				if((x-10)>=25&&(y-4)>=7&&(tic_tac[i-1][j-1]!='X'||tic_tac[i-1][j-1]!='0'))
				{
					x-=10;
					y-=4;
					i--;
					j--;
				}
				else
				{
					x+=10;
					y+=4;
					i++;
					j++;
				}
			}
		}
		else if(check=='e'&&(x+10)<=55&&(y-4)>=7)
		{
			x+=10;
			y-=4;
			i--;
			j++;
			if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
			{
				   if((x-10)<=55&&(y-4)>=7&&(tic_tac[i+1][j-1]!='X'||tic_tac[i-1][j-1]!='0'))
				   {
					   x+=10;
					y-=4;
					i--;
					j++;
				   }
				   else
				   {
					x-=10;
					y+=4;
					i++;
					j--;
				   }
			}
		}
		else if(check=='c'&&(x+10)<=50&&(y+4)<=17)
		{
			x+=10;
			y+=4;
			i++;
			j++;
			if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
			{
				if((x+10)<=50&&(y+4)<=17&&(tic_tac[i+1][j+1]=='X'||tic_tac[i+1][j+1]=='0'))
				{
					x+=10;
					y+=4;
					i++;
					j++;
				}
				else
				{
					x-=10;
					y-=4;
					i--;
					j--;
				}
			}
		}
		else if(check=='z'&&(x-10)>25&&(y+4)<18)
		{
			x-=10;
			y+=4;
			i++;
			j--;
			if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
			{
				if((x-10)>25&&(y+4)<18&&(tic_tac[i-1][j+1]!='X'||tic_tac[i-1][j+1]!='0'))
				{
					x-=10;
					y+=4;
					i++;
					j--;
				}
				else
				{
					x+=10;
					y-=4;
					i--;
					j++;
				}
			}
		}
		else if (check=='d')
		{
			if(x==50)
			{
				x=30;
				j=0;
			}
			else
			{
				x+=10;
				j++;
			}
			for(a=0;a<2;a++)
				if(tic_tac[i][j]=='X'||tic_tac[i][j]=='0')
				{
					if(x==50)
					{
						x=30;
						j=0;
					}
					else
					{
						x+=10;
						j++;
					}
				}
			gotoxy(x,y);
			continue;
		}
		else if(check>='A'&&check<='Z'&&check!='X'&&check!='0'&&tic_tac[i][j]!='0'&&tic_tac[i][j]!='X')
			cout<<" ";
		else if(pl[p]==check)
		{
			if(tic_tac[i][j]!=pl[!p])
			{
				cout<<check;
				tic_tac[i][j]=check;
				p1++;
			}
			if(p1>3)
			{
				for(a=0;a<3;a++)
				{
					counter=0;
					check=tic_tac[a][0];
					for(b=0;b<=2;b++)
					{
						if(check==tic_tac[a][b])
							counter++;
						else
						{
							m=b;
						}
					}
					if(counter==3)
					{
						gotoxy(10,17);
						textcolor(GREEN);
						cout<<"\n  Congratulations!!! Player "<<p+1<<" wins ";
						if(p+1==1)
						{
							modify1(u1.checkloginid());
						}
						if(p+1==2)
						{
							modify1(u2.checkloginid());
						}
						textcolor(WHITE);
						cont(1);
					}
					else if((counter==2&&(pl[!p]==tic_tac[a][1]||pl[!p]==tic_tac[a][2]))||tic_tac[a][1]==tic_tac[a][2])
						if(tic_tac[a][m]!=pl[p])
						{
							gotoxy(25,21);
							cout<<"Player   "<<pl[!p]<<" would win if he/she plays nicely             ";
						}
					if(counter==2&&(tic_tac[a][m]!='0'||tic_tac[a][m]!='X'))
					{
						n=tic_tac[a][!m];
						flag++;
					}
					counter=0;
					check=tic_tac[0][a];
					for(b=0;b<3;b++)
						if(check==tic_tac[b][a])
							counter++;
						else
						{
							m=b;
						}
					if(counter==3)
					{
						gotoxy(10,17);
						textcolor(GREEN);
						cout<<"\n  Congratulations!!! Player "<<p+1<<" wins ";
						if(p+1==1)
						{
							modify1(u1.checkloginid());
						}
						if(p+1==2)
						{
							modify1(u2.checkloginid());
						}
						textcolor(WHITE);
						cont(1);
					}
					else if((counter==2&&(pl[!p]==tic_tac[1][a]||pl[!p]==tic_tac[2][a]))||tic_tac[1][a]==tic_tac[2][a])
						if(tic_tac[a][m]!=pl[p])
						{
							gotoxy(25,21);
							cout<<"Player   "<<pl[!p]<<" would win if he/she plays nicely            ";
						}
					if(counter==2&&(tic_tac[a][m]!='0'||tic_tac[a][m]!='X')&&n==tic_tac[a][!m])
					{
						flag++;
						n=tic_tac[!m][!m];
					}
					if(flag>=2)
					{
						gotoxy(25,21);
						cout<<"Player "<<n<<" will win if he plays nicely           ";
						mc++;
					}
				}
				check=tic_tac[0][0];
				counter=0;
				for(a=0;a<3;a++)
				{
					for(b=0;b<3;b++)
						if(a==b&&check==tic_tac[b][a])
							counter++;
						else
						{
							m=b;
						}
				}
				if(counter==3)
				{
					gotoxy(10,17);
					textcolor(GREEN);
					cout<<"\n  Congratulations!!! Player "<<p+1<<" wins ";
					if(p+1==1)
					{
						modify1(u1.checkloginid());
					}
					if(p+1==2)
					{
						modify1(u1.checkloginid());
					}
					textcolor(WHITE);
					cont(1);
				}
				else if(counter==2&&(tic_tac[m][m]!='0'||tic_tac[m][m]!='X')&&tic_tac[!m][!m]==pl[!p])
				{
					gotoxy(25,21);
					cout<<" Player "<<!p+1<<" will win if he/she plays nicely                 ";
				}
				if(counter==2&&(tic_tac[m][m]!='0'||tic_tac[m][m]!='X')&&n==tic_tac[a][!m])
				{
					flag++;
					n=tic_tac[!m][!m];
				}
				if(mc==0&&flag>=2)
				{
					gotoxy(25,21);
					cout<<"Player "<<n<<" will win if he plays nicely            ";
					mc++;
				}
				check=tic_tac[0][2];
				counter=0;
				for(a=0;a<3;a++)
				{
					for(b=0;b<3;b++)
						if(a+b==2&&check==tic_tac[a][b])
							counter++;
						else
						{
							m=b;
							c=a;
						}
				}
				if(counter==3)
				{
					gotoxy(10,17);
					textcolor(GREEN);
					cout<<"\n  Congratulations!!! Player "<<p+1<<" wins ";
					textcolor(WHITE);
					cont(1);
				}
				else if(counter==2&&(tic_tac[m][m]!='0'||tic_tac[m][m]!='X')&&tic_tac[!m][!m]==pl[!p])
				{
					gotoxy(25,21);
					cout<<" Player "<<!p+1<<" will win if he/she plays nicely                ";
				}
				if(counter==2&&(tic_tac[c][m]!='0'||tic_tac[c][m]!='X')&&n==tic_tac[c][!m])
				{
					flag++;
					n=tic_tac[!m][!m];
				}
				if(mc==0&&flag>=2)
				{
					gotoxy(25,21);
					cout<<"Player "<<n<<" will win if he plays nicely                     ";
				}
			}
			p=!p;
		}
	}
}
void border()
{
	setcolor(RED);
	rectangle(10,10,630,470);
	rectangle(15,15,625,465);
	setcolor(CYAN);
	line(180,38,440,38);
	line(180,78,440,78);
	line(180,38,170,58);
	line(170,58,180,78);
	line(440,38,450,58);
	line(450,58,440,78);
	setcolor(BLUE);
	outtextxy(240,50,"GAMING MANIA");
}
void cont(int x=0)
{
	char ch1;
	if(x)
	{
		getch();
		menu2();
	}
	else
	{      getch();
		menu2();
	}
}

void end()
{
	randomize();
	clrscr();
	float k=0,j=10;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\tc\\bgi");
	for(int i=630;i>200;i=i-2)
	{
		j++;
		cleardevice();
		setcolor(RED);
		rectangle(10,10,630,470);
		rectangle(15,15,625,465);
		k+=0.3;
		setcolor(GREEN);
		circle(i,j,k);
		delay(10);
	}
	for(;i<300;i++)
	{
		cleardevice();
		setcolor(RED);
		rectangle(10,10,630,470);
		rectangle(15,15,625,465);
		k+=0.3;
		setcolor(CYAN);
		circle(i,j,k);
		delay(10);
	}
	for(;k<140;k=k+0.3)
	{
		cleardevice();
		setcolor(RED);
		rectangle(10,10,630,470);
		rectangle(15,15,625,465);
		setcolor(BLUE);
		circle(i,j,k);
		delay(10);
	}
	settextstyle(10,0,2);
	settextjustify(1,1);
	setcolor(GREEN);
	outtextxy(307,165,"PROJECT");
	setcolor(GREEN);
	outtextxy(315,210,"BY");
	settextstyle(10,0,2);
	settextjustify(1,1);
	setcolor(LIGHTGREEN);
	delay(250);
	outtextxy(300,265,"VIPUL");
	settextstyle(3,0,1);
	setcolor(YELLOW);
	outtextxy(510,450,"Press enter to continue");
	getch();
	closegraph();
}
void game1()
{
	randomize();
	cout<<"Reached";
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C:\\tc\\bgi");
	int points=0;
	clrscr();
	circle(200,180,5);
	int i=200,j=250,k=0,l=0;
	char ch=72;
	int m;
	rectangle(10,10,625,465);
	setcolor(RED);
	o:
	k=random(625);
	l=random(465);
	if(k<10||l<10)
		goto o;
	while(i>10 &&i<625 && j>10 && j<465)
	{
		setcolor(YELLOW);
		clrscr();
		border1();
		line(k,l,k+2,l);
		line(k+2,l,k+2,l+2);
		line(k+2,l+2,k,l+2);
		line(k,l+2,k,l);
		setcolor(WHITE);
		circle(i,j,5);
		delay(40-points*5);
		if(kbhit())
		{
			ch=getch();
		}
		if(ch==72)
			j--;
		if(ch==80)
			j++;
		if(ch==75)
			i--;
		if(ch==77)
			i++;
		if((i==k+1&&j==l+1) || (i==k+2&&j==l) || (i==k+2&&j==l+1) || (i==k+2&&j==l+2) || (i==k+1&&j==l+2) || (i==k&&j==l+2) || (i==k&&j==l+1) || (i==k&&j==l) || (i==k+1&&j==l) )
		{
			points++;
			goto o;
		}
	}
	textcolor(RED);
	setcolor(RED);
	gotoxy(30,15);
	cout<<"GAME OVER";
	gotoxy(30,17);
	cout<<"Your Final Score is:";
	cout<<points*10;
	modify1(u1.checkloginid());
	delay(2000);
	getch();
	menu2();
}
void f1(int x,int y)
{
	 line(x-5,y,x-10,y);
	  line(x-4,y-3,x-7,y-7);
	  line(x,y-5,x,y-10);
	  line(x+3,y-4,x+7,y-7);
	  line(x+5,y,x+10,y);
	  line(x+4,y+3,x+8,y+6);
	  line(x,y+5,x,y+10);
	  line(x-4,y+3,x-7,y+7);
	  line(x-5,y-2,x-9,y-5);
	  line(x-4,y-9,x-2,y-5);
	  line(x+2,y-5,x+4,y-9);
	  line(x+4,y-3,x+9,y-4);
	  line(x+5,y+2,x+10,y+3);
	  line(x+2,y+5,x+3,y+9);
	  line(x-2,y+5,x-5,y+9);
	  line(x-5,y+2,x-9,y+4);
}
void f2(int x,int y)
{
	  line(x+15,y,x+25,y);
	  line(x+6,y-14,x+12,y-22);
	  line(x+11,y-10,x+19,y-16);
	  line(x+14,y-6,x+23,y-9);
	  line(x,y+15,x,y+25);
	  line(x-15,y,x-25,y);
	  line(x,y-15,x,y-25);
	  line(x-14,y-6,x-22,y-11);
	  line(x-11,y-10,x-18,y-17);
	  line(x-7,y-15,x-12,y-22);
	  line(x+13,y+7,x+22,y+11);
	  line(x+10,y+11,x+18,y+17);
	  line(x+7,y+13,x+12,y+22);
	  line(x-13,y+7,x-22,y+11);
	  line(x-10,y+11,x-17,y+18);
	  line(x-7,y+13,x-11,y+22);
}
void f3(int x,int y)
{
	  line(x+30,y,x+40,y);
	  line(x-30,y,x-40,y);
	  line(x,y+30,x,y+40);
	  line(x,y-30,x,y-40);
	  line(x+9,y-29,x+14,y-37);
	  line(x+17,y-25,x+24,y-32);
	  line(x+22,y-20,x+30,y-26);
	  line(x+26,y-15,x+35,y-19);
	  line(x+29,y-9,x+38,y-12);
	  line(x-29,y+8,x-39,y+10);
	  line(x-25,y+16,x-33,y+22);
	  line(x-20,y+22,x-27,y+30);
	  line(x-15,y+26,x-19,y+35);
	  line(x-9,y+29,x-11,y+38);
	  line(x-7,y-29,x-13,y-38);
	  line(x-14,y-27,x-21,y-34);
	  line(x-19,y-23,x-27,y-30);
	  line(x-25,y-17,x-34,y-21);
	  line(x-28,y-10,x-38,y-12);
	  line(x+29,y+9,x+38,y+13);
	  line(x+26,y+15,x+35,y+20);
	  line(x+22,y+20,x+30,y+27);
	  line(x+14,y+27,x+21,y+34);
	  line(x+8,y+29,x+10,y+39);
}
void f4(int x,int y)
{
	  line(x+45,y,x+55,y);
	  line(x-45,y,x-55,y);
	  line(x,y+45,x,y+55);
	  line(x,y-45,x,y-55);
	  line(x+10,y-44,x+15,y-53);
	  line(x+20,y-40,x+27,y-48);
	  line(x+28,y-35,x+36,y-42);
	  line(x+34,y-29,x+43,y-34);
	  line(x+39,y-23,x+48,y-27);
	  line(x+42,y-16,x+51,y-20);
	  line(x+44,y-9,x+54,y-11);
	  line(x-44,y+9,x-53,y+12);
	  line(x-41,y+18,x-49,y+25);
	  line(x-35,y+28,x-43,y+34);
	  line(x-27,y+36,x-33,y+44);
	  line(x-20,y+40,x-24,y+49);
	  line(x-11,y+44,x-15,y+53);
	  line(x-6,y+45,x-8,y+54);
	  line(x+44,y+7,x+54,y+10);
	  line(x+43,y+14,x+52,y+19);
	  line(x+39,y+22,x+46,y+27);
	  line(x+31,y+33,x+38,y+40);
	  line(x+27,y+36,x+33,y+44);
	  line(x+10,y+44,x+13,y+53);
	  line(x+34,y+29,x+42,y+36);
	  line(x+19,y+41,x+23,y+50);
	  line(x-7,y-44,x-10,y-54);
	  line(x-15,y-42,x-18,y-52);
	  line(x-23,y-39,x-28,y-47);
	  line(x-33,y-31,x-41,y-37);
	  line(x-40,y-20,x-50,y-23);
	  line(x-44,y-9,x-54,y-12);
}
void f5(int x,int y)
{
	  line(x+60,y,x+75,y);
	  line(x-60,y,x-75,y);
	  line(x,y+60,x,y+75);
	  line(x,y-60,x,y-75);
	  line(x-7,y-60,x-10,y-74);
	  line(x-16,y-58,x-22,y-71);
	  line(x-26,y-54,x-31,y-68);
	  line(x-36,y-48,x-45,y-60);
	  line(x-46,y-39,x-57,y-49);
	  line(x-54,y-27,x-67,y-34);
	  line(x-58,y-18,x-71,y-23);
	  line(x-59,y-9,x-74,y-11);
	  line(x-59,y+8,x-74,y+10);
	  line(x-58,y+16,x-72,y+19);
	  line(x-55,y+24,x-69,y+31);
	  line(x-49,y+34,x-62,y+42);
	  line(x-41,y+44,x-51,y+55);
	  line(x-28,y+53,x-36,y+66);
	  line(x-20,y+57,x-27,y+70);
	  line(x-12,y+59,x-15,y+73);
	  line(x-35,y+49,x-44,y+61);
	  line(x+59,y+11,x+74,y+14);
	  line(x+57,y+20,x+71,y+25);
	  line(x+54,y+27,x+66,y+35);
	  line(x+47,y+37,x+58,y+47);
	  line(x+39,y+46,x+50,y+56);
	  line(x+28,y+53,x+36,y+66);
	  line(x+19,y+57,x+26,y+70);
	  line(x+9,y+59,x+10,y+74);
	  line(x+10,y-59,x+12,y-74);
	  line(x+20,y-57,x+27,y-70);
	  line(x+30,y-52,x+41,y-63);
	  line(x+37,y-47,x+47,y-58);
	  line(x+45,y-40,x+58,y-48);
	  line(x+51,y-32,x+65,y-38);
	  line(x+56,y-22,x+71,y-25);
	  line(x+59,y-11,x+74,y-14);
}
