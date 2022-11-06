#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <utility>

using namespace std;

list<string> backwardsSorter(list<string> listString);

int main()
{
    //opening and reading from the file
    //note that the file needs to have an empty line at the end of it for proper reading
    ifstream myfile;
    myfile.open("shopping_list.txt");                                                   //enter file name for the file to be sorted here

    //makes a list that will hold the data to be sorted
    list<string> fileContents = {};
    
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
                cout << "Would you like to sort by through the First method or the Second method?\nRespond '0' for First and '1' for Second\n";
                cin >> userInput;

                //checks userInput for validity. If invalid will throw userInput. O/W will sort based on user choice
                if ((userInput.compare("0") != 0 && userInput.compare("1") != 0)) {
                    throw userInput;
                }
                else {
                    cout << "Response is: " << userInput << endl;
                    hasRun = !hasRun;
                    if ((userInput.compare("0") == 0)) {
                        fileContents.sort();
                    }
                    else {
                        //delete the following line once backwardsSorter works
                        //cout << "sort backwards" << endl;
                        backwardsSorter(fileContents);
                    }
                    /*
                    //print contents of the array
                    for (string str : fileContents) {
                        cout << str << '\n';
                    }
                    */
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

list<string> backwardsSorter(list<string> listString) {
    //i for index and a list that will be sorted
    int i = 0;
    list<pair <string, int>> toSort;

    //this grabs all info and puts into a list of pairs
    for (string str : listString) {
        list<string> last;
        istringstream iss(str);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(last));
        if (!(last.empty())) {
            pair<string, int> toSortPair(last.back(), i);
            toSort.push_back(toSortPair);
        }
        i++;
    }

    //sort the list by the strings
    toSort.sort();

    //now we will match the index within the pairs to their respective strings to return



    /*
    //print list
    for (pair<string, int> toSortPair : toSort) {
        cout << toSortPair.first << " " << toSortPair.second;
    }
    */



    return listString;
}