#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Structure to hold response data
struct Response {
    char message[256];
    long status_code;
};

// Callback function to write the received data to a buffer
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Cast userdata to a pointer to struct Response
    struct Response *response = (struct Response *)userdata;

    // Copy received data (message) to the structure
    strncpy(response->message, ptr, sizeof(response->message) - 1);
    response->message[sizeof(response->message) - 1] = '\0';  // Ensure null termination

    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing libcurl\n");
        return 1;
    }

    // Set the URL to your Node.js API endpoint
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/user/login");

    // Set the Content-Type header
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the JSON data for POST request
    const char *json_data = "{\"username\": \"example_user\", \"password\": \"example_plassword\"}";
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
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return 0;
}
