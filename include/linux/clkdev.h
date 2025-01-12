/*
 *  include/linux/clkdev.h
 *
 *  Copyright (C) 2008 Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Helper for the clk API to assist looking up a struct clk.
 */
#ifndef __CLKDEV_H
#define __CLKDEV_H

#include <linux/slab.h>

struct clk;
struct clk_hw;
struct device;

struct clk_lookup {
	struct list_head	node;
	const char		*dev_id;
	const char		*con_id;
	int                     of_idx;
	struct clk		*clk;
	struct clk_hw		*clk_hw;
};

#define CLKDEV_INIT(d, n, c)	\
	{			\
		.dev_id = d,	\
		.con_id = n,	\
		.clk = c,	\
	}

struct clk_lookup *clkdev_alloc(struct clk *clk, const char *con_id,
	const char *dev_fmt, ...) __printf(3, 4);
struct clk_lookup *clkdev_hw_alloc(struct clk_hw *hw, const char *con_id,
	const char *dev_fmt, ...) __printf(3, 4);

void clkdev_add(struct clk_lookup *cl);
void clkdev_drop(struct clk_lookup *cl);

struct clk_lookup *clkdev_create(struct clk *clk, const char *con_id,
	const char *dev_fmt, ...) __printf(3, 4);
struct clk_lookup *clkdev_hw_create(struct clk_hw *hw, const char *con_id,
	const char *dev_fmt, ...) __printf(3, 4);

void clkdev_add_table(struct clk_lookup *, size_t);
int clk_add_alias(const char *, const char *, const char *, struct device *);

int clk_register_clkdev(struct clk *, const char *, const char *);
int clk_hw_register_clkdev(struct clk_hw *, const char *, const char *);

#endif
