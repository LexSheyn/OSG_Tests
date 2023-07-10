#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osg/Notify>

#include <iostream>
#include <cstdint>

osg::ref_ptr<osg::Node> create_scene_graph()
{
    // Create an object ot store geometry in.

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    // Create an array of four vertices.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    geometry->setVertexArray(vertices.get());

    vertices->push_back(osg::Vec3(-1.0f, 0.0f, -1.0f));
    vertices->push_back(osg::Vec3( 1.0f, 0.0f, -1.0f));
    vertices->push_back(osg::Vec3( 1.0f, 0.0f,  1.0f));
    vertices->push_back(osg::Vec3(-1.0f, 0.0f,  1.0f));

    // Create an array of four colors.

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();

    geometry->setColorArray(colors.get());
    geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Create an array for the single normal.

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();

    geometry->setNormalArray(normals.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    // Draw a four-vertex quad from the stored data.

    osg::DrawArrays* draw_arrays = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4);

    geometry->addPrimitiveSet(draw_arrays);

    // Add the Geometry (Drawable) to a Geode and
    // return the Geode.

    osg::ref_ptr<osg::Geode> geometry_node = new osg::Geode();

    geometry_node->addDrawable(geometry.get());

    return geometry_node.get();
}

// Open Scene Graph
// 
// Coordinate System
//
//              ^ z
//              |
//              |
//              |
//              |
//              |----------> x
//             /
//            /
//           /
//         |/_ y

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> root = create_scene_graph();

    if (!root.valid())
    {
        osg::notify(osg::FATAL) << "Failed to create scene graph!" << std::endl;
    }

    bool b_write_result = osgDB::writeNodeFile(*(root.get()), "simple.osg");

    if (!b_write_result)
    {
        osg::notify(osg::FATAL) << "Failed to write node file!" << std::endl;
    }

    return 0;
}