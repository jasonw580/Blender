/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2014 Blender Foundation.
 * All rights reserved.
 *
 * Contributor(s): Blender Foundation,
 *                 Lukas Toenne
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/blenkernel/intern/hair.c
 *  \ingroup bke
 */

#include "MEM_guardedalloc.h"

#include "DNA_hair_types.h"

#include "BKE_hair.h"

struct HairSystem *BKE_hairsys_new(void)
{
	HairSystem *hsys = MEM_callocN(sizeof(HairSystem), "hair system");
	return hsys;
}

void BKE_hairsys_free(struct HairSystem *hsys)
{
	if (hsys->curves)
		MEM_freeN(hsys->curves);
	if (hsys->points)
		MEM_freeN(hsys->points);
	MEM_freeN(hsys);
}

struct HairSystem *BKE_hairsys_copy(struct HairSystem *hsys)
{
	HairSystem *thsys = MEM_dupallocN(hsys);
	thsys->points = MEM_dupallocN(hsys->points);
	thsys->curves = MEM_dupallocN(hsys->curves);
	
	return thsys;
}

void BKE_hair_calc_curve_offsets(HairSystem *hsys)
{
	HairCurve *hair;
	int a;
	int offset = 0;
	
	for (a = 0, hair = hsys->curves; a < hsys->totcurves; ++a, ++hair) {
		hair->offset = offset;
		offset += hair->numpoints;
	}
}