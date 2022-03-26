///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab08d_animal_farm_1_to_clion - EE 205 - Spr 2022
///
/// @file reportCats.cpp
/// @version 1.0
///
/// @author Mark Nelson <marknels@hawaii.edu>
/// @date   14_Mar_2022
///////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstring>  // For strncmp
#include <stdexcept> // To throw if the enumName functions are bad

#include "config.h"
#include "reportCats.h"
#include "catDatabase.h"

using namespace std;

/*
void printAllCats() {
#ifdef DEBUG
   printf( "numCats = [%lu]\n", numCats ) ;
#endif

   for( size_t i = 0 ; i < numCats ; i++ ) {
      printCat( i ) ;
   }
}


size_t findCatByName( const char* name ) {
   if( name == nullptr ) {
      return BAD_CAT ;  // Silently return... no cat found
   }

   for( size_t i = 0 ; i < numCats ; i++ ) {
      if( strncmp( name, cats[i].name, MAX_CAT_NAME ) == 0 ) {  // Found a match!
         return i ;
      }
   }

   return BAD_CAT ; // No name matched
}
*/


/// @throws logic_error if the enum is not mapped to a string.
const char* genderName( const enum Gender gender ) {
   switch( gender ) {
      case UNKNOWN_GENDER: return "Unknown" ;
      case MALE:           return "Male"    ;
      case FEMALE:         return "Female"  ;
   }
   throw logic_error(PROGRAM_NAME ": Gender name not mapped to a string value");
}


/// @throws logic_error if the enum is not mapped to a string.
const char* breedName( const enum Breed breed ) {
   switch( breed ) {
      case UNKNOWN_BREED: return "Unknown"    ;
      case MAINE_COON   : return "Maine Coon" ;
      case MANX         : return "Manx"       ;
      case SHORTHAIR    : return "Shorthair"  ;
      case PERSIAN      : return "Persian"    ;
      case SPHYNX       : return "Sphynx"     ;
   }
   throw logic_error(PROGRAM_NAME ": Breed name not mapped to a string value");
}


/// @throws logic_error if the enum is not mapped to a string.
const char* colorName ( const enum Color color ) {
   switch( color ) {
      case UNKNOWN_COLOR: return "Unknown color" ;
      case BLACK        : return "Black" ;
      case WHITE        : return "White" ;
      case RED          : return "Red"   ;
      case BLUE         : return "Blue"  ;
      case GREEN        : return "Green" ;
      case PINK         : return "Pink"  ;
   }
   throw logic_error(PROGRAM_NAME ": Color name not mapped to a string value");
}