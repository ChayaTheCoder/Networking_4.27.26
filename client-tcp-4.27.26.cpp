/************************* INCLUDES **************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

/************************* MACROS ****************************/
#define MAXBUF 1000000
#define FALSE 0
#define TRUE 1

/************************* VARIABLES ****************************/
char bufin[MAXBUF+1];
char bufout[MAXBUF+1];
int n;

int main(int argc, char *argv[])
{
    struct sockaddr_in srvaddr;   // FIXED: declare server address struct
    int clnts;                    // FIXED: declare client socket

    // Get the port number and dotted decimal address of server
    if (argc == 3)
    {
        char *hostnum = argv[1];
        int portnum = atoi(argv[2]);

        // STEP #1: Initialize address data structure
        srvaddr.sin_family = AF_INET;
        srvaddr.sin_addr.s_addr = inet_addr(hostnum);
        srvaddr.sin_port = htons(portnum);

        // Run indefinitely until user enters /QUIT
        while (true)
        {
            // STEP #3: Create socket and connect to server
            clnts = socket(PF_INET, SOCK_STREAM, 0);

            if (connect(clnts, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) < 0)
            {
                cout << "Error: could not connect to server" << endl;
                exit(-1);
            }

            cout << "--------------------------------------" << endl;
            cout << "Connected to server at IP address = " << hostnum;
            cout << " and Port = " << portnum << endl;

            cout << "Input your request (99 characters max). Enter /QUIT when finished:" << endl;

            // Read message from user
            string msg;
            getline(cin, msg);

            if (msg == "/QUIT")
            {
                close(clnts);
                break;
            }

            cout << "Message: " << msg << endl;
            cout << "Message size: " << msg.length() << endl;

            // STEP #4: Send request to server (FIXED)
            send(clnts, msg.c_str(), msg.length(), 0);

            // Half-close writing end so server knows request is complete (FIXED)
            shutdown(clnts, 1);

            // STEP #5: Receive response from server
            char *bp = bufin;
            int cnt = MAXBUF;

            while ((n = recv(clnts, bp, cnt, 0)) > 0)
            {
                bp += n;
                cnt = MAXBUF - (bp - bufin);
            }

            *bp = '\0';

            if (n != -1)
            {
                cout << "Response was: " << bufin << endl;
            }
            else
            {
                perror("recv failed");
                exit(-1);
            }

            // Close socket
            close(clnts);
        }
    }
    else
    {
        cout << "usage: client-tcp <hostnum> <portnum>" << endl;
        exit(-1);
    }

    return 0;
}
