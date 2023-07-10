#include <osg/Geode>
#include <osg/ref_ptr>

#include <iostream>
#include <cstdint>

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Geode> geometry_node = new osg::Geode();

    if (geometry_node.valid())
    {
        std::cout << "geometry node is valid." << std::endl;
    }
    else
    {
        std::cout << "geometry node is invalid!" << std::endl;
    }

    return 0;
}