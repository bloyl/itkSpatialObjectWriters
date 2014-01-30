#include <itkSpatialObjectVTKPolyLineWriter.h>

#include <itkTestingMacros.h>

//
#include <itkGroupSpatialObject.h>
#include <itkLineSpatialObject.h>
#include <itkBoxSpatialObject.h>


using namespace itk;
int itkSpatialObjectVTKPolyLineWriterTest( int , char * argv[] )
{

  typedef SpatialObjectVTKPolyLineWriter<3>        SpatialObjectWriterType;
  SpatialObjectWriterType::Pointer writer = SpatialObjectWriterType::New();
  EXERCISE_BASIC_OBJECT_METHODS(writer, SpatialObjectWriterType);

  std::string outputFile = argv[1];
  writer->SetFileName(outputFile);

//  TEST_SET_GET_VALUE(outputFile,write->GetFileName());

  typedef GroupSpatialObject<3>   GroupSpatialObject;
  GroupSpatialObject::Pointer groupObject = GroupSpatialObject::New();

  //make and add a line object...
  typedef itk::LineSpatialObject<3>      LineType;
  typedef LineType::Pointer              LinePointer;
  typedef LineType::LinePointType        LinePointType;
  typedef itk::CovariantVector<double,3> VectorType;

  LineType::PointListType list;
  unsigned int i;
  for(i=0; i<10; i++)
  {
    LinePointType p;
    p.SetPosition(i,i+1,i+2);
    VectorType normal1;
    VectorType normal2;
    for(unsigned int j=0;j<3;j++)
    {
      normal1[j]=j;
      normal2[j]=j*2;
    }

    p.SetNormal(normal1,0);
    p.SetNormal(normal2,1);
    list.push_back(p);
  }

  // For coverage
  LinePointType p;
  p.SetPosition(0,1,2);

  // Create a Line Spatial Object
  LinePointer Line = LineType::New();
  Line->GetProperty()->SetName("Line 1");
  Line->SetId(1);
  Line->SetPoints(list);
  Line->ComputeBoundingBox();
  groupObject->AddSpatialObject(Line);

  //add a box...

  typedef itk::BoxSpatialObject< 3 >         BoxType;

  BoxType::Pointer box1 =     BoxType::New();
  box1->SetId(1);

  // Test the SetProperty()
  typedef BoxType::PropertyType PropertyType;
  PropertyType::Pointer prop = PropertyType::New();
  box1->SetProperty(prop);

  BoxType::SizeType  boxsize1;

  boxsize1[0] = 30;
  boxsize1[1] = 30;
  boxsize1[3] = 30;
  box1->SetSize( boxsize1 );

  BoxType::TransformType::OffsetType offset1;

  offset1[0] =  29.0;
  offset1[1] =  29.0;
  offset1[2] =  29.0;
  box1->GetObjectToParentTransform()->SetOffset( offset1 );
  box1->ComputeObjectToWorldTransform();

// Uncomment this line to test with a box spaitial object...
//  groupObject->AddSpatialObject(box1);

  writer->SetInput(groupObject);

  writer->Update();
  return EXIT_SUCCESS;
}
