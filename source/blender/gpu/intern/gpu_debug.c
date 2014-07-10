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
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Brecht Van Lommel.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/gpu/intern/gpu_debug.c
 *  \ingroup gpu
 */

#ifdef DEBUG

#if WITH_GL_PROFILE_COMPAT
#define GPU_MANGLE_DEPRECATED 0 /* Allow use of deprecated OpenGL functions in this file */
#endif

#include "GPU_draw.h"

#include <stdio.h>
#include <string.h>

/* debugging aid */
static void gpu_state_print_fl_ex(const char *name, GLenum type)
{
	const unsigned char err_mark[4] = {0xff, 0xff, 0xff, 0xff};

	float value[32];
	int a;

	memset(value, 0xff, sizeof(value));
	glGetFloatv(type, value);

	printf("%s: ", name);
	for (a = 0; a < 32; a++) {
		if (memcmp(&value[a], err_mark, sizeof(value[a])) == 0) {
			break;
		}
		printf("%.2f ", value[a]);
	}
	printf("\n");
}

#define gpu_state_print_fl(val) gpu_state_print_fl_ex(#val, val)

void GPU_state_print(void)
{
	gpu_state_print_fl(GL_ACCUM_ALPHA_BITS);
	gpu_state_print_fl(GL_ACCUM_BLUE_BITS);
	gpu_state_print_fl(GL_ACCUM_CLEAR_VALUE);
	gpu_state_print_fl(GL_ACCUM_GREEN_BITS);
	gpu_state_print_fl(GL_ACCUM_RED_BITS);
	gpu_state_print_fl(GL_ACTIVE_TEXTURE);
	gpu_state_print_fl(GL_ALIASED_LINE_WIDTH_RANGE);
	gpu_state_print_fl(GL_ALIASED_POINT_SIZE_RANGE);
	gpu_state_print_fl(GL_ALPHA_BIAS);
	gpu_state_print_fl(GL_ALPHA_BITS);
	gpu_state_print_fl(GL_ALPHA_SCALE);
	gpu_state_print_fl(GL_ALPHA_TEST);
	gpu_state_print_fl(GL_ALPHA_TEST_FUNC);
	gpu_state_print_fl(GL_ALPHA_TEST_REF);
	gpu_state_print_fl(GL_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_ATTRIB_STACK_DEPTH);
	gpu_state_print_fl(GL_AUTO_NORMAL);
	gpu_state_print_fl(GL_AUX_BUFFERS);
	gpu_state_print_fl(GL_BLEND);
	gpu_state_print_fl(GL_BLEND_COLOR);
	gpu_state_print_fl(GL_BLEND_DST_ALPHA);
	gpu_state_print_fl(GL_BLEND_DST_RGB);
	gpu_state_print_fl(GL_BLEND_EQUATION_ALPHA);
	gpu_state_print_fl(GL_BLEND_EQUATION_RGB);
	gpu_state_print_fl(GL_BLEND_SRC_ALPHA);
	gpu_state_print_fl(GL_BLEND_SRC_RGB);
	gpu_state_print_fl(GL_BLUE_BIAS);
	gpu_state_print_fl(GL_BLUE_BITS);
	gpu_state_print_fl(GL_BLUE_SCALE);
	gpu_state_print_fl(GL_CLIENT_ACTIVE_TEXTURE);
	gpu_state_print_fl(GL_CLIENT_ATTRIB_STACK_DEPTH);
	gpu_state_print_fl(GL_CLIP_PLANE0);
	gpu_state_print_fl(GL_COLOR_ARRAY);
	gpu_state_print_fl(GL_COLOR_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_COLOR_ARRAY_SIZE);
	gpu_state_print_fl(GL_COLOR_ARRAY_STRIDE);
	gpu_state_print_fl(GL_COLOR_ARRAY_TYPE);
	gpu_state_print_fl(GL_COLOR_CLEAR_VALUE);
	gpu_state_print_fl(GL_COLOR_LOGIC_OP);
	gpu_state_print_fl(GL_COLOR_MATERIAL);
	gpu_state_print_fl(GL_COLOR_MATERIAL_FACE);
	gpu_state_print_fl(GL_COLOR_MATERIAL_PARAMETER);
	gpu_state_print_fl(GL_COLOR_MATRIX);
	gpu_state_print_fl(GL_COLOR_MATRIX_STACK_DEPTH);
	gpu_state_print_fl(GL_COLOR_SUM);
	gpu_state_print_fl(GL_COLOR_TABLE);
	gpu_state_print_fl(GL_COLOR_WRITEMASK);
	gpu_state_print_fl(GL_COMPRESSED_TEXTURE_FORMATS);
	gpu_state_print_fl(GL_CONVOLUTION_1D);
	gpu_state_print_fl(GL_CONVOLUTION_2D);
	gpu_state_print_fl(GL_CULL_FACE);
	gpu_state_print_fl(GL_CULL_FACE_MODE);
	gpu_state_print_fl(GL_CURRENT_COLOR);
	gpu_state_print_fl(GL_CURRENT_FOG_COORD);
	gpu_state_print_fl(GL_CURRENT_INDEX);
	gpu_state_print_fl(GL_CURRENT_NORMAL);
	gpu_state_print_fl(GL_CURRENT_PROGRAM);
	gpu_state_print_fl(GL_CURRENT_RASTER_COLOR);
	gpu_state_print_fl(GL_CURRENT_RASTER_DISTANCE);
	gpu_state_print_fl(GL_CURRENT_RASTER_INDEX);
	gpu_state_print_fl(GL_CURRENT_RASTER_POSITION);
	gpu_state_print_fl(GL_CURRENT_RASTER_POSITION_VALID);
	gpu_state_print_fl(GL_CURRENT_RASTER_SECONDARY_COLOR);
	gpu_state_print_fl(GL_CURRENT_RASTER_TEXTURE_COORDS);
	gpu_state_print_fl(GL_CURRENT_SECONDARY_COLOR);
	gpu_state_print_fl(GL_CURRENT_TEXTURE_COORDS);
	gpu_state_print_fl(GL_DEPTH_BIAS);
	gpu_state_print_fl(GL_DEPTH_BITS);
	gpu_state_print_fl(GL_DEPTH_CLEAR_VALUE);
	gpu_state_print_fl(GL_DEPTH_FUNC);
	gpu_state_print_fl(GL_DEPTH_RANGE);
	gpu_state_print_fl(GL_DEPTH_SCALE);
	gpu_state_print_fl(GL_DEPTH_TEST);
	gpu_state_print_fl(GL_DEPTH_WRITEMASK);
	gpu_state_print_fl(GL_DITHER);
	gpu_state_print_fl(GL_DOUBLEBUFFER);
	gpu_state_print_fl(GL_DRAW_BUFFER);
	gpu_state_print_fl(GL_DRAW_BUFFER0);
	gpu_state_print_fl(GL_EDGE_FLAG);
	gpu_state_print_fl(GL_EDGE_FLAG_ARRAY);
	gpu_state_print_fl(GL_EDGE_FLAG_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_EDGE_FLAG_ARRAY_STRIDE);
	gpu_state_print_fl(GL_ELEMENT_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_FEEDBACK_BUFFER_SIZE);
	gpu_state_print_fl(GL_FEEDBACK_BUFFER_TYPE);
	gpu_state_print_fl(GL_FOG);
	gpu_state_print_fl(GL_FOG_COLOR);
	gpu_state_print_fl(GL_FOG_COORD_ARRAY);
	gpu_state_print_fl(GL_FOG_COORD_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_FOG_COORD_ARRAY_STRIDE);
	gpu_state_print_fl(GL_FOG_COORD_ARRAY_TYPE);
	gpu_state_print_fl(GL_FOG_COORD_SRC);
	gpu_state_print_fl(GL_FOG_DENSITY);
	gpu_state_print_fl(GL_FOG_END);
	gpu_state_print_fl(GL_FOG_HINT);
	gpu_state_print_fl(GL_FOG_INDEX);
	gpu_state_print_fl(GL_FOG_MODE);
	gpu_state_print_fl(GL_FOG_START);
	gpu_state_print_fl(GL_FRAGMENT_PROGRAM_ARB);
	gpu_state_print_fl(GL_FRAGMENT_SHADER_DERIVATIVE_HINT);
	gpu_state_print_fl(GL_FRONT_FACE);
	gpu_state_print_fl(GL_GENERATE_MIPMAP_HINT);
	gpu_state_print_fl(GL_GREEN_BIAS);
	gpu_state_print_fl(GL_GREEN_BITS);
	gpu_state_print_fl(GL_GREEN_SCALE);
	gpu_state_print_fl(GL_HISTOGRAM);
	gpu_state_print_fl(GL_INDEX_ARRAY);
	gpu_state_print_fl(GL_INDEX_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_INDEX_ARRAY_STRIDE);
	gpu_state_print_fl(GL_INDEX_ARRAY_TYPE);
	gpu_state_print_fl(GL_INDEX_BITS);
	gpu_state_print_fl(GL_INDEX_CLEAR_VALUE);
	gpu_state_print_fl(GL_INDEX_LOGIC_OP);
	gpu_state_print_fl(GL_INDEX_MODE);
	gpu_state_print_fl(GL_INDEX_OFFSET);
	gpu_state_print_fl(GL_INDEX_SHIFT);
	gpu_state_print_fl(GL_INDEX_WRITEMASK);
	gpu_state_print_fl(GL_LIGHT0);
	gpu_state_print_fl(GL_LIGHT1);
	gpu_state_print_fl(GL_LIGHT2);
	gpu_state_print_fl(GL_LIGHT3);
	gpu_state_print_fl(GL_LIGHT4);
	gpu_state_print_fl(GL_LIGHT5);
	gpu_state_print_fl(GL_LIGHT6);
	gpu_state_print_fl(GL_LIGHT7);
	gpu_state_print_fl(GL_LIGHTING);
	gpu_state_print_fl(GL_LIGHT_MODEL_AMBIENT);
	gpu_state_print_fl(GL_LIGHT_MODEL_COLOR_CONTROL);
	gpu_state_print_fl(GL_LIGHT_MODEL_LOCAL_VIEWER);
	gpu_state_print_fl(GL_LIGHT_MODEL_TWO_SIDE);
	gpu_state_print_fl(GL_LINE_SMOOTH);
	gpu_state_print_fl(GL_LINE_SMOOTH_HINT);
	gpu_state_print_fl(GL_LINE_STIPPLE);
	gpu_state_print_fl(GL_LINE_STIPPLE_PATTERN);
	gpu_state_print_fl(GL_LINE_STIPPLE_REPEAT);
	gpu_state_print_fl(GL_LINE_WIDTH);
	gpu_state_print_fl(GL_LINE_WIDTH_GRANULARITY);
	gpu_state_print_fl(GL_LINE_WIDTH_RANGE);
	gpu_state_print_fl(GL_LIST_BASE);
	gpu_state_print_fl(GL_LIST_INDEX);
	gpu_state_print_fl(GL_LIST_MODE);
	gpu_state_print_fl(GL_LOGIC_OP);
	gpu_state_print_fl(GL_LOGIC_OP_MODE);
	gpu_state_print_fl(GL_MAP1_COLOR_4);
	gpu_state_print_fl(GL_MAP1_GRID_DOMAIN);
	gpu_state_print_fl(GL_MAP1_GRID_SEGMENTS);
	gpu_state_print_fl(GL_MAP1_INDEX);
	gpu_state_print_fl(GL_MAP1_NORMAL);
	gpu_state_print_fl(GL_MAP1_TEXTURE_COORD_1);
	gpu_state_print_fl(GL_MAP1_TEXTURE_COORD_2);
	gpu_state_print_fl(GL_MAP1_TEXTURE_COORD_3);
	gpu_state_print_fl(GL_MAP1_TEXTURE_COORD_4);
	gpu_state_print_fl(GL_MAP1_VERTEX_3);
	gpu_state_print_fl(GL_MAP1_VERTEX_4);
	gpu_state_print_fl(GL_MAP2_COLOR_4);
	gpu_state_print_fl(GL_MAP2_GRID_DOMAIN);
	gpu_state_print_fl(GL_MAP2_GRID_SEGMENTS);
	gpu_state_print_fl(GL_MAP2_INDEX);
	gpu_state_print_fl(GL_MAP2_NORMAL);
	gpu_state_print_fl(GL_MAP2_TEXTURE_COORD_1);
	gpu_state_print_fl(GL_MAP2_TEXTURE_COORD_2);
	gpu_state_print_fl(GL_MAP2_TEXTURE_COORD_3);
	gpu_state_print_fl(GL_MAP2_TEXTURE_COORD_4);
	gpu_state_print_fl(GL_MAP2_VERTEX_3);
	gpu_state_print_fl(GL_MAP2_VERTEX_4);
	gpu_state_print_fl(GL_MAP_COLOR);
	gpu_state_print_fl(GL_MAP_STENCIL);
	gpu_state_print_fl(GL_MATRIX_MODE);
	gpu_state_print_fl(GL_MAX_3D_TEXTURE_SIZE);
	gpu_state_print_fl(GL_MAX_ATTRIB_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_CLIP_PLANES);
	gpu_state_print_fl(GL_MAX_COLOR_MATRIX_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	gpu_state_print_fl(GL_MAX_CUBE_MAP_TEXTURE_SIZE);
	gpu_state_print_fl(GL_MAX_DRAW_BUFFERS);
	gpu_state_print_fl(GL_MAX_ELEMENTS_INDICES);
	gpu_state_print_fl(GL_MAX_ELEMENTS_VERTICES);
	gpu_state_print_fl(GL_MAX_EVAL_ORDER);
	gpu_state_print_fl(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS);
	gpu_state_print_fl(GL_MAX_LIGHTS);
	gpu_state_print_fl(GL_MAX_LIST_NESTING);
	gpu_state_print_fl(GL_MAX_MODELVIEW_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_NAME_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_PIXEL_MAP_TABLE);
	gpu_state_print_fl(GL_MAX_PROJECTION_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_TEXTURE_COORDS);
	gpu_state_print_fl(GL_MAX_TEXTURE_IMAGE_UNITS);
	gpu_state_print_fl(GL_MAX_TEXTURE_LOD_BIAS);
	gpu_state_print_fl(GL_MAX_TEXTURE_SIZE);
	gpu_state_print_fl(GL_MAX_TEXTURE_STACK_DEPTH);
	gpu_state_print_fl(GL_MAX_TEXTURE_UNITS);
	gpu_state_print_fl(GL_MAX_VARYING_FLOATS);
	gpu_state_print_fl(GL_MAX_VERTEX_ATTRIBS);
	gpu_state_print_fl(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	gpu_state_print_fl(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
	gpu_state_print_fl(GL_MAX_VIEWPORT_DIMS);
	gpu_state_print_fl(GL_MINMAX);
	gpu_state_print_fl(GL_MODELVIEW_MATRIX);
	gpu_state_print_fl(GL_MODELVIEW_STACK_DEPTH);
	gpu_state_print_fl(GL_MULTISAMPLE);
	gpu_state_print_fl(GL_MULTISAMPLE_ARB);
	gpu_state_print_fl(GL_NAME_STACK_DEPTH);
	gpu_state_print_fl(GL_NORMALIZE);
	gpu_state_print_fl(GL_NORMAL_ARRAY);
	gpu_state_print_fl(GL_NORMAL_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_NORMAL_ARRAY_STRIDE);
	gpu_state_print_fl(GL_NORMAL_ARRAY_TYPE);
	gpu_state_print_fl(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
	gpu_state_print_fl(GL_PACK_ALIGNMENT);
	gpu_state_print_fl(GL_PACK_IMAGE_HEIGHT);
	gpu_state_print_fl(GL_PACK_LSB_FIRST);
	gpu_state_print_fl(GL_PACK_ROW_LENGTH);
	gpu_state_print_fl(GL_PACK_SKIP_IMAGES);
	gpu_state_print_fl(GL_PACK_SKIP_PIXELS);
	gpu_state_print_fl(GL_PACK_SKIP_ROWS);
	gpu_state_print_fl(GL_PACK_SWAP_BYTES);
	gpu_state_print_fl(GL_PERSPECTIVE_CORRECTION_HINT);
	gpu_state_print_fl(GL_PIXEL_MAP_A_TO_A_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_B_TO_B_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_G_TO_G_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_I_TO_A_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_I_TO_B_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_I_TO_G_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_I_TO_I_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_I_TO_R_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_R_TO_R_SIZE);
	gpu_state_print_fl(GL_PIXEL_MAP_S_TO_S_SIZE);
	gpu_state_print_fl(GL_PIXEL_PACK_BUFFER_BINDING);
	gpu_state_print_fl(GL_PIXEL_UNPACK_BUFFER_BINDING);
	gpu_state_print_fl(GL_POINT_DISTANCE_ATTENUATION);
	gpu_state_print_fl(GL_POINT_FADE_THRESHOLD_SIZE);
	gpu_state_print_fl(GL_POINT_SIZE);
	gpu_state_print_fl(GL_POINT_SIZE_GRANULARITY);
	gpu_state_print_fl(GL_POINT_SIZE_MAX);
	gpu_state_print_fl(GL_POINT_SIZE_MIN);
	gpu_state_print_fl(GL_POINT_SIZE_RANGE);
	gpu_state_print_fl(GL_POINT_SMOOTH);
	gpu_state_print_fl(GL_POINT_SMOOTH_HINT);
	gpu_state_print_fl(GL_POINT_SPRITE);
	gpu_state_print_fl(GL_POLYGON_MODE);
	gpu_state_print_fl(GL_POLYGON_OFFSET_FACTOR);
	gpu_state_print_fl(GL_POLYGON_OFFSET_FILL);
	gpu_state_print_fl(GL_POLYGON_OFFSET_LINE);
	gpu_state_print_fl(GL_POLYGON_OFFSET_POINT);
	gpu_state_print_fl(GL_POLYGON_OFFSET_UNITS);
	gpu_state_print_fl(GL_POLYGON_SMOOTH);
	gpu_state_print_fl(GL_POLYGON_SMOOTH_HINT);
	gpu_state_print_fl(GL_POLYGON_STIPPLE);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_ALPHA_BIAS);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_ALPHA_SCALE);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_BLUE_BIAS);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_BLUE_SCALE);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_COLOR_TABLE);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_GREEN_BIAS);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_GREEN_SCALE);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_RED_BIAS);
	gpu_state_print_fl(GL_POST_COLOR_MATRIX_RED_SCALE);
	gpu_state_print_fl(GL_POST_CONVOLUTION_ALPHA_BIAS);
	gpu_state_print_fl(GL_POST_CONVOLUTION_ALPHA_SCALE);
	gpu_state_print_fl(GL_POST_CONVOLUTION_BLUE_BIAS);
	gpu_state_print_fl(GL_POST_CONVOLUTION_BLUE_SCALE);
	gpu_state_print_fl(GL_POST_CONVOLUTION_COLOR_TABLE);
	gpu_state_print_fl(GL_POST_CONVOLUTION_GREEN_BIAS);
	gpu_state_print_fl(GL_POST_CONVOLUTION_GREEN_SCALE);
	gpu_state_print_fl(GL_POST_CONVOLUTION_RED_BIAS);
	gpu_state_print_fl(GL_POST_CONVOLUTION_RED_SCALE);
	gpu_state_print_fl(GL_PROJECTION_MATRIX);
	gpu_state_print_fl(GL_PROJECTION_STACK_DEPTH);
	gpu_state_print_fl(GL_READ_BUFFER);
	gpu_state_print_fl(GL_RED_BIAS);
	gpu_state_print_fl(GL_RED_BITS);
	gpu_state_print_fl(GL_RED_SCALE);
	gpu_state_print_fl(GL_RENDER_MODE);
	gpu_state_print_fl(GL_RESCALE_NORMAL);
	gpu_state_print_fl(GL_RGBA_MODE);
	gpu_state_print_fl(GL_SAMPLES);
	gpu_state_print_fl(GL_SAMPLE_BUFFERS);
	gpu_state_print_fl(GL_SAMPLE_COVERAGE_INVERT);
	gpu_state_print_fl(GL_SAMPLE_COVERAGE_VALUE);
	gpu_state_print_fl(GL_SCISSOR_BOX);
	gpu_state_print_fl(GL_SCISSOR_TEST);
	gpu_state_print_fl(GL_SECONDARY_COLOR_ARRAY);
	gpu_state_print_fl(GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_SECONDARY_COLOR_ARRAY_SIZE);
	gpu_state_print_fl(GL_SECONDARY_COLOR_ARRAY_STRIDE);
	gpu_state_print_fl(GL_SECONDARY_COLOR_ARRAY_TYPE);
	gpu_state_print_fl(GL_SELECTION_BUFFER_SIZE);
	gpu_state_print_fl(GL_SEPARABLE_2D);
	gpu_state_print_fl(GL_SHADE_MODEL);
	gpu_state_print_fl(GL_SMOOTH_LINE_WIDTH_GRANULARITY);
	gpu_state_print_fl(GL_SMOOTH_LINE_WIDTH_RANGE);
	gpu_state_print_fl(GL_SMOOTH_POINT_SIZE_GRANULARITY);
	gpu_state_print_fl(GL_SMOOTH_POINT_SIZE_RANGE);
	gpu_state_print_fl(GL_STENCIL_BACK_FAIL);
	gpu_state_print_fl(GL_STENCIL_BACK_FUNC);
	gpu_state_print_fl(GL_STENCIL_BACK_PASS_DEPTH_FAIL);
	gpu_state_print_fl(GL_STENCIL_BACK_PASS_DEPTH_PASS);
	gpu_state_print_fl(GL_STENCIL_BACK_REF);
	gpu_state_print_fl(GL_STENCIL_BACK_VALUE_MASK);
	gpu_state_print_fl(GL_STENCIL_BACK_WRITEMASK);
	gpu_state_print_fl(GL_STENCIL_BITS);
	gpu_state_print_fl(GL_STENCIL_CLEAR_VALUE);
	gpu_state_print_fl(GL_STENCIL_FAIL);
	gpu_state_print_fl(GL_STENCIL_FUNC);
	gpu_state_print_fl(GL_STENCIL_PASS_DEPTH_FAIL);
	gpu_state_print_fl(GL_STENCIL_PASS_DEPTH_PASS);
	gpu_state_print_fl(GL_STENCIL_REF);
	gpu_state_print_fl(GL_STENCIL_TEST);
	gpu_state_print_fl(GL_STENCIL_VALUE_MASK);
	gpu_state_print_fl(GL_STENCIL_WRITEMASK);
	gpu_state_print_fl(GL_STEREO);
	gpu_state_print_fl(GL_SUBPIXEL_BITS);
	gpu_state_print_fl(GL_TEXTURE_1D);
	gpu_state_print_fl(GL_TEXTURE_2D);
	gpu_state_print_fl(GL_TEXTURE_3D);
	gpu_state_print_fl(GL_TEXTURE_BINDING_1D);
	gpu_state_print_fl(GL_TEXTURE_BINDING_2D);
	gpu_state_print_fl(GL_TEXTURE_BINDING_3D);
	gpu_state_print_fl(GL_TEXTURE_BINDING_CUBE_MAP);
	gpu_state_print_fl(GL_TEXTURE_COMPRESSION_HINT);
	gpu_state_print_fl(GL_TEXTURE_COORD_ARRAY);
	gpu_state_print_fl(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_TEXTURE_COORD_ARRAY_SIZE);
	gpu_state_print_fl(GL_TEXTURE_COORD_ARRAY_STRIDE);
	gpu_state_print_fl(GL_TEXTURE_COORD_ARRAY_TYPE);
	gpu_state_print_fl(GL_TEXTURE_CUBE_MAP);
	gpu_state_print_fl(GL_TEXTURE_CUBE_MAP_ARB);
	gpu_state_print_fl(GL_TEXTURE_GEN_Q);
	gpu_state_print_fl(GL_TEXTURE_GEN_R);
	gpu_state_print_fl(GL_TEXTURE_GEN_S);
	gpu_state_print_fl(GL_TEXTURE_GEN_T);
	gpu_state_print_fl(GL_TEXTURE_MATRIX);
	gpu_state_print_fl(GL_TEXTURE_STACK_DEPTH);
	gpu_state_print_fl(GL_TRANSPOSE_COLOR_MATRIX);
	gpu_state_print_fl(GL_TRANSPOSE_MODELVIEW_MATRIX);
	gpu_state_print_fl(GL_TRANSPOSE_PROJECTION_MATRIX);
	gpu_state_print_fl(GL_TRANSPOSE_TEXTURE_MATRIX);
	gpu_state_print_fl(GL_UNPACK_ALIGNMENT);
	gpu_state_print_fl(GL_UNPACK_IMAGE_HEIGHT);
	gpu_state_print_fl(GL_UNPACK_LSB_FIRST);
	gpu_state_print_fl(GL_UNPACK_ROW_LENGTH);
	gpu_state_print_fl(GL_UNPACK_SKIP_IMAGES);
	gpu_state_print_fl(GL_UNPACK_SKIP_PIXELS);
	gpu_state_print_fl(GL_UNPACK_SKIP_ROWS);
	gpu_state_print_fl(GL_UNPACK_SWAP_BYTES);
	gpu_state_print_fl(GL_VERTEX_ARRAY);
	gpu_state_print_fl(GL_VERTEX_ARRAY_BUFFER_BINDING);
	gpu_state_print_fl(GL_VERTEX_ARRAY_SIZE);
	gpu_state_print_fl(GL_VERTEX_ARRAY_STRIDE);
	gpu_state_print_fl(GL_VERTEX_ARRAY_TYPE);
	gpu_state_print_fl(GL_VERTEX_PROGRAM_POINT_SIZE);
	gpu_state_print_fl(GL_VERTEX_PROGRAM_TWO_SIDE);
	gpu_state_print_fl(GL_VIEWPORT);
	gpu_state_print_fl(GL_ZOOM_X);
	gpu_state_print_fl(GL_ZOOM_Y);
}

#undef gpu_state_print_fl

#endif