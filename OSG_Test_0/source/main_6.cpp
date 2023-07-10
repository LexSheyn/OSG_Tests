#include <osg/ref_ptr>
#include <osg/Referenced>

#include <cstdint>
#include <iostream>

class Target : public osg::Referenced
{
public:
    Target(int32_t id) : m_id(id)
    {
        std::cout << "Constructed target [ " << m_id << " ]" << std::endl;
    }

protected:
    virtual ~Target()
    {
        std::cout << "Destroyed target [ " << m_id << " ]" << std::endl;
    }

private:
    int32_t m_id;
};

Target* createTarget(int32_t id)
{
    osg::ref_ptr<Target> target = new Target(id);

    return target.release();
}

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<Target> target = new Target(0);

    std::cout << "Reference count: " << target->referenceCount() << std::endl;

    osg::ref_ptr<Target> anotherTarget = target;

    std::cout << "Reference count: " << target->referenceCount() << std::endl;

    for (size_t i = 1; i < 5; ++i)
    {
        osg::ref_ptr<Target> subTarget = createTarget(i);
    }

    return 0;
}