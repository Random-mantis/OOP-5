#include <iostream>
#include "stack.h"

int main(){
    Stack<int, MapAllocator<int>> s;
    int choice, value;
    while (true) {
        std::cout << "\n1. Push\n2. Pop\n3. Top\n4. Print\n5. Clear\n6. Check empty\n7. Show allocations\n0. Exit\n> ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter value: ";
                std::cin >> value;
                s.push(value);
                break;
            case 2:
                s.delfirst();
                break;
            case 3:
                if (!s.is_void()) std::cout << "Top: " << s.top() << std::endl;
                else std::cout << "Stack is empty\n";
                break;
            case 4:
                for (auto& v : s) std::cout << v << " ";
                std::cout << std::endl;
                break;
            case 5:
                s.clear();
                break;
            case 6:
                std::cout << (s.is_void() ? "Empty" : "Not empty") << std::endl;
                break;
            case 7:
                MapAllocator<int>::print_allocations();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid option\n";
        }
    }
}