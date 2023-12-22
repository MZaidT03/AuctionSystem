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
    float initialPrice;
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
void AddProduct(ProductInfo product[])
{
    product[NUM_REC].no = NUM_REC;
    cin.ignore();
    cout << "Enter Your Name: ";
    getline(cin, product[NUM_REC].name);
    cout << "Enter Product Name: ";
    getline(cin, product[NUM_REC].productName);
    cout << "Enter Product Type: ";
    getline(cin, product[NUM_REC].productType);
    cout << "Enter Your CNIC: ";
    getline(cin, product[NUM_REC].cnic);
    cout << "Enter Initial: ";
    cin >> product[NUM_REC].initialPrice;
    NUM_REC += 1;
}
void startAuction(ProductInfo info[])
{
    int finalPrice[40] = {0};
    string productName;
    cin.ignore();
    cout << "Enter Product name for which you want to Start Auction: ";
    getline(cin, productName);

    for (int i = 0; i < NUM_REC; i++)
    {
        if (productName == info[i].productName)
        {
            cout << info[i].no << " "
                 << "Name: " << info[i].name << endl;
            cout << "Product Name: " << info[i].productName << endl;
            cout << "Product Type: " << info[i].productType << endl;
            cout << "CNIC: " << info[i].cnic << endl;
            cout << "Initial Price: " << info[i].initialPrice << endl;

            char c;
            cout << "Are you sure you want to start Auction for this product. (Y/N)";
            cin >> c;

            if (c == 'Y' || c == 'y')
            {
                int j = 0;
                int previousBid = info[i].initialPrice; // Initialize previousBid with initialPrice

                while (true)
                {
                    cout << "Enter Your Bid: ";
                    cin >> finalPrice[j];

                    // Check if the current bid is greater than the previous bid
                    if (finalPrice[j] <= previousBid)
                    {
                        cout << "Bid must be greater than the previous bid. Please enter a higher bid." << endl;
                        continue; // Continue the loop without updating previousBid
                    }

                    cout << endl
                         << "Current Bid is: " << finalPrice[j] << endl;
                    cout << "Want to increase the Bid (Y/N): ";
                    cin >> c;

                    if (c == 'N' || c == 'n')
                    {
                        cout << "Product Sold At " << finalPrice[j] << endl;

                        ofstream write("history.txt", ios::app);
                        if (!write.is_open())
                        {
                            cout << "File Not Opened.";
                        }
                        else
                        {
                            write << info[i].no << " "
                                  << "Name: " << info[i].name << endl;
                            write << "Product Name: " << info[i].productName << endl;
                            write << "Product Type: " << info[i].productType << endl;
                            write << "CNIC: " << info[i].cnic << endl;
                            write << info[i].initialPrice << endl;
                        }

                        break; // Exit the loop when auction is complete
                    }

                    // Update previousBid only if the current bid is greater
                    previousBid = finalPrice[j];

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

void ShowAllProduct(ProductInfo product[])
{
    for (int i = 0; i < NUM_REC; i++)
    {
        cout << "\nName: " << product[i].name << endl;
        cout << "Product Name: " << product[i].productName << endl;
        cout << "Product Type: " << product[i].productType << endl;
        cout << "CNIC: " << product[i].cnic << endl;
        cout << "Initial Price: " << product[i].initialPrice << endl;
    }
}
void ShowSummary()
{
    ProductInfo info;
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

            read.ignore();

            cout << info.no << endl;
            cout << info.name << endl;
            cout << info.productName << endl;
            cout << info.productType << endl;
            cout << info.cnic << endl;
            cout << "Initial Price: " << info.initialPrice << endl;
        }
    }
}
int main()
{

    ProductInfo product[MAX_REC];
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
            ShowSummary();
            break;
        case 5:
            exit(0);
            break;
        }

    } while (choice != 0);
}