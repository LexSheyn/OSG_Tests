#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osgViewer/Viewer>

#include <iostream>
#include <cstdint>

int32_t main(int32_t argc, char** argv)
{
    // Add thee osg::ShapeDrawable objects successively, each with a type if basic
    // shape. We set these shapes to different positions to make them visible to viewers
    // at the same time, and for the reason of distinguishing them from each other, we
    // color the shapes red, green and blue respectively by using the setColor()
    // method of osg::ShapeDrawable.
    
    osg::ref_ptr<osg::ShapeDrawable> shape_box = new osg::ShapeDrawable();

    shape_box->setShape(new osg::Box(osg::Vec3(-3.0f, 0.0f, 0.0f), 2.0f, 2.0f, 1.0f));
    shape_box->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape_cone = new osg::ShapeDrawable();

    shape_cone->setShape(new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f));
    shape_cone->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape_sphere = new osg::ShapeDrawable();

    shape_sphere->setShape(new osg::Sphere(osg::Vec3(3.0f, 0.0f, 0.0f), 1.0f));
    shape_sphere->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));

    osg::ref_ptr<osg::Geode> root = new osg::Geode();

    root->addDrawable(shape_box.get());
    root->addDrawable(shape_cone.get());
    root->addDrawable(shape_sphere.get());

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}