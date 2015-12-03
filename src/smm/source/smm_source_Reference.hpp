/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Reference.hpp                                 */
/* Description:     smm proof reference (element)                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_REFERENCE_HPP_
#define SMM_SOURCE_REFERENCE_HPP_

#include "smm/lexer/smm_lexer.hpp"
#include "smm/interface/smm_interface.hpp"

namespace smm {
namespace source {

class Reference : public Scalar<Reference> {
public :
	Reference();
	Reference (const Reference&);
	Reference
	(
		const Token :: Type,
		const value :: Index
	);
	~ Reference();

	Token :: Type getKind() const;
	value :: Index getIndex() const;

	void setKind (const Token :: Type);
	void setIndex (const value :: Index);

	bool operator == (const Reference&) const;
	bool operator != (const Reference&) const;
	void operator = (const Reference&);

	// object :: Object interface
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;

private :
	const Token :: Type kind_;
	const value :: Index index_;
};

	String&
	operator << (String&, const Reference&);
}

namespace vector{
	typedef
		Vector
		<
			source :: Reference,
			storage :: ByValue,
			allocator :: Heap
		>
		Reference;
}
}

#include "smm/source/smm_source_Reference.ipp"

#endif /*SMM_SOURCE_REFERENCE_HPP_*/
