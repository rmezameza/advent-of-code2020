#include <iostream>
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
    
    int factor_one{ 0 }, factor_two{ 0 };
    bool stop{ false };

    for( size_t i{ 0 }; i < ( input_numbers_vec.size() - 1 ); ++i ){
        for( size_t j{ i + 1 }; j < input_numbers_vec.size(); ++j ){
            if( ( input_numbers_vec.at( i ) + input_numbers_vec.at( j ) ) == 2020 ){
                factor_one = input_numbers_vec.at( i );
                factor_two = input_numbers_vec.at( j );
                stop = true;
                break;
            }
        }

        if( stop )
            break;
    }


    std::cout << "The two factors that sum 2020 are: " << factor_one << " and " << factor_two << "\n";
    std::cout << "The product of these two factors is: " << factor_one * factor_two << "\n";


    return 0;
}