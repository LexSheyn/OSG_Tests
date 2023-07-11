// Complex primitives will not be rendered correctly by the OpenGL API directly. This includes
// concave polygons, self-intersecting polygons, and polygonds with holes. Only after being
// subdivided into convex polygons, these non-convex polygons can be accepted by the OpenGL
// rendering pipeline. The osgUtil::Tesselator class can be used for the tessellation
// work in this case.

#include <osg/Geometry>
#include <osg/Geode>
#include <osgUtil/Tessellator>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

int32_t main(int32_t argc, char** argv)
{
    // We will create a concave polygon by using the osg::Geometry class. A simple
    // polygon is concave if any of its internal edge angles is greater than 180 degrees.
    // Here, the example geometry represents a quad with a cave on the right-hand side.
    // It is drawn as a GL_POLYGON primitive.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 2.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 2.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 3.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 3.0f));

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();

    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    geometry->setVertexArray(vertices.get());
    geometry->setNormalArray(normals.get());

    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    
    osg::DrawArrays* drawArraysCommand = new osg::DrawArrays(GL_POLYGON, 0, 8);

    geometry->addPrimitiveSet(drawArraysCommand);

    // If we immediately add the geometry variable to an osg::Geode object and
    // view it with osgViewer::Viewer, we will get an incorrect result, as shown
    // in the following screenshot.
    // To render the concave polygon correctly, we should use an
    // osgUtil::Tessellator to re-tessellate it.

    osgUtil::Tessellator tessellator;

    tessellator.retessellatePolygons(*geometry);

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(geometry.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}