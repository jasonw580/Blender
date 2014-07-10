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
 * The Original Code is: all of this file.
 *
 * Contributor(s): Jason Wilkins
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file glew-mx.c
 *  \ingroup glew-mx
 * GLEW Context Management
 */

#if GLEW_MX
#include "glew-mx.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

GLEWContext* _glewContext = NULL;

void glewSetContext(GLEWContext* ctx)
{
	_glewContext = ctx;
}

GLEWContext* glewCreateContext()
{
	GLEWContext* rv = malloc(sizeof(GLEWContext));

	if (rv != NULL)
		memset(rv, 0, sizeof(GLEWContext));

	return rv;
}

void glewDestroyContext(GLEWContext* ctx)
{
	if (_glewContext == ctx)
		_glewContext = NULL;

	free(ctx);
}
#endif