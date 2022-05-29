#include <iostream>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <fstream>

using namespace std;
int i, n;
ifstream fin;
ofstream fout;
fstream fio;
void disp();
class stock
{
	char name[20], pass[15];
	float pr;
	int quant;

public:
	void get();
	void get2();
	void show();
	int stchk(char nm[30]);
	void withd(int qty);
	void refil(int qty);
} st;
void stock::withd(int qty)
{
	if (quant >= qty)
	{
		quant -= qty;
		cout << "\n\nStock updated.\n";
		cout << "\n\nTotal price to be paid:" << pr * qty;
	}
	else
		cout << "\n\nInsufficient stock";
	getch();
}

void stock::refil(int qty)
{

	quant += qty;
	cout << "\n\nStock updated.";
	getch();
}
int stock::stchk(char nm[30])
{
	if (strcmp(nm, name) == 0)
		return 0;
	else
		return 1;
}
void stock::get()
{
	cin >> name >> pr >> quant;
	/*cout<<"\n\nEnter the password letter by letter\n";

	for(int z=0;z<5;z++)
	{

		cin>>pass[z];
		system("cls");
		cout<<"\n\nEnter the password letter by letter\n";
		for(i=1;i<=(z+1);i++)
		{
			cout<<"*";
		}
	}
	if(strcmp(pass,"hello")==0)
	{
	cout<<"\nCongrats!!Access Granted!!\n\n";
	cout<<"\nEnter the Name followed By the price and then by the quantity\n";
	cin>>name>>pr>>quant;
}
	else
	cout<<"Access Denied!!";*/
}
void stock::get2()
{
	cin >> name >> quant;
}

void stock::show()
{

	cout << "\n"
		 << name << "\t\t\t" << quant << "\t\t\t" << pr;
}
void addnew()
{
	//   cout<<"\n\n\nCongrats!!Access Granted!!\n\n";

	system("cls");
	// cout<<"\nEnter the Name followed By the price and then by the quantity\n";
	disp();
	getch();
	system("cls");

	cout << "\nEnter the No. of Products that you wish to add: ";
	cin >> n;

	if (n != 0)
	{

		int j, l, sum = 0;
		fout.open("local_database.csv", ios::binary | ios::app);
		for (i = 0; i < n; i++)

		{
			/*if(i==0)
			{
			system("cls");
		}*/
			cout << "\n\nInput the name, price and the quantity of item respectively\n\n";
			st.get();
			fout.write((char *)&st, sizeof(st));
			cout << "\n\nitem updated";
			cin.get();
		}
		cout << "\n\nStock Updated!!";

		fout.close();
		cin.get();
		system("cls");
		disp();
	}

	else
	{

		fout.close();
		cin.get();
		system("cls");
		cout << "\n\nNo items to be added";
	}
}

void withdraw()
{
	system("cls");
	char temp[100];
	int qty;
	int i = 0;
	long pos = 0;
	disp();
	cout << "\n\nEnter the product's name \n"
		 << endl;
	cin >> temp;
	cout << "\n\nEnter quantity: \n"
		 << endl;
	cin >> qty;
	fio.open("local_database.csv", ios::binary | ios::out | ios::in);
	while (fio)
	{
		pos = fio.tellp();
		fio.read((char *)&st, sizeof(st));
		if (st.stchk(temp) == 0)
		{

			st.withd(qty);
			fio.seekp(pos);
			fio.write((char *)&st, sizeof(st));
			i++;
			break;
		}
	}

	if (i != 1)
		cout << "\n\n!!Record not found!!";
	fio.close();
	cin.get();
	system("cls");
	disp();
	getch();
}
void disp()
{
	int i = 1;
	cout << "\n";
	cout << "\n\n\tTHE STOCK ITEMS ARE\t";
	cout << "\n\n\n";
	cout << "\n\nPARTICULARS\tSTOCK AVAILABLE\t\t\t PRICE";
	cout << "\n\n\n";
	fin.open("local_database.csv", ios::binary);
	while (!fin.eof())
	{
		fin.read((char *)&st, sizeof(st));
		if (!fin.eof())
		{
			if (fin.tellg() < 0)
			{
				i = 0;
				break;
			}
			st.show();
		}
	}
	if (i == 0)
	{
		cout << "\n\n\t\t\t!!Empty record room!!";
		getch();
	}
	fin.close();
}
void refill()
{
	system("cls");
	char temp[100];
	int qty;
	int i = 0;
	long pos = 0;
	disp();
	cout << "\n\nEnter the products name \n"
		 << endl;
	cin >> temp;
	cout << "\n\nEnter quantity: \n"
		 << endl;
	cin >> qty;
	fio.open("local_database.csv", ios::binary | ios::out | ios::in);
	while (fio)
	{
		pos = fio.tellp();
		fio.read((char *)&st, sizeof(st));
		if (st.stchk(temp) == 0)
		{

			st.refil(qty);
			fio.seekp(pos);
			fio.write((char *)&st, sizeof(st));
			i++;
			break;
		}
	}
	if (i != 1)
		cout << "\n\n!!Record not found!!";
	fio.close();
	system("cls");
	cin.get();
	disp();
	cin.get();
}
void remove()
{
	system("cls");
	int i = 0;
	char temp[30];
	cout << "\n\t\t\t\tDelete Record";
	cout << "\n\nEnter the name of the product:";
	cin >> temp;
	fout.open("temp.dat", ios::binary);
	fin.open("local_database.csv", ios::binary);
	while (!fin.eof())
	{
		fin.read((char *)&st, sizeof(st));
		if (!fin.eof())
			if (st.stchk(temp) == 0)
			{
				st.show();
				cout << "\n\n\t\tRecord deleted";
				i++;
			}
			else
				fout.write((char *)&st, sizeof(st));
	}
	if (i == 0)
		cout << "\n\n!!Record not found!!";
	fin.close();
	fout.close();
	remove("local_database.csv");
	rename("temp.dat", "local_database.csv");
}

#define Max_PName_Len 20
#define Max_Qty 50
#define Max_Price 100
int main()
{
	char pass[10], pass2[10];
	int i, j;
	char y_PName[Max_PName_Len], y_Qty[Max_Qty], y_Price[Max_Price];

	fstream my_file;
	my_file.open("local_database.csv", ios::in);
	if (!my_file)
	{
		cout << "No such file";
	}
	else
	{
		char ch;

		while (1)
		{
			my_file >> ch;
			if (my_file.eof())
				break;

			cout << ch;
		}
	}
	my_file.close();

	// fstream my_file_global;
	// my_file_global.open("https://dolatcapital-e299f-default-rtdb.firebaseio.com/", ios::in);
	// if (!my_file_global)
	// {
	// 	cout << "No such file";
	// }
	// else
	// {
	// 	char ch;

	// 	while (1)
	// 	{
	// 		my_file_global >> ch;
	// 		if (my_file_global.eof())
	// 			break;

	// 		cout << ch;
	// 	}
	// }
	// my_file_global.close();
	

	cout << "\n\n\t| WELCOME TO Dolat Capital inventory MANAGEMENT |";
	getch();
	system("cls");
	cout << "\n\t\t Dolat Capital inventory  MANAGEMENT SYSTEM\n";
	// cout<<"==";
	cout << "\n\n\t\t   1. Admin\n\n\t\t   2. IT Manager\n\n\t\t   3. IT Engineer \n\n\t\t   4. Product Owner";
	cout << "\n\n\n";
	cout << "\n\nEnter Your Choice:";
	cin >> j;
	if (j == 1)
	{

		system("cls");
		/*disp();

		cout<<"\n\n\n\nEnter the No. of Products that you wish to add: ";
		cin>>n;*/
		system("cls");
		cout << "\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";

		for (int z = 0; z < 12; z++)
		{
			pass[z] = getch();
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";
			for (i = 1; i <= (z + 1); i++)
			{
				cout << "*";
			}
		}
		if (strcmp(pass, "aaaaaaaaaaaa") != 0)
		{
			/*cout<<"\n\n\nCongrats!!Access Granted!!\n\n";
			getch();*/
			system("cls");
		adminmenu:
			system("cls");
			// cout<<"==================";
			cout << "\n\n\t\t\t    Admin\n1. Add new product\n2. Display stock\n3. update\n4. Remove an item\n5. Exit:";
			cout << "\n\n\n  END OF MENU ";
			cout << "\n\n Enter your Choice :\t";
			cin >> i;
			if (i == 1)
			{
				addnew();
				getch();
				goto adminmenu;
			}

			else if (i == 1)
			{
				system("cls");
				disp();
				getch();
				goto adminmenu;
			}
			else if (i == 2)
			{
				refill();
				goto adminmenu;
			}
			else if (i == 3)
			{
				refill();
				goto adminmenu;
			}
			else if (i == 4)
			{
				remove();
				getch();
				goto adminmenu;
			}
			else
			{
				system("cls");
				getch();
				exit(0);
			}
		}
		else
		{
			cout << "\n\n\nINPUT CORRECT PASSWORD!!!\n\n";
			getch();
			getch();
			getch();
			getch();
			getch();
			getch();
			exit(0);
		}
	}
	// Here IT Manager
	if (j == 2)
	{
	managermenu:
		system("cls");
		// cout<<"***********************************";
		cout << "\n\n\t\t\t IT Manager\n1. Requests\n2. Display stock\n3. Exit:";
		cout << "\n\n\n  END OF MENU";
		cout << "\n\n Enter your Choice :\t";
		cin >> i;

		if (i == 1)
		{
			withdraw();
			getch();
			goto managermenu;
		}
		else if (i == 2)
		{
			system("cls");
			disp();
			getch();
			goto managermenu;
		}

		else
		{
			system("cls");
			getch();
			exit(0);
		}
	}

	// IT Engineer
	if (j == 3)
	{
	Engmenu:
		system("cls");
		// cout<<"***********************************";
		cout << "\n\n\t\t\t IT Engineer\n1. Purchase\n2. Display stock\n3. Exit:";
		cout << "\n\n\n  END OF MENU";
		cout << "\n\n Enter your Choice :\t";
		cin >> i;

		if (i == 1)
		{
			withdraw();
			getch();
			goto Engmenu;
		}
		else if (i == 2)
		{
			system("cls");
			disp();
			getch();
			goto Engmenu;
		}

		else
		{
			system("cls");
			getch();
			exit(0);
		}
	}
	if (j == 4)

	{
		system("cls");
		cout << "\n\n\n\n\t\tPlease enter the password: ";

		for (int z = 0; z < 12; z++)
		{
			pass2[z] = getch();
			system("cls");
			cout << "\n\n\n\n\t\t\t\tPlease enter the password : ";
			for (i = 1; i <= (z + 1); i++)
			{
				cout << "*";
			}
		}
		if (strcmp(pass2, "aaaaaaaaaaaa") != 0)
		{
		productownermenu:
			system("cls");
			// cout<<"";
			cout << "\n\n\t\t\t Product Owner\n1. Display stock\n2. Refill\n3. Exit";
			cout << "\n\n\n  END OF MENU";
			cout << "\n\n Enter your Choice :\t";
			cin >> i;
			if (i == 1)
			{
				system("cls");
				disp();
				getch();
				goto productownermenu;
			}
			else if (i == 2)
			{
				refill();
				goto productownermenu;
			}
			else
			{
				system("cls");
				cout << "\n\n\n\t\t\tThank You!!";
				getch();
				exit(0);
			}
		}
		else
		{
			cout << "\n\nSorry!! Please Provide Valid Password..\n\n";
			getch();
			getch();
			getch();
			getch();
			getch();

			exit(0);
		}
	}

	getch();
}