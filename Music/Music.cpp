// Music.cpp : Defines the entry point for the console application.
//Harry Kalra

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

class node
{
	char artist[25];
	char song[25];
	node *next;

public:
	node(char artist[25], char song[25]);
	friend class songlist;
};
node::node(char a[25], char s[25])
{
	strcpy_s(artist, a);
	strcpy_s(song, s);
	next = NULL;
}

class songlist //linked list
{
	node *head;
	node *tail;
	char name[100];
public:
	songlist();
	void setName(char n[]);
	void readList();
	void addNodetoEnd(node * nptr);
	void showList();
	void playSong();
	void skipSong();
	int deleteSong();

};

songlist::songlist()
{
	head = NULL;
	tail = NULL;
}
void songlist::setName(char n[])
{
	strcpy_s(name, n);
}
void songlist::readList()
{
	ifstream infile(name);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		node *ptr;
		char artist[25];
		char song[25];

		infile.getline(artist, 25, ',');
		if (strlen(artist))
		{
			infile.getline(song, 25);
			ptr = new node(artist, song);
			addNodetoEnd(ptr);
		}
	}
	infile.close();
}
void songlist::showList()
{
	node *ptr;
	ptr = head;
	system("pause");
	system("cls");
	cout << "Song Playlist" << endl;
	cout << "------l--------------------" << endl;
	if (ptr == NULL)
	{
		cout << "There is nothing in the playlist " << endl;
		return;
	}
	while (ptr != NULL)
	{
		cout << "Artist: " << ptr->artist << "\t Title: " << ptr->song << endl;
		ptr = ptr->next;
	}
}
void songlist::playSong()
{
	char response[20];
	node *ptr;
	ptr = head;
	cout << "What song would you like to play?" << endl;
	cin.clear();
	cin.ignore();
	gets_s(response);
	while (ptr != NULL)
	{
		if (strcmp(response, ptr->song) == 0)
		{
			cout << "Playing " << ptr->song << " Artist: " << ptr->artist << endl;
		}
		ptr = ptr->next;
	}
}
void songlist::skipSong()
{
	char response[20];
	node *ptr;
	ptr = head;
	cout << "What song would you like to skip?" << endl;
	cin.clear();
	cin.ignore();
	gets_s(response);
	while (ptr != NULL)
	{
		if (strcmp(response, ptr->song) == 0)
		{
			cout << "Playing " << ptr->song << " Artist: " << ptr->artist << endl;
			cout << "Stopped" << ptr->song << " Artist: " << ptr->artist << endl;
			ptr = ptr->next;
			if (ptr->song)
				cout << "Now playing " << ptr->song << " Artist: " << ptr->artist << endl;
		}
		ptr = ptr->next;
	}

}
int songlist::deleteSong()
{
	char response[20];
	node *ptr = head;
	cout << "Type the song you want to delete" << endl;
	cin.clear();
	cin.ignore();
	gets_s(response);

	if (ptr == NULL)
		return -1;
	if (strcmp(response, ptr->song) == 0)
	{
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (strcmp((ptr->next)->song, response) == 0))
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}
void songlist::addNodetoEnd(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}
int main()
{
	bool answer = true;
	char response;

	char name[100];
	cout << "Music" << endl;
	cout << "---------------------" << endl;
	cout << "Please enter a file name: " << endl;
	gets_s(name);
	songlist *mylist = new songlist();

	mylist->setName(name);
	mylist->readList();
	do
	{
		mylist->showList();

		cout << " " << endl;
		cout << "--------------------------" << endl;
		cout << "Select an Option" << endl; //user options
		cout << "[P]lay " << endl;
		cout << "[S]kip " << endl;
		cout << "[D]elete " << endl;
		cout << "[Q]uit " << endl;
		cin >> response;
		cout << " " << endl;

		if ((response == 'P') || (response == 'p'))
		{
			mylist->playSong();
			answer = true;

		}
		else if ((response == 'S') || (response == 's'))
		{
			mylist->skipSong();
			answer = true;
		}
		else if ((response == 'D') || (response == 'd'))
		{
			if (mylist->deleteSong())
				mylist->showList();
			answer = true;
		}
		else if ((response == 'Q') || (response == 'q'))
		{
			system("cls");
			cout << "Quit!" << endl;
			answer = false;
		}
		else
		{
			system("cls");
			cout << "Invalid" << endl;
			answer = true;
		}
	} while (answer);
	
	return 0;
}
