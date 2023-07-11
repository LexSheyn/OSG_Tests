// The osg::TriangleFunctor<> functor class is ideal for collecting information on triangle
// faces. It will convert primitive sets of an osg::Drawable object to triangles whenever
// posiible. The template argument must implement an operator() with three const
// osg::Vec3& parameters and bool parameter, which will be called for every triangle when
// the functor is applied.

// We will implement the template argument as a structure including an operator().
// The first three 3D vector parameters represent the triangle vertices, and the last
// one indicates whether these vertices come from a temporary vertex array or not.

#include <osg/TriangleFunctor>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

struct OutputTriangleFunctor
{
    // Triangle:
    void operator()(const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3)
    {
        std::cout << "Triangle: [" << v1.x() << " " << v1.y() << " " << v1.z() << "]"
                            << "[" << v2.x() << " " << v2.y() << " " << v2.z() << "]"
                            << "[" << v3.x() << " " << v3.y() << " " << v3.z() << "]\n";
    }
};

int32_t main(int32_t argc, char** argv)
{
    // We will create a wall-like object by using GL_QUAD_STRIP, which means that the
    // geometry was not originally formed by triangles. This object includes eight vertices
    // and four quad faces.

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();

    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.5f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(2.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(3.0f, 0.0f, 1.5f));
    vertices->push_back(osg::Vec3(4.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(4.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array();

    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    osg::TriangleFunctor<OutputTriangleFunctor> outputTriangleFunctor;

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();

    geometry->setVertexArray(vertices.get());
    geometry->setNormalArray(normals.get());
    geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geometry->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP, 0, 10));
    geometry->accept(outputTriangleFunctor);

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(geometry.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}