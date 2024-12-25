
#include <iostream>
#include <list>
#include <string>
#include <windows.h>
using namespace std;

class Item
{
protected:
    string name;
    double price;

public:
    Item(string name,double price)
      :name(name),price(price){}
    Item()
      :name("Unknowen"), price(0.0) {}

    double getPrice()
    {
        return price;
    }
    string getName()
    {
        return name;
    }
    virtual void showDetails()
    {
        cout << name << " - $" << price;
    }
    bool operator==(const Item& other) const
    {
        return name == other.name && price == other.price;
    }
};


class Food : public Item
{
private:
    int calories;
public:
    Food(string name, double price, int calories)
        : Item(name,price),calories(calories){}
    Food()
        : Item("Unknowen", 0.0), calories(0) {}
    void showDetails()override
    {
        cout << " (Food) ==> " << name << " - $" << price << " | " << calories << " calories" << endl;
    }


};

class Drink : public Item
{
private:
    string size;
public:
    Drink(string name, double price, string size)
        : Item(name, price), size(size) {}
    Drink()
        : Item("Unknowen", 0.0), size("NULL") {}
    void showDetails()override
    {
        cout<< " (Drink)==> "<< name <<" - $" << price << " | Size: " << size << endl;
    }
};


class Order
{
private :
    list<Item*>order;
    double total;
    int table;

public:
    Order(int table)
    {
        total = 0.0;
        this->table = table;
    }
    Order()
    {
        total = 0.0;
        this->table = 1;
    }
    void addItem(Item*item)
    {
        order.push_front(item);
        total += item->getPrice();
    }
    void removeDish(Item* item)
    {
        order.remove(item);
        total -= item->getPrice();
    }
    void showDetails()
    {
        cout << "\n   Table: " << this->table << endl;
        cout << "===================================Your Order=================================== \n";
        for (Item*s : order)
        {
             s->showDetails();
        }
        cout<< "\n============================ Total Price: " << this->total <<" $ ================================ \n";
    }
    double getTotal()
    {
        return total;
    }
};


class Restraunt
{
private:
    string name;
    list<Item*>menu;
    list<Order*>orders;
public:
    Restraunt(string name)
    {
        this->name = name;
        menu = { new Food("Alferado",150.0,600),new Food("Chicken Ranch Pizza",414,1000), new Drink("Zero-Cola",20,"Meduim"), };
    }
    Restraunt()
    {
        this->name = "PHI Restraunt";
        menu = { };
    }
    string getName()
    {
        return name;
    }
    void addItemToMenu(Item* item)
    {
        menu.push_back(item);
    }
    void viewMenu() 
    {
        cout << "\nThat's our Menu :\n";
        int k = 0;
        for (Item* i : menu)
        {
            cout << " "<<++k << " -";
            i->showDetails();
        }
    }
    void addOrder(Order* order)
    {
        orders.push_front(order);
    }
    Item* getItemFromMenu(int index)
    {
        auto item = menu.begin();
        advance(item, index);
        return *item;
    }
    void choosingOrder()
    {
        system("Color E4");
        //system("Color 0A");
        Restraunt restraunt("PHI");
        cout << "\n================================================================================\n"
            << "===========================+WELCOME TO " << restraunt.getName() << " RESTRAUNT+===========================\n"
            << "================================================================================\n";
        restraunt.viewMenu();
        int  choice;
        Order* order = new Order(1);
        while (true)
        {
            cout << "\nEnter Your choice by index or enter 0 to EXIT: ";
            cin >> choice;
             if (choice == 0)
             {
                 cout << "\nFinishing your order..." << endl;
                 orders.push_back(order);
                 break;
             }
             else if(choice > 0 && choice <= menu.size())
             { 
             auto item = restraunt.getItemFromMenu(choice - 1);
             order->addItem(item);
               cout << "Added '" << item->getName() << "' to your order!\n";
             }
            cout << "Invalid choice! \n";
        }
        cout << "\n your order Details: \n";
        order->showDetails();

    }


};


using namespace std;
int main()
{
    Restraunt restraunt("PHI");
    restraunt.choosingOrder();

}
