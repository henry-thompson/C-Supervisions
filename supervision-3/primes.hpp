namespace ht367
{
    template<int N, int D>
    class HasDivisor
    {
        public:
        static const int HAS_DIVISOR = (N % D) && HasDivisor<N, D - 1>::HAS_DIVISOR;
    };

    template<int N>
    class HasDivisor<N, 1>
    {
        public:
        static const int HAS_DIVISOR = true;
    };

    template <int N>
    class IsPrime
    {
        public:
        static const int ISPRIME = HasDivisor<N, N - 1>::HAS_DIVISOR;
    };

    template <>
    class IsPrime<1>
    {
        public:
        static const int ISPRIME = false;
    };
}