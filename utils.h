#ifndef UTILS_H
#define UTILS_H

template<class T>
bool pertenece(T x, vector<T> v) {
    for (int i = 0; i < v.size(); ++i) {
        if (x == v[i]) {
            return true;
        }
    }
    return false;
}

template<class T>
int cantApariciones (T elem, vector<T> v ){
    int res = 0;
    for (int i = 0; i <v.size() ; ++i) {
        if (v[i] == elem){
            res++;
        }
    }
    return res;
}

template<class T>
bool camposRepetidos(vector<T> v){
    for (int i = 0; i < v.size() ; ++i) {
        if(cantApariciones (v[i],v)>1){
            return true;
        }
    }
    return false;
}

template<class T>
bool subset(vector<T> v1, vector<T> v2) {
    for (int i = 0; i < v1.size(); ++i) {
        if (not pertenece(v1[i], v2)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool seteq(vector<T> v1, vector<T> v2) {
    return subset(v1, v2) and subset(v2, v1);
}

#endif //UTILS_H
