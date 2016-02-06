/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Reference.ipp                                 */
/* Description:     smm proof reference (element)                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Reference :: Reference() :
	kind_ (Token :: UNKNOWN),
	index_ (value :: undefined :: INDEX) {
	}
	inline
	Reference :: Reference (const Reference& reference) :
	kind_ (reference.kind_),
	index_ (reference.index_) {
	}
	inline
	Reference :: Reference
	(
		const Token :: Type kind,
		const value :: Index index
	) :
	kind_ (kind),
	index_ (index) {
	}
	inline
	Reference :: ~ Reference() {
	}

	inline Token :: Type
	Reference :: getKind() const {
		return kind_;
	}
	inline value :: Index
	Reference :: getIndex() const {
		return index_;
	}

	inline void
	Reference :: setKind (const Token :: Type kind) {
		const_cast<Token :: Type&>(kind_) = kind;
	}
	inline void
	Reference :: setIndex (const value :: Index index) {
		const_cast<value :: Index&>(index_) = index;
	}

	inline bool
	Reference :: operator == (const Reference& reference) const
	{
		return
			kind_ == reference.kind_ &&
			index_ == reference.index_;
	}
	inline bool
	Reference :: operator != (const Reference& reference) const {
		return !operator == (reference);
	}
	inline void
	Reference :: operator = (const Reference& reference)
	{
		const_cast<Token :: Type&>(kind_) = reference.kind_;
		const_cast<value :: Index&>(index_) = reference.index_;
	}

	/*******************************
	 *		Overloaded operators
	 *******************************/

	inline String&
	operator << (String& string, const Reference& reference)
	{
		reference.show (string);
		return string;
	}
}
}


