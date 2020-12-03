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

  
    std::vector< size_t > all_tree_counters;
    size_t line_length{ input_map_vec.at( 0 ).length() };
    // There is no count in the first line.
    auto ignore_first_line{ input_map_vec.begin() + 1  };
    const char TREE{ '#' };


    
    
    for( size_t i{ 1 }; i < 10; i += 2 ){
        
        size_t tree_counter{ 0 };

        // If i is 9 -> then use the slope with jumping two rows and one right
        if( i == 9 ){
            size_t idx_counter{ 1 }, row_counter{ 2 };

            std::for_each( input_map_vec.begin() + 2, input_map_vec.end(), 
                [ & ]( const std::string& str_line )
                {
                    if( ( row_counter % 2 ) == 0 ){
                        if( str_line.at( idx_counter ) == TREE )
                            ++tree_counter;

                         if( ( idx_counter + 1 ) >= line_length)
                            idx_counter = 1 - ( line_length - idx_counter );
                        else
                            idx_counter += 1;
                    }

                    ++row_counter;
                } );
        }
        // Or else jump idx_counter to the right (cyclic) and one row down.
        else{
            size_t idx_counter{ i };
            
            std::for_each( ignore_first_line, input_map_vec.end(), 
                [ & ]( const std::string& str_line )
                {
                    if( str_line.at( idx_counter ) == TREE )
                        ++tree_counter;

                    // Check if index will be out of bound, if that is the case, 3 minus the difference
                    // of line_length - idx_counter. Or else increment idx_counter by three.
                    if( ( idx_counter + i ) >= line_length)
                        idx_counter = i - ( line_length - idx_counter );
                    else
                        idx_counter += i;   
                } );
        }
        
        all_tree_counters.push_back( tree_counter );
    }


    size_t product_of_all_trees{ 1 };

    for( const size_t& t : all_tree_counters )
        product_of_all_trees *= t;

    std::cout << "The product of all encountered trees is: >> " << product_of_all_trees << "\n";
     
    return 0;
}