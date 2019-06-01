#include<iostream>
#include "matrix.h"
#include "matrix.cpp"
int main(){
	double a[9]={1,-1,2,0,1,-1,1,2,1};
	Matrix<double> b(3,3,a),c,d(b),e,f(3,3),eb;//??????
	c=b;//????
	e=b^2;
	std::cout<<b<<std::endl;
	std::cout<<c<<std::endl;
	std::cout<<d<<std::endl;
	std::cout<<f<<std::endl;
	std::cin>>f;
	std::cout<<f<<std::endl;
	//
	std::cout<<b+d<<std::endl;//??????
	std::cout<<b-d<<std::endl;
	std::cout<<b*b<<std::endl;
	std::cout<<b*3<<std::endl;
	std::cout<<e/b<<std::endl;//Â³Ã½Â·Â¨Ã“ÃÃŽÃŠÃŒÃ¢
	std::cout<<e<<std::endl;
	std::cout<<b<<std::endl;
	b+=b;
	c-=c;
	d*=d;
	f*=3;
	e/=b;
	std::cout<<b<<std::endl;
	std::cout<<c<<std::endl;
	std::cout<<d<<std::endl;
	std::cout<<f<<std::endl;
	std::cout<<e<<std::endl;
	//
    std::cout<<b(2,1)<<std::endl;//??????
    std::cout<<b[2]<<std::endl;
    std::cout<<b(2)<<std::endl;
    std::cout<<b.SubMatrix(2,3,2,3)<<std::endl;
    std::cout<<b.Rotate()<<std::endl;
    std::cout<<detMatrix(b)<<std::endl;//==16
	//
	std::cout<<b.Inverse()<<std::endl;//ä¸æ”¯æŒdoubleï¼Œè¯¯å·®å¤§
	b=b*b.Inverse();
	std::cout<<b<<std::endl;
    //

	return 0;

}
