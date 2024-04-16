#include "Expense.h"
#include <stdio.h>
#include <curl/curl.h>
#include<string.h>
#include<stdlib.h>
struct Expense
{
    char id[200];
    char description[50];
    char cat[40];
    int amt;
    char wallet[40];
    char dat[60];
} send_data;

//structure to store file data
struct exp{
    char id[200];
    char descriptioon[50];
    char cat[40];
    int amt;
    char wallet[40];
};

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

    // Set the URL to retrieve data from
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/expense/get/6617fe24687e8ff747c06714");

    // Set the callback function to write data into a file
    FILE *file = fopen("data.txt", "wb");
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

}



