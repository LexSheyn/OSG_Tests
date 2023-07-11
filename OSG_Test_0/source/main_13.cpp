#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(5);

    (*vertices)[0] = osg::Vec3( 0.0f,  0.0f, 1.0f);
    (*vertices)[1] = osg::Vec3(-1.0f, -1.0f, 0.0f);
    (*vertices)[2] = osg::Vec3( 1.0f, -1.0f, 0.0f);
    (*vertices)[3] = osg::Vec3( 1.0f,  1.0f, 0.0f);
    (*vertices)[4] = osg::Vec3(-1.0f,  1.0f, 0.0f);

    osg::ref_ptr<osg::DrawElementsUInt> indices_top = new osg::DrawElementsUInt(GL_TRIANGLE_FAN, 12);

    (*indices_top)[0]  = 0;
    (*indices_top)[1]  = 1;
    (*indices_top)[2]  = 2;
    (*indices_top)[3]  = 0;
    (*indices_top)[4]  = 2;
    (*indices_top)[5]  = 3;
    (*indices_top)[6]  = 0;
    (*indices_top)[7]  = 3;
    (*indices_top)[8]  = 4;
    (*indices_top)[9]  = 0;
    (*indices_top)[10] = 4;
    (*indices_top)[11] = 1;

    osg::ref_ptr<osg::DrawElementsUInt> indices_bottom = new osg::DrawElementsUInt(GL_QUADS, 4);

    (*indices_bottom)[0] = 1;
    (*indices_bottom)[1] = 2;
    (*indices_bottom)[2] = 3;
    (*indices_bottom)[3] = 4;

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();

    normals->push_back(osg::Vec3(0.0f,  0.0f,  1.0f));
    normals->push_back(osg::Vec3(0.0f, -1.0f,  0.0f));

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    geometry->setVertexArray(vertices.get());
    geometry->addPrimitiveSet(indices_top.get());
    geometry->addPrimitiveSet(indices_bottom.get());
    geometry->setNormalArray(normals.get());
    
    geometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(geometry.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}