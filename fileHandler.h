//
// Created by Julien on 26.09.17.
//

#include <cstdio>
#include <string>
#include <vector>

#pragma once

#include "biere.h"

using namespace std;

bool loadAvailableBeers(vector<Beer>& beerList, const string& FILENAME, const string& FILENAME_TYPES);

void getLatexFileName(const string& LIST_NAME, string* filename, const string& PREFIX = "", const string& suffix = "");

bool createLatexFile(const string& FILENAME, const string& docName);

bool startSection(const string& FILENAME, const string& SECTION_NAME, bool startNewPage = false);

bool endSection(const string& FILENAME);

bool printBeersOnLatex(const vector<Beer>& LIST_BEERS, const string& FILENAME);

bool endLatexFile(const string& FILENAME);

bool printBreweryLogo(const string& FILENAME, const string& IMG_NAME);