#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <fstream>
#include <iostream>
#include <cstdint>

class LogFileHandler : public osg::NotifyHandler
{
public:
    LogFileHandler(const std::string& file)
    {
        m_fileStream.open(file.c_str());
    }

    virtual ~LogFileHandler()
    {
        m_fileStream.close();
    }

    virtual void notify(osg::NotifySeverity severity, const char* message) override
    {
        m_fileStream << message;
    }

private:
    std::ofstream m_fileStream;
};

int32_t main(int32_t argc, char** argv)
{
    osg::setNotifyLevel(osg::INFO);
    osg::setNotifyHandler(new LogFileHandler("log.txt"));

    osg::ArgumentParser argumentParser(&argc, argv);
    
    osg::ref_ptr<osg::Node> root = osgDB::readNodeFiles(argumentParser);

    if (!root)
    {
        osg::notify(osg::FATAL) << argumentParser.getApplicationName() << ": No data loaded." << std::endl;

        return -1;
    }

    osgViewer::Viewer viewer;

    viewer.setSceneData(root.get());

    return viewer.run();
}