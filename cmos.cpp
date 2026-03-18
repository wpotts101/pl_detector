#include <string>
#include <vector>
#include <cctype>

using namespace std;

string removeWhitespace(const string& input)
{
    string result;
    for(char ch : input)
    {
        if(!isspace(static_cast<unsigned char>(ch)))
        {
            result += ch;
        }
    }
    return result;
}

vector<string> generateKMers(const string& digits, int k)
{
    vector<string> kmers;
    for(int i = 0; i <= static_cast<int>(digits.length()) - k; i++)
    {
        kmers.push_back(digits.substr(i, k));
    }
    return kmers;
}