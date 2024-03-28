//header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

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
    login_connection(username,password);
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

struct Response {
    char message[256];
    long status_code;
    char id[100];
};
// Callback function to write the received data to a buffer
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Cast userdata to a pointer to struct Response
    struct Response *response = (struct Response *)userdata;

    // Parse the received JSON data
    sscanf(ptr, "{\"id\":%s, \"message\": \"%255[^\"]\"}", response->id, response->message);

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
    struct Response response;
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
            clrscr();
            printf(ANSI_GREEN"Login Successfull" ANSI_GREEN);
            sleep(2);
            printf("Welcome to ");
            sleep(2);
        }
        else if(response.status_code==206){
            printf("ID: %s\n", response.id);
            printf(ANSI_RED "Invalid Credentials"ANSI_RESET);
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