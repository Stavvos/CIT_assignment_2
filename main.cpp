/*written by Liam Henry 2018
 cit 020625*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


//Base class
class Product
{
string title;
string surname;
string isbn;
double wholesalePrice;
public:
void setAttributes (string,string,string,double);
double getWholesalePrice();
void setTitle(string);
string getTitle();
string getSurname();
string getIsbn();
Product();
~Product();
};

void Product::setTitle (string inOrderTitle)
{
   title = inOrderTitle;
};

double Product::getWholesalePrice()
{
    return wholesalePrice;
}

string Product::getTitle()
{
    return title;
}

string Product::getSurname()
{
    return surname;
}

string Product::getIsbn()
{
    return isbn;
}

void Product::setAttributes(string inTitle, string inSurname, string inIsbn, double inWholesalePrice)
{
title = inTitle;
surname = inSurname;
isbn = inIsbn;
wholesalePrice = inWholesalePrice;
};

Product::Product ()
{

};

Product::~Product ()
{

};

//derived class
class Stock : public Product
{
double retailPrice;
char bookFormat;
int stockLevel;
public:
void setAttributes(string,string,string,double, char, int);
double initalizeRetailPrice();
char getBookFormat();
double getRetailPrice();
int getStockLevel();
void setOrders(string, int);
Stock();
~Stock ();
};

void Stock::setOrders (string inOrderTitle, int inOrderStock)
{
Product::setTitle(inOrderTitle);
stockLevel = inOrderStock;
}

char Stock::getBookFormat()
{
    return bookFormat;
}

double Stock::getRetailPrice()
{
    return retailPrice;
}

int Stock::getStockLevel()
{
    return stockLevel;
}


double Stock::initalizeRetailPrice() {
	if (bookFormat == 'a')
		retailPrice = (getWholesalePrice() * 0.43) + getWholesalePrice();
	else
		if (bookFormat == 'e')
			retailPrice = (getWholesalePrice() * 0.08) + getWholesalePrice();
		else
			if (bookFormat == 'h')
				retailPrice = (getWholesalePrice() * 0.45) + getWholesalePrice();
			else
				if (bookFormat == 's')
					retailPrice = (getWholesalePrice() * 0.27) + getWholesalePrice();
 return retailPrice;
}

void Stock::setAttributes(string inTitle, string inSurname, string inIsbn, double inWholesalePrice, char inBookFormat, int inStockLevel)
{
Product::setAttributes(inTitle, inSurname, inIsbn, inWholesalePrice);
bookFormat = inBookFormat;
stockLevel = inStockLevel;
};

Stock::Stock()
{

};

Stock::~Stock()
{

};

//function declaration
void print (Stock*);
void enterBook (Stock*);
void inputArray (Stock*);
int Delete(Stock*, int);
void orders(Stock*);

int main()
{
   string Title = "####", Name = "####", Isbn = "####";
    double WholesalePrice = 0.00;
    char yesOrNo, BookFormat = 'a'; //had to initialise  Book format to 'a' to prevent a memory address see comment below
    int ArraySize = 22, StockLevel = 0;
    Stock Array [ArraySize];
    /*i did this to prevent a memory address popping up when the delete function is run,
     but no new book has been added to the array. */
    Array[0].setAttributes(Title, Name, Isbn, WholesalePrice, BookFormat, StockLevel);

    ifstream inData ("products.txt"); //create inData variable

    if (!inData) //test to see if prodcts.txt exists
    {
     cout << "products.txt not found, program will now end.";
     return 1;
    }

    ifstream inData2 ("orders.txt"); //create inData2 variable

    if (!inData2) //test to see if the orders.txt exists
    {
        cout << "orders.txt not found, program will now end.";
    return 1;
    }

    inputArray(Array); //run the input array function

    cout << "Would you like to enter a new book? Lower case y for yes, any other character for no: " << endl;
    cin >> yesOrNo;

    // a do while loop used for a yes or no option for the user
    //this is for the insert new book function
    if (yesOrNo == 'y')
    {
        do
            {
              enterBook(Array);
                yesOrNo = 'n';
                cout << endl;
            }
                  while (yesOrNo == 'y');
    }

    //a do while loop for a yes or no for the orders function

    cout << "Would you like to view an orders report? Lower case y for yes, any other character for no: " << endl;
    cin >> yesOrNo;

    if (yesOrNo == 'y')
    {
        do
            {
              orders(Array);
                yesOrNo = 'n';
                cout << endl;
            }
                  while (yesOrNo == 'y');
    }



   print (Array); //run the print function
    //yes or no for delete
   cout << "Would you like to delete an array element? Lower case y for yes, any other character for no: " << endl;
    cin >> yesOrNo;

    if (yesOrNo == 'y')
    {
        do
            {
                ArraySize = Delete(Array, ArraySize); //update array size within the main
                yesOrNo = 'n';
                   for (int i = 0; i < ArraySize; i++) //display the updated array
                {
                    cout << i << " " << Array[i].getTitle() << " " << Array[i].getBookFormat() << " " << setprecision(2) << fixed <<Array[i].initalizeRetailPrice();
                    cout << endl;
                }
            }
                  while (yesOrNo == 'y');
    }


    inData.close(); //close in file
    inData2.close(); //close in file
    return 0;
}

void orders (Stock *inArray) // this function determines if an order's information matches product data
{
    string title;
    int stock, temp;
    Stock OrdersArray [5]; //create an array to hold information from the orders.txt file
    ifstream inData ("orders.txt");

    for (int i = 0; i < 5; i++) // inputs data from orders.txt into the array
    {
        inData >> title >> stock;
        OrdersArray[i].setOrders(title, stock);
    }

    for (int j = 0; j < 5; j++) //determines if stock if product exists, and if stock is availible.
    {
        temp = 0;

        for (int i = 0; i < 22; i++)
        {
          if (OrdersArray[j].getTitle() == inArray[i].getTitle() && inArray[i].getStockLevel() >= OrdersArray[j].getStockLevel())
          {
            cout << inArray[i].getTitle() << " is availible and there's enough stock to fullfill the order" << endl;
            temp = 1; // this is used to determine if the book was found
            //condition for availible product and enough stock
          }
          else if (OrdersArray[j].getTitle() == inArray[i].getTitle() && OrdersArray[j].getStockLevel() > inArray[i].getStockLevel())
          {
              cout << OrdersArray[j].getTitle() << " is availible but there's not enough stock to fullfill the order" << endl;
            temp = 1;// this is used to determine if the book was found
            //condition for availible product, but not enough stock
          }
        }
    if (temp == 0) //statement used for the condition in which the book was not found
    {
        cout << OrdersArray[j].getTitle() << " is not availible at Bibloden" << endl;
        //condition if the product doesnt exist
    }
    }

    inData.close(); //close inData

};

int Delete(Stock *inArray, int counter) //delete function
{

int element; //the element for the array

cout << "Please enter the element of the array you wish to be deleted:" << endl;
cin >> element; //users input

counter --; // decrease the size of the array by one

for (int i = element; i < counter; i++)
{
    // copy the contents of the next value stored in the array, to the current value in the array.
    inArray [i] = inArray[i+1];
}

return counter; //  return the size of the array
};

void inputArray(Stock *inArray) //function for inputting data into array from products.txt
{
    string inSurname, inTitle, inIsbn;
    char inBookFormat;
    double inRetailPrice;
    int inStockLevel;

ifstream inData ("products.txt");
    //the top line in the for loop copies each word from the text file, into the appropriate variable
    //the bottom line uses the setAttributes function from the stock class to create the array of objects.

    for (int i = 1; i < 22; i++)
    {
        inData >> inSurname >> inTitle >> inStockLevel >> inBookFormat >> inIsbn >> inRetailPrice;
        inArray[i].setAttributes(inTitle, inSurname, inIsbn,inRetailPrice, inBookFormat, inStockLevel);
    }

    inData.close(); //close inData
};


void enterBook(Stock *inArray) //enter book function
{
    //simple cin into appropriate variables
    //variables used for the setAttributes function
    //inArray element set to 0 to ensure insertion happens at the start of the array
    string tempName, tempTitle, tempIsbn;
    char tempBookFormat;
    double tempWholesalePrice;
    int  tempStockLevel;
    cout << "Please enter in the new book in the following order:" << endl;
    cout << "ISBN: (String)  "; cin >> tempIsbn;
    cout << "Title: (String)  "; cin >>tempTitle;
    cout << "Authour's Name: (String)  "; cin >>tempName;
    cout << "Whole sale price: (Double)  "; cin>>tempWholesalePrice;
    cout << "Book format: (Char)  "; cin >>tempBookFormat;
    cout << "Stock level: (int)  "; cin >>tempStockLevel;
    inArray[0].setAttributes(tempTitle,tempName, tempIsbn, tempWholesalePrice, tempBookFormat, tempStockLevel);
};

void print (Stock *inArray) //function for printing an output file
{
    ofstream outFile ("output.txt"); //open output file

    //formatting for the output file
    outFile << "AudioBooks:" << endl;
	outFile << setw(180) << setfill('-') << "-" << endl;
	outFile << setfill(' ') << setw(15) << left << "ISBN" << setfill(' ') << setw(30) << left << "Title" << setw(15) <<left << "Author" << setw(15) << left << "Retail Cost" << setfill(' ') << setw(34) << right << "Quantity in stock" << "\n\n";

    //a loop used to determine if a book should be printed under the appropriate formatting,i.e AudioBooks
    for (int i = 0; i < 21; i++)
{
    if (inArray[i].getBookFormat() == 'a') //this test determines what the book type is
    {
    outFile << setfill(' ') << setw (15) << left << inArray[i].getIsbn() << setw (30) << left << inArray[i].getTitle()
    << setw (15) << left  << inArray[i].getSurname() << '$' <<setw(31) << left << fixed
    << setprecision(2) << inArray[i].initalizeRetailPrice() << setw (30) << left << inArray[i].getStockLevel();
    outFile << endl;
    }
}

    outFile << "\n\n";
	outFile << "eBooks:" << endl;
	outFile << setw(180) << setfill('-') << "-" << endl;
	outFile << setfill(' ') << setw(15) << left << "ISBN" << setfill(' ') << setw(30) << left << "Title" << setw(15) <<left << "Author" << setw(16) << left << "Retail Cost" << setfill(' ') <<setw(32) << right << "Quantity in stock" << "\n\n";


      for (int i = 0; i < 21; i++)
{
    if (inArray[i].getBookFormat() == 'e')
    {
    outFile << setfill(' ') << setw (15) << left << inArray[i].getIsbn() << setw (30) << left << inArray[i].getTitle()
    << setw (15) << left  << inArray[i].getSurname() << '$' << setw(30) << left << fixed
    << setprecision(2) << inArray[i].initalizeRetailPrice() << setw (30) << left << inArray[i].getStockLevel();
    outFile << endl;
    }
}

    outFile << "\n\n";
	outFile << "Hardback:" << endl;
	outFile << setw(180) << setfill('-') << "-" << endl;
	outFile << setfill(' ') << setw(15) << left << "ISBN" << setfill(' ') << setw(30) << left << "Title" << setw(15) <<left << "Author" << setw(16) << left << "Retail Cost" << setfill(' ') <<setw(32) << right << "Quantity in stock" << "\n\n";

	     for (int i = 0; i < 21; i++)
{
    if (inArray[i].getBookFormat() == 'h')
    {
    outFile << setfill(' ') << setw (15) << left << inArray[i].getIsbn() << setw (30) << left << inArray[i].getTitle()
    << setw (15) << left  << inArray[i].getSurname() << '$' << setw(30) << left << fixed
    << setprecision(2) << inArray[i].initalizeRetailPrice() << setw (30) << left << inArray[i].getStockLevel();
    outFile << endl;
    }
}

    outFile << "\n\n";
	outFile << "Paperback:" << endl;
	outFile << setw(180) << setfill('-') << "-" << endl;
	outFile << setfill(' ') << setw(15) << left << "ISBN" << setfill(' ') << setw(30) << left << "Title" << setw(15) <<left << "Author" << setw(16) << left << "Retail Cost" << setfill(' ') <<setw(32) << right << "Quantity in stock" << "\n\n";

	     for (int i = 0; i < 21; i++)
{
    if (inArray[i].getBookFormat() == 's')
    {
   outFile << setfill(' ') << setw (15) << left << inArray[i].getIsbn() << setw (30) << left << inArray[i].getTitle()
    << setw (15) << left  << inArray[i].getSurname() << '$' << setw(30) << left << fixed
    << setprecision(2) << inArray[i].initalizeRetailPrice() << setw (30) << left << inArray[i].getStockLevel();
    outFile << endl;
    }
}

outFile.close(); //close the output file
};



