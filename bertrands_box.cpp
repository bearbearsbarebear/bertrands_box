#include <iostream>

using namespace std;

/*
// There are three boxes, one with two gold coins, one with one gold and 
// one silver, one with two silver. A coin drawn at random is gold. What 
// is the probability that the other coin in the same box is gold? The 
// coin came either from the first box, or the second; there is no reason 
// for preferring either, so the chance should be a half. But the coin 
// picked was either the first in the first box, or the second in the first 
// box, or the one gold coin in the second box. Two of these three possibilities 
// give it that the other coin in the same box is gold, so the probability is 2/3.
*/

int main(int argc, char* argv[])
{
    char _boxes[3][2] = {{'y', 'y'}, {'y', 'w'}, {'w', 'w'}};

    char selected_box[2];
    int32_t random, other_index;
    float yy = 0, yw = 0;

    // Initializing random seed
    srand(time(NULL));

    for (int32_t i = 0; i < 100000; ++i) {
        // Chooses a box at random
        random = rand() % 3;

        copy(begin(_boxes[random]), end(_boxes[random]), begin(selected_box));

        // Selects a ball at random
        random = rand() % 2;

        // If the selected ball is yellow then proceed
        if (selected_box[random] == 'y') {
            other_index = (random == 0) ? 1 : 0;

            // Checks if the 2nd ball (at other_index) is yellow or not
            if (selected_box[other_index] == 'y') {
                ++yy;
            } else {
                ++yw;
            }
        }
    }

    printf("%f", yy / (yy + yw));

    return 0;
}
