import hou
import sys
import os

vex_snippet_0 = '''
string file = "op:{SOP_PATH}";

void corner_uv(string geo; int patch; export vector results[])
{{
    vector2 corner_st[];
    push(corner_st,{{0,0}});
    push(corner_st,{{1,0}});
    push(corner_st,{{1,1}});
    push(corner_st,{{0,1}});

    foreach(vector2 st;corner_st)
    {{
        vector uv;
        if (osd_limitsurfacevertex(geo, "uv", patch, st[0], st[1], uv))
        {{
            push(results,uv);
        }}
    }}
}}

int nfaces = osd_facecount(file);
printf("nfaces = %d\\n",nfaces);
int npatches = osd_patchcount(file);
printf("npatches = %d\\n",npatches);
int geohandle = 0;
for (int face_id = 0; face_id < nfaces; face_id++)
{{
    printf("face_id = %d\\n",face_id);
    int patch_count = osd_patchcount(geohandle,face_id);
    printf("patch_count = %d\\n",patch_count);
    if (patch_count > 0) {{
        int firstpatch_id = osd_firstpatch(geohandle,face_id);
        printf("firstpatch_id = %d\\n",firstpatch_id);
    }}
}}
for (int patch = 0; patch < npatches; patch++)
{{
    vector uv;
    float s = 0.0;
    float t = 0.0;
    if (osd_limitsurfacevertex(file, "uv", patch, s, t, uv))
    {{
        printf("uv = %f\\n",uv);
    }}
}}
for (int patch = 0; patch < npatches; patch++)
{{
    vector results[];
    corner_uv(file, patch, results);
    printf("%g\\n",results);
}}
'''

def main(hip_file:str) -> int:
    geo_node = hou.node('/obj').createNode('geo')

    grid_node = geo_node.createNode('grid')
    grid_node.parm("rows").set(3)
    grid_node.parm("cols").set(3)
    box_node = geo_node.createNode('box')
    platonic_node = geo_node.createNode('platonic')
    switch_node = geo_node.createNode('switch')
    switch_node.setFirstInput(grid_node)
    switch_node.setNextInput(box_node)
    switch_node.setNextInput(platonic_node)
    uvunwrap_node = geo_node.createNode('uvunwrap')
    uvunwrap_node.setInput(0, switch_node)

    facet_node = geo_node.createNode('facet')
    facet_node.setInput(0, uvunwrap_node)
    facet_node.parm("prenml").set(True)
    # print(type(facet_node))
    null_node = geo_node.createNode('null')
    null_node.setInput(0, facet_node)
    null_node.setTemplateFlag(True)

    null_node_sop_path = null_node.path()
    # print(f'facet_node_sop_path = {facet_node_sop_path}')
    attribwrangle_node = geo_node.createNode('attribwrangle')
    attribwrangle_node.parm("class").set(0)
    attribwrangle_node.parm("snippet").set(vex_snippet_0.format(SOP_PATH=null_node_sop_path))
    attribwrangle_node.setDisplayFlag(True)
    attribwrangle_node.setRenderFlag(True)


    hou.hipFile.save(hip_file)
    return 0

if __name__ == '__main__':
    if len(sys.argv) == 2:
        sys.exit(main(hip_file=sys.argv[1]))  # next section explains the use of sys.exit
