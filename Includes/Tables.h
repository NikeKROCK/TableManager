#pragma once
using namespace std;
#include"Time.h"
//стол---------------------------------------------------------------------------------------------
class Table {
private:
    Time StartTime;//буфер для хранения времени, начиная с которого стол использовался
    Time UsedTime;//суммарное время работы стола
    int Money{ 0 };//накопленная сумма
    string ClientName{ "" };
public:
    //нет смысла в инициализации данных, которые изначально определны 
public:
    //функции взаимодействия
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