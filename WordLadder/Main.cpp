#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cout << "Not enough arguments provided. Example usage:\n";
        cout << "WordLadder dictionary_file_path first_word last_word\n";

        return 0;
    }

    cout << "Hello World!\n";

    cout << "Argument 0: " << argv[0] << "\n";

    cout << "Argument 1 (name of dict file): " << argv[1] << "\n";

    cout << "Argument 2 (first word in the ladder): " << argv[2] << "\n";

    cout << "Argument 3 (last word in the ladder): " << argv[3] << "\n";

    return 0;
}