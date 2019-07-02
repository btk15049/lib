#include<bits/stdc++.h>

using namespace std;

template<typename F, typename T>
inline T multi_op(T&& v){
    return v;
}

template<typename F, typename T, typename... U>
inline T multi_op(T&& head, U&&... tail){
    return F(head, multi_op<F>(tail...));
}

template<typename T, typename... U>
inline T multi_min(T head, U&&... tail){
    return multi_op<operator<T><, T>(head,tail...);
}
