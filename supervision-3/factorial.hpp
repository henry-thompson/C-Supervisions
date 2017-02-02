namespace ht367
{
    template<int N>
    class Factorial
    {
        public:
        static const int FACTORIAL = Factorial<N - 1>::FACTORIAL * N;
    };

    template<>
    class Factorial<0>
    {
        public:
        static const int FACTORIAL = 1;
    };
}
