#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

int menu();

enum type { pass = 0, cargo = 1 };

struct vagon {
	int number = 0;
	enum type aType;
};

struct Node {
	vagon info;
	Node* prev = NULL;
	Node* next = NULL;
};

struct train {
	vagon* first;
	vagon* last;
};

//template <typename T>
struct Stack {
	Node* head = NULL;
	Node* tail = NULL;

	void addLast(vagon i) {
		Node* node = new Node;
		node->info = i;
		node->next = NULL;
		if (tail == NULL) {
			tail = node; head = node;
		}
		else {
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
	}

	void Print()
	{
		Node* cur = tail;
		while (cur) {
			cout << "Number: " << cur->info.number << " Type: ";
			if (cur->info.aType == pass)cout << "Passenger\n";
			else cout << "Cargo\n";
			cur = cur->prev;
		}
		return;
	}

	Node* peek()
	{
		return tail;
	};
	void push(vagon& v)
	{
		addLast(v);
	};
	Node* pop()
	{
		if (tail == NULL) {
			cout << "There are no elements!" << endl << endl;
			return false;
		}
		else {
			Node* cur = tail;
			if (tail != head) {
				tail = (tail)->prev;
				(tail)->next = NULL;
			}
			else tail = NULL;
			return cur;
		}
	};
};

void TrainSort(Stack& Train, Stack& Pass, Stack& Cargo) {

	while (Train.tail != NULL) {
		if (Train.peek()->info.aType == pass)Pass.push(Train.pop()->info);
		else Cargo.push(Train.pop()->info);
	}
}

void StackPrint(Stack stack) {
	stack.Print();
}

void VagonMaker(Stack& stack, vagon*& mas, int k)
{
	system("cls");
	ofstream file("Vagons.bin", ios::binary);
	int key = 0;
	for (int i = 0; i < k; ++i) {
		cout << "Vagon #" << i + 1 << endl;
		mas[i].number = i + 1;
		cout << "Enter type of Vagon:\n0 --> Passenger\n1 --> Cargo\n";
		cin >> key;
		switch (key) {
		case 0:mas[i].aType = pass; break;
		case 1:mas[i].aType = cargo; break;
		}
		cin.clear();
		stack.addLast(mas[i]);
		file.write((char*)& mas[i], sizeof(vagon));
		system("cls");
	}
	file.close();
	return;
}

int main()
{


	int k = 0, key = 0;

	bool isRunning = 1;
	while (isRunning) {
		key = menu();
		switch (key) {
		case 0: {
			cout << "How many vagons would you like?\n";
			cin >> k;
			vagon* mas = new vagon[k];
			Stack* Train = new Stack;
			VagonMaker(*Train, mas, k);
			StackPrint(*Train);
			system("pause");
			delete[] mas, Train;
			break;
		}
		case 1: {
			Stack* Train = new Stack;
			Stack* Pass = new Stack;
			Stack* Cargo = new Stack;
			ifstream f("Vagons.bin", ios::binary);
			vagon tmp;
			while (f.read((char*)& tmp, sizeof(vagon))) {
				Train->push(tmp);
			}
			StackPrint(*Train);
			TrainSort(*Train, *Pass, *Cargo);
			system("pause");
			system("cls");
			cout << "Passenger train:\n";
			StackPrint(*Pass);
			system("pause");
			cout << "\nCargo train:\n";
			StackPrint(*Cargo);
			system("pause");
			delete Train, Pass, Cargo;
			break;
		}
		case 2:isRunning = 0;
		}
	}

	return 0;
}


int menu()
{
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> Create general train" << endl;
		else  cout << "   Create general train" << endl;
		if (key == 1) cout << "-> Sort train" << endl;
		else  cout << "   Sort train" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}