#include <iostream>
#include <vector>
#include <random>

/*
* In this problem, 100 numbered prisoners must find their own 
* numbers in one of 100 drawers in order to survive. The rules 
* state that each prisoner may open only 50 drawers and cannot 
* communicate with other prisoners. At first glance, the situation 
* appears hopeless, but a clever strategy offers the prisoners a 
* realistic chance of survival. 
* https://en.wikipedia.org/wiki/100_prisoners_problem
*/

int main(int argc, char* argv[]) 
{
    int success = 0;
    for (int tries = 0; tries < 10000; ++tries) {
        std::vector<int> boxes(100);
        int prisoners = 100;
        int next_box, found;

        // Generating a vector enumerated from 1 to 100
        int n = 0;
        std::generate(boxes.begin(), boxes.end(), [&] { return ++n; });

        // Shuffling the generated vector seemingly randomly
        std::shuffle(std::begin(boxes), std::end(boxes), std::default_random_engine{ std::random_device { }() });

        while (prisoners > 0) {
            // The strategy starts at the current prisoner's number
            next_box = prisoners;

            found = 0;
            std::cout << "Prisoner number " << prisoners;
            for (int i = 0; i < 50; ++i) {
                if (boxes[next_box] == prisoners) {
                    std::cout << " found his box. (boxes[" << next_box << "]->" << boxes[next_box] << ")" << std::endl;
                    found = 1;
                    break;
                }
                //std::cout << " boxes[" << next_box << "]->" << boxes[next_box] << "";
                next_box = boxes[next_box];
            }

            std::cout << std::endl;

            // Failed attempt
            if (found == 0) {
                std::cout << " couldn't find his box." << std::endl;
                break;
            }

            --prisoners;
        }

        if (prisoners == 0) { ++success; }
    }

    std::cout << "Successes: " << success << std::endl;

    return 0;
}
