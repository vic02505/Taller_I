#include "wordscounter.h"
#include <string>
#include <string.h>
#include <fstream>

#define DELIM_WORDS " ,.;:\n"


Wordscounter::Wordscounter() {
    this->words = 0;
}

size_t Wordscounter::get_words() {
    return this->words;
}

void Wordscounter::process(std::istream& text_file) {
    int state = 0;
    do {
        char c = text_file.get();
        state = next_state(state, c);
    } while (state != 2);
}

int Wordscounter::next_state(int state, char c) {

    int next_state = state;

    if (state == 0) {
        if (c == EOF){ 
            next_state = 2;
        } else if (strchr(DELIM_WORDS, c) == NULL) {
            next_state = 1;
        }
    } else if (state == 1) {
        if ( c == EOF ) { 
            next_state = 2;
            words++;
        } else if (strchr(DELIM_WORDS, c) != NULL) {
            words++;
            next_state = 0;
        }
    }

    return next_state;

}
