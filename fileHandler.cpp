//
// Created by Julien on 26.09.17.
//

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "fileHandler.h"

#define PAD_T 0.6
#define PAD_B 0.6
#define PAD_L 0.75
#define PAD_R 0.75
#define DELIMITER ','

class Exception;

// Inspired and adapted from https://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
void split(const string& s, char delim, vector<string>& v) {
   auto i = 0;
   auto pos = s.find(delim);
   while (pos != string::npos) {
      string tmpStr = s.substr(i, pos-i);
      if (tmpStr.front() == '"') {
         tmpStr = tmpStr.substr(1, tmpStr.length());
         i = ++pos;
         pos = s.find(delim, pos);
         tmpStr.append(s.substr(i-1, pos-i));
      }

      v.push_back(tmpStr);
      i = ++pos;
      pos = s.find(delim, pos);

      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

void splitTypes(const string& s, char delim, vector<string>& v) {
   auto i = 0;
   auto pos = s.find(delim);
   if (pos == string::npos)
      v.push_back(s);
   else {
      while(pos != string::npos) {
         v.push_back(s.substr(i, pos-i));
         i = ++pos;
         pos = s.find(delim, pos);

         if (pos == string::npos);
            v.push_back(s.substr(i, s.length()));
      }
   }
}

const bool estDuMois(const string& date) {
   const time_t DATE = time(NULL);
   const char *FORMAT = "%Y-%m";
   tm *localTime = localtime(&DATE);
   char timestamp[8];
   strftime(timestamp, sizeof(timestamp), FORMAT, localTime);
   return string(timestamp) == date.substr(0, 7);
}

bool loadAvailableBeers(vector<Beer>& beerList, const string& FILENAME, const string& FILENAME_TYPES) {

   unordered_map<int, string> map = unordered_map<int, string>();
   ifstream typesFiles;
   typesFiles.open(FILENAME_TYPES);

   if (not typesFiles.is_open())
      return false;

   string lineTypes, nameTypes;
   int cntTypes = 0;

   while ( getline(typesFiles, lineTypes) ) {
      if (0 != cntTypes) {
         try {
            vector<string> params = vector<string>();
            split(lineTypes, DELIMITER, params);

            map.insert( { params.at(0).empty() ? -1 : stoi(params.at(0)), params.at(1) } );

         } catch(exception& e) {
            cerr << "Erreur lors de la lecture d'une bière ! (" << e.what() << ")" << endl;
            exit(-1);
         }
      }
      ++cntTypes;
   }

   ifstream csvFile;
   csvFile.open(FILENAME);

   if (not csvFile.is_open())
      return false;

   string line, name;
   int cnt = 0;

   while ( getline(csvFile, line) ) {
      if (0 != cnt) {
         try {
            vector<string> params = vector<string>();
            split(line, DELIMITER, params);

            string desc = params.at(7).empty() ? "" : params.at(7);
            if (desc.front() == '"' && desc.back() == '"')
               desc = desc.substr(1, params.at(7).length()-2);

            vector<string> v = vector<string>();
            splitTypes(params.at(3), DELIMITER, v);

            for (size_t i = 0; i < v.size(); ++i) {
               if (!v.at(i).empty())
                  v.at(i) = map.at(stoi(v.at(i)));
            }

            Beer b = Beer(
                    params.at(0),
                    params.at(1),
                    desc,
                    params.at(5).empty() ? 0 : (unsigned)stoi(params.at(5)),
                    v,
                    params.at(4).empty() ? 0. : stod(params.at(4)),
                    params.at(2).empty() ? 0 : (unsigned)stoi(params.at(2)),
                    estDuMois(params.at(6))
            );
            beerList.push_back(b);
         } catch(exception& e) {
            cerr << "Erreur lors de la lecture d'une bière ! (" << e.what() << ")" << endl;
            exit(-1);
         }
      }
      ++cnt;
   }

   return true;
}

void getLatexFileName(const string& LIST_NAME, string* filename, const string& PREFIX, const string& suffix) {
   const time_t DATE = time(NULL);
   const char *FORMAT = "%Y-%m-%d";
   tm *localTime = localtime(&DATE);
   char timestamp[12];
   strftime(timestamp, sizeof(timestamp), FORMAT, localTime);
   *filename = PREFIX + LIST_NAME + "_" + string(timestamp) + suffix + ".tex";
}

bool createLatexFile(const string& FILENAME, const string& docName) {
   ofstream latexFile;
   latexFile.open(FILENAME, ios::out);

   if (not latexFile.is_open())
      return false;

   latexFile << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"                                                 << endl
             << "% Medium Length Professional CV"                                                           << endl
             << "% LaTeX Template"                                                                          << endl
             << "% Version 2.0 (8/5/13)"                                                                    << endl
             << "%"                                                                                         << endl
             << "% This template has been downloaded from:"                                                 << endl
             << "% http://www.LaTeXTemplates.com"                                                           << endl
             << "%"                                                                                         << endl
             << "% Original author:"                                                                        << endl
             << "% Trey Hunner (http://www.treyhunner.com/)"                                                << endl
             << "%"                                                                                         << endl
             << "% Important note:"                                                                         << endl
             << "% This template requires the resume.cls file to be in the same directory as the"           << endl
             << "% .tex file. The resume.cls file provides the resume style used for structuring the"       << endl
             << "% document."                                                                               << endl
             << "%"                                                                                         << endl
             << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"                                                 << endl
             << "%"                                                                                         << endl
             << "%----------------------------------------------------------------------------------------" << endl
             << "%\tPACKAGES AND OTHER DOCUMENT CONFIGURATIONS"                                             << endl
             << "%----------------------------------------------------------------------------------------" << endl
             << "\\documentclass{resume} % Use the custom resume.cls style"                                 << endl
             << "%"                                                                                         << endl
             << "\\usepackage[french]{babel}"                                                               << endl
             << "\\usepackage[utf8]{inputenc}"                                                              << endl
             << "\\usepackage[T1]{fontenc}"                                                                 << endl
             << "\\usepackage{textcomp}"                                                                    << endl
             << "\\usepackage{lmodern}"                                                                     << endl
             << "\\usepackage{graphicx}"                                                                    << endl
             << "\\usepackage[top=" << PAD_T << "in, bottom=" << PAD_B << "in, left="
                                    << PAD_L << "in, right=" << PAD_R << "in]{geometry} % Document margins"
                                                                                                    << endl << endl
             << "\\name{" << docName << "}"                                                         << endl << endl
             << "\\renewcommand{\\familydefault}{\\sfdefault}"                                      << endl << endl
             << "\\begin{document}"                                                                 << endl << endl;
   latexFile.close();

   return true;
}

bool printBeersOnLatex(const vector<Beer>& LIST_BEERS, const string& FILENAME) {
   ofstream latexFile;
   latexFile.open(FILENAME, ios::out | ios::app);

   if (not latexFile.is_open())
      return false;

   for (Beer b : LIST_BEERS) {
      latexFile << "\t{\\bf " << b.getName() << "}";
      if (!b.isSoftDrink()) {
         latexFile << " – {\\em";
         for (string &type : b.getTypes())
            latexFile << " " << type;
         latexFile << " }";
         latexFile << " – {\\em " << b.getAbv() << "\\% Vol.}";
      }
      latexFile << " \\hfill {\\em " << b.getPrice()
                << " CHF}";
      if (!b.getDescription().empty())
         latexFile << " \\\\" << endl << "\t" << b.getDescription();
      latexFile << " \\\\" << endl << endl;
   }

   latexFile.close();
}

bool endLatexFile(const string& FILENAME) {
   ofstream latexFile;
   latexFile.open(FILENAME, ios::out | ios::app);

   if (not latexFile.is_open())
      return false;

   latexFile << "\\end{document}" << endl;
   latexFile.close();

   return true;
}

bool startSection(const string& FILENAME, const string& SECTION_NAME, bool startNewPage) {
   ofstream latexFile;
   latexFile.open(FILENAME, ios::out | ios::app);

   if (not latexFile.is_open())
      return false;

   if (startNewPage)
      latexFile << "\t\\newpage" << endl;

   latexFile << "\t\\begin{rSection}{" << SECTION_NAME << "}" << endl << endl;
   latexFile.close();

   return true;
}

bool endSection(const string& FILENAME) {
   ofstream latexFile;
   latexFile.open(FILENAME, ios::out | ios::app);

   if (not latexFile.is_open())
      return false;

   latexFile << "\t\\end{rSection}" << endl << endl;
   latexFile.close();

   return true;
}

bool printBreweryLogo(const string& FILENAME, const string& IMG_NAME) {
   ofstream latexFile;
   latexFile.open(FILENAME, ios::out | ios::app);

   if (not latexFile.is_open())
      return false;

   latexFile << "\t\\begin{center}" << endl
             << "\t\t\\includegraphics[width=0.8\\linewidth]{" << IMG_NAME << "}" << endl
             << "\t\\end{center}" << endl << endl;
   latexFile.close();

   return true;
}