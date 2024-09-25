#pragma once
#include <list>
#include <fstream>
#include <algorithm>
#include "text.h"

using namespace std;

struct recordlist
{
	char name[30];
	int score;
};

bool compare(recordlist el1, recordlist el2)
{
	return (el1.score > el2.score);
}

void padTo(std::string& str, const size_t num, const char paddingChar = ' ')
{
	if (num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}

void read(SDL_Renderer* renderer)
{
	text record(renderer);
	string currec;
	list <struct recordlist> top;
	recordlist X;
	ifstream in("records.dat", ios::binary | ios::in);
	int max = 0;
	//if (in.peek() == EOF) cout << "ÔÀÉË ÏÓÑÒ"<<endl;
	while (in.peek() != EOF)
	{
		in.read((char*)&X, sizeof X);
		top.push_back(X);
		max++;
	}
	top.sort(compare);
	list <struct recordlist> ::iterator it = top.begin();
	for (int i = 0, y = 150; i < max; i++, it++, y+=30)
	{
		currec = to_string(i + 1) + "\t" + it->name;
		record.show(currec, 40, y, 20);
		currec = to_string(it->score);
		padTo(currec, 6);
		record.show(currec, 540, y, 20);
	}
	in.close();
}

void write(int score, string player)
{
	list <struct recordlist> top;
	recordlist X; X.score = score; strcpy_s(X.name, player.c_str());
	top.push_back(X);
	int max=1;
	ifstream in("records.dat", ios::binary | ios::in);
	while (in.peek() != EOF)
	{
		recordlist* Y = new recordlist;
		in.read((char*)&(*Y), sizeof *Y);
		top.push_back(*Y);
		max++;
	}
	if (max > 10)
		max = 10;
	in.close();
	top.sort(compare);
	list <struct recordlist> ::iterator it = top.begin();
	ofstream out("records.dat", ios::binary | ios::out);
	for (int i = 0; i<max; i++, it++)
	{
		X.score = it->score; strcpy_s(X.name, it->name);
		out.write((char*)&X, sizeof X);
	}
	out.close();
}

void readtxt(SDL_Renderer* renderer)
{
	fstream txt("rules.txt");
	string str;
	text rules(renderer);
	int y = 140;
	if (!txt.is_open())
		cout << "Îøèáêà îòêðûòèÿ ôàéëà\n";
	while (txt.peek() != EOF)
	{
		y+=20;
		getline(txt, str);
		rules.show(str, 10, y, 20);
	}
	txt.close();
}