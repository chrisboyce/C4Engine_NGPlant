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

#ifndef __P3DHLI_H__
#define __P3DHLI_H__

#include <ngpcore/p3dmathrng.h>
#include <ngpcore/p3dmodel.h>

#define P3DHLI_VER_MAJOR    (0)
#define P3DHLI_VER_MINOR    (9)
#define P3DHLI_VER_RELEASE  (6)

typedef float *(P3DHLIVAttrBufferSet[P3D_MAX_ATTRS]);

class P3D_DLL_ENTRY P3DHLIVAttrBuffers
 {
  public           :

                   P3DHLIVAttrBuffers ();

  void             AddAttr            (unsigned_int32        Attr,
                                       void               *Data,
                                       unsigned_int32        Offset,
                                       unsigned_int32        Stride);

  bool             HasAttr            (unsigned_int32        Attr) const;
  void            *GetAttrBuffer      (unsigned_int32        Attr) const;
  unsigned_int32     GetAttrOffset      (unsigned_int32        Attr) const;
  unsigned_int32     GetAttrStride      (unsigned_int32        Attr) const;

  private          :

  void            *Buffers[P3D_MAX_ATTRS];
  unsigned_int32     Offsets[P3D_MAX_ATTRS];
  unsigned_int32     Strides[P3D_MAX_ATTRS];
 };

/******************************************************************************/
/* NOTE: Class P3DHLIVAttrFormat and P3DHLIPlantInstance::FillVAttrBufferI    */
/* are obsolete. Both of them will be removed in one of the next version.     */
/* Please, use P3DHLIVAttrBuffers and  P3DHLIPlantInstance::FillVAttrBuffersI */
/* instead.                                                                   */
/******************************************************************************/

class P3D_DLL_ENTRY P3DHLIVAttrFormat
 {
  public           :

                   P3DHLIVAttrFormat  (unsigned_int32        Stride);

  bool             HasAttr            (unsigned_int32        Attr) const;
  unsigned_int32     GetAttrOffset      (unsigned_int32        Attr) const;
  unsigned_int32     GetStride          () const;
  void             AddAttr            (unsigned_int32        Attr,
                                       unsigned_int32        Offset);

  private          :

  bool             Enabled[P3D_MAX_ATTRS];
  unsigned_int32     Offsets[P3D_MAX_ATTRS];
  unsigned_int32     Stride;
 };

class P3DHLIPlantInstance;

class P3D_DLL_ENTRY P3DHLIPlantTemplate
 {
  public           :

                   P3DHLIPlantTemplate(P3DInputStringStream
                                                          *SourceStream);
                   P3DHLIPlantTemplate(const P3DPlantModel*SourceModel);

  unsigned_int32     GetGroupCount      () const;

  const char      *GetGroupName       (unsigned_int32        GroupIndex) const;

  const
  P3DMaterialDef  *GetMaterial        (unsigned_int32        GroupIndex) const;

  void             GetBillboardSize   (float              *Width,
                                       float              *Height,
                                       unsigned_int32        GroupIndex) const;

  bool             IsCloneable        (unsigned_int32        GroupIndex,
                                       bool                AllowScaling) const;

  /* LOD-related */

  bool             IsLODVisRangeEnabled
                                      (unsigned_int32        GroupIndex) const;

  void             GetLODVisRange     (float              *MinLOD,
                                       float              *MaxLOD,
                                       unsigned_int32        GroupIndex) const;

  /* Per-attribute mode */

  unsigned_int32     GetVAttrCount      (unsigned_int32        GroupIndex,
                                       unsigned_int32        Attr) const;

  void             FillCloneVAttrBuffer
                                      (void               *VAttrBuffer,
                                       unsigned_int32        GroupIndex,
                                       unsigned_int32        Attr) const;

  unsigned_int32     GetPrimitiveCount  (unsigned_int32        GroupIndex) const;
  unsigned_int32     GetPrimitiveType   (unsigned_int32        GroupIndex,
                                       unsigned_int32        PrimitiveIndex) const;

  void             FillVAttrIndexBuffer
                                      (void               *IndexBuffer,
                                       unsigned_int32        GroupIndex,
                                       unsigned_int32        Attr,
                                       unsigned_int32        ElementType,
                                       unsigned_int32        IndexBase = 0) const;

  /* Indexed mode */

  unsigned_int32     GetVAttrCountI     (unsigned_int32        GroupIndex) const;

  void             FillCloneVAttrBuffersI
                                      (const P3DHLIVAttrBuffers
                                                          *VAttrBuffers,
                                       unsigned_int32        GroupIndex) const;

  unsigned_int32     GetIndexCount      (unsigned_int32        GroupIndex,
                                       unsigned_int32        PrimitiveType) const;

  void             FillIndexBuffer    (void               *IndexBuffer,
                                       unsigned_int32        GroupIndex,
                                       unsigned_int32        PrimitiveType,
                                       unsigned_int32        ElementType,
                                       unsigned_int32        IndexBase = 0) const;

  P3DHLIPlantInstance
                  *CreateInstance     (unsigned_int32        BaseSeed = 0) const;

  private          :

  const P3DPlantModel                 *Model;
  P3DPlantModel                        OwnedModel;
 };

class P3D_DLL_ENTRY P3DHLIPlantInstance
 {
  public           :

                   P3DHLIPlantInstance(const P3DPlantModel*Model,
                                       unsigned_int32        BaseSeed);

  unsigned_int32     GetBranchCount     (unsigned_int32        GroupIndex) const;
  void             GetBranchCountMulti(unsigned_int32       *BranchCounts) const;
  void             GetBoundingBox     (float              *Min,
                                       float              *Max) const;

  /* Per-clone mode (use only for "cloneable" groups) */

  /* size of OffsetBuffer      must be sizeof(float) * GetBranchCount() * 3 */
  /* size of OrientationBuffer must be sizeof(float) * GetBranchCount() * 4 */
  /* size of ScaleBuffer       must be sizeof(float) * GetBranchCount()     */
  void             FillCloneTransformBuffer
                                      (float              *OffsetBuffer,
                                       float              *OrientationBuffer,
                                       float              *ScaleBuffer,
                                       unsigned_int32        GroupIndex) const;

  /* Per-attribute mode */

  unsigned_int32     GetVAttrCount      (unsigned_int32        GroupIndex,
                                       unsigned_int32        Attr) const;

  void             FillVAttrBuffer    (void               *VAttrBuffer,
                                       unsigned_int32        GroupIndex,
                                       unsigned_int32        Attr) const;

  /* Indexed mode */

  unsigned_int32     GetVAttrCountI     (unsigned_int32        GroupIndex) const;

  void             FillVAttrBufferI   (void               *VAttrBuffer,
                                       unsigned_int32        GroupIndex,
                                       const P3DHLIVAttrFormat
                                                          *VAttrFormat) const;

  void             FillVAttrBuffersI  (const P3DHLIVAttrBuffers
                                                          *VAttrBuffers,
                                       unsigned_int32        GroupIndex) const;

  void             FillVAttrBuffersIMulti
                                      (P3DHLIVAttrBufferSet
                                                          *VAttrBufferSet) const;

  private          :

  bool             IsRandomnessEnabled() const;

  const P3DPlantModel                 *Model;
  unsigned_int32                         BaseSeed;
 };

#endif

