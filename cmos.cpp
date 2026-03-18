#include <string>
#include <vector>
#include <cctype>
#include <functional>   //for hashing
#include <fstream>     //file reading
#include <iostream>
#include <algorithm>

using namespace std;

//this will be used to keep all of the c programs
struct c_file_data {
    string file_name;
    string token_string;
    vector<size_t> fingerprints;
};


//takes the string of tokens and deletes spaces
string RMspace(const string& s){
    string cleaned = "";
    for (int i = 0; i < s.length(); i++){
        if (!isspace(s[i])){
             cleaned+=s[i];
        }
    }
    return cleaned;
}

//the intructions used 4, so we'll use 4
vector<size_t> gen_Kmers(const string& s){
    if (s.length() < 4){
        return {};
    }
    vector<string> Kmers;
    vector<size_t> hashed_Kmers;
    string tmp = "";
    for (int i = 0; i <= s.length()-4; i++){
        for (int j = i; j < i+4; j++){
            tmp += s[j];
        }
        Kmers.push_back(tmp);
        tmp = "";
    }
    hash<string> h;
    for (int i = 0; i < Kmers.size(); i++){
        hashed_Kmers.push_back(h(Kmers[i]));
    }
    return hashed_Kmers;
}

//we'll use w = 5, tweaking later if needed
vector<size_t> gen_fingerprints(const vector<size_t>& hashed_Kmers){
    if (hashed_Kmers.size() < 5){
        return {}; 
    }
    vector<size_t> fingerprints;
    size_t smallest;
    for (int i = 0; i <= hashed_Kmers.size()-5; i++){
        smallest = hashed_Kmers[i];
        for (int j = i+1; j < i+5; j++){
            if (hashed_Kmers[j] < smallest){
                smallest = hashed_Kmers[j];
            }
        }
        fingerprints.push_back(smallest);
    }
    return fingerprints;
}

float fingerprintComparison(const vector<size_t>& f1, const vector<size_t>& f2){
    if (f1.empty() || f2.empty()){
        return 0.0f;
    }

    int matches = 0;
    vector<bool> used(f2.size(), false);

    for (int i = 0; i < f1.size(); i++){
        for (int j = 0; j < f2.size(); j++){
            if (!used[j] && f1[i] == f2[j]){
                matches++;
                used[j] = true;
                break;
            }
        }
    }

    int total = min(f1.size(), f2.size());
    return (float)matches / total;
}


int main(){

    //opening files and getting all fingerprints
    ifstream in("tokens.txt");
    if (!in) {
        cerr << "failed to open tokens.txt\n";
        return 1;
    }

    vector<c_file_data> c_programs;
    string line;

    while (getline(in, line)){
        if (line.empty()) continue;

        size_t space = line.find(' ');
        if (space == string::npos) continue;

        string file_name = line.substr(0, space);
        string rest = line.substr(space + 1);

        string cleaned = RMspace(rest);
        vector<size_t> Kmers = gen_Kmers(cleaned);
        vector<size_t> fingerprints = gen_fingerprints(Kmers);

        c_file_data c;
        c.file_name = file_name;
        c.token_string = cleaned;
        c.fingerprints = fingerprints;

        c_programs.push_back(c);
    }


    //comparing the data:
    for (int i = 0; i < c_programs.size(); i++){
        for (int j = i + 1; j < c_programs.size(); j++){
            cout << "comparing programs " << i+1 << " and " << j+1 << "\n";
            cout << "ratio: " << fingerprintComparison(c_programs[i].fingerprints, c_programs[j].fingerprints) << "\n";
        }
    }

    return 0;

}

