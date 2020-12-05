#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>


int main(){

    std::ifstream input_passport_file{ "input_passport.txt" };
    std::vector< std::string > input_pass_vec;
    std::string line;

    if( input_passport_file.is_open() ){
        while( std::getline( input_passport_file, line) ){
            if( line == "" )
                input_pass_vec.push_back( "-" );                // replace empty line with "-" for separating passports.
            else
                input_pass_vec.push_back( line );
        }

        input_passport_file.close();
    }
    else
        std::cout << "Unable to open the file!";

    size_t required_field_counter{ 0 };
    size_t valid_passports{ 0 };

    std::vector< std::string > required_fields{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

    std::for_each( input_pass_vec.begin(), input_pass_vec.end(),
        [ & ]( const std::string& str_line )
        {
            if( str_line != "-" ){
                // search every entry in vector (str_line) for required fields, if line is not "-"
                for( size_t idx{ 0 }; idx < required_fields.size(); ++idx ){
                    if( static_cast< size_t >( str_line.find( required_fields.at( idx ) ) != std::string::npos ) )
                        ++required_field_counter;
                }
            }
            else{
                if( required_field_counter >= 7 )
                    ++valid_passports;

                required_field_counter = 0;
            }
        } );


    std::cout << "The total amount of valid passports are: " << valid_passports << "\n";


    return 0;
}