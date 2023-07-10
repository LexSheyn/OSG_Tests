#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osg/Image>
#include <osg/Texture2D>
#include <osgDB/Registry>
#include <osgDB/WriteFile>

#include <cstdint>

osg::ref_ptr<osg::Texture2D> createTexture2D(const char* filePath)
{
    //osg::ref_ptr<osg::Image> image = osgDB::readImageFile(filePath);
}

osg::ref_ptr<osg::Drawable> createDrawable()
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

    // Create an array of texture coordinates for texture unit 0.

    osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array();

    geometry->setTexCoordArray(0, texCoords.get());

    texCoords->push_back(osg::Vec2(0.0f, 0.0f));
    texCoords->push_back(osg::Vec2(1.0f, 0.0f));
    texCoords->push_back(osg::Vec2(1.0f, 1.0f));
    texCoords->push_back(osg::Vec2(0.0f, 1.0f));

    // Draw a four-vertex quad from the stored data.

    osg::DrawArrays* draw_arrays = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4);

    geometry->addPrimitiveSet(draw_arrays);

    // Add the Geometry (Drawable) to a Geode and
    // return the Geode.

    return geometry.get();
}

osg::ref_ptr<osg::Node> createSceneGraph()
{
    // Create the root node Group.

    osg::ref_ptr<osg::Group> root = new osg::Group();

    // Disable lighting in the root node's StateSet. Make
    // it PROTECTED to prevent osgViewer from enabling it.

    osg::StateSet* p_rootStateSet = root->getOrCreateStateSet();

    p_rootStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);

    // Create the leaf node Geode and attach the Drawable.
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    osg::ref_ptr<osg::Drawable> drawable = createDrawable();
    
    geode->addDrawable(drawable.get());

    // Upper left: Render the drawable with default state.
    
    const osg::Matrix matrixUL = osg::Matrix::translate(-2.0f, 0.0f, 2.0f);

    osg::ref_ptr<osg::MatrixTransform> transformUL = new osg::MatrixTransform();

    transformUL->setMatrix(matrixUL);

    root->addChild(transformUL.get());

    transformUL->addChild(geode.get());

    // Upper right: Set shade model to FLAT.

    const osg::Matrix matrixUR = osg::Matrix::translate(2.0f, 0.0f, 2.0f);

    osg::ref_ptr<osg::MatrixTransform> transformUR = new osg::MatrixTransform();

    transformUR->setMatrix(matrixUR);

    root->addChild(transformUR.get());

    transformUR->addChild(geode.get());

    osg::StateSet* p_stateSetUR = transformUR->getOrCreateStateSet();
    osg::ShadeModel* p_shadeModelUR = new osg::ShadeModel();

    p_shadeModelUR->setMode(osg::ShadeModel::FLAT);

    p_stateSetUR->setAttribute(p_shadeModelUR);

    // Lower left: Enable back face culling.

    const osg::Matrix matrixLL = osg::Matrix::translate(-2.0f, 0.0f, -2.0f);

    osg::ref_ptr<osg::MatrixTransform> transformLL = new osg::MatrixTransform();

    transformLL->setMatrix(matrixLL);

    root->addChild(transformLL.get());

    transformLL->addChild(geode.get());

    osg::StateSet* p_stateSetLL = transformLL->getOrCreateStateSet();
    osg::CullFace* p_cullFaceLL = new osg::CullFace(); // Default: BACK.

    p_stateSetLL->setAttributeAndModes(p_cullFaceLL);

    // Lower right: Set polygon mode to LINE in
    // draw3's StateSet.

    const osg::Matrix matrixLR = osg::Matrix::translate(2.0f, 0.0f, -2.0f);

    osg::ref_ptr<osg::MatrixTransform> transformLR = new osg::MatrixTransform();

    transformLR->setMatrix(matrixLR);

    root->addChild(transformLR.get());

    transformLR->addChild(geode.get());

    osg::StateSet* p_stateSetLR = transformLR->getOrCreateStateSet();
    osg::PolygonMode* p_polygonModeLR = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

    p_stateSetLR->setAttributeAndModes(p_polygonModeLR);

    // Also set the line width to 3.

    osg::LineWidth* p_lineWidthLR = new osg::LineWidth(3.0f);

    p_stateSetLR->setAttribute(p_lineWidthLR);

    return root.get();
}

int32_t main(int32_t argc, char** argv)
{
    osg::ref_ptr<osg::Node> root = createSceneGraph();

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