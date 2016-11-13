// Example program
#include <iostream>
#include <string>

#include <iostream>

#include <set>

void return_set(std::set<long>* LCS_positions_set){
    LCS_positions_set->insert(1);
    LCS_positions_set->insert(6);
    LCS_positions_set->insert(6);
    LCS_positions_set->insert(5);
    LCS_positions_set->insert(8998);
    std::cout<<"Inside Set Size = "<<LCS_positions_set->size()<<std::endl;

    return;
}

int main ()
{
     std::set<long>* LCS_positions_set = new std::set<long>();
     return_set(LCS_positions_set);
     for (std::set<long>::iterator it=LCS_positions_set->begin(); it!=LCS_positions_set->end(); ++it)
        std::cout << ' ' << *it;
    std::cout<<"\n";

  // Iterate through all the elements in a set and display the value.
  //for (std::set<long>::iterator it=L.begin(); it!=L.end(); ++it)
//	std::cout << ' ' << *it;
//  std::cout<<"\n";

  delete LCS_positions_set;
  return 0;
}
