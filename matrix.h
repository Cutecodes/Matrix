#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<cstring>
template <typename T> class Matrix{//矩阵模板类
protected:
	int rows;
	int cols;
	T* _elem;//数据区
public:
	Matrix();
	Matrix(int r,int c,T* p);//基于数组的构造
	Matrix(int r,int c);//基于输入的构造，或构造全为0的矩阵
	Matrix(Matrix<T> const& m);//基于复制的构造
	~Matrix();
	//
	Matrix<T> operator+(const Matrix<T>&);
	Matrix<T> operator-(const Matrix<T>&);
	Matrix<T> operator*(const Matrix<T>&);
	Matrix<T> operator*(T);
	Matrix<T> operator/(const Matrix<T>&);
	Matrix<T> operator^(int);
	Matrix<T>& operator=(const Matrix<T>&);
	Matrix<T>& operator+=(const Matrix<T>&);
	Matrix<T>& operator-=(const Matrix<T>&);
	Matrix<T>& operator*=(const Matrix<T>&);
	Matrix<T>& operator*=(T);
	Matrix<T>& operator/=(const Matrix<T>&);
	inline T& operator()(int x,int y){return _elem[(x-1)*cols+y-1];}
	//

	friend std::ostream& operator<<(std::ostream& o,Matrix const& m){
	for(int i=0;i<m.rows*m.cols;i++){
		if((i+1)%m.cols ==0)
			o<<m._elem[i]<<std::endl;
		else
			o<<m._elem[i]<<" ";
	}
	return o;
	}//打印矩阵
	friend std::istream & operator >> (std::istream &in, Matrix<T> const &m){
		for(int i=0;i<m.rows*m.cols;i++)
			in>>m._elem[i];
	}

	//
	Matrix<T> operator[](int);//取某行
	Matrix<T> operator()(int);//取某列
	Matrix<T> SubMatrix(int,int,int,int);
	//
	Matrix<T> Rotate();//转置
	Matrix<T> Inverse();//求逆矩阵
	void Swaprows(int r1,int r2);//换行
	void Krows(int r,int k);//第r行乘k
	void RowAddKrow(int r1,int r2,int k);//r1行+=第r2行乘k

	friend T detMatrix(const Matrix<T>&m){//求方阵行列式
		if(m.rows !=m.cols)exit(0);
	int M,n,s,t,k=1;
	T c,x,sn,f=1;
	for(int i =0,j=0;i<m.rows&&j<m.rows;i++,j++){
		if(m._elem[i*m.cols+j]==0){
			for(M=i;m._elem[M*m.cols+j]==0;M++);
			if(M==m.rows){
				sn=0;
				return sn;
			}
			else
				for(n=j;n<m.rows;n++){
					c =m._elem[i*m.cols+n];
					m._elem[i*m.cols+n]=m._elem[M*m.cols+n];
					m._elem[M*m.cols+n]=c;
				}
				k*=(-1);
		}
		for(s=m.rows-1;s>j;s--){
			x=m._elem[s*m.cols+j];
			for(t=j;t<m.rows;t++)
				m._elem[s*m.cols+t]-=m._elem[i*m.cols+t]*(x/m._elem[i*m.cols+j]);
		}
	}
	for(int i=0;i<m.rows;i++)
		f*=m._elem[i*m.cols+i];
	sn=k*f;
	return sn;
	}
};
#endif
