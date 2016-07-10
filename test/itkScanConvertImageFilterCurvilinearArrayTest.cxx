/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkUltrasoundImageFileReader.h"
#include "itkCurvilinearArraySpecialCoordinatesImage.h"
#include "itkScanConvertImageFilter.h"

#include "itkTestingMacros.h"
#include "itkImageFileWriter.h"

int itkScanConvertImageFilterCurvilinearArrayTest( int argc, char* argv[] )
{
  if( argc < 3 )
    {
    std::cerr << "Usage: " << argv[0] << "inputImage outputImage" << std::endl;
    return EXIT_FAILURE;
    }
  const char * inputImageFileName = argv[1];
  const char * outputImageFileName = argv[2];

  const unsigned int Dimension = 3;
  typedef unsigned char                                                        PixelType;
  typedef itk::CurvilinearArraySpecialCoordinatesImage< PixelType, Dimension > InputImageType;

  typedef itk::Image< PixelType, Dimension >                                   OutputImageType;

  typedef itk::UltrasoundImageFileReader< InputImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( inputImageFileName );


  typedef itk::ImageFileWriter< OutputImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputImageFileName );
  //writer->SetInput( scanConverter->GetOutput() );
  writer->SetUseCompression( true );

  try
    {
    //writer->Update();
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error while resampling data: " << error << std::endl;
    return EXIT_FAILURE;
    }
  //std::cout << scanConverter << std::endl;

  return EXIT_SUCCESS;
}
