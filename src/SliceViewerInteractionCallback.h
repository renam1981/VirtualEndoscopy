/*
**    CPE Lyon
**    2018 Camille FARINEAU / Nicolas Ranc
**    Projet Majeur - Virtual Endoscopy
**
**    SliceViewerInteractionCallback.h
**    Callback Interactor Mouse style : Display text on image viewer - Allow interaction between mouse and image viewers
**
**    This code comes from this source code: https://www.vtk.org/Wiki/VTK/Examples/Cxx/Images/PickPixel2
*/

#ifndef SliceViewerInteractionCallback_H
#define SliceViewerInteractionCallback_H

#include <vtkAssemblyPath.h>
#include <vtkCornerAnnotation.h>
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractionStyleObjectFactory.h>
#include <vtkInteractorStyle.h>
#include <vtkMath.h>
#include "vtkImageActor.h"
#include "vtkVariant.h"
#include "vtkImageData.h"
#include <vtkRenderWindow.h>
#include "vtkResliceImageViewer.h"

using namespace std;

// Template for image value reading
template<typename T>
void vtkValueMessageTemplate(vtkImageData* image, int* position,
                             std::string& message)
{
  T* tuple = ((T*)image->GetScalarPointer(position));
  int components = image->GetNumberOfScalarComponents();
  for (int c = 0; c < components; ++c)
    {
    message += vtkVariant(tuple[c]).ToString();
    if (c != (components - 1))
      {
      message += ", ";
      }
    }
  message += " )";
}


/**
 * @brief The SliceViewerInteractionCallback class: Class used to return mouse coordinates from 2D to 3D world
 */
class SliceViewerInteractionCallback : public vtkCommand
{
public:

    /**
     * @brief Dynamic allocation of SliceViewerInteractionCallback
     * @return an instance of SliceViewerInteractionCallback
     */
    static SliceViewerInteractionCallback *New()
    {
        return new SliceViewerInteractionCallback;
    }

   /**
   * @brief Constructor
   */
  SliceViewerInteractionCallback();

  /**
   * @brief Destructor
   */
  ~SliceViewerInteractionCallback();

  /**
   * @brief SetPicker : Set the correct picker (to know where the user clicked)
   * @param picker
   */
  void SetPicker(vtkPropPicker *picker);

  /**
   * @brief SetAnnotation : Set the correct annotation (text displayed on the vtkResliceImageViewer)
   * @param annotation
   */
  void SetAnnotation(vtkCornerAnnotation *annotation);

  /**
   * @brief SetViewer : Set the correct viewer resliced
   * @param viewer
   */
  void SetViewer(vtkResliceImageViewer *viewer);

  /**
   * @brief Execute : Similar to the callback function
   * @param vtkObject * : Current object
   * @param event : Id of the event
   */
  virtual void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *);

private:
  /**
   * @brief Viewer: the ResliceImageViewer associated with this InteractorStyle
   */
  vtkResliceImageViewer*      Viewer;

  /**
   * @brief Picker: the Picker associated with this InteractorStyle
   */
  vtkPropPicker*        Picker;

  /**
   * @brief Annotation: the Corner Annotation associated with this InteractorStyle
   */
  vtkCornerAnnotation*  Annotation;
};


#endif // SliceViewerInteractionCallback_H
