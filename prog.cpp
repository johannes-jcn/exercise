#include <iostream>
#include <string>

using namespace std; 

enum rowReturn {
    INVALID = 0,
    VALID,
    EMPTY
};

bool validadeEAN(string ean) {

    if(ean.empty()) return false;

    if(ean[0] == '\"' ) {
        ean = ean.substr(1, ean.size() - 2);
    }
    while(ean[0] == '0') {
        ean = ean.substr(1, ean.size() - 1);
    }

    int size = ean.size();
    
    if(size > 13) return false;
    if(size < 13) {
        string pad = string(13 - size, '0');
        ean = pad + ean;
    }
    cout << ean << endl;

    int checksumDigit = ean[ean.size() - 1] - '0';
    int checksum = 0;

    for (int i = size - 2 ; i >= 0; i = i - 2 ) {
        if(ean[i] - '0' > 9 ) return false;
        checksum += (ean[i] - '0') * 3;
    }
    
    for (int i = size - 3 ; i >= 0; i = i - 2 ) {
        if(ean[i] - '0' > 9 ) return false;
        checksum += (ean[i] - '0');
    }

    int multipleOfTen = 10 * ((checksum / 10) + 1);
    cout << "multipleOfTen: " << multipleOfTen << endl;
    cout << "checksum: " << checksum<< endl;
    cout << "checksumDigit: " << checksumDigit<< endl;
    cout << (((multipleOfTen - checksum) % 10) == checksumDigit) << endl << endl ;

    if((multipleOfTen - checksum) % 10 == checksumDigit) return true;

    //cout << ean << endl;
    return false;
}

int parseHeader(int* valid) {

    string input;
    cin >> input;

    std::string::size_type delim;

    delim = input.find(",");
    //cout << input.substr(0, delim) << endl;
    bool validEAN = validadeEAN(input.substr(0, delim));
    if(validEAN == true){
        *valid = *valid + 1;
        return 0;
    }

    string aux;

    delim = input.find(",");
    int eanPos = -1;
    int currPos = 0;

    while(delim != input.npos) {
        aux = input.substr(0, delim);
        input = input.substr(delim + 1, input.size());
        if(aux == "ean" || aux == "\"ean\"") {
            eanPos = currPos;
        }
        delim = input.find(",");
    } 
    //cout << eanPos << endl; 
    return eanPos;
}

rowReturn parseRow(int column) {
    string input;
    cin >> input;
    if(input.empty()) return rowReturn::EMPTY;
    std::string::size_type delim;
    for(int i = 0; i < column; i++) {
        delim = input.find(",");
        input = input.substr(delim + 1, input.size());
    }
    delim = input.find(",");
    //cout << input.substr(0, delim) << endl;
    bool validEAN = validadeEAN(input.substr(0, delim));
    cout << validEAN << endl;
    if(validEAN == true) return rowReturn::VALID;
    else return rowReturn::INVALID;

}

int main(void) {
    
    int valid = 0;
    int invalid = 0;

    int col = parseHeader(&valid);

    if(col == -1){
        cout << "0 0\n";
        return 0;
    }
    rowReturn ret;
    while(cin.eof() == false){
        ret = parseRow(col);
        if(ret == rowReturn::VALID) {
            valid++;
        } else if(ret == rowReturn::INVALID) invalid++;
    }
    
    cout << valid << " " << invalid << endl; 

    return 0;    
}