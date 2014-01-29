#include <itkSpatialObjectVTKPolyLineWriter.h>

#include <itkTestingMacros.h>

//
#include <itkGroupSpatialObject.h>


using namespace itk;
int itkSpatialObjectVTKPolyLineWriterTest( int , char * argv[] )
{

  typedef SpatialObjectVTKPolyLineWriter<3>        SpatialObjectWriterType;
  SpatialObjectWriterType::Pointer writer = SpatialObjectWriterType::New();
  EXERCISE_BASIC_OBJECT_METHODS(writer, SpatialObjectWriterType);

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

  writer->SetInput(groupObject);
  writer->SetFileName(argv[1]);
  writer->Update();
  return EXIT_SUCCESS;
}
