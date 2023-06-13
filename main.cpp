#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>

bool compareByPages(const std::pair<std::string, std::set<int>>& pair1, const std::pair<std::string, std::set<int>>& pair2)
{
    return (pair1.second).size() > (pair2.second).size();
}

void display_words(const std::vector<std::pair<std::string, std::set<int>>>& words)
{
    std::cout << std::setw(12) << std::left << "\nWord"
        << "Occurrences" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    for (auto pair: words) {
        std::cout << std::setw(12) << std::left << pair.first
                       << std::left << "[ ";
        for (auto i: pair.second)
            std::cout << i << " ";
        std::cout << "]" << std::endl;
    }
}

std::map<std::string, std::set<int>> countWords(std::map<std::string, std::set<int>>& wordCounts, const std::string& text, int lineNumber)
{
    std::stringstream iss(text);
    std::string word;
    
    while(iss >> word)
    {
        wordCounts[word].insert(lineNumber);
    }
    return wordCounts;
}

std::string clean_string(const std::string& s) {
    std::string result;
    for (char c: s) {
        if (c == '.' || c == ',' || c == ';' || c == ':')
            continue;
        else
            result += c;
    }
    return result;
}

void part2() {
    std::map<std::string, std::set<int>> words;
    std::string line;
    std::string word;
    std::ifstream in_file {"/Users/brunobrett/Desktop/XCODE PROJECTS/WORD_FINDER/WORD_FINDER//words.txt"};
    int line_num = 0;
    if (in_file) {
        while(std::getline(in_file, line))
        {
            ++line_num;
            line = clean_string(line);
            words = countWords(words, line, line_num);
        }
        
        std::vector<std::pair<std::string, std::set<int>>> vectorPairs(words.begin(), words.end());
        std::sort(vectorPairs.begin(), vectorPairs.end(), compareByPages);
        display_words(vectorPairs);
        
        
        in_file.close();

    } else {
        std::cerr << "Error opening input file" << std::endl;
    }
}

int main() {
    part2();
    return 0;
}


