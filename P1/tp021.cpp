#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int linhas, colunas;

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

unordered_map<vector<int>, long long, VectorHasher> umap;


long long computeConfigurations(vector<int> v, int currentLine){

    long long num = 0;

    vector<int> v2;
    vector<int> v3;

    while((v)[0] == 0 && (int)(v).size() > 1){
        (v).erase((v).begin());
        if(currentLine > 0){
            currentLine -= 1;
        }
    }

    auto it = umap.find(v);
    if(it != umap.end()){
        return it->second+1;
    }

    if(*max_element((v).begin(), (v).end()) == 0){
        umap.insert({v, num});
        return num + 1;
    }

    int _maxSquare = min((v)[currentLine], (int)distance((v).begin() + currentLine, (v).end()));

    while(_maxSquare > (int)distance((v).begin() + currentLine, (v).end()) || _maxSquare > (v)[currentLine]){
        _maxSquare -= 1;
    }

    for(int m = currentLine; m < currentLine + _maxSquare; m++){
        if((v)[m] < (v)[currentLine]){
            _maxSquare -= 1;
            m = currentLine;
        }
    }

    for(size_t i=0; i<(v).size(); i++){
        v2.push_back((v)[i]);
        v3.push_back(colunas - (v)[i]);
    }

    for(int l = 1; l <= _maxSquare; l++){

        for(int j = currentLine; j < currentLine+l; j++){
            v2[j] -= l;
            v3[j] += l;
        }

        int newCurrentLine = (int)distance(v3.begin(),min_element(v3.begin(), v3.end()));

        num += computeConfigurations(v2, newCurrentLine);

        for(int k = currentLine; k < currentLine+l; k++){
            v2[k] += l;
            v3[k] -= l;
        }
    }
    umap.insert({v, num-1L});
    return num;
}

int main(){
    int temp, flag = 0;
    long long num;
    vector<int> v;

    cin >> linhas;
    cin >> colunas;

    for(int i = 0; i < linhas; i++) {
        cin >> temp;
        if(temp == 0){
            flag += 1;
        }
        v.push_back(temp);
    }

    if(flag == linhas){
        cout << 0 << endl;
        return 0;
    }

    num = computeConfigurations(v, 0);

    cout << num << endl;

    return 0;
}
