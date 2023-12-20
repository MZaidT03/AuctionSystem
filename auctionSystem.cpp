#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};
struct ProductInfo
{
    int no;
    string name, productName, productType, cnic;
    float initialPrice;
};

void menu()
{
    cout << "\n\t\tAuction System:\n";
    cout << "1. Add Product\n";
    cout << "2. Start Auction\n";
    cout << "3. Show All Products\n";
    cout << "4. Exit\n";
}
void startAuction(ProductInfo info)
{
}
int main()
{
    ProductInfo product;
    ofstream write;
    ifstream read;
    int find, f;
    int choice;
    do
    {

        menu();
        cout << "Enter your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Product No: ";
            cin >> product.no;
            cin.ignore();
            cout << "Enter Your Name: ";
            getline(cin, product.name);
            cout << "Enter Product Name: ";
            getline(cin, product.productName);
            cout << "Enter Product Type: ";
            getline(cin, product.productType);
            cout << "Enter Your CNIC: ";
            cin >> product.cnic;
            cout << "Enter Initial Price: ";
            cin >> product.initialPrice;

            write.open("product.txt", ios::app);
            if (!write.is_open())
            {
                cout << "File Not Opened";
            }
            else
            {
                write << product.no << endl;
                write << product.name << endl;
                write << product.productName << endl;
                write << product.productType << endl;
                write << product.cnic << endl;
                write << product.initialPrice << endl;

                write.close();
            }
            break;
        case 2:
            cout << "Enter Product No for which you want to start Auction";
            cin >> find;

            read.open("product.txt");
            if (!read.is_open())
            {
                cout << "File Not Opened." << endl;
            }
            else
            {
                while (!read.eof())
                {
                    read >> product.no;
                    read.ignore();
                    getline(read, product.name);
                    getline(read, product.productName);
                    getline(read, product.productType);
                    read >> product.initialPrice;
                    read.ignore();

                    if (find == product.no)
                    {
                        f++;
                        cout << product.no << ") Name:" << product.name << endl;
                        cout << "CNIC: " << product.cnic << endl;
                        cout << "Product: " << product.productName << "--" << product.productType << endl;
                        cout << "Initial Price" << product.initialPrice << endl;
                    }
                }

                read.close();
            }

            break;
        case 3:
            read.open("product.txt");
            if (!read.is_open())
            {
                cout << "Not Connected";
            }
            else
            {

                while (!read.eof())
                {

                    read >> product.no;
                    read.ignore();
                    getline(read, product.name);
                    getline(read, product.productName);
                    getline(read, product.productType);
                    getline(read, product.cnic);
                    read >> product.initialPrice;
                    cout << product.no << ") Name:" << product.name << endl;
                    cout << "CNIC: " << product.cnic << endl;
                    cout << "Product: " << product.productName << "--" << product.productType << endl;
                    cout << "Initial Price" << product.initialPrice << endl;
                }
                if (f == 0)
                {
                    cout << "No Product Available." << endl;
                }
                read.close();
            }
            break;
        }

    } while (choice != 0);
}