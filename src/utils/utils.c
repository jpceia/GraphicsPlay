/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   mlx_utils.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jceia <jceia@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/09/01 20:28:58 by jceia			 #+#	#+#			 */
/*   Updated: 2021/09/02 00:22:11 by jceia			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "miniRT.h"

void	data_draw_image(t_data *vars)
{
	calculate_camera_params(
		vars->camera, vars->width, vars->height);
	raytrace_scenario(vars);
	create_bmp(vars->file_name, vars->width, vars->height, vars->buf);
}

void	data_init(t_data *vars, const t_args *args)
{
	ft_bzero(vars, sizeof(*vars));
	if (!parse_data_from_file(vars, args->scene_fname))
		clean_exit(vars, "Error parsing data from file", data_clean, 1);
	vars->buf = ft_calloc(args->width * args->height, sizeof(*vars->buf));
	if (!vars->buf)
		clean_exit(vars, "Error allocating memory to buffer",
			data_clean, 1);
	if (!vars->camera)
		clean_exit(vars, "Undefined camera", data_clean, 1);
	vars->file_name = ft_strdup(args->output_fname);
	vars->width = args->width;
	vars->height = args->height;
	vars->n_antialias = args->n_antialias;
	vars->n_reflections = args->n_reflections;
}
