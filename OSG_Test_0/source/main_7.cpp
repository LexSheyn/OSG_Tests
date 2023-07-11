#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <cstdint>
#include <iostream>
#include <string>

int32_t main(int32_t argc, char** argv)
{
    osg::ArgumentParser argumentParser(&argc, argv);
    
    std::string filePath;
    float_t size = 1.0f;

    argumentParser.read("--model", filePath);
    argumentParser.read("--size", size);

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile(filePath);

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}