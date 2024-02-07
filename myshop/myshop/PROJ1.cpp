// This is a shop management console based system using data structures and algorithm in C++
/*
Perform various function of a shop like inserting a new product in shop, easy to locate an item using hashing,
generating bill of a customer, modifying product details, removing a product, checking the stock availability,
reversing a bill also, display all products or a particular product and many more.
*/

// Name of this shop is MyShop :)

#include<bits/stdc++.h>
#define f(i,a,n) for(i=a;i<n;i++)
using namespace std;
// declaring structure for generating a bill
struct bill
{
    int billid; // bill id of the customer
    string custname;  // name of the customer
    string pname;  // name of the product
    int quantity; // quantity of product
    int price; // price of the product
    int netamount;
};
// holds data for a new product entry in the shop
struct newproduct
{
    int pno; // product number
	string pname; // product name
	float price;  // price of the product
	int quantity,shelfno,rowno;  // quantity and location of product
};
struct newproduct h[26][100];  // 26 size bacause we are taking just the first character of product name for hashing
int hashkey(string s)  // generating hashkey for a product
{
    int sum=0;
    int key=0;
    for(int j=0;j<s.length();j++)
    {
        sum=sum+int(s[j]); // hashkey generation by summing the ascii value of all characters in string
    }
    key=sum%100; // hash function is hash(x)= x%100
    return key; // return that key value
}
void generatebill() // generate bill function. This will generate a bill receipt for customer
{
    struct bill b;
    int i=0,j,k=0,key=0,flag=0;
    string product_name,cname;
    FILE *f1;
    fflush(stdin);
    f1=fopen("bill.dat","ab"); // opening bill file
    cout<<endl<<"Please Enter The Bill Number: ";
    cin>>b.billid;// input the bill number
    cout<<endl<<"Please Enter The Name of The Customer: ";
    fflush(stdin);
    cin>>b.custname; // input customer name
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>b.pname; // input product name
    transform((b.pname).begin(),(b.pname).end(),(b.pname).begin(),::toupper);// transform product name to uppercase
    key=hashkey(b.pname); // generating hash key for the product name
    while(h[int(b.pname[0])-65][key].pname!=(b.pname))
    {
        if(k > 50) // check if the product is Available  in the shop or not
        {
            cout<<"Product not Available"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(b.pname[0])-65;
    j=key;
    if (flag==0) // if stock is available then generate the bill after asking quantity purchased
    {
      cout<<"Stock Available: "<<h[i][j].quantity<<endl;
      cout<<"Enter Quantity:  ";
      cin>>b.quantity;
      b.price=h[i][j].price;
      b.netamount=b.price*b.quantity; // calculate total amount to be paid by customer
      if (b.quantity>h[i][j].quantity) // if not enough quantity available
        cout<<"Order Declined! Not enough stock available!";
      else
      {
        cout<<"\nBillNo: "<<b.billid<<endl;
        cout<<"Customer Name: "<<b.custname<<endl;
        cout<<"Product Name: "<<b.pname<<endl;
        cout<<"Price: "<<b.price<<endl;
        cout<<"Quantity: "<<b.quantity<<endl;
        cout<<"NetAmount: "<<b.netamount<<endl;
        h[i][j].quantity=h[i][j].quantity-b.quantity;
        fwrite(&b,1,sizeof(struct bill),f1); // update the data for that item i.e. the quantity remained
      }
    }
    fclose(f1); // closing the file
}
// function to print all the bills i.e. the bill book
void billbook()
{
    struct bill b;
    int i=0,j,k=0,key=0,flag=0;
    string product_name,cname;
    FILE *f1; // file pointer
    f1=fopen("bill.dat","rb"); // opening file for reading
    while(fread(&b,1,sizeof(struct bill),f1))
    {
        // print all the bill data
        cout<<"\nBillNo: "<<b.billid<<endl;
        cout<<"Customer Name: "<<b.custname<<endl;
        cout<<"Product Name: "<<b.pname<<endl;
        cout<<"Price: "<<b.price<<endl;
        cout<<"Quantity: "<<b.quantity<<endl;
        cout<<"NetAmount: "<<b.netamount<<endl;
    }
    fclose(f1);// closing the file
}
// this function will reverse a generated bill
void reversebill()
{
    struct bill b;
    int billno;
    int i=0,j,k=0,key=0,flag=0,flag1=0;
    string product_name,cname;
    ifstream f1; // opening file for reading
    cout<<"\nEnter Bill Id to be reversed: ";
    cin>>billno; // input the customer bill id
    f1.open("bill.dat",ios::in | ios::binary);
    while(f1.read((char *) & b,sizeof(b)))
    {
        if (b.billid==billno) // check if bill has ever been generated or not
       {
          key=hashkey(product_name); // generate hashkey
          b.pname=product_name;
          while(h[int(product_name[0])-65][key].pname!=product_name)
          {
             if(k > 50)
             {
                cout<<"Product not Available"<<endl;
                flag=1;
                break;
             }
             key=(key+(k*k))%100; // updating key until product is found
             k++;
          }
          i=int(product_name[0])-65;
          j=key;
          if (flag==0)
          {
              h[i][j].quantity=h[i][j].quantity+b.quantity;// add quantity purchased to remaining quantity
              cout<<"\nBill successfully Reversed";
          }
          flag1=1;
          break;
       }
    }
    if (flag1==0)
    cout<<"\nBill not found! ";
    f1.close();// closing the file
}
// this function will create and insert a new product in our shop
void createproduct()
{
		int product_number,product_quantity,shelf,row;
		int i=0,key=0,flag=0;
	    float  product_price;
	    string product_name;
		cout<<endl<<"Please Enter The Product Number: ";
		cin>>product_number; // input product number
		cout<<endl<<"Please Enter The Name of The Product: ";
		cin>>product_name; // input product name
		cout<<endl<<"Please Enter The Price of The Product: ";
		cin>>product_price; // input product price
		cout<<endl<<"Please Enter Total Quantity of The Product: ";
		cin>>product_quantity; // input quantity in stock
		cout<<endl<<"Please Enter Shelf Number: ";
		cin>>shelf; // input shelf number
		cout<<endl<<"Please Enter row Number";
		cin>>row; // input row number in that shelf
		transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
		key=hashkey(product_name); // now generate hash key for that product to store
		while(h[int(product_name[0])-65][key].pno!='\0')
        {
            key=(key+(i*i))%100;
            if (i>500)
            {
                cout<<"no space available"; // if already that space is filled
                break;
                flag=1;
            }
            i++;}
		if (flag==0)
		// insert at that location our new product
        {h[int(product_name[0])-65][key]={product_number,product_name,product_price,product_quantity,shelf,row};
		//cout<<key<<endl;
        }
}
//this function will display all details of all products available in MYSHOP
void displayallproducts()
{
    int i,j;
    for(i=0;i<26;i++) // hash table size
    {
        for(j=0;j<100;j++)
        {
            if(h[i][j].pno!='\0')
            {
                // display product details
                cout<<"product No:"<<h[i][j].pno<<endl;
                cout<<"Name: "<<h[i][j].pname<<endl;
                cout<<"Price: "<<h[i][j].price<<endl;
                cout<<"Quantity: "<<h[i][j].quantity<<endl;
                cout<<"shelfno: "<<h[i][j].shelfno<<endl;
                cout<<"Rowno: "<<h[i][j].rowno<<"\n"<<endl;
                //cout<<"i,j"<<i<<" "<<j<<endl;
            }
        }
    }
}
// this function will automatically check all item stocks in the shop
// and prints those items whose stock needs to be added
void autocheckstock()
{
    int i,j,flag=0;
    for(i=0;i<26;i++)
    {// check whole hash table
        for(j=0;j<100;j++)
        {
            if(h[i][j].pno!='\0' && h[i][j].quantity<5) // if item quantity is less tahn 5 then print its details and
            //tell the shopkeeper that this is soon going to be out of stock
            {
                cout<<"product No:"<<h[i][j].pno<<endl;
                cout<<"Name: "<<h[i][j].pname<<endl;
                cout<<"Price: "<<h[i][j].price<<endl;
                cout<<"Quantity: "<<h[i][j].quantity<<endl;
                cout<<"shelfno: "<<h[i][j].shelfno<<endl;
                cout<<"Rowno: "<<h[i][j].rowno<<"\n"<<endl;
                //cout<<"i,j"<<i<<" "<<j<<endl;
            }
        }
    }
    if(flag==1){
    cout<<"The above items are short in stock!\n";
    cout<<"Please maintain stock as soon as possible!\n";
    }
    else
    cout<<"Stock is full.\n"; // else print stock is full
}
// this function will print details of a particular item instead of whole shop items
void showproduct()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name; // input the name of the product
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper); // transform that to uppercase
    key=hashkey(product_name); // generate hashkey
    //cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
    cout<<"product No:"<<h[i][j].pno<<endl;
    cout<<"Name: "<<h[i][j].pname<<endl;
    cout<<"Price: "<<h[i][j].price<<endl;
    cout<<"Quantity: "<<h[i][j].quantity<<endl;
    cout<<"shelfno: "<<h[i][j].shelfno<<endl;
    cout<<"Rowno: "<<h[i][j].rowno<<endl;
    //cout<<"i,j"<<i<<" "<<j<<endl;
    }
}
// this function will check stock of a particular item
void checkstock()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name; // input item name
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    //cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)  // hash table chain size is maximum 50
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {// print name and number of item
    cout<<"product No:"<<h[i][j].pno<<endl;
    cout<<"Name: "<<h[i][j].pname<<endl;
    cout<<"STOCK AVAILABLE: "<<h[i][j].quantity<<endl;
    }
}
// this function will find the location of a product i.e. the shelf number and row number
void productloc()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    //cout<<key;
    // find location of the product
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
    cout<<"Name: "<<h[i][j].pname<<endl;
    cout<<"shelfno: "<<h[i][j].shelfno<<endl; // printing shelf no
    cout<<"Rowno: "<<h[i][j].rowno<<endl;
    }
}
// this function will enable the shopkeeper to change or update any item details
void modifyproduct()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name;
    int product_number,product_quantity,shelf,row;
    float product_price;
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name; // input product name
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper); // change it to uppercase
    key=hashkey(product_name); // find the hashkey
    while(h[int(product_name[0])-65][key].pname.compare(product_name)!=0)
    {
        if(k>50) // if hashchain exceeds
        {
            cout<<"Product not Available !"<<endl; // print product is not in list
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    { // print menu that what should be changed
        int c;
        cout<<"\n\tPress 1 to  CHANGE PRICE";
	    cout<<"\n\tPress 2 to UPDATE QUANTITY";
	    cout<<"\n\tPress 3 to UPDATE PRODUCT LOCATION\n";
	    product_number=h[i][j].pno;
	    product_name=h[i][j].pname;
        product_price=h[i][j].price;
        product_quantity=h[i][j].quantity;
        shelf=h[i][j].shelfno;
        row=h[i][j].rowno;
	    cin>>c;
        switch(c) // apply switch case for change
        {
        case 1:
            cout<<endl<<"Please Enter The New Price of The Product: ";
		    cin>>product_price;
		    break;
        case 2:
            cout<<endl<<"Please Enter updated Quantity of The Product: ";
		    cin>>product_quantity;
		    break;
        case 3:
            cout<<endl<<"Please Enter New Shelf Number: ";
		    cin>>shelf;
		    cout<<endl<<"Please Enter New row Number";
		    cin>>row;
		    break;
        default:
            cout<<"Wrong Input!"<<endl;
        }
        // update the changes in original list
        h[int(product_name[0])-65][key]={product_number,product_name,product_price,product_quantity,shelf,row};
    }
}
// this will enable the shopkeeper to remove any particular item from stock
void removeproduct()
{
    int i=0,j,k=0;
    int flag=0,key=0;
    string product_name; // input name of product
    cout<<endl<<"Please Enter The Name of The Product: ";
    fflush(stdin);
    cin>>product_name;
    transform(product_name.begin(),product_name.end(),product_name.begin(),::toupper);
    key=hashkey(product_name);
    //cout<<key;
    while(h[int(product_name[0])-65][key].pname!=product_name)
    {
        if(k > 50)
        {
            cout<<"Product not found !"<<endl;
            cout<<"please Enter Correct Product Name"<<endl;
            flag=1;
            break;
        }
        key=(key+(k*k))%100;
        k++;
    }
    i=int(product_name[0])-65;
    j=key;
    if (flag==0)
    {
    cout<<"product No:"<<h[i][j].pno<<endl;
    h[i][j].pno='\0'; // change product number to null
    }
}
// this function is just for graphics like designing the GUI
void kuchh(int n)
 {
     int i;
     f(i,0,n)
    {
        cout<<"*";
    }
 }
void kuch(int n)
 {
     while(n--)
     {
         cout<<" ";
     }
 }
 // this will print MY SHOP in the starting of the program
string printRandomString(int n)
{
    string alphabet( "MYSHOP" );
    string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % 6];
    return res;
}
// this will print the whole admin menu in GUI
void admin_menu()
{
	int option;
	int flag=0;
	kuchh(30);
	while(1)// diaply all options available in MYSHOP
	{cout<<"\n\tPress 1 to INSERT NEW PRODUCT";
	cout<<"\n\tPress 2 to DISPLAY COMPLETE STOCK";
	cout<<"\n\tPress 3 to SHOW PRODUCT DETAILS";
	cout<<"\n\tPress 4 to UPDATE PRODUCT DETAILS";
	cout<<"\n\tPress 5 to REMOVE PRODUCT";
	cout<<"\n\tPress 6 to AUTO CHECK STOCK";
	cout<<"\n\tPress 7 to CHECK STOCK MANUALLY";
	cout<<"\n\tPress 8 to FIND PRODUCT LOCATION";
	cout<<"\n\tPress 9 to GO BACK TO MAIN MENU\n";
    kuchh(30);
    cout<<"\n\n\tOption: ";
	cin>>option; // input user's choice and then call respective fucntion using switch cases
	switch(option)
	{
		case 1:
		    createproduct();
            break;

		case 2:
                displayallproducts();
				break;

		case 3:
				showproduct();
				break;

		case 4:
		    modifyproduct();
		    break;

		case 5: removeproduct();
		        break;

		case 6: autocheckstock();
				break;
        case 7: checkstock();
                break;
        case 8:
            productloc();
            break;
        case 9:
            flag=1;
            break;
        default:admin_menu();
	}
	if (flag==1)
    {
        break;
    }}
}
// displaying the design of data structures and algorithms at start of program
void menu()
{
    int j,i,p;
    for(j=0;j<=10;j++)
    {
        f(i,0,60)
        {
            cout<<printRandomString(1);
            //Sleep(1);
        }
        cout<<"\r";
        f(i,0,60)
        cout<<" ";
        if(j==0)
        { // PRINT DATA
        f(i,0,51)
        {
            if(i>=0&&i<=9)
            {
                cout<<"D";
            }
            if(i==10)
            {
                cout<<"   ";
            }
            if((i>=13&&i<=23)||(i>=40&&i<=50))
            {
                cout<<"A";
            }
            if(i==24)
            {
                cout<<"   ";
            }
            if(i>=27&&i<=36)
            cout<<"T";
            if(i==37)
            {
                cout<<"   ";
            }
        }
    }
    if(j>=1 && j<=9)
    {

        f(i,0,51)
        {

            p=0;
            if(i==0||i==9)
            {
                p=1;
                cout<<"D";
            }
            if(j==5)
           {
            if((i>=13&&i<=23)||(i>=40&&i<=50))
            {
            p=1;
            cout<<"A";
            }
           }
           else {
            if((i==13||i==23)||(i==40||i==50))
            {
            p=1;
            cout<<"A";
            }
            }
            if(i==31)
            {
                p=1;
                i++;
                cout<<"TT";
            }

            if(p==0)
            {
                cout<<" ";
            }
        }
    }
    if(j==10)
    {
        f(i,0,51)
        {
            p=0;
             if(i>=0&&i<=9)
            {
                p=1;
                cout<<"D";
            }

            if((i==13||i==23)||(i==40||i==50))
            {
            p=1;
            cout<<"A";
            }
              if(i==31)
            {
                p=1;
                i++;
                cout<<"TT";
            }
            if(p==0)
            {
                cout<<" ";
            }
        }
    }
    cout<<endl;

    }
    cout<<endl;
    f(j,0,1){
    f(i,0,60)
        {
            cout<<printRandomString(1);
           // Sleep(1);
        }
        cout<<"\r";
        f(i,0,73)
        cout<<" ";
        cout<<"STRUCTURES   AND   ALGORITHM\n";

    }
    cout<<endl<<endl<<endl;
    for(j=0;j<5;j++)
    {
        f(i,0,65)
        {
            cout<<printRandomString(1);
//            Sleep(1);
        }
        cout<<"\r";
        f(i,0,65)
        cout<<" ";
        for(i=0;i<=40;i++)
        {
            p=0;
            if(i==0||i==4)
            {
                p=1;
                cout<<"M";
            }
            if(j==0)
            {
                if(i==7||i==11)
                {p=1;
                    cout<<"Y";
                }
                if(i>=16&&i<=20)
                {
                    p=1;
                    cout<<"S";
                }
                if(i==23||i==27)
                {
                    p=1;
                    cout<<"H";
                }
                if(i>=30&&i<=34)
                {
                    p=1;
                    cout<<"O";
                }
                if(i>=37&&i<=40)
                {
                    p=1;
                    cout<<"P";
                }
            }
            if(j==1)
            {

                if(i==1||i==3)
                {
                    p=1;
                    cout<<"M";
                }
                if(i==8||i==10)
                {
                    p=1;
                    cout<<"Y";
                }

                if(i==16)
                {
                    p=1;
                    cout<<"S";
                }


                if(i==23||i==27)
                {
                    p=1;
                    cout<<"H";
                }

                if(i==30||i==34)
                {
                    p=1;
                    cout<<"O";
                }

                if(i==37||i==40)
                {
                    p=1;
                    cout<<"P";

                }
            }
            if(j==2)
            {
                if(i==2)
                {

                p=1;
                    cout<<"M";
                }
                if(i==9)
                {
                    p=1;
                    cout<<"Y";
                }
                 if(i>=16&&i<=20)
                {
                    p=1;
                    cout<<"S";
                }
                if(i>=23&&i<=27)
                {
                    p=1;
                    cout<<"H";
                }

                if(i==30||i==34)
                {
                    p=1;
                    cout<<"O";
                }

                if(i>=37&&i<=40)
                {
                    p=1;
                    cout<<"P";

                }
            }
            if(j==3)
            {
                if(i==37)
                {
                    p=1;
                    cout<<"P";
                }
                   if(i==9)
                    {
                        p=1;
                        cout<<"Y";
                    }
                    if(i==20)
                    {
                        p=1;
                        cout<<"S";
                    }
                    if(i==23||i==27)
                    {
                        p=1;
                        cout<<"H";
                    }
                    if(i==30||i==34)
                    {
                        p=1;
                        cout<<"O";
                    }
               }
               if(j==4)
               {
                if(i==37)
                {
                    p=1;
                    cout<<"P";
                }
                if(i==9)
                {
                    p=1;
                    cout<<"Y";
                }
                if(i>=16&&i<=20)
                {
                    p=1;
                    cout<<"S";
                }
                if(i==23||i==27)
                {
                    p=1;
                    cout<<"H";
                }
                if(i>=30&&i<=34)
                {
                    p=1;
                    cout<<"O";
                }

               }
            if(p==0)
            {

                cout<<" ";
            }
        }
    cout<<endl;
    }
}
int main()
{
    int i,j,p,t;
    fflush(stdin);
    // set every product number as null in the beginning
    for(i=0;i<26;i++)
    {
        for(j=0;j<100;j++)
        {
            h[i][j].pno='\0';
        }
    }
    ifstream fp1;// file pointer for reading the file
    fp1.open("product.dat",ios::in | ios::binary);
    fp1.read((char *) & h,sizeof(h));
    fp1.close();
    cout<<"PRESS 1 TO EXECUTE:";
    cin>>t;
    cout<<"\r";
    if(t==1)
    {
        menu(); // display the Whole design
    }
    cout<<endl<<endl<<endl;
    string cname;
    int ccontactno;
    kuchh(67);
    cout<<"WE ARE GRATIFY TO SEE YOU";
    kuchh(70);
    cout<<endl;
    cout<<endl;
    cout<<"PLEASE ENTER YOUR DETAIL::\nYOUR FIRST NAME : ";
    cin>>cname; // input first name of user
    cin.ignore();
    cout<<"CONTACT NUMBER : ";
    cin>>ccontactno; // input its contact number
    //cin.ignore();
    kuchh(60);
    cout<<"PRESS 1 TO EXPLORE YOUR DAY IN MY SHOP";
    kuchh(70);
    while(1)
    {
        int option;
        cout<<"PRESS 1 FOR MAIN MENU\n";
        cout<<"Any other key to exit\n";
        cin>>t; // input user choice if other than 1 entered than exit
        if(t==1)
        {
            cout<<"!!!!WE WELCOME YOU!!!!\n";
            cout<<cname<<endl;
		    cout<<"\n\t1. BILLING COUNTER";
		    cout<<"\n\t2. MySHOP MANAGEMENT";
		    cout<<"\n\t3. EXIT";
		    cout<<"\n\tOption: ";
		    cin>>option;
            switch(option)
		    {
			    case 1:
                    cout<<"\n\t1. GENERATE BILL"; // want to generate a bill
		            cout<<"\n\t2. PRINT BILL BOOK"; // print whole bill book
                    cout<<"\n\t3. REVERSE BILL"; // reverse any bill
		            cout<<"\n\t4. EXIT\n";
		            int x;
		            cin>>x;
		            switch(x)
		            {
                    case 1:
                        generatebill(); // generate bill fucntion called
                        break;
                    case 2:
                        billbook(); // generate billbook function
                        break;
                    case 4:
                        break;
                    default:
                        break;
		            }
					break;

			case 2: admin_menu();
					break;
			case 3:
					ofstream fp; // file pointer for writing
                    fp.open("product.dat",ios::out | ios::binary);
                    fp.write((char *)& h,sizeof(h));
                    delete [] &h;
                    fp.close();
                    break;
		    }
        }
        else
        break;
    }
}
