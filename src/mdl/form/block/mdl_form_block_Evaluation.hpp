/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Evaluation.hpp                            */
/* Description:     assertion usage experience                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_EVALUATION_HPP_
#define MDL_FORM_BLOCK_EVALUATION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"

namespace mdl {
namespace form {
namespace block {

class Evaluation :
	public mdl :: Evaluation,
	public Identifiable,
	public Scalar<Evaluation> {
public :
	Evaluation
	(
		value :: Name,
		mdl :: Assertion*
	);
	Evaluation
	(
		const Location&,
		const mdl :: Comments*,
		value :: Name,
		mdl :: Identificator*,
		const mdl :: evaluation :: parser :: vector :: Function&,
		mdl :: Theory*
	);
	virtual ~ Evaluation();

	// mdl :: Evaluation interface
	virtual void setToDefault();
	virtual index :: Arity getSize() const;
	virtual mdl :: evaluation :: Function* getFunction (const index :: Arity);
	virtual const mdl :: evaluation :: Function* getFunction (const index :: Arity) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		form :: evaluation :: function :: WeightedSum
		DefaultFunction_;

	mdl :: Identificator* assertionId_;
	mdl :: evaluation :: vector :: Function functionVector_;
	mdl :: Assertion* assertion_;
};

}
}
}

#endif /*MDL_FORM_BLOCK_EVALUATION_HPP_*/
