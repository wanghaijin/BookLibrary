#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <conio.h>
#include <string.h>
#include <fstream>
#include "models/Book.h"
#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;


void SetScreenGrid() {
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}

void SetSysCaption() {
	system("title Sample");
}

void ClearScreen() {
	system("cls");
}

//��ӭҳ��
void ShowWelcome() {
	for (int i = 0; i < 7; ++i) {
		cout << end;
	}
	cout << setw(40);
	cout << "**************************" << endl;
	cout << setw(40);
	cout << "ͼ�����ϵͳ" << endl;
	cout << setw(40);
	cout << "**********************" << endl;
}

//��ʾϵͳ���˵�
void ShowRootMenu() {
	cout << setw(40);
	cout << "��ѡ����" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 �������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 ���ȫ��" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 ɾ��ͼ��" << endl;
}

void WaitUser() {
	init iInputPage = 0;
	cout << "enter �������˵� q �˳�" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
}

int gets_select() {
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}

// �������
void GuideInput() {
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout << "��������" << endl;
	cin >> inName;
	cout << "����ISBN" << endl;
	cin >> inIsbn;
	cout << "����۸�" << endl;
	cin >> inPrice;
	cout << "��������" << endl;
	cin >> inAuthor;

	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.writeData();
	cout << "Write Finish" << endl;
	WaitUser();
}


// �鿴ģ��
void ViewData(int iSelPage = 1) {
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char price[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	iStream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "���м�¼" << iDataCount << "";
	cout << "����ҳ��" << iPage << "";
	cout << "��ǰҳ��" << iCurPage << "";
	cout << "n��ʾ��һҳm����" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name" << setw(22) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try {
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail()) {
			for (int i = 1; i < 21; ++i) {
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(price, 0, 50);
				memset(inAuthor, 0, 50);
				if (bIndex)
					cout << setw(3) << ((iCurPage - 1) * 20 + i);
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);
				cout << setw(24) << inIsbn;
				ifile.read(price, NUM2);
				cout << setw(12) << price;
				ifile.read(inAuthor, NUM2);
				cout << setw(12) << inAuthor;
				cout << endl;
				if (ifile.tellg() < 0) {
					bIndex = false;
				}
				else {
					bIndex = true;
				}
			}
		}
	}
	catch (...) {
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}
	if (iCurPage < iPage) {
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}

long GetFileLength(ifstream& ifs) {
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}

void DeleteBookFromFile() {
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}

void WaitView(int iCurPage) {
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
	if (buf[0] == 'm')
		mainloop();
	if (buf[0] == 'n')
		ViewData(iCurPage);
}

void mainloop() {
	ShowWelcome();
	while (1) {
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch(gets_select())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;

		}
	}
}

void main() {
	SetScreenGrid();
	SetSysCaption("ͼ�����ϵͳ");
	mainloop();
}