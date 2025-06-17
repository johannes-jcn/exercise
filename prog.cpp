#include <iostream>
#include <string>

using namespace std; 


bool validadeEAN(string ean) {
    if(ean[0] == '\"' ) {
        ean = ean.substr(1, ean.size() - 2);
    }
    while(ean[0] == '0') {
        ean = ean.substr(1, ean.size() - 1);
    }
    
    if(ean.size() != 13) return false;

    int checksumDigit = ean[ean.size() - 1] - '0';
    int checksum = 0;

    for (int i = ean.size() - 2 ; i >= 0; i = i - 2 ) {
        if(ean[i] - '0' > 9 ) return false;
        checksum += (ean[i] - '0') * 3;
    }
    
    for (int i = ean.size() - 3 ; i >= 0; i = i - 2 ) {
        if(ean[i] - '0' > 9 ) return false;
        checksum += (ean[i] - '0');
    }

    int multipleOfTen = 10 * ((checksum / 10) + 1);

    if(multipleOfTen - checksum == checksumDigit) return true;

    cout << ean << endl;
    return false;
}

void parseHeader() {

    string input;
    cin >> input;

    string aux;

    std::string::size_type delim;
    delim = input.find(",");
    int eanPos = -1;
    int currPos = 0;
    

    while(delim != input.npos) {
        aux = input.substr(0, delim);
        input = input.substr(delim + 1, input.size());
        if(aux == "ean" || aux == "\"ean\"") {
            eanPos = currPos;
            break;
        }
        delim = input.find(",");
    }
    cout << eanPos; 
    
}

int main(void) {

    //parseHeader();
    if(validadeEAN(string("\"4065418448246\""))) cout << '1';
    else cout << '0';

    return 0;    
}