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
#ifndef itkScanConvertImageFilter_h
#define itkScanConvertImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk
{

/**
 * \class ScanConvertImageFilter
 *
 * \brief Scan convert an ultrasound SpecialCoordinatesImage
 *
 * \ingroup Ultrasound
 *
 * \sa ResampleImageFilter
 * \sa SpecialCoordinatesImage
 *
 */
template < typename TInputImage, typename TOutputImage >
class ScanConvertImageFilter:
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs.   */
  typedef ScanConvertImageFilter                          Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self >                      ConstPointer;

  /** The type of input image.   */
  typedef TInputImage InputImageType;

  /** Dimension of the input and output images. */
  itkStaticConstMacro (ImageDimension, unsigned int, TInputImage::ImageDimension);

  /** The type of output image.   */
  typedef TOutputImage OutputImageType;

  /** Run-time type information (and related methods) */
  itkTypeMacro( ScanConvertImageFilter, ImageToImageFilter );

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  enum ResamplingMethod {
    ITK_NEAREST_NEIGHBOR = 0,
    ITK_LINEAR,
    ITK_WINDOWED_SINC
  };

  /** Set/Get the ScanConversionResamplingMethod. */
  itkSetMacro( Method, ResamplingMethod );
  itkGetConstMacro( Method, ResamplingMethod );

protected:
  ScanConvertImageFilter();
  ~ScanConvertImageFilter() {}

  virtual void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;

  virtual void GenerateData() ITK_OVERRIDE;

  // These behave like their analogs in Forward1DFFTImageFilter.
  virtual void GenerateInputRequestedRegion() ITK_OVERRIDE;
  virtual void EnlargeOutputRequestedRegion(DataObject *output) ITK_OVERRIDE;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(ScanConvertImageFilter);

  ResamplingMethod m_Method;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkScanConvertImageFilter.hxx"
#endif

#endif // itkScanConvertImageFilter_h
