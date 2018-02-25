//
// Created by Julien on 23.02.18.
//

#include <vector>
#include <string>

#pragma once

// Taken from https://stackoverflow.com/a/39883851/7986459
std::string iso_8859_1_to_utf8(std::string &str) {
   string strOut;
   for (std::string::iterator it = str.begin(); it != str.end(); ++it)
   {
      uint8_t ch = *it;
      if (ch < 0x80) {
         strOut.push_back(ch);
      }
      else {
         strOut.push_back(0xc0 | ch >> 6);
         strOut.push_back(0x80 | (ch & 0x3f));
      }
   }
   return strOut;
}