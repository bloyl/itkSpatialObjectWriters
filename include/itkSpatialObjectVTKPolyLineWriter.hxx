
#ifndef __itkSpatialObjectVTKPolyLineWriter_hxx
#define __itkSpatialObjectVTKPolyLineWriter_hxx

#include "itkSpatialObjectVTKPolyLineWriter.h"
#include <itkLineSpatialObject.h>


#include <vtkTransformPolyDataFilter.h>
#include <vtkTransform.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkPolyData.h>
#include <vtkPolyLine.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkCellArray.h>

namespace itk
{
template< unsigned int NDimensions >
SpatialObjectVTKPolyLineWriter< NDimensions >
::SpatialObjectVTKPolyLineWriter()
{
  m_FileName = "";
  m_SpatialObject = 0;
}

template< unsigned int NDimensions >
SpatialObjectVTKPolyLineWriter< NDimensions >
::~SpatialObjectVTKPolyLineWriter()
{}

template< unsigned int NDimensions >
void
SpatialObjectVTKPolyLineWriter< NDimensions >
::Update()
{
  if ( m_SpatialObject.IsNotNull() )
  {
    typedef vtkSmartPointer<vtkPoints>      VtkPointsPointer;

    //Suported
    typedef LineSpatialObject<NDimensions>  LineType;
    typedef typename LineType::Pointer      LinePointer;


    // Create a polydata to store everything in
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

    VtkPointsPointer outPoints = VtkPointsPointer::New();
    vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();

    //Add each of the children to polyData!
    typename SpatialObjectType::ChildrenListType * childrenList = m_SpatialObject->GetChildren();
    typename SpatialObjectType::ChildrenListType::const_iterator it = childrenList->begin();
    while(it != childrenList->end())
    {
      std::string objectTypeName = (*it)->GetNameOfClass();
      if ( objectTypeName == "LineSpatialObject")
      {
        LinePointer line = dynamic_cast<LineType *>( (*it).GetPointer() );
        // float fiberId = static_cast<float>( line->GetId() );

        unsigned int numPts = line->GetNumberOfPoints();
        vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
        polyLine->GetPointIds()->SetNumberOfIds(numPts);

        for (unsigned int i = 0; i < numPts; ++i)
        {
          double pt[3];
          typename LineType::PointType lpsPnt = line->GetPoint(i)->GetPosition();
          pt[0] = lpsPnt[0];
          pt[1] = lpsPnt[1];
          pt[2] = lpsPnt[2];
          vtkIdType ptId = outPoints->InsertNextPoint( pt );
          // fiberIdLabel->InsertNextValue(fiberId);
          polyLine->GetPointIds()->SetId(i,ptId);
        }
        cells->InsertNextCell(polyLine);
      }
      else
      {
        itkExceptionMacro(<< " Unsupported itk SpatialObject encountered : " << (*it)->GetNameOfClass())
      }
      it++;
    }
    delete childrenList;

    polyData->SetPoints(outPoints);
    polyData->SetLines(cells);

    //Write out the polydata
    vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    #if VTK_MAJOR_VERSION <= 5
      transformFilter->SetInput(polyData);
    #else
      transformFilter->SetInputData(polyData);
    #endif
    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    
    //TODO THIS should come from m_SpatialObject world transform!!
    vtkSmartPointer<vtkMatrix4x4> mat = vtkSmartPointer<vtkMatrix4x4>::New();
    mat->Identity();
    transform->SetMatrix(mat);
    transformFilter->SetTransform(transform);
    
    transformFilter->Update();

    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();

    writer->SetFileName(m_FileName.c_str());
    #if VTK_MAJOR_VERSION <= 5
      writer->SetInput(transformFilter->GetOutput());
    #else
      writer->SetInputData(transformFilter->GetOutput());
    #endif
    writer->Write();

    m_SpatialObject = NULL;
  }
}

} // namespace itk

#endif
