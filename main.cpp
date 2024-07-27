/*This is the Banking Management Software which will help you perform some banking operations along with the Loan Management System.*/
#include <iostream> //header file to use cin and cout functions
#include <vector>   //header file to use vector standard template library
#include <string>   //header file to use the string data type
#include <math.h>   //header file to use pre-defined mathematical functions
#include <cstdlib>  //header file to generate random number 
#include <ctime>    //header file to generate random number time-to-time
#include <cstring>  //header file to use per-defined functions on string data type
#include <fstream>  //header file for read, write and append operation into a file

using namespace std;

class Customer      // customer class managed by Bank Administrative
{
private:
    double account_balance; // to store the account balance
    char account_type;      // whether the account is current or savings
    bool debit_card_issued; // whether the debit card is issued or not
    bool text_services;     // whether the text message service is issued or not

public:
    string name;                        // to store the name of the customer
    double annualSalary;                // to store the annual salary
    vector<string> monthlySheet;        // to store the monthly balance sheet
    vector<double> monthlyTransactions; // to store the monthly transaction
    int account_opened_month_count;     // to take the count of month
    long long int acc_no;               // to store the account number
    double loan_submitted;              // to store how many loan is submitted
    int unique_no;                      // to store the unique number that has been entered by the customer
    bool loanApplied;                   // to check whether the customer has any loan or not
    double loanRM;                      // to store for how many RM customer has applied for loan
    vector<double> installments;        // to store how many installments has submitted and how much per month
    double loanToBeSubmitted;           // how many loan to be submitted if the customer has applied for any loan
    double rateofInterest;              // rate of interest of the loan applied per annum
    Customer() {}                       // default constructor
    Customer(string name, char account_type, bool debit_card_issued, bool text_services, double balance, long long int acc_no, int uni_no, double salary)
    { // parameterized constructor
        this->name = name;
        this->account_type = account_type;
        this->debit_card_issued = debit_card_issued;
        this->text_services = text_services;
        this->account_balance = balance;
        this->acc_no = acc_no;
        this->unique_no = uni_no;
        account_opened_month_count = 0;
        loanRM = 0;
        loanApplied = 0;
        loan_submitted = 0;
        this->annualSalary = salary;
    }
    void displayBalance();             // to display balance
    void withdrawMoney(double);        // to withdraw the money
    void depositMoney(double);         // to deposit the money
    void calculateInterest();          // to calculate the compound interest for the positive balance
    void quaterlyCharges();            // to update balance for the quaterly charges
    void concludeMonthlySheet();       // to conclude the monthly balance sheet in case of any disrepancy
    void monthCompleted();             // to store the count of months
    void displayDetails();             // to display the details of the customer
    int isEligibleForCarLoan();        // whether the customer is eligible for car loan if he/she requires
    int isEligibleForTwoWheelerLoan(); // whether the customer is eligible for the two wheeler loan if he/she requires
    int isEligibleForPersonalLoan();   // whether the customer is eligible for the personal loan if he/she requires
    void loanSubmission(double);       // to submit the installments of the loan
    double calculateMonthlyPayment();  // to calculate the monthly transaction
    int isInstallmentsPaid();          // to check whether the installment has been paid for consecutively 2 months
};

double Customer ::calculateMonthlyPayment()
{
    double monthlyRate = rateofInterest / 12 / 100; // Convert annual rate to monthly
    int numberOfPayments = 60;

    // Calculate monthly payment using the loan formula
    double monthlyPayment = (loanRM * monthlyRate * pow(1 + monthlyRate, numberOfPayments)) /
                            (pow(1 + monthlyRate, numberOfPayments) - 1);

    return monthlyPayment;
}

void Customer ::loanSubmission(double amount)
{
    loanToBeSubmitted -= amount;
    cout << "Your Leftover Loan is : " << loanToBeSubmitted << endl;
}

int Customer ::isEligibleForCarLoan()
{
    int isEligible = 1;
    if (account_opened_month_count < 6)
    {
        return 0;
    }
    for (int j = 0; j < 5; j++)
    {
        if (monthlyTransactions[monthlyTransactions.size() - 1 - j] < 20000)
        {
            isEligible = 0;
        }
    }
    return isEligible;
}

int Customer ::isEligibleForPersonalLoan()
{
    int isEligible = 1;
    if (account_opened_month_count < 6)
    {
        return 0;
    }
    for (int j = 0; j < 5; j++)
    {
        if (monthlyTransactions[monthlyTransactions.size() - 1 - j] < 20000)
        {
            isEligible = 0;
        }
    }
    return isEligible;
}

int Customer ::isEligibleForTwoWheelerLoan()
{
    if (account_opened_month_count < 6)
    {
        return 0;
    }
    for (int j = 0; j < 5; j++)
    {
        if (monthlyTransactions[monthlyTransactions.size() - 1 - j] < 5000)
        {
            return 0;
        }
    }
    return 1;
}

void Customer ::monthCompleted()
{
    monthlyTransactions.push_back(account_balance);
    account_opened_month_count++;
}

void Customer ::displayDetails()
{
    cout << "Name is : " << name << endl;
    cout << "Account Number is : " << acc_no << endl;
}

void Customer ::concludeMonthlySheet()
{
    for (string s : monthlySheet)
    {
        cout << s << endl;
    }
}

void Customer ::calculateInterest()
{
    string result;
    if (account_type == 'S')
    {
        account_balance += (0.05 * account_balance);
        result = to_string(0.05 * account_balance);
    }
    else if (account_type == 'C')
    {
        account_balance += (0.04 * account_balance);
        result = to_string(0.05 * account_balance);
    }
    string str = "Account balance had been credited with Rate of Interest RM " + result;
    monthlySheet.push_back(str);
}

void Customer ::displayBalance()
{
    cout << "The Bank Balance is : " << account_balance << endl;
}

void Customer ::quaterlyCharges()
{
    if (debit_card_issued)
    {
        account_balance -= 10;
        string str = "The account balance had been debited by charges of Debit Card RM 10";
        monthlySheet.push_back(str);
    }
    if (text_services)
    {
        account_balance -= 5;
        string str = "The account balance had been debited by charges of Text Message Services RM 5";
        monthlySheet.push_back(str);
    }
}

void Customer ::withdrawMoney(double amount)
{
    if (account_type == 'C' && account_balance - amount >= -50000)
    {
        if (account_balance < amount)
        {
            cout << "Insufficient Funds" << endl;
            return;
        }
        account_balance -= amount;
        if (account_balance < 0)
        {
            account_balance -= (0.06 * account_balance);
            string result = to_string(0.06 * account_balance);
            string str = "Account balance had been debited for negative balance RM " + result;
            monthlySheet.push_back(str);
        }
    }
    else if (account_type == 'S' && account_balance - amount >= 50)
    {
        if (account_balance < amount)
        {
            cout << "Insufficient Funds" << endl;
            return;
        }
        account_balance -= amount;
    }
    cout << "Amount has been Debited" << endl;
    string result = to_string(amount);
    string str = "The account balance had been debited by RM " + result;
    monthlySheet.push_back(str);
}

void Customer ::depositMoney(double amount)
{
    string result = to_string(amount);
    account_balance += amount;
    cout << "Amount has been Credited" << endl;
    string str = "The account balance had been credited by RM " + result;
    monthlySheet.push_back(str);
}

long long int generateAccountNumber()
{ // to generate the 12-digit account number
    srand(static_cast<unsigned int>(time(nullptr)));
    long long accountNumber = 0;
    for (int i = 0; i < 12; ++i)
    {
        accountNumber = accountNumber * 10 + rand() % 10;
    }

    return accountNumber;
}

int main()
{
    cout << "\t\t\t\t------------------------------------------------------" << endl;
    cout << "\t\t\t\t|        Welcome to Banking Management Software      |" << endl;
    cout << "\t\t\t\t------------------------------------------------------" << endl;
    vector<Customer> customers;
    int ch, c, loan_choice;
    string name;
    bool isDebit, isText, loan_ask;
    double installment, salary;
    char type_of_account;
    string name_ch;
    double balance;
    int isLoop;
    int unique_no, isFound, k = 1, i = 0;
    long long int account_number;
    customers.push_back(Customer("Dhruv", 'C', 1, 1, 60000, generateAccountNumber() + (i++), 88648368, 6000000));
    customers.push_back(Customer("Archit", 'S', 1, 0, 6000, generateAccountNumber() + (i++), 12345678, 600000));
    do
    {
        cout << "MENU\n1. Create Account\n2. Log In\n3. Forgot Account Number\n4. Exit\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter the Customer Name : ";
            cin.ignore(); // to get '\n' character that has been entered by the user.
            cin >> name;
            cout << "Enter the type of account (S-Savings/C-Current): ";
            cin >> type_of_account;
            if (type_of_account == 'c')
            {
                type_of_account = 'C';
            }
            if (type_of_account == 's')
            {
                type_of_account = 'S';
            }
            cout << "Want Debit Card?? (1-Yes/0-No) : ";
            cin >> isDebit;
            cout << "Want Text Messages Services?? (1-Yes/0-No) : ";
            cin >> isText;
            cout << "Enter the 8-digit unique number : ";
            cin >> unique_no;
            cout << "Enter the annual salary : ";
            cin >> salary;
            account_number = generateAccountNumber() + (i++);
            if (type_of_account == 'C')
            {
                cout << "Minimum Balance required to open an account is : RM 5000" << endl;
                cout << "Enter the initial amount : ";
                cin >> balance;
                if (balance < 5000)
                {
                    cout << "Try Again" << endl;
                    break;
                }
            }
            else
            {
                cout << "Minimum Balance required to open an account is : RM 100" << endl;
                cout << "Enter the initial amount : ";
                cin >> balance;
                if (balance < 100)
                {
                    cout << "Try Again" << endl;
                    break;
                }
            }
            customers.push_back(Customer(name, type_of_account, isDebit, isText, balance, generateAccountNumber() + (i++), unique_no, salary));
            cout << "Account has been created" << endl;
            cout << "Account Number is : " << customers[customers.size() - 1].acc_no << endl;
            break;
        case 2:
            cout << "Enter the account number : ";
            cin >> account_number;
            cout << "Enter the unique number : ";
            cin >> unique_no;
            isLoop = 0;
            for (Customer &cust : customers)
            {
                if (cust.acc_no == account_number && cust.unique_no == unique_no)
                {
                    isLoop = 1;
                    cust.displayDetails();
                    do
                    {
                        cout << "MENU\n1. Display Balance\n2. Withdraw Money\n3. Deposit Money\n4. Quaterly Charges\n5. Monthly Balance Sheet\n6. Rate of Interest\n7. Check for Loan\n8. Month Completed\n9. Loan Submission\n10. Exit\n";
                        cin >> c;
                        switch (c)
                        {
                        case 1:
                            cust.displayBalance();
                            break;
                        case 2:
                            cout << "Enter the money to withdraw : ";
                            cin >> balance;
                            cust.withdrawMoney(balance);
                            break;
                        case 3:
                            cout << "Enter the money to deposit : ";
                            cin >> balance;
                            cust.depositMoney(balance);
                            break;
                        case 4:
                            cust.quaterlyCharges();
                            break;
                        case 5:
                            cust.concludeMonthlySheet();
                            break;
                        case 6:
                            cust.calculateInterest();
                            break;
                        case 7:
                            cout << "MENU\n1. Car Loan\n2. Two-Wheeler Loan\n3. Personal Loan\n4. Exit" << endl;
                            cin >> loan_choice;
                            switch (loan_choice)
                            {
                            case 1:
                                if (cust.loanApplied)
                                {
                                    cout << "You have the loan already" << endl;
                                    break;
                                }
                                if (!(cust.isEligibleForCarLoan()))
                                {
                                    cout << "Not Eligible for Car Loan" << endl;
                                }
                                else
                                {
                                    cout << "Eligible for Car Loan" << endl;
                                    cout << "Want to apply for Loan (1-Yes/0-No) : ";
                                    cin >> loan_ask;
                                    if (loan_ask)
                                    {
                                        cout << "Duration of Loan will be 60 Months" << endl;
                                        cout << "Rate of Interest will be 6% per annum" << endl;
                                        cust.rateofInterest = 6;
                                        cout << "How many RM want as a loan : ";
                                        cin >> cust.loanRM;
                                        cout << "Congratulations!! The Loan is Applied" << endl;
                                        cout << "Total RM had to pay per month : " << cust.calculateMonthlyPayment() << endl;
                                        cout << "Total amount needs to be get paid is : " << cust.calculateMonthlyPayment() * 60 << endl;
                                        cust.loanToBeSubmitted = cust.calculateMonthlyPayment() * 60;
                                        cust.loanApplied = 1;
                                    }
                                    else
                                    {
                                        cout << "Thank You" << endl;
                                    }
                                }
                                break;
                            case 2:
                                if (cust.loanApplied)
                                {
                                    cout << "You have the loan already" << endl;
                                    break;
                                }
                                if (!(cust.isEligibleForTwoWheelerLoan()))
                                {
                                    cout << "Not Eligible for Two Wheeler Loan" << endl;
                                }
                                else
                                {
                                    cout << "Eligible for Two Wheeler Loan" << endl;
                                    cout << "Want to apply for Loan (1-Yes/0-No) : ";
                                    cin >> loan_ask;
                                    if (loan_ask)
                                    {
                                        cout << "Duration of Loan will be 60 Months" << endl;
                                        cout << "Rate of Interest will be 4% per annum" << endl;
                                        cust.rateofInterest = 4;
                                        cout << "How many RM of Loan you want : ";
                                        cin >> cust.loanRM;
                                        cout << "Congratulations!! The Loan is Applied" << endl;
                                        cout << "Total RM had to pay per month : " << cust.calculateMonthlyPayment() << endl;
                                        cout << "Total amount needs to be get paid is : " << cust.calculateMonthlyPayment() * 60 << endl;
                                        cust.loanToBeSubmitted = cust.calculateMonthlyPayment() * 60;
                                        cust.loanApplied = 1;
                                    }
                                    else
                                    {
                                        cout << "Thank You" << endl;
                                    }
                                }
                                break;
                            case 3:
                                if (cust.loanApplied)
                                {
                                    cout << "You have the loan already" << endl;
                                    break;
                                }
                                if (!(cust.isEligibleForPersonalLoan()))
                                {
                                    cout << "Not Eligible for Personal Loan" << endl;
                                }
                                else
                                {
                                    cout << "Eligible for Personal Loan" << endl;
                                    cout << "Want to apply for Loan (1-Yes/0-No) : ";
                                    cin >> loan_ask;
                                    if (loan_ask)
                                    {
                                        cout << "Duration of Loan will be 60 Months" << endl;
                                        cout << "Rate of Interest will be 10% per annum" << endl;
                                        cust.rateofInterest = 10;
                                        cout << "Maximum Loan to demand is : " << cust.annualSalary * 0.2 << endl;
                                        cout << "How many RM of Loan wanted : ";
                                        cin >> cust.loanRM;
                                        if (cust.loanRM > cust.annualSalary * 0.2)
                                        {
                                            cust.loanRM = cust.annualSalary * 0.2;
                                            cout << "Maximum loan has been opted : " << cust.loanRM << endl;
                                        }
                                        cout << "Congratulations!! Your Loan is Applied" << endl;
                                        cout << "Total RM had to pay per month : " << cust.calculateMonthlyPayment() << endl;
                                        cout << "Total amount had to be paid is : " << cust.calculateMonthlyPayment() * 60 << endl;
                                        cust.loanToBeSubmitted = cust.calculateMonthlyPayment() * 60;
                                        cust.loanApplied = 1;
                                    }
                                    else
                                    {
                                        cout << "Thank You" << endl;
                                    }
                                }
                                break;
                            case 4:
                                break;
                            default:
                            {
                                cout << "Invalid Choice\nExiting..." << endl;
                                break;
                            }
                            }
                            break;
                        case 8:
                            cust.monthCompleted();
                            break;
                        case 9:
                            if (cust.loanApplied)
                            {
                                cout << "Installment of RM : ";
                                cin >> installment;
                                if (cust.loanToBeSubmitted < installment)
                                {
                                    cout << "Your Leftover loan is only : " << cust.loanToBeSubmitted << endl;
                                    cout << "Enter again : ";
                                    cin >> installment;
                                }
                                cust.installments.push_back(installment);
                                cust.loanSubmission(installment);
                            }
                            else
                            {
                                cout << "No Loan has been applied on your name" << endl;
                            }
                            break;
                        case 10:
                            break;
                        default:
                            cout << "Invalid Choice" << endl;
                            break;
                        }
                    } while (c != 10);
                }
            }
            if (!isLoop)
            {
                cout << "Incorrect Details" << endl;
            }
            break;
        case 3:
            isFound = 0;
            cout << "Enter the name : ";
            cin >> name_ch;
            for (Customer cust : customers)
            {
                if (strcmp(cust.name.c_str(), name_ch.c_str()) == 0)
                {
                    cout << "Account Number is : " << cust.acc_no << endl;
                    isFound = 1;
                    break;
                }
            }
            if (!isFound)
            {
                cout << "No Account has been opened on this name" << endl;
            }
            break;
        case 4:
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    } while (ch != 4);
    cout << "Exiting!!" << endl;
    cout << "Thank You For Using Banking Management Software!!" << endl;
    return 0;
}