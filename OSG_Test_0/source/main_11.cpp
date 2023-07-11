#include <osg/Geometry>
#include <osg/Geode>
#include <osgUtil/SmoothingVisitor>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

int32_t main(int32_t argc, char** argv)
{
    // As we have duscussed before, the osg::Vec3Array class inherits
    // the characteristics of std::vector and can construct using a
    // predetermined size parameter and work with operator[] directly.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(6);

    (*vertices)[0].set( 0.0f,  0.0f,  1.0f);
    (*vertices)[1].set(-0.5f, -0.5f,  0.0f);
    (*vertices)[2].set( 0.5f, -0.5f,  0.0f);
    (*vertices)[3].set( 0.5f,  0.5f,  0.0f);
    (*vertices)[4].set(-0.5f,  0.5f,  0.0f);
    (*vertices)[5].set( 0.0f,  0.0f, -1.0f);

    // The osg::DrawElementsUInt accepts a size parameter besides
    // the drawing mode parameter, too. After that, we will specify the
    // indices of vertices to describe all eight triangle faces.

    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 24);

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
    (*indices)[12] = 5;
    (*indices)[13] = 2;
    (*indices)[14] = 1;    
    (*indices)[15] = 5;
    (*indices)[16] = 3;
    (*indices)[17] = 2;    
    (*indices)[18] = 5;
    (*indices)[19] = 4;
    (*indices)[20] = 3;    
    (*indices)[21] = 5;
    (*indices)[22] = 1;
    (*indices)[23] = 4;

    // In order to create a geometry with a default white color, we will only set
    // the vertex array and the osg::DrawElementsUInt primitive set. The
    // normal arrat is also required but is not easy to compute manually. We will
    // use a smoothed normal calculator to automatically obtain it,

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    geometry->setVertexArray(vertices.get());
    geometry->addPrimitiveSet(indices.get());

    osgUtil::SmoothingVisitor::smooth(*geometry);

    // Add the geometry to an osg::Geode object and make it the scene root.

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(geometry.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}