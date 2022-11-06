#include <iostream>
#include <fstream> //iftream
#include <sstream> //istream and istringstream
#include <algorithm> //sort and copy
#include <string>
#include <vector>
#include <tuple>

using namespace std;

vector<string> backwardsSorter(vector<string> vectorString);

int main()
{
    //opening and reading from the file
    //note that the file needs to have an empty line at the end of it for proper reading
    ifstream myfile;
    myfile.open("sample_file.txt");

    //makes a list that will hold the data to be sorted
    vector<string> fileContents;
    
    //if file is open does operation O/W prints msg to user
    if (myfile.is_open()) {

        //grab the contents of the file and insert them into the list. then close the file
        string myline;
        while (myfile) {
            getline(myfile, myline);
            fileContents.push_back(myline);
        }
        myfile.close();

        //now gives the option to the user on whether they would prefer to be sorting by the first character of each line
        //or by the first character of the LAST word separated by spaces in each line
        //repeat this process until either option is chosen
        string userInput;
        bool hasRun = false;

        do {
            try {
                cout << "Would you like to sort by First Word or the Last Word?\nRespond '0' for First and '1' for Second\n";
                cin >> userInput;

                //checks userInput for validity. If invalid will throw userInput. O/W will sort based on user choice
                if ((userInput.compare("0") != 0 && userInput.compare("1") != 0)) {
                    throw userInput;
                }
                else {
                    cout << "Response is: " << userInput << endl << endl;
                    hasRun = !hasRun;

                    if ((userInput.compare("0") == 0)) {
                        sort(fileContents.begin(), fileContents.end());

                        cout << "Sorted by First word" << endl << endl;
                    }
                    else {
                        fileContents = backwardsSorter(fileContents);

                        cout << "Sorted by Last word" << endl << endl;
                    }
                    
                    //print contents of the array
                    for (string str : fileContents) {
                        cout << str << '\n';
                    }

                    //now want to output fileContents into the file that was read



                }
            }
            catch (...) {
                cout << "Incorrect Input. Valid inputs are: '0' and '1'";
            }
        } while (!hasRun);
    }
    else {
        cout << "ERROR READING FILE";
    }
}

//will sort based on the last "word" of the line in vectorString
vector<string> backwardsSorter(vector<string> vectorString) {
    //i for iterating
    //vector will hold a list of tuples that
    //contain: the last "word", index number, and size of "line"
    int i = 0;
    vector<tuple <string, int, int>> lastWords;

    //this grabs all info and puts into a vector of tuples
    for (string str : vectorString) {
        vector<string> last;
        istringstream iss(str);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(last));
        if (!(last.empty())) {
            lastWords.push_back(make_tuple(last.back(), i, str.size()));
            //last.size() gives # words in string
            //last[#].size() gives length of last word
        }
        i++;
    }
    
    sort(lastWords.begin(), lastWords.end());
    //now the words are in alphabetical order
    //however there may be lines that are longer than others that are out of desired order
    
    //notice that i now holds the length of lastWords
    //We will now use j as our iterator
    int j = 0;
    
    //will sort by length of string ( get<2>lastWords[INDEX] ) for each character 
    while (j != i - 2) {
        if ((get<0>(lastWords[j]).front() == get<0>(lastWords[j + 1]).front()) && (get<2>(lastWords[j]) > get<2>(lastWords[j + 1]))) {
            //may want to add additional conditions based on other
            //words coming before the final one
            tuple <string, int, int> temp = lastWords[j];
            lastWords[j] = lastWords[j + 1];
            lastWords[j + 1] = temp;
            j = -1;
        }
        j++;
    }

    //now want to insert the now sorted array from lastWords into a sortedVector
    vector<string> sortedVector;

    for (j = 0; j < i - 1; j++) {
        sortedVector.push_back(vectorString[get<1>(lastWords[j])]);
    }

    return sortedVector;
}
