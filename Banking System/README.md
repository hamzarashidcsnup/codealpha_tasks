V1:
Original Version of the code.
Uses vector to store data of user and transactions.
Features include account creation, deposit, withdraw and transfer money.

V2:
Modified the original version of code.
**Changes Made:**
Data is now permanently stored in a .txt file as well as in vector array.
Added a storinguser function and a storingTransactionHistory function to write the data into a file.
Added two functions to load the data from the files when the program starts.
Emptied out the constructor in Customer class and made a new function to register a new user.
Fixed bugs, bugs included; negative amount entered to withdraw, transfer or deposit; transfer money into your own account(sender and reciever account numbers could be same);
