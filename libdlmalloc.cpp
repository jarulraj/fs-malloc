/* -*- C++ -*- */

/*

  Heap Layers: An Extensible Memory Allocation Infrastructure
  
  Copyright (C) 2000-2003 by Emery Berger
  http://www.cs.umass.edu/~emery
  emery@cs.umass.edu
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*
 * @file   libdlmalloc.cpp
 * @brief  This file replaces malloc etc. in your application.
 * @author Emery Berger <http://www.cs.umass.edu/~emery>
 */

#include <stdlib.h>
#include <new>

class std::bad_alloc;

extern "C" {
  void * dlmalloc (size_t);
  void dlfree (void *);
  size_t dlmalloc_usable_size (void *);
}

int anyThreadCreated = 1;

class TheCustomHeapType {
public:
  inline void * malloc (size_t sz) {
    return dlmalloc(sz);
  }
  inline void free (void * ptr) {
    dlfree(ptr);
  }
  inline size_t getSize (void * ptr) {
    return dlmalloc_usable_size (ptr);
  }
};


inline static TheCustomHeapType * getCustomHeap (void) {
  static char thBuf[sizeof(TheCustomHeapType)];
  static TheCustomHeapType * th = new (thBuf) TheCustomHeapType;
  return th;
}

