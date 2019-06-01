#include"matrix.h"
#include"matrix.cpp"
int main(){
	Matrix<double> a(3,3);
	std::cin>>a;
	std::cout<<a<<std::endl;
	a.Swaprows(1,3);
	std::cout<<a<<std::endl;
	a.Krows(1,3);
	std::cout<<a<<std::endl;
	a.RowAddKrow(1,3,2);
	std::cout<<a<<std::endl;
	return 0;
}
