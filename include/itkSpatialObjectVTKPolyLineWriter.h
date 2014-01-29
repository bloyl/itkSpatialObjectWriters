#ifndef __itkSpatialObjectVTKPolyLineWriter_h
#define __itkSpatialObjectVTKPolyLineWriter_h

#include "itkSpatialObject.h"
#include "itkObject.h"


namespace itk
{
template< unsigned int NDimensions = 3
          >
class SpatialObjectVTKPolyLineWriter:public Object
{
public:

  /** SmartPointer typedef support */
  typedef SpatialObjectVTKPolyLineWriter  Self;
  typedef SmartPointer< Self > Pointer;

  typedef SpatialObject< NDimensions >              SpatialObjectType;
  typedef typename SpatialObjectType::ConstPointer  SpatialObjectConstPointer;

  /** Method for creation through the object factory */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  typedef Object Superclass;
  itkTypeMacro(SpatialObjectVTKPolyLineWriter, Object);

  /** Load a tube file. */
  void Update(void);

  /** Set the filename  */
  itkSetStringMacro(FileName);

  /** Get the filename */
  itkGetStringMacro(FileName);

  /** Set the Input  */
  void SetInput(const SpatialObjectType *input){ m_SpatialObject = input; }

protected:
  SpatialObjectVTKPolyLineWriter(const Self &); //purposely not implemented
  void operator=(const Self &);      //purposely not implemented

  SpatialObjectVTKPolyLineWriter();
  virtual ~SpatialObjectVTKPolyLineWriter();

private:

  std::string                           m_FileName;
  SpatialObjectConstPointer             m_SpatialObject;

};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkSpatialObjectVTKPolyLineWriter.hxx"
#endif

#endif // __itkSpatialObjectVTKPolyLineWriter_h
