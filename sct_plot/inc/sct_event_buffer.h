#ifndef sct_event_buffer_h__
#define sct_event_buffer_h__

#include <vector>
#include <map>
#include "Rtypes.h"
class TArrayD;

class treeCollection;
class treeCollection_ouput;
class root_event{
public:
  root_event(TArrayD  *ID,
    TArrayD *x,
    TArrayD  *y,
    Int_t*                event_nr);
  root_event();
  TArrayD  *m_ID = nullptr;
  TArrayD  *m_x = nullptr;
  TArrayD *m_y = nullptr;
  Int_t*                m_event_nr=nullptr;
};


class sct_event_buffer{
public:
  void set(const char * name, root_event* ev);
  bool get(const char* name, root_event* ev);
  bool IsCollection(const char* name);
  void reset();

  std::map<std::string, root_event> m_events;
};
#endif // sct_event_buffer_h__
