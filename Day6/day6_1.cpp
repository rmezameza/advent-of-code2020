#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>


int main(){

    std::ifstream input_file{ "input_answers.txt" };
    std::vector< std::string > input_vec;
    std::string line;

    if( input_file.is_open() ){
        while( std::getline( input_file, line) ){
           input_vec.push_back( line );
        }

        input_file.close();
    }
    else
        std::cout << "Unable to open the file!";



    std::vector< int > answers_all_groups;
    std::string found_chars_one_group;

    // If the char is not in that string found_chars_one_group, than add,
    // else ignore the char. When newspace comes, check the length and add it
    // to the vector. Finally sum all the values (groups -> yes'es) in the vector

    std::for_each( input_vec.begin(), input_vec.end(),
        [ & ]( const std::string& str_line )
        {
            if( str_line != "" )
            {
                std::for_each( str_line.begin(), str_line.end(),
                    [ & ]( const char& c )
                    {
                        size_t found_char{ found_chars_one_group.find( c ) };

                        if( found_char == std::string::npos )
                        {
                            found_chars_one_group.push_back( c );
                        }
                    } );

                    
            }
            else
            {
                answers_all_groups.push_back( found_chars_one_group.length() );
                found_chars_one_group.clear();
            }
        } );



    int sum_all_groups{ std::accumulate( answers_all_groups.begin(), answers_all_groups.end(), 0 ) };

    std::cout << "The sum of all counts of yes by all groups is: " << sum_all_groups << "\n";

    return 0;
}