#include "../rsb.hpp"

void print_eval_set_result(const std::string& formula, const std::vector<std::vector<int>> sets) {
    std::vector<int> result = rsb::eval_set(formula, sets);
    std::cout << "Formula: " << formula << " \t Result: ";
    rsb::print_set(result);
    std::cout << std::endl;
}

int main() {
    // Test cases for eval_set
    std::vector<std::vector<int>> sets = {
        {1, 2, 3},
        {2, 3, 4},
        {1, 4}
    };

    //print sets:
    for (size_t i = 0; i < sets.size(); ++i) {
        std::cout << "Set " << char('A' + i) << ": ";
        rsb::print_set(sets[i]);
        std::cout << std::endl;
    }

    print_eval_set_result("A", sets); 
    print_eval_set_result("AB|", sets);
    print_eval_set_result("AC&", sets);
    print_eval_set_result("A!", sets);
    print_eval_set_result("ABC&&", sets);
    print_eval_set_result("AB>", sets);
    print_eval_set_result("AC^", sets);
    
    return 0;
}