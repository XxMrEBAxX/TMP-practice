#include <iostream>

template <int X, int Y>
struct GCD {
    static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0> {
    static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
private:
    const static int _gcd = GCD<N, D>::value;

public:
    typedef Ratio<N / _gcd, D / _gcd> type;
    static const int num = N / _gcd;
    static const int den = D / _gcd;
};
template <class R1, class R2>
struct _Ratio_add {
    using type = Ratio<R1::num* R2::den + R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_subtract {
    using type = Ratio<R1::num* R2::den - R2::num * R1::den, R1::den* R2::den>;
};

template <class R1, class R2>
struct Ratio_subtract : _Ratio_subtract<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_multiply {
    using type = Ratio<R1::num * R2::num, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_multiply : _Ratio_multiply<R1, R2>::type {};

template <class R1, class R2>
struct _Ratio_divide {
    using type = Ratio<R1::num* R2::den, R1::den* R2::num>;
};

template <class R1, class R2>
struct Ratio_divide : _Ratio_divide<R1, R2>::type {};

//

template <int X>
struct fib {
    static const int result = fib<X - 1>::result + fib<X - 2>::result;
};
template<>
struct fib<2> {
    static const int result = 1;
};
template<>
struct fib<1> {
    static const int result = 1;
};

//

template <int N>
struct INT {
    static const int num = N;
};

template <typename a, typename b>
struct add {
    typedef INT<a::num + b::num> result;
};

template <typename a, typename b>
struct divide {
    typedef INT<a::num / b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template <typename N, typename d>
struct check_div {
    // result 중에서 한 개라도 true 면 전체가 true
    static const bool result = (N::num % d::num == 0) ||
        check_div<N, typename add<d, one>::result>::result;
};

template <typename N>
struct _is_prime {
    static const bool result = !check_div<N, two>::result;
};

template <>
struct _is_prime<two> {
    static const bool result = true;
};

template <>
struct _is_prime<three> {
    static const bool result = true;
};

template <typename N>
struct check_div<N, typename divide<N, two>::result> {
    static const bool result = (N::num % (N::num / 2) == 0);
};

template <int N>
struct is_prime {
    static const bool result = _is_prime<INT<N>>::result;
};

int main() {
    using r1 = Ratio<2, 3>;
    using r2 = Ratio<3, 2>;

    using r3 = Ratio_add<r1, r2>;
    std::cout << "2/3 + 3/2 = " << r3::num << " / " << r3::den << std::endl;

    using r4 = Ratio_multiply<r1, r3>;
    std::cout << "13 / 6 * 2 /3 = " << r4::num << " / " << r4::den << std::endl;

    //

    std::cout << "10 번째 피보나치 수 :: " << fib<10>::result << std::endl;

    //

    std::cout << std::boolalpha;
    std::cout << "Is 2 prime ? :: " << is_prime<2>::result << std::endl;
    std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl;
    std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl;
    std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl;
}