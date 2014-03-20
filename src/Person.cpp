/*
 * Person.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: Charles
 */

#include "Person.hpp"


Person::Person() :
    _expenses(0),
    _payback(0) {

}


Person::Person(const string& iName,const string& iPhone,float iExpenses) :
                _name(iName),
                _phone(iPhone),
                _expenses(iExpenses),
                _payback(0)
{
}

Person::Person(const string& iName,const string& iPhone,float iExpenses,const Group* iLink) :
                _name(iName),
                _phone(iPhone),
                _expenses(iExpenses),
                _payback(0),
                _link(iLink)
{
}

void Person::setName(const string& iName){
        _name = iName;
}

void Person::setLink(const Group* iLink){
        _link = iLink;
}

void Person::setPhone(const string& iPhone){
        _phone = iPhone;
}

void Person::setExpenses(float iExpenses){
        _expenses = iExpenses;
}

void Person::setPayback(float iPayback){
        _payback = iPayback;
}

const string& Person::getName(){
        return _name;
}

const Group* Person::getLink(){
        return _link;
}

const string& Person::getPhone(){
        return _phone;
}

float Person::getExpenses() const{
        return _expenses;
}

float Person::getPayback(){
        return _payback;
}





void Person::operatePayback(const float iExpensesPerPerson) {
    _payback = _expenses - iExpensesPerPerson;
}


Person::~Person() {

}
