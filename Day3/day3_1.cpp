#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

int main(){

    std::ifstream input_map_file{ "input_map.txt" };
    std::vector< std::string > input_map_vec;
    std::string line;

    if( input_map_file.is_open() ){
        while( std::getline( input_map_file, line) ){
            input_map_vec.push_back( line );
        }

        input_map_file.close();
    }
    else
        std::cout << "Unable to open the file!";

  

    
    size_t idx_counter{ 3 }, tree_counter{ 0 };
    size_t line_length{ input_map_vec.at( 0 ).length() };
    const char TREE{ '#' };

    // There is no count in the first line.
    auto ignore_first_line{ input_map_vec.begin() + 1  };

    std::for_each( ignore_first_line, input_map_vec.end(), 
        [ & ]( const std::string& str_line )
        {
            if( str_line.at( idx_counter ) == TREE )
                ++tree_counter;
            
            // Check if index will be out of bound, if that is the case, 3 minus the difference
            // of line_length - idx_counter. Or else increment idx_counter by three.
            if( ( idx_counter + 3 ) >= line_length)
                idx_counter = 3 - ( line_length - idx_counter );
            else
                idx_counter += 3;   
        } );

    
    std::cout << "I encountered >> " << tree_counter << " << trees!\n";


    return 0;
}