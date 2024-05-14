#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
//�����--------------------------------------------------------------------------------
class Time {
private:
    //������
    int Minutes{ 0 };
public:
    //������������ �� ������, ��� ��� ���� ������, ���������� ������� ������� � �������, �������������� �������� ������ 
public:
    //������� ��������������
    int GetMinutes() { return Minutes; }
    string GetString() {
        int hours = (Minutes / 60) % 24;
        string ret = "";
        if (hours < 10)ret += '0';
        ret += to_string(hours);
        ret += ':';
        if ((Minutes % 60) < 10)ret += '0';
        ret += to_string(Minutes % 60);
        return ret;
    }
    void SetMinutes(int min) {
        Minutes = min;
    };
    void SetFromString(string from) {
        if (from.size() == 5) {
            Minutes = (stoi(string(1, from[0])) * 10 + stoi(string(1, from[1]))) * 60 + stoi(string(1, from[3])) * 10 + stoi(string(1, from[4]));
        }
        else {
            cout << "������:�������� ������ �������\n";
        }
    }
public:
    //�������������� �������
    friend Time operator+(const Time& left, const Time& right);
    friend Time operator-(const Time& left, const Time& right);
    friend bool operator>(const Time& left, const Time& right);
};
//�������� ���������� ������� Time �� ������
ifstream& operator>>(std::ifstream& in, Time& t) {
    string from;
    in >> from;
    t.SetFromString(from);
    return in;
}
//�������� ����������� ������� Time
bool operator>(const Time& left, const Time& right) {
    return left.Minutes > right.Minutes;
}
Time operator-(const Time& left, const Time& right) {
    Time ret;
    ret.Minutes = left.Minutes - right.Minutes;
    return ret;
}
Time operator+(const Time& left, const Time& right) {
    Time ret;
    ret.Minutes = left.Minutes + right.Minutes;
    return ret;
}