#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>
#include <map>

using namespace std;
double y_tochky_vstrechy(double y_0, int napr, double v_y, double v_x, double x, double x_0, double x_d, double g){
    double new_t=y_0+napr*(v_y/v_x)*(x-x_0-2*x_d)-g*((x-x_0-2*x_d)*(x-x_0-2*x_d)/(2*v_x*v_x));
    return std::round(new_t * 10000000000.0) / 10000000000.0;
}
void polet(string file_name, int mass_size,double** mass_stolbov,int index=0,int napr=1, double g=9.81, double y_0=1,double x_0=0, double x_d=0, double v_x=3, double v_y=1, int nomer_stolba=0){
    int k=0;
    string line;
    double x,y,new_y;
    // string *mass_stolbov_1 = new string[mass_size];
    double** mass_stolbov_1 = new double* [mass_size];
    for ( int i = 0; i < mass_size; i++)
        mass_stolbov_1[i] = new double[2];
    while (true){
        x = mass_stolbov[k][0];
        y = mass_stolbov[k][1];
        k++;
        if(k == 1){
            mass_stolbov_1[k-1][0]=x;
            mass_stolbov_1[k-1][1]=y;
            continue;
        }
        //проверка столбика
        new_y=y_tochky_vstrechy(y_0, napr, v_y,  v_x,  x,  x_0,  x_d,  g);
        if(x==x_0){
            std::cout <<"0" << std::endl;
            break;
        }
        if(new_y <= 0){
            std::cout <<to_string(nomer_stolba) << std::endl;
            break;
        }
        if(new_y<=y){ // попал
            mass_stolbov_1[k-1][0]=x;
            mass_stolbov_1[k-1][1]=y;
            x_d=x-x_d; //смещение
            //рекурсим
            index++;
            napr=-1*napr;
            //тут разворот массива координат столбов
            if(k!=2){
                double** mass_stolbov_2 = new double*[k];
                for ( int i = 0; i < k; i++)
                    mass_stolbov_2[i] = new double[2];

                for (int i = 0; i < k; i++) {
                    mass_stolbov_2[i] = mass_stolbov_1[i];
                }
                delete[] mass_stolbov_1;
                double temp;
                for (int j = 0, i = (k) - 1; j < i; --i, ++j)
                {
                    temp = mass_stolbov_2[i][0];
                    mass_stolbov_2[i][0] = mass_stolbov_2[j][0];
                    mass_stolbov_2[j][0] = temp;

                    temp = mass_stolbov_2[i][1];
                    mass_stolbov_2[i][1] = mass_stolbov_2[j][1];
                    mass_stolbov_2[j][1] = temp;
                }

                mass_size=k;
                polet(file_name,mass_size,mass_stolbov_2,index,napr, g, y_0, x_0,  x_d,  v_x,  v_y, nomer_stolba);
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
                mass_stolbov_1[k-1][0]=x;
                mass_stolbov_1[k-1][1]=y;
            }
            else{
                std::cout <<"0" << std::endl;
                break;
            }
        }
    }
}
void polet0(string file_name, int mass_size,double** mass_stolbov,int index=0,int napr=1, double g=9.81, double y_0=1,double x_0=0, double x_d=0, double v_x=3, double v_y=1,  int nomer_stolba=0){
    std::string line;
    int k= 0;
    double x,y,new_y;
    std::ifstream in(file_name); // окрываем файл для чтения
    if (in.is_open()) {
        // переписать формат ввода....
        in >> y_0;
        if (x == 0 && y==0) {
            std::cout << "0" << std::endl;
        }

        in >> v_x >> v_y;
        if (abs(v_x) + abs(v_y) == 0) {
            std::cout << "0" << std::endl;
        }
        k=2;
        while (in >> x >> y) // перебераем столбы
        {
            k++;
            //проверка столбика
            new_y = y_tochky_vstrechy(y_0, napr, v_y, v_x, x, x_0, x_d, g);
            if (x <= x_0) {
                std::cout << "0" << std::endl;
                break;
            }
            if (new_y <= 0) {
                std::cout << to_string(nomer_stolba) << std::endl;
                break;
            }
            if (new_y <= y) { // попал
                mass_stolbov[k - 2][0] = x;
                mass_stolbov[k - 2][1] = y;
                x_d = x - x_d; //смещение
                //рекурсим
                index++;
                napr = -1 * napr;
                //тут надо развернуть массив координат столбов
                if (k - 1 != 2) {
                    double** mass_stolbov_2 = new double*[k - 1];
                    for ( int i = 0; i < k - 1; i++)
                        mass_stolbov_2[i] = new double[2];

                    for (int i = 1; i < k - 1; i++) {
                        mass_stolbov_2[i][0] = mass_stolbov[i][0];
                        mass_stolbov_2[i][1] = mass_stolbov[i][1];
                    }
                    delete[] mass_stolbov;
                    double temp;
                    for (int j = 0, i = (k - 1) - 1; j < i; --i, ++j)
                    {
                        temp = mass_stolbov_2[i][0];
                        mass_stolbov_2[i][0] = mass_stolbov_2[j][0];
                        mass_stolbov_2[j][0] = temp;

                        temp = mass_stolbov_2[i][1];
                        mass_stolbov_2[i][1] = mass_stolbov_2[j][1];
                        mass_stolbov_2[j][1] = temp;
                    }
                    mass_size = k - 1;
                    polet(file_name, mass_size, mass_stolbov_2, index, napr, g, y_0, x_0, x_d, v_x, v_y,
                          nomer_stolba);
                    break;
                } else {
                    std::cout << to_string(nomer_stolba) << std::endl;
                    break;
                }
            } else { // не попал
                nomer_stolba += napr * 1;
                mass_stolbov[k - 2][0] = x;
                mass_stolbov[k - 2][1] = y;
                if (k - 1 == mass_size - 1) {
                    std::cout << to_string(nomer_stolba) << std::endl;
                }
            }
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
        double** mass_stolbov = new double* [m];
        for ( int i = 0; i < m; i++)
            mass_stolbov[i] = new double[2];
        polet0(argv[1],m, mass_stolbov);
    }
    //
    return 0;
}
