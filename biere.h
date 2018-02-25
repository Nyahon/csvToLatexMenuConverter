//
// Created by Julien on 26.09.17.
//

#include <string>
#include <iomanip>
#include <unordered_map>
#include <vector>

#pragma once

using namespace std;

class Beer {
   private:
      string name;
      string brewery;
      string description;
      unsigned price;
      vector<string> types;
      double abv;             // in alcohol percentage
      unsigned volume;        // in ml
      bool beerOfTheMonth;

   public:
      Beer(string& n, string& b, string& d, const unsigned p, const vector<string>& t,
            const double a, const unsigned v, const bool e);

      void setName(string &n);
      void setBrewery(string &b);
      void setDescription(string& d);
      void setPrice(const unsigned p);
      void setType(const vector<string>& t);
      void setAbv(const double a);
      void setVolume(const unsigned v);
      void setBeerOfTheMonth(const bool isBeerOfTheMonth);

      string getName() const;
      string getBrewery() const;
      string getDescription() const;
      unsigned getPrice();
      vector<string>& getTypes();
      double getAbv();
      unsigned getVolume();
      bool isBeerOfTheMonth();
      bool isSoftDrink();

      friend bool operator == (const Beer& b1, const Beer& b2) {
         return b1.getName() == b2.getName();
      }

      friend bool operator < (const Beer& b1, const Beer& b2) {
         if (b1.getBrewery() > b2.getBrewery())
            return false;
         else if (b1.getBrewery() == b2.getBrewery())
            return b1.getName() < b2.getName();
         else
            return true;
      }
};
