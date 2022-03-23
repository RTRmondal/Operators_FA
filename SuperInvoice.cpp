#include <iostream>
#include <vector>
#include <string>
class Item
{
private:
    std::string name_;
    float unit_net_price_;
    char VAT_type_;
    int amount_sold_;
public:
    Item(std::string name, float unp, char VAT_t, int ams)
    {
        name_ = name;
        unit_net_price_ = unp;
        VAT_type_ = VAT_t;
        amount_sold_ = ams;
    }

    std::string get_name()
    {
        return name_;
    }

    float get_unit_price()
    {
        return unit_net_price_;
    }

    char get_vat()
    {
        return VAT_type_;
    }

    int get_ams()
    {
        return amount_sold_;
    }

    float calculate_net_price()
    {
        return unit_net_price_ * (float)amount_sold_;
    }
    
    float calculate_total()
    {
        float vat = 1.0; 
        if(VAT_type_ == 'A')
        {
            vat = 1.23;
        }
        else if(VAT_type_ == 'B')
        {
            vat = 1.08;
        }
        return calculate_net_price() * vat;
    }
};

class Invoice
{
private:
    long double nip_seller_;
    long double nip_buyer_;
    std::vector<Item> items_;
public:

    Invoice(long double nip_s, long double nip_b, std::vector<Item> items = {})
    {
        nip_seller_ = nip_s;
        nip_buyer_ = nip_b;
        items_ = items;
    }

    void add_item(Item item)
    {
        items_.emplace_back(item);
    }
    friend std::ostream &operator<<(std::ostream &stream, Invoice &rhs)
    {
        stream << "------------------VAT invoice------------------\n";
        stream << "===============================================\n";
        stream << "Seller: "<< rhs.nip_seller_ << "      " << "Buyer: " << rhs.nip_buyer_ << "\n\n";
        stream << "                  c.j. VAT   il.    net   total\n";
        float net = 0;
        float total = 0;
        for(int i = 0; i < (int)rhs.items_.size(); i++)
        {
            stream << i+1 << ". " << rhs.items_[i].get_name() << "\t| " << rhs.items_[i].get_unit_price() << "  " << rhs.items_[i].get_vt() << " |  ";
            stream << rhs.items_[i].get_ams() << " |  " << rhs.items_[i].calculate_net_price() << " | " << rhs.items_[i].calculate_total();
            stream << std::fixed << std::setprecision(2) << "\n";
            net += rhs.items_[i].calculate_net_price();
            total += rhs.items_[i].calculate_total();
        }
        stream << "\n------------------------------------ TOTAL ----\n";
        stream << "                                  " << net << " | " << total << "\n";
        return stream;
    }
};
int main()
{
    Invoice inv(7770003699, 1123456789);
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    std::cout << inv << std::endl;
    return 0;
}
