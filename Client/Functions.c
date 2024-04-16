#include "Expense.h"
#include <stdio.h>
#include <curl/curl.h>
#include<string.h>
#include <cJSON.h>
#include<stdlib.h>
#include <unistd.h>

#define ANSI_ORANGE "\x1b[38;5;208m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_RESET   "\x1b[0m"

#define MAX_ITEMS 20

//function prototype
int deleteExpense();

int struct_n,count=1;
struct Expense
{
    char id[200];
    char description[50];
    char cat[40];
    int amt;
    char wallet[40];
    char dat[60];
} send_data;

struct Transaction{
    char id[200];
    char desc[50];
    char cat[40];
    char wallet[25];
    int amount;
}transactions[MAX_ITEMS];






// get data function
int getData()
{
    printf("Category of Expense :");
    scanf("%s", send_data.cat);
    printf("Enter Description : ");
    scanf("%s", send_data.description);
    printf("Enter Expense Amount :");
    scanf("%d", &send_data.amt);
    printf("Enter wallet you used");
    scanf("%s", send_data.wallet);
}

// Expense api functions

size_t write_callback1(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    printf("%.*s", (int)(size * nmemb), ptr);
    return size * nmemb;
}
int addExpense(char *id)
{
    printf("%s",id);
    int status_code;
    CURL *curl;
    CURLcode res;
    char *url = "http://localhost:3000/expense/post"; // Replace with your API endpoint

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl)
    {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Format the data into JSON
        char data[712]; // Adjust buffer size as needed
        
        snprintf(data, sizeof(data), "{\"id\":\"%s\",\"desc\":\"%s\",\"cat\":\"%s\",\"amount\":%d,\"wallet\":\"%s\"}",
                 id, send_data.description, send_data.cat, send_data.amt, send_data.wallet);
        // Set POST data
        printf("%s",data);
       curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        //Perform the POST request
      res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
        // Check for errors
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        if(status_code==200){
            printf("Expense Added");
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    return 0;
}


//Get expense data
size_t write_callback_view(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}
int viewExpense(char *id){
 CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing curl.\n");
        return 1;
    }
   char url[100];
   strcpy(url, "http://localhost:3000/expense/get/");
   strcat(url, id);
    //url for get request
    curl_easy_setopt(curl, CURLOPT_URL, url);

    
    FILE *file = fopen("data.json", "wb");
    if (!file) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_view);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error performing request: %s\n", curl_easy_strerror(res));
        return 1;
    }

    // Clean up libcurl
    curl_easy_cleanup(curl);
    fclose(file);
    fileRead();
}
int fileRead(){
    count=1;
     FILE *file = fopen("data.json", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read JSON data from file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *json_data = (char *)malloc(fileSize + 1);
    fread(json_data, 1, fileSize, file);
    fclose(file);
    json_data[fileSize] = '\0'; //terminate the string

    // Parse JSON string
    cJSON *root = cJSON_Parse(json_data);
    if (!root) {
        printf("Error parsing JSON.\n");
        free(json_data);
        return 1;
    }
    free(json_data);

    // Check if root is an array
    if (!cJSON_IsArray(root)) {
        printf("JSON root is not an array.\n");
        cJSON_Delete(root);
        return 1;
    }

    struct_n= cJSON_GetArraySize(root);
    

    // Getting json
    for (int i = 0; i < struct_n && i < MAX_ITEMS; i++) {
        cJSON *transaction = cJSON_GetArrayItem(root, i);
        cJSON *id = cJSON_GetObjectItem(transaction, "_id");
        cJSON *desc = cJSON_GetObjectItem(transaction, "desc");
        cJSON *cat = cJSON_GetObjectItem(transaction, "cat");
        cJSON *wallet = cJSON_GetObjectItem(transaction, "wallet");
        cJSON *amount = cJSON_GetObjectItem(transaction, "amount");
//copy each json

        if (id && desc && cat && amount) {
            strcpy(transactions[i].id, id->valuestring);
            strcpy(transactions[i].desc, desc->valuestring);
            strcpy(transactions[i].cat, cat->valuestring);
            transactions[i].amount = amount->valueint;
            if (wallet)
                strcpy(transactions[i].wallet, wallet->valuestring);
            else
                transactions[i].wallet[0] = '\0';

          
        }
    }
    printf("\033[H\033[J");
    printf(ANSI_ORANGE"\033[1mYour Expenses on recent times : \n\n"ANSI_RESET);
    printf(ANSI_GREEN"\033[1m%-10s %-25s %-10s %-20s %-10s\n", "S.N.", "Description", "Category", "Wallet", "Amount"ANSI_RESET);
    for (int i = 0; i < struct_n && i < MAX_ITEMS; i++) {
        printf("%-10d %-25s %-10s %-20s %-10d\n", count, transactions[i].desc, transactions[i].cat, transactions[i].wallet, transactions[i].amount);
        count++;
    }

    // Cleanup cJSON
    cJSON_Delete(root);

    return 0;

}
int deleteExpense(){
    int sn;
    printf("Enter S.N for the expense to delete : ");
    scanf("%d",&sn);
    if(sn>count){
        printf("Invalid Selection");
    }
    //handling delete request
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    //url for delete request
    long status_code;
    char url[100];
    strcpy(url, "http://localhost:3000/expense/del/");
      curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
    
    if(status_code==200){
        printf(ANSI_RED"\n Deleted Successfull"ANSI_RESET);
    }

    // Cleanup libcurl
    curl_easy_cleanup(curl);
    sleep(3);
    printf("\033[H\033[J"); 
    return 0;
}

