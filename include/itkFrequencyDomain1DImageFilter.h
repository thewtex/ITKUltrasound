/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#ifndef itkFrequencyDomain1DImageFilter_h
#define itkFrequencyDomain1DImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkFrequencyDomain1DFilterFunction.h"

namespace itk
{
/** \class FrequencyDomain1DImageFilter
 * \brief Filter a frequency domain along a single direction.
 *
 * Apply a 1D filter along a given direction (SetDirection) to an input image.
 * The input image is expected to be an image with 1D frequency aloing a single
 * direction,such as generated by Forwward1DFFTImageFilter.
 *
 * The default filter is an identity function. To implement a particalar filter
 * subclass FrequencyDomain1DFilterFunction and override the
 * FrequencyDomain1DFilterFunction::Evaluate function
 *
 * \ingroup FourierTransform
 * \ingroup Ultrasound
 */
template< typename TInputImage, typename TOutputImage = TInputImage >
class ITK_TEMPLATE_EXPORT FrequencyDomain1DImageFilter:
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(FrequencyDomain1DImageFilter);

  /** Standard class typedefs. */
  typedef TInputImage                                         InputImageType;
  typedef TOutputImage                                        OutputImageType;
  typedef typename OutputImageType::RegionType                OutputImageRegionType;

  itkStaticConstMacro(ImageDimension, unsigned int, InputImageType::ImageDimension);

  typedef FrequencyDomain1DImageFilter                          Self;
  typedef ImageToImageFilter< InputImageType, OutputImageType > Superclass;
  typedef SmartPointer< Self >                                  Pointer;
  typedef SmartPointer< const Self >                            ConstPointer;

  itkTypeMacro( FrequencyDomain1DImageFilter, ImageToImageFilter );
  itkNewMacro( Self );


  itkSetMacro(Direction, unsigned int);
  itkGetMacro(Direction, unsigned int);

  void SetFilterFunction(FrequencyDomain1DFilterFunction *function)
    {
    m_FilterFunction = function;
    };

protected:
  FrequencyDomain1DImageFilter();
  virtual ~FrequencyDomain1DImageFilter() {}

  void PrintSelf(std::ostream& os, Indent indent) const override;

  // These behave like their analogs in Forward1DFFTImageFilter.
  void GenerateInputRequestedRegion() override;
  void EnlargeOutputRequestedRegion(DataObject *output) override;

  void GenerateData() override;

private:
  FrequencyDomain1DFilterFunction::Pointer m_FilterFunction;

  unsigned int m_Direction;

};
}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkFrequencyDomain1DImageFilter.hxx"
#endif

#endif // itkFrequencyDomain1DImageFilter_h
