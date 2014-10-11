# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####

# <pep8 compliant>
import bpy
from bpy.types import Panel, Menu, UIList
from bpy.app.translations import pgettext_iface as iface_


class FLUID_MT_presets(Menu):
    bl_label = "Fluid Presets"
    preset_subdir = "fluid"
    preset_operator = "script.execute_preset"
    draw = Menu.draw_preset

class FRACTURE_MT_presets(Menu):
    bl_label = "Fracture Presets"
    preset_subdir = "fracture"
    preset_operator = "script.execute_preset"
    draw = Menu.draw_preset


class PhysicButtonsPanel():
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = "physics"

    @classmethod
    def poll(cls, context):
        ob = context.object
        rd = context.scene.render
        return (ob and (ob.type == 'MESH' or ob.type == 'CURVE' or ob.type == 'SURFACE' or ob.type == 'FONT')) and (not rd.use_game_engine) and (context.fracture)

class FRACTURE_UL_fracture_levels(UIList):
    def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
        fl = item
        if self.layout_type in {'DEFAULT', 'COMPACT'}:
            layout.prop(fl, "name", text="", emboss=False, icon_value=icon)
        elif self.layout_type in {'GRID'}:
            layout.alignment = 'CENTER'
            layout.label(text="", icon_value=icon)

class PHYSICS_PT_fracture(PhysicButtonsPanel, Panel):
    bl_label = "Fracture"

    def icon(self, bool):
        if bool:
            return 'TRIA_DOWN'
        else:
            return 'TRIA_RIGHT'

    def draw(self, context):
        layout = self.layout

        md = context.fracture

        layout.label(text="Presets:")
        sub = layout.row(align=True)
        sub.menu("FRACTURE_MT_presets", text=bpy.types.FRACTURE_MT_presets.bl_label)
        sub.operator("fracture.preset_add", text="", icon='ZOOMIN')
        sub.operator("fracture.preset_add", text="", icon='ZOOMOUT').remove_active = True

        layout.prop(md, "frac_algorithm")
        col = layout.column(align=True)
        col.prop(md, "shard_count")
        col.prop(md, "cluster_count")
        col.prop(md, "point_seed")
        if md.frac_algorithm == 'BOOLEAN' or md.frac_algorithm == 'BISECT_FILL' or md.frac_algorithm == 'BISECT_FAST_FILL':
            layout.prop(md, "inner_material")
        row = layout.row()
        row.prop(md, "shards_to_islands")
        row.prop(md, "auto_execute")
        layout.operator("object.fracture_refresh", text="Execute Fracture")

class PHYSICS_PT_fracture_simulation(PhysicButtonsPanel, Panel):
    bl_label = "Fracture Simulation"

    def icon(self, bool):
        if bool:
            return 'TRIA_DOWN'
        else:
            return 'TRIA_RIGHT'

    def draw(self, context):
        layout = self.layout
        md = context.fracture
        ob = context.object

        #layout.operator("object.rigidbody_constraints_refresh", text="Refresh Constraints Only")
        layout.label("Constraint Building Settings")
        layout.prop(md, "use_constraints")
        col = layout.column(align=True)
        col.prop(md, "constraint_limit", text="Constraint limit, per MeshIsland")
        col.prop(md, "contact_dist")
        layout.label("Constraint Breaking Settings")
        col = layout.column(align=True)
        col.prop(md, "breaking_threshold", text="Threshold")
        col.prop(md, "cluster_breaking_threshold")

        #experimental stuff
        box = layout.box()
        box.prop(md, "use_experimental", text="Experimental, use with caution !", icon=self.icon(md.use_experimental), emboss = False)
        if md.use_experimental:
            box.label("Fracture Point Source:")
            box.prop(md, "point_source")
            box.prop(md, "extra_group")
            box.prop(md, "dm_group")
            box.prop(md, "use_particle_birth_coordinates")

            box.prop(md, "percentage")
            box.label("Constraint Breaking Settings")
            col = box.column(align=True)
            row = col.row()
            row.prop(md, "breaking_percentage", text="Percentage")
            row.prop(md, "breaking_percentage_weighted")

            row = col.row()
            row.prop(md, "breaking_angle", text="Angle")
            row.prop(md, "breaking_angle_weighted")

            row = col.row()
            row.prop(md, "breaking_distance", text="Distance")
            row.prop(md, "breaking_distance_weighted")

            box.prop(md, "solver_iterations_override")
            box.prop(md, "use_mass_dependent_thresholds")
            box.label("Threshold Vertex Group:")
            box.prop_search(md, "thresh_vertex_group", ob, "vertex_groups", text = "")
            box.label("Passive Vertex Group:")
            box.prop_search(md, "ground_vertex_group", ob, "vertex_groups", text = "")
            box.label("Inner Vertex Group:")
            box.prop_search(md, "inner_vertex_group", ob, "vertex_groups", text = "")
            box.prop(md, "autohide_dist")

            box.prop(md, "fix_normals");
            if not(md.refresh):
                box.prop(md, "execute_threaded")
            box.operator("object.rigidbody_convert_to_objects", text = "Convert To Objects")

if __name__ == "__main__":  # only for live edit.
    bpy.utils.register_module(__name__)