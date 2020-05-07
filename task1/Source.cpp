#include <fstream>
#include <iostream>
const int NL = 10; // text lenght in liness
const int NS = 100; // lines length
const int NW = 200; // word lenght
const int MAX = NL * NS + 10;

using namespace std;

ifstream in;
ofstream out;

char* information;
struct List {
	char* value;
	List* next = NULL;
};

char* read(const char* filename); // функция, читающая текст из файла.
List* extractWords(char* text);
List* insertElement(List* current, char* value);
bool isAlpha(char c);
bool isCorrect(char* word, char letter);
char* echo(const char* file);
void ansver();

int main() {
	setlocale(LC_ALL, "rus");
	system("chcp 1251");

	while (true) {
		cout << "введите 1 - для перезаписи информации\n\
введите 2 - для показа записаных данных;\n\
введите 3 - для обработки входных данных;\n\
введите 4 - для пока результатов;\nиначе программа будет завершнена\n";
		int step;
		cin >> step;
		switch (step) {
		case 1: {
			cout << "введите текст для анализа, в одну строку\n";
			char *text = new char[MAX];
			int len = 0;
			cin.get();
			cin.get(text, MAX - 10, '\n');
			cin.get();
			out.open("input.txt");
			out << text << '/';
			out.close();

			break;
		}
		case 2: {
			char* text = echo("input.txt");
			cout << "текст:\n";
			cout << text << endl << endl;
			break;
		}
		case 3: {
			cout << "ответ подсчитан\n\n";
			ansver();
			break;
		}
		case 4: {
			char* text = echo("output.txt");
			cout << "текст:\n";
			cout << text << endl << endl;
			break;
		}
		default:
			return 0;
			break;
		}
	}

	
	return 0;
}


void ansver() {
	information = read("input.txt");
	char alpha;

	List* zero = extractWords(information);
	List* curent = zero->next;

	out.open("output.txt");
	out << information << endl;
	out << "\nсостояние списка:\n";
	while (curent != NULL) {
		out << (curent->value) << ' ';
		if (curent->next == NULL) {
			alpha = curent->value[strlen(curent->value) - 1];
		}
		curent = curent->next;
	}
	out << endl;
	curent = zero->next;
	while (curent != NULL) {
		if (isCorrect(curent->value, alpha))
			out << curent->value << ' ';
		curent = curent->next;
	}
	out << '/';
	out.close();
}

char* echo(const char* file) {
	char* text = new char[10000];
	ifstream in;
	in.open(file);
	in.get(text, 10000, '/');
	in.close();
	return text;
}

bool isCorrect(char* word, char letter) {
	return word[0] == word[strlen(word)-1] && word[0] == letter;
}

char toLower(char c) {
	if (c >= 'А' && c <= 'Я') {
		c = c + 32;
	}
	return c;
}
bool isAlpha(char c) {
	bool ans = 'А' <= c && c <= 'я';
	return ans;
}

List* insertElement(List* current, char* value) {
	List* boofPattern = current->next;
	current->next = new List;
	current = current->next;
	current->value = value;
	current->next = boofPattern;
	return current;
}

List* extractWords(char* text) {
	List* first = new List;
	List* current = first;
	bool isWordStart = false;
	char* boof = new char[NW + 1];
	int len = 0;
	for (int i = 0; text[i] != '\0'; i++) {
		if (isAlpha(text[i])) {
			boof[len] = toLower(text[i]);
			len++;
			isWordStart = true;
		}
		else {
			if (isWordStart) {
				boof[len] = '\0';
				current = insertElement(current, boof);
				isWordStart = false;
				len = 0;
				boof = new char[NW + 1];
			}
		}
	}
	boof[len] = '\0';
	if(len != 0) current = insertElement(current, boof);
	return first;
}

char* read(const char* filename) {
	in.open(filename);
	char* pointer = new char[MAX];
	in.get(pointer, MAX - 10, '/');
	in.close();
	return pointer;
}

char New();
char c;