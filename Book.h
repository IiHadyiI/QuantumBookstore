// #ifndef BOOK_H_
// #define BOOK_H_
// #include<iostream>
// #include <vector>
// #include <memory>
// #include "ExoServices.h"
// #include "User.h"
// using namespace::std;
// enum BookType{EBOOK,PAPERBOOK};
// class User;
// class product{

// };
// class Book : public product
// {
// private:
//     const std::string title,ISBN,author_name,year,demo;
//     bool hasDemo;
// protected:
    
// public:
//     int number_of_pages;
//     Book();
//     Book(std::string tilte,std::string ISBN,std::string author_name,int number_of_pages,string demo={});
//     const std::string&get_book_title()const;
//     int get_number_of_pages()const;
//     virtual bool buy_book(ExoServices&exoServices,User&currentUser)=0;
//     virtual ~Book();
// };
// Book::Book(){}
// Book::Book(std::string tilte,std::string ISBN,std::string author_name,int number_of_pages,string demo)
// :title(tilte),ISBN(ISBN),author_name(author_name),demo(demo)
// {
//     if(!demo.empty())
//         hasDemo=true;
// }
// const std::string&Book::get_book_title()const{
//     return title;
// }
// int Book::get_number_of_pages()const{
//     return number_of_pages;
// }
// Book::~Book()
// {
// }

// // ==================EBOOK===================
// class EBook:public Book{
//     private:
//         std::vector<std::string>book_pages;
//     public:
//         EBook(std::string tilte,std::string ISBN,std::string author_name,
//             int number_of_pages,std::vector<std::string>book_pages,string demo={});
//         void add_pages(std::vector<std::string> page);
//         std::vector<std::string>&get_book_pages();
//         std::string get_page_content(int posistion);
//         virtual bool buy_book(ExoServices&exoServices,User*currentUser);
//         const string to_pdf()const;
// };
// EBook::EBook(std::string tilte,std::string ISBN,std::string author_name,
//         int number_of_pages,std::vector<std::string>book_pages,string demo)
// :Book(tilte,ISBN,author_name,number_of_pages,demo),book_pages(book_pages){
    
// }
// std::string EBook::get_page_content(int positin){
//     return book_pages[positin];
// }
// void EBook::add_pages(std::vector<std::string> pages){
//     for(auto page:pages)
//         book_pages.push_back(page),number_of_pages++;
// }
// std::vector<std::string>&EBook::get_book_pages() {
//     return book_pages;
// }
// const string EBook::to_pdf()const{
//     return "Book";
// }
// bool EBook::buy_book(ExoServices&exoServices,User*currentUser){
//     exoServices.mail("fldkjs",to_pdf());
//     return 1;
// }
// // =====================PAPERBOOK========================
// class PaperBook:public Book
// {
// private:
//     int quantity;
// public:
//     PaperBook(std::string title,std::string ISBN,std::string author_name,
//         int number_of_pages,int quantity,string demo={});
//     void inc_quantity(int newQuant);
//     bool dec_quantity(int quant);
//     virtual bool buy_book(ExoServices&exoServices,User*currentUser);
//     ~PaperBook();
// };

// PaperBook::PaperBook(std::string title,std::string ISBN,std::string author_name,int number_of_pages,int quantity,string demo)
// :Book(title,ISBN,author_name,number_of_pages,demo),quantity(quantity)
// {
// }
// void PaperBook::inc_quantity(int newQuant){
//     quantity+=newQuant;
// }
// bool PaperBook::dec_quantity(int quant){
//     if(quant<=quantity){
//         quantity-=quant;
//         return 1;
//     }
//     return 0;
// }
// bool PaperBook::buy_book(ExoServices&exoServices,User*currentUser){
//     exoServices.ship(currentUser->get_address());
//     return 1;
// }
// PaperBook::~PaperBook()
// {
// }

// std::shared_ptr<Book>book_factory(BookType bookType,std::string tilte,std::string ISBN,std::string author_name,
//         int number_of_pages,int quantity={},string demo={}){
//     switch (bookType)
//     {
//     case BookType::EBOOK:{
//         cout << "working\n";
//         std::vector<std::string> pages;
//         for (int i = 1; i <= number_of_pages; ++i) {
//             std::string page;
//             std::cout << "Enter page #" << i << ": ";
//             std::getline(std::cin >> std::ws, page);
//             pages.push_back(page);
//         }
//         return std::make_shared<EBook>(tilte,ISBN,author_name,number_of_pages,pages,demo);
//         break;
//     }
//     case PAPERBOOK:
//         cout << "notworking\n";
//         return std::make_shared<PaperBook>(tilte,ISBN,author_name,number_of_pages,quantity,demo);
    
//     }
//     return nullptr;
// }
// #endif

#ifndef BOOK_H_
#define BOOK_H_

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "ExoServices.h"

enum BookType { EBOOK, PAPERBOOK };

class User;  // forward declaration only — no methods called here

class product {
    // Empty base class for now
};

class Book : public product {
protected:
    const std::string title, ISBN, author_name, year, demo;
    bool hasDemo;
    int number_of_pages;

public:
    Book();
    Book(std::string title, std::string ISBN, std::string author_name, int number_of_pages, std::string demo = {});
    
    const std::string& get_book_title() const;
    int get_number_of_pages() const;

    virtual bool buy_book(ExoServices& exoServices, User& currentUser) = 0;
    virtual ~Book();
};

// =============== EBOOK ===================
class EBook : public Book {
private:
    std::vector<std::string> book_pages;

public:
    EBook(std::string title, std::string ISBN, std::string author_name, int number_of_pages,
          std::vector<std::string> book_pages, std::string demo = {});

    void add_pages(std::vector<std::string> page);
    std::vector<std::string>& get_book_pages();
    std::string get_page_content(int position);
    virtual bool buy_book(ExoServices& exoServices, User& currentUser);
    const std::string to_pdf() const;
};

// =============== PAPERBOOK ===================
class PaperBook : public Book {
private:
    int quantity;

public:
    PaperBook(std::string title, std::string ISBN, std::string author_name, int number_of_pages,
              int quantity, std::string demo = {});

    void inc_quantity(int newQuant);
    bool dec_quantity(int quant);
    virtual bool buy_book(ExoServices& exoServices, User& currentUser);
    ~PaperBook();
};

// =============== FACTORY ===================
std::shared_ptr<Book> book_factory(BookType bookType, std::string title, std::string ISBN, 
                                   std::string author_name, int number_of_pages, int quantity = {}, 
                                   std::string demo = {});

#endif
