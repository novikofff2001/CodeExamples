#include <template.h>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
T sum(std::vector<T> vec)
{
    T sum{0};
    for(typename vector<T>::iterator it = vec.begin(); it!= vec.end(); it++)
        sum += *it;
    return sum / vec.size();
}
//
template <typename T>
ostream& operator<<(ostream& out, vector<T>& vec)
{
    for (typename vector<T>::iterator it = vec.begin(); it!= vec.end(); it++)
    {
        if(it != vec.begin())
            out<<" + ";
        out<<*it;
    }
    return out;
}
//
template <typename T>
void print(vector<T> vec)
{
    cout<<"( "<<vec<<" )"<<" / "<<vec.size()<<" = "<<sum(vec)<<endl;
}
//

template <typename T>
T average(vector<T> vec)
{
    T sum{0};
    for(typename vector<T>::iterator it = vec.begin(); it!= vec.end(); it++)
        sum += *it;
    return sum / vec.size();
}
//
int main()
{
    vector<int> int_vec;
    vector<double> double_vec;
    vector<char> char_vec;
    for(int i = 0;i<10;i++)
    {
        int_vec.push_back(i);
        double_vec.push_back(i+0.5);
    }
    print(int_vec);
    print(double_vec);
    //
    vector<PointOnPlane<double>> points = {PointOnPlane<double>(1.2, 0), PointOnPlane<double>(0.8, 0.8)};
    PointOnPlane<double> aver_point = average(points);
    cout<<aver_point.get_x()<<" "<<aver_point.get_y()<<" ";



}
