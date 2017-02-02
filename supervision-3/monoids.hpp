#include <vector>
#include <set>
#include <stdint.h>
#include <iostream>

namespace ht367
{
    namespace monoids
    {
        enum MonoidType {
            Multiply, Add, Union
        };

        template<class T, T Id, MonoidType Op>
        class Monoid
        {
            public:
            Monoid() : value(Id) {};
            Monoid(T value) : value(value) {};

            T getValue();
            Monoid<T, Id, Op> append(std::vector<Monoid<T, Id, Op> > monoids);
            Monoid<T, Id, Op> append(Monoid<T, Id, Op> monoid);

            protected:
            T value;
        };

        template<class T, T Id>
        class Monoid<T, Id, Add>
        {
            public:
            Monoid() : value(Id) {};
            Monoid(T value) : value(value) {};

            Monoid<T, Id, Add> append(Monoid<T, Id, Add> monoid)
            {
                return Monoid(this->value + monoid.value);
            }

            T getValue()
            {
                return value;
            }

            protected:
            T value;
        };

        template<class T, T Id>
        class Monoid<T, Id, Multiply>
        {
            public:
            Monoid() : value(Id) {};
            Monoid(T value) : value(value) {};

            Monoid<T, Id, Multiply> append(Monoid<T, Id, Multiply> monoid)
            {
                return Monoid(this->value * monoid.value);
            }

            T getValue()
            {
                return value;
            }

            protected:
            T value;
        };
        
        class EmptyListException {};

        template<class T, T Id, MonoidType Op>
        Monoid<T, Id, Op> concat(std::vector<Monoid<T, Id, Op> > monoids)
        {
            if (monoids.size() == 0) {
                throw new EmptyListException();
            }

            Monoid<T, Id, Op> result = monoids[0];

            for (uint16_t i = 1; i < monoids.size(); i++) {
                result = result.append(monoids[i]);
            }

            return result;
        }
    }
}

typedef ht367::monoids::Monoid<int, 0, ht367::monoids::Add> intAddMonoid_t;
typedef ht367::monoids::Monoid<int, 1, ht367::monoids::Multiply> intMultMonoid_t;