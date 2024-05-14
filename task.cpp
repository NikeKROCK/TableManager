#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Includes/Events.h"
#include"Includes/Tables.h"
#include"Includes/Time.h"
using namespace std;
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    if (argc < 2) {
        cout << "���������� ������� ��� ����� � �������� ��������� ��������� ������.\n";
        return 1;
    }
    ifstream ifs(argv[1]);
    if (!ifs) {
        cout << "�� ������� ������� ���� " << argv[1] << "\n";
        return 1;
    }
    //vector<string> ReadedFile;
    string ReadingLine;
    //������������� ����������
    int TablesNumber;
    if (!(ifs >> TablesNumber)) {
        cout << "\n ������:������ ������� ���������� ������\n";
        return 1;
    }
    Time StartTime;
    if (!(ifs >> StartTime)) {
        cout << "\n ������:������ ������� ����� ������\n";
        return 1;
    }
    Time EndTime;
    if (!(ifs >> EndTime)) {
        cout << "\n ������:������ ������� ����� ���������\n";
        return 1;
    }
    int Cost;
    if (!(ifs >> Cost)) {
        cout << "\n ������:������ ������� ����\n";
        return 1;
    }
    vector<string> Guests;
    vector<string> Queue;
    vector<Table> Tables(TablesNumber);
    //���� �������
    Time EventTime;
    int ID;
    string ClientName;
    int TableNubmber;
    cout << StartTime.GetString()<<'\n';
    while (ifs >> ReadingLine) {
        EventTime.SetFromString(ReadingLine);
        ifs >> ID;
        ifs >> ClientName;
        if (EventTime > EndTime) { cout << EventTime.GetString()<<' ' << ID << ' ' << ClientName << " We're already closed!\n"; }
        else {
            if (ID == 2) { ifs >> TableNubmber; }
            cout << EventTime.GetString() << ' ' << ID <<' ' << ClientName;//������� ������ ������ (����� �������)
            if (ID == 2) { cout <<' ' << TableNubmber << ' '; }
            cout << '\n';
            switch (ID)
            {
            case 1:
                ClientCome(Queue, Guests, Tables, StartTime, EventTime, ClientName);
                break;
            case 2:
                ClientSit(ClientName, EventTime, Cost, TableNubmber - 1, Queue, Tables, Guests);
                break;
            case 3:
                ClientWait(EventTime, ClientName, Cost, Guests, Queue, Tables);
                break;
            case 4:
                ClientLeft(ClientName, EventTime, Cost, Queue, Tables, Guests);
                break;
            default:
                break;
            }
        }
    }
    for (int i = 0; i < Tables.size(); i++) {
        if (Tables[i].GetClientName() != "") { 
            cout << EndTime.GetString() << " 11 " << Tables[i].GetClientName()<<'\n';
            Tables[i].ClientLeft(EndTime, Cost);
        }

    }
    cout << EndTime.GetString()<<'\n';
    for (int i = 0; i < Tables.size(); i++) {
        cout << i + 1 << ' ' << Tables[i].Result() << '\n';
    }
    

    return 0;
}