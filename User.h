#ifndef __USER__
#define __USER__
#include <iostream>
#include <vector>
#include<map>
#include"Book.h"
#include"Inventory.h"
#include "Session.h"

int ReadInt(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return ReadInt(low, high);
}

int ShowReadMenu(const vector<string> &choices) {
	cout << "\nMenu:\n";
	for (int ch = 0; ch < (int) choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return ReadInt(1, choices.size());
}
class User{
    private:
        std::string user_name;
        std::string password;
        std::string name;
        std::string email;
		std::string address;
        std::vector<Book>books;
        std::vector<Session>my_sessions;
        bool isAdmin;
        int user_count=0;
    public:
        User(std::string user_name,std::string password,std::string email,std::string name
			,std::string address,bool isAdmin=false);
        ~User();
        Session&add_session(EBook&ebook);
        int display_my_reading_history()const;
        const std::string&get_user_name()const;
        const std::string&get_password()const;
        const std::string&get_name()const;
        const std::string&get_email()const;
        const std::string&get_address()const;
        const bool  is_library_admin()const;
        void view_profile()const;
		Session&get_session(int idx);
};
std::vector<User>users;

const int max_user_count=100;
User::User(std::string user_name,std::string password,std::string email,
	std::string name,std::string address,bool isAdmin)
:user_name(user_name),password(password),name(name),email(email)
,user_count(user_count+1),address(address),isAdmin(isAdmin){}
User::~User(){}
int User::display_my_reading_history()const{
    for(int i=0;i<my_sessions.size();i++)
        std::cout << i+1 << ":" 
            << my_sessions[i].get_book_name()
            << " Page:" << my_sessions[i].get_current_page()
            << " - " << my_sessions[i].get_session_date() << "\n";
    return my_sessions.size();
}
const std::string&User::get_user_name()const{
    return user_name;
}
const std::string&User::get_password()const{
    return password;
}
const std::string&User::get_name()const{
    return name;
}
const std::string&User::get_email()const{
    return email;
}
const std::string&User::get_address()const{
	return address;
}
const bool User::is_library_admin()const{
    if(isAdmin)
        return 1;
    return 0;
}
void User::view_profile()const{
    std::cout << " User-Name:\t\t" << user_name
    << "\n email:\t\t" << email 
    << "\n books: \n \t";
    for(auto&book:books)
        std::cout << book.get_book_title() << "\n \t";
}
Session&User::add_session(EBook&ebook){
    my_sessions.push_back(Session(ebook));
    return my_sessions.back();
}
Session&User::get_session(int idx){
	return my_sessions[idx];
}

// =========================================USER_MANAGER================================================

class UsersManager {
private:
	User* current_user {nullptr};
	map<string, User*> userame_userobject_map;
	void FreeLoadedData() {
		for (auto pair : userame_userobject_map) {
			delete pair.second;
		}
		userame_userobject_map.clear();
		current_user = nullptr;
	}

public:
	UsersManager()
    {
	}

	~UsersManager() {
		cout << "Destuctor: UsersManager\n";
		FreeLoadedData();
	}

	UsersManager(const UsersManager&) = delete;
	void operator=(const UsersManager&) = delete;

	void LoadDatabase() {
		if (userame_userobject_map.size() > 0)
			return;		// let's assume 1 run for this system only

		cout << "UsersManager: LoadDatabase\n";

		FreeLoadedData();
		// Some "Dummy Data" for simplicity
		User* user1 = new User("mostafa","111","most@gmail.com","Mostafa Saad Ibrahim","cairo",true);
		userame_userobject_map[user1->get_user_name()] = user1;
		User* user2 = new User("asmaa","222","asmaa@gmail.com","Asmaa Saad Ibrahim","alex",false);
		userame_userobject_map[user2->get_user_name()] = user2;
	}

	void AccessSystem() {
		int choice = ShowReadMenu( { "Login", "Sign Up" });
		if (choice == 1)
			DoLogin();
		else
			DoSignUp();
	}

	void DoLogin() {
		LoadDatabase();

		while (true) {
			string user_name, pass;
			cout << "Enter user name (no spaces): ";
			cin >> user_name;
			cout << "Enter password (no spaces): ";
			cin >> pass;

			if (!userame_userobject_map.count(user_name)) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			User* user_exist = userame_userobject_map.find(user_name)->second;

			if (pass != user_exist->get_password()) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			current_user = user_exist;
			break;
		}
	}

	void DoSignUp() {
		string user_name;
		while (true) {
			cout << "Enter user name (No spaces): ";
			cin >> user_name;

			if (userame_userobject_map.count(user_name))
				cout << "Already used. Try again\n";
			else
				break;
		}

        string password;
		cout << "Enter password (no spaces): ";
		cin >> password;

        string name;
		cout << "Enter name (no spaces): ";
		cin >> name;

        string email;
		cout << "Enter email (no spaces): ";
		cin >> email;

		string address;
		cout << "Enter address (no spaces): ";
		cin >> address;

		current_user = new User(user_name,password,email,name,address);
		string t = current_user->get_user_name();
		userame_userobject_map[current_user->get_user_name()] = current_user;
	}

	// BookReadingSession* AddReadingSession(Book* book) {
	// 	return current_user->AddReadingSession(book);
	// }

	User* GetCurrentUser() const {
		return current_user;
	}
    Session&add_book(EBook ebook){
        return current_user->add_session(ebook);
    }
    void start_session(){
        
    }
};

// =======================================USER VIEW=====================================================

class UserView {
private:
	UsersManager&users_manager;
	Inventory&inventory;
	SessionManager&sessoin_manager;
public:

	UserView(UsersManager & users_manager, Inventory &inventory,SessionManager sessoin_manager) :
			users_manager(users_manager), inventory(inventory),sessoin_manager(sessoin_manager){

	}

	void Display() {
		const User* user = users_manager.GetCurrentUser();
		cout << "\n\nHello " << user->get_name() << " | User View\n";

		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("List & Select from My Reading History");
		menu.push_back("List & Select from Available Books");
		menu.push_back("Logout");

		while (true) {
			int choice = ShowReadMenu(menu);
			if (choice == 1)
				ViewProfile();
			else if (choice == 2)
				ListReadingHistory();
			else if (choice == 3)
				ListAvailableBooks();
			else
				break;
		}
	}

	void ViewProfile() {
		const User* user = users_manager.GetCurrentUser();

		// cout << "\n" << user->ToString() << "\n";
	}

	void DisplaySession(Session& session) {
		vector<string> menu;
		menu.push_back("Next Page");
		menu.push_back("Previous Page");
		menu.push_back("Stop Reading");

		while (true) {
			cout << "Current Page: " << session.get_page_num() << "\n";
			cout << session.get_current_page() << "\n";

			int choice = ShowReadMenu(menu);
			if (choice == 1)
				session.next_page();
			else if (choice == 2)
				session.previous_page();
			else
				break;
		}
		session.set_date();
	}

	void ListReadingHistory() {
		int idx = users_manager.GetCurrentUser()->display_my_reading_history();

		if (idx == 0)
			cout << "\nNo history. List books and start having fun\n";
		else {
			cout << "\nWhich session to open?: ";
			int choice = ReadInt(1, idx);
			sessoin_manager.DisplaySession(users_manager.GetCurrentUser()->get_session(choice));
		}
	}

	void ListAvailableBooks() {
		inventory.display_all_books();

		cout << "\nOur current book collection:\n";
		int idx = inventory.get_inventory_size();

		cout << "\nWhich book to read?: ";
		int choice = ReadInt(1, idx);	// For simplicity, assume a new book is selected
		auto ebookPtr = std::dynamic_pointer_cast<EBook>(inventory.get_book_by_index(choice-1));
		if (ebookPtr) {
			sessoin_manager.DisplaySession(users_manager.add_book(*ebookPtr));
		} else {
			std::cout << "Failed to cast.\n";
		}
	}
};


#endif