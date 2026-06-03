#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void regUser(string newUser, string newPass){
    ifstream inFile("usersandpasswordstroage.txt");
    string fileUser, filePass;
    int CheckforDuplicateUser=0; //using integers instead of bool for checking
    while(getline(inFile, fileUser, ',') && getline(inFile, filePass)){
        if(fileUser==newUser){
            CheckforDuplicateUser=1;
            break;
        }
    }
    inFile.close();
    if(CheckforDuplicateUser==1){
        cout<<"Error! Username is already taken. Please try a different username!"<<endl;
    }
    else{
        ofstream outFile("usersandpasswordstroage.txt", ios::app);
        outFile<<newUser<<","<<newPass<<"\n";
        outFile.close();
        cout<<"Account successfully created for "<<newUser<<"!\n";
    }
}
void loginUser(string reqUser, string reqPass){
    ifstream inFile("usersandpasswordstroage.txt");
    string fileUser, filePass;
    int userisFound=0;
    while(getline(inFile, fileUser, ',') && getline(inFile, filePass)){
        if(fileUser==reqUser && filePass==reqPass){
            userisFound=1;
            break;
        }
    }
    inFile.close();
    if(userisFound==1){
        cout<<"Login Successful"<<endl;
    }
    else{
        cout<<"Invalid Credentials"<<endl;
    }
}
int main(){
    int choice=0;
    while(choice!=3){
    cout<<"Welcome! Please select from the following:\nEnter 1 if you want to log in to an already existing account.\nEnter 2 if you want to register a new account.\nEnter 3 to exit from the menu.\n";
    cin>>choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout<<"Invalid Choice, try again";
        continue;
        }
        if(choice==1){
            string usernameEnteredbyUser, passEnteredbyUser;
                cin.ignore(10000, '\n');
                cout<<"Enter username: ";
                getline(cin, usernameEnteredbyUser);
                cout<<"Enter password: ";
                getline(cin, passEnteredbyUser);
                loginUser(usernameEnteredbyUser, passEnteredbyUser);
                break;
        }
        else if(choice==2){
            string newUsernameEnteredbyUser, newPassEnteredbyUser;
            cin.ignore(10000, '\n');
            cout<<"Enter the username you want: ";
            getline(cin, newUsernameEnteredbyUser);
            cout<<"Enter a password for your account: ";
            getline(cin, newPassEnteredbyUser);
            regUser(newUsernameEnteredbyUser, newPassEnteredbyUser);
        }
        else if(choice==3){
            cout<<"Exiting the menu!";
        }
        else{
            cout<<"Error, please try again!";
        }
    }
    return 0;
}