/***************************************************************************

 Copyright (c) 2007 Sergey Prokhorchuk.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. Neither the name of the author nor the names of contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 SUCH DAMAGE.

***************************************************************************/

#ifndef __P3DGMESHDATA_H__
#define __P3DGMESHDATA_H__

#include <ngpcore/p3ddefs.h>

#define P3D_GMESH_MAX_ATTRS   (P3D_MAX_ATTRS - 1) // do not take into account P3D_ATTR_BILLBOARD_POS

class P3DGMeshData
 {
  public           :

                   P3DGMeshData       (const unsigned_int32 *VAttrCount,
                                       unsigned_int32        PrimitiveCount,
                                       unsigned_int32        IndexCount,
                                       unsigned_int32        VAttrCountI,
                                       unsigned_int32        IndexCountI);

                  ~P3DGMeshData       ();

  unsigned_int32     GetVAttrCount      (unsigned_int32        Attr) const;
  float           *GetVAttrBuffer     (unsigned_int32        Attr);
  const float     *GetVAttrBuffer     (unsigned_int32        Attr) const;
  unsigned_int32     GetPrimitiveCount  () const;
  unsigned_int32    *GetPrimitiveBuffer ();
  const
  unsigned_int32    *GetPrimitiveBuffer () const;
  unsigned_int32     GetIndexCount      () const;
  unsigned_int32    *GetIndexBuffer     (unsigned_int32        Attr) const;

  unsigned_int32     GetVAttrCountI     () const;
  float           *GetVAttrBufferI    (unsigned_int32        Attr);
  const float     *GetVAttrBufferI    (unsigned_int32        Attr) const;
  unsigned_int32     GetIndexCountI     () const;
  unsigned_int32    *GetIndexBufferI    () const;

  P3DGMeshData    *CreateCopy         () const;

  private          :

  float           *VAttrValues[P3D_GMESH_MAX_ATTRS];
  unsigned_int32     VAttrValueCounts[P3D_GMESH_MAX_ATTRS];
  unsigned_int32    *VAttrValueIndices[P3D_GMESH_MAX_ATTRS];
  unsigned_int32     VAttrValueIndexCount;
  unsigned_int32     PrimitiveCount;
  unsigned_int32    *PrimitiveTypes;

  unsigned_int32     VAttrCountI;
  float           *VAttrBuffersI[P3D_GMESH_MAX_ATTRS];
  unsigned_int32     IndexCountI;
  unsigned_int32    *IndexBufferI;
 };

#endif

