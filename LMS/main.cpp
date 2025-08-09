#include <iostream>
#include "Book.h"
#include "Category.h"

int main() {
    // Tạo thể loại
    Category cat1("C001", "Science Fiction");
    Category cat2("C002", "Programming");

    // Tạo sách (thêm tên nhà xuất bản)
    Book book1("978-0-123456-47-2", "Dune", "Frank Herbert", "Chilton Books", cat1, 1965, true);
    Book book2("978-0-987654-32-1", "Effective C++", "Scott Meyers", "Addison-Wesley", cat2, 2005, false);

    std::cout << "\n=== BOOK LIST ===\n";
    book1.display();
    std::cout << "\n";
    book2.display();

    return 0;
}
