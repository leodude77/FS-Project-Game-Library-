#include<dir.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<iomanip.h>
#include<graphics.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int count = 0;
char knodes[100][100];

class videog;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IOBUFFER
{
public:
	void initialize()
	{
		Nextbyte = 0; Buffersize = 75; Buffer[0] = 0;
	}

	virtual int Read(istream&, int) = 0;
	virtual int Write(ostream&) = 0;
	virtual int pack(videog&, fstream&) = 0;
	virtual int unpack(videog&, fstream&) = 0;

protected:
	char Buffer[100];
	int Buffersize;
	int Nextbyte;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FixedLengthBuffer :public IOBUFFER
{
public:
	int Read(istream&, int);
	int Write(ostream&);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VariableFieldBuffer :public FixedLengthBuffer
{
public:
	int pack(videog&, fstream&);
	int unpack(videog&, fstream&);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class videog
{
public:
	char id[30], title[30], dev[30], pub[30], rel_date[30], genre[30];
	videog()
	{
		id[0] = 0;
		title[0] = 0;
		dev[0] = 0;
		pub[0] = 0;
		rel_date[0] = 0;
		genre[0] = 0;
	}
	void Input();
	void Modify();
	void Assign1(videog&);
	void Display();
	int  Binary(char*);
	void Indexprimary();
	void del();
	void KeySort();
	void Indexdisplay(int);
	void Invertprimary();
	void Invertsecondary();
	void Invertsecondarysort();
	void CheckDup();
	void displayInvert();
	int  InvertSecondSearch(char*);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class fsearch
{
public:
	int Search(char*);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int videog::Binary(char* key)
{
	int mid = 0, k, ptr1, low, high, i = 0;
	low = 0;
	high = count - 1;
	char ntitle[20] = "", recaddr[10], * endptr;
	int l = strlen(key);
	while (1)
	{
		for (int j = 0; j < 15; j++)
			ntitle[j] = '\0';
		mid = (low + high) / 2;

		if (low > high)
			return -1;

		for (i = 0; knodes[mid][i] != '|'; i++)
			ntitle[i] = knodes[mid][i];
		i++;

		for (int n = 0; knodes[mid][i] != '|'; i++)
			recaddr[n++] = knodes[mid][i];

		int num = strtol(recaddr, &endptr, 10);
		ptr1 = strnicmp(ntitle, key, l);

		if (ptr1 > 0)
			high = mid - 1;
		else if (ptr1 < 0)
			low = mid + 1;
		else if (ptr1 == 0)
			return num;

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

videog s1, s2;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void videog::Modify()
{
	char key[20], Buff[100];
	int size = 0, found = 0, asize = 75, Next = 0;
	clrscr();
	cout << "\n\tENTER THE SEARCH KEY: ";
	cin >> key;
	VariableFieldBuffer b;
	fstream file("vlist.txt", ios::in | ios::out | ios::ate | ios::binary);
	file.seekg(0, ios::beg);
	while (b.unpack(*this, file))
	{
		if (strcmpi(id, key) == 0)
		{
			found = 1;
			break;
		}
		size = size + 75;
	}
	if (found == 1)
	{
		char choice[10];
		cout << "\n\n\t\t\t\tRecord is found ...." << endl << endl;
		cout << "\n\t\t\tDetails Of Record";
		cout << "\n\t\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\f\n\n";
		cout << "\n\t\t\tGame ID       :" << id << endl;
		cout << "\n\t\t\tTitle         :" << title << endl;
		cout << "\n\t\t\tDeveloper     :" << dev << endl;
		cout << "\n\t\t\tPublisher     :" << pub << endl;
		cout << "\n\t\t\tGenre         :" << genre << endl;
		cout << "\n\t\t\tRelease Date  :" << rel_date << endl;
		cout << "\n\n\t\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\v\n\n";
		cout << "\nDo You Want To Update Game ID(Y/N)       :";
		cin >> choice;
		if (choice[0] == 'y' || choice[0] == 'Y')
		{
			cout << "\n\t\tEnter the Game ID              :";
			cin >> id;
		}
		cout << "\nDO You Want To Update Title(Y/N)      :";
		cin >> choice;
		if (choice[0] == 'y' || choice[0] == 'Y')
		{
			cout << "\n\t\tEnter the Title                :";
			cin >> title;
		}

		cout << "\nDO You Want To Update Developer(Y/N)   :";
		cin >> choice;
		if (choice[0] == 'y' || choice[0] == 'Y')
		{
			cout << "\n\t\tEnter the Developer Name       :";
			cin >> dev;
		}

		cout << "\nDO You Want To Update Publisher(Y/N)   :";
		cin >> choice;

		if (choice[0] == 'y' || choice[0] == 'Y')
		{
			cout << "\n\t\tEnter the Publisher            :";
			cin >> pub;
		}
		cout << "\nDO You Want To Update Genre(Y/N) :";
		cin >> choice;

		if (choice[0] == 'y' || choice[0] == 'Y')
		{
			cout << "\n\t\tEnter the Genre                :";
			cin >> genre;
		}
		cout << "\nDO You Want To Update Release Date(Y/N)    :";
		cin >> choice;

		if (choice[0] == 'y' || choice[0] == 'Y')
		{
			cout << "\n\t\tEnter the Release Date         :";
			cin >> rel_date;
		}

		for (int i = 0; i < 75; i++)
		{
			Buff[i] = ' ';
		}

		this->Assign1(s1);
		memcpy(&Buff, &asize, sizeof(asize));
		strcpy(Buff, s1.id); strcat(Buff, "|");
		strcat(Buff, s1.title); strcat(Buff, "|");
		strcat(Buff, s1.dev); strcat(Buff, "|");
		strcat(Buff, s1.pub); strcat(Buff, "|");
		strcat(Buff, s1.genre); strcat(Buff, "|");
		strcat(Buff, s1.rel_date); strcat(Buff, "|");
		Next = strlen(Buff);

		if (Next > asize)
			cout << "\n\n\t\t\tRecord Overflow .... \n";
		else
		{
			file.seekp(size);
			file.write(Buff, asize);
			cout << "\n\n\t\t\t\tRecord Is Updated ....\n";
		}

	}

	else
		cout << setw(40) << "\n\n\n\t\t\tRecord Not Found ....\n";

	file.close();
	getch();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::Assign1(videog& s1)
{
	strcpy(s1.id, id);
	strcpy(s1.title, title);
	strcpy(s1.dev, dev);
	strcpy(s1.pub, pub);
	strcpy(s1.genre, genre);
	strcpy(s1.rel_date, rel_date);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::Input()
{
	int k, value;
	char usn[30];
	videog a;
	fsearch v;
	VariableFieldBuffer b;
	fstream file;
	clrscr();
	cout << "\n\t--------------------------------------------------\n\n";
	cout << "\n\tEnter the Game ID       :";
	cin >> id;
	while (v.Search(id) == 1)
	{
		cout << "\n\nDuplicate Entry Re-Enter The Game ID Value: ";
		cin >> id;
	}
	cout << "\n\tEnter the Title         :";
	cin >> title;
	cout << "\n\tEnter the Developer     :";
	cin >> dev;
	cout << "\n\tEnter the Publisher     :";
	cin >> pub;
	cout << "\n\tEnter the Genre         :";
	cin >> genre;
	cout << "\n\tEnter the Release Date  :";
	cin >> rel_date;
	file.open("vlist.txt", ios::app);
	k = b.pack(*this, file);
	file.close();
	if (k == 1)
		cout << "\n\n\t\t\tRecord Inserted ....\n\n";
	else
		cout << "Some problem";
}

/*Display function*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::Display()
{
	VariableFieldBuffer c;
	fstream file("vlist.txt", ios::in);
	file.seekg(0, ios::beg);
	while (c.unpack(*this, file))
	{
		clrscr();
		cout << endl << endl << endl;
		cout << setw(25) << " " << "DISPLAYING RECORD'S" << endl << endl << endl << endl;
		for (int i = 0; i < 80; i++)   cout << '*';   cout << endl << endl << endl;
		cout << setw(20) << " " << "Game ID                   : " << id << endl << endl << endl;
		cout << setw(20) << " " << "Title                     : " << title << endl << endl << endl;
		cout << setw(20) << " " << "Developer                 : " << dev << endl << endl << endl;
		cout << setw(20) << " " << "Publisher                 : " << pub << endl << endl << endl;
		cout << setw(20) << " " << "Genre                     : " << genre << endl << endl << endl;
		cout << setw(20) << " " << "Release Date              : " << rel_date << endl << endl << endl << endl;
		for (i = 0; i < 80; i++) cout << '*';
		cout << endl << endl << setw(39) << " ";
		getch();
	}
	if (!(c.unpack(*this, file)))
	{
		cout << endl << endl << endl << endl << setw(40) << "NO RECORDS FOUND ....";
		getch();
		return;
	}

	file.clear();
	file.close();
}


/*Delete function*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::del()
{
	char key[20], Buff[100];
	int size = 0, asize = 75, found = 0;
	clrscr();
	cout << "\nENTER THE RECORD KEY TO BE DELETED  :";
	cin >> key;
	fsearch u;
	found = u.Search(key);
	if (found == 1)
		cout << "\n\n\n\t\t\tRecord Is Found ....";
	else
	{
		cout << "\n\n\n\t\t\tRecord Is Not Found ....";
		getch();
		return;
	}

	VariableFieldBuffer b;
	fstream file, file1;
	if (found == 1)
	{
		file.open("vlist.txt", ios::app | ios::in | ios::out | ios::ate | ios::binary);
		file.seekg(0, ios::beg);
		file1.open("vllist.txt", ios::out);
		file1.seekg(0, ios::beg);
		while (b.unpack(*this, file))
		{
			if (strcmp(id, key) == 0)
			{
				cout << "\n\n\n\n\t\tRecord Is Deleted ....\n";

			}
			else
			{
				for (int i = 0; i < 75; i++)
				{
					Buff[i] = ' ';
				}
				this->Assign1(s1);
				memcpy(&Buff, &asize, sizeof(asize));
				strcpy(Buff, s1.id); strcat(Buff, "|");
				strcat(Buff, s1.title); strcat(Buff, "|");
				strcat(Buff, s1.dev); strcat(Buff, "|");
				strcat(Buff, s1.pub); strcat(Buff, "|");
				strcat(Buff, s1.genre); strcat(Buff, "|");
				strcat(Buff, s1.rel_date); strcat(Buff, "|");
				file1.write(Buff, asize);
				size = size + 75;
			}
		}
	}



	file1.close();
	file.close();
	unlink("vlist.txt");
	rename("vllist.txt", "vlist.txt");
	getch();
}

/*Key sorting*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::KeySort()
{
	char Buffer[15], str1[15] = "", str2[15] = "";
	int length = 15, ptr, i = 0;
	fstream file("vindex.txt", ios::in);
	file.seekg(0, ios::beg);

	while (1)
	{
		file.read(Buffer, length);
		if (file.fail())
			break;
		for (int j = 0; j < 15; j++)
			knodes[i][j] = Buffer[j];
		i++;
	}

	for (int j = 0; j < 15; j++)
		knodes[i][j] = Buffer[j];
	file.close();

	for (i = 0; i < count; i++)
	{
		for (int m = 0; m < 15; m++)
			str1[m] = knodes[i][m];
		j = i - 1;
	a:
		for (m = 0; m < 15; m++)
			str2[m] = knodes[j][m];
		ptr = strnicmp(str1, str2, 10);
		while (j >= 0 && ptr < 0)
		{
			for (m = 0; m < 15; m++)
				knodes[j + 1][m] = knodes[j][m];
			j--;
			goto a;
		}

		for (m = 0; m < 15; m++)
			knodes[j + 1][m] = str1[m];
	}

	knodes[i][j] = Buffer[j];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void  videog::Indexprimary()
{
	int size = 0, length = 75;
	char uns[15] = "0", IBuff[75] = "";
	count = 0;
	ifstream ofile("vlist.txt", ios::in);
	ofile.seekg(0, ios::beg);
	fstream nfile("vindex.txt", ios::out);
	if (ofile.fail())
		cout << "File not exist";
	else
		while (1)
		{
			ofile.read(IBuff, length);
			if (ofile.fail())
				break;
			for (int i = 0; IBuff[i] != '|'; i++)
				uns[i] = IBuff[i];
			count++;
			nfile.seekp(size);
			nfile << uns << "|" << count << "|";
			size = size + 15;
		}
	nfile.close();
	ofile.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::Indexdisplay(int size)
{
	VariableFieldBuffer c;
	fstream file("vlist.txt", ios::in);
	file.seekg(size, ios::beg);
	c.unpack(*this, file);
	clrscr();
	cout << endl << endl << endl;
	cout << setw(25) << " " << "DISPLAYING RECORD'S" << endl << endl << endl << endl;

	for (int i = 0; i < 80; i++)   cout << '*';   cout << endl << endl << endl;
	cout << setw(20) << " " << " Game ID            :  " << id << endl << endl << endl;
	cout << setw(20) << " " << " Title              :  " << title << endl << endl << endl;
	cout << setw(20) << " " << " Developer          :  " << dev << endl << endl << endl;
	cout << setw(20) << " " << " Publisher          :  " << pub << endl << endl << endl;
	cout << setw(20) << " " << " Genre              :  " << genre << endl << endl << endl;
	cout << setw(20) << " " << " Release Date       :  " << rel_date << endl << endl << endl << endl;
	for (i = 0; i < 80; i++) cout << '*';
	cout << endl << endl << setw(39) << " ";
	getch();
	file.clear();
	file.close();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void videog::Invertprimary()
{
	int size = 0, length = 75;
	char uns[20] = "0", IBuff[75] = "";
	count = 0;
	ifstream ofile("vlist.txt", ios::in);
	ofile.seekg(0, ios::beg);
	fstream nfile("vindex1.txt", ios::out);
	if (ofile.fail())
		cout << "File not exist";
	else
		while (1)
		{
			ofile.read(IBuff, length);
			if (ofile.fail())
				break;
			for (int i = 0; IBuff[i] != '|'; i++)
				uns[i] = IBuff[i];
			count++;
			nfile.seekp(size);
			nfile << count << "|" << uns << "|" << -1 << "|";
			size = size + 25;
		}

	nfile.close();
	ofile.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void videog::Invertsecondary()
{
	int size = 0, length = 75;
	char uns[20] = "0", IBuff[75] = "", title[20] = "";
	count = 0;
	videog as;
	ifstream ofile("vlist.txt", ios::in);
	ofile.seekg(0, ios::beg);
	fstream nfile("vsecond1.txt", ios::out);
	if (ofile.fail())
		cout << "File not exist";
	else
		while (1)
		{
			ofile.read(IBuff, length);
			if (ofile.fail())
				break;

			for (int i = 0; IBuff[i] != '|'; i++)
				uns[i] = IBuff[i];
			i++;

			for (int k = 0; IBuff[i] != '|'; i++)
				title[k++] = IBuff[i];
			title[k] = '\0';
			count++;
			nfile.seekp(size);
			nfile << title << "|" << count << "|";
			size = size + 25;
		}
	nfile.close();
	ofile.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void videog::Invertsecondarysort()
{
	char Buffer[25], str1[30] = "", str2[30] = "";
	int length = 25, ptr, i = 0;
	fstream file("vsecond1.txt", ios::in);
	file.seekg(0, ios::beg);
	for (int j = 0; j < 25; j++)
		knodes[i][j] = '\0';
	while (1)
	{
		for (int j = 0; j < 25; j++)
			Buffer[j] = '\0';
		file.read(Buffer, length);

		if (file.fail())
			break;

		for (j = 0; j < 25; j++)
			knodes[i][j] = Buffer[j];
		i++;
	}

	for (j = 0; j < 25; j++)
		knodes[i][j] = Buffer[j];

	file.close();

	for (i = 0; i < count; i++)
	{
		j = 0;
		for (int m = 0; m < 25; m++)
			str1[m] = knodes[i][m];
		j = i - 1;
	a:
		for (m = 0; m < 25; m++)
			str2[m] = knodes[j][m];
		ptr = strnicmp(str1, str2, 10);

		while (j >= 0 && ptr < 0)
		{
			for (m = 0; m < 25; m++)
				knodes[j + 1][m] = knodes[j][m];
			j--;
			goto a;
		}

		for (m = 0; m < 25; m++)
			knodes[j + 1][m] = str1[m];
	}

	knodes[i][j] = Buffer[j];
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void videog::CheckDup()
{
	int found, size = 0, length = 75;
	char ntitle[25] = "", ktitle[20] = "", klen[5] = "", * endptr, Buffer[75] = "", ukk[15] = "";
	videog sss;
	fstream qfile("vsecond3.txt", ios::out);
	qfile.seekp(0, ios::beg);
	fstream ffile("vsecond2.txt", ios::out);
	ffile.seekp(0, ios::beg);
	fstream file("vsecond1.txt", ios::in | ios::out);
	file.seekg(0, ios::beg);
	found = count;
	int i = 0;
	while (i < count)
	{
		int l = 0;
		for (int m = 0; m < 20; m++)
			ktitle[m] = '\0';
		for (int j = 0; knodes[i][j] != '|'; j++)
			ktitle[j] = knodes[i][j];
		j++;

		for (int n = 0; knodes[i][j] != '|'; j++)
			klen[n++] = knodes[i][j];


		int p = strlen(ktitle);
		int  ptr = strnicmp(ktitle, ntitle, p);

		if (ptr == 0)
		{
			ffile << klen << "|";
			fstream nfile("vlist.txt", ios::in);
			nfile.seekg(0, ios::beg);
			int  num = strtol(klen, &endptr, 10);
			num = num - 1;
			num = num * 75;
			nfile.seekg(num);
			nfile.read(Buffer, length);
			for (int i = 0; Buffer[i] != '|'; i++)
				ukk[l++] = Buffer[i];
			ukk[l] = '\0';
			qfile << ukk << "|";

			found = found + 1;
			nfile.close();
		}

		if (ptr > 0)
		{
			ffile.seekp(size);
			strcpy(ntitle, ktitle);
			ffile << ktitle << "|" << klen << "|";
			fstream nfile("vlist.txt", ios::in);
			nfile.seekg(0, ios::beg);
			int  num = strtol(klen, &endptr, 10);
			num = num - 1;
			num = num * 75;
			nfile.seekg(num);

			nfile.read(Buffer, length);

			for (int i = 0; Buffer[i] != '|'; i++)
				ukk[l++] = Buffer[i];

			ukk[l] = '\0';
			qfile.seekp(size);
			qfile << ktitle << "|" << ukk << "|";
			nfile.close();
			size = size + 30;
		}

		i++;
		found--;
	}
	ffile.close();
	file.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void videog::displayInvert()
{
	char Buffer[30], str1[30] = "", str2[30] = "";
	int length = 30, ptr, i = 0;
	fstream file("vsecond3.txt", ios::in);
	file.seekg(0, ios::beg);

	while (1)
	{
		file.read(Buffer, length);
		if (file.fail())
			break;

		for (int j = 0; j < 30; j++)
			knodes[i][j] = Buffer[j];
		i++;
	}

	for (int j = 0; j < 30; j++)
		knodes[i][j] = Buffer[j];
	file.close();

	for (i = 0; i < count; i++)
	{
		j = 0;
		for (int m = 0; m < 30; m++)
			str1[m] = knodes[i][m];
		j = i - 1;
	a:

		for (m = 0; m < 30; m++)
			str2[m] = knodes[j][m];
		ptr = strnicmp(str1, str2, 10);

		while (j >= 0 && ptr < 0)
		{
			for (m = 0; m < 30; m++)
				knodes[j + 1][m] = knodes[j][m];
			j--;
			goto a;
		}

		for (m = 0; m < 30; m++)
			knodes[j + 1][m] = str1[m];
	}

	knodes[i][j] = Buffer[j];

	for (i = 0; i < count; i++)
		for (j = 0; j < 30; j++)
			cout << knodes[i][j];
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int  videog::InvertSecondSearch(char* key)
{
	clrscr();
	char str1[30] = "";
	int found = 0;
	char Buffer[30];
	int length = 30, ptr, i = 0;
	fstream file("vsecond3.txt", ios::in);
	file.seekg(0, ios::beg);

	while (1)
	{
		file.read(Buffer, length);
		if (file.fail())
			break;
		for (int j = 0; j < 30; j++)
			knodes[i][j] = Buffer[j];
		i++;
	}

	for (int j = 0; j < 30; j++)
		knodes[i][j] = Buffer[j];

	for (i = 0; i < count; i++)
	{
		for (int j = 0; knodes[i][j] != '|'; j++)
			str1[j] = knodes[i][j];
		str1[j] = '\0';
		int l = strlen(key);
		int ptr = strnicmp(str1, key, l);
		if (ptr == 0)
		{
			found = 1;
			break;
		}
	}

	if (found == 1)

	{
		for (int j = 0; j < 30; j++)
			cout << knodes[i][j];
		return 1;
	}
	else
		return -1;
}

//$////////////////////////////////////////////////////////////////////////////////////////////////////////

int FixedLengthBuffer::Read(istream& stream, int size)
{
	stream.read(Buffer, Buffersize + size);
	return stream.good();
}

int FixedLengthBuffer::Write(ostream& stream)
{
	stream.write(Buffer, Buffersize);
	return stream.good();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normal();
void screen();
void screen1();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VariableFieldBuffer::pack(videog& s, fstream& file)
{
	int value;
	initialize();

	for (int i = 0; i < 75; i++)
	{
		Buffer[i] = ' ';
	}

	memcpy(&Buffer[0], &Buffersize, sizeof(Buffersize));
	strcpy(Buffer, s.id); strcat(Buffer, "|");
	strcat(Buffer, s.title); strcat(Buffer, "|");
	strcat(Buffer, s.dev); strcat(Buffer, "|");
	strcat(Buffer, s.pub); strcat(Buffer, "|");
	strcat(Buffer, s.genre); strcat(Buffer, "|");
	strcat(Buffer, s.rel_date); strcat(Buffer, "|");
	Nextbyte = strlen(Buffer);

	if (Nextbyte > Buffersize)
		return 0;

	else
		value = Write(file);
	return value;
}

/*Unpack Function*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VariableFieldBuffer::unpack(videog& s, fstream& file)
{
	initialize();
	Nextbyte = 0;
	int value = Read(file, Nextbyte);
	if (value == 0) return 0;
	if (Buffersize > 0)
	{
		int j = 0;
		for (int i = 0; Buffer[i] != '|'; i++)
			s.id[j++] = Buffer[i];
		s.id[j] = '\0';
		i++;

		for (j = 0; Buffer[i] != '|'; i++)
			s.title[j++] = Buffer[i];
		s.title[j] = '\0';
		i++;

		for (j = 0; Buffer[i] != '|'; i++)
			s.dev[j++] = Buffer[i];
		s.dev[j] = '\0';
		i++;

		for (j = 0; Buffer[i] != '|'; i++)
			s.pub[j++] = Buffer[i];
		s.pub[j] = '\0';
		i++;

		for (j = 0; Buffer[i] != '|'; i++)
			s.genre[j++] = Buffer[i];
		s.genre[j] = '\0';
		i++;


		for (j = 0; Buffer[i] != '|'; i++)
			s.rel_date[j++] = Buffer[i];
		s.rel_date[j] = '\0';
		i++;

		Nextbyte = Buffersize + 75;
		return 1;
	}
	return 0;
}


/*Function to search a key*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int fsearch::Search(char* key)
{
	int found = 0;
	videog s1;
	VariableFieldBuffer b;
	fstream file("vlist.txt", ios::in || ios::out);
	file.seekg(0, ios::beg);
	while (b.unpack(s1, file))
		if (strcmpi(s1.id, key) == 0)
			found = 1;
	file.close();
	return found;
}

/*Main function*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	int choice, ch, cho, a;
	char key[15];
	videog s;
	clrscr();
	do
	{
		screen();

		cout << "     PLEASE ENTER YOUR CHOICE [1-3]  :   ";
		cin >> ch;
		switch (ch)
		{
		case 1:do
		{
			clrscr();
			clrscr();
			textbackground(8);
			gotoxy(25, 3);
			textcolor(10);
			cprintf("        VIDEO GAME RECORDS");
			gotoxy(25, 4);
			cprintf("**********************************");
			int z = 19, q = 10;
			gotoxy(25, 7);
			textcolor(15);
			cprintf("        M A I N    M E N U ");
			normal();
			gotoxy(z, q++);
			cout << "1 >  Insert";
			gotoxy(z, q++);
			cout << "2 >  Update";
			gotoxy(z, q++);
			cout << "3 >  Display";
			gotoxy(z, q++);
			cout << "4 >  Delete";
			gotoxy(z, q++);
			cout << "5 >  Quit";
			gotoxy(z, q++);
			gotoxy(z, q++);
			gotoxy(z, q++);
			cout << "     PLEASE ENTER YOUR CHOICE : ";
			cin >> choice;

			switch (choice)
			{
			case 1:s.Input();  //input is inbsurt function
				break;

			case 2:s.Modify(); //modify is update function
				break;

			case 3:s.Display();
				break;

			case 4:s.del();
				break;

			case 5:clrscr();
				screen();
				break;

			default:exit(0);
			}
		} while (choice != 5); break;

		case 2:
			do
			{
				screen1();
				cout << "     PLEASE ENTER YOUR CHOICE  : ";
				cin >> cho;

				switch (cho)
				{


				case 1:
					s.Invertprimary();
					s.Invertsecondary();
					s.Invertsecondarysort();
					s.CheckDup();
					clrscr();
					gotoxy(25, 20);
					cout << "Enter the Secondary key: ";
					cin >> key;
					a = s.Binary(key);
					if (a == -1)
					{
						cout << "\n\nRecord not found....!";
						getch();
					}
					s.displayInvert();
					int b = s.InvertSecondSearch(key);
					if (b == 1)
					{
						s.Indexprimary();
						s.KeySort();
						gotoxy(20, 25);
						gotoxy(25, 20);
						cprintf("Enter the Primary key: ");
						cin >> key;
						a = s.Binary(key);
						if (a == -1)
						{
							gotoxy(25, 70);
							cout << "\n\nRecord not found....!";
							getch();
						}
						else
						{
							//int b=a;
							a = a - 1;
							a = a * 75;
							s.Indexdisplay(a);
							cout << "\n\n\nSuccessful search......  :";
							getch();
						}
					}

					//////


					else
					{
						clrscr();
						gotoxy(20, 25);
						cout << "Record not found...!";
					}
					break;

				case 2:clrscr();
				}
			}

			while (cho != 2); screen(); break;

		case 3:exit(0);

		default: exit(0);//sound(100);delay(500);nosound();break;
		}
	} while (ch != 3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void screen()
{
	int g = 19, h = 10;
	clrscr();
	clrscr();
	clrscr();
	gotoxy(25, 3);
	textcolor(10);
	cprintf("        FILE STRUCTURE       ");
	gotoxy(25, 4);
	cprintf("*******************************");
	gotoxy(25, 7);
	textcolor(15);
	cprintf(" Welcome to Video Game Library ");
	normal();
	gotoxy(g, h++);
	cout << "   -> Video Game Records";
	gotoxy(g, h++);
	cout << "   -> Indexing";
	gotoxy(g, h++);
	cout << "   -> Quit";
	gotoxy(g, h++);
	gotoxy(g, h++);
	gotoxy(g, h++);
	normal();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void normal()
{
	textattr(7);
	textcolor(7);
	textbackground(BLACK);
	_setcursortype(_NORMALCURSOR);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void screen1()
{

	int b, g = 19, h = 10;
	clrscr();
	gotoxy(27, 3);
	textcolor(10);
	cprintf("       INDEXING");
	gotoxy(25, 4);
	cprintf("************************");
	gotoxy(27, 7);
	textcolor(15);
	cprintf(" M A I N     M E N U ");
	normal();
	gotoxy(g, h++);
	cout << "-> Inverted List";
	gotoxy(g, h++);
	cout << "-> Quit";
	gotoxy(g, h++);
	gotoxy(g, h++);
	gotoxy(g, h++);
}
