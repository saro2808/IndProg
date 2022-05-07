'''
This script is to be run in blender python shell to export the data of tree leaves
'''

objs = C.scene.objects
tree_leaves = [x for x in objs if x.name[:27] == 'Stages_CyTree10_Leaf_Lod0.0']
tree_leaves_data = [(x.name, x.location, x.rotation_euler, x.scale) for x in tree_leaves]
for x in tree_leaves_data:
    print(x[0], (x[1][0], x[1][1], x[1][2]), (x[2][0], x[2][1], x[2][2]), (x[3][0], x[3][1], x[3][2]))