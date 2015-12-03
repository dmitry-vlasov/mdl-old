/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_vector.hpp                                     */
/* Description:     basic vector types                                       */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_TYPES_VECTOR_HPP_
#define SMM_TYPES_VECTOR_HPP_

namespace smm {

	using nstd :: container :: Vector;

namespace vector {

	typedef
		Vector<value :: Literal, storage :: ByValue, allocator :: Heap>
		Literal;
}
}

#endif /*SMM_TYPES_VECTOR_HPP_*/
