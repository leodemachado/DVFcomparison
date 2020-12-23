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

// In this example we will run 3D rigid registration
// with Both Mattes and Tsallis Metric
//

// Software Guide : BeginCodeSnippet
#include <iostream>
#include <fstream>

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVectorImage.h"

#include "itkImageRegionIterator.h"

#include "math.h"


int main( int argc, char *argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " DVF1   DVF2 "<< std::endl;
    return EXIT_FAILURE;
    }

  const    unsigned int    Dimension = 3;

  typedef  float           PixelType;

  typedef itk::VectorImage< PixelType, Dimension >  DVFImageType;

  typedef itk::ImageFileReader< DVFImageType > DVFImageReaderType;

  DVFImageReaderType::Pointer dvfImageReader1 = DVFImageReaderType::New();
  DVFImageReaderType::Pointer dvfImageReader2 = DVFImageReaderType::New();

  dvfImageReader1->SetFileName( argv[1] );
  dvfImageReader1->Update();
  dvfImageReader2->SetFileName( argv[2] );
  dvfImageReader2->Update();

  using IteratorType = itk::ImageRegionIterator<DVFImageType>;
  IteratorType DVFIter1 (dvfImageReader1->GetOutput(), dvfImageReader1->GetOutput()->GetLargestPossibleRegion());
  IteratorType DVFIter2 (dvfImageReader2->GetOutput(), dvfImageReader2->GetOutput()->GetLargestPossibleRegion());

  DVFIter1.GoToBegin();
  DVFIter2.GoToBegin();

  float totalDisplacement = 0.0;

  long int numOfPixels = 0;

  while(!DVFIter1.IsAtEnd()){

      DVFImageType::PixelType field1 = DVFIter1.Get();
      DVFImageType::PixelType field2 = DVFIter2.Get();
      float displacement_x = field1[0] - field2[0];
      float displacement_y = field1[1] - field2[1];
      float displacement_z = field1[2] - field2[2];

      float pixelDisplacement = sqrt(displacement_x*displacement_x + displacement_y*displacement_y + displacement_z*displacement_z);

      std::cout<<"Pixel Displacement: "<<pixelDisplacement<<std::endl;

      totalDisplacement += pixelDisplacement;

      numOfPixels += 1;

      ++DVFIter1;
      ++DVFIter2;
  }

  std::cout<<"Num of pixels: "<<numOfPixels<<std::endl;

  float averageDisplacement = totalDisplacement/numOfPixels;

  // Printing results:

  //std::cout<<" Average Component Displacements: "<< std::endl;
  //std::cout<<" Average X Component = "<<averageDisp_x<< std::endl;
  //std::cout<<" Average Y Component = "<<averageDisp_y<< std::endl;
  //std::cout<<" Average Z Component = "<<averageDisp_z<< std::endl;
  std::cout<<std::endl;
  std::cout<<" Average displacement = "<<averageDisplacement<< std::endl;
  return EXIT_SUCCESS;
}
