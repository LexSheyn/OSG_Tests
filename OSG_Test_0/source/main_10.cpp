// Let's work on a common shape in order to see the steps to complete a renderable geometry
// model. We will create a quadrangle with only four vertices as the four corners, and use
// GL_QUADS mode to draw these vertices. The GL)DUADS mode tells OpenGL to combine
// the first four coordinates in the vertex array as one quad, the second four as the second
// quad, and so on.

#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

int32_t main(int32_t argc, char** argv)
{
    // Create the vertex array and push the four corner points to the back of the array
    // by using std::vector like operations.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    // We have to indicate the normal of each vertex; otherwise OpenGL will use default
    // (0, 0, 1) normal vector and the lighting equation calculation may be incorrect. The
    // four vertices actually face the same direction, so a single normal vector is enough.
    // We will also set the setNormalBinding() method to BIND_OVERALL later.

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();

    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    // We will indicate a unique color value to each vertex and make them colored. By
    // default, OpenGL will use shooth coloring and blend colors at each vertex together.

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array();

    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Next, we create the osg::Geometry object and set the prepared vertex, normal,
    // and color arrays to it. We also indicate thath the single normal should be bound
    // to the entire geometry and that the colors should be bound per vertex.

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry();

    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setColorArray(colors.get());

    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    // The last step required to fonosh a geometry and add it to the scene graph
    // is to specify the primitive set. A newly allocated osg::DrawArrays
    // instance with the drawing mode set to GL_QUADS is used here, in order to
    // render the four vertices as quad corners in a counter-clockwise order.

    osg::DrawArrays* drawArraysCommand = new osg::DrawArrays(GL_QUADS, 0, 4);

    quad->addPrimitiveSet(drawArraysCommand);

    // Add the geometry to an osg::Geode object and render it in the scene viewer.

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(quad.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}