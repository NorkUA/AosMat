#define _USE_MATH_DEFINES
#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <cmath>
#include <algorithm>




using namespace std;

double R1, R2, R3, R4, R5, R6, R7,R8;

string fract_to_bin(string decimal, int n) {

    float conv = stof(decimal);
    int res;
    string save = "";

    while (n) {
        conv *= 2;
        res = (int)conv;

        save += to_string(res);
        conv -= res;
        n--;
    }

    std::reverse(save.begin(), save.end());

    return save;
}

string to_bin(string decimal) { // conert decimal to binary form 

    int convert = stoi(decimal);
    string result = "";
    if (convert == 0) result = "0";
    
    else {
        while (convert) {

            result += to_string((convert % 2));
            convert /= 2;
        }
    }

    std::reverse(result.begin(), result.end());

    return result;
}

string for_negative(string binnary) {

    string res = "";
    int  k = 1;

    for (int i = 0; i < binnary.size(); i++) {

        binnary[i] == '1' ? res.push_back('0') : res.push_back('1'); // 1 for negativ numbers  , and 0 for  positiv
    }
     res[res.size() - 1] == '1' ? res[res.size() - 1] = '2': res[res.size() - 1] = '1';
  

    int i = res.size() - 1;

    while (res[i] == '2') {
        res[i - 1] == '1' ? res[i - 1] = '2': res[i - 1] = '1';
        
        res[i] = '0';
        i--;
    }
    return res;
}

string convert_num(string someNum, int n) {

    string res;

    if (abs(stoi(someNum)) < pow(2, n) ) {

        if (someNum[0] == '-') {

            res = someNum.substr(1, someNum.size() - 1);
            res = to_bin(res);
            res = for_negative(res);
        }

        else {

            res = to_bin(someNum);
        }
    }

    return res;
}

string perform_convertation(bool sign, string num34bit, string num6bit) { // exp -6 , mantisa -34

    string res = "";
    string new34bit = "";
    string mantisa_to_bin;

    new34bit = convert_num(num34bit, 6); // for mantisa 
    int i = 2;
    int exp = 0;

    if (num34bit == "0") {

        while (num6bit[i] == '1') {
            exp--;
            i++;
        }
        exp--;
    }else {

        exp = new34bit.size() - 1;
    }

    int m = 31 + exp; // 2^(6-1)-1

    string exp_to_bin = convert_num(to_string(m), 6);

    std::reverse(exp_to_bin.begin(), exp_to_bin.end());

    while (exp_to_bin.size() < 6) {

        exp_to_bin.push_back('0');
    }

    std::reverse(exp_to_bin.begin(), exp_to_bin.end());
    num6bit = fract_to_bin(num6bit, 34 +exp);
    mantisa_to_bin.insert(mantisa_to_bin.end(), new34bit.begin()+1, new34bit.end());
    mantisa_to_bin.insert(mantisa_to_bin.end(), num6bit.begin(), num6bit.end());

    while (mantisa_to_bin.size() > 34) { // max size of mantiss  is "34"
        mantisa_to_bin.pop_back();
    }

    res += to_string(sign);
    res += "|";

    res.insert(res.end(), exp_to_bin.begin(), exp_to_bin.end());
    res += "|";
    res.insert(res.end(), mantisa_to_bin.begin(), mantisa_to_bin.end());

    return res;
}

string for_cout(double number) {
    if (abs(number) > 63) {  // number is to big  2^6 -1 
        return "inf"; // if the number goes out of bounds during the calculation 
    }
    if (abs(number) == 0) { // cann`t read  " 0 " number
        return "0|000000|0000000000000000000000000000000000";
    }  if (abs(number) <= (2 ^ (-31))) { // 2 ^(6-1) -1 
        return "0|000001|0000000000000000000000000000000000"; // if the number goes out of bounds during the calculation
    }

    bool sign; //  if 1 - number is less than 0 , else - bigger than 0 
    float whole;
    float fractionl;
    string res;

    number >= 0 ?  sign = 0: sign = 1; // determine the sign of a number
  

    number = abs(number);
    whole = (int)number; // extract the whole part 
    fractionl = number - whole; //  extract the fractional part
    res = perform_convertation(sign, to_string(whole), to_string(fractionl));

    return res;
}

double perform_task(  double a, double b) {
    int q = 63; // if number will be to big  char - 5 bit 
    double q1 = 2e-33; // for to small number  2^33

    //for inputing numbers
    if (abs(a) == 0 || abs(b) == 0) { // cann`t read  " 0 " number
        cout << "Sorry we can`t use 0 in this exercise \n 0|000000|0000000000000000000000000000000000";
        return 0; // End our program 
    }else if (abs(a) > q || abs(b) > q) { // check our "a" and "b" for max
       cout << "Number 1 or 2 is inf : \t\tIEEE 754 : 0 or 1   |111111|0000000000000000000000000000000000" << "\n";
        return 0;// End our program 
    } else if (abs(a) < q1 || abs(b) < q1) {// check our "a" and "b" for min
        cout << "Number 1 or 2 is to  small : \n Incorect number  is  \t\tIEEE 754 : 0|000001|0000000000000000000000000000000000" << "\n";
        return 0;// End our program 
    } 

   cout << "Variant 1 by  Bazyliev Ivan" << "\n\n";

   cout << "0 |111110|  1111111111111111111111111111111111   max   // (2 - 2 ^(-34)) * 2 ^ 31 - where 31 =2^5(h)-1  , 34 -m \n";      // (2 - 2 ^(-5)) * 2 ^ 4095
   cout << "1 |111110|  0000000000000000000000000000000000   min   // -(2 - 2 ^(-34)) * 2 ^ 31 - where 31 =2^5(h)-1 34 -m  \n";     // -(2 - 2 ^(-5)) * 2 ^ 4095
   cout << "0 |000001|  0000000000000000000000000000000000   closest to 0   //  (2 ^ (-31) ,  \n";       // 2e-33
   cout << "0 |011111|  0000000000000000000000000000000000   for (1e0) - you can copy for check \n";
   cout << "0 |111111|  0000000000000000000000000000000000   +inf *0 at the beginning,if number is bigger than 0 and (abs) is too big \n";
   cout << "1 |111111|  0000000000000000000000000000000000   inf *1 at the beginning , if number is less than 0 and (abs) is too big   \n";
   cout << "0 |111111|  0000000000000000000000000000000000   NaN values  // it`s can be literals or something else \n\n";

   cout << "Num a  is  " << a << "\t\tIEEE 754 : " << for_cout(a) << "\n";
   cout << "Numb b is  " << b << "\t\tIEEE 754 : " << for_cout(b) << "\n";
   cout << "****************************************************************\nVariant task : a - b/a +1.5/b\n****************************************************************\n";

   R1 = a; 
   cout << "a in R1 :\n"<< "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) << "\nR3: " << for_cout(R3) << "\nR4: "
       << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: "
       << for_cout(R7) <<  "\nR8: "<<for_cout(R8)<< "\n";
   cout << "****************************************************************\n";

    R2 = b;
   cout << "b in R2 :\n<<"<< "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) << "\nR3: " << for_cout(R3) 
       << "\nR4: " << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: "
       << for_cout(R7) << "\nR8: " << for_cout(R8) << "\n";
   cout << "****************************************************************\n";

    R3 = -R2;
   cout << "(-1)*b in R3 :\n" << "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) << "\nR3: "
       << for_cout(R3) << "\nR4: " << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: "
       << for_cout(R7) << "\nR8: " << for_cout(R8) << "\n";
   cout << "****************************************************************\n";

    R4 =R3/R1;
   cout << "-b/a in R4 :\n"<< "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) << "\nR3: " 
       << for_cout(R3) << "\nR4: " << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: "
       << for_cout(R7) << "\nR8: " << for_cout(R8) << "\n";
   cout << "****************************************************************\n";

    R5 = 1.5/R2;
   cout << "1.5/b in R5 :\n" << "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) << "\nR3: "
       << for_cout(R3) << "\nR4: " << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: " 
       << for_cout(R7) << "\nR8: " << for_cout(R8) << "\n";
   cout << "****************************************************************\n";

    R6 = R1+R4;
   cout << "a - b/a in R6 :\n";
   cout << "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) << "\nR3: " << for_cout(R3) 
       << "\nR4: " << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: " 
       << for_cout(R7) << "\nR8: " << for_cout(R8) << "\n";
   cout << "****************************************************************\n";


    R7 = R6+R5;
   cout << "a - b/a +1.5/b in R7 :\n" << "Regist Status : \nR1: " << for_cout(R1) << "\nR2: " << for_cout(R2) 
       << "\nR3: " << for_cout(R3) << "\nR4: " << for_cout(R4) << "\nR5: "<< for_cout(R5) << "\nR6: " << for_cout(R6) << "\nR7: "
       << for_cout(R7) << "\nR8: " << for_cout(R8) << "\n";
   cout << "****************************************************************\n";

    return 0;
}

int main() {
    double a, b;
    cout << "Enter a = ";
    cin >> a;

    cout << "Enter b = ";
    cin >> b;
    cout << endl;

    perform_task(a, b); // start our work


    
}
