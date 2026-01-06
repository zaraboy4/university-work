#include <map>
#include <string>
#include <iostream>

int main() {
    // за мапа можем да мислим, че е двоично наредено дърво и по ключ търсим стойност
    // реално е RedBlackTree
    std::map<int, std::string> m;

    // insert връща двойка (итератор към добавения елемент, bool дали е добавен елементът)
    // std::pair<std::map<int, std::string>::iterator, bool> p = m.insert({1, "Ivan"});
    auto p = m.insert({1, "Ivan"});
    std::cout << "key: " << p.first->first << '\n';
    std::cout << "is inserted: " << p.second << '\n';

    auto p2 = m.insert({1, "Petar"}); // ако двойка с такъв ключ вече има в мапа, 
                                      //то се връща итератор към нея
    std::cout << "key: " << p2.first->first << '\n';
    std::cout << "value: " << p2.first->second << '\n';
    std::cout << "is inserted: " << p2.second << '\n';
    
    m.insert({3, "Petkan"});
    m.insert({2, "Bogdan"});

    // find връща итератор към намерения елемент
    std::map<int, std::string>::iterator it = m.find(3);
    std::cout << "key: " << it->first << '\n'; // 3
    std::cout << "value: " << it->second << '\n'; // Petkan

    // как се проверява, че елемент не е в мапа
    if (m.find(4) == m.end()) {
        std::cout << "no pair with that key\n";
    }

    // обхождане на елементите на мапа, което се случва в сортиран ред
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << '(' << it->first << ", " << it->second << ") ";
    } 
    return 0;
}
