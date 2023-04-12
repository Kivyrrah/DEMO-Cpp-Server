// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "iostream"
#include "stdio.h"
#include "string"
#include "afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            //Code ở đây nhé các bạn
            //----------------------------

            //Khai báo Socket
            AfxSocketInit(NULL);
            //Khai báo các Socket của Client
            CSocket client;
            //Khai báo các Socket của Server
            CSocket server;

            //Khởi tạo Socket với port 3153
            server.Create(3153);

            //Lắng nghe kết nối từ Client
            server.Listen();

            cout << "Dang ket noi toi Client..." << endl;

            //Chấp nhận kết nối của Client
            if (server.Accept(client)) 
            {
                cout << "Da ket noi voi Client thanh cong!" << endl;
            }

            char message[100];
            int len = 0;

            //Bắt đầu gửi tin nhắn
            while (true)
            {
                client.Receive(&len, sizeof(int), 0);
                char* temp = new char[len + 1];
                client.Receive(message, len, 0);

                temp[len] = 0;

                cout << "Client: " << temp << endl;
                delete temp;

                cout << "Hay nhap tin nhan cho Client: ";
                gets_s(message);
                len = strlen(message);

                client.Send(&len, sizeof(int), 0);
                client.Send(message, len, 0);

            }

            server.Close();
            //----------------------------
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        nRetCode = 1;
    }

    return nRetCode;
}
