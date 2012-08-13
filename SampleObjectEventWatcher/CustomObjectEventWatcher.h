/////////////////////////////////////////////////////////////////////////////
// CustomObjectEventWatcher.h
//

#include "StdAfx.h"

/*
The CRhinoEventWatcher class has virtual functions that you can override in a subclass
to be notified when events occur in Rhino.

NOTE: the class is named an event WATCHER for a reason; it should only watch and never change
the objects that are in the rhino database. This will mess up things like the undo stack.
*/
class CCustomObjectEventWatcher : public CRhinoEventWatcher
{
public:
  CCustomObjectEventWatcher() {}
  ~CCustomObjectEventWatcher() {}
 
  // override virtual function when add object
  void OnAddObject(
		CRhinoDoc& doc,
		CRhinoObject& object
		);

  // override virtual function when delete object
  void OnDeleteObject(
		CRhinoDoc& doc,
		CRhinoObject& object
		);

  // override virtual function when replace object
  void OnReplaceObject(
		CRhinoDoc& doc,
		CRhinoObject& old_object,
		CRhinoObject& new_object
		);

  // override virtual function when undelete object
  void OnUnDeleteObject(
		CRhinoDoc& doc,
		CRhinoObject& object
		);
};