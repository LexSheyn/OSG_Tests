#include <osg/Geometry>
#include <osg/Geode>
#include <osgUtil/SmoothingVisitor>
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

    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 18);

    (*indices)[0]  = 0;
    (*indices)[1]  = 1;
    (*indices)[2]  = 2;
    (*indices)[3]  = 0;
    (*indices)[4]  = 2;
    (*indices)[5]  = 3;
    (*indices)[6]  = 0;
    (*indices)[7]  = 3;
    (*indices)[8]  = 4;
    (*indices)[9]  = 0;
    (*indices)[10] = 4;
    (*indices)[11] = 1;
    (*indices)[12] = 1;
    (*indices)[13] = 2;
    (*indices)[14] = 4;
    (*indices)[15] = 4;
    (*indices)[16] = 2;
    (*indices)[17] = 3;

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    geometry->setVertexArray(vertices.get());
    geometry->addPrimitiveSet(indices.get());

    osgUtil::SmoothingVisitor::smooth(*geometry);

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(geometry.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}