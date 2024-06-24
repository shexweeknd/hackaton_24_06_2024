/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hck_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabarij <nrabarij@student.42antanana>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:41:54 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/24 15:48:42 by nrabarij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hck.h"

void	hck_print_map(t_map *tmp);

void	hck_clear_point(t_map *p)
{
	if (!p)
		return ;
	hck_clear_point(p->nxt);
	free(p);
	p = NULL;
}

t_map	*hck_create_point(int x_pos, int y_pos)
{
	t_map	*map = NULL;

	map = (t_map *)malloc(sizeof(t_map));
	if (map)
	{
		map->nb[0] = NULL;
		map->nb[1] = NULL;
		map->nb[2] = NULL;
		map->nb[3] = NULL;
		map->nb[4] = NULL;
		map->nb[5] = NULL;
		map->nb[6] = NULL;
		map->nb[7] = NULL;
		map->pion = NULL;
		map->position.x = x_pos;
		map->position.y = y_pos;
		map->nxt = NULL;
		map->prv = NULL;
	}
	return (map);
}

void	hck_point_add_back(t_map **bgn, t_map *new)
{
	if (!new)
		return ;
	if (!(*bgn))
	{
		(*bgn) = new;
		(*bgn)->prv = (*bgn);
		(*bgn)->nxt = NULL;
		return ;
	}
	(*bgn)->prv->nxt = new;
	(*bgn)->prv->nxt->prv = (*bgn)->prv;
	(*bgn)->prv->nxt->nxt = NULL;
	(*bgn)->prv = (*bgn)->prv->nxt;
}

t_map	*hck_create_map(int width, int height)
{
	t_map	*new;
	t_map	*nxt;

	new = NULL;
	nxt = NULL;
	int	i = 0;
	while (i < height)
	{
		int	j = 0;
		while (j < width)
		{
			new = hck_create_point(j, i);
			if (!new)
				hck_clear_point(nxt);
			hck_point_add_back(&nxt, new);
			j++;
		}
		i++;
	}
	return (nxt);
}

/*void	fdf_link(t_fdf *d, t_point *p)
{
	t_point	*tmp;

	if (!p)
		return ;
	fdf_origin(d, p);
	while (p)
	{
		tmp = p->nxt;
		if (!(p->rgt) && tmp && tmp->x > p->x && tmp->y == p->y)
			p->rgt = tmp;
		while (tmp && tmp->x != p->x)
			tmp = tmp->nxt;
		if (!(p->dwn) && tmp && tmp->x == p->x && tmp->y > p->y)
			p->dwn = tmp;
		p = p->nxt;
	}
}*/

void	hck_link_diag_map(t_map **bgn)
{
	t_map	*tmp1;

	if (!bgn || !(*bgn))
		return ;
}

void	hck_link_square_map(t_map **bgn)
{
	t_map	*tmp1;
	t_map	*tmp2;

	if (!bgn || !(*bgn))
		return ;
	tmp1 = (*bgn);
	while (tmp1)
	{
		if (tmp1->nxt)
		{
			tmp2 = tmp1->nxt;
			if (tmp1->nxt->position.x == tmp1->position.x + 1 && tmp1->nxt->position.y == tmp1->position.y && tmp1->nb[2] == NULL)
			{
				tmp1->nb[2] = tmp1->nxt;
				tmp1->nxt->nb[6] = tmp1;
			}
			while (tmp2 && tmp2->position.x != tmp1->position.x)
				tmp2 = tmp2->nxt;
			if (tmp2)
			{
				tmp1->nb[4] = tmp2;
				tmp2->nb[0] = tmp1;
			}
		}
		tmp1 = tmp1->nxt;
	}
}

int	main(void)
{
	t_map	*map;
	int	i, j;

	i = 5;
	j = 9;
	map = hck_create_map(j, i);
	if (!map)
		exit(1);
	hck_link_square_map(&map);
	hck_print_map(map);
	hck_clear_point(map);
}

















































void	hck_print_map(t_map *tmp)
{
	while (tmp)
	{
		printf("Cur: [%p]\t[%3d] [%3d]\tTop: [%p]\t Rgt: [%p]\tDwn: [%p]\tLft: [%p]\n", tmp, tmp->position.x, tmp->position.y, tmp->nb[0], tmp->nb[2], tmp->nb[4], tmp->nb[6]);
		tmp = tmp->nxt;
	}
}
