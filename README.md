# csvToLatexMenuConverter
_(could not find a shorter name)_

## Situation
I wrote this piece of code for a student bar I am in charge of.  
We use a [Dolibarr](https://www.dolibarr.org) instance to keep track of our stocks and the orders we make, among other
things. We make our best to offer the greatest diversity of beers all along the year. I wanted to have a way to display
the beers in stock for the clients to have a look at the beers and for our benevolent to have a document to refer to for
the beers we have, their types, brewery, prices,...  

The programmes does the following: it uses a CSV file having a specific format (defined by our Dolibarr instance) to
produces one to two latex documents (depends if there is a brewery of the month or not). Those latex documents are
formated to produce a simple menu with some basic informations. 

The original latex source is a resume template made by [Trey Hunner](http://www.treyhunner.com/). 

## Constraints 
 * Load beers list according to this format :  
   **Name,Brewery,Volume,BeerType,% ABV,PriceByUnit,Date,Description**  
   In the Date field, only the month and year are used. The goal is to identify the current
   month's brewery for promotion (have a dedicated page).    
 * Some strings to display in the latex file were encoded in ISO 8859-1 which was not really suitable. It may produce some errors with other caracters (not tested).  
   [The solution for encoding from ISO 8859-1 to utf-8](https://stackoverflow.com/a/39883851/7986459)
   was **very** useful.  
  
 ## Disclamer
 **Warning : this programme does make allocation memory that are not retrieved. Will maybe be corrected.  
 Do use with caution.**
 
 ## Licence
 This code is under [GNU GPL 3](https://www.gnu.org/licenses/gpl-3.0.txt).