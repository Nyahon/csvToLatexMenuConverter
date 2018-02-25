//
// Created by Julien on 26.09.17.
//

#include <iostream>
#include "biere.h"
#include "utils.h"

Beer::Beer(string& n, string& b, string& d, const unsigned p, const vector<string>& t, const double a,
             const unsigned v, const bool e) {
   setName(n);
   setBrewery(b);
   setDescription(d);
   setPrice(p);
   setType(t);
   setAbv(a);
   setVolume(v);
   setBeerOfTheMonth(e);
}

// We have to change the encoding for the latex file to be correctly interpreted
void Beer::setName(string &n) {
   this->name = iso_8859_1_to_utf8(n);
}

void Beer::setBrewery(string &b) {
   this->brewery = iso_8859_1_to_utf8(b);
}

void Beer::setDescription(string& d) {
   this->description = iso_8859_1_to_utf8(d);
}

void Beer::setPrice(const unsigned p) {
   this->price = p;
}

void Beer::setType(const vector<string>& t) {
   this->types = t;
}

void Beer::setAbv(const double a) {
   this->abv = a;
}

void Beer::setVolume(const unsigned v) {
   this->volume = v;
}

void Beer::setBeerOfTheMonth(const bool e) {
   this->beerOfTheMonth = e;
}

string Beer::getName() const {
   return name;
}

string Beer::getBrewery() const {
   return brewery;
}

string Beer::getDescription() const {
   return description;
}

unsigned Beer::getPrice() {
   return price;
}

vector<string>& Beer::getTypes() {
   return types;
}

double Beer::getAbv() {
   return abv;
}

unsigned Beer::getVolume() {
   return volume;
}

bool Beer::isBeerOfTheMonth() {
   return beerOfTheMonth;
}

bool Beer::isSoftDrink() {
   return brewery.empty();
}