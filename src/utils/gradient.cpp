/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:24:32 by jpceia            #+#    #+#             */
/*   Updated: 2022/03/11 18:27:14 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void gradient_x(float** M, int width, int height, float** grad_x)
{
    // left column
    for (int i = 0; i < height; ++i)
        grad_x[i][0] = M[i][1] - M[i][0];
    // right column
    for (int i = 0; i < height; ++i)
        grad_x[i][width - 1] = M[i][width - 1] - M[i][width - 2];
    // middle columns
    for (int j = 1; j < width - 1; ++j)
    {
        for (int i = 0; i < height; ++i)
            grad_x[i][j] = M[i][j + 1] - M[i][j - 1];
    }
}

void gradient_y(float** M, int width, int height, float** grad_y)
{
    // top row
    for (int i = 0; i < width; ++i)
        grad_y[0][i] = M[1][i] - M[0][i];
    // bottom row
    for (int i = 0; i < width; ++i)
        grad_y[height - 1][i] = M[height - 1][i] - M[height - 2][i];
    // middle rows
    for (int j = 1; j < height - 1; ++j)
    {
        for (int i = 0; i < width; ++i)
            grad_y[j][i] = M[j + 1][i] - M[j - 1][i];
    }
}
