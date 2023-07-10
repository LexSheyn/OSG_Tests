#include <osg/Geode>
#include <osg/Group>
#include <osg/ref_ptr>

#include <iostream>
#include <cstdint>

osg::ref_ptr<osg::Group> create_group()
{
    osg::ref_ptr<osg::Group> group = new osg::Group();

    // Return the new Group's address. This stores the group
    // address in a ref_ptr<...> and places the ref_ptr<...>
    // on the call stack as the return value.

    return group;
}

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Group> group_node = new osg::Group();

    {
        // Create a new osg::Geode object. The assignment to the
        // ref_ptr<...> increments the reference count to 1.

        osg::ref_ptr<osg::Geode> geometry_node = new osg::Geode();

        // Assume 'group_node' is a pointer to an osg::Group node. Group
        // uses a ref_ptr<...> to point to its children, so addChild()
        // again increments the reference count ot 2.

        const bool b_add_result = group_node->addChild(geometry_node.get());
    }

    // The 'geometry_node' ref_ptr<...> variable goes out of scope here.
    // This decrements the reference count back to 1.

    return 0;
}