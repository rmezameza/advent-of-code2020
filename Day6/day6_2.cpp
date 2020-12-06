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

    
    std::vector< int> yes_all_groups;
    std::string group;

    size_t count_group{ 0 };


    std::for_each( input_vec.begin(), input_vec.end(),
        [ & ]( const std::string& str_line )
        {
            // Add one group to one string and count how many groups (lines)
            if( str_line != "" )
            {
                 group += str_line;
                ++count_group;
            }
            else
            {
                if( count_group == 1 )
                {
                    yes_all_groups.push_back( group.length() );
                }
                else
                {
                    int group_yes_sum{ 0 };

                    for( size_t idx_first{ 0 }; idx_first < ( group.length() - 1 ) ; ++idx_first )
                    {
                        size_t count_char{ 1 };

                        // Count the actual char in the string
                        for( size_t idx_second{ idx_first + 1 }; idx_second < group.length(); ++idx_second )
                        {
                            if( group.at( idx_first ) == group.at( idx_second ) )
                                ++count_char;
                        }

                        // If the char counter is equal to the group counter, increment the total yes sum for the group
                        if( count_char == count_group )
                            ++group_yes_sum;
                    }
                    
                    yes_all_groups.push_back( group_yes_sum );
                }
                

                // Reset string and counter
                group.clear();
                count_group = 0;
            }
        } );


    
    int sum_all_groups{ std::accumulate( yes_all_groups.begin(), yes_all_groups.end(), 0 ) };

    std::cout << "The sum of all counts of the same yes checkboxes by all groups is: " << sum_all_groups << "\n";
    
    return 0;
}