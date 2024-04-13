#include "Expense.h"
#include<stdio.h>
#include <curl/curl.h>



struct Expense{
    char id[200];
    char description[50];
    char cat[40];
    int amt;
    char wallet[40];
    char dat[60];
}send_data;
//get data function
int getData(){
    printf("Enter id");
    scanf("%s",send_data.id);
    printf("Category of Expense :");
    scanf("%s",send_data.cat);
    printf("Enter Description : ");
    scanf("%s",send_data.description);
    printf("Enter Expense Amount :");
    scanf("%d",&send_data.amt);
    printf("Enter date");
    scanf("%s",send_data.dat);
    printf("Enter wallet you used");
    scanf("%s",send_data.wallet);
}

// Expense api functions

size_t write_callback1(char *ptr, size_t size, size_t nmemb, void *userdata) {
    printf("%.*s", (int)(size * nmemb), ptr);
    return size * nmemb;
}
int addExpense()
     {
        CURL *curl;
    CURLcode res;
    char *url = "http://localhost:3000/expense/post"; // Replace with your API endpoint

    // Initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Format the data into JSON
        char data[512]; // Adjust buffer size as needed
        snprintf(data, sizeof(data), "{\"id\":\"%s\",\"desc\":\"%s\",\"cat\":\"%s\",\"amount\":%d,\"wallet\":\"%s\"}",
                 send_data.id, send_data.description, send_data.cat, send_data.amt, send_data.wallet);
         printf("JSON Data:\n%s\n", data);
        // Set POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        // Perform the POST request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    return 0;
}