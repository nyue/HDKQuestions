import hou
import sys
import os

vex_snippet_0 = '''
string file = "op:{SOP_PATH}";

int nfaces = osd_facecount(file);
printf("nfaces = %d\\n",nfaces);
int geohandle = 0;
for (int face_id = 0; face_id < nfaces; face_id++)
{{
    int patch_count = osd_patchcount(geohandle,face_id);
    printf("patch_count = %d\\n",patch_count);    
    int firstpatch_id = osd_firstpatch(geohandle,face_id);
    printf("firstpatch_id = %d\\n",firstpatch_id);    
}}
'''

def main(hip_file:str) -> int:
    geo_node = hou.node('/obj').createNode('geo')
    platonic_node = geo_node.createNode('platonic')
    facet_node = geo_node.createNode('facet')
    facet_node.setInput(0, platonic_node)
    facet_node.parm("prenml").set(True)
    # print(type(facet_node))
    facet_node_sop_path = facet_node.path()
    # print(f'facet_node_sop_path = {facet_node_sop_path}')
    attribwrangle_node = geo_node.createNode('attribwrangle')
    attribwrangle_node.parm("class").set(0)
    attribwrangle_node.parm("snippet").set(vex_snippet_0.format(SOP_PATH=facet_node_sop_path))
    attribwrangle_node.setDisplayFlag(True)
    attribwrangle_node.setRenderFlag(True)

    hou.hipFile.save(hip_file)
    return 0

if __name__ == '__main__':
    sys.exit(main('nicholas.hip'))  # next section explains the use of sys.exit
