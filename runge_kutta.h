// Dani van Enk, 11823526

#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

// declare used functions
template<class T>
double k1(double (*f)(double, double, T*), double t, double y, double h,
    T *obj_C=nullptr);
template<class T>
double k2(double (*f)(double, double, T*), double t, double y, double h,
    T *obj_C=nullptr);
template<class T>
double k3(double (*f)(double, double, T*), double t, double y, double h,
    T *obj_C=nullptr);
template<class T>
double k4(double (*f)(double, double, T*), double t, double y, double h,
    T *obj_C=nullptr);

// find the next y value using a 4th order Runge-Kutta solver
template <class T>
double next(double (*f)(double, double, T*), double t, double y, double h,
        T *obj_C=nullptr) {

    return y + h / 6 * (k1<T>(f, t, y, h, obj_C) + 2 * k2<T>(f, t, y, h, obj_C)
        + 2 * k3<T>(f, t, y, h, obj_C) + k4<T>(f, t, y, h, obj_C));
};

// help functions for the 4th order Runge-Kutta solver
template <class T>
double k1(double (*f)(double, double, T*), double t, double y, double h,
        T *obj_C) {
    return f(t, y, obj_C);
};
template <class T>
double k2(double (*f)(double, double, T*), double t, double y, double h,
        T *obj_C) {
    return f(t + h/2, y + h/2 * k1<T>(f, t, y, h, obj_C), obj_C);
};
template<class T>
double k3(double (*f)(double, double, T*), double t, double y, double h,
        T *obj_C) {
    return f(t + h / 2, y + h / 2 * k2<T>(f, t, y, h, obj_C), obj_C);
};
template <class T>
double k4(double (*f)(double, double, T*), double t, double y, double h,
        T *obj_C) {
    return f(t + h, y + h * k3<T>(f, t, y, h, obj_C), obj_C);
};

#endif