#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include "json.hpp"
#include<cmath>
using namespace std;
long long decodeValue(const string& value,int base){
    long long res=0;
    for(char c:value){
        int digit=(c>='0' && c<='9')? c-'0':c-'A'+10;
        res=res*base+digit;
    }
    return res;
}
double lagrange(const vextor<pair<int,double>>& points){
    double constant=0.0;
    int n=points.size();
    for(int i=0;i<n;i++){
        double term=points[i].second;
        for(int j=0;j<n;j++){
            if(i!=j){
                term*=(0.0-points[j].first)/(points[i].first-points[j].first);
            }
        }
        constant+=term;
    }
    return constant;
}
int main(){
    ifstream file("input.json");
    if(!file.is_open()){
        cerr<<"ERROR IN OPENING FILE"<<endl;
        return 1;
    }
    Json::Value root;
    file>>root;
    int n=root["keys"]["n"].asInt();
    int k=root["keys"]["k"].asInt();
    vector<pair<int,double>> points;
    for(int i=1;i<=n;i++){
        string x_str=to_string(i);
        int x=i;
        int base=stoi(root[x_str]["base"].asString());
        string value=root[x_str]["value"].asString();
        double y=decodeValue(value,base);
        points.emplace_back(x,y);
    }
    double constant=lagrange(points);
    cout<<"Constant term(c): "<<constant<<endl;
    return 0;
}