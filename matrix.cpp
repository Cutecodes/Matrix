#include "matrix.h"
#include<iostream>
#include<cstring>
template <typename T>
Matrix<T>::Matrix(){
	rows = 0;
	cols = 0;
	_elem = NULL;
}

template <typename T>
Matrix<T>::Matrix(int r,int c,T* p){
	rows = r;
	cols = c;
	_elem = new T[r*c];
	for(int i=0;i<r*c;i++)
		_elem[i] = p[i];
}

template <typename T>
Matrix<T>::Matrix(int r,int c){
	rows = r;
	cols = c;
	_elem = new T[r*c];
	for(int i=0;i<r*c;i++)
		_elem[i] = 0;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> const& m){
	rows = m.rows;
	cols = m.cols;
	_elem = new T[rows*cols];
	for(int i=0;i<cols*rows;i++)
		_elem[i] = m._elem[i];
}

template <typename T>
Matrix<T>::~Matrix(){
	if(_elem!=NULL){
		delete[] _elem;
		_elem = NULL;
	}
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>&m){
	if(rows != m.rows || cols != m.cols )exit(0);
	Matrix<T> temp;
	temp.rows = rows;
	temp.cols = cols;
	temp._elem = new T[rows*cols];
	for(int i=0;i<rows*cols;i++)
		temp._elem[i]=_elem[i]+m._elem[i];
	return temp;

}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>&m){
	if(rows != m.rows || cols != m.cols )exit(0);
	Matrix<T> temp;
	temp.rows = rows;
	temp.cols = cols;
	temp._elem = new T[rows*cols];
	for(int i=0;i<rows*cols;i++)
		temp._elem[i]=_elem[i]- m._elem[i];
	return temp;

}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>&m){
	if(cols != m.rows)exit(0);
	Matrix<T> temp;
	temp.rows = rows;
	temp.cols = m.cols;
	temp._elem = new T[rows*m.cols];
	memset(temp._elem,0,sizeof(T)*rows*m.cols);//初始化为0
	temp._elem[0]=0;
	int k,count,t;
	k=count=t=0;
	for(int i=0;i<rows;i++){
		while(k<m.cols){
			for(int j=i*cols;j<(i+1)*cols;j++){
					temp._elem[count] +=_elem[j]*m._elem[t];
					t+=m.cols;
			}
			k++;
			t=k;
			count++;
		}
		t=0;
		k=0;
	}
	return temp;

}
template <typename T>
Matrix<T> Matrix<T>::operator*(T t){
	Matrix<T> temp;
	temp.rows = rows;
	temp.cols = cols;
	temp._elem = new T[rows*cols];
	for(int i=0;i<rows*cols;i++)
		temp._elem[i] = _elem[i]*t;
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>&m){
	if(rows!=cols)exit(0);
	Matrix<T> temp,temp1;
	temp1=m;
	temp=(*this)*temp1.Inverse();
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator^(int t){
	Matrix<T> temp(*this);
	for(int i=1;i<t;i++)
		temp*=(*this);
	return temp;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>&m){
	rows = m.rows;
	cols = m.cols;
	_elem = new T[rows*cols];
	for(int i=0;i<rows*cols;i++)
		_elem[i] = m._elem[i];
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>&m){
	if(rows!=m.rows || cols!=m.cols)exit(0);
	for(int i =0;i<rows*cols;i++)
		_elem[i]+=m._elem[i];
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>&m){
	if(rows!=m.rows || cols!=m.cols)exit(0);
	for(int i =0;i<rows*cols;i++)
		_elem[i]-=m._elem[i];
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>&m){
	(*this)=(*this)*m;
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T t){
	(*this)=(*this)*t;
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix<T>&m){
	Matrix<T> temp;
	temp=m;
	(*this)=(*this)*temp.Inverse();
	return (*this);
}

//
/*template <typename T>
std::ostream& operator<<(std::ostream& o,Matrix<T> const& m){
	for(int i=0;i<m.rows*m.cols;i++){
		if((i+1)%m.cols ==0)
			o<<m._elem[i]<<std::endl;
		else
			o<<m._elem[i]<<" ";
	}
	return o;
}*/

template <typename T>
Matrix<T> Matrix<T>::operator[](int r){
	Matrix<T> temp;
	temp.rows =1;
	temp.cols =cols;
	temp._elem = new T[cols];
	for(int i=0;i<cols;i++)
		temp._elem[i]=_elem[(r-1)*cols+i];
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator()(int c){
	Matrix<T> temp;
	temp.rows =rows;
	temp.cols =1;
	temp._elem = new T[rows];
	for(int i=0;i<cols;i++)
		temp._elem[i]=_elem[i*cols+c-1];
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::SubMatrix(int r1,int r2,int c1,int c2){
	//需要对参数检查，但此处并未实现
	int count =0;
	Matrix<T> temp;
	temp.rows=r2-r1+1;
	temp.cols=c2-c1+1;
	temp._elem = new T[temp.rows*temp.cols];
	for(int i=(r1-1)*cols+c1-1;i<(r2-1)*cols+c2;i++){
		temp._elem[count++]=_elem[i];
		if(count % temp.cols ==0)
			i+=(cols+c1-c2-1);
	}
	return temp;
}

template <typename T>
Matrix<T> Matrix<T>::Rotate(){
	Matrix<T> temp;
	temp.rows =cols;
	temp.cols =rows;
	temp._elem = new T[rows*cols];
	for(int i =0;i<rows;i++)
		for(int j=0;j<cols;j++)
			temp._elem[j*rows+i]=_elem[i*cols+j];
	return temp;
}


template <typename T>
Matrix<T> Matrix<T>::Inverse(){
	int count =0;
	T var =0;
	T var1;
	if((var=detMatrix(*this))==0)exit(0);
	Matrix temp1,temp2;
	temp1.rows =rows;
	temp1.cols =cols;
	temp1._elem =new T[rows*cols];

	temp2.rows = rows-1;
	temp2.cols = cols-1;
	temp2._elem = new T[temp2.rows*temp2.cols];

	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++){
			int l;
			if((i+j)%2==0)
				l=1;
			else
				l=-1;
			for(int k=0;k<temp2.rows*temp2.cols;){
				if(count/rows==i||count%rows ==j){
					count++;
					continue;
				}
				temp2._elem[k]=_elem[count];
				k++;
				count++;
			}
			count=0;
			var1 =detMatrix(temp2)*l/var;
			temp1._elem[j*rows+i]=var1?var1:0;
		}
		return temp1;
}

template <typename T>
void Matrix<T>::Swaprows(int r1,int r2){//换行
	T temp;
	for(int i =0;i<cols;i++){
		temp=_elem[(r1-1)*cols+i];
		_elem[(r1-1)*cols+i]=_elem[(r2-1)*cols+i];
		_elem[(r2-1)*cols+i]=temp;
	}
}
template <typename T>
void Matrix<T>::Krows(int r,int k){//第r行乘k
	for(int i=0;i<cols;i++)
		_elem[(r-1)*cols+i]*=k;
}
template <typename T>
void Matrix<T>::RowAddKrow(int r1,int r2,int k){//r1行+=第r2行乘k
	for(int i=0;i<cols;i++)
		_elem[(r1-1)*cols+i]+=(_elem[(r2-1)*cols+i]*k);
}
/*template <typename T>
T detMartix(const Matrix<T> m){
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
}*/
