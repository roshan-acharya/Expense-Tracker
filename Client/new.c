//header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include"Expense.h"
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
int login_connection(char[], char[]);
int signup_connection(char[], char[]);
int home();

//main function

int main(){
    Screen();
   
}
int Screen(){
    int ch;
    printf(ANSI_GREEN"\n--------------------WELCOME TO EXPENZ------------------------\n\n"ANSI_RESET);
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
    signup();
    break;
    case 3:
    break;
    case 4:
    exit(0);
    break;
    default:
    exit(0);
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
    login_connection(username,password);
    
    return 0;    
}
int signup(){
    char username[60],password[70];
    printf("\n--------------SIGNUP---------------\n\n");
    
    printf("Enter Your Username :");
    scanf("%s",username);
    printf("Enter Your Password :");
    scanf("%s",password);
    signup_connection(username,password);
    return 0;    
}

struct Response {
    char message[256];
    long status_code;
    char id[200];
}response;
// Callback function for bufferr
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Type casting  userdata to a pointer to struct Response
    struct Response *response = (struct Response *)userdata;
    // Parse the received JSON data
   sscanf(ptr, "{\"id\":\"%[^}\"]\"", response->id);
    return size * nmemb;
}
int login_connection(char username[50],char password[50]){
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl = curl_easy_init();
    if (!curl) {
        printf("Error initializing libcurl\n");
        return 1;
    }

    // Set the URL to your Node.js API endpoint
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/user/login");

    // Set the Content-Type header
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the JSON data for POST request
     char json_data[100];
    snprintf(json_data, sizeof(json_data), "{\"username\": \"%s\", \"password\": \"%s\"}", username, password);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

    // Structure to store response data
    
    response.message[0] = '\0';  // Initialize the message field

    // Set the userdata pointer to point to the struct Response
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Set the callback function to handle the response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // Perform the HTTP POST request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // Get the status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);

        // Print the received message and status code
        if(response.status_code==200){
            printf("\033[H\033[J"); 
            printf(ANSI_ORANGE"Login Successfull\033[1m " ANSI_RESET);
            sleep(2);
            printf("\033[H\033[J"); 
            printf("\033[1m Welcome to Expenz , ");
            printf(ANSI_GREEN"\033[1m%s\033[1m \n\n"ANSI_RESET,username);
            home();
           
        }
        else if(response.status_code==206){
            
            int ch;
            printf("\033[H\033[J"); 
            printf(ANSI_RED "\nInvalid Credentials\n\n"ANSI_RESET);
            printf(ANSI_GREEN"1. Login \n"ANSI_RESET);
            printf(ANSI_ORANGE"2.Go Back\n "ANSI_RESET);
            printf("Select Your choice........ ");
            scanf("%d",&ch);
            switch(ch){
                case 1:
                login();
                break;
                case 2:
                Screen();
                break;
                default:
                exit(0);
                break;
            }
            
        }
        else{
            login();
        }
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}
int signup_connection(char username[50],char password[50]){
    CURL *curl;
    CURLcode res;

    //  libcurl initialization
    curl = curl_easy_init();
    if (!curl) {
        printf("Error initializing libcurl\n");
        return 1;
    }

    // Node.js API endpoint for setup
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/user/signup");

    // Set the Content-Type header
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // JSON data for POST request
     char json_data[100];
    snprintf(json_data, sizeof(json_data), "{\"username\": \"%s\", \"password\": \"%s\"}", username, password);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

    // Structure to store response data
    
    response.message[0] = '\0';  // Initialize the message field

    // Set the userdata pointer to point to the struct Response

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Set the callback function to handle the response
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // Perform the HTTP POST request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // Get the status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status_code);

        // Print the received message and status code
        printf("Received Message: %s\n", response.message);
        printf("Status Code: %ld\n", response.status_code);
         printf("ID: %s\n", response.id);

        if(response.status_code==200){
            printf("\033[H\033[J"); 
            printf(ANSI_ORANGE"Signup Successfull" ANSI_RESET);
            sleep(2);
            printf("\033[H\033[J"); 
            printf("Welcome to Expenz ,");
            printf(ANSI_GREEN"\033[1m%s\033[1m"ANSI_RESET,username);
            home();
        }
        else if(response.status_code==206){
            int ch;
            printf("\033[H\033[J");
            printf(ANSI_RED "\n User already exist \n\n"ANSI_RESET);
            printf("If you already have account \n");
            printf("1. Login \n");
            printf("2.Go Back\n ");
            printf("Select Your choice ");
            scanf("%d",&ch);
            switch(ch){
                case 1:
                login();
                break;
                case 2:
                Screen();
                break;
                default:
                exit(0);
                break;
            }
        }
        else if(response.status_code==422){
            printf(ANSI_RED "Credentials must be filled"ANSI_RESET);
        }
        else{
            login();
        }
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}
int home(){
    int ch;
    printf(ANSI_GREEN"1. View Expense \n");
    printf("2. Add Expense \n");
    printf("3. Update Expense \n");
    printf("4. Delete Expense \n"ANSI_RESET);
    printf(ANSI_RED"5. Log Out \n"ANSI_RESET);
    printf("Enter any key to continue......");
    scanf("%d",&ch);
    switch(ch){
        case 1:
        viewExpense(response.id);
        home();
        break;
        case 2:
        getData();
        addExpense(response.id);
        home();
        break;
        case 3:
        printf("\033[H\033[J"); 
        viewExpense(response.id);
        updateExpense();
        break;
        
        break;
        case 4:
        printf("\033[H\033[J"); 
        viewExpense(response.id);
        printf("\n");
        deleteExpense();
        viewExpense(response.id);
        home();
        break;
        default:{
            exit(0);
        }
    }

    return 0;
    }
