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

    // like part 1, but adding few more steps:
    // sorting the vector and find the missing id's
    // the result is a vector with the missing front and back seats
    // and the missing seat id which is mine.
    
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

    std::sort( boarding_ids.begin(), boarding_ids.end() );

    std::vector< int > missing_ids;
    int next = 0;

    for( size_t idx{ 0 }; idx < boarding_ids.size(); ++idx )
    {
        while( next != boarding_ids.at( idx ) )
        {
            missing_ids.push_back( next );
            ++next;
        }

        ++next;
    }
    
    for( const auto& i : missing_ids )
        std::cout << i << "\n";

    return 0;
}