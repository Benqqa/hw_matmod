#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>

using namespace std;
int main() {
    std::string line;
    double xn,yn,fx_r,fy_r,fx_l,fy_l;
    double max_d_r=0;
    double max_d_l=0;
    std::ifstream in("in.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        double x=0; double y=0;
        in >> x >> y;
        xn=(-1)*x;
        yn=(-1)*y;
        while (in >> x >> y)
        {
                //растояние
                double dist;
                if(xn !=0 && yn !=0){
                    dist=(abs(-1*(x)/xn+y/yn)/sqrt((1/xn)*(1/xn)+(1/yn)*(1/yn)));
					//dist = std::round(dist * 10000000000.0) / 10000000000.0;
                }
                else{
                    (xn ==0)? dist =x:dist= y;
                }
                //<0 - справа:
                if(((xn-0)*(y-0)-(yn-0)*(x-0))>=0 && dist>=max_d_r){
                        max_d_r=dist;
                        fx_r=x;
                        fy_r=y;
                }//>0 - слева
                if( ((xn-0)*(y-0)-(yn-0)*(x-0))<0 && dist>=max_d_l){
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
