#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

int main(){

    std::ifstream input_data_file{ "input_passwords.txt" };
    std::vector< std::string > input_data_vec;
    std::string line;

    if( input_data_file.is_open() ){
        while( std::getline( input_data_file, line) ){
            input_data_vec.push_back( line );
        }

        input_data_file.close();
    }
    else
        std::cout << "Unable to open the file!";


    size_t count_valid_lines{ 0 };
    
    std::for_each( input_data_vec.begin(), input_data_vec.end(),
        [ &count_valid_lines ]( const std::string& str_line )
        {
            int min_num{ 0 }, max_num{ 0 }, count_char{ 0 };
            char wanted_char{ ' ' };
            
            std::string temp;

            // Find dash for first number
            auto dash{ std::find( str_line.begin(), str_line.end(), '-' ) };            
            std::copy( str_line.begin(), dash, std::inserter( temp, temp.begin() ) );
            min_num = std::stoi( temp ) - 1;
            temp.clear();

            // Find first space for second number.
            auto space_one{ std::find_if( ++dash, str_line.end(),
                []( const char& c )
                {
                    return std::isspace( c );
                } ) };
            std::copy( dash, space_one, std::inserter( temp, temp.begin() ) );
            max_num = std::stoi( temp ) - 1;
            temp.clear();

            wanted_char = *( ++space_one );

            // space_one iterator goes to position with first char from password
            space_one += 3;
            std::copy( space_one, str_line.end(), std::inserter( temp, temp.begin() ) );

            // Initialize variables for better readability
            char first_char{ *( temp.begin() + min_num ) }, second_char{ *( temp.begin() + max_num ) }; 
            bool min{ first_char == wanted_char }, max{ second_char == wanted_char };

            // XOR
            if( ( min && !max ) || ( !min && max ) ){
                ++count_valid_lines;
            }
        } );
        
        std::cout << count_valid_lines << " passwords are valid!\n";

    
    return 0;   
}