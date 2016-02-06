/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_vector_index.hpp                               */
/* Description:     basic types for vectors of indexes                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace vector {
namespace index {

	typedef
		Vector<mdl :: value :: Literal, storage :: ByValue, allocator :: Heap>
		Literal;
	typedef
		Vector<mdl :: value :: Name, storage :: ByValue, allocator :: Heap>
		Name;
	typedef
		Vector<mdl :: value :: Kind, storage :: ByValue, allocator :: Heap>
		Kind;
}
}
}


