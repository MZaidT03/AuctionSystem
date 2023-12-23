#include <iostream>
#include <string>
#include <fstream>

using namespace std;
const int MAX_REC = 100;
int NUM_REC = 0;
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
    float initialPrice, finalPrice;
};
void header()
{
    cout << "\t\t|-----------Auction System------------|" << endl;
    cout << "\t\t|         Muhammad Zaid Tahir         |" << endl;
    cout << "\t\t|             2023-CS-426             |" << endl;
    cout << "\t\t|    muhammadzaidtahir90@gmail.com    |" << endl;
    cout << "\t\t|------------0336-7339855-------------|" << endl;
}
void menu()
{
    cout << "\n\t\tAuction System:\n";
    cout << "1. Add Product\n";
    cout << "2. Start Auction\n";
    cout << "3. Show All Products.\n";
    cout << "4. Show Summary Sold Products.\n";
    cout << "5. Exit\n";
}
void AddProduct(ProductInfo info)
{
    ofstream write("product.txt", ios::app);

    info.no = NUM_REC;
    cin.ignore();
    cout << "Enter Your Name: ";
    getline(cin, info.name);
    cout << "Enter Product Name: ";
    getline(cin, info.productName);
    cout << "Enter Product Type: ";
    getline(cin, info.productType);
    cout << "Enter Your CNIC: ";
    getline(cin, info.cnic);
    cout << "Enter Initial: ";
    cin >> info.initialPrice;

    if (!write.is_open())
    {
        cout << "File Not Opened.";
    }
    else
    {
        write << info.no << " "
              << info.name << endl;
        write << info.productName << endl;
        write << info.productType << endl;
        write << info.cnic << endl;
        write << info.initialPrice << endl;
    }
    NUM_REC += 1;
}
void startAuction(ProductInfo info)
{
    ofstream write("history.txt", ios::app);
    ifstream read("product.txt");
    int finalPrice;
    string productName;
    cin.ignore();
    cout << "Enter Product name for which you want to Start Auction: ";
    getline(cin, productName);
    if (!read.is_open())
    {
        cout << "File Not Opened.";
    }
    else
    {
        while (read >> info.no)
        {
            read.ignore();
            getline(read, info.name);
            getline(read, info.productName);
            getline(read, info.productType);
            getline(read, info.cnic);
            read >> info.initialPrice;
            read.ignore();
            if (productName == info.productName)
            {
                cout << info.no << " "
                     << "Name: " << info.name << endl;
                cout << "Product Name: " << info.productName << endl;
                cout << "Product Type: " << info.productType << endl;
                cout << "CNIC: " << info.cnic << endl;
                cout << "Initial Price: " << info.initialPrice << endl;

                char c;
                cout << "Are you sure you want to start Auction for this product. (Y/N)";
                cin >> c;

                if (c == 'Y' || c == 'y')
                {
                    int j = 0;
                    int previousBid = info.initialPrice; // Initialize previousBid with initialPrice

                    while (true)
                    {
                        cout << "Enter Your Bid: ";
                        cin >> finalPrice;

                        // Check if the current bid is greater than the previous bid
                        if (finalPrice <= previousBid)
                        {
                            cout << "Bid must be greater than the previous bid. Please enter a higher bid." << endl;
                            continue; // Continue the loop without updating previousBid
                        }

                        cout << endl
                             << "Current Bid is: " << finalPrice << endl;
                        cout << "Want to increase the Bid (Y/N): ";
                        cin >> c;

                        if (c == 'N' || c == 'n')
                        {
                            cout << "Product Sold At " << finalPrice << endl;
                            if (!write.is_open())
                            {
                                cout << "File Not Opened.";
                            }
                            else
                            {
                                write << info.no << " "
                                      << info.name << endl;
                                write << info.productName << endl;
                                write << info.productType << endl;
                                write << info.cnic << endl;
                                write << info.initialPrice << endl;
                                write << info.finalPrice << endl;
                            }

                            break; // Exit the loop when auction is complete
                        }

                        // Update previousBid only if the current bid is greater
                        previousBid = finalPrice;

                        j++;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                cout << "No Product Found." << endl;
            }
        }
    }
}

void ShowAllProduct(ProductInfo info)
{
    ifstream read("product.txt");
    if (!read.is_open())
    {
        cout << "File Not Opened.";
    }
    else
    {
        while (read >> info.no)
        {
            read.ignore();
            getline(read, info.name);
            getline(read, info.productName);
            getline(read, info.productType);
            getline(read, info.cnic);
            read >> info.initialPrice;

            read.ignore();

            cout << info.no << endl;
            cout << "Name: " << info.name << endl;
            cout << "Product Name: " << info.productName << endl;
            cout << "Product Type: " << info.productType << endl;
            cout << "CNIC: " << info.cnic << endl;
            cout << "Initial Price: " << info.initialPrice << endl;
        }
    }
}
void ShowSummary(ProductInfo info)
{
    ifstream read("history.txt");
    if (!read.is_open())
    {
        cout << "File Not Opened.";
    }
    else
    {
        while (read >> info.no)
        {
            read.ignore();
            getline(read, info.name);
            getline(read, info.productName);
            getline(read, info.productType);
            getline(read, info.cnic);
            read >> info.initialPrice;
            read >> info.finalPrice;

            read.ignore();

            cout << info.no << endl;
            cout << "Name: " << info.name << endl;
            cout << "Product Name: " << info.productName << endl;
            cout << "Product Type: " << info.productType << endl;
            cout << "CNIC: " << info.cnic << endl;
            cout << "Initial Price: " << info.initialPrice << endl;
            cout << "Sold Price: " << info.finalPrice << endl;
        }
    }
}
int main()
{

    ProductInfo product;
    ofstream write;
    ifstream read;
    int find, f;
    int choice;
    header();
    do
    {

        menu();
        cout << "Enter your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            AddProduct(product);
            break;
        case 2:
            startAuction(product);
            break;
        case 3:
            ShowAllProduct(product);
            break;
        case 4:
            ShowSummary(product);
            break;
        }

    } while (choice != 5);
}