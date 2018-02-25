#include <iostream>
#include <vector>

#include "biere.h"
#include "fileHandler.h"

using namespace std;

int main() {

   const string LIST_NAME = "liste_biere";
   const string O_FILE_PREFIX = "../generatedLists/";
   const string I_FILE_PREFIX = "../csv/";
   const string IMG_FOLDER = "../img/";
   const string LIST_BEERS = "listeStocks.csv";
   const string LIST_TYPES = "listTypes.csv";
   const string IMG_FILE_NAME = "challensoise.png";
   const string DOC_NAME = "Liste des bières";
   const string DOC_NAME_MONTH = "Brasserie du mois";
   string latexFileName, latexFileNameMonth;
   vector<Beer> beerList = vector<Beer>();

   /************************************** IMPORTATION ***********************************************/
   // We import the drinks
   loadAvailableBeers(beerList, I_FILE_PREFIX + LIST_BEERS, I_FILE_PREFIX + LIST_TYPES);
   /************************************** SORT BEERS ************************************************/
   // We sort the drinks
   vector<Beer> softs = vector<Beer>();
   vector<Beer> beerOfTheMonth = vector<Beer>();
   vector<vector<Beer>> beers = vector<vector<Beer>>();
   bool added;
   for (Beer b : beerList) {
      if (b.isSoftDrink())
         softs.push_back(b);
      else if (b.isBeerOfTheMonth())
            beerOfTheMonth.push_back(b);
      else {
         added = false;
         for (size_t i = 0; i < beers.size(); ++i) {
            if (beers.at(i).at(0).getBrewery() == b.getBrewery()) {
               beers.at(i).push_back(b);
               added = true;
               break;
            }
         }
         if (!added) {
            vector<Beer> newBrewery = vector<Beer>();
            newBrewery.push_back(b);
            beers.push_back(newBrewery);
         }
      }
   }

   /************************************** MONTHLY BEERS ***********************************************/
   if (!beerOfTheMonth.empty()) {
      // We create a file for monthly beers
      getLatexFileName(LIST_NAME, &latexFileNameMonth, O_FILE_PREFIX, "_month");
      if (not createLatexFile(latexFileNameMonth, DOC_NAME_MONTH + " : " + beerOfTheMonth.at(0).getBrewery()))
         return EXIT_FAILURE;

      if (not printBreweryLogo(latexFileNameMonth, IMG_FOLDER + IMG_FILE_NAME))
         cerr << "Error while printing brewery of the month's logo !" << endl;
      printBeersOnLatex(beerOfTheMonth, latexFileNameMonth);

      // We end the latex file for monthly beers
      if (not endLatexFile(latexFileNameMonth))
         return EXIT_FAILURE;
   }

    /************************************** REGULAR BEERS ***********************************************/
   // We create the latex file with header
   getLatexFileName(LIST_NAME, &latexFileName, O_FILE_PREFIX);
   if (not createLatexFile(latexFileName, DOC_NAME))
      return EXIT_FAILURE;

   // We sort by brewery
   sort(beers.begin(), beers.end(), [&](const vector<Beer>& b1, const vector<Beer>& b2)
                     { return b1.at(0).getBrewery() < b2.at(0).getBrewery(); });

   for (vector<Beer> brewery : beers) {
      // We finally print the beers by brewery
      startSection(latexFileName, brewery.at(0).getBrewery());
      printBeersOnLatex(brewery, latexFileName);
      endSection(latexFileName);
   }

   // We print the softs
   startSection(latexFileName, "Softs", true);
   printBeersOnLatex(softs, latexFileName);
   endSection(latexFileName);

   // We end the latex file
   if (not endLatexFile(latexFileName))
      return EXIT_FAILURE;
   
   return EXIT_SUCCESS;

}