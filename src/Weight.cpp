///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab10d_animal_farm_3 - EE 205 - Spr 2022
///
/// @file Weight.cpp
/// @version 1.0
///
/// @author Mark Nelson <marknels@hawaii.edu>
/// @date   06_Apr_2022
///////////////////////////////////////////////////////////////////////////////

#include <cassert>    // For assert()
#include <iostream>   // For cout
#include <stdexcept>  // For out_of_range
#include <iomanip>    // For setw() & setfill()

#include "config.h"
#include "Weight.h"

using namespace std;

const Weight::t_weight Weight::UNKNOWN_WEIGHT = -1 ;

const Weight::t_weight Weight::KILOS_IN_A_POUND = 0.453592 ;
const Weight::t_weight Weight::SLUGS_IN_A_POUND = 0.031081 ;  ///< @see https://en.wikipedia.org/wiki/Slug_(unit)

const string Weight::POUND_LABEL = "Pound" ; ///< @see https://en.wikipedia.org/wiki/Pound_(mass)
const string Weight::KILO_LABEL  = "Kilo" ;  ///< @see https://en.wikipedia.org/wiki/Kilogram
const string Weight::SLUG_LABEL  = "Slug" ;  ///< @see https://en.wikipedia.org/wiki/Slug_(unit)


Weight::Weight() noexcept {
   assert( validate() );
}



Weight::Weight( const Weight::t_weight newWeight ) {
   setWeight( newWeight );
   assert( validate() );
}


/// Once UnitOfWeight is set, it can't be changed
Weight::Weight( const Weight::UnitOfWeight newUnitOfWeight ) noexcept {
   unitOfWeight = newUnitOfWeight ;
   assert( validate() );
}


/// Once UnitOfWeight is set, it can't be changed
Weight::Weight( const Weight::t_weight newWeight, const Weight::UnitOfWeight newUnitOfWeight ) : Weight( newUnitOfWeight ) {
   setWeight( newWeight, newUnitOfWeight );
   assert( validate() );
}


/// Once maxWeight is set, it can't be changed
Weight::Weight( const Weight::t_weight newWeight, const Weight::t_weight newMaxWeight ) {
   setMaxWeight( newMaxWeight );
   setWeight( newWeight );
   assert( validate() );
}


/// Once UnitOfWeight is set, it can't be changed.
/// Once maxWeight is set, it can't be changed.
Weight::Weight( const Weight::UnitOfWeight newUnitOfWeight, const Weight::t_weight newMaxWeight ) : Weight( newUnitOfWeight ) {
   setMaxWeight( newMaxWeight );
   assert( validate() );
}


/// Once UnitOfWeight is set, it can't be changed.
/// Once maxWeight is set, it can't be changed.
Weight::Weight( const Weight::t_weight newWeight
        ,const Weight::UnitOfWeight newUnitOfWeight
        ,const Weight::t_weight newMaxWeight ) : Weight( newUnitOfWeight, newMaxWeight ) {
   setWeight( newWeight );
   assert( validate() );
}


bool Weight::isWeightKnown() const noexcept {
   assert( validate() );

   return bIsKnown;
}


bool Weight::hasMaxWeight() const noexcept {
   assert( validate() );

   return bHasMax;
}


/// If the weight is not known, return UNKNOWN_WEIGHT.
Weight::t_weight Weight::getWeight() const noexcept {
   assert( validate() );

   if( bIsKnown )
      return weight ;
   else
      return UNKNOWN_WEIGHT ;
}


Weight::t_weight Weight::getWeight( const Weight::UnitOfWeight weightUnits ) const noexcept {
   assert( validate() );

   return convertWeight( weight, unitOfWeight, weightUnits );
}


/// If the maximum weight is not known, return UNKNOWN_WEIGHT.
Weight::t_weight Weight::getMaxWeight() const noexcept {
   assert( validate() );

   if( bHasMax )
      return maxWeight ;
   else
      return UNKNOWN_WEIGHT ;
}


Weight::UnitOfWeight Weight::getWeightUnit() const noexcept {
   assert( validate() );

   return unitOfWeight ;
}


void Weight::setWeight( const Weight::t_weight newWeight ) {
   assert( validate() );

   if( !isWeightValid( newWeight ) ) {
      /// @throws out_of_range When the weight is <=0 or > `maxWeight` (if `maxWeight` is set)
      throw out_of_range( "Weight is out of range" ) ;
   }

   weight = newWeight ;
   bIsKnown = true ;
   assert( validate() );
}


void Weight::setWeight( const Weight::t_weight newWeight, const Weight::UnitOfWeight weightUnits ) {
   setWeight( convertWeight( newWeight, weightUnits, unitOfWeight ));
}


void Weight::setMaxWeight( const Weight::t_weight newMaxWeight ) {
   /// The maximum weight should not be set when we start this routine
   assert( !bHasMax );

   if( !isWeightValid( newMaxWeight) ) {
      /// @throws out_of_range When the maximum weight is <= 0
      throw out_of_range( "The maximum weight is out of range" );
   }

   maxWeight = newMaxWeight;
   bHasMax = true ;

   // We can't do this yet as the weight hasn't been set yet
   // assert( bIsKnown == true && weight <= maxWeight );
}


bool Weight::isWeightValid( const Weight::t_weight checkWeight ) const noexcept {
   /// Verify that `checkWeight` > 0
   if( checkWeight <= 0 ) {
      cout << "Weight [" << checkWeight << "] can not be <= 0" << endl ;
      return false;
   }

   /// If `bHasMax`, then `checkWeight` must be <= `maxWeight`
   if( bHasMax ) {
      if( checkWeight > maxWeight ) {
         cout << "Weight [" << checkWeight << "] is > the maximum weight [" << maxWeight << "]" << endl ;
         return false;
      }
   }

   return true;
}


bool Weight::validate() const noexcept {
   if( bHasMax ) {
      if( !isWeightValid(( maxWeight))) {
         cout << "Max weight is <= 0" << endl;
         return false;
      }

      assert( maxWeight > 0 );
   }

   if( bIsKnown ) {
      if( !isWeightValid( weight ) ) {
         return false;
      }

      assert( weight > 0);

      if( bHasMax ) {
         assert( weight <= maxWeight );
      }
   }

   return true;
}


Weight::t_weight Weight::fromKilogramToPound( const Weight::t_weight kilogram ) noexcept {
   return kilogram / KILOS_IN_A_POUND ;
}


Weight::t_weight Weight::fromPoundToKilogram( const Weight::t_weight pound ) noexcept {
   return pound * KILOS_IN_A_POUND ;
}


Weight::t_weight Weight::fromSlugToPound( const Weight::t_weight slug ) noexcept {
   return slug / SLUGS_IN_A_POUND ;
}


Weight::t_weight Weight::fromPoundToSlug( const Weight::t_weight pound ) noexcept {
   return pound * SLUGS_IN_A_POUND ;
}


Weight::t_weight Weight::convertWeight( const Weight::t_weight fromWeight
        ,const UnitOfWeight fromUnit
        ,const UnitOfWeight toUnit ) noexcept {
   Weight::t_weight commonWeight = UNKNOWN_WEIGHT;

   switch( fromUnit ) {
      case POUND: commonWeight = fromWeight ;
         break;
      case KILO: commonWeight = fromKilogramToPound( fromWeight ) ;
         break;
      case SLUG: commonWeight = fromSlugToPound( fromWeight ) ;
         break;
      default: assert( false );  // We should never get here
   }

   // cout << "commonWeight = [" << commonWeight << "] " << POUND_LABEL << endl;

   Weight::t_weight toWeight = UNKNOWN_WEIGHT;

   switch( toUnit ) {
      case POUND: toWeight = commonWeight ;  // No conversion necessary
         break;
      case KILO: toWeight = fromPoundToKilogram( commonWeight );
         break;
      case SLUG: toWeight = fromPoundToSlug( commonWeight );
         break;
      default: assert( false );  // We should never get here
   }

   // cout << fromWeight << " " << fromUnit << " is " << toWeight << " " << toUnit << endl ;

   return toWeight ;
}


/// #### Sample Output
/// @code
/// Weight noWeight;
///     ==============================================
///     Weight  this                0x7ffd00c73360
///     Weight  isKnown             false
///     Weight  weight              0
///     Weight  unitOfWeight        Pound
///     Weight  hasMax              false
///     Weight  maxWeight           0
///
/// Weight myWeight( 3.14, Weight::KILO, 20 );
///     ==============================================
///     Weight  this                0x7ffcc65aeb00
///     Weight  isKnown             true
///     Weight  weight              3.14
///     Weight  unitOfWeight        Kilo
///     Weight  hasMax              true
///     Weight  maxWeight           20
/// @endcode
///
void Weight::dump() const noexcept {
   FORMAT_LINE_FOR_DUMP( "Weight", "this" ) << this << endl ;
   FORMAT_LINE_FOR_DUMP( "Weight", "isKnown" ) << bIsKnown << endl ;
   FORMAT_LINE_FOR_DUMP( "Weight", "weight" ) << weight << endl ;
   FORMAT_LINE_FOR_DUMP( "Weight", "unitOfWeight" ) << unitOfWeight << endl ;
   FORMAT_LINE_FOR_DUMP( "Weight", "hasMax" ) << bHasMax << endl ;
   FORMAT_LINE_FOR_DUMP( "Weight", "maxWeight" ) << maxWeight << endl ;
   // FORMAT_LINE_FOR_DUMP( "Weight", "<<" ) << this << endl ;
}


/// #### Output rules
///
///   - If the weight is unknown, print `Unknown`
///   - If the weight has a maximum weight, print the weight followed by ` out of ` and the maximum weight
///   - Print the unit.  If the last number that's printed is > 1, then make the unit plural by adding an `s`
///
/// #### Sample Output
///
/// Test vectors for Weight << override:
///     | Usage                                   | The Output              |
///     |-----------------------------------------|-------------------------|
///     | `Weight weight`                         | `Unknown`               |
///     | `Weight weight( 0.5 )`                  | `0.5 Pound`             |
///     | `Weight weight( 1 )`                    | `1 Pound`               |
///     | `Weight weight( 1.5 )`                  | `1.5 Pounds`            |
///     | `Weight weight( 1.5, Weight::KILO )`    | `1.5 Kilos`             |
///     | `Weight weight( 0.5, Weight::KILO, 1 )` | `0.5 out of 1 Kilo`     |
///     | `Weight weight( 0.5, Weight::KILO, 2 )` | `0.5 out of 2 Kilos`    |
///     | `Weight weight( Weight::KILO, 1 )`      | `Unknown out of 1 Kilo` |
///
std::ostream& operator<<( std::ostream& lhs_stream, const Weight& rhs_Weight ) {
   stringstream stringBuffer;

   if( !rhs_Weight.isWeightKnown() && !rhs_Weight.hasMaxWeight() ) {
      lhs_stream << "Unknown" ;
      return lhs_stream;
   }
   else if( rhs_Weight.isWeightKnown() ) {
      stringBuffer << rhs_Weight.getWeight();
   } else {
      stringBuffer << "Unknown";
   }

   if( rhs_Weight.hasMaxWeight() ) {
      stringBuffer << " out of " << rhs_Weight.getMaxWeight();
   }

   stringBuffer << " " << rhs_Weight.getWeightUnit() ;

   /// If the numeric weight is 1, use the singular form of the unit.
   /// If the numeric weight is not 1, use the plural form of the unit.
   if(    ( !rhs_Weight.hasMaxWeight() && rhs_Weight.getWeight() > 1 )
          || ( rhs_Weight.hasMaxWeight() && rhs_Weight.getMaxWeight() > 1 ) ) {
      stringBuffer << "s";
   }

   return lhs_stream << stringBuffer.str();
}


std::ostream& operator<<( ostream& lhs_stream, const Weight::UnitOfWeight rhs_UnitOfWeight ) {
   switch( rhs_UnitOfWeight ) {
      case Weight::POUND: return lhs_stream << Weight::POUND_LABEL ;
      case Weight::KILO:  return lhs_stream << Weight::KILO_LABEL ;
      case Weight::SLUG:  return lhs_stream << Weight::SLUG_LABEL ;
      default: throw out_of_range( "The unit can not be converted to a string" );
   }
}


bool Weight::operator==( const Weight& rhs_Weight ) const {
   /// Remember to convert the two weight's units into a common unit!
   /// Treat unknown weights as 0 (so we can sort them without dealing with exceptions)
   Weight::t_weight lhs_weight = (bIsKnown) ? getWeight(Weight::POUND) : 0;
   Weight::t_weight rhs_weight = (rhs_Weight.bIsKnown) ? rhs_Weight.getWeight(Weight::POUND) : 0;

   return lhs_weight == rhs_weight;
}


bool Weight::operator<( const Weight& rhs_Weight ) const {
   /// Remember to convert the two weight's units into a common unit!
   /// Treat unknown weights as 0 (so we can sort them without dealing with exceptions)
   Weight::t_weight lhs_weight = (bIsKnown) ? getWeight(Weight::POUND) : 0;
   Weight::t_weight rhs_weight = (rhs_Weight.bIsKnown) ? rhs_Weight.getWeight(Weight::POUND) : 0;

   return lhs_weight < rhs_weight;
}


/// It's assumed that rhs_addToWeight is in the same units as Weight
Weight& Weight::operator+=( const Weight::t_weight rhs_addToWeight ) {
   if( !bIsKnown ) {
      /// @throws out_of_range When a mathematical operation is attempted when the weight is unknown
      throw out_of_range( "Weight is unknown" ) ;
   }

   setWeight( weight + rhs_addToWeight );

   return *this;
}
