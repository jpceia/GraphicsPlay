/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:20:40 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 02:35:26 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <cmath>
# include <sstream>
# include <string>

namespace rt
{

template <typename T, std::size_t N>
class vector
{
public:
    typedef T value_type;

    // -----------------------------------------------------------------------
    // ---------------------------- CONSTRUCTORS -----------------------------
    // -----------------------------------------------------------------------
    vector()
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] = T();
    }

    vector(const T& value)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] = value;
    }

    vector(const T arr[N])
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] = arr[i];
    }

    vector(const vector& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] = rhs._data[i];
    }

    vector& operator=(const vector& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] = rhs._data[i];
        return *this;
    }

    // -----------------------------------------------------------------------
    // ------------------------------ DESTRUCTOR -----------------------------
    // -----------------------------------------------------------------------
    ~vector()
    {
    }

    // -----------------------------------------------------------------------
    // ------------------------------ ACCESSORS ------------------------------
    // -----------------------------------------------------------------------
    
    T& operator[](std::size_t i)
    {
        return _data[i];
    }

    const T& operator[](std::size_t i) const
    {
        return _data[i];
    }

    std::size_t size() const
    {
        return N;
    }

    // -----------------------------------------------------------------------
    // ----------------------------- OPERATORS -------------------------------
    // -----------------------------------------------------------------------

    // ---------------------- VECTOR - VECTOR OPERATORS ----------------------

    vector& operator+=(const vector& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] += rhs._data[i];
        return *this;
    }

    vector& operator-=(const vector& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] -= rhs._data[i];
        return *this;
    }

    vector operator+(const vector& rhs) const
    {
        vector result(*this);
        result += rhs;
        return result;
    }

    vector operator-(const vector& rhs) const
    {
        vector result(*this);
        result -= rhs;
        return result;
    }

    // -------------------------- SCALAR OPERATORS ---------------------------

    /*
    vector& operator+= (const T& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] += rhs;
        return *this;
    }

    vector& operator-= (const T& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] -= rhs;
        return *this;
    }
    */

    vector& operator*=(const T& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] *= rhs;
        return *this;
    }

    vector& operator/=(const T& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _data[i] /= rhs;
        return *this;
    }

    /*
    vector operator+(const T& rhs) const
    {
        vector result(*this);
        result += rhs;
        return result;
    }

    vector operator-(const T& rhs) const
    {
        vector result(*this);
        result -= rhs;
        return result;
    }
    */
   
    vector operator*(const T& rhs) const
    {
        vector result(*this);
        result *= rhs;
        return result;
    }

    vector operator/(const T& rhs) const
    {
        vector result(*this);
        result /= rhs;
        return result;
    }

    // --------------------------- UNARY OPERATORS ---------------------------

    const vector& operator+(int) const
    {
        return *this;
    }

    vector& operator+(int)
    {
        return *this;
    }
    
    vector operator-(int) const
    {
        vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i)
            result[i] = -_data[i];
        return result;
    }

    // -----------------------------------------------------------------------
    // ---------------------------- OTHER METHODS ----------------------------
    // -----------------------------------------------------------------------
    
    T lengthSquared() const
    {
        T result = T();
        for (std::size_t i = 0; i < N; ++i)
            result += _data[i] * _data[i];
        return result;
    }
    
    T length() const
    {
        return std::sqrt(lengthSquared());
    }

    vector& normalize()
    {
        T len = length();
        if (len > 0)
            *this /= len;
        return *this;
    }

    static vector normalize(const vector& v)
    {
        vector result(v);
        result.normalize();
        return result;
    }

    T dot(const vector& rhs) const
    {
        T result = T();
        for (std::size_t i = 0; i < N; ++i)
            result += _data[i] * rhs[i];
        return result;
    }

private:
    T _data[N];
};


template <typename T, std::size_t N>
T dot(const vector<T, N>& lhs, const vector<T, N>& rhs)
{
    return lhs.dot(rhs);
}

template <typename T>
T cross(const vector<T, 2>& rhs, const vector<T, 2>& lhs)
{
    return rhs[0] * lhs[1] - rhs[1] * lhs[0];
}

template <typename T>
vector<T, 3> cross(const vector<T, 3>& rhs, const vector<T, 3>& lhs)
{
    vector<T, 3> v;

    v[0] = rhs[1] * lhs[2] - rhs[2] * lhs[1];
    v[1] = rhs[2] * lhs[0] - rhs[0] * lhs[2],
    v[2] = rhs[0] * lhs[1] - rhs[1] * lhs[0];
    return v;
}

template <typename T, std::size_t N>
vector<T, N> elementwise_product(const vector<T, N>& lhs, const vector<T, N>& rhs)
{
    vector<T, N> result;
    for (std::size_t i = 0; i < N; ++i)
        result[i] = lhs[i] * rhs[i];
    return result;
}

} // namespace rt

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const rt::vector<T, N>& v)
{
    for (std::size_t i = 0; i < N; ++i)
        os << v[i] << " ";
    return os;
}

template <typename T, std::size_t N>
std::istream& operator>>(std::istream& is, rt::vector<T, N>& v)
{
    for (std::size_t i = 0; i < N - 1; ++i)
    {
        is >> v[i];
        // skip the comma
        is.ignore(1);
    }
    is >> v[N - 1];
    if (is.fail())
    {
        is.clear();
        throw std::runtime_error("Error reading vector");
    }
    return is;
}

template <typename T, std::size_t N>
std::stringstream& operator>>(std::stringstream& is, rt::vector<T, N>& v)
{
    for (std::size_t i = 0; i < N - 1; ++i)
    {
        is >> v[i];
        // skip the comma
        is.ignore(1);
    }
    is >> v[N - 1];
    if (is.fail())
    {
        is.clear();
        throw std::runtime_error("Error reading vector");
    }
    return is;
}

typedef rt::vector<float, 3>	t_rgb;

#endif
