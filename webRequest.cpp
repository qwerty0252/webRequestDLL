#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

extern "C" {
    __declspec(dllexport) int makeGetRequest() {
         WSADATA wsaData;
         int data=0;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            printf("WSAStartup failed.\n");
            return 0;
        }

        SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        struct hostent *host;
        host = gethostbyname("127.0.0.1");

        SOCKADDR_IN SockAddr;
        SockAddr.sin_port = htons(8000);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

        if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
            printf("Could not connect");
            system("pause");
            return 1;
        }
        //here is the request url: /test2, host: 127.0.0.1,
        send(Socket, "GET /test HTTP/1.1\r\nHost: your-server-ip\r\nConnection: close\r\n\r\n", strlen("GET /test HTTP/1.1\r\nHost: your-server-ip\r\nConnection: close\r\n\r\n"), 0);
        char buffer[10000];

        int nDataLength;
        int headersPrinted = 0;
        char numberBuffer[20];

    while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
        int i = 0;

        char* responseString = strstr(buffer, "Response");
        if (responseString != NULL) {
            if (!headersPrinted) {
                printf("%s", responseString);
                headersPrinted = 1;
            }
            int j = 0;
            while (responseString[i] != '\0' && (responseString[i] < '0' || responseString[i] > '9')) {
                i++;
            }
            
            while (responseString[i] >= '0' && responseString[i] <= '9') {
                numberBuffer[j++] = responseString[i++];
            }
            numberBuffer[j] = '\0';

            printf("Number: %s\n", numberBuffer);

            int dynamicNumber = atoi(numberBuffer);
            data =  dynamicNumber;
            printf("Integer Value: %d\n", dynamicNumber);
        }
    }

    closesocket(Socket);
    WSACleanup();

    return data;
    }

    __declspec(dllexport) int makePostRequest(float a, float b, float c) {
    WSADATA wsaData;
    float prediction;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct hostent* host;
    host = gethostbyname("127.0.0.1");

    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(8000);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
        printf("Could not connect");
        system("pause");
        return 1;
    }

    char postData[100];  // Allocate memory for postData
    sprintf(postData, "{\"a\":%f, \"b\":%f, \"c\":%f}", a, b, c);// here is the post data
    char request[1000];    //here is the request url: /test2, host: 127.0.0.1,  
    sprintf(request, "POST /test2 HTTP/1.1\r\nHost: 127.0.0.1\r\nContent-Type: application/json\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s", strlen(postData), postData);

    send(Socket, request, strlen(request), 0);

    char buffer[10000];

    int nDataLength;
    int headersPrinted = 0;
    char numberBuffer[20];

    while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
        int i = 0;

        char* responseString = strstr(buffer, "Response");
        if (responseString != NULL) {
            if (!headersPrinted) {
                printf("%s", responseString);
                headersPrinted = 1;
            }

            int j = 0;
            while (responseString[i] != '\0' && !isdigit(responseString[i]) && responseString[i] != '-' && responseString[i] != '.') {
                i++;
            }

            while (isdigit(responseString[i]) || responseString[i] == '.' || responseString[i] == '-') {
                numberBuffer[j++] = responseString[i++];
            }
            numberBuffer[j] = '\0';

            printf("\n");

            printf("Number: %s\n", numberBuffer);
            float dynamicNumber = atof(numberBuffer);
            printf("Float Value: %f\n", dynamicNumber);
            prediction = dynamicNumber;
            printf("Prediction Value: %f\n", prediction);
        }
    }
    
    closesocket(Socket);
    WSACleanup();

    return prediction;
}

}


