#include <iostream>
#include <fstream>
#include <valarray>

using namespace std;
int main() {
    std::string line;
    int xn,yn,fx_r,fy_r,fx_l,fy_l;
    double max_d_r=0;
    double max_d_l=0;
    std::ifstream in("in.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        int x=0; int y=0;
        in >> x >> y;
        xn=-x;
        yn=-y;
        double dist;
        while (in >> x >> y)
        {
                //растояние
                (xn ==0)? dist =x:(yn ==0)? dist= y : dist = abs(xn*x-yn*y)/sqrt(xn*xn+yn*yn);
                //<0 - справа:
                if((xn*y-yn*x)>=0 && dist>=max_d_r){
                        max_d_r=dist;
                        fx_r=x;
                        fy_r=y;
                }//>0 - слева
                if( (xn*y-yn*x)<0 && dist>=max_d_l){
                    max_d_l=dist;
                    fx_l=x;
                    fy_l=y;
                }
        }
    }
    in.close();     // закрываем файл
    std::cout << "Leftmost: " << fx_l << " " << fy_l << "\n";
    std::cout << "Rightmost: " << fx_r << " " << fy_r << "\n";

    return 0;
}
