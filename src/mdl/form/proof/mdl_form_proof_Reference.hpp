/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Reference.hpp                             */
/* Description:     reference to the proof node                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_REFERENCE_HPP_
#define MDL_FORM_PROOF_REFERENCE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace form {
namespace proof {

class Reference :
	public mdl :: proof :: Reference,
	public Scalar<Reference> {
public :
	Reference
	(
		const Location&,
		value :: Kind,
		index :: Step,
		mdl :: proof :: Node* = NULL,
		mdl :: Theory* = NULL
	);
	Reference (const Reference&);
	Reference (const mdl :: proof :: Reference*);
	virtual ~ Reference();

	// mdl :: proof :: Reference interface
	virtual value :: Kind getKind() const;
	virtual index :: Step getIndex() const;
	virtual void build (mdl :: proof :: Scope*);
	virtual mdl :: proof :: Node* getNode();
	virtual const mdl :: proof :: Node* getNode() const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class refactor :: redundant :: Hypotheses;
	friend class refactor :: redundant :: Steps;


	const Location location_;
	value :: Kind kind_;
	index :: Step index_;
	mdl :: proof :: Node* node_;
};

}
}
}

#endif /*MDL_FORM_PROOF_REFERENCE_HPP_*/

