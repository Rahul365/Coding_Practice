#include<bits/stdc++.h>
using namespace std;


class Solution {
private:
    string MAX = "2147483647";
    string MIN = "2147483648";
    int l = MAX.length();
    int sign = 1;
    
    bool isNumeric(char ch){
        return ch>='0' && ch<='9';    
    }
    bool isSign(char ch){
        return ch == '-' || ch == '+';
    }
    
    bool isSpace(char ch){
        return ch == ' ';
    }

    string trim(string str){
        //trim from front
        int i = 0;
        int n = str.length();
        while(isSpace(str[i])){
            ++i;
        }
        if(!isNumeric(str[i]) && !isSign(str[i])) return "";
        if(isSign(str[i]))
        {
            sign = (str[i] == '-')?-1:1;
            i++;
        }
        while(str[i] == '0') i++; // trim leading zeroes if any
        
        //trim from back
        
        while(i < n && !isNumeric(str[n-1])){ n--;}
        
        if(i >= n) { return "";}
        return str.substr(i,n);
    }
    /**
        to check non numeric char
    */
    void clean(string &str){
        int i = 0;
        while(i < str.length()){
            if(!isNumeric(str[i])){
                str = str.substr(0,i);
                break;
            }
            ++i;
        }
    }
    
    
    bool overflowcheck(string str){
        if(l > str.length()) return false;
        if(l < str.length()) return true;
        int i = 0;
        int j = 0;
        if(sign == 1){
            //max overflow
            while(i < str.length()){
                if(str[i] < MAX[j]) return false;
                ++i,++j;
            }
        }
        else{
            //min overflow
            while(i < str.length()){
                if(str[i] < MIN[j]) return false;
                ++i,++j;
            }
        }
       return true;
    }
    
    string filter(string str){
         sign = 1;
        string tmp = trim(str);
        clean(tmp);//remove '.' if any  
        return tmp;
    }
public:
    int myAtoi(string str) {
        string tmp = filter(str);
        if(tmp.length() > MAX.length()) return sign==1?INT_MAX:INT_MIN;
        
        if(tmp == MAX)
            return sign == 1?INT_MAX:(sign*INT_MAX);
        if(tmp == MIN)
            return sign == -1?INT_MIN:INT_MAX;
       
        // cout<<tmp<<"\n";
        // cout<<tmp.length() <<" "<<l<<"\n";
        if(overflowcheck(tmp))
        {
            if(sign == -1){
                //overflow INT_MIN value
                return INT_MIN;
            }
            else{
                return INT_MAX;
            } 
        }
        int i = 0;
        int num = 0;
        while(i < tmp.length()){
            if(i == l-1){
                if(sign == -1){
                    if(num > abs(INT_MIN/10)/* || (num == abs(INT_MIN/10) && tmp[i] > MIN[i])*/) 
                        return INT_MIN; 
                }
                else{
                    if(num > abs(INT_MAX/10)/* || (num == abs(INT_MAX/10) && tmp[i] > MAX[i])*/) 
                        return INT_MAX;
                }
            }
            num = num * 10 + (tmp[i] - '0');
            i++;
        }
        num = num * sign;
        
        return num;
    }
};