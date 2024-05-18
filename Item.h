//
// Created by at991 on 5/18/2024.
//

#ifndef ASSIGNMENT_2_ITEM_H
#define ASSIGNMENT_2_ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item {
private:
    string name;
    string category;
    int price;
public:
    Item() {}
    Item(const string& n, const string& c, int p)
    : name{n}, category{c}, price{p} {

    }

    void print() const {
        cout << "Item name: " << this->name << endl;
        cout << "Item category: " << this->category << endl;
        cout << "Item price: " << this->price << endl;
    }

    // getters
    string get_name() const { return this->name; }
    string get_category() const { return this->category; }
    int get_price() const { return this->price; }

    bool operator<(const Item &item) const {
        return this->price < item.price;
    }

    Item& operator=(const Item &item) {
        this->name = item.name;
        this->category = item.category;
        this->price = item.price;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Item item);
};

ostream& operator<<(ostream& os, const Item item) {
    item.print();
    return os;
}

#endif //ASSIGNMENT_2_ITEM_H
