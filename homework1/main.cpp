#include <iostream>
#include <fstream>
#include <valarray>

using namespace std;


int main() {
    int xn,yn,fx_r,fy_r,fx_l,fy_l;
    int a=0; int b=0;
    double max_d_r=0;
    double max_d_l=0;
    std::ifstream in("in.txt"); // окрываем файл для чтения

        int x=0; int y=0;
        in >> x >> y;
        xn=(-1)*x;
        yn=(-1)*y;
        a=x;
        b=y;
        //std::<<  <<::endl;
        double dist;
        while (in >> x >> y)
        {
                //растояние

                if(xn !=0 && yn !=0){
                   // dist=(abs(-1*(x)/xn+y/yn)/sqrt((1/xn)*(1/xn)+(1/yn)*(1/yn)));
                    double len = std::sqrt((xn ) * (xn) + (yn) * (yn));
                    dist = std::abs((yn ) * x - (xn) * y ) / len;
					//dist = std::round(dist * 10000000000.0) / 10000000000.0;
                }
                else{
                    (xn ==0)? dist =x:dist= y;
                }
                //<0 - справа:
                if(((xn-0)*(y-0)-(yn-0)*(x-0))>=0){
                    if(dist>=max_d_r){
                        max_d_r=dist;
                        fx_r=x;
                        fy_r=y;
                    }
                }//>0 - слева
                else{
                    if(dist>=max_d_l){
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
