
set(itkSpatialObjectWritersTests
  itkSpatialObjectVTKPolyLineWriterTest.cxx
)

set(LIBS ${ITK_LIBRARIES} ${VTK_LIBRARIES} )
if( "${ITK_VERSION_MAJOR}" LESS 4 )
  list(APPEND LIBS ITKIO ITKCommon)
endif( "${ITK_VERSION_MAJOR}" LESS 4 )

create_test_sourcelist(Tests itkSpatialObjectWritersTestDriver.cxx ${itkSpatialObjectWritersTests} )
add_executable(itkSpatialObjectWritersTestDriver itkSpatialObjectWritersTestDriver.cxx ${Tests} )
target_link_libraries(itkSpatialObjectWritersTestDriver ${LIBS})

add_test(NAME itkSpatialObjectVTKPolyLineWriterTest
  COMMAND itkSpatialObjectWritersTestDriver itkSpatialObjectVTKPolyLineWriterTest "itkSpatialObjectVTKPolyLineWriterTestOutput.vtp" )
