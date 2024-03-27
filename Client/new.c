//header file
#include<stdio.h>
#define ANSI_ORANGE "\x1b[38;5;208m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_RESET   "\x1b[0m"
//function prototype

int isUser();
int Screen();
int login();
int signup();
int reset();
//main function

int main(){
    Screen();
}
int Screen(){
    int ch;
    printf(ANSI_GREEN"\n----------------WELCOME TO EXPENSE TRACKER--------------------\n\n"ANSI_RESET);
    printf(ANSI_ORANGE"-----------MONITOR AND KEEP TRACK OF YOUR EXPENSES-------------\n\n\n"ANSI_RESET);
    printf("Expense Tracker is a simple console-based application to help you manage your \nexpenses efficiently. You can track your spending, view reports, and set budgets.\n\n");
    printf("\n INSTRUCTIONS :\n\n");
    printf(" '1' : ");
    printf(ANSI_GREEN"Login \n"ANSI_RESET);
    printf(" '2' : ");
    printf(ANSI_GREEN"SignUp \n"ANSI_RESET);
    printf(" '3' : ");
    printf(ANSI_GREEN"Reset Password \n"ANSI_RESET);
    printf(" '4' : ");
    printf(ANSI_RED"Exit Application \n"ANSI_RESET);

    printf("Press any key to continue...");
    scanf("%d",&ch);
    switch (ch){
    case 1:
    login();
    break;
    case 2:
    
    break;
    case 3:
    break;
    case 4:
    break;
    default:
    printf("Wrong Choice");
    break;
}}
int login(){
    char username[60],password[70];
    printf(ANSI_GREEN "\n----------Welcome Back------------\n" ANSI_RESET);
    printf("\n--------------LOGIN---------------\n\n");
    
    printf("Enter Your Username :");
    scanf("%s",username);
    printf("Enter Your Password :");
    scanf("%s",password);
    return 0;    
}
int signup(){
    char username[60],password[70];
    printf(ANSI_GREEN "\n----------Welcome Back------------\n" ANSI_RESET);
    printf("\n--------------LOGIN---------------\n\n");
    
    printf("Enter Your Username :");
    scanf("%s",username);
    printf("Enter Your Password :");
    scanf("%s",password);
    return 0;    
}