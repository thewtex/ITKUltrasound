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
#ifndef __itkVnlFFT1DRealToComplexConjugateImageFilter_hxx
#define __itkVnlFFT1DRealToComplexConjugateImageFilter_hxx

#include "itkVnlFFT1DRealToComplexConjugateImageFilter.h"

#include "itkFFT1DRealToComplexConjugateImageFilter.hxx"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkIndent.h"
#include "itkMetaDataObject.h"
#include "itkExceptionObject.h"
#include "itkVnlFFTCommon.h"
#include "vnl/algo/vnl_fft_base.h"
#include "vnl/algo/vnl_fft_1d.h"

namespace itk
{

template< typename TPixel, unsigned int VDimension>
void
VnlFFT1DRealToComplexConjugateImageFilter<TPixel,VDimension>
::ThreadedGenerateData( const OutputImageRegionType& outputRegion, ThreadIdType itkNotUsed( threadID ) )
{
  // get pointers to the input and output
  typename Superclass::InputImageType::ConstPointer  inputPtr  = this->GetInput();
  typename Superclass::OutputImageType::Pointer      outputPtr = this->GetOutput();

  if ( !inputPtr || !outputPtr )
    {
    return;
    }

  const typename Superclass::InputImageType::SizeType&   inputSize
    = inputPtr->GetRequestedRegion().GetSize();

  unsigned int vecSize = inputSize[this->m_Direction];
  if( ! VnlFFTCommon::IsDimensionSizeLegal(vecSize) )
    {
    ExceptionObject exception(__FILE__, __LINE__);
    exception.SetDescription("Illegal Array DIM for FFT");
    exception.SetLocation(ITK_LOCATION);
    throw exception;
    }


  typedef itk::ImageLinearConstIteratorWithIndex< InputImageType >  InputIteratorType;
  typedef itk::ImageLinearIteratorWithIndex< OutputImageType >      OutputIteratorType;
  InputIteratorType inputIt( inputPtr, outputRegion );
  OutputIteratorType outputIt( outputPtr, outputRegion );

  inputIt.SetDirection(this->m_Direction);
  outputIt.SetDirection(this->m_Direction);

  vnl_vector< vcl_complex<TPixel> > inputBuffer( vecSize );
  typename vnl_vector< vcl_complex< TPixel > >::iterator inputBufferIt = inputBuffer.begin();
    // fft is done in-place
  typename vnl_vector< vcl_complex< TPixel > >::iterator outputBufferIt = inputBuffer.begin();
  vnl_fft_1d<TPixel> v1d(vecSize);

  // for every fft line
  for( inputIt.GoToBegin(), outputIt.GoToBegin(); !inputIt.IsAtEnd();
    outputIt.NextLine(), inputIt.NextLine() )
    {
    // copy the input line into our buffer
    inputIt.GoToBeginOfLine();
    inputBufferIt = inputBuffer.begin();
    while( !inputIt.IsAtEndOfLine() )
      {
      *inputBufferIt = inputIt.Get();
      ++inputIt;
      ++inputBufferIt;
      }

    // do the transform
    v1d.bwd_transform(inputBuffer);

    // copy the output from the buffer into our line
    outputBufferIt = inputBuffer.begin();
    outputIt.GoToBeginOfLine();
    while( !outputIt.IsAtEndOfLine() )
      {
      outputIt.Set( *outputBufferIt );
      ++outputIt;
      ++outputBufferIt;
      }
    }
}

} // end namespace itk

#endif
