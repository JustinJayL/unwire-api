// unwire-api.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "curl\curl.h"
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

using std::string;
using std::cout;
using std::vector;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//need to get: access_token, expires time, user uuid
// by user i mean logged in user

char* stringToCharP(string str0) {
    int n = str0.length();
    char* char_p = new char[n + 1];
    strcpy_s(char_p, n + 1, str0.c_str());
    return char_p;
}

struct AuthToken {
    string accessToken;
    string userUUID;
    //todo: might need to change this to a time type or something
    double expiresAt;
};

//Post to /access with the old bearer
AuthToken refreshToken() {
    json j;
    const char* data = "";
    string readBuffer;
    CURL* curl = curl_easy_init();

    if (curl) {
        struct curl_slist* header_list;
        //don't need bearer token here
        header_list = curl_slist_append(NULL, "Accept: application/json");
        header_list = curl_slist_append(header_list, "Cookie: zuid=TODO");

        curl_easy_setopt(curl, CURLOPT_URL, "https://prod-nginz-https.wire.com/login?persist=true");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        curl_easy_perform(curl);
    }
    //todo: delete
    cout << readBuffer << std::endl;
    delete data;

    json jResp = json::parse(readBuffer);
    //TODO: 
    AuthToken authToken;

    //I guess that whole string is used as the bearer token.
    authToken.accessToken = jResp["access_token"];
    authToken.expiresAt = jResp["expires_in"];
    authToken.userUUID = jResp["user"];
    return authToken;
}


/*TODO, TEMP
uri: /login?persist=true
Host: prod-nginz-https.wire.com
Accept: application/json
Content-Type: application/json;charset=UTF-8
Origin: https://app.wire.com

{"password":"<passwordhere>","email":"<emailhere>"}
*/
//Login at /login, returns AuthToken
AuthToken initialLogin(string email, string password) {
    json jReq;
    jReq["password"] = password;
    jReq["email"] = email;

    string j_string = jReq.dump();
    long j_length = j_string.length();

    const char* data = stringToCharP(jReq.dump());
    string readBuffer;
    CURL* curl = curl_easy_init();
    if (curl) {
        struct curl_slist* header_list;
        header_list = curl_slist_append(NULL, "Accept: application/json");
        header_list = curl_slist_append(header_list, "Content-Type: application/json;charset=UTF-8");

        curl_easy_setopt(curl, CURLOPT_URL, "https://prod-nginz-https.wire.com/login?persist=true");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, j_length);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        curl_easy_perform(curl);
    }
    //todo: delete
    cout << readBuffer << std::endl;
    delete data;

    json jResp = json::parse(readBuffer);
    //TODO: 
    AuthToken authToken;

    //I guess that whole string is used as the bearer token.
    authToken.accessToken = jResp["access_token"];
    authToken.expiresAt = jResp["expires_in"];
    authToken.userUUID = jResp["user"];
    return authToken;
}

int main()
{
    std::ifstream file("file.json");
    json j;
    file >> j;
    AuthToken authToken = initialLogin(j["email", j["password"]);

    cout << "Login successfull. Access token: " + authToken.accessToken + ", UUID: " + authToken.userUUID << std::endl;
    return 0;

    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        cout << readBuffer << std::endl;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
