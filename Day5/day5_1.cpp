#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


int main(){

    std::ifstream input_boarding_file{ "input_boarding.txt" };
    std::vector< std::string > input_board_vec;
    std::string line;

    if( input_boarding_file.is_open() ){
        while( std::getline( input_boarding_file, line) ){
            input_board_vec.push_back( line );
        }

        input_boarding_file.close();
    }
    else
        std::cout << "Unable to open the file!";

    
    std::vector< std::vector< int > > input_board_binary_vec;

    // convert the char to 1 (B,R) and 0 (F,L), result is a binary number
    // reverse the number (because of push_back) and convert the
    // binary to an integer by 2 to the power of idx.
    // finally find the max seat id.

    std::for_each( input_board_vec.begin(), input_board_vec.end(),
        [ & ]( std::string str_line )
        {
            std::vector< int > binary_vec;

            for( size_t idx{ 0 }; idx < str_line.size(); ++idx )
            {
                if( str_line.at( idx ) == 'B' || str_line.at( idx ) == 'R' )
                    binary_vec.push_back( 1 );
                else
                    binary_vec.push_back( 0 );
            }
            
            input_board_binary_vec.push_back( binary_vec );
        } );

    std::vector< int > boarding_ids;

    std::for_each( input_board_binary_vec.begin(), input_board_binary_vec.end(),
        [ & ]( std::vector< int > vec )
        {
            int board_id{ 0 };
            std::reverse( std::begin( vec ), std::end( vec ) );

            for( size_t idx{ 0 }; idx < vec.size(); ++idx )
            {
                if( vec.at( idx ) )
                    board_id += pow( 2, idx );
            }

            boarding_ids.push_back( board_id );
        } );

    auto heighest_id{ std::max_element( boarding_ids.begin(), boarding_ids.end() ) };

    std::cout << "The highest seat ID on a boarding pass is: " << *heighest_id << "\n";

    return 0;
}