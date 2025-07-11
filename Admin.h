#ifndef _ADMINS_
#define _ADMINS_
#include <iostream>
#include <memory>
#include <vector>
#include "User.h"
#include "Book.h"
#include "Inventory.h"
class Admin{
    private:
        int order;
        Inventory&inventory;
        UsersManager&userManager;
    public:
        Admin(Inventory&inventory,UsersManager&userManager);
        void view_profile()const;
        void add_book()const;
        bool logout()const;
        void admin_menu()const;
};
Admin::Admin(Inventory&inventory,UsersManager&userManager)
:inventory(inventory),userManager(userManager){};
void Admin::view_profile()const{
    std::cout << "\t-user name: " << userManager.GetCurrentUser()->get_user_name() << "\n";
    std::cout << "\t-name: " << userManager.GetCurrentUser()->get_name() << "\n";
    std::cout << "\t-email: " << userManager.GetCurrentUser()->get_email() << "\n";
}
void Admin::add_book()const{
    std::cout << "Enter type: \n";
    std::cout << "\t1-EBook\n";
    std::cout << "\t2-PaperBook\n";

    int choice;
    std::cin >> choice;
    BookType bookType;
    switch (choice)
    {
    case 1:
        bookType=BookType::EBOOK;
        break;
    case 2:
        bookType=BookType::PAPERBOOK;
        break;
    }

    std::cout << "Enter ISBN: ";
    std::string ISBN;
    std::cin >> ISBN;

    std::cout << "Enter Title: ";
    std::string title;
    std::cin >> title;

    std::cout << "Enter Author Name: ";
    std::string author_name;
    std::cin >> author_name;

    std::cout << "Enter number of pages: ";
    int number_of_pages;
    std::cin >> number_of_pages;

    shared_ptr<Book> book = book_factory(bookType,title,ISBN,author_name,number_of_pages);
    inventory.add_book(book);
}
void Admin::admin_menu()const{
    while(true){
        std::cout << "Menu:\n"
            << "\t\t1: View Profile\n"
            << "\t\t2: AddBook\n"
            << "\t\t3: Logout\n" 
            << "Enter number in range 1 - 3: ";
        int choise;
        std::cin >> choise;
        if(choise==1)
            view_profile();
        else if(choise==2)
            add_book();
        else if(choise==3)
            break;
    }
};


#endif