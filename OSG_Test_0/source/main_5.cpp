#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <cstdint>
#include <iostream>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("cessna.osg");

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}