#include <iostream>
#include <fstream>
#include <valarray>
int main() {
    int xn=0,yn=0,fx_r=0,fy_r=0,fx_l=0,fy_l=0;
    double max_d_r=0;
    double max_d_l=0;
    std::ifstream in("in.txt"); // окрываем файл для чтения
    int x=0; int y=0;
    in >> xn >> yn;
    double dist;
    while (in >> x >> y)
    {
            //растояние
            dist = fabs(yn*x-xn*y)/sqrt(xn*xn+yn*yn);
            //<0 - справа:
            if((xn*y-yn*x)<=0 && dist>=max_d_r){
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
    in.close();     // закрываем файл
    std::cout << "Leftmost: " << fx_l << " " << fy_l << "\n";
    std::cout << "Rightmost: " << fx_r << " " << fy_r << "\n";
}
