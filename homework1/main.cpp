#include <iostream>
#include <fstream>
#include <valarray>
int main() {
    int x=0,y=0,xn=0,yn=0,fx_r=0,fy_r=0,fx_l=0,fy_l=0;
    double max_d_r=0,max_d_l=0,dist;
    std::ifstream in("in.txt"); // окрываем файл для чтения
    in >> xn >> yn;
    while (in >> x >> y)
    {
        dist = fabs(yn*x-xn*y)/sqrt(xn*xn+yn*yn);//растояние
        if((xn*y-yn*x)<=0 && dist>=max_d_r){//<0 - справа:
            max_d_r=dist;
            fx_r=x;
            fy_r=y;
        }//>0 - слева
        if( (xn*y-yn*x)>0 && dist>=max_d_l){
            max_d_l=dist;
            fx_l=x;
            fy_l=y;
        }
    }
    std::cout << "Leftmost: " << fx_l << " " << fy_l << "\n";
    std::cout << "Rightmost: " << fx_r << " " << fy_r << "\n";
}