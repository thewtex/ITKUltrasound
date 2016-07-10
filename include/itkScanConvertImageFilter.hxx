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
#ifndef itkScanConvertImageFilter_hxx
#define itkScanConvertImageFilter_hxx

#include "itkScanConvertImageFilter.h"

namespace itk
{

template < typename TInputImage, typename TOutputImage >
ScanConvertImageFilter< TInputImage, TOutputImage >
::ScanConvertImageFilter(): m_Method( ITK_NEAREST_NEIGHBOR )
{
}


template < typename TInputImage, typename TOutputImage >
void
ScanConvertImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf( os, indent );

  os << indent << "Method: " << this->m_Method << std::endl;
}


template < typename TInputImage, typename TOutputImage >
void
ScanConvertImageFilter< TInputImage, TOutputImage >
::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // get pointers to the inputs
  InputImageType * input = const_cast<InputImageType *>( this->GetInput() );
  input->SetRequestedRegionToLargestPossibleRegion();
}


template < typename TInputImage, typename TOutputImage >
void
ScanConvertImageFilter< TInputImage, TOutputImage >
::EnlargeOutputRequestedRegion( DataObject * output )
{
  Superclass::EnlargeOutputRequestedRegion( output );
  output->SetRequestedRegionToLargestPossibleRegion();
}


template < typename TInputImage, typename TOutputImage >
void
ScanConvertImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  this->AllocateOutputs();

  const InputImageType * inputPtr = this->GetInput();
  OutputImageType * outputPtr = this->GetOutput();

  //m_LogFilter->GraftOutput( outputPtr );
  //m_LogFilter->Update();
  //this->GraftOutput( m_LogFilter->GetOutput() );
}

} // end namespace itk

#endif
