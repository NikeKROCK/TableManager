#pragma once
using namespace std;
#include"Time.h"
//����---------------------------------------------------------------------------------------------
class Table {
private:
    Time StartTime;//����� ��� �������� �������, ������� � �������� ���� �������������
    Time UsedTime;//��������� ����� ������ �����
    int Money{ 0 };//����������� �����
    string ClientName{ "" };
public:
    //��� ������ � ������������� ������, ������� ���������� ��������� 
public:
    //������� ��������������
    bool IsBusy() { return ClientName != ""; }
    void ClientLeft(Time at, int price) {
        if (ClientName != "") {
            UsedTime = UsedTime + at - StartTime;
            Money += price * (((at - StartTime).GetMinutes() / 60) + ((at - StartTime).GetMinutes() % 60 > 0 ? 1 : 0));
            ClientName = "";
        }
    }
    string Result() {
        return to_string(Money) + ' ' + UsedTime.GetString();
    }
    string GetClientName() {
        return ClientName;
    }
    bool ClientSet(string name, Time at, int price) {
        if (IsBusy()) { cout << at.GetString() + " 13 ThePlaceIsBusy\n"; return false; }
        else {
            ClientLeft(at, price);
            ClientName = name;
            StartTime.SetMinutes(at.GetMinutes());
            return true;
        }
    }
};