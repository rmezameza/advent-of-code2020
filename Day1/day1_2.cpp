#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

int main(){

    std::ifstream input_numbers_file{ "input_numbers.txt" };
    std::vector<int> input_numbers_vec;
    std::string line;

    if( input_numbers_file.is_open() ){
        while( std::getline( input_numbers_file, line) ){
            input_numbers_vec.push_back( std::stoi( line ) );
        }

        input_numbers_file.close();
    }
    else
        std::cout << "Unable to open the file!";
    
    int factor_one{ 0 }, factor_two{ 0 }, factor_three{ 0 };
    bool stop{ false };

    std::for_each( input_numbers_vec.begin(), input_numbers_vec.end(),
        [ & ]( const int& first_num )
        {
            std::for_each( input_numbers_vec.begin(), input_numbers_vec.end(),
                [ & ]( const int& second_num )
                {
                    std::for_each( input_numbers_vec.begin(), input_numbers_vec.end(),
                    [ & ]( const int& third_num ){
                        if( ( first_num + second_num + third_num ) == 2020 ){
                            factor_one = first_num;
                            factor_two = second_num;
                            factor_three = third_num;
                        }
                    } );
                } );
        });

    /*
    for( size_t i{ 0 }; i < ( input_numbers_vec.size() - 2 ); ++i ){
        for( size_t j{ i + 1 }; j < ( input_numbers_vec.size() - 1 ); ++j ){
            for( size_t k{ j + 1}; k < input_numbers_vec; ++k ){
                if( ( input_numbers_vec.at( i ) + input_numbers_vec.at( j ) ) == 2020 ){
                    factor_one = input_numbers_vec.at( i );
                    factor_two = input_numbers_vec.at( j );
                    factor_three = input_numbers_vec.at( k );
                    stop = true;
                    break;
            }
            if( stop )
                break;
        }

        if( stop )
            break;
    }*/


    std::cout << "The three factors that sum 2020 are: " << factor_one << ", " << factor_two << " and " << factor_three << "\n";
    std::cout << "The product of these two factors is: " << factor_one * factor_two *factor_three << "\n";


    return 0;
}