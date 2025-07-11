#include "Book.h"
#include "User.h"  // only needed here for buy_book()

using namespace std;

// ==== Book ====
Book::Book() {}

Book::Book(std::string title, std::string ISBN, std::string author_name, int number_of_pages, string demo)
    : title(title), ISBN(ISBN), author_name(author_name), year(""), demo(demo), number_of_pages(number_of_pages)
{
    hasDemo = !demo.empty();
}

const std::string& Book::get_book_title() const { return title; }
int Book::get_number_of_pages() const { return number_of_pages; }
Book::~Book() {}

// ==== EBook ====
EBook::EBook(std::string title, std::string ISBN, std::string author_name, int number_of_pages,
             std::vector<std::string> book_pages, string demo)
    : Book(title, ISBN, author_name, number_of_pages, demo), book_pages(book_pages) {}

std::string EBook::get_page_content(int position) { return book_pages[position]; }

void EBook::add_pages(std::vector<std::string> pages) {
    for (auto& page : pages) {
        book_pages.push_back(page);
        number_of_pages++;
    }
}

std::vector<std::string>& EBook::get_book_pages() { return book_pages; }

const string EBook::to_pdf() const { return "Book"; }

bool EBook::buy_book(ExoServices& exoServices, User& currentUser) {
    exoServices.mail("download link", to_pdf());
    return true;
}

// ==== PaperBook ====
PaperBook::PaperBook(std::string title, std::string ISBN, std::string author_name, int number_of_pages,
                     int quantity, string demo)
    : Book(title, ISBN, author_name, number_of_pages, demo), quantity(quantity) {}

void PaperBook::inc_quantity(int newQuant) { quantity += newQuant; }

bool PaperBook::dec_quantity(int quant) {
    if (quant <= quantity) {
        quantity -= quant;
        return true;
    }
    return false;
}

bool PaperBook::buy_book(ExoServices& exoServices, User& currentUser) {
    exoServices.ship(currentUser.get_address());
    return true;
}

PaperBook::~PaperBook() {}

// ==== Factory ====
std::shared_ptr<Book> book_factory(BookType bookType, std::string title, std::string ISBN, 
                                   std::string author_name, int number_of_pages, int quantity, std::string demo)
{
    switch (bookType) {
        case BookType::EBOOK: {
            cout << "Adding EBook\n";
            std::vector<std::string> pages;
            for (int i = 1; i <= number_of_pages; ++i) {
                std::string page;
                std::cout << "Enter page #" << i << ": ";
                std::getline(std::cin >> std::ws, page);
                pages.push_back(page);
            }
            return std::make_shared<EBook>(title, ISBN, author_name, number_of_pages, pages, demo);
        }
        case PAPERBOOK:
            cout << "Adding PaperBook\n";
            return std::make_shared<PaperBook>(title, ISBN, author_name, number_of_pages, quantity, demo);
    }
    return nullptr;
}