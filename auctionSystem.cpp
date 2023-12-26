#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Date
{
    int day, month, year;
};
struct ProductInfo
{
    int no;
    string name, productName, productType, cnic, buyerName, buyerCnic;
    float initialPrice, finalPrice;
    Date date, datePurchase;
};
void writeNumRecToFile(int numRec)
{
    ofstream write("/Users/mzaidt/Documents/PF (UET)/Auction_System/num_rec.txt");
    if (write.is_open())
    {
        write << numRec << endl;
        write.close();
    }
}

int readNumRecFromFile()
{
    int numRec = 0;
    ifstream read("/Users/mzaidt/Documents/PF (UET)/Auction_System/num_rec.txt");
    if (read.is_open())
    {
        read >> numRec;
        read.close();
    }
    return numRec;
}

void header()
{
    cout << endl;
    cout << "\t\t ____________Auction System___________" << endl;
    cout << "\t\t|         Muhammad Zaid Tahir         |" << endl;
    cout << "\t\t|             2023-CS-426             |" << endl;
    cout << "\t\t|    muhammadzaidtahir90@gmail.com    |" << endl;
    cout << "\t\t|            0336-7339855             |" << endl;
    cout << "\t\t|_____________________________________|" << endl;
}
void menu()
{
    cout << " ___________________________________________" << endl;
    cout << "|     1. Add Product                        |" << endl;
    cout << "|     2. Start Auction                      |" << endl;
    cout << "|     3. Show All Products                  |" << endl;
    cout << "|     4. Filter Products(According Category)|" << endl;
    cout << "|     5. Filter Products(According Date)    |" << endl;
    cout << "|     6. Show Summary(Sold Products)        |" << endl;
    cout << "|     7. Delete A Record                    |" << endl;
    cout << "|     8. Exit                               |" << endl;
    cout << "|___________________________________________|" << endl;
}
void AddProduct(ProductInfo info, int NUM_REC)
{
    ofstream write("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt", ios::app);
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
    cout << "Enter Date (dd mm yyyy): ";
    cin >> info.date.day >> info.date.month >> info.date.year;

    if (!write.is_open())
    {
        cout << "File Not Opened." << endl;
    }
    else
    {
        write << info.no << " "
              << info.name << endl;
        write << info.productName << endl;
        write << info.productType << endl;
        write << info.cnic << endl;
        write << info.initialPrice << endl;
        write << info.date.day << "/";
        write << info.date.month << "/";
        write << info.date.year << endl;
    }
}
void startAuction(ProductInfo &info, string productName)
{
    ofstream writeHistory("/Users/mzaidt/Documents/PF (UET)/Auction_System/history.txt", ios::app);
    ifstream readProduct("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    ofstream writeTemp("/Users/mzaidt/Documents/PF (UET)/Auction_System/temp.txt");
    if (!readProduct.is_open() || !writeHistory.is_open() || !writeTemp.is_open())
    {
        cout << "File Not Opened." << endl;
    }
    else
    {
        while (readProduct >> info.no)
        {
            readProduct.ignore();
            getline(readProduct, info.name);
            getline(readProduct, info.productName);
            getline(readProduct, info.productType);
            getline(readProduct, info.cnic);
            readProduct >> info.initialPrice;
            readProduct.ignore();
            readProduct >> info.date.day;
            readProduct.ignore();
            readProduct >> info.date.month;
            readProduct.ignore();
            readProduct >> info.date.year;
            readProduct.ignore();

            if (productName == info.productName)
            {
                cout << info.no << " "
                     << "Name: " << info.name << endl;
                cout << "Product Name: " << info.productName << endl;
                cout << "Product Type: " << info.productType << endl;
                cout << "CNIC: " << info.cnic << endl;
                cout << "Initial Price: " << info.initialPrice << endl;
                cout << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;

                char c;
                cout << "Are you sure you want to start Auction for this product? (Y/N): ";
                cin >> c;

                if (c == 'Y' || c == 'y')
                {
                    int previousBid = info.initialPrice;
                    while (true)
                    {
                        cout << "Enter Your Bid: ";
                        cin >> info.finalPrice;
                        if (info.finalPrice <= previousBid)
                        {
                            cout << "Bid must be greater than the previous bid. Please enter a higher bid! " << endl;
                            continue;
                        }
                        cout << "Current Bid is: " << info.finalPrice << endl;
                        cout << "Want to increase the Bid? (Y/N): ";
                        cin >> c;

                        if (c == 'N' || c == 'n')
                        {
                            cout << "Product Sold At " << info.finalPrice << endl;
                            cout << "Enter Buyer Name: ";
                            cin.ignore();
                            getline(cin, info.buyerName);
                            cout << "Enter Buyer CNIC: ";
                            getline(cin, info.buyerCnic);
                            cout << "Enter Date of Purchase (dd mm yyyy): ";
                            cin >> info.datePurchase.day >> info.datePurchase.month >> info.datePurchase.year;

                            writeHistory << info.no << " " << info.name << endl;
                            writeHistory << info.productName << endl;
                            writeHistory << info.productType << endl;
                            writeHistory << info.cnic << endl;
                            writeHistory << info.buyerName << endl;
                            writeHistory << info.buyerCnic << endl;
                            writeHistory << info.initialPrice << endl;
                            writeHistory << info.finalPrice << endl;
                            writeHistory << info.datePurchase.day << "/" << info.datePurchase.month << "/" << info.datePurchase.year << endl;

                            break;
                        }

                        previousBid = info.finalPrice;
                    }
                }
                else
                {
                    writeTemp << info.no << " " << info.name << endl;
                    writeTemp << info.productName << endl;
                    writeTemp << info.productType << endl;
                    writeTemp << info.cnic << endl;
                    writeTemp << info.initialPrice << endl;
                    writeTemp << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;
                }
            }
            else
            {
                writeTemp << info.no << " " << info.name << endl;
                writeTemp << info.productName << endl;
                writeTemp << info.productType << endl;
                writeTemp << info.cnic << endl;
                writeTemp << info.initialPrice << endl;
                writeTemp << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;
            }
        }
    }

    readProduct.close();
    writeHistory.close();
    writeTemp.close();

    remove("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    rename("/Users/mzaidt/Documents/PF (UET)/Auction_System/temp.txt", "/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
}

void ShowAllProduct(ProductInfo info)
{
    int flag = 0;
    ifstream read("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    if (!read.is_open())
    {
        cout << "File Not Opened." << endl;
    }
    else
    {
        while (read >> info.no)
        {
            flag = 1;
            read.ignore();
            getline(read, info.name);
            getline(read, info.productName);
            getline(read, info.productType);
            getline(read, info.cnic);
            read >> info.initialPrice;
            read.ignore();
            read >> info.date.day;
            read.ignore();
            read >> info.date.month;
            read.ignore();
            read >> info.date.year;

            read.ignore();
            cout << info.no << endl;
            cout << "Name: " << info.name << endl;
            cout << "Product Name: " << info.productName << endl;
            cout << "Product Type: " << info.productType << endl;
            cout << "CNIC: " << info.cnic << endl;
            cout << "Initial Price: " << info.initialPrice << endl;
            cout << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;
            cout << "----------------------------------------" << endl;
        }
        if (flag == 0)
        {
            cout << "No Products Available." << endl;
        }
    }
    read.close();
}
void ShowSummary(ProductInfo info)
{
    int flag = 0;
    ifstream read("/Users/mzaidt/Documents/PF (UET)/Auction_System/history.txt");
    if (!read.is_open())
    {
        cout << "File Not Opened." << endl;
    }
    else
    {
        while (read >> info.no)
        {
            flag = 1;
            read.ignore();
            getline(read, info.name);
            getline(read, info.productName);
            getline(read, info.productType);
            getline(read, info.cnic);
            getline(read, info.buyerName);
            getline(read, info.buyerCnic);
            read >> info.initialPrice;
            read >> info.finalPrice;
            read.ignore();
            read >> info.datePurchase.day;
            read.ignore();
            read >> info.datePurchase.month;
            read.ignore();
            read >> info.datePurchase.year;
            read.ignore();

            cout << info.no << endl;
            cout << "Name: " << info.name << endl;
            cout << "Product Name: " << info.productName << endl;
            cout << "Product Type: " << info.productType << endl;
            cout << "CNIC: " << info.cnic << endl;
            cout << "Buyer's Name: " << info.buyerName << endl;
            cout << "Buyer's CNIC: " << info.buyerCnic << endl;
            cout << "Initial Price: " << info.initialPrice << endl;
            cout << "Sold Price: " << info.finalPrice << endl;
            cout << "Date of Purchase: " << info.datePurchase.day << "/" << info.datePurchase.month << "/" << info.datePurchase.year << endl;

            cout << "----------------------------------------" << endl;
        }
        if (flag == 0)
        {
            cout << "No Products Available." << endl;
        }
    }
}
void deleteRecord(ProductInfo info)
{
    ifstream read("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    ofstream write("/Users/mzaidt/Documents/PF (UET)/Auction_System/temp.txt");
    int flag = 0;
    string name;
    cout << "Enter Name of product that you want to delete: ";
    cin.ignore();
    getline(cin, name);
    if (!read.is_open() || !write.is_open())
    {
        cout << "File Not Opened." << endl;
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
            read >> info.date.day;
            read.ignore();
            read >> info.date.month;
            read.ignore();
            read >> info.date.year;

            if (name == info.productName)
            {
                flag = 1;
            }
            else
            {
                write << info.no << " "
                      << info.name << endl;
                write << info.productName << endl;
                write << info.productType << endl;
                write << info.cnic << endl;
                write << info.initialPrice << endl;
                write << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;
            }
        }
        if (flag == 1)
        {
            cout << "Record Deleted" << endl;
        }
        else
        {
            cout << "Record Not Found" << endl;
        }
        write.close();
        read.close();
        remove("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
        rename("/Users/mzaidt/Documents/PF (UET)/Auction_System/temp.txt", "/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    }
}
void showProductByCategory(ProductInfo info)
{
    int flag = 0;
    ifstream read("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    string category;
    cout << "Enter Category for which you want to search the products: ";
    cin.ignore();
    getline(cin, category);
    if (!read.is_open())
    {
        cout << "File Not Opened." << endl;
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
            read >> info.date.day;
            read.ignore();
            read >> info.date.month;
            read.ignore();
            read >> info.date.year;

            read.ignore();
            if (category == info.productType)
            {
                flag = 1;
                cout << info.no << endl;
                cout << "Name: " << info.name << endl;
                cout << "Product Name: " << info.productName << endl;
                cout << "Product Type: " << info.productType << endl;
                cout << "CNIC: " << info.cnic << endl;
                cout << "Initial Price: " << info.initialPrice << endl;
                cout << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;

                cout << "----------------------------------------" << endl;
            }
        }
        if (flag == 0)
        {
            cout << "No Product found for " << category << " Category" << endl;
        }
    }
}
void showProductByDate(ProductInfo info)
{
    int flag = 0;
    ifstream read("/Users/mzaidt/Documents/PF (UET)/Auction_System/product.txt");
    Date dateToSearch;
    cout << "Enter Specific Date for which you want to search the products(dd mm yyyy): ";
    cin >> dateToSearch.day >> dateToSearch.month >> dateToSearch.year;

    if (!read.is_open())
    {
        cout << "File Not Opened." << endl;
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
            read >> info.date.day;
            read.ignore();
            read >> info.date.month;
            read.ignore();
            read >> info.date.year;

            read.ignore();
            if (dateToSearch.day == info.date.day && dateToSearch.month == info.date.month && dateToSearch.year == info.date.year)
            {
                flag = 1;
                cout << info.no << endl;
                cout << "Name: " << info.name << endl;
                cout << "Product Name: " << info.productName << endl;
                cout << "Product Type: " << info.productType << endl;
                cout << "CNIC: " << info.cnic << endl;
                cout << "Initial Price: " << info.initialPrice << endl;
                cout << info.date.day << "/" << info.date.month << "/" << info.date.year << endl;

                cout << "----------------------------------------" << endl;
            }
        }
        if (flag == 0)
        {
            cout << "No Product found for " << dateToSearch.day << "/" << dateToSearch.month << "/" << dateToSearch.year << " Specific Date." << endl;
        }
    }
}

int main()
{

    ProductInfo product;
    ofstream write;
    ifstream read;

    string productName;
    int find, f;
    int choice;
    int NUM_REC = readNumRecFromFile();
    header();
    do
    {

        menu();
        cout << "Enter your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            AddProduct(product, NUM_REC);
            NUM_REC++;
            break;
        case 2:
            cout << "Enter Product name for which you want to Start Auction: ";
            cin.ignore();
            getline(cin, productName);
            startAuction(product, productName);
            break;
        case 3:
            ShowAllProduct(product);
            break;
        case 4:
            showProductByCategory(product);
            break;
        case 5:
            showProductByDate(product);
            break;
        case 6:
            ShowSummary(product);
            break;
        case 7:
            deleteRecord(product);
            break;
        case 8:
            cout << "Closing The System..........";
            break;
        default:
            cout << "Invalid Choice";
        }

    } while (choice != 8);

    writeNumRecToFile(NUM_REC);
}