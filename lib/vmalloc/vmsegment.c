/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

#include	"vmhdr.h"

/*	Get the segment containing this address
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 02/07/95
*/

/**
 * @param vm region
 * @param addr address
 */
void *vmsegment(Vmalloc_t * vm, void * addr)
{
    reg Seg_t *seg;
    reg Vmdata_t *vd = vm->data;

    if (!(vd->mode & VM_TRUST)) {
	if (ISLOCK(vd, 0))
	    return NIL(void *);
	SETLOCK(vd, 0);
    }

    for (seg = vd->seg; seg; seg = seg->next)
	if ((Vmuchar_t *) addr >= (Vmuchar_t *) seg->addr &&
	    (Vmuchar_t *) addr < (Vmuchar_t *) seg->baddr)
	    break;

    CLRLOCK(vd, 0);
    return seg ? (void *) seg->addr : NIL(void *);
}
