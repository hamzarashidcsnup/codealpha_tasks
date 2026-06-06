#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

int availableaccountnumber=10001;

void storingusers(string newusername, int newaccountnumber){
    ofstream storingFile("user & account numbers.txt", ios::app);
    if(storingFile.is_open()){
        storingFile<<newusername<<" "<<newaccountnumber<<endl;
        storingFile.close();
    }
    else{
        cout<<"Couldn't open file for writing!"<<endl;
    }
}
void storingTransactionhistory(int accountnumber, string typeoftransaction, double amountoftransaction){
    ofstream transactionfile("Transactions log.txt", ios::app);
    if(transactionfile.is_open()){
        transactionfile<<accountnumber<<" "<<typeoftransaction<<" "<<amountoftransaction<<endl;
    }
}

class Transaction{
    public:
            string typeoftransaction;
            double amountoftransaction;
};
class Account{
    public:
            int accountNumber;
            double balance=0;
            vector<Transaction> history;
            Account(){
                accountNumber=availableaccountnumber;
                availableaccountnumber=availableaccountnumber+1;
            }
            void DepositMoney(){
                double amounttoDeposit;
                cout<<"Enter the amount you want to deposit: ";
                cin>>amounttoDeposit;
                balance=balance+amounttoDeposit;
                cout<<"Deposited "<<amounttoDeposit<<" in your account!"<<endl;
                Transaction Transactionobj;
                Transactionobj.typeoftransaction="Deposit";
                Transactionobj.amountoftransaction=amounttoDeposit;
                history.push_back(Transactionobj);
                storingTransactionhistory(accountNumber, "Deposit", amounttoDeposit);
            }
            void withdrawMoney(){
                double amounttoWithdraw;
                cout<<"Enter the amount you want to withdraw: ";
                cin>>amounttoWithdraw;
                if(amounttoWithdraw>balance){
                    cout<<"Error, insufficient funds!"<<endl;
                }
                else if(amounttoWithdraw<=balance){
                    balance=balance-amounttoWithdraw;
                    cout<<"Successfully withdrawn "<<amounttoWithdraw<<" from your account!"<<endl;
                    Transaction Transactionobj;
                    Transactionobj.typeoftransaction="Withdraw";
                    Transactionobj.amountoftransaction=amounttoWithdraw;
                    history.push_back(Transactionobj);
                    storingTransactionhistory(accountNumber, "Withdraw", amounttoWithdraw);
                }
                else{
                    cout<<"Error, please try again!"<<endl;
                }
            }
            void transferMoney(Account &otheraccountnumber){
                double amounttotransfer;
                cout<<"Enter the amount you want to transfer to other account: ";
                cin>>amounttotransfer;
                if(this->accountNumber==otheraccountnumber.accountNumber){
                    cout<<"Error! You can't transfer money into your own account"<<endl;
                }
                if(amounttotransfer<=0){
                    cout<<"Error! The transfer amount should be greater than 0"<<endl;
                }
                if(amounttotransfer<=balance){
                    balance=balance-amounttotransfer;
                    otheraccountnumber.balance=otheraccountnumber.balance+amounttotransfer;
                    cout<<"Transfer success!"<<endl;
                    Transaction Transactionobj;
                    Transactionobj.typeoftransaction="Transfer";
                    Transactionobj.amountoftransaction=amounttotransfer;
                    history.push_back(Transactionobj);
                    storingTransactionhistory(accountNumber, "Transfer", amounttotransfer);
                    Transaction Transactionobjforreciever;
                    Transactionobjforreciever.typeoftransaction="Received";
                    Transactionobjforreciever.amountoftransaction=amounttotransfer;
                    otheraccountnumber.history.push_back(Transactionobjforreciever);
                    storingTransactionhistory(otheraccountnumber.accountNumber, "Received", amounttotransfer);
                }
                else if(amounttotransfer>balance){
                    cout<<"Insufficient funds."<<endl;
                }
                else{
                    cout<<"Error, please try again."<<endl;
                }
            }
};
class Customer{
    public:
            string name;
            Account Accountobj;
            Customer(){}
            void registerNewUser(){
                cin.ignore(10000, '\n');
                cout<<"Enter your name: (no spaces)";
                cin>>name;
                cout << "Account successfully created for " << name << endl;
                cout << "Your account number is " << Accountobj.accountNumber << endl;
                storingusers(name, Accountobj.accountNumber);
            }
            void showDetails(){
                cout<<"Name: "<<name<<endl;
                cout<<"Account Number: "<<Accountobj.accountNumber<<endl;
                cout<<"Balance: "<<Accountobj.balance<<endl;
                cout<<"Recent transactions:"<<endl;
                if(Accountobj.history.empty()){
                    cout<<"No recent transactions yet"<<endl;
                }
                for(int i=0;i<Accountobj.history.size();i++){
                    cout<<Accountobj.history[i].typeoftransaction<<" "<<Accountobj.history[i].amountoftransaction<<endl;
                }
            }
};
int indexhelper(vector<Customer> &databaseforthebank, int accountnumbertobesearched){
    for(int i=0;i<databaseforthebank.size();i++){
        if(databaseforthebank[i].Accountobj.accountNumber==accountnumbertobesearched){
            return i;
        }
    }
    return -1; //standard code for not found
}

void loadingaccounts(vector<Customer>& databaseforthebank){
    ifstream storingFile("user & account numbers.txt");
    if(!storingFile.is_open())
    return;
    string loadedname; int highestaccountnumber=10000, loadedaccountnumber;

    while(storingFile>>loadedname>>loadedaccountnumber){
        Customer Customerobj;
        Customerobj.name=loadedname;
        Customerobj.Accountobj.accountNumber=loadedaccountnumber;
        databaseforthebank.push_back(Customerobj);
        if(loadedaccountnumber>highestaccountnumber){
            highestaccountnumber=loadedaccountnumber;
        }
    }
    storingFile.close();
    availableaccountnumber=highestaccountnumber+1;
}

void loadingtransactions(vector<Customer>& databseforthebank){
    ifstream transactionFile("Transactions log.txt");
    if(!transactionFile.is_open())
    return;
    int accountnumber; string typeoftransaction; double amountoftransactions;

    while(transactionFile>>accountnumber>>typeoftransaction>>amountoftransactions){
        int index=indexhelper(databseforthebank, accountnumber);
        if(index!=-1){
            Transaction Transactionobj;
            Transactionobj.typeoftransaction=typeoftransaction;
            Transactionobj.amountoftransaction=amountoftransactions;
            databseforthebank[index].Accountobj.history.push_back(Transactionobj);
            if(typeoftransaction=="Deposit" || typeoftransaction=="Received"){
                databseforthebank[index].Accountobj.balance+=amountoftransactions;
            }
            else if(typeoftransaction=="Withdraw" || typeoftransaction=="Transfer"){
                databseforthebank[index].Accountobj.balance-=amountoftransactions;
            }
        }
    }
    transactionFile.close();
}

int main(){
    vector<Customer> BankDatabase;
    loadingaccounts(BankDatabase);
    loadingtransactions(BankDatabase);
    int choiceenteredbyuser=0;
    while(choiceenteredbyuser!=6){
        cout<<"Welcome to the main menu of Banking System. Please enter numbers 1-4 according to what operation you want to perform.\n1.Create a new account.\n2.Deposit money in your account.\n3.Withdraw money from your account.\n4.Transfer funds into another account.\n5.Show details of account.\n6.Exit from the menu.\n";
        cin>>choiceenteredbyuser;
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Enter a valid choice.\n";
            continue;
                }
    if(choiceenteredbyuser==1){
        Customer Customerobj;
        Customerobj.registerNewUser();
        BankDatabase.push_back(Customerobj);  //saving in the database
        }
    else if(choiceenteredbyuser==2){
        int accountnumberofuser;
        cout<<"Enter your account number: ";
        cin>>accountnumberofuser;
        int index=indexhelper(BankDatabase, accountnumberofuser);
        if(index!=-1){
            BankDatabase[index].Accountobj.DepositMoney();
            }
        else{
            cout<<"Account not found"<<endl;
            }
        }
    else if(choiceenteredbyuser==3){
        int accountnumberofuser;
        cout<<"Enter your account number: ";
        cin>>accountnumberofuser;
        int index=indexhelper(BankDatabase, accountnumberofuser);
        if(index!=-1){
            BankDatabase[index].Accountobj.withdrawMoney();
        }
        else{
            cout<<"Account not found."<<endl;
            }
        }
    else if(choiceenteredbyuser==4){
        int accountnumberofsender, accountnumberofreciever;
        cout<<"Enter the account number of sender: ";
        cin>>accountnumberofsender;
        cout<<"Enter the account number of reciever: ";
        cin>>accountnumberofreciever;
        int indexofsender=indexhelper(BankDatabase, accountnumberofsender);
        int indexofreciever=indexhelper(BankDatabase, accountnumberofreciever);
        if(indexofsender!=-1 && indexofreciever!=-1){
            BankDatabase[indexofsender].Accountobj.transferMoney(BankDatabase[indexofreciever].Accountobj);
            }
        else{
            cout<<"One or both accounts were not found, please try again."<<endl;
            }
        }
    else if(choiceenteredbyuser==5){
        int accountnumberenteredbyuser;
        cout<<"Enter your account number: ";
        cin>>accountnumberenteredbyuser;
        int index=indexhelper(BankDatabase, accountnumberenteredbyuser);
        if(index!=-1){
            BankDatabase[index].showDetails();
            }
        else{
            cout<<"Account not found."<<endl;
            }
    }
    else if(choiceenteredbyuser==6){
        cout<<"Exiting the menu."<<endl;
        }
    else{
        cout<<"Invalid choice, try again"<<endl;
        }
    }
    return 0;
}
