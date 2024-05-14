#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"Tables.h"
#include"Time.h"
using namespace std;
//эвенты------------------------------------------------------------------------------------------------
void ClientLeft(string name, Time at, int price,
    vector<string>& queue, vector<Table>& Tables, vector<string>& guests) {
    bool isComputer = false;
    bool isQueue = false;
    int pos = -1;
    //поиск по очереди, столам, только пришедшим
    for (int i = 0; i < queue.size(); i++) {
        if (name == queue[i]) {
            isQueue = true;
            pos = i;
            break;
        }
    }
    for (int i = 0; i < Tables.size(); i++) {
        if (name == Tables[i].GetClientName()) {
            pos = i;
            isComputer = true;
            break;
        }
    }
    for (int i = 0; i < guests.size(); i++) {
        if (name == guests[i]) {
            pos = i;
            break;
        }
    }
    if (pos == -1) { cout << at.GetString() + " 13 ClientUnknown\n"; }
    else {
        if (isComputer) { Tables[pos].ClientLeft(at, price); }
        else if (isQueue) { queue.erase(queue.begin() + pos); }
        else { guests.erase(guests.begin() + pos); };
        if (isComputer && queue.size() > 0) {
            cout << at.GetString() + " 12 " + queue[0] + to_string(pos) << '\n';//перемещение первого из очереди, если стол свободен
            Tables[pos].ClientSet(queue[0], at, price);
            queue.erase(queue.begin());
        }
    }
}
void ClientCome(vector<string>& queue, vector<string>& guests, vector<Table>& Tables,
    Time Start, Time at, string name) {
    if (Start > at) { cout << at.GetString() + " 13 NotOpenYet\n"; }
    else {
        //поиск по очереди, столам, только пришедшим
        int pos = -1;
        for (int i = 0; i < queue.size(); i++) {
            if (name == queue[i]) {
                pos = i;
                break;
            }
        }
        for (int i = 0; i < Tables.size(); i++) {
            if (name == Tables[i].GetClientName()) {
                pos = i;
                break;
            }
        }
        for (int i = 0; i < guests.size(); i++) {
            if (name == guests[i]) {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            cout << at.GetString() + " 13 YouShallNotPass\n";
        }
        else { guests.push_back(name); }
    }
}

void ClientWait(Time at, string name, int price,
    vector<string>& guests, vector<string>& queue, vector<Table>& Tables) {
    bool isComputer = false;
    bool isQueue = false;
    int pos = -1;
    //поиск по очереди, столам, только пришедшим
    for (int i = 0; i < queue.size(); i++) {
        if (name == queue[i]) {
            isQueue = true;
            pos = i;
            break;
        }
    }
    for (int i = 0; i < Tables.size(); i++) {
        if (name == Tables[i].GetClientName()) {
            pos = i;
            isComputer = true;
            break;
        }
    }
    for (int i = 0; i < guests.size(); i++) {
        if (name == guests[i]) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {//если найден
        cout << at.GetString() + " 13 NoClientToWait\n";
    }
    else {
        if (queue.size() > Tables.size() && !isQueue) {
            cout << at.GetString() + " 11 " + name + '\n';
        }
        else {
            for (int i = 0; i < Tables.size(); i++) {
                if (Tables[i].GetClientName() == "") {//если есть свободный стол
                    cout << at.GetString() << " 13 ICanWaitNoLonger!\n";
                    break;
                }
            }
            if (isComputer) { Tables[pos].ClientLeft(at, price); }
            else if (isQueue) {
                cout << at.GetString() + " 13 I was already at queue!\n";
                queue.erase(queue.begin() + pos);
            }
            else { guests.erase(guests.begin() + pos); }
            queue.push_back(name);
        }
    }
}
void ClientSit(string name, Time at, int price, int TableNumber,
    vector<string>& queue, vector<Table>& Tables, vector<string>& guests) {
    bool isComputer = false;
    bool isQueue = false;
    int pos = -1;
    //поиск по очереди, столам, только пришедшим
    for (int i = 0; i < queue.size(); i++) {
        if (name == queue[i]) {
            isQueue = true;
            pos = i;
            break;
        }
    }
    for (int i = 0; i < Tables.size(); i++) {
        if (name == Tables[i].GetClientName()) {
            pos = i;
            isComputer = true;
            break;
        }
    }
    for (int i = 0; i < guests.size(); i++) {
        if (name == guests[i]) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        cout << at.GetString() + " 13 ClientUnknown\n";
    }
    else {//если найден
        if (TableNumber >= Tables.size() || TableNumber<0) {
            cout << at.GetString() + " 13 Table isn't exists\n";
        }
        else
        {
            if (isComputer) {
                if (pos == TableNumber) { at.GetString() + " 13 Table isn't changed\n"; }
                if (Tables[TableNumber].ClientSet(name, at, price)) { Tables[pos].ClientLeft(at, price); }
            }
            else {
                if (Tables[TableNumber].ClientSet(name, at, price)) {
                    isQueue ? queue.erase(queue.begin() + pos) : guests.erase(guests.begin() + pos);
                }
            }

        }
    }
}