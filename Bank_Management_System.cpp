#include<fstream>
#include<iostream>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctime>
#include<stdlib.h>
#include<iomanip>
using namespace std;

int date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout<<"DATE : ";
    cout<<ltm->tm_mday <<"-"<<1 + ltm->tm_mon<<"-"<<1900 + ltm->tm_year<<endl;
    return 0;
}
int acc_number()
{
    srand(time(NULL));
    int account[9]={1,2,3,4,5,6,7,8,9},a;
    for(int x=9;x>0;x--)
    {
        a=rand()%x;
        cout<<account[a];
        while(a<x-1)
        {
            account[a]=account[a+1];
            a++;
        }
    }
    cin.get();
    cin.ignore();
    return 0;
}

class account
{
private:
    long double ac_number,contact;
    char Fname[30],address[1000];
    int Bdate,Bmonth,Byear,pin;
    float mne,d_mne,w_mne;
    public:
    account()
    {
        ac_number=0;
        strcpy(Fname,"No Name");
        mne=0;
        d_mne=0;
        w_mne=0;
    }
    void newgetaccountdata();
    void getaccountdata()
    {
        cout<<endl<<"Enter your Full name :";
        cin.ignore();
        cin.getline(Fname,29);
        cout<<"Enter Date Of Birth :";
        backtodate:
        cin>>Bdate;
        cin>>Bmonth;
        cin>>Byear;
        if(Bdate<1 || Bdate>31 || Bmonth<1 || Bmonth>12)
        {
                cout<<"Enter valid Date Of Birth :";
                goto backtodate;
        }
        cout<<"Enter Your Address in single line :";
        cin.ignore();
        cin.getline(address,999);
        cout<<"Enter your Contact Number(10 digit only):";
        cin>>contact;

        cout<<"Your account number :";
        acc_number();
        cout<<"Enter your account number given for confirmation :";
        cin>>ac_number;

        cout<<"Enter pin you want to set:";
        cin>>pin;

        cout<<"Enter some depositary money(min 1000) :";
        cin>>mne;
        while(mne<=1000)
        {
            cout<<endl<<"Enter valid amount :";
            cin>>mne;
            if(mne>=1000)
                break;
        }

    }
    void showaccountdata()
    {
        cout<<endl<<"account holder's name :"<<Fname;
        cout<<endl<<"Holder Date OF Birth :"<<Bdate<<"|"<<Bmonth<<"|"<<Byear;
        cout<<endl<<"Holder Address :"<<address;
        cout<<endl<<"Holder Contact Number :"<<fixed<<setprecision(0)<<contact;
        cout<<endl<<"Holder Current Balance :"<<fixed<<setprecision(0)<<mne;
    }
    int storeaccountdata();
    void viewallaccount();
    void searchaccount(long double *);
    void deleteaccount(long double *,int *);
    void updateaccount(long double *);
};
void account::newgetaccountdata()
{
        char ans[5];
        //cout<<"Do account holder's name is to be edited (YES or NO) :";
        //cin>>ans;
        /*if(!strcmp(ans,"NO"))
            cout<<endl<<"Account holder's name:"<<Fname<<endl;
        else
        {
            cout<<endl<<"Enter new account holder's name:";
            cin>>Fname;
        }*/
        cout<<endl<<"Account holder's name:"<<Fname;
        cout<<endl<<"Do account holder's contact is to be edited (YES or NO) :";
        cin>>ans;
        if(!strcmp(ans,"NO"))
            cout<<endl<<"Account holder's Contact:"<<fixed<<setprecision(0)<<contact<<endl;
        else
        {
            cout<<endl<<"Enter new account holder's Contact:";
            cin>>contact;
        }

        cout<<endl<<"Do account holder's Address is to be edited (YES or NO) :";
        cin>>ans;
        if(!strcmp(ans,"NO"))
            cout<<endl<<"Account holder's Address:"<<address<<endl;
        else
        {
            cout<<endl<<"Enter new account holder's Address:";
            cin.ignore();
            cin.getline(address,999);
        }

        cout<<"Enter a depository amount:";
        cin>>d_mne;
        mne=d_mne+mne;
        cout<<"Enter withdrawal amount:";
        cin>>w_mne;
        mne=mne-w_mne;
        cout<<"Current balance of this account: "<<mne;
}
int account::storeaccountdata()
{
    if(ac_number==0 && mne==0)
    {
        cout<<"Account not created.";
        return(0);
    }
    else
    {
        ofstream fout;
        fout.open("file.dat",ios::app|ios::ate|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return(1);
    }
}
void account::viewallaccount()
{
    int cnt=1;
    ifstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n File not found.";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            cout<<"Account:"<<cnt;
            showaccountdata();
            fin.read((char*)this,sizeof(*this));
            cout<<endl<<endl;
            cnt++;
        }
        cout<<"This "<<cnt-1<<" account exists.";
        fin.close();
    }
}
void account::searchaccount(long double *t)
{
    int cnt=0,pin2;
    char dcision[4];
    ifstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n File not found";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(*t==ac_number)
                {
                    cout<<"\nEnter your account pin:";
                    cin>>pin2;
                    backtopin:;
                    if(pin2==(*this).pin)
                        {
                            showaccountdata();
                            cnt++;
                        }
                        else
                            {
                                cout<<"Enter YES or NO if you remember the pin:";
                                cin.ignore();
                                cin.getline(dcision,4);
                                if(!strcmp(dcision,"YES"))
                                {
                                    cout<<"Enter valid pin:";
                                    cin>>pin2;
                                    goto backtopin;
                                }
                                else
                                {
                                    cout<<"Sorry we cannot help you, Contact BANK HELP CENTRE.";
                                    goto out;
                                }
                            }
                }
            fin.read((char*)this,sizeof(*this));
        }
    }
    if(cnt==0)
    {
        cout<<"\n Error..! Account not found";
    }
    out:;
    fin.close();
}
void account::deleteaccount(long double *t,int *pin2)
{
    long double temp_num;
    int temp_pin;
    ifstream fin;
    ofstream fout;
    fin.open("file.dat",ios::out|ios::binary);
    if(!fin)
        cout<<"\n File not found";
    else{
        fout.open("temp.dat",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(*t!=ac_number)
            {
                if(*pin2!=pin)
                    {
                        fout.write((char*)this,sizeof(*this));
                    }
            }
            else
            {
                temp_num=ac_number;
                temp_pin=pin;

            }
            fin.read((char*)this,sizeof(*this));
        }
        if(*t==temp_num && *pin2==temp_pin)
        {
            cout<<"Account is deleted & COLLECT your CASH FROM DESK.";
            fin.close();
            fout.close();
            remove("file.dat");
            rename("temp.dat","file.dat");
        }
        else
        {
            cout<<"Account number or pin is invalid.";
            fin.close();
            fout.close();
        }
    }
}
void account::updateaccount(long double *t)
{
    int pin2;
    char dcision[4];
    fstream file;
    file.open("file.dat",ios::in|ios::out|ios::binary|ios::ate);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));
    while(!file.eof())
    {
        if(*t==ac_number)
        {
            cout<<"Enter pin:";
            cin>>pin2;
            if(pin2==(*this).pin)
            {
                newgetaccountdata();
                file.seekp(file.tellp()-sizeof(*this));
                file.write((char*)this,sizeof(*this));
            }
            else
            {
                cout<<"Sorry we cannot help you."<<endl<<"Pin is incorrect.";
            }
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
}
int menu()
{
    int choice;
    date();
    cout<<"\n\t\t\t-->****  Bank management  ****<--";
    cout<<endl<<endl<<"\n\t--> 1. Insert a bank account.";
    cout<<"\n\t--> 2. View all bank accounts.";
    cout<<"\n\t--> 3. Search a bank account.";
    cout<<"\n\t--> 4. Delete a bank account.";
    cout<<"\n\t--> 5. Update a bank account.";
    cout<<"\n\t--> 6. Exit";
    cout<<"\n\n Enter a choice :";
    cin>>choice;
    return choice;
}
int main()
{
    account b1;
    while(1)
    {

        system("cls");
        switch(menu())
        {
        case 1:

            b1.getaccountdata();
            b1.storeaccountdata();
            cout<<"Account is created.";
            break;
        case 2:

            b1.viewallaccount();
            break;
        case 3:

            cout<<"Enter account number to search :";
            long double atemp;
            cin.ignore();
            cin>>atemp;
            b1.searchaccount(&atemp);
            break;
        case 4:

            int pin2;
            cout<<"Enter account number to delete account :";
            cin>>atemp;
            cout<<"Enter pin : ";
            cin>>pin2;
            b1.deleteaccount(&atemp,&pin2);
            break;
        case 5:

            cout<<"Enter account number to update account :";
            cin>>atemp;
            b1.updateaccount(&atemp);
            break;
        case 6:

            cout<<"Thank you for using this application";
            cout<<"\nPress any key to continue";
            _getch();
            system("cls");
            exit(0);
            break;
        default:

            cout<<"\nInvalid Choice";
            }
        _getch();
        }
}
