/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 02:39:13 by jpceia            #+#    #+#             */
/*   Updated: 2022/03/20 12:08:59 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRADIENT_HPP
# define GRADIENT_HPP

template <typename T>
void gradient_x(T* M, int width, int height, T* res)
{
    int size = width * height;
    // left column
    for (int k = 0; k < size; k += width)
        res[k] = M[k + 1] - M[k];
    // right column
    for (int k = 0; k < size; k += width)
        res[k + width - 1] = M[k + width - 1] - M[k + width - 2];
    // middle columns
    for (int k = 0; k < size; k += width)
        for (int j = 1; j < width - 1; ++j)
            res[k + j] = (M[k + j + 1] - M[k + j - 1]) / 2.0;
}

template <typename T>
void gradient_y(T* M, int width, int height, T* res)
{
    // top row
    for (int j = 0; j < width; ++j)
        res[j] = M[width + j] - M[j];
    // bottom row
    int start = (height - 1) * width;
    for (int j = 0; j < width; ++j)
        res[start] = M[start + j] - M[start - width + j];
    // middle rows
    for (int k = width; k < start; k += width)
        for (int j = 0; j < width; ++j)
            res[k + j] = (M[k + j + width] - M[k + j - width]) / 2.0;
}

template <typename T>
void smooth_x(T* M, int width, int height)
{
    for (int j = 0; j < height; ++j) // for each row
    {
        T curr = M[j * width];
        T next = M[j * width + 1];
        M[j * width] = (0.5 * curr + 0.25 * next) / 0.75;
        for (int i = 1; i < width - 1; ++i)
        {
            T prev = curr;
            curr = next;
            next = M[j * width + i + 1];
            M[j * width + i] = 0.25 * prev + 0.5 * curr + 0.25 * next;
        }
        M[j * width + width - 1] = (0.25 * curr + 0.5 * next) / 0.75;
    }
}

template <typename T>
void smooth_y(T* M, int width, int height)
{
    for (int i = 0; i < height; ++i) // for each column
    {
        T curr = M[i * height];
        T next = M[(i + 1) * height];
        M[i * height] = (0.5 * curr + 0.25 * next) / 0.75;
        for (int j = 1; j < width - 1; ++j)
        {
            T prev = curr;
            curr = next;
            next = M[j * width + i + 1];
            M[j * width + i] = 0.25 * prev + 0.5 * curr + 0.25 * next;
        }
        M[i * width + width - 1] = (0.25 * curr + 0.5 * next) / 0.75;
    }
}

#endif
