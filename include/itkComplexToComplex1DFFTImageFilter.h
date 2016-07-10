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
#ifndef itkComplexToComplex1DFFTImageFilter_h
#define itkComplexToComplex1DFFTImageFilter_h

#include <complex>

#include "itkImage.h"
#include "itkImageToImageFilter.h"
#include "itkImageRegionSplitterDirection.h"

namespace itk
{
/** \class ComplexToComplex1DFFTImageFilter
 * \brief Perform the Fast Fourier Transform, complex input to complex output,
 * but only along one dimension.
 *
 * The direction of the transform, 'Forward' or 'Inverse', can be set with
 * SetTransformDirection() and GetTransformDirection().
 *
 * The dimension along which to apply to filter can be specified with
 * SetDirection() and GetDirection().
 *
 * \ingroup FourierTransform
 * \ingroup Ultrasound
 */
template< typename TInputImage, typename TOutputImage=TInputImage >
class ComplexToComplex1DFFTImageFilter:
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef TInputImage                          InputImageType;
  typedef TOutputImage                         OutputImageType;
  typedef typename OutputImageType::RegionType OutputImageRegionType;

  typedef ComplexToComplex1DFFTImageFilter                      Self;
  typedef ImageToImageFilter< InputImageType, OutputImageType > Superclass;
  typedef SmartPointer< Self >                                  Pointer;
  typedef SmartPointer< const Self >                            ConstPointer;

  itkStaticConstMacro(ImageDimension, unsigned int, InputImageType::ImageDimension );

  itkTypeMacro( ComplexToComplex1DFFTImageFilter, ImageToImageFilter );

  /** Customized object creation methods that support configuration-based
    * selection of FFT implementation.
    *
    * Default implementation is VnlFFT1D.
    */
  static Pointer New();

  /** Transform direction. */
  typedef enum { DIRECT = 1, INVERSE } TransformDirectionType;

  /** Set/Get the direction in which the transform will be applied.
   * By selecting DIRECT, this filter will perform a direct (forward) Fourier
   * Transform.
   * By selecting INVERSE, this filter will perform an inverse Fourier
   * Transform. */
  itkSetMacro( TransformDirection, TransformDirectionType );
  itkGetConstMacro( TransformDirection, TransformDirectionType );

  /** Get the direction in which the filter is to be applied. */
  itkGetMacro(Direction, unsigned int);

  /** Set the direction in which the filter is to be applied. */
  itkSetClampMacro(Direction, unsigned int, 0, ImageDimension - 1);

protected:
  ComplexToComplex1DFFTImageFilter();
  virtual ~ComplexToComplex1DFFTImageFilter() {}

  void PrintSelf(std::ostream& os, Indent indent) const ITK_OVERRIDE;

  virtual void GenerateInputRequestedRegion() ITK_OVERRIDE;
  virtual void EnlargeOutputRequestedRegion(DataObject *output) ITK_OVERRIDE;

  virtual void BeforeThreadedGenerateData() ITK_OVERRIDE;

  /** Override to return a splitter that does not split along the direction we
   * are performing the transform. */
  virtual const ImageRegionSplitterBase* GetImageRegionSplitter() const ITK_OVERRIDE;

  /** Direction in which the filter is to be applied
   * this should be in the range [0,ImageDimension-1]. */
  unsigned int m_Direction;

  /** Direction to apply the transform (forward/inverse). */
  TransformDirectionType m_TransformDirection;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(ComplexToComplex1DFFTImageFilter);

  ImageRegionSplitterDirection::Pointer m_ImageRegionSplitter;
};
}

#ifndef ITK_MANUAL_INSTANTIATION
#ifndef itkVnlComplexToComplex1DFFTImageFilter_h
#ifndef itkVnlComplexToComplex1DFFTImageFilter_hxx
#ifndef itkFFTWComplexToComplex1DFFTImageFilter_h
#ifndef itkFFTWComplexToComplex1DFFTImageFilter_hxx
#include "itkComplexToComplex1DFFTImageFilter.hxx"
#endif
#endif
#endif
#endif
#endif

#endif // itkComplexToComplex1DFFTImageFilter_h
