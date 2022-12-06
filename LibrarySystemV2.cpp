/*LIBRARY SYSTEM PROJECT V3 Bobby
it is possible to refactor this code to adhere to object-oriented programming principles. 
Some key changes that could be made include:

Create separate Book and User classes, each with its own header and cpp file. 
The code for each class should be moved out of the library_system struct and into these new files.

Make the member functions of the Book and User classes private so that they can only be accessed by other member functions of the same class. 
This will help enforce encapsulation and modularity.

Define the member functions of the Book and User classes in the cpp files. 
This will help keep the code organized and easy to read.

Add a LibrarySystem class that will manage the books and users in the library. 
This class should have its own header and cpp file as well.
*/

Create member functions for the LibrarySystem class that allow users to borrow and return books, and allow the system to keep track of which books have been borrowed by which users. These functions should use the Book and User classes to perform their operations.
#include<iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <assert.h>
using namespace std;


struct Book 
{
	int id;
	string name;
	int total_quantity;
	int total_borrowed;

	Book() 
	{
		total_quantity = total_borrowed = 0;
		id = -1;
		name = "";
	}

	void read() {
		cout << "Please enter the book id:  ";
		cin >> id;
		cout << "What is the title of the book?    ";
		cin >> name;
		cout << "How many copies does the library have?   ";
		cin >> total_quantity;
		total_borrowed = 0;  
		//Note how the initial 'borrowed' is 0!
	}

	bool borrow() 
	{
		if (total_quantity - total_borrowed == 0)
			return false;
		++total_borrowed;
		return true;
	}
	
	void return_copy() 
	{
		assert(total_borrowed > 0);
		--total_borrowed;
	}

	bool has_prefix(string prefix) 
	{
		if (name.size() < prefix.size())
			return false;

		for (int i = 0; i < (int)prefix.size(); ++i) 
		{
			if (prefix[i] != name[i])
				return false;
		}
		return true;
	}

	void print() 
	{
		cout << "Book id:  " << id 
			<< "    Book title: " << name
			<< "    (Total quantity: " << total_quantity 
			<< ", with " << total_borrowed << " borrowed)"
			<< "\n";
	}
};

bool compare_books_by_id(book& a, book& b) {
	return a.id < b.id;
}

bool compare_books_by_name(book& a, book& b) 
{
	return a.name < b.name;
}

struct user 
{
	int id;
	string name;
	set<int> borrowed_books_ids;

	user() {
		name = "";
		id = -1;
	}

	void read() 
	{
		cout << "Please enter the user's name:  ";
		cin >> name;
		cout << "Now enter the user id:   ";
		cin >> id;
	}

	void borrow(int book_id)
	{
		borrowed_books_ids.insert(book_id);
	}

	void return_copy(int book_id) 
	{
		auto it = borrowed_books_ids.find(book_id);

		if (it != borrowed_books_ids.end())
			borrowed_books_ids.erase(it);
		else
			cout << "User " << name << 
			" didn't borrow book id " << book_id
			<< "\n";
	}

	bool is_borrowed(int book_id) 
	{
		auto it = borrowed_books_ids.find(book_id);
		return it != borrowed_books_ids.end();
	}

	void print() 
	{
		cout << "User: " << name << ", with id: (" << id 
			<< ") has the following borrowed book ids: ";
		for (int book_id : borrowed_books_ids)
			cout << book_id << " ";
		cout << "\n";
	}
};

struct library_system
{
	vector<book> books;
	vector<user> users;

	library_system() 
	{
	}

	void run() 
	{
		while (true) 
		{
			int choice = menu();

			if (choice == 1)
				add_book();
			else if (choice == 2)
				search_books_by_prefix();
			else if (choice == 3)
				print_who_borrowed_book_by_name();
			else if (choice == 4)
				print_library_by_id();
			else if (choice == 5)
				print_library_by_name();
			else if (choice == 6)
				add_user();
			else if (choice == 7)
				user_borrow_book();
			else if (choice == 8)
				user_return_book();
			else if (choice == 9)
				print_users();
			else
				break;
		}
	}

	int menu()
	{
		int choice = -1;
		while (choice == -1) 
		{
			cout << "Library Menu:\n";
			cout << "1) Add a book\n";
			cout << "2) Search by prefix\n";
			cout << "3) Print users borrowing a specific book\n";
			cout << "4) Print library by ID\n";
			cout << "5) Print library by book title\n";
			cout << "6) Add a user\n";
			cout << "7) User borrows a book\n";
			cout << "8) User returns a book\n";
			cout << "9) Print users\n";
			cout << "10) Exit\n";
			cout << "Please enter your choice (1 - 10): ";
			cin >> choice;
			if (!(1 <= choice && choice <= 10)) 
			{
				cout << "Invalid choice. Try again\n";
				choice = -1;
			}
		}
		return choice;
	}

	void add_book() 
	{
		Book b;
		b.read();   //See lines 24-33
		Books.push_back(b);
	}

	void search_books_by_prefix() 
	{
		cout << "Please enter your prefix:  ";
		string prefix;
		cin >> prefix;
		int count = 0;
		for (Book& b : Books) {
			if (b.has_prefix(prefix))    
				//Note how this calls a book struct function (lines 49-60)
			{
				cout << b.name << "\n";
				++count;
			}
		}
		if (!count)
			cout << "No books with such prefix\n";
	}

	void add_user() 
	{
		user u;
		u.read();   //Lines 92-98
		users.push_back(u);  //Users vector
	}

	int find_book_idx_by_name(string name) //Uses the books vector in this struct
	{
		for (int i = 0; i < (int)books.size(); ++i) 
		{
			if (name == books[i].name)
				return i;
		}
		return -1;
	}

	int find_user_idx_by_name(string name)   //Uses the users vector in this struct
	{
		for (int i = 0; i < (int)users.size(); ++i) 
		{
			if (name == users[i].name)
				return i;
		}
		return -1;
	}

	bool read_user_name_and_book_name(int& user_idx, int& book_idx, int trials =3) 
	{
		string user_name;
		string book_name;
		while (trials--) {
			cout << "Enter user name and book name: ";
			cin >> user_name >> book_name;
			user_idx = find_user_idx_by_name(user_name);  //Lines 240-248
			if (user_idx == -1) 
			{
				cout << "Invalid user name. Try again\n";
				continue;
			}
			book_idx = find_book_idx_by_name(book_name);  //Lines 230-238
			if (book_idx == -1) 
			{
				cout << "Invalid book name. Try again\n";
				continue;
			}
			return true;
		}
		cout << "You did several trials! Try later.";
		return false;
	}

	void user_borrow_book() 
	{
		int user_idx, book_idx;
		if (!read_user_name_and_book_name(user_idx, book_idx))  //Lines 250-274 (which calls 240-248 and 230-238)
			return;
		int book_id = books[book_idx].id;
		if (!books[book_idx].borrow())  //Lines 35-41
			cout << "No more copies available right now\n";
		else
			users[user_idx].borrow(book_id);  //Lines 100-103
	}

	void user_return_book() 
	{
		int user_idx, book_idx;
		if (!read_user_name_and_book_name(user_idx, book_idx))  //Lines 250-274 (which calls 240-248 and 230-238)
			return;
		int book_id = books[book_idx].id;
		books[book_idx].return_copy();   //Lines 43-47
		users[user_idx].return_copy(book_id);  //Lines 105-115
	}

	void print_library_by_id() 
	{
		sort(books.begin(), books.end(), compare_books_by_id);  //Lines 72-74
		cout << "\n";
		for (book& b : books)
			b.print();  //Lines 62-70 (in the book struct)
	}
	
	void print_library_by_name() 
	{
		sort(books.begin(), books.end(), compare_books_by_name);  //Lines 76-79
		cout << "\n";
		for (book& b : books)
			b.print();  //Lines 62-70 (in the book struct)
	}

	void print_users() 
	{
		cout << "\n";
		for (user& u : users)
			u.print();  //Lines 123-131 (User struct)
	}

	void print_who_borrowed_book_by_name() 
	{
		string book_name;
		cout << "Enter book name: ";
		cin >> book_name;
		int book_idx = find_book_idx_by_name(book_name);   //Lines 230-238 (book related)
		if (book_idx == -1) 
		{
			cout << "Invalid book name.\n";
			return;
		}
		int book_id = books[book_idx].id;
		if (books[book_idx].total_borrowed == 0) 
		{
			cout << "No borrowed copies\n";
			return;
		}
		for (user& u : users) 
		{
			if (u.is_borrowed(book_id))    //Lines 117-121  (in the user struct)
				cout << u.name << "\n";
		}
	}
};

int main() 
{
	library_system library;
	library.run();
	return 0;
}
