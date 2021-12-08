#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>
#include <map>

using namespace std;
string * StringToMass(string base_str, char delim, int size){
    size_t pos = 0;
    size_t base_str_size = base_str.size();
    size_t delim_size=1;
    string temp;
    int i=0;
    string *mass_str = new string[size];
    while (pos < base_str_size) {
        temp = temp.assign(base_str, pos, base_str.find(delim, pos) - pos);
        if (temp.size() > 0)  // проверка на пустую строку при необходимости
        {
            mass_str[i] = temp;
            i++;
            if(i==size){
                break;
            }
        }
        pos += temp.size() + delim_size;
    }
    return mass_str;
}
//napr = 1 напрво - true; налево - false
double y_tochky_vstrechy(double y_0, int napr, double v_y, double v_x, double x, double x_0, double x_d, double g, double v_0){
    double new_t=y_0+napr*(v_y/v_x)*(x-x_0-2*x_d)-g*(pow(x-x_0-2*x_d,2)/(2*pow(v_0,2)));
    return std::round(new_t * 10000000000.0) / 10000000000.0;
}
void polet(string file_name, int mass_size,string *mass_stolbov,int index=0,int napr=1, double g=9.81, double y_0=1,double x_0=0, double x_d=0, double v_x=3, double v_y=1, double v_0=3.162277, int nomer_stolba=0){
    if(index == 0){// первый вход - наполним массив столбов до первого пападания
        std::string line;
            int k= 0;
            double x,y,new_y;
        std::ifstream in(file_name); // окрываем файл для чтения
        if (in.is_open()) {
            // переписать формат ввода....
            while (getline(in, line)) // перебераем столбы
            {
                //кусок кода надо формить красиво
                k++;

                if (k == 1) {
                    mass_stolbov[k - 1] = "0 " + line;
                    string *values_start = StringToMass("0 " + line, ' ', 2);
                    y_0 = atof(values_start[1].c_str());
                    x_0 = atof(values_start[0].c_str());

                    delete[] values_start;
                    if (line.length() == 0) {
                        std::cout << "0" << std::endl;
                        break;
                    }
                    continue;
                }
                if (k == 2) {
                    string *values_start = StringToMass(line, ' ', 2);
                    x_d = 0; // коэф смещения
                    v_x = atof(values_start[0].c_str());
                    v_y = atof(values_start[1].c_str());
                    v_0 = sqrt(pow(v_x, 2) + pow(v_y, 2));

                    delete[] values_start;
                    if (line.length() == 0 || abs(v_x) + abs(v_y) == 0) {
                        std::cout << "0" << std::endl;
                        break;
                    }
                    continue;
                }
                string *values = StringToMass(line, ' ', 2);
                x = atof(values[0].c_str());
                y = atof(values[1].c_str());
                //проверка столбика
                new_y = y_tochky_vstrechy(y_0, napr, v_y, v_x, x, x_0, x_d, g, v_0);
                if (x <= x_0) {
                    std::cout << "0" << std::endl;
                    break;
                }
                if (new_y <= 0) {
                    std::cout << to_string(nomer_stolba) << std::endl;
                    break;
                }
                if (new_y <= y) { // попал
                    mass_stolbov[k - 2] = line;
                    x_d = x - x_d; //смещение
                    //рекурсим
                    index++;
                    napr = -1 * napr;
                    //тут надо развернуть массив координат столбов
                    if (k - 1 != 2) {
                        string *mass_stolbov_2 = new string[k - 1];
                        for (int i = 0; i < k - 1; i++) {
                            mass_stolbov_2[i] = mass_stolbov[i];
                        }
                        delete[] mass_stolbov;
                        string *mass_stolbov_2_1 = new string[k - 1];
                        for (int i = 0; i < k - 1; i++) {
                            mass_stolbov_2_1[i] = mass_stolbov_2[k - 2 - i];
                        }
                        for (int i = 0; i < k - 1; i++) {
                            mass_stolbov_2[i] = mass_stolbov_2_1[i];
                        }
                        delete[] mass_stolbov_2_1;
                        mass_size = k - 1;
                        delete[] values;
                        polet(file_name, mass_size, mass_stolbov_2, index, napr, g, y_0, x_0, x_d, v_x, v_y, v_0,
                              nomer_stolba);
                        break;
                    } else {
                        std::cout << to_string(nomer_stolba) << std::endl;
                        break;
                    }
                } else { // не попал
                    nomer_stolba += napr * 1;
                    //тут надо слхранить координаты в массив
                    mass_stolbov[k - 2] = line;
                    if (k - 1 == mass_size - 1) {
                        std::cout << to_string(nomer_stolba) << std::endl;
                    }
                }
                delete[] values;
            }
        }
    }
//-----------------------------------------------------------------------------------------------
    else{
        int k=0;
        string line;
        double x,y,new_y;
        string *mass_stolbov_1 = new string[mass_size];
        while (true){
            line =mass_stolbov[k];
            k++;
            if(k == 1){
                mass_stolbov_1[k-1]=line;
                continue;
            }
            string *values=StringToMass(line,' ',2);
            x=atof( values[0].c_str() );
            y=atof( values[1].c_str() );
            //проверка столбика
            new_y=y_tochky_vstrechy(y_0, napr, v_y,  v_x,  x,  x_0,  x_d,  g,  v_0);
            if(x==x_0){
                std::cout <<"0" << std::endl;
                break;
            }
            if(new_y <= 0){
                std::cout <<to_string(nomer_stolba) << std::endl;
                break;
            }
            if(new_y<=y){ // попал
                mass_stolbov_1[k-1]=line;
                x_d=x-x_d; //смещение
                //рекурсим
                index++;
                napr=-1*napr;
                //тут разворот массива координат столбов
                if(k!=2){

                    string *mass_stolbov_2 = new string[k];
                    for(int i=0; i<k; i++){
                        mass_stolbov_2[i]=mass_stolbov_1[i];
                    }
                    delete[] mass_stolbov;
                    delete[] mass_stolbov_1;
                    string *mass_stolbov_2_1 = new string[k];
                    for(int i=0; i<k; i++){
                        mass_stolbov_2_1[i]=mass_stolbov_2[k-1-i];
                    }
                    for(int i=0; i<k; i++){
                        mass_stolbov_2[i]=mass_stolbov_2_1[i];
                    }
                    delete[] mass_stolbov_2_1;
                    mass_size=k;
                    polet(file_name,mass_size,mass_stolbov_2,index,napr, g, y_0, x_0,  x_d,  v_x,  v_y,  v_0, nomer_stolba);
                    break;
                }
                else{
                    std::cout <<to_string(nomer_stolba) << std::endl;
                    break;
                }
            }
            else{ // не попал
                //слхраним координаты в массив
                if(x!=x_0){
                    nomer_stolba+=napr*1;
                    mass_stolbov_1[k-1]=line;
                }
                else{
                    std::cout <<"0" << std::endl;
                    break;
                }
            }
            delete[] values;
        }
    }
}
int main(int argc, char** argv) {
    if(argc == 2){
    }else{
        return 1;
    }
    std::string line;
    std::ifstream in(argv[1]); // окрываем файл для чтения
    if (in.is_open()) {
        int m = 0; //mass_size
        while (getline(in, line)) // перебераем столбы
        {
            if (line.length() != 0) {
                m++;
            }
        }
        if(m <=2){
            std::cout <<"0" << std::endl;
        }
        string *mass_stolbov = new string[m];
        polet(argv[1],m, mass_stolbov);
    }
    //
    return 0;
}
